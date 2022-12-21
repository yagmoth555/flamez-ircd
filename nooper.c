/* Nooper/SNOpper list functions.
 *
 * That Nooper/snooper add-on is based from the original idea
 * from uworld, The devel. of it is mainly because uworld
 * source are almost impossible to get and that add-on can
 * be a great tool to prevent takeover attempt by unthrusty 
 * operator and/or server. A must for any network that want 
 * additionnal security.
 * Copyright (c) 2001 Philippe Levesque <EMail: yagmoth555.yahoo.com>
 *
 *
 * IRC Services is copyright (c) 1996-2001 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "pseudo.h"

/*************************************************************************/

typedef struct nooper Nooper;
struct nooper {
    char *mask;
    char *reason;
    char who[NICKMAX];
    time_t time;
};

static int32 nnooper = 0;
static int32 nooper_size = 0;
static struct nooper *noopers = NULL;

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_nooper_stats(long *nrec, long *memuse)
{
    long mem;
    int i;

    mem = sizeof(struct nooper) * nooper_size;
    for (i = 0; i < nnooper; i++) {
	mem += strlen(noopers[i].mask)+1;
	mem += strlen(noopers[i].reason)+1;
    }
    *nrec = nnooper;
    *memuse = mem;
}


int num_noopers(void)
{
    return (int) nnooper;
}

/*************************************************************************/
/************************** INPUT/OUTPUT functions ***********************/
/*************************************************************************/
#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", NooperDBName);	\
	nnooper = i;					\
	break;						\
    }							\
} while (0)

void load_nooper(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;
    int32 tmp32;

    if (!(f = open_db("NOOPER", NooperDBName, "r")))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    nnooper = tmp16;
    if (nnooper < 8)
	nooper_size = 16;
    else if (nnooper >= 16384)
	nooper_size = 32767;
    else
	nooper_size = 2*nnooper;
    noopers = scalloc(sizeof(*noopers), nooper_size);

    switch (ver) {
      case 11:
	for (i = 0; i < nnooper; i++) {
	    SAFE(read_string(&noopers[i].mask, f));
	    SAFE(read_string(&noopers[i].reason, f));
	    SAFE(read_buffer(noopers[i].who, f));
	    SAFE(read_int32(&tmp32, f));
	    noopers[i].time = tmp32;
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", NooperDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, NooperDBName);
    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_nooper(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db("NOOPER", NooperDBName, "w");
    write_int16(nnooper, f);
    for (i = 0; i < nnooper; i++) {
	SAFE(write_string(noopers[i].mask, f));
	SAFE(write_string(noopers[i].reason, f));
	SAFE(write_buffer(noopers[i].who, f));
	SAFE(write_int32(noopers[i].time, f));
    }
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", NooperDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", NooperDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/************************** External functions ***************************/
/*************************************************************************/

/* Does the user that is dooing a +o match any nooper added?, if yes return 1,
 * else 0. 
 *	TO-DO, Add a command line to desactivate the nooper/snooper check.
 *		   Use the nick to KILL the person, in case it try too much time to oper up.
 */

int is_nooper(const char *nick, const char *username, const char *host)
{
    char buf[BUFSIZE];
    int i;

    snprintf(buf, sizeof(buf), "%s@%s", username, host);
    for (i = 0; i < nnooper; i++) {
	if (match_wild_nocase(noopers[i].mask, buf)) {
	    /* We return 1 rigth now, the +o is only gonna be ignored
		 * from m_modes and we display a warning to other opers online. */
		wallops(s_OperServ, "Removing IRC operator modes on \2%s\2 ,host(\2%s\2) matching in the \2NOOPER\2 list", nick, buf);
		return 1;
	}
    }
    return 0;
}

/*************************************************************************/
/************************** NOOPER list editing **************************/
/*************************************************************************/

/* Note that all string parameters are assumed to be non-NULL.
 */

void add_nooper(const char *mask, const char *reason, const char *who)
{
    Nooper *nooper;
	char buf[BUFSIZE];
	User *u;

    if (nnooper >= 32767) {
	log("%s: Attempt to add NOOPER to full list!", s_OperServ);
	return;
    }

	if (nnooper >= nooper_size) {
	if (nooper_size < 8)
	    nooper_size = 8;
	else if (nooper_size >= 16384)
	    nooper_size = 32767;
	else
	    nooper_size *= 2;
	noopers = srealloc(noopers, sizeof(*noopers) * nooper_size);
    }
    nooper = &noopers[nnooper];
    nooper->mask = sstrdup(mask);
    nooper->reason = sstrdup(reason);
    nooper->time = time(NULL);
    strscpy(nooper->who, who, NICKMAX);
	nnooper++;
	
	/* here, we will try to find user matching that mask....  */
	/* if there is a better way to do that, let me know -jabea */
    for (u = firstuser(); u; u = nextuser()) {
		if (is_oper_u(u)) {
			snprintf(buf, sizeof(buf), "%s@%s", u->username, u->host);
			if (match_wild_nocase(mask, buf)) {
				send_cmd(s_NickServ, "SVSMODE %s :-oOaA", u->nick);
				if (WallOSNooper)
				wallops(s_OperServ, "Removing IRC operator modes on \2%s\2 ,host(\2%s\2) matching in the \2NOOPER\2 list", 
						u->nick, buf);
			}
		}
    }
	/* end of search */
}

/*************************************************************************/

/* Return whether the mask was found in the NOOPER list. */

static int del_nooper(const char *mask)
{
    int i;

    for (i = 0; i < nnooper && strcmp(noopers[i].mask, mask) != 0; i++)
	;
    if (i < nnooper) {
	free(noopers[i].mask);
	free(noopers[i].reason);
	nnooper--;
	if (i < nnooper)
	    memmove(noopers+i, noopers+i+1, sizeof(*noopers) * (nnooper-i));
	return 1;
    } else {
	return 0;
    }
}

/*************************************************************************/

/* Handle an OperServ NOOPER command. */

void do_nooper(User *u)
{
    char *cmd, *mask, *reason, *s, *t;
    int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	//time_t now = time(NULL);

	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
		}

	if (nnooper >= 32767) {
	    return;
	}

	mask = strtok(NULL, " ");
	reason = strtok(NULL, "");

	if (!reason) {
		send_cmd(s_OperServ, "NOTICE %s :NOOPER ADD \2mask\2 \2reason\2", u->nick);
	    return;
	}

	if (strchr(mask, '!')) {
		send_cmd(s_OperServ, "NOTICE %s :\2Notice\2: NOOPER masks cannot contain nicknames; make sure you have \2not\2 included a nick portion in your mask.", u->nick);
		send_cmd(s_OperServ, "NOTICE %s :Mask must be in the form \2username\2@\2host\2", u->nick);
	    return;
	}
	s = strchr(mask, '@');
	if (!s) {
	    send_cmd(s_OperServ, "NOTICE %s :Mask must be in the form \2username\2@\2host\2", u->nick);
	    return;
	}

	/* Make sure mask does not already exist on nooper list. */
	for (i = 0; i < nnooper && strcmp(noopers[i].mask, mask) != 0; i++)
	    ;
	if (i < nnooper) {
	    send_cmd(s_OperServ, "NOTICE %s :NOOPER mask already exist!", u->nick);
	    return;
	}

	/* Make sure mask is not too general. */
	*s++ = 0;
	if (strchr(mask,'*') != NULL && mask[strspn(mask,"*?")] == 0
	 && ((t = strchr(mask,'?')) == NULL || strchr(t,'?') == NULL)
	) {
	    /* Username part matches anything; check host part */
	    if (strchr(s,'*') != NULL && s[strspn(s,"*?.")] == 0
	     && ((t = strchr(mask,'.')) == NULL || strchr(t,'.') == NULL)
	    ) {
		/* Hostname mask matches anything or nearly anything, so
		 * disallow mask. */
		send_cmd(s_OperServ, "NOTICE %s :NOOPER \2mask\2 a lot to general", u->nick);
		return;
	    }
	}
	s[-1] = '@';	/* Replace "@" that we killed above */

	strlower(mask);
	add_nooper(mask, reason, u->nick);
	send_cmd(s_OperServ, "NOTICE %s :NOOPER succesfully added \2%s\2", u->nick, mask);
	if (WallOSNooper) {
	    wallops(s_OperServ, "%s added an NOOPER for \2%s\2 (%s)",
		    u->nick, mask, reason);
	}
	if (readonly)
		notice_lang(s_OperServ, u, READ_ONLY_MODE);
    } else if (stricmp(cmd, "DEL") == 0) {
	
	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
		}	
	mask = strtok(NULL, " ");
	if (mask) {
	    strlower(mask);
	    if (del_nooper(mask)) {
		send_cmd(s_OperServ, "NOTICE %s :NOOPER succesfully removed \2%s\2", u->nick, mask);
		if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		send_cmd(s_OperServ, "NOTICE %s :NOOPER not found for \2%s\2", u->nick, mask);
	    }
	} else {
	    send_cmd(s_OperServ, "NOTICE %s :\2%s\2 not found on the NOOPER list", u->nick, mask);
	}

    } else if (stricmp(cmd, "LIST") == 0 || stricmp(cmd, "VIEW") == 0) {
	int is_view = stricmp(cmd,"VIEW")==0;

	s = strtok(NULL, " ");
	if (!s)
	    s = "*";

	if (strchr(s, '@'))
	    strlower(strchr(s, '@'));
	send_cmd(s_OperServ, "NOTICE %s :Current NOOPER list", u->nick);
	for (i = 0; i < nnooper; i++) {
	    if (!s || (match_wild(s, noopers[i].mask))) {
		if (is_view) {
		    char timebuf[BUFSIZE];
		    struct tm tm;
		    time_t t = time(NULL);

		    tm = *localtime(noopers[i].time ? &noopers[i].time : &t);
		    strftime_lang(timebuf, sizeof(timebuf),
				  u, STRFTIME_SHORT_DATE_FORMAT, &tm);
			send_cmd(s_OperServ, "NOTICE %s :%s (by %s on %s) %s", u->nick, noopers[i].mask,
				*noopers[i].who ? noopers[i].who : "<unknown>", timebuf, noopers[i].reason);
		} else { /* !is_view */
			send_cmd(s_OperServ, "NOTICE %s :%-32s %s", u->nick, noopers[i].mask, noopers[i].reason);
		}
	    }
	}

    } else if (stricmp(cmd, "COUNT") == 0) {
	send_cmd(s_OperServ, "NOTICE %s :There is %d peoples on the nooper list.", u->nick, nnooper);

    } else {
	send_cmd(s_OperServ, "NOTICE %s :NOOPER {ADD | DEL | LIST | VIEW | COUNT} [mask. [.reason.]].", u->nick);
    }
}

/*************************************************************************/

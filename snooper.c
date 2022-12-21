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

typedef struct snooper SNooper;
struct snooper {
    char *mask;
    char *reason;
    char who[NICKMAX];
    time_t time;
};

static int32 nsnooper = 0;
static int32 snooper_size = 0;
static struct snooper *snoopers = NULL;

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_snooper_stats(long *nrec, long *memuse)
{
    long mem;
    int i;

    mem = sizeof(struct snooper) * snooper_size;
    for (i = 0; i < nsnooper; i++) {
	mem += strlen(snoopers[i].mask)+1;
	mem += strlen(snoopers[i].reason)+1;
    }
    *nrec = nsnooper;
    *memuse = mem;
}


int num_snoopers(void)
{
    return (int) nsnooper;
}

/*************************************************************************/
/************************** INPUT/OUTPUT functions ***********************/
/*************************************************************************/
#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", SNooperDBName);	\
	nsnooper = i;					\
	break;						\
    }							\
} while (0)

void load_snooper(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;
    int32 tmp32;

    if (!(f = open_db("SNOOPER", SNooperDBName, "r")))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    nsnooper = tmp16;
    if (nsnooper < 8)
	snooper_size = 16;
    else if (nsnooper >= 16384)
	snooper_size = 32767;
    else
	snooper_size = 2*nsnooper;
    snoopers = scalloc(sizeof(*snoopers), snooper_size);

    switch (ver) {
      case 11:
	for (i = 0; i < nsnooper; i++) {
	    SAFE(read_string(&snoopers[i].mask, f));
	    SAFE(read_string(&snoopers[i].reason, f));
	    SAFE(read_buffer(snoopers[i].who, f));
	    SAFE(read_int32(&tmp32, f));
	    snoopers[i].time = tmp32;
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", SNooperDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, SNooperDBName);
    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_snooper(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db("SNOOPER", SNooperDBName, "w");
    write_int16(nsnooper, f);
    for (i = 0; i < nsnooper; i++) {
	SAFE(write_string(snoopers[i].mask, f));
	SAFE(write_string(snoopers[i].reason, f));
	SAFE(write_buffer(snoopers[i].who, f));
	SAFE(write_int32(snoopers[i].time, f));
    }
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", SNooperDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", SNooperDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/************************** External functions ***************************/
/*************************************************************************/

/* Does the user that is dooing a +o match any snooper added?, if yes return 1,
 * else 0. 
 *	TO-DO, Add a command line to desactivate the nooper/snooper check.
 *		   Use the nick to KILL the person, in case it try too much time to oper up.
 */

int is_snooper(const char *nick, const Server *server)
{
    char buf[BUFSIZE];
    int i;

    snprintf(buf, sizeof(buf), "%s", server->name);
    for (i = 0; i < nsnooper; i++) {
	if (match_wild_nocase(snoopers[i].mask, buf)) {
	    /* We return 1 rigth now, the +o is only gonna be ignored
		 * from m_modes and we display a warning to other opers online. */
		if (WallOSSNooper)
			wallops(s_OperServ, "Removing Operator modes on \2%s\2 %s. Server was found on the SNOOPER list.", nick, buf);
		return 1;
	}
    }
    return 0;
}

/*************************************************************************/
/************************** SNOOPER list editing *************************/
/*************************************************************************/

/* Note that all string parameters are assumed to be non-NULL.
 */

void add_snooper(const char *mask, const char *reason, const char *who)
{
    SNooper *snooper;
	char buf[BUFSIZE];
	User *u;

    if (nsnooper >= 32767) {
	log("%s: Attempt to add SNOOPER to full list!", s_OperServ);
	return;
    }

	if (nsnooper >= snooper_size) {
	if (snooper_size < 8)
	    snooper_size = 8;
	else if (snooper_size >= 16384)
	    snooper_size = 32767;
	else
	    snooper_size *= 2;
	snoopers = srealloc(snoopers, sizeof(*snoopers) * snooper_size);
    }
    snooper = &snoopers[nsnooper];
    snooper->mask = sstrdup(mask);
    snooper->reason = sstrdup(reason);
    snooper->time = time(NULL);
    strscpy(snooper->who, who, NICKMAX);
	nsnooper++;

	/* here, we will try to find user matching that mask....  */
	/* if there is a better way to do that, let me know -jabea */
    for (u = firstuser(); u; u = nextuser()) {
		if (is_oper_u(u)) {
			snprintf(buf, sizeof(buf), "%s", u->server->name);
			if (match_wild_nocase(mask, buf)) {
				send_cmd(s_NickServ, "SVSMODE %s :-oOaA", u->nick);
				if (WallOSSNooper)
					wallops(s_OperServ, "Removing Operator modes on \2%s\2 %s. Server was found on the SNOOPER list.", u->nick, buf);
			}
		}
    }
	/* end of search */
}

/*************************************************************************/

/* Return whether the mask was found in the SNOOPER list. */

static int del_snooper(const char *mask)
{
    int i;

    for (i = 0; i < nsnooper && strcmp(snoopers[i].mask, mask) != 0; i++)
	;
    if (i < nsnooper) {
	free(snoopers[i].mask);
	free(snoopers[i].reason);
	nsnooper--;
	if (i < nsnooper)
	    memmove(snoopers+i, snoopers+i+1, sizeof(*snoopers) * (nsnooper-i));
	return 1;
    } else {
	return 0;
    }
}

/*************************************************************************/

/* Handle an OperServ SNOOPER command. */

void do_snooper(User *u)
{
    char *cmd, *mask, *reason, *s;
    int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	//time_t now = time(NULL);

	if (!is_services_root(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
		}

	if (nsnooper >= 32767) {
	    return;
	}

	mask = strtok(NULL, " ");
	reason = strtok(NULL, "");

	if (!reason) {
		send_cmd(s_OperServ, "NOTICE %s :SNOOPER ADD \2mask\2 \2reason\2", u->nick);
	    return;
	}

	if (strchr(mask, '!')) {
		send_cmd(s_OperServ, "NOTICE %s :\2Notice\2: SNOOPER masks cannot contain nicknames or ident; make sure you have \2not\2 included a nick or ident portion in your mask.", u->nick);
		send_cmd(s_OperServ, "NOTICE %s :Mask must be in the form \2host\2", u->nick);
	    return;
	}
	s = strchr(mask, '@');
	if (s) {
	    send_cmd(s_OperServ, "NOTICE %s :Mask must be in the form \2host\2", u->nick);
	    return;
	}

	
	/* Make sure mask does not already exist on snooper list. */
	for (i = 0; i < nsnooper && strcmp(snoopers[i].mask, mask) != 0; i++)
	    ;
	if (i < nsnooper) {
	    send_cmd(s_OperServ, "NOTICE %s :SNOOPER mask already exist!", u->nick);
	    return;
	}

	/* Make sure mask is not too general. */
	s = strchr(mask, '*');
	if (s) {
	    send_cmd(s_OperServ, "NOTICE %s :SNOOPER \2mask\2 \2dont\2 accept wildcard", u->nick);
	    return;
	}
	s = strchr(mask, '?');
	if (s) {
	    send_cmd(s_OperServ, "NOTICE %s :SNOOPER \2mask\2 \2dont\2 accept wildcard", u->nick);
	    return;
	}

	strlower(mask);
	add_snooper(mask, reason, u->nick);
	send_cmd(s_OperServ, "NOTICE %s :SNOOPER succesfully added \2%s\2", u->nick, mask);
	if (WallOSSNooper) {
	    wallops(s_OperServ, "%s added an SNOOPER for \2%s\2 (%s)",
		    u->nick, mask, reason);
	}
	if (readonly)
		notice_lang(s_OperServ, u, READ_ONLY_MODE);
    } else if (stricmp(cmd, "DEL") == 0) {
	
	if (!is_services_root(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
		}	
	mask = strtok(NULL, " ");
	if (mask) {
	    strlower(mask);
	    if (del_snooper(mask)) {
		send_cmd(s_OperServ, "NOTICE %s :SNOOPER succesfully removed \2%s\2", u->nick, mask);
		if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		send_cmd(s_OperServ, "NOTICE %s :SNOOPER not found for \2%s\2", u->nick, mask);
	    }
	} else {
	    send_cmd(s_OperServ, "NOTICE %s :\2%s\2 not found on the SNOOPER list", u->nick, mask);
	}

    } else if (stricmp(cmd, "LIST") == 0 || stricmp(cmd, "VIEW") == 0) {
	int is_view = stricmp(cmd,"VIEW")==0;

	s = strtok(NULL, " ");
	if (!s)
	    s = "*";

	send_cmd(s_OperServ, "NOTICE %s :Current SNOOPER list", u->nick);
	for (i = 0; i < nsnooper; i++) {
	    if (!s || (match_wild(s, snoopers[i].mask))) {
		if (is_view) {
		    char timebuf[BUFSIZE];
		    struct tm tm;
		    time_t t = time(NULL);

		    tm = *localtime(snoopers[i].time ? &snoopers[i].time : &t);
		    strftime_lang(timebuf, sizeof(timebuf),
				  u, STRFTIME_SHORT_DATE_FORMAT, &tm);
			send_cmd(s_OperServ, "NOTICE %s :%s (by %s on %s) %s", u->nick, snoopers[i].mask,
				*snoopers[i].who ? snoopers[i].who : "<unknown>", timebuf, snoopers[i].reason);
		} else { /* !is_view */
			send_cmd(s_OperServ, "NOTICE %s :%-32s %s", u->nick, snoopers[i].mask, snoopers[i].reason);
		}
	    }
	}

    } else if (stricmp(cmd, "COUNT") == 0) {
	send_cmd(s_OperServ, "NOTICE %s :There is %d peoples on the snooper list.", u->nick, nsnooper);

    } else {
	send_cmd(s_OperServ, "NOTICE %s :SNOOPER {ADD | DEL | LIST | VIEW | COUNT} [mask. [.reason.]].", u->nick);
    }
}

/*************************************************************************/

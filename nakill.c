/* Nakill list functions.
 *
 * NAkill is primary a way to akill from a nick
 * to prevent a lot of clone, it's always handy 
 * to have that functionnality
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

typedef struct nakill Nakill;
struct nakill {
    char *nick;
    char *reason;
    char who[NICKMAX];
    time_t time;
};

static int32 nnakill = 0;
static int32 nakill_size = 0;
static struct nakill *nakills = NULL;

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_nakill_stats(long *nrec, long *memuse)
{
    long mem;
    int i;

    mem = sizeof(struct nakill) * nakill_size;
    for (i = 0; i < nnakill; i++) {
	mem += strlen(nakills[i].nick)+1;
	mem += strlen(nakills[i].reason)+1;
    }
    *nrec = nnakill;
    *memuse = mem;
}


int num_nakills(void)
{
    return (int) nnakill;
}

/*************************************************************************/
/************************** INPUT/OUTPUT functions ***********************/
/*************************************************************************/
#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", NakillDBName);	\
	nnakill = i;					\
	break;						\
    }							\
} while (0)

void load_nakill(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;
    int32 tmp32;

    if (!(f = open_db("NAKILL", NakillDBName, "r")))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    nnakill = tmp16;
    if (nnakill < 8)
	nakill_size = 16;
    else if (nnakill >= 16384)
	nakill_size = 32767;
    else
	nakill_size = 2*nnakill;
    nakills = scalloc(sizeof(*nakills), nakill_size);

    switch (ver) {
      case 11:
	for (i = 0; i < nnakill; i++) {
	    SAFE(read_string(&nakills[i].nick, f));
	    SAFE(read_string(&nakills[i].reason, f));
	    SAFE(read_buffer(nakills[i].who, f));
	    SAFE(read_int32(&tmp32, f));
	    nakills[i].time = tmp32;
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", NakillDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, NakillDBName);
    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_nakill(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db("NAKILL", NakillDBName, "w");
    write_int16(nnakill, f);
    for (i = 0; i < nnakill; i++) {
	SAFE(write_string(nakills[i].nick, f));
	SAFE(write_string(nakills[i].reason, f));
	SAFE(write_buffer(nakills[i].who, f));
	SAFE(write_int32(nakills[i].time, f));
    }
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", NakillDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", NakillDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/************************** External functions ***************************/
/*************************************************************************/

/* Does the user that is dooing a nick change match any nick added?, if yes return 1,
 * else 0. 
 */

int check_nakill(const char *nick, const char *host)
{
    char buf[BUFSIZE];
    int i;

    
    for (i = 0; i < nnakill; i++) {
	if (match_wild_nocase(nakills[i].nick, nick)) {
		if (!is_akilled(host)) {
			send_cmd(s_OperServ, "KILL %s :%s (%s)", nick, s_OperServ, nakills[i].reason);
			snprintf(buf, sizeof(buf), "*@%s", host);
			add_akill(buf, nakills[i].reason, s_OperServ, time(NULL) + AutokillExpiry);
			if (WallOSNakill) {
				char buffer[128];
				expires_in_lang(buffer, sizeof(buffer), NULL, time(NULL) + AutokillExpiry);
				wallops(s_OperServ, "%s added an AKILL for \2%s\2 (%s)", s_OperServ, buf, buffer);
				}
			return 1;
		}
	}
    }
    return 0;
}

/* Does the user that is dooing a nick change match any nick added?, if yes return 1,
 * else 0. (use kill_user, not the KILL msg, user already logged when that call got called
 */
int is_nakill(const char *host, const char *nick)
{
    char buf[BUFSIZE];
    int i;

    snprintf(buf, sizeof(buf), "%s", nick);
    for (i = 0; i < nnakill; i++) {
	if (match_wild_nocase(nakills[i].nick, buf)) {
		if (!is_akilled(host)) {
			snprintf(buf, sizeof(buf), "*@%s", host);
			add_akill(buf, nakills[i].reason, s_OperServ, time(NULL) + AutokillExpiry);
			if (WallOSNakill) {
				char buffer[128];
				expires_in_lang(buffer, sizeof(buffer), NULL, time(NULL) + AutokillExpiry);
				wallops(s_OperServ, "%s added an AKILL for \2%s\2 (%s)", s_OperServ, buf, buffer);
				}
			return 1;
		}
	}
	}
    return 0;
}

/*************************************************************************/
/************************** NAKILL list editing **************************/
/*************************************************************************/

/* Note that all string parameters are assumed to be non-NULL.
 */
void add_nakill(const char *mask, const char *reason, const char *who)
{
    Nakill *nakill;
	User *u, *next;

    if (nnakill >= 32767) {
	log("%s: Attempt to add a Nakill to full list!", s_OperServ);
	return;
    }

	if (nnakill >= nakill_size) {
	if (nakill_size < 8)
	    nakill_size = 8;
	else if (nakill_size >= 16384)
	    nakill_size = 32767;
	else
	    nakill_size *= 2;
	nakills = srealloc(nakills, sizeof(*nakills) * nakill_size);
    }
    nakill = &nakills[nnakill];
    nakill->nick = sstrdup(mask);
    nakill->reason = sstrdup(reason);
    nakill->time = time(NULL);
    strscpy(nakill->who, who, NICKMAX);
	nnakill++;

	/* here, we will try to find user matching that nick....  */
	/* if there is a better way to do that, let me know -jabea */
    //for (u = firstuser(); u; u = nextuser()) {
	//	if (match_wild_nocase(mask, u->nick)) {
	//		kill_user(s_OperServ, u->nick, nakill->reason);
	//	}
	//}
	u = firstuser();
	while (u)
	{
		next = nextuser();
		if (match_wild_nocase(mask, u->nick)) {
			kill_user(s_OperServ, u->nick, nakill->reason);
		}
		u = next;
	}
	/* end of search */
}

/*************************************************************************/

/* Return whether the mask was found in the nakill list. */

static int del_nakill(const char *mask)
{
    int i;

    for (i = 0; i < nnakill && stricmp(nakills[i].nick, mask) != 0; i++)
	;
    if (i < nnakill) {
	free(nakills[i].nick);
	free(nakills[i].reason);
	nnakill--;
	if (i < nnakill)
	    memmove(nakills+i, nakills+i+1, sizeof(*nakills) * (nnakill-i));
	return 1;
    } else {
	return 0;
    }
}

/*************************************************************************/

/* Handle an OperServ nakill command. */

void do_nakill(User *u)
{
    char *cmd, *mask, *reason, *s;
    int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {

	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
		}

	if (nnakill >= 32767) {
	    return;
	}

	mask = strtok(NULL, " ");
	reason = strtok(NULL, "");

	if (!reason) {
		send_cmd(s_OperServ, "NOTICE %s :NAKILL ADD \2mask\2 \2reason\2", u->nick);
	    return;
	}

	/* Make sure mask does not already exist on nakill list. */
	for (i = 0; i < nnakill && stricmp(nakills[i].nick, mask) != 0; i++)
	    ;
	if (i < nnakill) {
	    send_cmd(s_OperServ, "NOTICE %s :NAKILL nick already exist!", u->nick);
	    return;
	}

	add_nakill(mask, reason, u->nick);
	send_cmd(s_OperServ, "NOTICE %s :NAKILL succesfully added \2%s\2", u->nick, mask);
	if (WallOSNakill) {
	    wallops(s_OperServ, "%s added an NAKILL for \2%s\2 (%s)",
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
	    if (del_nakill(mask)) {
		send_cmd(s_OperServ, "NOTICE %s :NAKILL succesfully removed \2%s\2", u->nick, mask);
		if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		send_cmd(s_OperServ, "NOTICE %s :NAKILL not found for \2%s\2", u->nick, mask);
	    }
	} else {
	    send_cmd(s_OperServ, "NOTICE %s :\2%s\2 not found on the NAKILL list", u->nick, mask);
	}

    } else if (stricmp(cmd, "LIST") == 0 || stricmp(cmd, "VIEW") == 0) {
	int is_view = stricmp(cmd,"VIEW")==0;

	s = strtok(NULL, " ");
	if (!s)
	    s = "*";

	send_cmd(s_OperServ, "NOTICE %s :Current NAKILL list", u->nick);
	for (i = 0; i < nnakill; i++) {
	    if (!s || (match_wild(s, nakills[i].nick))) {
		if (is_view) {
		    char timebuf[BUFSIZE];
		    struct tm tm;
		    time_t t = time(NULL);

		    tm = *localtime(nakills[i].time ? &nakills[i].time : &t);
		    strftime_lang(timebuf, sizeof(timebuf),
				  u, STRFTIME_SHORT_DATE_FORMAT, &tm);
			send_cmd(s_OperServ, "NOTICE %s :%s (by %s on %s) %s", u->nick, nakills[i].nick,
				*nakills[i].who ? nakills[i].who : "<unknown>", timebuf, nakills[i].reason);
		} else { /* !is_view */
			send_cmd(s_OperServ, "NOTICE %s :%-32s %s", u->nick, nakills[i].nick, nakills[i].reason);
		}
	    }
	}

    } else if (stricmp(cmd, "COUNT") == 0) {
	send_cmd(s_OperServ, "NOTICE %s :There is %d peoples on the NAKILL list.", u->nick, nnakill);

    } else {
	send_cmd(s_OperServ, "NOTICE %s :NAKILL {ADD | DEL | LIST | VIEW | COUNT} [mask. [.reason.]].", u->nick);
    }
}

/*************************************************************************/

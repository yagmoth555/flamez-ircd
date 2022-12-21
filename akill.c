/* Autokill list functions.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "pseudo.h"

/*************************************************************************/

typedef struct akill Akill;
struct akill {
    char *mask;
    char *reason;
    char who[NICKMAX];
    time_t time;
    time_t expires;	/* or 0 for no expiry */
};

static int32 nakill = 0;
static int32 akill_size = 0;
static struct akill *akills = NULL;

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_akill_stats(long *nrec, long *memuse)
{
    long mem;
    int i;

    mem = sizeof(struct akill) * akill_size;
    for (i = 0; i < nakill; i++) {
	mem += strlen(akills[i].mask)+1;
	mem += strlen(akills[i].reason)+1;
    }
    *nrec = nakill;
    *memuse = mem;
}


int num_akills(void)
{
    return (int) nakill;
}

/*************************************************************************/
/*********************** AKILL database load/save ************************/
/*************************************************************************/

#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", AutokillDBName);	\
	nakill = i;					\
	break;						\
    }							\
} while (0)

void load_akill(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;
    int32 tmp32;

    if (!(f = open_db("AKILL", AutokillDBName, "r")))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    nakill = tmp16;
    if (nakill < 8)
	akill_size = 16;
    else if (nakill >= 16384)
	akill_size = 32767;
    else
	akill_size = 2*nakill;
    akills = scalloc(sizeof(*akills), akill_size);

    switch (ver) {
      case 11:
      case 10:
      case 9:
      case 8:
      case 7:
      case 6:
      case 5:
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	    SAFE(read_buffer(akills[i].who, f));
	    SAFE(read_int32(&tmp32, f));
	    akills[i].time = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    akills[i].expires = tmp32;
	}
	break;

      case 4:
      case 3: {
	struct {
	    char *mask;
	    char *reason;
	    char who[NICKMAX];
	    time_t time;
	    time_t expires;
	    long reserved[4];
	} old_akill;

	for (i = 0; i < nakill; i++) {
	    SAFE(read_variable(old_akill, f));
	    strscpy(akills[i].who, old_akill.who, NICKMAX);
	    akills[i].time = old_akill.time;
	    akills[i].expires = old_akill.expires;
	}
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	}
	break;
      } /* case 3/4 */

      case 2: {
	struct {
	    char *mask;
	    char *reason;
	    char who[NICKMAX];
	    time_t time;
	} old_akill;

	for (i = 0; i < nakill; i++) {
	    SAFE(read_variable(old_akill, f));
	    akills[i].time = old_akill.time;
	    strscpy(akills[i].who, old_akill.who, sizeof(akills[i].who));
	    akills[i].expires = 0;
	}
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	}
	break;
      } /* case 2 */

      case 1: {
	struct {
	    char *mask;
	    char *reason;
	    time_t time;
	} old_akill;

	for (i = 0; i < nakill; i++) {
	    SAFE(read_variable(old_akill, f));
	    akills[i].time = old_akill.time;
	    akills[i].who[0] = 0;
	    akills[i].expires = 0;
	}
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	}
	break;
      } /* case 1 */

      case -1:
	fatal("Unable to read version number from %s", AutokillDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, AutokillDBName);
    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_akill(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db("AKILL", AutokillDBName, "w");
    write_int16(nakill, f);
    for (i = 0; i < nakill; i++) {
	SAFE(write_string(akills[i].mask, f));
	SAFE(write_string(akills[i].reason, f));
	SAFE(write_buffer(akills[i].who, f));
	SAFE(write_int32(akills[i].time, f));
	SAFE(write_int32(akills[i].expires, f));
    }
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", AutokillDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", AutokillDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/************************** Internal functions ***************************/
/*************************************************************************/

static void send_akill(const Akill *akill)
{
#if defined(IRC_DALNET) || defined(IRC_UNDERNET)
    char *username;
    char *host;
#if defined(IRC_BAHAMUT) || defined(IRC_UNDERNET)
    time_t now = time(NULL);
#endif

    username = sstrdup(akill->mask);
    host = strchr(username, '@');
    if (!host) {
	/* Glurp... this oughtn't happen, but if it does, let's not
	 * play with null pointers.  Yell and bail out.
	 */
	wallops(NULL, "Missing @ in AKILL: %s", akill->mask);
	log("Missing @ in AKILL: %s", akill->mask);
	return;
    }
    *host++ = 0;

#if defined(IRC_UNREAL)
    send_cmd(ServerName,
	    "TKL + G %s %s %s %ld %ld :%s",
	    username, host, akill->who ? akill->who : "<unknown>",
	    akill->expires, akill->time,
	    StaticAkillReason ? StaticAkillReason : akill->reason);
#elif defined(IRC_BAHAMUT)
    send_cmd(ServerName,
	    "AKILL %s %s %ld %s %ld :%s",
	    host, username,
	    (akill->expires && akill->expires > now)
			? akill->expires - now
			: 0,
	    akill->who ? akill->who : "<unknown>", now,
	    StaticAkillReason ? StaticAkillReason : akill->reason);
#elif defined(IRC_DALNET)
    send_cmd(ServerName,
	    "AKILL %s %s :%s",
	    host, username,
	    StaticAkillReason ? StaticAkillReason : akill->reason);
#elif defined(IRC_UNDERNET)
    send_cmd(ServerName,
	    "GLINE * +%ld %s@%s :%s",
	    (akill->expires && akill->expires > now)
			? akill->expires - now
			: 999999999,
	    username, host,
	    StaticAkillReason ? StaticAkillReason : akill->reason);
#endif
    free(username);
#endif /* defined(IRC_DALNET) || defined(IRC_UNDERNET) */
}

/*************************************************************************/

static void cancel_akill(char *mask)
{
#if defined(IRC_UNREAL) || defined(IRC_DALNET)
    char *s = strchr(mask, '@');
    if (s) {
	*s++ = 0;
	strlower(s);
# if defined(IRC_UNREAL)
	send_cmd(ServerName, "TKL - G %s %s %s", mask, s, ServerName);
# elif defined(IRC_DALNET)
	send_cmd(ServerName, "RAKILL %s %s", s, mask);
# endif
    }
#endif
}

/*************************************************************************/
/************************** External functions ***************************/
/*************************************************************************/

/* Does the user match any AKILLs?  Return 1 (and kill the user) if so,
 * else 0.
 */

int check_akill(const char *nick, const char *username, const char *host)
{
    char buf[BUFSIZE];
    int i;

    if (noakill)
	return 0;

    snprintf(buf, sizeof(buf), "%s@%s", username, host);
    for (i = 0; i < nakill; i++) {
	if (match_wild_nocase(akills[i].mask, buf)) {
	    if (akills[i].expires && akills[i].expires <= time(NULL)) {
		/* Presumably not needed, since the user was able to
		 * connect in the first place, but just in case... */
		if (WallAkillExpire)
		    wallops(s_OperServ, "AKILL on %s has expired",
			    akills[i].mask);
		cancel_akill(akills[i].mask);
		free(akills[i].mask);
		free(akills[i].reason);
		nakill--;
		if (i < nakill)
		    memmove(akills+i, akills+i+1, sizeof(*akills)*(nakill-i));
		i--;
	    } else {
		/* Don't use kill_user(); that's for people who have
		 * already signed on.  This is called before the User
		 * structure is created. */
		send_cmd(s_OperServ, "KILL %s :%s (%s)", nick, s_OperServ,
			 StaticAkillReason ? StaticAkillReason
					   : akills[i].reason);
		send_akill(&akills[i]);
		return 1;
	    }
	}
    }
    return 0;
}

/*************************************************************************/

/* Delete any expired autokills. */

void expire_akills(void)
{
    int i;
    time_t now = time(NULL);

    for (i = 0; i < nakill; i++) {
	if (akills[i].expires == 0 || akills[i].expires > now)
	    continue;
	if (WallAkillExpire)
	    wallops(s_OperServ, "AKILL on %s has expired", akills[i].mask);
	cancel_akill(akills[i].mask);
	free(akills[i].mask);
	free(akills[i].reason);
	nakill--;
	if (i < nakill)
	    memmove(akills+i, akills+i+1, sizeof(*akills)*(nakill-i));
	i--;
    }
}

/*************************************************************************/

#ifdef IRC_UNREAL

void m_tkl(char *source, int ac, char **av)
{
    char buf[BUFSIZE];
    int i;

    if (noakill || ac < 4 || (*av[0] != '+' && *av[0] != '-') || *av[1] != 'G')
	return;

    snprintf(buf, sizeof(buf), "%s@%s", av[2], av[3]);
    for (i = 0; i < nakill; i++) {
	if (stricmp(akills[i].mask, buf) == 0) {
	    if (akills[i].expires && akills[i].expires <= time(NULL)) {
		/* This autokill has expired, clear it if necessary */
		if (WallAkillExpire)
		    wallops(s_OperServ, "AKILL on %s has expired",
			    akills[i].mask);
		if (*av[0] == '+')
		    cancel_akill(akills[i].mask);
		free(akills[i].mask);
		free(akills[i].reason);
		nakill--;
		if (i < nakill)
		    memmove(akills+i, akills+i+1, sizeof(*akills)*(nakill-i));
		i--;
	    } else if (*av[0] == '-') {
		/* Autokill is still valid, re-send */
		send_akill(&akills[i]);
	    }
	    return;
	}
    }
    /* Not found; if it was a +, clear it */
    if (*av[0] == '+')
	cancel_akill(buf);
}

#endif

/*************************************************************************/
/************************** AKILL list editing ***************************/
/*************************************************************************/

/* Note that all string parameters are assumed to be non-NULL; expiry must
 * be set to the time when the autokill should expire (0 for none).  Mask
 * is converted to lowercase on return.
 */

void add_akill(char *mask, const char *reason, const char *who,
	       const time_t expiry)
{
    Akill *akill;

    strlower(mask);
    if (nakill >= 32767) {
	log("%s: Attempt to add AKILL to full list!", s_OperServ);
	return;
    }
    if (nakill >= akill_size) {
	if (akill_size < 8)
	    akill_size = 8;
	else if (akill_size >= 16384)
	    akill_size = 32767;
	else
	    akill_size *= 2;
	akills = srealloc(akills, sizeof(*akills) * akill_size);
    }
    akill = &akills[nakill];
    akill->mask = sstrdup(mask);
    akill->reason = sstrdup(reason);
    akill->time = time(NULL);
    akill->expires = expiry;
    strscpy(akill->who, who, NICKMAX);
    nakill++;

    if (ImmediatelySendAkill)
	send_akill(akill);
}

/*************************************************************************/

/* Return whether the mask was found in the AKILL list.  Mask is converted
 * to lowercase on return.
 */

static int del_akill(char *mask)
{
    int i;

    strlower(mask);
    for (i = 0; i < nakill && strcmp(akills[i].mask, mask) != 0; i++)
	;
    if (i < nakill) {
	cancel_akill(akills[i].mask);
	free(akills[i].mask);
	free(akills[i].reason);
	nakill--;
	if (i < nakill)
	    memmove(akills+i, akills+i+1, sizeof(*akills) * (nakill-i));
	return 1;
    } else {
	return 0;
    }
}

/*************************************************************************/

/* Handle an OperServ AKILL command. */

void do_akill(User *u)
{
    char *cmd, *mask, *reason, *expiry, *s, *t;
    time_t expires;
    int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	time_t now = time(NULL);

	if (nakill >= 32767) {
	    notice_lang(s_OperServ, u, OPER_TOO_MANY_AKILLS);
	    return;
	}
	mask = strtok(NULL, " ");
	if (mask && *mask == '+') {
	    expiry = mask;
	    mask = strtok(NULL, " ");
	} else {
	    expiry = NULL;
	}
	reason = strtok(NULL, "");
	if (!reason) {
	    syntax_error(s_OperServ, u, "AKILL", OPER_AKILL_ADD_SYNTAX);
	    return;
	}

	expires = expiry ? dotime(expiry) : AutokillExpiry;
	if (expires < 0) {
	    notice_lang(s_OperServ, u, BAD_EXPIRY_TIME);
	    return;
	} else if (expires > 0) {
	    expires += now;	/* Set an absolute time */
	}

	if (strchr(mask, '!')) {
	    notice_lang(s_OperServ, u, OPER_AKILL_NO_NICK);
	    notice_lang(s_OperServ, u, BAD_USERHOST_MASK);
	    return;
	}
	s = strchr(mask, '@');
	if (!s || s == mask || s[1] == 0) {
	    notice_lang(s_OperServ, u, BAD_USERHOST_MASK);
	    return;
	}

	/* Make sure mask does not already exist on autokill list. */
	strlower(mask);
	for (i = 0; i < nakill && strcmp(akills[i].mask, mask) != 0; i++)
	    ;
	if (i < nakill) {
	    notice_lang(s_OperServ, u, OPER_AKILL_EXISTS, mask);
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
		notice_lang(s_OperServ, u, OPER_AKILL_MASK_TOO_GENERAL);
		return;
	    }
	}
	s[-1] = '@';	/* Replace "@" that we killed above */

	add_akill(mask, reason, u->nick, expires);
	notice_lang(s_OperServ, u, OPER_AKILL_ADDED, mask);
	if (WallOSAkill) {
	    char buf[128];
	    expires_in_lang(buf, sizeof(buf), NULL, expires);
	    wallops(s_OperServ, "%s added an AKILL for \2%s\2 (%s)",
		    u->nick, mask, buf);
	}
	if (readonly)
	    notice_lang(s_OperServ, u, READ_ONLY_MODE);

    } else if (stricmp(cmd, "DEL") == 0) {
	mask = strtok(NULL, " ");
	if (mask) {
	    if (del_akill(mask)) {
		notice_lang(s_OperServ, u, OPER_AKILL_REMOVED, mask);
		if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		notice_lang(s_OperServ, u, OPER_AKILL_NOT_FOUND, mask);
	    }
	} else {
	    syntax_error(s_OperServ, u, "AKILL", OPER_AKILL_DEL_SYNTAX);
	}

    } else if (stricmp(cmd, "LIST") == 0 || stricmp(cmd, "VIEW") == 0) {
	int is_view = stricmp(cmd,"VIEW")==0;
	char *expiry;
	time_t expires = -1;	/* Do not match on expiry time */

	expire_akills();
	s = strtok(NULL, " ");
	if (!s)
	    s = "*";
	else {
	    /* This is a little longwinded for what it acheives - but we can
	     * extend it later to allow for user defined expiry times. */
	    expiry = strtok(NULL, " ");
	    if (expiry && stricmp(expiry, "NOEXPIRE") == 0)
		expires = 0;	/* Akills that never expire */
	}

	notice_lang(s_OperServ, u, OPER_AKILL_LIST_HEADER);
	for (i = 0; i < nakill; i++) {
	    if (!s || (match_wild_nocase(s, akills[i].mask) &&
	               (expires == -1 || akills[i].expires == expires))) {
		if (is_view) {
		    char timebuf[BUFSIZE], expirebuf[BUFSIZE];
		    struct tm tm;
		    time_t t = time(NULL);

		    tm = *localtime(akills[i].time ? &akills[i].time : &t);
		    strftime_lang(timebuf, sizeof(timebuf),
				  u, STRFTIME_SHORT_DATE_FORMAT, &tm);
		    expires_in_lang(expirebuf, sizeof(expirebuf), u->ni,
				    akills[i].expires);
		    notice_lang(s_OperServ, u, OPER_AKILL_VIEW_FORMAT,
				akills[i].mask,
				*akills[i].who ? akills[i].who : "<unknown>",
				timebuf, expirebuf, akills[i].reason);
		} else { /* !is_view */
		    notice_lang(s_OperServ, u, OPER_AKILL_LIST_FORMAT,
				akills[i].mask, akills[i].reason);
		}
	    }
	}

    } else if (stricmp(cmd, "COUNT") == 0) {
	notice_lang(s_OperServ, u, OPER_AKILL_COUNT, nakill);

    } else {
	syntax_error(s_OperServ, u, "AKILL", OPER_AKILL_SYNTAX);
    }
}

/*************************************************************************/
// added by jabea
int is_akilled(const char *mask)
{
	int i;

	if (mask) {
		for (i = 0; i < nakill && stricmp(akills[i].mask, mask) != 0; i++)
	    ;
		if (i < nakill) return 1;
		else return 0;
	}
	return 0;
}

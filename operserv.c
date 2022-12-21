/* OperServ functions.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "pseudo.h"
#include "news.h"

#include <unistd.h>

/*************************************************************************/

/* Message to send when unable to set modes or kick on a channel. */
#if defined(IRC_DALNET) || defined(IRC_UNDERNET)
# define OPER_BOUNCY_MODES_MESSAGE OPER_BOUNCY_MODES_U_LINE
#else
# define OPER_BOUNCY_MODES_MESSAGE OPER_BOUNCY_MODES
#endif

/* Services admin list */
static NickInfo *services_admins[MAX_SERVADMINS];

/* Services operator list */
static NickInfo *services_opers[MAX_SERVOPERS];

/* Services super-user password */
static char supass[PASSMAX];
/* Is the password currently unset? */
static char no_supass = 1;


struct clone {
    char *host;
    long time;
};

/* List of most recent users - statically initialized to zeros */
static struct clone clonelist[CLONE_DETECT_SIZE];

/* Which hosts have we warned about, and when?  This is used to keep us
 * from sending out notices over and over for clones from the same host. */
static struct clone warnings[CLONE_DETECT_SIZE];

/* CloseNet stat */
static int net_stat = 0;

/*************************************************************************/

static void do_help(User *u);
static void do_global(User *u);
static void do_stats(User *u);
static void do_admin(User *u);
static void do_oper(User *u);
static void do_os_mode(User *u);
static void do_clearmodes(User *u);
static void do_clearchan(User *u);
static void do_os_kick(User *u);
static void do_su(User *u);
static void do_set(User *u);
static void do_jupe(User *u);
static void do_raw(User *u);
static void do_update(User *u);
static void do_os_quit(User *u);
static void do_shutdown(User *u);
static void do_restart(User *u);
static void do_listignore(User *u);
static void do_killclones(User *u);
static void do_closenet (User *u);
static void closenet_timeout(Timeout *to);

#ifdef DEBUG_COMMANDS
static void send_clone_lists(User *u);
static void do_matchwild(User *u);
#endif

/*************************************************************************/

static Command cmds[] = {
    { "HELP",       do_help,       NULL,  -1,                   -1,-1,-1,-1 },
    { "GLOBAL",     do_global,     NULL,  OPER_HELP_GLOBAL,     -1,-1,-1,-1 },
    { "STATS",      do_stats,      NULL,  OPER_HELP_STATS,      -1,-1,-1,-1 },
    { "UPTIME",     do_stats,      NULL,  OPER_HELP_STATS,      -1,-1,-1,-1 },

    /* Anyone can use the LIST option to the ADMIN and OPER commands; those
     * routines check privileges to ensure that only authorized users
     * modify the list. */
    { "ADMIN",      do_admin,      NULL,  OPER_HELP_ADMIN,      -1,-1,-1,-1 },
    { "OPER",       do_oper,       NULL,  OPER_HELP_OPER,       -1,-1,-1,-1 },
	{ "NOOPER",		do_nooper,     NULL,  OPER_HELP_NOOPER,     -1,-1,-1,-1 },
	{ "SNOOPER",	do_snooper,    NULL,  OPER_HELP_SNOOPER,    -1,-1,-1,-1 },
	{ "NAKILL",		do_nakill,     NULL,  -1,				    -1,-1,-1,-1 },
    /* Similarly, anyone can use *NEWS LIST, but *NEWS {ADD,DEL} are
     * reserved for Services operators. */
    { "LOGONNEWS",  do_logonnews,  NULL,  NEWS_HELP_LOGON,      -1,-1,-1,-1 },
    { "OPERNEWS",   do_opernews,   NULL,  NEWS_HELP_OPER,       -1,-1,-1,-1 },

    /* Commands for Services opers: */
    { "MODE",       do_os_mode,    is_services_oper,
	OPER_HELP_MODE, -1,-1,-1,-1 },
    { "KICK",       do_os_kick,    is_services_oper,
	OPER_HELP_KICK, -1,-1,-1,-1 },
    { "CLEARMODES", do_clearmodes, is_services_oper,
	OPER_HELP_CLEARMODES, -1,-1,-1,-1 },
    { "CLEARCHAN",  do_clearchan,  is_services_oper,
	OPER_HELP_CLEARCHAN, -1,-1,-1,-1 },
    { "KILLCLONES", do_killclones, is_services_oper,
	OPER_HELP_KILLCLONES, -1,-1,-1, -1 },
    { "AKILL",      do_akill,      is_services_oper,
	OPER_HELP_AKILL, -1,-1,-1,-1 },
#ifndef STREAMLINED
    { "SESSION",    do_session,    is_services_oper,
        OPER_HELP_SESSION, -1,-1,-1, -1 },
    { "EXCEPTION",  do_exception,  is_services_oper,
        OPER_HELP_EXCEPTION, -1,-1,-1, -1 },
#endif

    /* Commands for Services admins: */
    { "SU",         do_su,         NULL,  /* do_su() checks perms itself */
	OPER_HELP_SU, -1,-1,-1,-1 },
    { "SET",        do_set,        is_services_admin,
	OPER_HELP_SET, -1,-1,-1,-1 },
    { "SET READONLY",0,0,  OPER_HELP_SET_READONLY, -1,-1,-1,-1 },
    { "SET DEBUG",0,0,     OPER_HELP_SET_DEBUG, -1,-1,-1,-1 },
    { "SET SUPASS",0,0,    OPER_HELP_SET_SUPASS, -1,-1,-1,-1 },
    { "JUPE",       do_jupe,       is_services_admin,
	OPER_HELP_JUPE, -1,-1,-1,-1 },
    { "RAW",        do_raw,        is_services_admin,
	OPER_HELP_RAW, -1,-1,-1,-1 },
    { "UPDATE",     do_update,     is_services_admin,
	OPER_HELP_UPDATE, -1,-1,-1,-1 },
    { "QUIT",       do_os_quit,    is_services_admin,
	OPER_HELP_QUIT, -1,-1,-1,-1 },
    { "SHUTDOWN",   do_shutdown,   is_services_admin,
	OPER_HELP_SHUTDOWN, -1,-1,-1,-1 },
    { "RESTART",    do_restart,    is_services_admin,
	OPER_HELP_RESTART, -1,-1,-1,-1 },
    { "LISTIGNORE", do_listignore, is_services_admin,
	-1,-1,-1,-1, -1 },
	{ "ACONNECT", do_aconnect, NULL,
	OPER_HELP_ACONNECT,-1,-1,-1, -1 },
	{ "CLOSENET",	do_closenet, is_services_admin,
	OPER_HELP_CLOSENET,-1,-1,-1,-1 },

    /* Commands for Services super-user: */

#ifdef DEBUG_COMMANDS
    { "LISTSERVERS",send_server_list,   is_services_root, -1,-1,-1,-1,-1 },
    { "LISTCHANS",  send_channel_list,  is_services_root, -1,-1,-1,-1,-1 },
    { "LISTCHAN",   send_channel_users, is_services_root, -1,-1,-1,-1,-1 },
    { "LISTUSERS",  send_user_list,     is_services_root, -1,-1,-1,-1,-1 },
    { "LISTUSER",   send_user_info,     is_services_root, -1,-1,-1,-1,-1 },
    { "LISTTIMERS", send_timeout_list,  is_services_root, -1,-1,-1,-1,-1 },
    { "MATCHWILD",  do_matchwild,       is_services_root, -1,-1,-1,-1,-1 },
    { "LISTCLONES", send_clone_lists,   is_services_root, -1,-1,-1,-1,-1 },
#endif

    /* Fencepost: */
    { NULL }
};

/*************************************************************************/
/*************************************************************************/

/* OperServ initialization. */

void os_init(void)
{
    Command *cmd;

    cmd = lookup_cmd(cmds, "GLOBAL");
    if (cmd)
	cmd->help_param1 = s_GlobalNoticer;
    cmd = lookup_cmd(cmds, "ADMIN");
    if (cmd)
	cmd->help_param1 = s_NickServ;
    cmd = lookup_cmd(cmds, "OPER");
    if (cmd)
	cmd->help_param1 = s_NickServ;
}

/*************************************************************************/

/* Main OperServ routine. */

void operserv(const char *source, char *buf)
{
    char *cmd;
    char *s;
    User *u = finduser(source);

    if (!u) {
	log("%s: user record for %s not found", s_OperServ, source);
	notice(s_OperServ, source,
		getstring((NickInfo *)NULL, USER_RECORD_NOT_FOUND));
	return;
    }

    /* Don't log stuff that might be passwords */
    if (strnicmp(buf, "SU ", 3) == 0) {
	log("%s: %s: SU xxxxxx", s_OperServ, source);
    } else if (strnicmp(buf, "SET ", 4) == 0
	       && (s = stristr(buf, "SUPASS")) != NULL
	       && strspn(buf+4, " ") == s-(buf+4)) {
	/* All that was needed to make sure someone doesn't fool us with
	 * "SET READONLY ON SUPASS".  Which wouldn't work anyway, but we
	 * ought to log it properly... */
	log("%s: %s: SET SUPASS xxxxxx", s_OperServ, source);
    } else {
	log("%s: %s: %s", s_OperServ, source, buf);
    }

    cmd = strtok(buf, " ");
    if (!cmd) {
	return;
    } else if (stricmp(cmd, "\1PING") == 0) {
	if (!(s = strtok(NULL, "")))
	    s = "\1";
	notice(s_OperServ, source, "\1PING %s", s);
    } else {
	run_cmd(s_OperServ, u, cmds, cmd);
    }
}

/*************************************************************************/
/************************ Database loading/saving ************************/
/*************************************************************************/

/* Load OperServ data. */

#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", OperDBName);	\
	failed = 1;					\
	close_db(f);					\
	return;						\
    }							\
} while (0)

void load_os_dbase(void)
{
    dbFILE *f;
    int16 i, n;
    int32 ver;
    char *s;
    int failed = 0;

    if (!(f = open_db(s_OperServ, OperDBName, "r")))
	return;
    switch (ver = get_file_version(f)) {
      case 11:
      case 10:
      case 9:
      case 8:
      case 7:
      case 6:
      case 5:
	SAFE(read_int16(&n, f));
	for (i = 0; i < n; i++) {
	    SAFE(read_string(&s, f));
	    if (s && i < MAX_SERVADMINS)
		services_admins[i] = findnick(s);
	    if (s)
		free(s);
	}
	SAFE(read_int16(&n, f));
	for (i = 0; i < n; i++) {
	    SAFE(read_string(&s, f));
	    if (s && i < MAX_SERVOPERS)
		services_opers[i] = findnick(s);
	    if (s)
		free(s);
	}
	if (ver >= 7) {
	    int32 tmp32;
	    SAFE(read_int32(&maxusercnt, f));
	    SAFE(read_int32(&tmp32, f));
	    maxusertime = tmp32;
	}
	if (ver >= 9) {
	    SAFE(read_int8(&no_supass, f));
	    if (!no_supass)
		SAFE(read_buffer(supass, f));
	}
	break;

      case 4:
      case 3:
	SAFE(read_int16(&n, f));
	for (i = 0; i < n; i++) {
	    SAFE(read_string(&s, f));
	    if (s && i < MAX_SERVADMINS)
		services_admins[i] = findnick(s);
	    if (s)
		free(s);
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", OperDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, OperDBName);
    } /* switch (version) */
    close_db(f);
}

#undef SAFE

/*************************************************************************/

/* Save OperServ data. */

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_os_dbase(void)
{
    dbFILE *f;
    int16 i, count = 0;
    static time_t lastwarn = 0;

    if (!(f = open_db(s_OperServ, OperDBName, "w")))
	return;
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i])
	    count++;
    }
    SAFE(write_int16(count, f));
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i])
	    SAFE(write_string(services_admins[i]->nick, f));
    }
    count = 0;
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i])
	    count++;
    }
    SAFE(write_int16(count, f));
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i])
	    SAFE(write_string(services_opers[i]->nick, f));
    }
    SAFE(write_int32(maxusercnt, f));
    SAFE(write_int32(maxusertime, f));
    SAFE(write_int8(no_supass, f));
    if (!no_supass)
	SAFE(write_buffer(supass, f));
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", OperDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", OperDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/**************************** Privilege checks ***************************/
/*************************************************************************/

/* Does the given user have Services super-user privileges? */

int is_services_root(User *u)
{
    if (u->real_ni && (u->real_ni->status & NS_SERVROOT))
	return 1;
    if (!is_oper_u(u) || stricmp(u->nick, ServicesRoot) != 0)
	return 0;
    if (skeleton || nick_identified(u))
	return 1;
    return 0;
}

/*************************************************************************/

/* Does the given user have Services admin privileges? */

int is_services_admin(User *u)
{
    int i;

    if (!is_oper_u(u))
	return 0;
    if (is_services_root(u))
	return 1;
    if (skeleton)
	return 1;
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i] && u->ni == getlink(services_admins[i])) {
	    if (nick_identified(u))
		return 1;
	    return 0;
	}
    }
    return 0;
}

/*************************************************************************/

/* Does the given user have Services oper privileges? */

int is_services_oper(User *u)
{
    int i;

    if (!is_oper_u(u))
	return 0;
    if (is_services_admin(u))
	return 1;
    if (skeleton)
	return 1;
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i] && u->ni == getlink(services_opers[i])) {
	    if (nick_identified(u))
		return 1;
	    return 0;
	}
    }
    return 0;
}

/*************************************************************************/

/* Is the given nick a Services admin/root nick? */

/* NOTE: Do not use this to check if a user who is online is a services
 * admin or root. This function only checks if a user has the ABILITY to be
 * a services admin. Rather use is_services_admin(User *u). -TheShadow */

int nick_is_services_admin(NickInfo *ni)
{
    int i;

    if (!ni)
	return 0;
    if (stricmp(ni->nick, ServicesRoot) == 0)
	return 1;
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i] && getlink(ni) == getlink(services_admins[i]))
	    return 1;
    }
    return 0;
}

/*************************************************************************/

/* Expunge a deleted nick from the Services admin/oper lists. */

void os_remove_nick(const NickInfo *ni)
{
    int i;

    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i] == ni)
	    services_admins[i] = NULL;
    }
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i] == ni)
	    services_opers[i] = NULL;
    }
}

/*************************************************************************/
/**************************** Clone detection ****************************/
/*************************************************************************/

/* We just got a new user; does it look like a clone?  If so, send out a
 * wallops.
 */

void check_clones(User *user)
{
#ifndef STREAMLINED
    int i, clone_count;
    long last_time;

    if (!CheckClones)
	return;

    if (clonelist[0].host)
	free(clonelist[0].host);
    i = CLONE_DETECT_SIZE-1;
    memmove(clonelist, clonelist+1, sizeof(struct clone) * i);
    clonelist[i].host = sstrdup(user->host);
    last_time = clonelist[i].time = time(NULL);
    clone_count = 1;
    while (--i >= 0 && clonelist[i].host) {
	if (clonelist[i].time < last_time - CloneMaxDelay)
	    break;
	if (stricmp(clonelist[i].host, user->host) == 0) {
	    ++clone_count;
	    last_time = clonelist[i].time;
	    if (clone_count >= CloneMinUsers)
		break;
	}
    }
    if (clone_count >= CloneMinUsers) {
	/* Okay, we have clones.  Check first to see if we already know
	 * about them. */
	for (i = CLONE_DETECT_SIZE-1; i >= 0 && warnings[i].host; --i) {
	    if (stricmp(warnings[i].host, user->host) == 0)
		break;
	}
	if (i < 0 || warnings[i].time < user->signon - CloneWarningDelay) {
	    /* Send out the warning, and note it. */
	    wallops(s_OperServ,
		"\2WARNING\2 - possible clones detected from %s", user->host);
	    log("%s: possible clones detected from %s",
		s_OperServ, user->host);
	    i = CLONE_DETECT_SIZE-1;
	    if (warnings[0].host)
		free(warnings[0].host);
	    memmove(warnings, warnings+1, sizeof(struct clone) * i);
	    warnings[i].host = sstrdup(user->host);
	    warnings[i].time = clonelist[i].time;
	    if (KillClones)
		kill_user(s_OperServ, user->nick, "Clone kill");
	}
    }
#endif	/* !STREAMLINED */
}

/*************************************************************************/

#ifdef DEBUG_COMMANDS

/* Send clone arrays to given nick. */

static void send_clone_lists(User *u)
{
#ifdef STREAMLINED
    notice(s_OperServ, u->nick, "No clone checking in STREAMLINED mode.");
#else
    int i;

    if (!CheckClones) {
	notice(s_OperServ, u->nick, "CheckClones not enabled.");
	return;
    }

    notice(s_OperServ, u->nick, "clonelist[]");
    for (i = 0; i < CLONE_DETECT_SIZE; i++) {
	if (clonelist[i].host)
	    notice(s_OperServ, u->nick, "    %10ld  %s", clonelist[i].time, clonelist[i].host ? clonelist[i].host : "(null)");
    }
    notice(s_OperServ, u->nick, "warnings[]");
    for (i = 0; i < CLONE_DETECT_SIZE; i++) {
	if (clonelist[i].host)
	    notice(s_OperServ, u->nick, "    %10ld  %s", warnings[i].time, warnings[i].host ? warnings[i].host : "(null)");
    }
#endif /* !STREAMLINED */
}

#endif	/* DEBUG_COMMANDS */

/*************************************************************************/
/********************** Admin/oper list modification *********************/
/*************************************************************************/

#define LIST_ADMIN	0
#define LIST_OPER	1

#define MSG_EXISTS	0
#define MSG_ADDED	1
#define MSG_TOOMANY	2
#define MSG_REMOVED	3
#define MSG_NOTFOUND	4

static int privlist_msgs[2][5] = {
    { OPER_ADMIN_EXISTS,
      OPER_ADMIN_ADDED,
      OPER_ADMIN_TOO_MANY,
      OPER_ADMIN_REMOVED,
      OPER_ADMIN_NOT_FOUND,
    },
    { OPER_OPER_EXISTS,
      OPER_OPER_ADDED,
      OPER_OPER_TOO_MANY,
      OPER_OPER_REMOVED,
      OPER_OPER_NOT_FOUND,
    },
};

/*************************************************************************/

/* Add a nick to the Services admin/oper list.  u is the command sender. */

static void privlist_add(User *u, int listid, const char *nick)
{
    NickInfo **list = (listid==LIST_ADMIN ? services_admins : services_opers);
    int max = (listid==LIST_ADMIN ? MAX_SERVADMINS : MAX_SERVOPERS);
    int *msgs = privlist_msgs[listid];
    NickInfo *ni;
    int i;

    if (!(ni = findnick(nick))) {
	notice_lang(s_OperServ, u, NICK_X_NOT_REGISTERED, nick);
	return;
    }
    for (i = 0; i < max; i++) {
	if (!list[i] || list[i] == ni)
	    break;
    }
    if (list[i] == ni) {
	notice_lang(s_OperServ, u, msgs[MSG_EXISTS], ni->nick);
    } else if (i < max) {
	list[i] = ni;
	notice_lang(s_OperServ, u, msgs[MSG_ADDED], ni->nick);
	if (readonly)
	    notice_lang(s_OperServ, u, READ_ONLY_MODE);
    } else {
	notice_lang(s_OperServ, u, msgs[MSG_TOOMANY], max);
    }
}

/*************************************************************************/

/* Remove a nick from the Services admin/oper list. */

static void privlist_rem(User *u, int listid, const char *nick)
{
    NickInfo **list = (listid==LIST_ADMIN ? services_admins : services_opers);
    int max = (listid==LIST_ADMIN ? MAX_SERVADMINS : MAX_SERVOPERS);
    int *msgs = privlist_msgs[listid];
    NickInfo *ni;
    int i;

    if (!(ni = findnick(nick))) {
	notice_lang(s_OperServ, u, NICK_X_NOT_REGISTERED, nick);
	return;
    }
    for (i = 0; i < max; i++) {
	if (list[i] == ni)
	    break;
    }
    if (i < max) {
	list[i] = NULL;
	notice_lang(s_OperServ, u, msgs[MSG_REMOVED], ni->nick);
	if (readonly)
	    notice_lang(s_OperServ, u, READ_ONLY_MODE);
    } else {
	notice_lang(s_OperServ, u, msgs[MSG_NOTFOUND], ni->nick);
    }
}

/*************************************************************************/
/*********************** OperServ command functions **********************/
/*************************************************************************/

/* HELP command. */

static void do_help(User *u)
{
    const char *cmd = strtok(NULL, "");

    if (!cmd) {
	notice_help(s_OperServ, u, OPER_HELP);
    } else {
	help_cmd(s_OperServ, u, cmds, cmd);
    }
}

/*************************************************************************/

/* Global notice sending via GlobalNoticer. */

static void do_global(User *u)
{
    char *msg = strtok(NULL, "");

    if (!msg) {
	syntax_error(s_OperServ, u, "GLOBAL", OPER_GLOBAL_SYNTAX);
	return;
    }
#ifdef HAVE_ALLWILD_NOTICE
    notice(s_GlobalNoticer, "$*", "%s", msg);
#else
# ifdef NETWORK_DOMAIN
    notice(s_GlobalNoticer, "$*." NETWORK_DOMAIN, "%s", msg);
# else
    /* Go through all common top-level domains.  If you have others,
     * add them here.
     */
    notice(s_GlobalNoticer, "$*.com", "%s", msg);
    notice(s_GlobalNoticer, "$*.net", "%s", msg);
    notice(s_GlobalNoticer, "$*.org", "%s", msg);
    notice(s_GlobalNoticer, "$*.edu", "%s", msg);
# endif
#endif
}

/*************************************************************************/

/* STATS command. */

static void do_stats(User *u)
{
    time_t uptime = time(NULL) - start_time;
    char *extra = strtok(NULL, "");
    int days = uptime/86400, hours = (uptime/3600)%24,
        mins = (uptime/60)%60, secs = uptime%60;
    struct tm *tm;
    char timebuf[64];

    if (extra && stricmp(extra, "UPTIME") == 0)
	extra = NULL;

    if (extra && stricmp(extra, "ALL") != 0) {
	if (stricmp(extra, "AKILL") == 0) {
	    int timeout = AutokillExpiry+59;
	    notice_lang(s_OperServ, u, OPER_STATS_AKILL_COUNT, num_akills());
	    if (timeout >= 172800)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_DAYS,
			timeout/86400);
	    else if (timeout >= 86400)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_DAY);
	    else if (timeout >= 7200)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_HOURS,
			timeout/3600);
	    else if (timeout >= 3600)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_HOUR);
	    else if (timeout >= 120)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_MINS,
			timeout/60);
	    else if (timeout >= 60)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_MIN);
	    else
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_NONE);
	} else if (stricmp(extra, "RESET") == 0) {
	    maxusercnt = usercnt;
	    maxusertime = time(NULL);
	    notice_lang(s_OperServ, u, OPER_STATS_RESET_USER_COUNT);
	} else {
	    notice_lang(s_OperServ, u, OPER_STATS_UNKNOWN_OPTION,
			strupper(extra));
	}
	return;
    }

    notice_lang(s_OperServ, u, OPER_STATS_CURRENT_USERS, usercnt, opcnt);
    tm = localtime(&maxusertime);
    strftime_lang(timebuf, sizeof(timebuf), u, STRFTIME_DATE_TIME_FORMAT, tm);
    notice_lang(s_OperServ, u, OPER_STATS_MAX_USERS, maxusercnt, timebuf);
    if (days >= 1) {
	char *str = getstring(u->ni, days!=1 ? STR_DAYS : STR_DAY);
	notice_lang(s_OperServ, u, OPER_STATS_UPTIME_DHMS,
		days, str, hours, mins, secs);
    } else {
	char *str1, *str2;
	if (hours >= 1) {
	    str1 = getstring(u->ni, hours!=1 ? STR_HOURS : STR_HOUR);
	    str2 = getstring(u->ni, mins!=1 ? STR_MINUTES : STR_MINUTE);
	    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_HM_MS,
			hours, str1, mins, str2);
	} else {
	    str1 = getstring(u->ni, mins!=1 ? STR_MINUTES : STR_MINUTE);
	    str2 = getstring(u->ni, secs!=1 ? STR_SECONDS : STR_SECOND);
	    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_HM_MS,
			mins, str1, secs, str2);
	}
    }

    if (extra && stricmp(extra, "ALL") == 0 && is_services_admin(u)) {
	long count, mem, count2, mem2;
	int i;

	notice_lang(s_OperServ, u, OPER_STATS_BYTES_READ, total_read / 1024);
	notice_lang(s_OperServ, u, OPER_STATS_BYTES_WRITTEN,
			total_written / 1024);

	get_user_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_USER_MEM,
			count, (mem+512) / 1024);
	get_server_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_SERVER_MEM,
			count, (mem+512) / 1024);
	get_channel_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_CHANNEL_MEM,
			count, (mem+512) / 1024);
	get_nickserv_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_NICKSERV_MEM,
			count, (mem+512) / 1024);
	get_chanserv_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_CHANSERV_MEM,
			count, (mem+512) / 1024);
	get_memoserv_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_MEMOSERV_MEM,
			count, (mem+512) / 1024);
#ifdef STATISTICS
	get_statserv_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_STATSERV_MEM,
			count, (mem+512) / 1024);
#endif
	count = 0;
	if (CheckClones) {
	    mem = sizeof(struct clone) * CLONE_DETECT_SIZE * 2;
	    for (i = 0; i < CLONE_DETECT_SIZE; i++) {
		if (clonelist[i].host) {
		    count++;
		    mem += strlen(clonelist[i].host)+1;
		}
		if (warnings[i].host) {
		    count++;
		    mem += strlen(warnings[i].host)+1;
		}
	    }
	}
	get_akill_stats(&count2, &mem2);
	count += count2;
	mem += mem2;
	get_news_stats(&count2, &mem2);
	count += count2;
	mem += mem2;
#ifndef STREAMLINED
	get_exception_stats(&count2, &mem2);
	count += count2;
	mem += mem2;
#endif
	notice_lang(s_OperServ, u, OPER_STATS_OPERSERV_MEM,
			count, (mem+512) / 1024);

#ifndef STREAMLINED
	get_session_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_SESSIONS_MEM,
			count, (mem+512) / 1024);
#endif
    }
}

/*************************************************************************/

/* Channel mode changing (MODE command). */

static void do_os_mode(User *u)
{
    int argc;
    char **argv;
    char *s = strtok(NULL, "");
    char *chan, *modes;
    Channel *c;

    if (!s) {
	syntax_error(s_OperServ, u, "MODE", OPER_MODE_SYNTAX);
	return;
    }
    chan = s;
    s += strcspn(s, " ");
    if (!*s) {
	syntax_error(s_OperServ, u, "MODE", OPER_MODE_SYNTAX);
	return;
    }
    *s = 0;
    modes = (s+1) + strspn(s+1, " ");
    if (!*modes) {
	syntax_error(s_OperServ, u, "MODE", OPER_MODE_SYNTAX);
	return;
    }
    if (!(c = findchan(chan))) {
	notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_OperServ, u, OPER_BOUNCY_MODES_MESSAGE);
	return;
    } else {
	send_cmd(s_OperServ, "MODE %s %s", chan, modes);
	if (WallOSChannel)
	    wallops(s_OperServ, "%s used MODE %s on %s", u->nick, modes, chan);
	*s = ' ';
	argc = split_buf(chan, &argv, 1);
	do_cmode(s_OperServ, argc, argv);
    }
}

/*************************************************************************/

/* Clear all modes from a channel. */

static void do_clearmodes(User *u)
{
    char *s;
    char *chan = strtok(NULL, " ");
    Channel *c;
    int all = 0;

    if (!chan) {
	syntax_error(s_OperServ, u, "CLEARMODES", OPER_CLEARMODES_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_OperServ, u, OPER_BOUNCY_MODES_MESSAGE);
	return;
    } else {
	s = strtok(NULL, " ");
	if (s) {
	    if (stricmp(s, "ALL") == 0) {
		all = 1;
	    } else {
		syntax_error(s_OperServ,u,"CLEARMODES",OPER_CLEARMODES_SYNTAX);
		return;
	    }
	}
	if (WallOSChannel)
	    wallops(s_OperServ, "%s used CLEARMODES%s on %s",
			u->nick, all ? " ALL" : "", chan);
	if (all) {
	    clear_channel(c, CLEAR_UMODES, (void *)MODE_ALL);
	    clear_channel(c, CLEAR_MODES | CLEAR_BANS | CLEAR_EXCEPTS, NULL);
	    notice_lang(s_OperServ, u, OPER_CLEARMODES_ALL_DONE, chan);
	} else {
	    clear_channel(c, CLEAR_MODES | CLEAR_BANS | CLEAR_EXCEPTS, NULL);
	    notice_lang(s_OperServ, u, OPER_CLEARMODES_DONE, chan);
	}
    }
}

/*************************************************************************/

/* Remove all users from a channel. */

static void do_clearchan(User *u)
{
    char *chan = strtok(NULL, " ");
    Channel *c;
    char buf[BUFSIZE];

    if (!chan) {
	syntax_error(s_OperServ, u, "CLEARCHAN", OPER_CLEARCHAN_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_OperServ, u, OPER_BOUNCY_MODES_MESSAGE);
	return;
    } else {
	if (WallOSChannel)
	    wallops(s_OperServ, "%s used CLEARCHAN on %s", u->nick, chan);
	snprintf(buf, sizeof(buf), "CLEARCHAN by %s", u->nick);
	clear_channel(c, CLEAR_USERS, buf);
	notice_lang(s_OperServ, u, OPER_CLEARCHAN_DONE, chan);
    }
}

/*************************************************************************/

/* Kick a user from a channel (KICK command). */

static void do_os_kick(User *u)
{
    char *argv[3];
    char *chan, *nick, *s;
    Channel *c;

    chan = strtok(NULL, " ");
    nick = strtok(NULL, " ");
    s = strtok(NULL, "");
    if (!chan || !nick || !s) {
	syntax_error(s_OperServ, u, "KICK", OPER_KICK_SYNTAX);
	return;
    }
    if (!(c = findchan(chan))) {
	notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_OperServ, u, OPER_BOUNCY_MODES_MESSAGE);
	return;
    }
    send_cmd(s_OperServ, "KICK %s %s :%s (%s)", chan, nick, u->nick, s);
    if (WallOSChannel)
	wallops(s_OperServ, "%s used KICK on %s/%s", u->nick, nick, chan);
    argv[0] = chan;
    argv[1] = nick;
    argv[2] = s;
    do_kick(s_OperServ, 3, argv);
}

/*************************************************************************/

/* Services admin list viewing/modification. */

static void do_admin(User *u)
{
    char *cmd, *nick;
    int i;

    if (skeleton) {
	notice_lang(s_OperServ, u, OPER_ADMIN_SKELETON);
	return;
    }
    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	if (!is_services_root(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick)
	    privlist_add(u, LIST_ADMIN, nick);
	else
	    syntax_error(s_OperServ, u, "ADMIN", OPER_ADMIN_ADD_SYNTAX);

    } else if (stricmp(cmd, "DEL") == 0) {
	if (!is_services_root(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick)
	    privlist_rem(u, LIST_ADMIN, nick);
	else
	    syntax_error(s_OperServ, u, "ADMIN", OPER_ADMIN_DEL_SYNTAX);

    } else if (stricmp(cmd, "LIST") == 0) {
	notice_lang(s_OperServ, u, OPER_ADMIN_LIST_HEADER);
	for (i = 0; i < MAX_SERVADMINS; i++) {
	    if (services_admins[i])
		notice(s_OperServ, u->nick, "%s", services_admins[i]->nick);
	}

    } else {
	syntax_error(s_OperServ, u, "ADMIN", OPER_ADMIN_SYNTAX);
    }
}

/*************************************************************************/

/* Services oper list viewing/modification. */

static void do_oper(User *u)
{
    char *cmd, *nick;
    int i;

    if (skeleton) {
	notice_lang(s_OperServ, u, OPER_OPER_SKELETON);
	return;
    }
    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick)
	    privlist_add(u, LIST_OPER, nick);
	else
	    syntax_error(s_OperServ, u, "OPER", OPER_OPER_ADD_SYNTAX);

    } else if (stricmp(cmd, "DEL") == 0) {
	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick)
	    privlist_rem(u, LIST_OPER, nick);
	else
	    syntax_error(s_OperServ, u, "OPER", OPER_OPER_DEL_SYNTAX);

    } else if (stricmp(cmd, "LIST") == 0) {
	notice_lang(s_OperServ, u, OPER_OPER_LIST_HEADER);
	for (i = 0; i < MAX_SERVOPERS; i++) {
	    if (services_opers[i])
		notice(s_OperServ, u->nick, "%s", services_opers[i]->nick);
	}

    } else {
	syntax_error(s_OperServ, u, "OPER", OPER_OPER_SYNTAX);
    }
}

/*************************************************************************/

/* Obtain Services root privileges.  We check permissions here instead of
 * letting run_cmd() do it for us so we can send out warnings when a
 * non-admin tries to use the command.
 */

static void do_su(User *u)
{
    char *password = strtok(NULL, "");
    int res;

    if (!is_services_admin(u)) {
	wallops(s_OperServ, "\2NOTICE:\2 %s!%s@%s attempted to use SU "
		"command (not Services admin)",
		u->nick, u->username, u->host);
	notice_lang(s_OperServ, u, PERMISSION_DENIED);
	return;
    }

    if (!password) {
	syntax_error(s_OperServ, u, "SU", OPER_SU_SYNTAX);
    } else if (skeleton) {
	notice_lang(s_OperServ, u, OPER_SKELETON_MODE);
    } else if (no_supass) {
	notice_lang(s_OperServ, u, OPER_SU_NO_PASSWORD);
    } else if ((res = check_password(password, supass)) < 0) {
	notice_lang(s_OperServ, u, OPER_SU_FAILED);
    } else if (res == 0) {
	log("%s: Failed SU by %s!%s@%s",
	    s_OperServ, u->nick, u->username, u->host);
	wallops(s_OperServ, "\2NOTICE:\2 Failed SU by %s!%s@%s",
		u->nick, u->username, u->host);
	bad_password(s_OperServ, u, "Services root");
    } else {
	/* The user must be a Services admin to get here so we know they
	 * have a valid NickInfo. */
	u->real_ni->status |= NS_SERVROOT;
	if (WallSU)
	    wallops(s_OperServ,
		    "%s!%s@%s obtained Services super-user privileges",
		    u->nick, u->username, u->host);
	notice_lang(s_OperServ, u, OPER_SU_SUCCEEDED);
    }
}

/*************************************************************************/

/* Set various Services runtime options. */

static void do_set(User *u)
{
    char *option = strtok(NULL, " ");
    char *setting = strtok(NULL, "");

    if (!option || (!setting && stricmp(option, "SUPASS") != 0)) {
	syntax_error(s_OperServ, u, "SET", OPER_SET_SYNTAX);

    } else if (stricmp(option, "IGNORE") == 0) {
	if (stricmp(setting, "on") == 0) {
	    allow_ignore = 1;
	    notice_lang(s_OperServ, u, OPER_SET_IGNORE_ON);
	} else if (stricmp(setting, "off") == 0) {
	    allow_ignore = 0;
	    notice_lang(s_OperServ, u, OPER_SET_IGNORE_OFF);
	} else {
	    notice_lang(s_OperServ, u, OPER_SET_IGNORE_ERROR);
	}

    } else if (stricmp(option, "READONLY") == 0) {
	if (stricmp(setting, "on") == 0) {
	    readonly = 1;
	    log("Read-only mode activated");
	    close_log();
	    notice_lang(s_OperServ, u, OPER_SET_READONLY_ON);
	} else if (stricmp(setting, "off") == 0) {
	    readonly = 0;
	    open_log();
	    log("Read-only mode deactivated");
	    notice_lang(s_OperServ, u, OPER_SET_READONLY_OFF);
	} else {
	    notice_lang(s_OperServ, u, OPER_SET_READONLY_ERROR);
	}

    } else if (stricmp(option, "DEBUG") == 0) {
	if (stricmp(setting, "on") == 0) {
	    debug = 1;
	    log("Debug mode activated");
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_ON);
	} else if (stricmp(setting, "off") == 0 ||
				(*setting == '0' && atoi(setting) == 0)) {
	    log("Debug mode deactivated");
	    debug = 0;
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_OFF);
	} else if (isdigit(*setting) && atoi(setting) > 0) {
	    debug = atoi(setting);
	    log("Debug mode activated (level %d)", debug);
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_LEVEL, debug);
	} else {
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_ERROR);
	}

    } else if (stricmp(option, "SUPASS") == 0) {
	int len;
	char newpass[PASSMAX];

	if (!is_services_root(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	if (!setting) {
	    no_supass = 1;
	    notice_lang(s_OperServ, u, OPER_SET_SUPASS_NONE);
	    return;
	}
	len = strlen(setting);
	if (len >= PASSMAX) {
	    memset(setting+PASSMAX-1, 0, len-(PASSMAX-1));
	    len = PASSMAX-1;
	    notice_lang(s_OperServ, u, PASSWORD_TRUNCATED, len);
	}
	if (encrypt(setting, len, newpass, PASSMAX) < 0) {
	    notice_lang(s_OperServ, u, OPER_SET_SUPASS_FAILED);
	} else {
	    no_supass = 0;
	    memcpy(supass, newpass, PASSMAX);
	    notice_lang(s_OperServ, u, OPER_SET_SUPASS_OK);
	}

    } else {
	notice_lang(s_OperServ, u, OPER_SET_UNKNOWN_OPTION, option);
    }
}

/*************************************************************************/

static void do_jupe(User *u)
{
    char *jserver = strtok(NULL, " ");
    char *reason = strtok(NULL, "");
    char buf[BUFSIZE];

    if (!jserver) {
	syntax_error(s_OperServ, u, "JUPE", OPER_JUPE_SYNTAX);
    } else {
	wallops(s_OperServ, "\2Juping\2 %s by request of \2%s\2.",
		jserver, u->nick);
	if (reason)
	    snprintf(buf, sizeof(buf), "%s (%s)", reason, u->nick);
	else
	    snprintf(buf, sizeof(buf), "Jupitered by %s", u->nick);
	send_server_remote(jserver, buf);
    }
}

/*************************************************************************/

static void do_raw(User *u)
{
    char *text = strtok(NULL, "");

    if (!text)
	syntax_error(s_OperServ, u, "RAW", OPER_RAW_SYNTAX);
    else
	send_cmd(NULL, "%s", text);
}

/*************************************************************************/

static void do_update(User *u)
{
    notice_lang(s_OperServ, u, OPER_UPDATING);
    save_data = 1;
}

/*************************************************************************/

static void do_os_quit(User *u)
{
    quitmsg = malloc(28 + strlen(u->nick));
    if (!quitmsg)
	quitmsg = "QUIT command received, but out of memory!";
    else
	sprintf(quitmsg, "QUIT command received from %s", u->nick);
    quitting = 1;
}

/*************************************************************************/

static void do_shutdown(User *u)
{
    quitmsg = malloc(32 + strlen(u->nick));
    if (!quitmsg)
	quitmsg = "SHUTDOWN command received, but out of memory!";
    else
	sprintf(quitmsg, "SHUTDOWN command received from %s", u->nick);
    save_data = 1;
    delayed_quit = 1;
}

/*************************************************************************/

static void do_restart(User *u)
{
    quitmsg = malloc(31 + strlen(u->nick));
    if (!quitmsg)
	quitmsg = "RESTART command received, but out of memory!";
    else
	sprintf(quitmsg, "RESTART command received from %s", u->nick);
    raise(SIGHUP);
}

/*************************************************************************/

static void do_listignore(User *u)
{
    int sent_header = 0;
    IgnoreData *id;

    for (id = first_ignore(); id; id = next_ignore()) {
	if (!sent_header) {
	    notice_lang(s_OperServ, u, OPER_IGNORE_LIST);
	    sent_header = 1;
	}
	notice(s_OperServ, u->nick, "%ld %s", id->time, id->who);
    }
    if (!sent_header)
	notice_lang(s_OperServ, u, OPER_IGNORE_LIST_EMPTY);
}

/*************************************************************************/

#ifdef DEBUG_COMMANDS

static void do_matchwild(User *u)
{
    char *pat = strtok(NULL, " ");
    char *str = strtok(NULL, " ");
    if (pat && str)
	notice(s_OperServ, u->nick, "%d", match_wild(pat, str));
    else
	notice(s_OperServ, u->nick, "Syntax error.");
}

#endif	/* DEBUG_COMMANDS */

/*************************************************************************/

/* Kill all users matching a certain host. The host is obtained from the
 * supplied nick. The raw hostmsk is not supplied with the command in an effort
 * to prevent abuse and mistakes from being made - which might cause *.com to
 * be killed. It also makes it very quick and simple to use - which is usually
 * what you want when someone starts loading numerous clones. In addition to
 * killing the clones, we add a temporary AKILL to prevent them from
 * immediately reconnecting.
 * Syntax: KILLCLONES nick
 * -TheShadow (29 Mar 1999)
 */

static void do_killclones(User *u)
{
    char *clonenick = strtok(NULL, " ");
    int count=0;
    User *cloneuser, *user, *tempuser;
    char *clonemask, *akillmask;
    char killreason[NICKMAX+32];
    char akillreason[] = "Temporary KILLCLONES akill.";

    if (!clonenick) {
	notice_lang(s_OperServ, u, OPER_KILLCLONES_SYNTAX);

    } else if (!(cloneuser = finduser(clonenick))) {
	notice_lang(s_OperServ, u, OPER_KILLCLONES_UNKNOWN_NICK, clonenick);

    } else {
	clonemask = smalloc(strlen(cloneuser->host) + 5);
	sprintf(clonemask, "*!*@%s", cloneuser->host);

	akillmask = smalloc(strlen(cloneuser->host) + 3);
	sprintf(akillmask, "*@%s", strlower(cloneuser->host));

	user = firstuser();
	while (user) {
	    if (match_usermask(clonemask, user) != 0) {
		tempuser = nextuser();
		count++;
		snprintf(killreason, sizeof(killreason),
					"Cloning [%d]", count);
		kill_user(NULL, user->nick, killreason);
		user = tempuser;
	    } else {
		user = nextuser();
	    }
	}

	add_akill(akillmask, akillreason, u->nick,
			time(NULL) + KillClonesAkillExpire);

	wallops(s_OperServ, "\2%s\2 used KILLCLONES for \2%s\2 killing "
			"\2%d\2 clones. A temporary AKILL has been added "
			"for \2%s\2.", u->nick, clonemask, count, akillmask);

	log("%s: KILLCLONES: %d clone(s) matching %s killed.",
			s_OperServ, count, clonemask);

	free(akillmask);
	free(clonemask);
    }
}

/*************************************************************************/

/*************************************************************************/

/* Close the NETwork in case of mass loading of clone into the network.
 * aKa, nobody except opers & ppl on exception list will be able to enter 
 * the net.
 */
static void do_closenet (User *u) {
	char *closingtime = strtok(NULL, " ");
	Timeout *t = NULL;
	int delay;
	
	if  (!closingtime) {
		if (net_stat==1) {
			net_stat=0;
			wallops(s_OperServ, "\2%s\2 cancelled a previously called CLOSENET.", u->nick);
		} 
		else {
			send_cmd(s_OperServ, "NOTICE %s :CLOSENET \2Time in seconds\2 (Time should be between 1 and 600)", u->nick);
		}
	}
	else {
		delay = atoi(closingtime);
		if ((delay < 1) || (delay > 600)) {
			send_cmd(s_OperServ, "NOTICE %s :CLOSENET \2Time in seconds\2 (Time should be between 1 and 600)", u->nick);
			return;
		}
		t = add_timeout(delay, closenet_timeout, 0);
		send_cmd(s_OperServ, "NOTICE %s :CLOSENET Successfully \2added\2 for %d seconds", u->nick, delay);
		wallops(s_OperServ, "\2%s\2 closed the net for %d seconds.", u->nick, delay);
		net_stat = 1;
	}
}

/*************************************************************************/

static void closenet_timeout(Timeout *to)
{
	if (net_stat==1) {
		net_stat=0;
		wallops(s_OperServ, "CLOSENET normally timed out.");
	}
	else { 
		net_stat=0;
	}
}

/*************************************************************************/

int is_net_closed(void)
{
	return (int) net_stat;
}

/*************************************************************************/


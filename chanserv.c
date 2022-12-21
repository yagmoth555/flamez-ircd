/* ChanServ functions.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

/*************************************************************************/

#include "services.h"
#include "pseudo.h"

/*************************************************************************/
/************************** Declaration section **************************/
/*************************************************************************/

#define HASH(chan)  (hashtable[(unsigned char)((chan)[1])]<<5 \
		     | (chan[1] ? hashtable[(unsigned char)((chan)[2])] : 0))
#define HASHSIZE    1024
static ChannelInfo *chanlists[HASHSIZE];

static const char hashtable[256] = {
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,24,25,26,27,28,29, 0, 0,
     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,30,

    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,

    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
};

/*************************************************************************/

/* Channel option list. */

typedef struct {
    char *name;
    int32 flag;
    int namestr;  /* If -1, will be ignored by cs_flags_to_string() */
    int onstr, offstr, syntaxstr;
} ChanOpt;

#define CHANOPT(x) \
    { #x, CI_##x, CHAN_INFO_OPT_##x, \
      CHAN_SET_##x##_ON, CHAN_SET_##x##_OFF, CHAN_SET_##x##_SYNTAX }
ChanOpt chanopts[] = {
    CHANOPT(KEEPTOPIC),
    CHANOPT(TOPICLOCK),
    CHANOPT(PRIVATE),
    CHANOPT(SECUREOPS),
    CHANOPT(LEAVEOPS),
    CHANOPT(RESTRICTED),
    CHANOPT(SECURE),
    CHANOPT(OPNOTICE),
    CHANOPT(ENFORCE),
    { "NOEXPIRE", CI_NOEXPIRE, -1, CHAN_SET_NOEXPIRE_ON,
	  CHAN_SET_NOEXPIRE_OFF, CHAN_SET_NOEXPIRE_SYNTAX },
    { NULL }
};
#undef CHANOPT

/*************************************************************************/

/* Access level control data. */

/* Default levels.  All levels MUST be listed here irrespective of IRC
 * server type. */
static int def_levels[][2] = {
    { CA_AUTOOP,             5 },
    { CA_AUTOVOICE,          3 },
    { CA_AUTODEOP,          -1 },
    { CA_NOJOIN,            -2 },
    { CA_INVITE,             5 },
    { CA_AKICK,             10 },
    { CA_SET,   ACCLEV_INVALID },
    { CA_CLEAR, ACCLEV_INVALID },
    { CA_UNBAN,              5 },
    { CA_OPDEOP,             5 },
    { CA_ACCESS_LIST,        0 },
    { CA_ACCESS_CHANGE,     10 },
    { CA_MEMO,              10 },
    { CA_VOICE,              3 },
    { CA_AUTOHALFOP,         4 },
    { CA_HALFOP,             4 },
    { CA_AUTOPROTECT,       10 },
    { CA_PROTECT,           10 },
    { -1 }
};

/* Information for LEVELS command.  Levels not listed here will not be
 * viewable or settable by the user. */
typedef struct {
    int what;
    char *name;
    int desc;
} LevelInfo;
static LevelInfo levelinfo[] = {
    { CA_AUTOOP,        "AUTOOP",     CHAN_LEVEL_AUTOOP },
    { CA_AUTOVOICE,     "AUTOVOICE",  CHAN_LEVEL_AUTOVOICE },
#ifdef HAVE_HALFOP
    { CA_AUTODEOP,      "AUTODEOP",   CHAN_LEVEL_AUTODEOP_HALFOP },
#else
    { CA_AUTODEOP,      "AUTODEOP",   CHAN_LEVEL_AUTODEOP },
#endif
    { CA_NOJOIN,        "NOJOIN",     CHAN_LEVEL_NOJOIN },
    { CA_INVITE,        "INVITE",     CHAN_LEVEL_INVITE },
    { CA_AKICK,         "AKICK",      CHAN_LEVEL_AKICK },
    { CA_SET,           "SET",        CHAN_LEVEL_SET },
    { CA_CLEAR,         "CLEAR",      CHAN_LEVEL_CLEAR },
    { CA_UNBAN,         "UNBAN",      CHAN_LEVEL_UNBAN },
    { CA_OPDEOP,        "OP-DEOP",    CHAN_LEVEL_OPDEOP },
    { CA_ACCESS_LIST,   "ACC-LIST",   CHAN_LEVEL_ACCESS_LIST },
    { CA_ACCESS_CHANGE, "ACC-CHANGE", CHAN_LEVEL_ACCESS_CHANGE },
    { CA_MEMO,          "MEMO",       CHAN_LEVEL_MEMO },
    { CA_VOICE,         "VOICE",      CHAN_LEVEL_VOICE },
#ifdef HAVE_HALFOP
    { CA_AUTOHALFOP,    "AUTOHALFOP", CHAN_LEVEL_AUTOHALFOP },
    { CA_HALFOP,        "HALFOP",     CHAN_LEVEL_HALFOP },
#endif
#ifdef HAVE_CHANPROT
    { CA_AUTOPROTECT,   "AUTOPROTECT",CHAN_LEVEL_AUTOPROTECT },
    { CA_PROTECT,       "PROTECT",    CHAN_LEVEL_PROTECT },
#endif
    { -1 }
};
static int levelinfo_maxwidth = 0;

/*************************************************************************/

/* Local functions. */

static void alpha_insert_chan(ChannelInfo *ci);
static ChannelInfo *makechan(const char *chan);
static int delchan(ChannelInfo *ci);
static void count_chan(ChannelInfo *ci);
static void uncount_chan(ChannelInfo *ci);
static void reset_levels(ChannelInfo *ci);
static int is_founder(User *user, ChannelInfo *ci);
static int is_identified(User *user, ChannelInfo *ci);
static int get_access(User *user, ChannelInfo *ci);
static void suspend(ChannelInfo *ci, const char *reason,
		    const char *who, const time_t expires);
static void unsuspend(ChannelInfo *ci, int set_time);
static void chan_bad_password(User *u, ChannelInfo *ci);
static ChanOpt *chanopt_from_name(const char *optname);

static void do_help(User *u);
static void do_register(User *u);
static void do_identify(User *u);
static void do_drop(User *u);
static void do_set(User *u);
static void do_unset(User *u);
static void do_set_founder(User *u, ChannelInfo *ci, char *param);
static void do_set_successor(User *u, ChannelInfo *ci, char *param);
static void do_set_password(User *u, ChannelInfo *ci, char *param);
static void do_set_floodserv(User *u, ChannelInfo *ci, char *param);
static void do_set_desc(User *u, ChannelInfo *ci, char *param);
static void do_set_url(User *u, ChannelInfo *ci, char *param);
static void do_set_email(User *u, ChannelInfo *ci, char *param);
static void do_set_entrymsg(User *u, ChannelInfo *ci, char *param);
static void do_set_topic(User *u, ChannelInfo *ci, char *param);
static void do_set_mlock(User *u, ChannelInfo *ci, char *param);
static void do_set_boolean(User *u, ChannelInfo *ci, ChanOpt *co, char *param);
static void do_access(User *u);
static void do_sop(User *u);
static void do_aop(User *u);
#ifdef HAVE_HALFOP
static void do_hop(User *u);
#endif
static void do_vop(User *u);
static void do_akick(User *u);
static void do_info(User *u);
static void do_list(User *u);
static void do_invite(User *u);
static void do_levels(User *u);
static void do_op(User *u);
static void do_deop(User *u);
static void do_voice(User *u);
static void do_devoice(User *u);
#ifdef HAVE_HALFOP
static void do_halfop(User *u);
static void do_dehalfop(User *u);
#endif
#ifdef HAVE_CHANPROT
static void do_protect(User *u);
static void do_deprotect(User *u);
#endif
static void do_unban(User *u);
static void do_clear(User *u);
static void do_getpass(User *u);
static void do_forbid(User *u);
static void do_suspend(User *u);
static void do_unsuspend(User *u);
static void do_status(User *u);

/*************************************************************************/

/* Command list. */

static Command cmds[] = {
    { "HELP",     do_help,     NULL,  -1,                       -1,-1,-1,-1 },
    { "REGISTER", do_register, NULL,  CHAN_HELP_REGISTER,       -1,-1,-1,-1 },
    { "IDENTIFY", do_identify, NULL,  CHAN_HELP_IDENTIFY,       -1,-1,-1,-1 },
    { "DROP",     do_drop,     NULL,  -1,
		CHAN_HELP_DROP, CHAN_SERVADMIN_HELP_DROP,
		CHAN_SERVADMIN_HELP_DROP, CHAN_SERVADMIN_HELP_DROP },
    { "SET",      do_set,      NULL,  CHAN_HELP_SET,
		-1, CHAN_SERVADMIN_HELP_SET,
		CHAN_SERVADMIN_HELP_SET, CHAN_SERVADMIN_HELP_SET },
    { "SET FOUNDER",    NULL,  NULL,  CHAN_HELP_SET_FOUNDER,    -1,-1,-1,-1 },
    { "SET SUCCESSOR",  NULL,  NULL,  CHAN_HELP_SET_SUCCESSOR,  -1,-1,-1,-1 },
    { "SET PASSWORD",   NULL,  NULL,  CHAN_HELP_SET_PASSWORD,   -1,-1,-1,-1 },
	{ "SET FLOODSERV",  NULL,  NULL,  CHAN_HELP_SET_FLOODSERV,  -1,-1,-1,-1 },
    { "SET DESC",       NULL,  NULL,  CHAN_HELP_SET_DESC,       -1,-1,-1,-1 },
    { "SET URL",        NULL,  NULL,  CHAN_HELP_SET_URL,        -1,-1,-1,-1 },
    { "SET EMAIL",      NULL,  NULL,  CHAN_HELP_SET_EMAIL,      -1,-1,-1,-1 },
    { "SET ENTRYMSG",   NULL,  NULL,  CHAN_HELP_SET_ENTRYMSG,   -1,-1,-1,-1 },
    { "SET TOPIC",      NULL,  NULL,  CHAN_HELP_SET_TOPIC,      -1,-1,-1,-1 },
    { "SET KEEPTOPIC",  NULL,  NULL,  CHAN_HELP_SET_KEEPTOPIC,  -1,-1,-1,-1 },
    { "SET TOPICLOCK",  NULL,  NULL,  CHAN_HELP_SET_TOPICLOCK,  -1,-1,-1,-1 },
    { "SET MLOCK",      NULL,  NULL,  CHAN_HELP_SET_MLOCK,      -1,-1,-1,-1 },
    { "SET PRIVATE",    NULL,  NULL,  CHAN_HELP_SET_PRIVATE,	-1,-1,-1,-1 },
    { "SET RESTRICTED", NULL,  NULL,  CHAN_HELP_SET_RESTRICTED, -1,-1,-1,-1 },
    { "SET SECURE",     NULL,  NULL,  CHAN_HELP_SET_SECURE,     -1,-1,-1,-1 },
    { "SET SECUREOPS",  NULL,  NULL,  CHAN_HELP_SET_SECUREOPS,  -1,-1,-1,-1 },
    { "SET LEAVEOPS",   NULL,  NULL,  CHAN_HELP_SET_LEAVEOPS,   -1,-1,-1,-1 },
    { "SET OPNOTICE",   NULL,  NULL,  CHAN_HELP_SET_OPNOTICE,   -1,-1,-1,-1 },
    { "SET ENFORCE",    NULL,  NULL,  CHAN_HELP_SET_ENFORCE,    -1,-1,-1,-1 },
    { "SET NOEXPIRE",   NULL,  NULL,  -1, -1,
		CHAN_SERVADMIN_HELP_SET_NOEXPIRE,
		CHAN_SERVADMIN_HELP_SET_NOEXPIRE,
		CHAN_SERVADMIN_HELP_SET_NOEXPIRE },
    { "UNSET",    do_unset,    NULL,  CHAN_HELP_UNSET,
		-1, CHAN_SERVADMIN_HELP_UNSET,
		CHAN_SERVADMIN_HELP_UNSET, CHAN_SERVADMIN_HELP_UNSET },
    { "SOP",	  do_sop,      NULL,  CHAN_HELP_SOP,            -1,-1,-1,-1 },
    { "AOP",	  do_aop,      NULL,  CHAN_HELP_AOP,            -1,-1,-1,-1 },
#ifdef HAVE_HALFOP
    { "HOP",	  do_hop,      NULL,  CHAN_HELP_HOP,            -1,-1,-1,-1 },
#endif
    { "VOP",	  do_vop,      NULL,  CHAN_HELP_VOP,            -1,-1,-1,-1 },
    { "ACCESS",   do_access,   NULL,  CHAN_HELP_ACCESS,         -1,-1,-1,-1,
		(const char *)ACCLEV_SOP,
		(const char *)ACCLEV_AOP,
		(const char *)ACCLEV_VOP },
    { "ACCESS LEVELS",  NULL,  NULL,  CHAN_HELP_ACCESS_LEVELS,  -1,-1,-1,-1,
		(const char *)ACCLEV_SOP,
		(const char *)ACCLEV_AOP,
		(const char *)ACCLEV_VOP },
    { "AKICK",    do_akick,    NULL,  CHAN_HELP_AKICK,          -1,-1,-1,-1 },
    { "LEVELS",   do_levels,   NULL,  CHAN_HELP_LEVELS,         -1,-1,-1,-1 },
    { "INFO",     do_info,     NULL,  CHAN_HELP_INFO,
		-1, CHAN_SERVADMIN_HELP_INFO, CHAN_SERVADMIN_HELP_INFO,
		CHAN_SERVADMIN_HELP_INFO },
    { "LIST",     do_list,     NULL,  -1,
		CHAN_HELP_LIST, CHAN_SERVADMIN_HELP_LIST,
		CHAN_SERVADMIN_HELP_LIST, CHAN_SERVADMIN_HELP_LIST },
    { "OP",       do_op,       NULL,  CHAN_HELP_OP,             -1,-1,-1,-1 },
    { "DEOP",     do_deop,     NULL,  CHAN_HELP_DEOP,           -1,-1,-1,-1 },
    { "VOICE",    do_voice,    NULL,  CHAN_HELP_VOICE,          -1,-1,-1,-1 },
    { "DEVOICE",  do_devoice,  NULL,  CHAN_HELP_DEVOICE,        -1,-1,-1,-1 },
#ifdef HAVE_HALFOP
    { "HALFOP",   do_halfop,   NULL,  CHAN_HELP_HALFOP,         -1,-1,-1,-1 },
    { "DEHALFOP", do_dehalfop, NULL,  CHAN_HELP_DEHALFOP,       -1,-1,-1,-1 },
#endif
#ifdef HAVE_CHANPROT
    { "PROTECT",  do_protect,  NULL,  CHAN_HELP_PROTECT,        -1,-1,-1,-1 },
    { "DEPROTECT",do_deprotect,NULL,  CHAN_HELP_DEPROTECT,      -1,-1,-1,-1 },
#endif
    { "INVITE",   do_invite,   NULL,  CHAN_HELP_INVITE,         -1,-1,-1,-1 },
    { "UNBAN",    do_unban,    NULL,  CHAN_HELP_UNBAN,          -1,-1,-1,-1 },
    { "CLEAR",    do_clear,    NULL,  CHAN_HELP_CLEAR,          -1,-1,-1,-1 },
    { "GETPASS",  do_getpass,  is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_GETPASS,
		CHAN_SERVADMIN_HELP_GETPASS, CHAN_SERVADMIN_HELP_GETPASS },
    { "FORBID",   do_forbid,   is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_FORBID,
		CHAN_SERVADMIN_HELP_FORBID, CHAN_SERVADMIN_HELP_FORBID },
    { "SUSPEND",  do_suspend,  is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_SUSPEND,
		CHAN_SERVADMIN_HELP_SUSPEND, CHAN_SERVADMIN_HELP_SUSPEND },
    { "UNSUSPEND",do_unsuspend,is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_UNSUSPEND,
		CHAN_SERVADMIN_HELP_UNSUSPEND, CHAN_SERVADMIN_HELP_UNSUSPEND },
    { "STATUS",   do_status,   is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_STATUS,
		CHAN_SERVADMIN_HELP_STATUS, CHAN_SERVADMIN_HELP_STATUS },
    { NULL }
};

/*************************************************************************/
/************************ Main ChanServ routines *************************/
/*************************************************************************/

/* ChanServ initialization. */

void cs_init(void)
{
    Command *cmd;

    cmd = lookup_cmd(cmds, "REGISTER");
    if (cmd)
	cmd->help_param1 = s_NickServ;
    cmd = lookup_cmd(cmds, "SET SECURE");
    if (cmd)
	cmd->help_param1 = s_NickServ;
    cmd = lookup_cmd(cmds, "SET SUCCESSOR");
    if (cmd)
	cmd->help_param1 = (char *)(long)CSMaxReg;
}

/*************************************************************************/

/* Main ChanServ routine. */

void chanserv(const char *source, char *buf)
{
    char *cmd, *s;
    User *u = finduser(source);

    if (!u) {
	log("%s: user record for %s not found", s_ChanServ, source);
	notice(s_ChanServ, source,
		getstring((NickInfo *)NULL, USER_RECORD_NOT_FOUND));
	return;
    }

    cmd = strtok(buf, " ");

    if (!cmd) {
	return;
    } else if (stricmp(cmd, "\1PING") == 0) {
	if (!(s = strtok(NULL, "")))
	    s = "\1";
	notice(s_ChanServ, source, "\1PING %s", s);
    } else if (skeleton) {
	notice_lang(s_ChanServ, u, SERVICE_OFFLINE, s_ChanServ);
    } else {
	run_cmd(s_ChanServ, u, cmds, cmd);
    }
}

/*************************************************************************/

/* Return the ChannelInfo structure for the given channel, or NULL if the
 * channel isn't registered. */

ChannelInfo *cs_findchan(const char *chan)
{
    ChannelInfo *ci;

    for (ci = chanlists[HASH(chan)]; ci; ci = ci->next) {
	if (irc_stricmp(ci->name, chan) == 0)
	    return ci;
    }
    return NULL;
}

/*************************************************************************/

/* Iterate over all ChannelInfo structures.  Return NULL when called after
 * reaching the last channel.
 */

static int iterator_pos = HASHSIZE;   /* return NULL initially */
static ChannelInfo *iterator_ptr = NULL;

ChannelInfo *cs_firstchan(void)
{
    iterator_pos = -1;
    iterator_ptr = NULL;
    return cs_nextchan();
}

ChannelInfo *cs_nextchan(void)
{
    if (iterator_ptr)
	iterator_ptr = iterator_ptr->next;
    while (!iterator_ptr && iterator_pos < HASHSIZE) {
	iterator_pos++;
	if (iterator_pos < HASHSIZE)
	    iterator_ptr = chanlists[iterator_pos];
    }
    return iterator_ptr;
}

/*************************************************************************/

/* Return information on memory use.  Assumes pointers are valid. */

void get_chanserv_stats(long *nrec, long *memuse)
{
    long count = 0, mem = 0;
    int i;
    ChannelInfo *ci;

    for (ci = cs_firstchan(); ci; ci = cs_nextchan()) {
	count++;
	mem += sizeof(*ci);
	if (ci->desc)
	    mem += strlen(ci->desc)+1;
	if (ci->url)
	    mem += strlen(ci->url)+1;
	if (ci->email)
	    mem += strlen(ci->email)+1;
	mem += ci->accesscount * sizeof(ChanAccess);
	mem += ci->akickcount * sizeof(AutoKick);
	for (i = 0; i < ci->akickcount; i++) {
	    if (!ci->akick[i].is_nick && ci->akick[i].u.mask)
		mem += strlen(ci->akick[i].u.mask)+1;
	    if (ci->akick[i].reason)
		mem += strlen(ci->akick[i].reason)+1;
	}
	if (ci->mlock_key)
	    mem += strlen(ci->mlock_key)+1;
	if (ci->last_topic)
	    mem += strlen(ci->last_topic)+1;
	if (ci->entry_message)
	    mem += strlen(ci->entry_message)+1;
	if (ci->levels)
	    mem += sizeof(*ci->levels) * CA_SIZE;
    }
    *nrec = count;
    *memuse = mem;
}

/*************************************************************************/
/************************ Global utility routines ************************/
/*************************************************************************/

#include "cs-loadsave.c"

/*************************************************************************/

/* Check the current modes on a channel; if they conflict with a mode lock,
 * fix them. */

void check_modes(const char *chan)
{
    Channel *c = findchan(chan);
    ChannelInfo *ci;
    char newmodes[40];	/* 31 possible modes + extra leeway */
    char *newkey = NULL;
    int32 newlimit = 0;
    char *end = newmodes;
    int modes;
    int set_limit = 0, set_key = 0;

    if (!c || c->bouncy_modes)
	return;

    if (!NoBouncyModes) {
	/* Check for mode bouncing */
	if (c->server_modecount >= 3 && c->chanserv_modecount >= 3) {
#if defined(IRC_DALNET) || defined(IRC_UNDERNET)
	    wallops(NULL, "Warning: unable to set modes on channel %s.  "
		    "Are your servers' U:lines configured correctly?", chan);
#else
	    wallops(NULL, "Warning: unable to set modes on channel %s.  "
		    "Are your servers configured correctly?", chan);
#endif
	    log("%s: Bouncy modes on channel %s", s_ChanServ, c->name);
	    c->bouncy_modes = 1;
	    return;
	}
	if (c->chanserv_modetime != time(NULL)) {
	    c->chanserv_modecount = 0;
	    c->chanserv_modetime = time(NULL);
	}
	c->chanserv_modecount++;
    }

    ci = c->ci;
    if (!ci) {
	/* Services _always_ knows who should be +r. If a channel tries to be
	 * +r and is not registered, send mode -r. This will compensate for
	 * servers that are split when mode -r is initially sent and then try
	 * to set +r when they rejoin. -TheShadow
	 */
	if (c->mode & CMODE_REG) {
	    c->mode &= ~CMODE_REG;
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -%s", c->name,
		     mode_flags_to_string(CMODE_REG, MODE_CHANNEL));
	}
	return;
    }

    modes = ~c->mode & (ci->mlock_on | CMODE_REG);
    end += snprintf(end, sizeof(newmodes)-(end-newmodes)-2,
		    "+%s", mode_flags_to_string(modes, MODE_CHANNEL));
    c->mode |= modes;
    if (ci->mlock_limit && ci->mlock_limit != c->limit) {
	*end++ = 'l';
	newlimit = ci->mlock_limit;
	c->limit = newlimit;
	set_limit = 1;
    }
    if (ci->mlock_key) {
	if (c->key && strcmp(c->key, ci->mlock_key) != 0) {
	    /* Send this directly, since send_cmode() will edit it out */
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -k %s",
		     c->name, c->key);
	    free(c->key);
	    c->key = NULL;
	}
	if (!c->key) {
	    *end++ = 'k';
	    newkey = ci->mlock_key;
	    c->key = sstrdup(newkey);
	    set_key = 1;
	}
    }
    if (end[-1] == '+')
	end--;

    modes = c->mode & ci->mlock_off;
    end += snprintf(end, sizeof(newmodes)-(end-newmodes)-1,
		    "-%s", mode_flags_to_string(modes, MODE_CHANNEL));
    c->mode &= ~modes;
    if (c->limit && (ci->mlock_off & CMODE_l)) {
	*end++ = 'l';
	c->limit = 0;
    }
    if (c->key && (ci->mlock_off & CMODE_k)) {
	*end++ = 'k';
	newkey = sstrdup(c->key);
	free(c->key);
	c->key = NULL;
	set_key = 1;
    }
    if (end[-1] == '-')
	end--;

    if (end == newmodes)
	return;
    *end = 0;
    if (set_limit) {
	char newlimit_str[32];
	snprintf(newlimit_str, sizeof(newlimit_str), "%d", newlimit);
	send_cmode(MODE_SENDER(s_ChanServ), c->name, newmodes, newlimit_str,
		   newkey ? newkey : "");
    } else {
	send_cmode(MODE_SENDER(s_ChanServ), c->name, newmodes,
		   newkey ? newkey : "");
    }

    if (newkey && !c->key)
	free(newkey);
}

/*************************************************************************/

/* Check whether a user should be opped or voiced on a channel, and if so,
 * do it.  Return the user's new modes on the channel (CUMODE_* flags).
 * Updates the channel's last used time if the user is opped.  `modes' is
 * the user's current mode set.  `source' is the source of the message
 * which caused the mode change, NULL for a join.
 * On Unreal servers, sets +q mode for channel founder or identified users.
 */

int check_chan_user_modes(const char *source, User *user, const char *chan,
			  int32 modes)
{
    ChannelInfo *ci = cs_findchan(chan);
    int is_servermode = (!source || strchr(source, '.') != NULL);

    /* Don't change modes on unregistered, forbidden, or modeless channels */
    if (!ci || (ci->flags & CI_VERBOTEN) || *chan == '+')
	return modes;

    /* Don't reverse mode changes made by the user him/herself, or by
     * Services (because we prevent people from doing improper mode changes
     * via Services already, so anything that gets here must be okay). */
    if (source && (irc_stricmp(source, user->nick) == 0
		   || irc_stricmp(source, MODE_SENDER(s_ChanServ)) == 0
		   || irc_stricmp(source, MODE_SENDER(s_OperServ)) == 0))
	return modes;

#ifdef IRC_UNREAL
    /* Don't change modes for a +I user */
    if (user->mode & UMODE_I)
	return modes;
#endif

    /* Check early for server auto-ops */
    if ((modes & CUMODE_o)
     && !(ci->flags & CI_LEAVEOPS)
     && is_servermode
     && time(NULL)-start_time >= CSRestrictDelay
     && !check_access(user, ci, CA_AUTOOP)
    ) {
	notice_lang(s_ChanServ, user, CHAN_IS_REGISTERED, s_ChanServ);
	send_cmode(MODE_SENDER(s_ChanServ), chan, "-o", user->nick);
	modes &= ~CUMODE_o;
    }

    /* Mode additions.  Only check for join or server mode change, unless
     * ENFORCE is set */
    if (is_servermode || (ci->flags & CI_ENFORCE)) {
#ifdef HAVE_CHANPROT
	if (is_founder(user, ci)) {
	    ci->last_used = time(NULL);
	    if (!(modes & CUMODE_q))
		send_cmode(MODE_SENDER(s_ChanServ), chan, "+q", user->nick);
	    modes |= CUMODE_q;
	} else if (check_access(user, ci, CA_AUTOPROTECT)) {
	    ci->last_used = time(NULL);
	    if (!(modes & CUMODE_a))
		send_cmode(MODE_SENDER(s_ChanServ), chan, "+a", user->nick);
	    modes |= CUMODE_a;
	}
#endif
	if (check_access(user, ci, CA_AUTOOP)) {
	    ci->last_used = time(NULL);
	    if (!(modes & CUMODE_o))
		send_cmode(MODE_SENDER(s_ChanServ), chan, "+o", user->nick);
	    modes |= CUMODE_o;
#ifdef HAVE_HALFOP
	} else if (check_access(user, ci, CA_AUTOHALFOP)) {
	    if (!(modes & CUMODE_h))
		send_cmode(MODE_SENDER(s_ChanServ), chan, "+h", user->nick);
	    modes |= CUMODE_h;
#endif
	} else if (check_access(user, ci, CA_AUTOVOICE)) {
	    if (!(modes & CUMODE_v))
		send_cmode(MODE_SENDER(s_ChanServ), chan, "+v", user->nick);
	    modes |= CUMODE_v;
	}
    }

    /* Don't subtract modes from opers or Services admins */
    if (is_oper_u(user) || is_services_admin(user))
	return modes;

    /* Mode subtractions */
    if (check_access(user, ci, CA_AUTODEOP)) {
	if (modes & CUMODE_o) {
	    send_cmode(MODE_SENDER(s_ChanServ), chan, "-o", user->nick);
	    modes &= ~CUMODE_o;
	}
#ifdef HAVE_HALFOP
	if (modes & CUMODE_h) {
	    send_cmode(MODE_SENDER(s_ChanServ), chan, "-h", user->nick);
	    modes &= ~CUMODE_h;
	}
#endif
#ifdef HAVE_CHANPROT
	if (modes & CUMODE_a) {
	    send_cmode(MODE_SENDER(s_ChanServ), chan, "-a", user->nick);
	    modes &= ~CUMODE_a;
	}
	if (modes & CUMODE_q) {
	    send_cmode(MODE_SENDER(s_ChanServ), chan, "-q", user->nick);
	    modes &= ~CUMODE_q;
	}
#endif
    }

    return modes;
}

/*************************************************************************/

/* Tiny helper routine to get ChanServ out of a channel after it went in. */

static void timeout_leave(Timeout *to)
{
    char *chan = to->data;
    send_cmd(s_ChanServ, "PART %s", chan);
    free(to->data);
}


/* Check whether a user is permitted to be on a channel.  If so, return 0;
 * else, kickban the user with an appropriate message (could be either
 * AKICK or restricted access) and return 1.  Note that this is called
 * _before_ the user is added to internal channel lists (so do_kick() is
 * not called).
 */

int check_kick(User *user, const char *chan)
{
    Channel *c = findchan(chan);
    ChannelInfo *ci = cs_findchan(chan);
    AutoKick *akick;
    int i;
    NickInfo *ni;
    char *av[3], *mask, *s;
    const char *reason;
    Timeout *t;
    int stay;

    if (!ci)
	return 0;

    if (is_services_admin(user))
	return 0;

#ifdef IRC_UNREAL
    /* Don't let plain opers into +A (admin only) channels */
    if ((ci->mlock_on & CMODE_A) && !(user->mode & (UMODE_A|UMODE_N|UMODE_T))){
	mask = create_mask(user, 1);
	reason = getstring(user->ni, CHAN_NOT_ALLOWED_TO_JOIN);
	goto kick;
    }
    /* Don't let hiding users into no-hiding channels */
    if ((ci->mlock_on & CMODE_H) && (user->mode & UMODE_I)){
	mask = create_mask(user, 1);
	reason = getstring(user->ni, CHAN_NOT_ALLOWED_TO_JOIN);
	goto kick;
    }
#endif /* IRC_UNREAL */

    if (is_oper_u(user))
	return 0;

    if ((ci->flags & CI_VERBOTEN) || ci->suspendinfo) {
	mask = sstrdup("*!*@*");
	reason = getstring(user->ni, CHAN_MAY_NOT_BE_USED);
	goto kick;
    }

    if (ci->mlock_on & CMODE_OPERONLY) {
	/* We already know they're not an oper, so kick them off */
	mask = create_mask(user, 1);
	reason = getstring(user->ni, CHAN_NOT_ALLOWED_TO_JOIN);
	goto kick;
    }

    if (nick_recognized(user))
	ni = user->ni;
    else
	ni = NULL;

    for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
	if (!akick->in_use)
	    continue;
	if ((akick->is_nick && getlink(akick->u.ni) == ni)
	 || (!akick->is_nick && match_usermask(akick->u.mask, user))
	) {
	    if (debug >= 2) {
		log("debug: %s matched akick %s", user->nick,
			akick->is_nick ? akick->u.ni->nick : akick->u.mask);
	    }
	    mask = akick->is_nick ? create_mask(user, 1)
	                          : sstrdup(akick->u.mask);
	    reason = akick->reason ? akick->reason : CSAutokickReason;
	    goto kick;
	}
    }

    if (time(NULL)-start_time >= CSRestrictDelay
				&& check_access(user, ci, CA_NOJOIN)) {
	mask = create_mask(user, 1);
	reason = getstring(user->ni, CHAN_NOT_ALLOWED_TO_JOIN);
	goto kick;
    }

    return 0;

kick:
    if (debug) {
	log("debug: channel: AutoKicking %s!%s@%s",
		user->nick, user->username, user->host);
    }
    /* Remember that the user has not been added to our channel user list
     * yet, so we check whether the channel does not exist */
    stay = (c == NULL);
    av[0] = (char *)chan;
    if (stay) {
	send_cmd(s_ChanServ, "JOIN %s", chan);
	t = add_timeout(CSInhabit, timeout_leave, 0);
	t->data = sstrdup(chan);
    }
    /* Make sure the mask has an ! in it */
    if (!(s = strchr(mask, '!')) || s > strchr(mask, '@')) {
	int len = strlen(mask);
	mask = srealloc(mask, len+3);
	memmove(mask+2, mask, len+1);
	mask[0] = '*';
	mask[1] = '!';
    }
    /* Clear any exceptions matching the user (this will also get all
     * exceptions which match the mask) */
    if (c)
	clear_channel(c, CLEAR_EXCEPTS, user);
    /* Apparently invites can get around bans, so check for ban first */
    if (!chan_has_ban(chan, mask)) {
	av[1] = "+b";
	av[2] = mask;
	send_cmode(MODE_SENDER(s_ChanServ), chan, "+b", mask);
	do_cmode(MODE_SENDER(s_ChanServ), 3, av);
    }
    free(mask);
    send_cmd(MODE_SENDER(s_ChanServ), "KICK %s %s :%s", chan, user->nick,
	     reason);
    return 1;
}

/*************************************************************************/

/* Record the current channel topic in the ChannelInfo structure. */

void record_topic(Channel *c)
{
    ChannelInfo *ci = c->ci;

    if (readonly || !ci)
	return;
    if (ci->last_topic)
	free(ci->last_topic);
    if (c->topic)
	ci->last_topic = sstrdup(c->topic);
    else
	ci->last_topic = NULL;
    strscpy(ci->last_topic_setter, c->topic_setter, NICKMAX);
    ci->last_topic_time = c->topic_time;
}

/*************************************************************************/

/* Restore the topic in a channel when it's created, if we should. */

void restore_topic(Channel *c)
{
    ChannelInfo *ci = c->ci;

    if (!ci || !(ci->flags & CI_KEEPTOPIC))
	return;
    set_topic(c, ci->last_topic,
	      *ci->last_topic_setter ? ci->last_topic_setter : s_ChanServ,
	      ci->last_topic_time);
}

/*************************************************************************/

/* See if the topic is locked on the given channel, and return 1 (and fix
 * the topic) if so, 0 if not. */

int check_topiclock(const char *chan)
{
    Channel *c = findchan(chan);
    ChannelInfo *ci;

    if (!c || !(ci = c->ci) || !(ci->flags & CI_TOPICLOCK))
	return 0;
    set_topic(c, ci->last_topic,
	      *ci->last_topic_setter ? ci->last_topic_setter : s_ChanServ,
	      ci->last_topic_time);
    return 1;
}

/*************************************************************************/

/* Remove all channels and clear all suspensions which have expired. */

void expire_chans()
{
    ChannelInfo *ci, *next;
    time_t now = time(NULL);
    Channel *c;

    if (!CSExpire)
	return;

    for (ci = cs_firstchan(); ci; ci = next) {
	next = cs_nextchan();
	if (now >= ci->last_used + CSExpire
	 && !(ci->flags & (CI_VERBOTEN | CI_NOEXPIRE))
	 && !ci->suspendinfo
	) {
	    log("%s: Expiring channel %s", s_ChanServ, ci->name);
	    if (CMODE_REG && (c = findchan(ci->name))) {
		c->mode &= ~CMODE_REG;
		/* Send this out immediately, no send_cmode() delay */
		send_cmd(s_ChanServ, "MODE %s -%s", ci->name,
			 mode_flags_to_string(CMODE_REG, MODE_CHANNEL));
	    }
	    delchan(ci);
	} else if (ci->suspendinfo && ci->suspendinfo->expires
		   && now >= ci->suspendinfo->expires) {
	    log("%s: Expiring suspension for %s", s_ChanServ, ci->name);
	    unsuspend(ci, 1);
	}
    }
}

/*************************************************************************/

/* Remove a (deleted or expired) nickname from all channel lists. */

void cs_remove_nick(const NickInfo *ni)
{
    int i;
    ChannelInfo *ci, *next;
    ChanAccess *ca;
    AutoKick *akick;

    for (ci = cs_firstchan(); ci; ci = next) {
	next = cs_nextchan();
	if (ci->founder == ni) {
	    int was_suspended = (ci->suspendinfo != NULL);
	    char name_save[CHANMAX];
	    if (was_suspended)
		strscpy(name_save, ci->name, CHANMAX);
	    uncount_chan(ci);  /* Make sure it disappears from founderchans */
	    if (ci->successor) {
		NickInfo *ni2 = ci->successor;
		if (check_channel_limit(ni2) < 0) {
		    log("%s: Transferring foundership of %s from deleted "
			"nick %s to successor %s",
			s_ChanServ, ci->name, ni->nick, ni2->nick);
		    ci->founder = ni2;
		    ci->successor = NULL;
		    count_chan(ci);
		} else {
		    log("%s: Successor (%s) of %s owns too many channels, "
			"deleting channel",
			s_ChanServ, ni2->nick, ci->name);
		    goto delete;
		}
	    } else {
		log("%s: Deleting channel %s owned by deleted nick %s",
		    s_ChanServ, ci->name, ni->nick);
	      delete:
		delchan(ci);
		if (was_suspended) {
		    /* Channel was suspended, so make it forbidden */
		    log("%s: Channel %s was suspended, forbidding it",
			s_ChanServ, name_save);
		    ci = makechan(name_save);
		    ci->flags |= CI_VERBOTEN;
		}
		continue;
	    }
	}
	if (ci->successor == ni)
	    ci->successor = NULL;
	for (ca = ci->access, i = ci->accesscount; i > 0; ca++, i--) {
	    if (ca->in_use && ca->ni == ni) {
		ca->in_use = 0;
		ca->ni = NULL;
	    }
	}
	for (akick = ci->akick, i = ci->akickcount; i > 0; akick++, i--) {
	    if (akick->is_nick && akick->u.ni == ni) {
		akick->in_use = akick->is_nick = 0;
		akick->u.ni = NULL;
		if (akick->reason) {
		    free(akick->reason);
		    akick->reason = NULL;
		}
	    }
	}
    }
}

/*************************************************************************/

/* Return 1 if the user's access level on the given channel falls into the
 * given category, 0 otherwise.  Note that this may seem slightly confusing
 * in some cases: for example, check_access(..., CA_NOJOIN) returns true if
 * the user does _not_ have access to the channel (i.e. matches the NOJOIN
 * criterion). */

int check_access(User *user, ChannelInfo *ci, int what)
{
    int level = get_access(user, ci);
    int limit = ci->levels[what];

    if (level == ACCLEV_FOUNDER)
	return (what==CA_AUTODEOP || what==CA_NOJOIN) ? 0 : 1;
    /* Hacks to make flags work */
    if (what == CA_AUTODEOP && (ci->flags & CI_SECUREOPS) && level == 0)
	return 1;
    if (limit == ACCLEV_INVALID)
	return 0;
    if (what == CA_AUTODEOP || what == CA_NOJOIN)
	return level <= ci->levels[what];
    else
	return level >= ci->levels[what];
}

/*************************************************************************/

/* Check the nick's number of registered channels against its limit, and
 * return -1 if below the limit, 0 if at it exactly, and 1 if over it.
 */

int check_channel_limit(NickInfo *ni)
{
    register uint16 max, count;

    ni = getlink(ni);
    max = ni->channelmax;
    if (!max)
	max = MAX_CHANNELCOUNT;
    count = ni->channelcount;
    return count<max ? -1 : count==max ? 0 : 1;
}

/*************************************************************************/

/* Return a string listing the options (those given in chanopts[]) set on
 * the given channel.  Uses the given NickInfo for language information.
 * The returned string is stored in a static buffer which will be
 * overwritten on the next call.
 */

char *chanopts_to_string(ChannelInfo *ci, NickInfo *ni)
{
    static char buf[BUFSIZE];
    char *end = buf;
    const char *commastr = getstring(ni, COMMA_SPACE);
    const char *s;
    int need_comma = 0;
    int i;

    for (i = 0; chanopts[i].name && end-buf < sizeof(buf)-1; i++) {
	if (ni && chanopts[i].namestr < 0)
	    continue;
	if (ci->flags & chanopts[i].flag && chanopts[i].namestr >= 0) {
	    s = getstring(ni, chanopts[i].namestr);
	    if (need_comma)
		end += snprintf(end, sizeof(buf)-(end-buf), "%s", commastr);
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s", s);
	    need_comma = 1;
	}
    }
    return buf;
}

/*************************************************************************/
/*********************** ChanServ private routines ***********************/
/*************************************************************************/

/* Insert a channel alphabetically into the database. */

static void alpha_insert_chan(ChannelInfo *ci)
{
    ChannelInfo *ptr, *prev;
    char *chan = ci->name;
    int hash = HASH(chan);

    for (prev = NULL, ptr = chanlists[hash];
	 ptr != NULL && irc_stricmp(ptr->name, chan) < 0;
	 prev = ptr, ptr = ptr->next)
	;
    ci->prev = prev;
    ci->next = ptr;
    if (!prev)
	chanlists[hash] = ci;
    else
	prev->next = ci;
    if (ptr)
	ptr->prev = ci;
}

/*************************************************************************/

/* Add a channel to the database.  Returns a pointer to the new ChannelInfo
 * structure if the channel was successfully registered, NULL otherwise.
 * Assumes channel does not already exist. */

static ChannelInfo *makechan(const char *chan)
{
    ChannelInfo *ci;

    ci = scalloc(sizeof(ChannelInfo), 1);
    strscpy(ci->name, chan, CHANMAX);
    ci->time_registered = time(NULL);
    reset_levels(ci);
    alpha_insert_chan(ci);
    return ci;
}

/*************************************************************************/

/* Remove a channel from the ChanServ database.  Return 1 on success, 0
 * otherwise. */

static int delchan(ChannelInfo *ci)
{
    int i;
    User *u;

    /* Remove channel from founder's owned-channel count */
    uncount_chan(ci);

    /* Clear channel from users' identified-channel lists */
    for (u = firstuser(); u; u = nextuser()) {
	struct u_chaninfolist *uc, *next;
	for (uc = u->founder_chans; uc; uc = next) {
	    next = uc->next;
	    if (uc->chan == ci) {
		if (uc->next)
		    uc->next->prev = uc->prev;
		if (uc->prev)
		    uc->prev->next = uc->next;
		else
		    u->founder_chans = uc->next;
		free(uc);
	    }
	}
    }

    /* Now actually free channel data */
    if (ci->c)
	ci->c->ci = NULL;
    if (ci->next)
	ci->next->prev = ci->prev;
    if (ci->prev)
	ci->prev->next = ci->next;
    else
	chanlists[HASH(ci->name)] = ci->next;
    if (ci->desc)
	free(ci->desc);
    if (ci->mlock_key)
	free(ci->mlock_key);
    if (ci->last_topic)
	free(ci->last_topic);
    if (ci->suspendinfo)
	unsuspend(ci, 0);
    if (ci->access)
	free(ci->access);
    for (i = 0; i < ci->akickcount; i++) {
	if (!ci->akick[i].is_nick && ci->akick[i].u.mask)
	    free(ci->akick[i].u.mask);
	if (ci->akick[i].reason)
	    free(ci->akick[i].reason);
    }
    if (ci->akick)
	free(ci->akick);
    if (ci->levels)
	free(ci->levels);
    if (ci->memos.memos) {
	for (i = 0; i < ci->memos.memocount; i++) {
	    if (ci->memos.memos[i].text)
		free(ci->memos.memos[i].text);
	}
	free(ci->memos.memos);
    }
    free(ci);

    return 1;
}

/*************************************************************************/

/* Mark the given channel as owned by its founder.  This updates the
 * founder's list of owned channels (ni->founderchans) and the count of
 * owned channels for the founder and all linked nicks.
 */

static void count_chan(ChannelInfo *ci)
{
    NickInfo *ni = ci->founder;

    if (!ni)
	return;
    ni->foundercount++;
    ni->founderchans = srealloc(ni->founderchans,
				sizeof(*ni->founderchans) * ni->foundercount);
    ni->founderchans[ni->foundercount-1] = ci;
    while (ni) {
	/* Be paranoid--this could overflow in extreme cases, though we
	 * check for that elsewhere as well. */
	if (ni->channelcount+1 > ni->channelcount)
	    ni->channelcount++;
	ni = ni->link;
    }
}

/*************************************************************************/

/* Mark the given channel as no longer owned by its founder. */

static void uncount_chan(ChannelInfo *ci)
{
    NickInfo *ni = ci->founder;
    int i;

    if (!ni)
	return;
    for (i = 0; i < ni->foundercount; i++) {
	if (ni->founderchans[i] == ci) {
	    ni->foundercount--;
	    if (i < ni->foundercount)
		memmove(&ni->founderchans[i], &ni->founderchans[i+1],
			sizeof(*ni->founderchans) * (ni->foundercount-i));
	    ni->founderchans = srealloc(ni->founderchans,
			sizeof(*ni->founderchans) * ni->foundercount);
	    break;
	}
    }
    while (ni) {
	if (ni->channelcount > 0)
	    ni->channelcount--;
	ni = ni->link;
    }
}

/*************************************************************************/

/* Reset channel access level values to their default state. */

static void reset_levels(ChannelInfo *ci)
{
    int i;

    if (ci->levels)
	free(ci->levels);
    ci->levels = scalloc(CA_SIZE, sizeof(*ci->levels));
    for (i = 0; def_levels[i][0] >= 0; i++)
	ci->levels[def_levels[i][0]] = def_levels[i][1];
}

/*************************************************************************/

/* Does the given user have founder access to the channel? */

static int is_founder(User *user, ChannelInfo *ci)
{
    if ((ci->flags & CI_VERBOTEN) || ci->suspendinfo)
	return 0;
    if (user->ni == getlink(ci->founder)) {
	if ((nick_identified(user) ||
		 (nick_recognized(user) && !(ci->flags & CI_SECURE))))
	    return 1;
    }
    if (is_identified(user, ci))
	return 1;
    return 0;
}

/*************************************************************************/

/* Has the given user password-identified as founder for the channel? */

static int is_identified(User *user, ChannelInfo *ci)
{
    struct u_chaninfolist *c;

    for (c = user->founder_chans; c; c = c->next) {
	if (c->chan == ci)
	    return 1;
    }
    return 0;
}

/*************************************************************************/

/* Return the access level the given user has on the channel.  If the
 * channel doesn't exist, the user isn't on the access list, or the channel
 * is CS_SECURE and the user hasn't IDENTIFY'd with NickServ, return 0. */

static int get_access(User *user, ChannelInfo *ci)
{
    NickInfo *ni = user->ni;
    ChanAccess *access;
    int i;

    if (!ci || !ni || (ci->flags & CI_VERBOTEN) || ci->suspendinfo)
	return 0;
    if (is_founder(user, ci))
	return ACCLEV_FOUNDER;
    if (nick_identified(user)
	|| (nick_recognized(user) && !(ci->flags & CI_SECURE))
    ) {
	for (access = ci->access, i = 0; i < ci->accesscount; access++, i++) {
	    if (access->in_use && getlink(access->ni) == ni)
		return access->level;
	}
    }
    return 0;
}

/*************************************************************************/

/* Create a new SuspendInfo structure and associate it with the given
 * channel. */

static void suspend(ChannelInfo *ci, const char *reason,
		    const char *who, const time_t expires)
{
    SuspendInfo *si;

    si = scalloc(sizeof(*si), 1);
    strscpy(si->who, who, NICKMAX);
    si->reason = sstrdup(reason);
    si->suspended = time(NULL);
    si->expires = expires;
    ci->suspendinfo = si;
}

/*************************************************************************/

/* Delete the suspension data for the given channel.  We also alter the
 * last_seen value to ensure that it does not expire within the next
 * CSSuspendGrace seconds, giving its users a chance to reclaim it
 * (but only if set_time is non-zero).
 */

static void unsuspend(ChannelInfo *ci, int set_time)
{
    time_t now = time(NULL);

    if (!ci->suspendinfo) {
	log("%s: unsuspend() called on non-suspended channel %s",
	    s_ChanServ, ci->name);
	return;
    }
    if (ci->suspendinfo->reason)
	free(ci->suspendinfo->reason);
    free(ci->suspendinfo);
    ci->suspendinfo = NULL;
    if (set_time && CSExpire && CSSuspendGrace
     && (now - ci->last_used >= CSExpire - CSSuspendGrace)
    ) {
	ci->last_used = now - CSExpire + CSSuspendGrace;
	log("%s: unsuspend: Altering last_used time for %s to %ld.",
	    s_ChanServ, ci->name, ci->last_used);
    }
}

/*************************************************************************/

/* Register a bad password attempt for a channel. */

static void chan_bad_password(User *u, ChannelInfo *ci)
{
    bad_password(s_ChanServ, u, ci->name);
    ci->bad_passwords++;
    if (BadPassWarning && ci->bad_passwords == BadPassWarning) {
	wallops(s_ChanServ, "\2Warning:\2 Repeated bad password attempts"
	                    " for channel %s", ci->name);
    }
    if (BadPassSuspend && ci->bad_passwords == BadPassSuspend) {
	time_t expire = 0;
	if (CSSuspendExpire)
	    expire = time(NULL) + CSSuspendExpire;
	suspend(ci, "Too many bad passwords (automatic suspend)",
		s_ChanServ, expire);
	log("%s: Automatic suspend for %s (too many bad passwords)",
	    s_ChanServ, ci->name);
	/* Clear bad password count for when channel is unsuspended */
	ci->bad_passwords = 0;
    }
}

/*************************************************************************/

/* Return the ChanOpt structure for the given option name.  If not found,
 * return NULL.
 */

static ChanOpt *chanopt_from_name(const char *optname)
{
    int i;
    for (i = 0; chanopts[i].name; i++) {
	if (stricmp(chanopts[i].name, optname) == 0)
	    return &chanopts[i];
    }
    return NULL;
}

/*************************************************************************/
/*********************** ChanServ command routines ***********************/
/*************************************************************************/

static void do_help(User *u)
{
    char *cmd = strtok(NULL, "");

    if (!cmd) {
	notice_help(s_ChanServ, u, CHAN_HELP);
#if defined(HAVE_HALFOP) && defined(HAVE_CHANPROT)
	notice_help(s_ChanServ, u, CHAN_HELP_OTHERS_HALFOP_CHANPROT);
#elif defined(HAVE_HALFOP)
	notice_help(s_ChanServ, u, CHAN_HELP_OTHERS_HALFOP);
#elif defined(HAVE_CHANPROT)
	notice_help(s_ChanServ, u, CHAN_HELP_OTHERS_CHANPROT);
#else
	notice_help(s_ChanServ, u, CHAN_HELP_OTHERS);
#endif
	if (CSExpire >= 86400)
	    notice_help(s_ChanServ, u, CHAN_HELP_EXPIRES, CSExpire/86400);
	if (is_services_oper(u))
	    notice_help(s_ChanServ, u, CHAN_SERVADMIN_HELP);
    } else if (stricmp(cmd, "LEVELS DESC") == 0) {
	int i;
	notice_help(s_ChanServ, u, CHAN_HELP_LEVELS_DESC);
	if (!levelinfo_maxwidth) {
	    for (i = 0; levelinfo[i].what >= 0; i++) {
		int len = strlen(levelinfo[i].name);
		if (len > levelinfo_maxwidth)
		    levelinfo_maxwidth = len;
	    }
	}
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    notice_help(s_ChanServ, u, CHAN_HELP_LEVELS_DESC_FORMAT,
			levelinfo_maxwidth, levelinfo[i].name,
			getstring(u->ni, levelinfo[i].desc));
	}
    } else if (stricmp(cmd, "CLEAR") == 0) {
	notice_help(s_ChanServ, u, CHAN_HELP_CLEAR);
#ifdef HAVE_BANEXCEPT
	notice_help(s_ChanServ, u, CHAN_HELP_CLEAR_EXCEPTIONS);
#endif
	notice_help(s_ChanServ, u, CHAN_HELP_CLEAR_MID);
#ifdef HAVE_HALFOP
	notice_help(s_ChanServ, u, CHAN_HELP_CLEAR_HALFOPS);
#endif
	notice_help(s_ChanServ, u, CHAN_HELP_CLEAR_END);
    } else if (stricmp(cmd, "SOP") == 0) {
	notice_help(s_ChanServ, u, CHAN_HELP_SOP);
#ifdef HAVE_CHANPROT
	notice_help(s_ChanServ, u, CHAN_HELP_SOP_PROT);
#else
	notice_help(s_ChanServ, u, CHAN_HELP_SOP_NOPROT);
#endif
	notice_help(s_ChanServ, u, CHAN_HELP_SOP_END);
    } else {
	help_cmd(s_ChanServ, u, cmds, cmd);
    }
}

/*************************************************************************/

static void do_register(User *u)
{
    char *chan = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    char *desc = strtok(NULL, "");
    NickInfo *ni = u->ni;
    Channel *c;
    ChannelInfo *ci;
    struct u_chaninfolist *uc;
#ifdef USE_ENCRYPTION
    char founderpass[PASSMAX+1];
#endif

    if (readonly) {
	notice_lang(s_ChanServ, u, CHAN_REGISTER_DISABLED);
	return;
    }

    if (!desc) {
	syntax_error(s_ChanServ, u, "REGISTER", CHAN_REGISTER_SYNTAX);
    } else if (*chan == '&') {
	notice_lang(s_ChanServ, u, CHAN_REGISTER_NOT_LOCAL);
    } else if (!ni) {
	notice_lang(s_ChanServ, u, CHAN_MUST_REGISTER_NICK, s_NickServ);
    } else if (!nick_recognized(u)) {
	notice_lang(s_ChanServ, u, CHAN_MUST_IDENTIFY_NICK,
		s_NickServ, s_NickServ);

    } else if ((ci = cs_findchan(chan)) != NULL) {
	if (ci->flags & CI_VERBOTEN) {
	    log("%s: Attempt to register FORBIDden channel %s by %s!%s@%s",
			s_ChanServ, ci->name, u->nick, u->username, u->host);
	    notice_lang(s_ChanServ, u, CHAN_MAY_NOT_BE_REGISTERED, chan);
	} else if (ci->suspendinfo) {
	    log("%s: Attempt to register SUSPENDed channel %s by %s!%s@%s",
			s_ChanServ, ci->name, u->nick, u->username, u->host);
	    notice_lang(s_ChanServ, u, CHAN_ALREADY_REGISTERED, chan);
	} else {
	    notice_lang(s_ChanServ, u, CHAN_ALREADY_REGISTERED, chan);
	}

    } else if (!is_chanop(u->nick, chan)) {
	notice_lang(s_ChanServ, u, CHAN_MUST_BE_CHANOP);

    } else if (check_channel_limit(ni) >= 0) {
	int max = ni->channelmax ? ni->channelmax : MAX_CHANNELCOUNT;
	notice_lang(s_ChanServ, u,
		ni->channelcount > max ? CHAN_EXCEEDED_CHANNEL_LIMIT
				       : CHAN_REACHED_CHANNEL_LIMIT, max);

    } else if (!(c = findchan(chan))) {
	log("%s: Channel %s not found for REGISTER", s_ChanServ, chan);
	notice_lang(s_ChanServ, u, CHAN_REGISTRATION_FAILED);

    } else if (!(ci = makechan(chan))) {
	log("%s: makechan() failed for REGISTER %s", s_ChanServ, chan);
	notice_lang(s_ChanServ, u, CHAN_REGISTRATION_FAILED);

#ifdef USE_ENCRYPTION
    } else if (strscpy(founderpass, pass, PASSMAX+1),
               encrypt_in_place(founderpass, PASSMAX) < 0) {
	log("%s: Couldn't encrypt password for %s (REGISTER)",
		s_ChanServ, chan);
	notice_lang(s_ChanServ, u, CHAN_REGISTRATION_FAILED);
	delchan(ci);
#endif

    } else {
	c->ci = ci;
	ci->c = c;
	ci->flags = CI_KEEPTOPIC | CI_SECURE;
	ci->mlock_on = CMODE_n | CMODE_t;
	ci->memos.memomax = MSMaxMemos;
	ci->last_used = ci->time_registered;
	ci->founder = u->real_ni;
#ifdef USE_ENCRYPTION
	if (strlen(pass) > PASSMAX)
	    notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX);
	memset(pass, 0, strlen(pass));
	memcpy(ci->founderpass, founderpass, PASSMAX);
	ci->flags |= CI_ENCRYPTEDPW;
#else
	if (strlen(pass) > PASSMAX-1) /* -1 for null byte */
	    notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
	strscpy(ci->founderpass, pass, PASSMAX);
#endif
	ci->desc = sstrdup(desc);
	if (c->topic) {
	    ci->last_topic = sstrdup(c->topic);
	    strscpy(ci->last_topic_setter, c->topic_setter, NICKMAX);
	    ci->last_topic_time = c->topic_time;
	}
	count_chan(ci);
	log("%s: Channel %s registered by %s!%s@%s", s_ChanServ, chan,
		u->nick, u->username, u->host);
	notice_lang(s_ChanServ, u, CHAN_REGISTERED, chan, u->nick);
#ifndef USE_ENCRYPTION
	notice_lang(s_ChanServ, u, CHAN_PASSWORD_IS, ci->founderpass);
#endif
	uc = smalloc(sizeof(*uc));
	uc->next = u->founder_chans;
	uc->prev = NULL;
	if (u->founder_chans)
	    u->founder_chans->prev = uc;
	u->founder_chans = uc;
	uc->chan = ci;
	/* Implement new mode lock */
	check_modes(ci->name);

    }
}

/*************************************************************************/

static void do_identify(User *u)
{
    char *chan = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    ChannelInfo *ci;
    struct u_chaninfolist *uc;

    if (!pass) {
	syntax_error(s_ChanServ, u, "IDENTIFY", CHAN_IDENTIFY_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (ci->suspendinfo) {
	notice_lang(s_ChanServ, u, CHAN_X_SUSPENDED, chan);
    } else {
	int res = check_password(pass, ci->founderpass);
	if (res == 1) {
	    ci->bad_passwords = 0;
	    ci->last_used = time(NULL);
	    if (!is_identified(u, ci)) {
		uc = smalloc(sizeof(*uc));
		uc->next = u->founder_chans;
		uc->prev = NULL;
		if (u->founder_chans)
		    u->founder_chans->prev = uc;
		u->founder_chans = uc;
		uc->chan = ci;
		log("%s: %s!%s@%s identified for %s", s_ChanServ,
			u->nick, u->username, u->host, ci->name);
	    }
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_SUCCEEDED, chan);
	} else if (res < 0) {
	    log("%s: check_password failed for %s", s_ChanServ, ci->name);
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_FAILED);
	} else {
	    log("%s: Failed IDENTIFY for %s by %s!%s@%s",
			s_ChanServ, ci->name, u->nick, u->username, u->host);
	    chan_bad_password(u, ci);
	}

    }
}

/*************************************************************************/

static void do_drop(User *u)
{
    char *chan = strtok(NULL, " ");
    ChannelInfo *ci;
    int is_servadmin = is_services_admin(u);
    Channel *c;

    if (readonly && !is_servadmin) {
	notice_lang(s_ChanServ, u, CHAN_DROP_DISABLED);
	return;
    }

    if (!chan) {
	syntax_error(s_ChanServ, u, "DROP", CHAN_DROP_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (!is_servadmin && (ci->flags & CI_VERBOTEN)) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!is_servadmin && !is_identified(u, ci)) {
	notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED, s_ChanServ, chan);
    } else {
	if (readonly)  /* in this case we know they're a Services admin */
	    notice_lang(s_ChanServ, u, READ_ONLY_MODE);
	log("%s: Channel %s dropped by %s!%s@%s", s_ChanServ, ci->name,
			u->nick, u->username, u->host);
	delchan(ci);
	if (CMODE_REG && (c = findchan(chan))) {
	    c->mode &= ~CMODE_REG;
	    send_cmd(s_ChanServ, "MODE %s -%s", chan,
		     mode_flags_to_string(CMODE_REG, MODE_CHANNEL));
	}
	notice_lang(s_ChanServ, u, CHAN_DROPPED, chan);
    }
}

/*************************************************************************/

/* Main SET routine.  Calls other routines as follows:
 *	do_set_command(User *command_sender, ChannelInfo *ci, char *param);
 * The parameter passed is the first space-delimited parameter after the
 * option name, except in the case of DESC, TOPIC, and ENTRYMSG, in which
 * it is the entire remainder of the line.  Additional parameters beyond
 * the first passed in the function call can be retrieved using
 * strtok(NULL, toks).
 *
 * do_set_boolean, the default handler, is an exception to this in that it
 * also takes the ChanOpt structure for the selected option as a parameter.
 */

static void do_set(User *u)
{
    char *chan = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    char *param;
    ChannelInfo *ci;
    int is_servadmin = is_services_admin(u);

    if (readonly) {
	notice_lang(s_ChanServ, u, CHAN_SET_DISABLED);
	return;
    }

    if (cmd) {
	if (stricmp(cmd, "DESC") == 0 || stricmp(cmd, "TOPIC") == 0
	 || stricmp(cmd, "ENTRYMSG") == 0)
	    param = strtok(NULL, "");
	else
	    param = strtok(NULL, " ");
    } else {
	param = NULL;
    }

    if (!param) {
	syntax_error(s_ChanServ, u, "SET", CHAN_SET_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!is_servadmin && !check_access(u, ci, CA_SET)) {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);
    } else if (stricmp(cmd, "FOUNDER") == 0) {
	if (!is_servadmin && !is_founder(u, ci)) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED,s_ChanServ,chan);
	} else {
	    do_set_founder(u, ci, param);
	}
    } else if (stricmp(cmd, "SUCCESSOR") == 0) {
	if (!is_servadmin && !is_founder(u, ci)) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED,s_ChanServ,chan);
	} else {
	    do_set_successor(u, ci, param);
	}
    } else if (stricmp(cmd, "PASSWORD") == 0) {
	if (!is_servadmin && !is_founder(u, ci)) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED,s_ChanServ,chan);
	} else {
	    do_set_password(u, ci, param);
	}
	} else if (stricmp(cmd, "FLOODSERV") == 0) {
	if (!is_servadmin && !is_founder(u, ci)) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED,s_ChanServ,chan);
	} else {
	    do_set_floodserv(u, ci, param);
	}
    } else if (stricmp(cmd, "DESC") == 0) {
	do_set_desc(u, ci, param);
    } else if (stricmp(cmd, "URL") == 0) {
	do_set_url(u, ci, param);
    } else if (stricmp(cmd, "EMAIL") == 0) {
	do_set_email(u, ci, param);
    } else if (stricmp(cmd, "ENTRYMSG") == 0) {
	do_set_entrymsg(u, ci, param);
    } else if (stricmp(cmd, "TOPIC") == 0) {
	do_set_topic(u, ci, param);
    } else if (stricmp(cmd, "MLOCK") == 0) {
	do_set_mlock(u, ci, param);
    } else {
	ChanOpt *co = chanopt_from_name(cmd);
	if (co && co->flag == CI_NOEXPIRE && !is_servadmin)
	    co = NULL;
	if (co) {
	    do_set_boolean(u, ci, co, param);
	} else {
	    notice_lang(s_ChanServ, u, CHAN_SET_UNKNOWN_OPTION, strupper(cmd));
	    notice_lang(s_ChanServ, u, MORE_INFO, s_ChanServ, "SET");
	}
    }
}

/*************************************************************************/

static void do_unset(User *u)
{
    char *chan = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    ChannelInfo *ci;
    int is_servadmin = is_services_admin(u);

    if (readonly) {
	notice_lang(s_ChanServ, u, CHAN_SET_DISABLED);
	return;
    }

    if (!cmd) {
	syntax_error(s_ChanServ, u, "UNSET", CHAN_UNSET_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!is_servadmin && !check_access(u, ci, CA_SET)) {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);
    } else if (stricmp(cmd, "SUCCESSOR") == 0) {
	if (!is_servadmin && !is_founder(u, ci)) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED,s_ChanServ,chan);
	} else {
	    do_set_successor(u, ci, NULL);
	}
    } else if (stricmp(cmd, "URL") == 0) {
	do_set_url(u, ci, NULL);
    } else if (stricmp(cmd, "EMAIL") == 0) {
	do_set_email(u, ci, NULL);
    } else if (stricmp(cmd, "ENTRYMSG") == 0) {
	do_set_entrymsg(u, ci, NULL);
    } else {
	syntax_error(s_ChanServ, u, "UNSET", CHAN_UNSET_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_founder(User *u, ChannelInfo *ci, char *param)
{
    NickInfo *ni = findnick(param);

    if (!ni) {
	notice_lang(s_ChanServ, u, NICK_X_NOT_REGISTERED, param);
	return;
    } else if (ni->status & NS_VERBOTEN) {
	notice_lang(s_ChanServ, u, NICK_X_FORBIDDEN, param);
	return;
    }
    if ((ni->channelcount >= ni->channelmax && !is_services_admin(u))
     || ni->channelcount >= MAX_CHANNELCOUNT
    ) {
	notice_lang(s_ChanServ, u, CHAN_SET_FOUNDER_TOO_MANY_CHANS, param);
	return;
    }
	if (is_services_admin(u) && !is_founder(u, ci)) {
	wallops(s_OperServ, "\2%s\2 used SET FOUNDER as Services Admin on channel \2%s\2. New Founder: \2%s\2", u->nick, ci->name, param);
	}
    uncount_chan(ci);
    ci->founder = ni;
    count_chan(ci);
    if (ci->successor == ci->founder)
	ci->successor = NULL;
    log("%s: Changing founder of %s to %s by %s!%s@%s", s_ChanServ,
		ci->name, param, u->nick, u->username, u->host);
    notice_lang(s_ChanServ, u, CHAN_FOUNDER_CHANGED, ci->name, param);
}

/*************************************************************************/

static void do_set_successor(User *u, ChannelInfo *ci, char *param)
{
    NickInfo *ni;

    if (param) {
	ni = findnick(param);
	if (!ni) {
	    notice_lang(s_ChanServ, u, NICK_X_NOT_REGISTERED, param);
	    return;
	} else if (ni->status & NS_VERBOTEN) {
	    notice_lang(s_ChanServ, u, NICK_X_FORBIDDEN, param);
	    return;
	} else if (ni == ci->founder) {
	    notice_lang(s_ChanServ, u, CHAN_SUCCESSOR_IS_FOUNDER);
	    return;
	}
    } else {
	ni = NULL;
    }
    ci->successor = ni;
    if (ni)
	notice_lang(s_ChanServ, u, CHAN_SUCCESSOR_CHANGED, ci->name, param);
    else
	notice_lang(s_ChanServ, u, CHAN_SUCCESSOR_UNSET, ci->name);
}

/*************************************************************************/

static void do_set_password(User *u, ChannelInfo *ci, char *param)
{
#ifdef USE_ENCRYPTION
    int len = strlen(param);
    int len2 = len;
    if (len2 > PASSMAX) {
	len2 = PASSMAX;
	param[len2] = 0;
	notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX);
    }
    if (encrypt(param, len2, ci->founderpass, PASSMAX) < 0) {
	memset(param, 0, len);
	log("%s: Failed to encrypt password for %s (set)",
	    s_ChanServ, ci->name);
	notice_lang(s_ChanServ, u, CHAN_SET_PASSWORD_FAILED);
	return;
    }
    memset(param, 0, len);
    notice_lang(s_ChanServ, u, CHAN_PASSWORD_CHANGED, ci->name);
#else /* !USE_ENCRYPTION */
    if (strlen(param) > PASSMAX-1) /* -1 for null byte */
	notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
    strscpy(ci->founderpass, param, PASSMAX);
    notice_lang(s_ChanServ, u, CHAN_PASSWORD_CHANGED_TO,
		ci->name, ci->founderpass);
#endif /* USE_ENCRYPTION */
    if (get_access(u, ci) < ACCLEV_FOUNDER) {
	log("%s: %s!%s@%s set password as Services admin for %s",
		s_ChanServ, u->nick, u->username, u->host, ci->name);
	if (WallSetpass)
	    wallops(s_ChanServ, "\2%s\2 set password as Services admin for "
				"channel \2%s\2", u->nick, ci->name);
    }
}

/*************************************************************************/
// added by jabea
static void do_set_floodserv(User *u, ChannelInfo *ci, char *param)
{
    if (ci->name) {
		if (stricmp(param, "ON") == 0) {
			fs_add_chan(u, ci->name);
			send_cmd(s_FloodServ, "NOTICE %s :\2FloodServ\2 is now activated for %s", u->nick, ci->name);
		} else if (stricmp(param, "OFF") == 0) {
			fs_del_chan(u, ci->name);
			send_cmd(s_FloodServ, "NOTICE %s :\2FloodServ\2 is now deactivated for %s", u->nick, ci->name);
		}
	}
}

/*************************************************************************/

static void do_set_desc(User *u, ChannelInfo *ci, char *param)
{
    if (ci->desc)
	free(ci->desc);
    ci->desc = sstrdup(param);
    notice_lang(s_ChanServ, u, CHAN_DESC_CHANGED, ci->name, param);
}

/*************************************************************************/

static void do_set_url(User *u, ChannelInfo *ci, char *param)
{
    if (ci->url)
	free(ci->url);
    if (param) {
	if (!valid_url(param)) {
	    ci->url = NULL;
	    notice_lang(s_ChanServ, u, BAD_URL);
	} else {
	    ci->url = sstrdup(param);
	    notice_lang(s_ChanServ, u, CHAN_URL_CHANGED, ci->name, param);
	}
    } else {
	ci->url = NULL;
	notice_lang(s_ChanServ, u, CHAN_URL_UNSET, ci->name);
    }
}

/*************************************************************************/

static void do_set_email(User *u, ChannelInfo *ci, char *param)
{
    if (ci->email)
	free(ci->email);
    if (param) {
	if (!valid_email(param)) {
	    ci->email = NULL;
	    notice_lang(s_ChanServ, u, BAD_EMAIL);
	} else {
	    ci->email = sstrdup(param);
	    notice_lang(s_ChanServ, u, CHAN_EMAIL_CHANGED, ci->name, param);
	}
    } else {
	ci->email = NULL;
	notice_lang(s_ChanServ, u, CHAN_EMAIL_UNSET, ci->name);
    }
}

/*************************************************************************/

static void do_set_entrymsg(User *u, ChannelInfo *ci, char *param)
{
    if (ci->entry_message)
	free(ci->entry_message);
    if (param) {
	ci->entry_message = sstrdup(param);
	notice_lang(s_ChanServ, u, CHAN_ENTRY_MSG_CHANGED, ci->name, param);
    } else {
	ci->entry_message = NULL;
	notice_lang(s_ChanServ, u, CHAN_ENTRY_MSG_UNSET, ci->name);
    }
}

/*************************************************************************/

static void do_set_topic(User *u, ChannelInfo *ci, char *param)
{
    Channel *c = ci->c;
    time_t now = time(NULL);

    if (!c) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, ci->name);
	return;
    }
    set_topic(c, param, u->nick, now);
    record_topic(c);
}

/*************************************************************************/

static void do_set_mlock(User *u, ChannelInfo *ci, char *param)
{
    char *s, modebuf[32], *end, c;
    int add = -1;	/* 1 if adding, 0 if deleting, -1 if neither */
    int32 newlock_on = 0, newlock_off = 0, newlock_limit = 0;
    char *newlock_key = NULL;

    while (*param) {
	if (*param != '+' && *param != '-' && add < 0) {
	    param++;
	    continue;
	}
	switch ((c = *param++)) {
	  case '+':
	    add = 1;
	    break;
	  case '-':
	    add = 0;
	    break;
	  case 'k':
	    if (add) {
		if (!(s = strtok(NULL, " "))) {
		    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_KEY_REQUIRED);
		    return;
		}
		if (newlock_key)
		    free(newlock_key);
		newlock_key = sstrdup(s);
		newlock_off &= ~CMODE_k;
	    } else {
		if (newlock_key) {
		    free(newlock_key);
		    newlock_key = NULL;
		}
		newlock_off |= CMODE_k;
	    }
	    break;
	  case 'l':
	    if (add) {
		if (!(s = strtok(NULL, " "))) {
		    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_LIMIT_REQUIRED);
		    return;
		}
		if (atol(s) <= 0) {
		    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_LIMIT_POSITIVE);
		    return;
		}
		newlock_limit = atol(s);
		newlock_off &= ~CMODE_l;
	    } else {
		newlock_limit = 0;
		newlock_off |= CMODE_l;
	    }
	    break;
#ifdef IRC_UNREAL
	  case 'f':
	    if (add) {
		notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_MODE_F_BAD);
		break;
	    }
	    /* fall through to default */
#endif
	  default: {
	    int32 flag = mode_char_to_flag(c, MODE_CHANNEL);
#ifdef IRC_UNREAL
	    if ((flag & (CMODE_A | CMODE_H))
		&& !(is_services_admin(u)
		     || (u->mode & (UMODE_A|UMODE_N|UMODE_T)))
	    ) {
		continue;
	    }
#endif
	    if ((flag & CMODE_OPERONLY) && !is_oper_u(u))
		continue;
	    if (flag) {
		if (flag & CMODE_REG)
		    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_MODE_REG_BAD, c);
		else if (add)
		    newlock_on |= flag, newlock_off &= ~flag;
		else
		    newlock_off |= flag, newlock_on &= ~flag;
	    } else {
		notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_UNKNOWN_CHAR, c);
	    }
	    break;
	  } /* default case */
	} /* switch */
    } /* while (*param) */

    /* Now that everything's okay, actually set the new mode lock. */
    ci->mlock_on = newlock_on;
    ci->mlock_off = newlock_off;
    ci->mlock_limit = newlock_limit;
    if (ci->mlock_key)
	free(ci->mlock_key);
    ci->mlock_key = newlock_key;

    /* Tell the user about it. */
    end = modebuf;
    *end = 0;
    if (ci->mlock_on || ci->mlock_key || ci->mlock_limit)
	end += snprintf(end, sizeof(modebuf)-(end-modebuf), "+%s%s%s",
			mode_flags_to_string(ci->mlock_on, MODE_CHANNEL),
			(ci->mlock_key  ) ? "k" : "",
			(ci->mlock_limit) ? "l" : "");
    if (ci->mlock_off)
	end += snprintf(end, sizeof(modebuf)-(end-modebuf), "-%s",
			mode_flags_to_string(ci->mlock_off, MODE_CHANNEL));
    if (*modebuf) {
	notice_lang(s_ChanServ, u, CHAN_MLOCK_CHANGED, ci->name, modebuf);
    } else {
	notice_lang(s_ChanServ, u, CHAN_MLOCK_REMOVED, ci->name);
    }

    /* Implement the new lock. */
    check_modes(ci->name);
}

/*************************************************************************/

static void do_set_boolean(User *u, ChannelInfo *ci, ChanOpt *co, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= co->flag;
	if (co->flag == CI_RESTRICTED && ci->levels[CA_NOJOIN] < 0)
	    ci->levels[CA_NOJOIN] = 0;
	notice_lang(s_ChanServ, u, co->onstr, ci->name);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~co->flag;
	if (co->flag == CI_RESTRICTED && ci->levels[CA_NOJOIN] >= 0)
	    ci->levels[CA_NOJOIN] = -1;
	notice_lang(s_ChanServ, u, co->offstr, ci->name);
    } else {
	char buf[BUFSIZE];
	snprintf(buf, sizeof(buf), "SET %s", co->name);
	syntax_error(s_ChanServ, u, buf, co->syntaxstr);
    }
}

/*************************************************************************/

#include "cs-access.c"

/*************************************************************************/

/* `last' is set to the last index this routine was called with */
static int akick_del(User *u, AutoKick *akick)
{
    if (!akick->in_use)
	return 0;
    if (akick->is_nick) {
	akick->u.ni = NULL;
    } else {
	free(akick->u.mask);
	akick->u.mask = NULL;
    }
    if (akick->reason) {
	free(akick->reason);
	akick->reason = NULL;
    }
    akick->in_use = akick->is_nick = 0;
    return 1;
}

static int akick_del_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *last = va_arg(args, int *);
    if (num < 1 || num > ci->akickcount)
	return 0;
    *last = num;
    return akick_del(u, &ci->akick[num-1]);
}


static int akick_list(User *u, int index, ChannelInfo *ci, int *sent_header,
		      int is_view)
{
    AutoKick *akick = &ci->akick[index];
    char buf[BUFSIZE], buf2[BUFSIZE];

    if (!akick->in_use)
	return 0;
    if (!*sent_header) {
	notice_lang(s_ChanServ, u, CHAN_AKICK_LIST_HEADER, ci->name);
	*sent_header = 1;
    }
    if (akick->is_nick) {
	if (akick->u.ni->flags & NI_HIDE_MASK)
	    strscpy(buf, akick->u.ni->nick, sizeof(buf));
	else
	    snprintf(buf, sizeof(buf), "%s (%s)",
			akick->u.ni->nick, akick->u.ni->last_usermask);
    } else {
	strscpy(buf, akick->u.mask, sizeof(buf));
    }
    if (akick->reason)
	snprintf(buf2, sizeof(buf2), " (%s)", akick->reason);
    else
	*buf2 = 0;
    if (is_view)
	notice_lang(s_ChanServ, u, CHAN_AKICK_VIEW_FORMAT,
		    index+1, buf, akick->who[0] ? akick->who : "<unknown>",
		    buf2);
    else
	notice_lang(s_ChanServ, u, CHAN_AKICK_LIST_FORMAT, index+1, buf, buf2);
    return 1;
}

static int akick_list_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *sent_header = va_arg(args, int *);
    int is_view = va_arg(args, int);
    if (num < 1 || num > ci->akickcount)
	return 0;
    return akick_list(u, num-1, ci, sent_header, is_view);
}

static void do_akick(User *u)
{
    char *chan   = strtok(NULL, " ");
    char *cmd    = strtok(NULL, " ");
    char *mask   = strtok(NULL, " ");
    char *reason = strtok(NULL, "");
    ChannelInfo *ci;
    int i;
    AutoKick *akick;

    if (!cmd || (!mask &&
		(stricmp(cmd, "ADD") == 0 || stricmp(cmd, "DEL") == 0))) {
	syntax_error(s_ChanServ, u, "AKICK", CHAN_AKICK_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!check_access(u, ci, CA_AKICK) && !is_services_admin(u)) {
	if (ci->founder && getlink(ci->founder) == u->ni)
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED, s_ChanServ,
			chan);
	else
	    notice_lang(s_ChanServ, u, ACCESS_DENIED);

    } else if (stricmp(cmd, "ADD") == 0) {

	NickInfo *ni = findnick(mask);
	char *nick, *user, *host;

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_AKICK_DISABLED);
	    return;
	}

	if (!ni) {
	    split_usermask(mask, &nick, &user, &host);
	    mask = smalloc(strlen(nick)+strlen(user)+strlen(host)+3);
	    sprintf(mask, "%s!%s@%s", nick, user, host);
	    free(nick);
	    free(user);
	    free(host);
	} else if (ni->status & NS_VERBOTEN) {
	    notice_lang(s_ChanServ, u, NICK_X_FORBIDDEN, mask);
	    return;
	}

	for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
	    if (!akick->in_use)
		continue;
	    if (akick->is_nick ? akick->u.ni == ni
	                       : stricmp(akick->u.mask,mask) == 0) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_ALREADY_EXISTS,
			akick->is_nick ? akick->u.ni->nick : akick->u.mask,
			chan);
		return;
	    }
	}

	for (i = 0; i < ci->akickcount; i++) {
	    if (!ci->akick[i].in_use)
		break;
	}
	if (i == ci->akickcount) {
	    if (ci->akickcount >= CSAutokickMax) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_REACHED_LIMIT,
			CSAutokickMax);
		return;
	    }
	    ci->akickcount++;
	    ci->akick = srealloc(ci->akick, sizeof(AutoKick) * ci->akickcount);
	}
	akick = &ci->akick[i];
	akick->in_use = 1;
	if (ni) {
	    akick->is_nick = 1;
	    akick->u.ni = ni;
	} else {
	    akick->is_nick = 0;
	    akick->u.mask = mask;
	}
	if (reason)
	    akick->reason = sstrdup(reason);
	else
	    akick->reason = NULL;
	strscpy(akick->who, u->nick, NICKMAX);
	notice_lang(s_ChanServ, u, CHAN_AKICK_ADDED, mask, chan);

    } else if (stricmp(cmd, "DEL") == 0) {

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_AKICK_DISABLED);
	    return;
	}

	/* Special case: is it a number/list?  Only do search if it isn't. */
	if (isdigit(*mask) && strspn(mask, "1234567890,-") == strlen(mask)) {
	    int count, deleted, last = -1;
	    deleted = process_numlist(mask, &count, akick_del_callback, u,
					ci, &last);
	    if (!deleted) {
		if (count == 1) {
		    notice_lang(s_ChanServ, u, CHAN_AKICK_NO_SUCH_ENTRY,
				last, ci->name);
		} else {
		    notice_lang(s_ChanServ, u, CHAN_AKICK_NO_MATCH, ci->name);
		}
	    } else if (deleted == 1) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_DELETED_ONE, ci->name);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_AKICK_DELETED_SEVERAL,
				deleted, ci->name);
	    }
	} else {
	    NickInfo *ni = findnick(mask);  /* don't worry if this is NULL */

	    for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
		if (!akick->in_use)
		    continue;
		if ((akick->is_nick && akick->u.ni == ni)
		 || (!akick->is_nick && stricmp(akick->u.mask, mask) == 0))
		    break;
	    }
	    if (i == ci->akickcount) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_NOT_FOUND, mask, chan);
		return;
	    }
	    notice_lang(s_ChanServ, u, CHAN_AKICK_DELETED, mask, chan);
	    akick_del(u, akick);
	}

    } else if (stricmp(cmd, "LIST") == 0 || stricmp(cmd, "VIEW") == 0) {
	int is_view = stricmp(cmd,"VIEW")==0;
	int sent_header = 0;

	if (ci->akickcount == 0) {
	    notice_lang(s_ChanServ, u, CHAN_AKICK_LIST_EMPTY, chan);
	    return;
	}
	if (mask && isdigit(*mask) &&
			strspn(mask, "1234567890,-") == strlen(mask)) {
	    process_numlist(mask, NULL, akick_list_callback, u, ci,
			    &sent_header, is_view);
	} else {
	    for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
		if (!akick->in_use)
		    continue;
		if (mask) {
		    if (!akick->is_nick
		     && !match_wild_nocase(mask, akick->u.mask))
			continue;
		    if (akick->is_nick
		     && !match_wild_nocase(mask, akick->u.ni->nick))
			continue;
		}
		akick_list(u, i, ci, &sent_header, is_view);
	    }
	}
	if (!sent_header)
	    notice_lang(s_ChanServ, u, CHAN_AKICK_NO_MATCH, chan);

    } else if (stricmp(cmd, "ENFORCE") == 0) {
	Channel *c = findchan(ci->name);
	struct c_userlist *cu = NULL;
	struct c_userlist *next;
	char *argv[3];
	int count = 0;

	if (!c) {
	    notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, ci->name);
	    return;
	}

	cu = c->users;
	while (cu) {
	    next = cu->next;
	    if (check_kick(cu->user, c->name)) {
		/* check_kick() will do the actual kick, but will not
		 * remove the user from the channel's user list */
		argv[0] = c->name;
		argv[1] = cu->user->nick;
		argv[2] = CSAutokickReason;
		do_kick(s_ChanServ, 3, argv);
		count++;
	    }
	    cu = next;
	}

	notice_lang(s_ChanServ, u, CHAN_AKICK_ENFORCE_DONE, chan, count);

    } else if (stricmp(cmd, "COUNT") == 0) {
	int count = 0, i;
	for (i = 0; i < ci->akickcount; i++) {
	    if (ci->akick[i].in_use)
		count++;
	}
        notice_lang(s_ChanServ, u, CHAN_AKICK_COUNT, ci->name, count);

    } else {
	syntax_error(s_ChanServ, u, "AKICK", CHAN_AKICK_SYNTAX);
    }
}

/*************************************************************************/

static void do_levels(User *u)
{
    char *chan = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    char *what = strtok(NULL, " ");
    char *s    = strtok(NULL, " ");
    ChannelInfo *ci;
    short level;
    int i;

    /* If SET, we want two extra parameters; if DIS[ABLE], we want only
     * one; else, we want none.
     */
    if (!cmd || ((stricmp(cmd,"SET")==0) ? !s :
			(strnicmp(cmd,"DIS",3)==0) ? (!what || s) : !!what)) {
	syntax_error(s_ChanServ, u, "LEVELS", CHAN_LEVELS_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!is_founder(u, ci) && !is_services_admin(u)) {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);

    } else if (stricmp(cmd, "SET") == 0) {
	level = atoi(s);
	if (level <= ACCLEV_INVALID || level >= ACCLEV_FOUNDER) {
	    notice_lang(s_ChanServ, u, CHAN_LEVELS_RANGE,
			ACCLEV_INVALID+1, ACCLEV_FOUNDER-1);
	    return;
	}
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    if (stricmp(levelinfo[i].name, what) == 0) {
		ci->levels[levelinfo[i].what] = level;
		notice_lang(s_ChanServ, u, CHAN_LEVELS_CHANGED,
			levelinfo[i].name, chan, level);
		return;
	    }
	}
	notice_lang(s_ChanServ, u, CHAN_LEVELS_UNKNOWN, what, s_ChanServ);

    } else if (stricmp(cmd, "DIS") == 0 || stricmp(cmd, "DISABLE") == 0) {
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    if (stricmp(levelinfo[i].name, what) == 0) {
		ci->levels[levelinfo[i].what] = ACCLEV_INVALID;
		notice_lang(s_ChanServ, u, CHAN_LEVELS_DISABLED,
			levelinfo[i].name, chan);
		return;
	    }
	}
	notice_lang(s_ChanServ, u, CHAN_LEVELS_UNKNOWN, what, s_ChanServ);

    } else if (stricmp(cmd, "LIST") == 0) {
	int i;
	notice_lang(s_ChanServ, u, CHAN_LEVELS_LIST_HEADER, chan);
	if (!levelinfo_maxwidth) {
	    for (i = 0; levelinfo[i].what >= 0; i++) {
		int len = strlen(levelinfo[i].name);
		if (len > levelinfo_maxwidth)
		    levelinfo_maxwidth = len;
	    }
	}
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    int j = ci->levels[levelinfo[i].what];
	    if (j == ACCLEV_INVALID)
		notice_lang(s_ChanServ, u, CHAN_LEVELS_LIST_DISABLED,
			    levelinfo_maxwidth, levelinfo[i].name);
	    else
		notice_lang(s_ChanServ, u, CHAN_LEVELS_LIST_NORMAL,
			    levelinfo_maxwidth, levelinfo[i].name, j);
	}

    } else if (stricmp(cmd, "RESET") == 0) {
	reset_levels(ci);
	notice_lang(s_ChanServ, u, CHAN_LEVELS_RESET, chan);

    } else {
	syntax_error(s_ChanServ, u, "LEVELS", CHAN_LEVELS_SYNTAX);
    }
}

/*************************************************************************/

/* SADMINS, and users who have identified for a channel, can now cause its
 * entry message and successor to be displayed by supplying the ALL
 * parameter.
 * Syntax: INFO channel [ALL]
 * -TheShadow (29 Mar 1999)
 */

/* Check the status of show_all and make a note of having done so.  See
 * comments at nickserv.c/do_info() for details. */
#define CHECK_SHOW_ALL (used_all++, show_all)

static void do_info(User *u)
{
    char *chan = strtok(NULL, " ");
    char *param = strtok(NULL, " ");
    ChannelInfo *ci;
    NickInfo *ni;
    char buf[BUFSIZE], *end, *s;
    struct tm *tm;
    int is_servadmin = is_services_admin(u);
    int can_show_all = 0, show_all = 0, used_all = 0;

    if (!chan) {
        syntax_error(s_ChanServ, u, "INFO", CHAN_INFO_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
        notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
        notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!ci->founder) {
        /* Paranoia... this shouldn't be able to happen */
        delchan(ci);
        notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else {

        /* Only show all the channel's settings to sadmins and founders. */
	can_show_all = (is_identified(u, ci) || is_servadmin);

        if ((param && stricmp(param, "ALL") == 0) && can_show_all)
            show_all = 1;

        notice_lang(s_ChanServ, u, CHAN_INFO_HEADER, chan);
        ni = ci->founder;
        if (ni->last_usermask && (is_servadmin || !(ni->flags & NI_HIDE_MASK)))
        {
            notice_lang(s_ChanServ, u, CHAN_INFO_FOUNDER, ni->nick,
                        ni->last_usermask);
        } else {
            notice_lang(s_ChanServ, u, CHAN_INFO_NO_FOUNDER, ni->nick);
        }

	if ((ni = ci->successor) != NULL && CHECK_SHOW_ALL) {
	    if (ni->last_usermask && (is_servadmin ||
						!(ni->flags & NI_HIDE_MASK))) {
		notice_lang(s_ChanServ, u, CHAN_INFO_SUCCESSOR, ni->nick,
			    ni->last_usermask);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_INFO_NO_SUCCESSOR, ni->nick);
	    }
	}

	notice_lang(s_ChanServ, u, CHAN_INFO_DESCRIPTION, ci->desc);
	tm = localtime(&ci->time_registered);
	strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
	notice_lang(s_ChanServ, u, CHAN_INFO_TIME_REGGED, buf);
	tm = localtime(&ci->last_used);
	strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
	notice_lang(s_ChanServ, u, CHAN_INFO_LAST_USED, buf);

	/* Do not show last_topic if channel is mlock'ed +s or +p, or if the
	 * channel's current modes include +s or +p. -TheShadow */
	if (ci->last_topic && !(ci->mlock_on & (CMODE_s | CMODE_p))) {
	    if (!ci->c || !(ci->c->mode & (CMODE_s | CMODE_p))) {
		notice_lang(s_ChanServ, u, CHAN_INFO_LAST_TOPIC,
			    ci->last_topic);
		notice_lang(s_ChanServ, u, CHAN_INFO_TOPIC_SET_BY,
			    ci->last_topic_setter);
	    }
	}

	if (ci->entry_message && CHECK_SHOW_ALL)
	    notice_lang(s_ChanServ, u, CHAN_INFO_ENTRYMSG, ci->entry_message);
	if (ci->url)
	    notice_lang(s_ChanServ, u, CHAN_INFO_URL, ci->url);
	if (ci->email)
	    notice_lang(s_ChanServ, u, CHAN_INFO_EMAIL, ci->email);
	s = chanopts_to_string(ci, u->ni);
	notice_lang(s_ChanServ, u, CHAN_INFO_OPTIONS,
		    *s ? s : getstring(u->ni, CHAN_INFO_OPT_NONE));
	end = buf;
	*end = 0;
	if (ci->mlock_on || ci->mlock_key || ci->mlock_limit)
	    end += snprintf(end, sizeof(buf)-(end-buf), "+%s%s%s",
			    mode_flags_to_string(ci->mlock_on, MODE_CHANNEL),
			    (ci->mlock_key  ) ? "k" : "",
			    (ci->mlock_limit) ? "l" : "");
	if (ci->mlock_off)
	    end += snprintf(end, sizeof(buf)-(end-buf), "-%s",
			    mode_flags_to_string(ci->mlock_off, MODE_CHANNEL));
	if (*buf)
	    notice_lang(s_ChanServ, u, CHAN_INFO_MODE_LOCK, buf);

        if ((ci->flags & CI_NOEXPIRE) && CHECK_SHOW_ALL)
	    notice_lang(s_ChanServ, u, CHAN_INFO_NO_EXPIRE);

	if (ci->suspendinfo) {
	    notice_lang(s_ChanServ, u, CHAN_X_SUSPENDED, chan);
	    if (CHECK_SHOW_ALL) {
		SuspendInfo *si = ci->suspendinfo;
		char timebuf[BUFSIZE], expirebuf[BUFSIZE];

		tm = localtime(&si->suspended);
		strftime_lang(timebuf, sizeof(timebuf), u,
			      STRFTIME_DATE_TIME_FORMAT, tm);
		expires_in_lang(expirebuf, sizeof(expirebuf), u->ni,
				si->expires);
		notice_lang(s_ChanServ, u, CHAN_INFO_SUSPEND_DETAILS,
			    si->who, timebuf, expirebuf);
		notice_lang(s_ChanServ, u, CHAN_INFO_SUSPEND_REASON,
			    si->reason);
	    }
	}

	if (can_show_all && !show_all && used_all)
	    notice_lang(s_ChanServ, u, CHAN_INFO_SHOW_ALL, s_ChanServ,
			ci->name);

    }
}

/*************************************************************************/

/* SADMINS can search for channels based on their CI_VERBOTEN and
 * CI_NOEXPIRE flags and suspension status. This works in the same way as
 * NickServ's LIST command.
 * Syntax for sadmins: LIST pattern [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
 * Also fixed CI_PRIVATE channels being shown to non-sadmins.
 * -TheShadow
 */

static void do_list(User *u)
{
    char *pattern = strtok(NULL, " ");
    char *keyword;
    ChannelInfo *ci;
    int nchans;
    char buf[BUFSIZE];
    int is_servadmin = is_services_admin(u);
    int32 matchflags = 0; /* CI_ flags a chan must match one of to qualify */
    int match_susp = 0;	/* nonzero to match suspended channels */


    if (CSListOpersOnly && (!u || !is_oper_u(u))) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	return;
    }

    if (!pattern) {
	syntax_error(s_ChanServ, u, "LIST",
		is_servadmin ? CHAN_LIST_SERVADMIN_SYNTAX : CHAN_LIST_SYNTAX);
    } else {
	nchans = 0;

	while (is_servadmin && (keyword = strtok(NULL, " "))) {
	    if (stricmp(keyword, "FORBIDDEN") == 0)
		matchflags |= CI_VERBOTEN;
	    if (stricmp(keyword, "NOEXPIRE") == 0)
		matchflags |= CI_NOEXPIRE;
	    if (stricmp(keyword, "SUSPENDED") == 0)
		match_susp = 1;
	}

	notice_lang(s_ChanServ, u, CHAN_LIST_HEADER, pattern);
	for (ci = cs_firstchan(); ci; ci = cs_nextchan()) {
	    if (!is_servadmin && (ci->flags & (CI_PRIVATE | CI_VERBOTEN)))
		continue;
	    if (matchflags || match_susp) {
		if (!((ci->flags & matchflags) || (ci->suspendinfo && match_susp)))
		    continue;
	    }

	    snprintf(buf, sizeof(buf), "%-20s  %s", ci->name,
		     ci->desc ? ci->desc : "");
	    if (irc_stricmp(pattern, ci->name) == 0 || match_wild_nocase(pattern, buf)) {
		if (++nchans <= CSListMax) {
		    char noexpire_char = ' ', suspended_char = ' ';
		    if (is_servadmin) {
			if (ci->flags & CI_NOEXPIRE)
			    noexpire_char = '!';
			if (ci->suspendinfo)
			    noexpire_char = '*';
		    }

		    /* This can only be true for SADMINS - normal users
		     * will never get this far with a VERBOTEN channel.
		     * -TheShadow */
		    if (ci->flags & CI_VERBOTEN) {
			snprintf(buf, sizeof(buf), "%-20s  [Forbidden]",
				 ci->name);
		    }

		    notice(s_ChanServ, u->nick, "  %c%c%s",
			   suspended_char, noexpire_char, buf);
		}
	    }
	}
	notice_lang(s_ChanServ, u, CHAN_LIST_END,
			nchans>CSListMax ? CSListMax : nchans, nchans);
    }

}

/*************************************************************************/

static void do_invite(User *u)
{
    char *chan = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;

    if (!chan) {
	syntax_error(s_ChanServ, u, "INVITE", CHAN_INVITE_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_ChanServ, u, CHAN_BOUNCY_MODES, "INVITE");
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_INVITE)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else {
	send_cmd(s_ChanServ, "INVITE %s %s", u->nick, chan);
	notice_lang(s_ChanServ, u, CHAN_INVITE_OK, u->nick, chan);
    }
}

/*************************************************************************/

/* Internal routine to handle all op/voice-type requests. */

static struct {
    const char *cmd;
    int add;
    int32 mode;
    int sender_acc;	/* Access required for the sender */
    int target_acc;	/* Target access level at which we refuse command */
    int target_nextacc;	/* Level above target_acc (voice -> halfop etc) */
    int success_msg, failure_msg;
} opvoice_data[] = {
    { "OP",        1, CUMODE_o, CA_OPDEOP, CA_AUTODEOP, -1,
	  CHAN_OP_SUCCEEDED, CHAN_OP_FAILED },
    { "DEOP",      0, CUMODE_o, CA_OPDEOP, CA_AUTOOP, -1,
	  CHAN_DEOP_SUCCEEDED, CHAN_DEOP_FAILED },
    { "VOICE",     1, CUMODE_v, CA_VOICE, -1, -1,
	  CHAN_VOICE_SUCCEEDED, CHAN_VOICE_FAILED },
#ifndef HAVE_HALFOP
    { "DEVOICE",   0, CUMODE_v, CA_VOICE, CA_AUTOVOICE, CA_AUTOOP,
	  CHAN_DEVOICE_SUCCEEDED, CHAN_DEVOICE_FAILED },
#else
    { "DEVOICE",   0, CUMODE_v, CA_VOICE, CA_AUTOVOICE, CA_AUTOHALFOP,
	  CHAN_DEVOICE_SUCCEEDED, CHAN_DEVOICE_FAILED },
    { "HALFOP",    1, CUMODE_h, CA_HALFOP, CA_AUTODEOP, -1,
	  CHAN_HALFOP_SUCCEEDED, CHAN_HALFOP_FAILED },
    { "DEHALFOP",  0, CUMODE_h, CA_HALFOP, CA_AUTOHALFOP, CA_AUTOOP,
	  CHAN_DEHALFOP_SUCCEEDED, CHAN_DEHALFOP_FAILED },
#endif
#ifdef HAVE_CHANPROT
    { "PROTECT",   1, CUMODE_a, CA_PROTECT, -1, -1,
	  CHAN_PROTECT_SUCCEEDED, CHAN_PROTECT_FAILED },
    { "DEPROTECT", 0, CUMODE_a, CA_PROTECT, -1, -1,
	  CHAN_DEPROTECT_SUCCEEDED, CHAN_DEPROTECT_FAILED },
#endif
};

static void do_opvoice(User *u, const char *cmd)
{
    char *chan = strtok(NULL, " ");
    char *target = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;
    User *target_user;
    int i;
    int add, sender_acc, target_acc, target_nextacc, success_msg, failure_msg;
    int32 mode;

    for (i = 0; strcmp(opvoice_data[i].cmd, cmd) != 0; i++)
	;
    add            = opvoice_data[i].add;
    mode           = opvoice_data[i].mode;
    sender_acc     = opvoice_data[i].sender_acc;
    target_acc     = opvoice_data[i].target_acc;
    target_nextacc = opvoice_data[i].target_nextacc;
    success_msg    = opvoice_data[i].success_msg;
    failure_msg    = opvoice_data[i].failure_msg;

    if (!chan || !target) {
	char buf[BUFSIZE];
	snprintf(buf, sizeof(buf), getstring(u->ni, CHAN_OPVOICE_SYNTAX), cmd);
	notice_lang(s_ChanServ, u, SYNTAX_ERROR, buf);
	notice_lang(s_ChanServ, u, MORE_INFO, s_ChanServ, cmd);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_ChanServ, u, CHAN_BOUNCY_MODES, cmd);
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, sender_acc)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else if (!(target_user = finduser(target))) {
	notice_lang(s_ChanServ, u, NICK_X_NOT_IN_USE, target);
    } else if (target_user != u && !(!add && !(ci->flags & CI_ENFORCE))
	               /* Allow changing own mode; allow deops if !ENFORCE */
	       && target_acc >= 0 && check_access(target_user, ci, target_acc)
	               /* Disallow if user is at/above disallow level... */
	       && (target_nextacc < 0
		   || !check_access(target_user, ci, target_nextacc))
	               /* ... and below level-above-disallow-level (if any) */
    ) {
	notice_lang(s_ChanServ, u, failure_msg, target, chan);
    } else {
	char *av[3];
	char modebuf[3];
        struct u_chanlist *c;

        for (c = target_user->chans; c; c = c->next) {
            if (irc_stricmp(chan, c->chan->name) == 0)
                break;
        }
        if (!c) {
	    notice_lang(s_ChanServ, u, NICK_X_NOT_ON_CHAN_X, target, chan);
            return;
	}

	modebuf[0] = add ? '+' : '-';
	modebuf[1] = mode_flag_to_char(mode, MODE_CHANUSER);
	modebuf[2] = 0;
	send_cmode(MODE_SENDER(s_ChanServ), chan, modebuf, target);
	av[0] = chan;
	av[1] = modebuf;
	av[2] = target;
	do_cmode(s_ChanServ, 3, av);
	if (ci->flags & CI_OPNOTICE) {
	    notice(s_ChanServ, chan, "%s command used for %s by %s",
		   cmd, target, u->nick);
	}
	notice_lang(s_ChanServ, u, success_msg, target, chan);
	/* If it was an OP command, update the last-used time */
	if (strcmp(cmd, "OP") == 0)
	    ci->last_used = time(NULL);
    }
}

static void do_op(User *u)
{
    do_opvoice(u, "OP");
}

static void do_deop(User *u)
{
    do_opvoice(u, "DEOP");
}

static void do_voice(User *u)
{
    do_opvoice(u, "VOICE");
}

static void do_devoice(User *u)
{
    do_opvoice(u, "DEVOICE");
}

#ifdef HAVE_HALFOP
static void do_halfop(User *u)
{
    do_opvoice(u, "HALFOP");
}

static void do_dehalfop(User *u)
{
    do_opvoice(u, "DEHALFOP");
}
#endif  /* HAVE_HALFOP */

#ifdef HAVE_CHANPROT
static void do_protect(User *u)
{
    do_opvoice(u, "PROTECT");
}

static void do_deprotect(User *u)
{
    do_opvoice(u, "DEPROTECT");
}
#endif  /* HAVE_CHANPROT */

/*************************************************************************/

static void do_unban(User *u)
{
    char *chan = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;

    if (!chan) {
	syntax_error(s_ChanServ, u, "UNBAN", CHAN_UNBAN_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_ChanServ, u, CHAN_BOUNCY_MODES, "UNBAN");
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_UNBAN)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else {
#ifdef IRC_BAHAMUT
	/* SVSMODE does this for us (note that we can't do it ourselves
	 * because Bahamut servers apply IP-address bans to hostnames, and
	 * we don't have the user's IP address) */
	send_cmd(s_ChanServ, "SVSMODE %s -b %s", chan, u->nick);
#else
	clear_channel(c, CLEAR_BANS, u);
#endif /* IRC_BAHAMUT */
	notice_lang(s_ChanServ, u, CHAN_UNBANNED, chan);
    }
}

/*************************************************************************/

static void do_clear(User *u)
{
    char *chan = strtok(NULL, " ");
    char *what = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;

    if (!what) {
	syntax_error(s_ChanServ, u, "CLEAR", CHAN_CLEAR_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_ChanServ, u, CHAN_BOUNCY_MODES, "CLEAR");
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_CLEAR)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else if (stricmp(what, "BANS") == 0) {
	clear_channel(c, CLEAR_BANS, NULL);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_BANS, chan);
#ifdef HAVE_BANEXCEPT
    } else if (stricmp(what, "EXCEPTIONS") == 0) {
	clear_channel(c, CLEAR_EXCEPTS, NULL);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_EXCEPTIONS, chan);
#endif
    } else if (stricmp(what, "MODES") == 0) {
	clear_channel(c, CLEAR_MODES, NULL);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_MODES, chan);
    } else if (stricmp(what, "OPS") == 0) {
	clear_channel(c, CLEAR_UMODES, (void *)CUMODE_o);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_OPS, chan);
#ifdef HAVE_HALFOP
    } else if (stricmp(what, "HALFOPS") == 0) {
	clear_channel(c, CLEAR_UMODES, (void *)CUMODE_h);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_HALFOPS, chan);
#endif
    } else if (stricmp(what, "VOICES") == 0) {
	clear_channel(c, CLEAR_UMODES, (void *)CUMODE_v);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_VOICES, chan);
    } else if (stricmp(what, "USERS") == 0) {
	char buf[BUFSIZE];
	snprintf(buf, sizeof(buf), "CLEAR USERS command from %s", u->nick);
	clear_channel(c, CLEAR_USERS, buf);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_USERS, chan);
    } else {
	syntax_error(s_ChanServ, u, "CLEAR", CHAN_CLEAR_SYNTAX);
    }
}

/*************************************************************************/

/* Assumes that permission checking has already been done. */

static void do_getpass(User *u)
{
#ifdef USE_ENCRYPTION
    notice_lang(s_ChanServ, u, CHAN_GETPASS_UNAVAILABLE);
#else
    char *chan = strtok(NULL, " ");
    ChannelInfo *ci;

    if (!chan) {
	syntax_error(s_ChanServ, u, "GETPASS", CHAN_GETPASS_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else {
	log("%s: %s!%s@%s used GETPASS on %s",
		s_ChanServ, u->nick, u->username, u->host, ci->name);
	if (WallGetpass) {
	    wallops(s_ChanServ, "\2%s\2 used GETPASS on channel \2%s\2",
		u->nick, chan);
	}
	notice_lang(s_ChanServ, u, CHAN_GETPASS_PASSWORD_IS,
		chan, ci->founderpass);
    }
#endif
}

/*************************************************************************/

static void do_forbid(User *u)
{
    ChannelInfo *ci;
    char *chan = strtok(NULL, " ");

    /* Assumes that permission checking has already been done. */
    if (!chan || *chan != '#') {
	syntax_error(s_ChanServ, u, "FORBID", CHAN_FORBID_SYNTAX);
	return;
    }
    if (readonly)
	notice_lang(s_ChanServ, u, READ_ONLY_MODE);
    if ((ci = cs_findchan(chan)) != NULL)
	delchan(ci);
    ci = makechan(chan);
    if (ci) {
	Channel *c;
	log("%s: %s set FORBID for channel %s", s_ChanServ, u->nick,
		ci->name);
	ci->flags |= CI_VERBOTEN;
	ci->time_registered = time(NULL);
	notice_lang(s_ChanServ, u, CHAN_FORBID_SUCCEEDED, chan);
	c = findchan(chan);
	if (c)
	    clear_channel(c, CLEAR_USERS,
			  "Use of this channel has been forbidden");
    } else {
	log("%s: Valid FORBID for %s by %s failed", s_ChanServ, ci->name,
		u->nick);
	notice_lang(s_ChanServ, u, CHAN_FORBID_FAILED, chan);
    }
}

/*************************************************************************/

static void do_suspend(User *u)
{
    ChannelInfo *ci;
    char *expiry, *chan, *reason;
    time_t expires;

    chan = strtok(NULL, " ");
    if (chan && *chan == '+') {
	expiry = chan;
	chan = strtok(NULL, " ");
    } else {
	expiry = NULL;
    }
    reason = strtok(NULL, "");

    if (!reason) {
	syntax_error(s_ChanServ, u, "SUSPEND", CHAN_SUSPEND_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (ci->suspendinfo) {
	notice_lang(s_ChanServ, u, CHAN_SUSPEND_ALREADY_SUSPENDED, chan);
    } else {
	Channel *c;
	if (expiry)
	    expires = dotime(expiry);
	else
	    expires = CSSuspendExpire;
	if (expires < 0) {
	    notice_lang(s_ChanServ, u, BAD_EXPIRY_TIME);
	    return;
	} else if (expires > 0) {
	    expires += time(NULL);	/* Set an absolute time */
	}
	log("%s: %s suspended %s", s_ChanServ, u->nick, ci->name);
	suspend(ci, reason, u->nick, expires);
	notice_lang(s_ChanServ, u, CHAN_SUSPEND_SUCCEEDED, chan);
	c = findchan(chan);
	if (c)
	    clear_channel(c, CLEAR_USERS,
			  "Use of this channel has been forbidden");
	if (readonly)
	    notice_lang(s_ChanServ, u, READ_ONLY_MODE);
    }
}

/*************************************************************************/

static void do_unsuspend(User *u)
{
    ChannelInfo *ci;
    char *chan = strtok(NULL, " ");

    if (!chan) {
	syntax_error(s_ChanServ, u, "UNSUSPEND", CHAN_UNSUSPEND_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!ci->suspendinfo) {
	notice_lang(s_ChanServ, u, CHAN_SUSPEND_NOT_SUSPENDED, chan);
    } else {
	if (readonly)
	    notice_lang(s_ChanServ, u, READ_ONLY_MODE);
	log("%s: %s unsuspended %s", s_ChanServ, u->nick, ci->name);
	unsuspend(ci, 1);
	notice_lang(s_ChanServ, u, CHAN_UNSUSPEND_SUCCEEDED, chan);
    }
}

/*************************************************************************/

static void do_status(User *u)
{
    ChannelInfo *ci;
    User *u2;
    char *nick, *chan;

    chan = strtok(NULL, " ");
    nick = strtok(NULL, " ");
    if (!nick || strtok(NULL, " ")) {
	notice(s_ChanServ, u->nick, "STATUS ERROR Syntax error");
	return;
    }
    if (!(ci = cs_findchan(chan))) {
	char *temp = chan;
	chan = nick;
	nick = temp;
	ci = cs_findchan(chan);
    }
    if (!ci) {
	notice(s_ChanServ, u->nick, "STATUS ERROR Channel %s not registered",
		chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice(s_ChanServ, u->nick, "STATUS ERROR Channel %s forbidden", chan);
	return;
    } else if ((u2 = finduser(nick)) != NULL) {
	notice(s_ChanServ, u->nick, "STATUS %s %s %d",
		chan, nick, get_access(u2, ci));
    } else { /* !u2 */
	notice(s_ChanServ, u->nick, "STATUS ERROR Nick %s not online", nick);
    }
}

/*************************************************************************/

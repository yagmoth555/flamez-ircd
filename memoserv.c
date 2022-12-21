/* MemoServ functions.
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

/* Error codes for getmemoinfo(). */
#define GMI_NOTFOUND	-1
#define GMI_FORBIDDEN	-2
#define GMI_SUSPENDED	-3

/*************************************************************************/

static MemoInfo *getmemoinfo(const char *name, int *ischan, int *isverboten);
static int list_memo(User *u, int index, MemoInfo *mi, int *sent_header,
			int new, const char *chan);
static int list_memo_callback(User *u, int num, va_list args);
static int read_memo(User *u, int index, MemoInfo *mi, const char *chan);
static int read_memo_callback(User *u, int num, va_list args);
static int del_memo(MemoInfo *mi, int num);
static int del_memo_callback(User *u, int num, va_list args);

static void do_help(User *u);
static void do_send(User *u);
static void do_list(User *u);
static void do_read(User *u);
static void do_del(User *u);
static void do_set(User *u);
static void do_set_notify(User *u, MemoInfo *mi, char *param);
static void do_set_limit(User *u, MemoInfo *mi, char *param);
static void do_info(User *u);

/*************************************************************************/

static Command cmds[] = {
    { "HELP",       do_help, NULL,  -1,                      -1,-1,-1,-1 },
    { "SEND",       do_send, NULL,  MEMO_HELP_SEND,          -1,-1,-1,-1 },
    { "LIST",       do_list, NULL,  MEMO_HELP_LIST,          -1,-1,-1,-1 },
    { "READ",       do_read, NULL,  MEMO_HELP_READ,          -1,-1,-1,-1 },
    { "DEL",        do_del,  NULL,  MEMO_HELP_DEL,           -1,-1,-1,-1 },
    { "SET",        do_set,  NULL,  MEMO_HELP_SET,           -1,-1,-1,-1 },
    { "SET NOTIFY", NULL,    NULL,  MEMO_HELP_SET_NOTIFY,    -1,-1,-1,-1 },
    { "SET LIMIT",  NULL,    NULL,  -1,
    		MEMO_HELP_SET_LIMIT, MEMO_SERVADMIN_HELP_SET_LIMIT,
		MEMO_SERVADMIN_HELP_SET_LIMIT, MEMO_SERVADMIN_HELP_SET_LIMIT },
    { "INFO",       do_info, NULL,  -1,
		MEMO_HELP_INFO, MEMO_SERVADMIN_HELP_INFO,
		MEMO_SERVADMIN_HELP_INFO, MEMO_SERVADMIN_HELP_INFO },
    { NULL }
};

/*************************************************************************/
/*************************************************************************/

/* MemoServ initialization. */

void ms_init(void)
{
    Command *cmd;

    cmd = lookup_cmd(cmds, "SET LIMIT");
    if (cmd)
	cmd->help_param1 = (char *)(long)MSMaxMemos;
}

/*************************************************************************/

/* memoserv:  Main MemoServ routine.
 *            Note that the User structure passed to the do_* routines will
 *            always be valid (non-NULL) and will always have a valid
 *            NickInfo pointer in the `ni' field.
 */

void memoserv(const char *source, char *buf)
{
    char *cmd, *s;
    User *u = finduser(source);

    if (!u) {
	log("%s: user record for %s not found", s_MemoServ, source);
	notice(s_MemoServ, source,
		getstring((NickInfo *)NULL, USER_RECORD_NOT_FOUND));
	return;
    }

    cmd = strtok(buf, " ");
    if (!cmd) {
	return;
    } else if (stricmp(cmd, "\1PING") == 0) {
	if (!(s = strtok(NULL, "")))
	    s = "\1";
	notice(s_MemoServ, source, "\1PING %s", s);
    } else if (skeleton) {
	notice_lang(s_MemoServ, u, SERVICE_OFFLINE, s_MemoServ);
    } else {
	if (!u->ni && stricmp(cmd, "HELP") != 0)
	    notice_lang(s_MemoServ, u, NICK_NOT_REGISTERED_HELP, s_NickServ);
	else
	    run_cmd(s_MemoServ, u, cmds, cmd);
    }
}

/*************************************************************************/

/* Return memo stats.  Assumes pointers are valid. */

void get_memoserv_stats(long *nrec, long *memuse)
{
    long count = 0, mem = 0;
    int i;
    NickInfo *ni;
    ChannelInfo *ci;

    for (ni = firstnick(); ni; ni = nextnick()) {
	mem += ni->memos.memocount * sizeof(Memo);
	for (i = 0; i < ni->memos.memocount; i++) {
	    count++;
	    if (ni->memos.memos[i].text)
		mem += strlen(ni->memos.memos[i].text)+1;
	}
    }
    for (ci = cs_firstchan(); ci; ci = cs_nextchan()) {
	mem += ci->memos.memocount * sizeof(Memo);
	for (i = 0; i < ci->memos.memocount; i++) {
	    if (ci->memos.memos[i].text)
		mem += strlen(ci->memos.memos[i].text)+1;
	}
    }
    *nrec = count;
    *memuse = mem;
}

/*************************************************************************/

/* Compatibility memo load routine. */

#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on memo.db");		\
	failed = 1;					\
	break;						\
    }							\
} while (0)

void load_old_ms_dbase(void)
{
    dbFILE *f;
    int ver, i, j, c;
    NickInfo *ni;
    Memo *memos;
    struct memolist_ {
	struct memolist_ *next, *prev;
	char nick[NICKMAX];
	long n_memos;
	Memo *memos;
	long reserved[4];
    } old_memolist;
    struct {
	char sender[NICKMAX];
	long number;
	time_t time;
	char *text;
	short flags;
	short reserved_s;
	long reserved[3];
    } oldmemo;
    int failed = 0;

    if (!(f = open_db(s_MemoServ, "memo.db", "r")))
	return;
    switch (ver = get_file_version(f)) {
      case 4:
      case 3:
      case 2:
      case 1:
	for (i = 33; i < 256 && !failed; ++i) {
	    while ((c = getc_db(f)) != 0) {
		if (c != 1)
		    fatal("Invalid format in memo.db");
		SAFE(read_variable(old_memolist, f));
		if (debug >= 3)
		    log("debug: load_old_ms_dbase: got memolist for %s",
				old_memolist.nick);
		old_memolist.memos = memos =
				smalloc(sizeof(Memo) * old_memolist.n_memos);
		for (j = 0; j < old_memolist.n_memos; j++, memos++) {
		    SAFE(read_variable(oldmemo, f));
		    strscpy(memos->sender, oldmemo.sender, NICKMAX);
		    memos->number = oldmemo.number;
		    memos->time = oldmemo.time;
		    memos->flags = oldmemo.flags;
		}
		memos = old_memolist.memos;
		for (j = 0; j < old_memolist.n_memos; j++) {
		    if (read_string(&memos[j].text, f) < 0)
			fatal("Read error on memo.db");
		}
		ni = findnick(old_memolist.nick);
		if (ni) {
		    ni->memos.memocount = old_memolist.n_memos;
		    ni->memos.memos = old_memolist.memos;
		}
	    }
	}
	break;
      case -1:
	fatal("Unable to read version number from memo.db");
      default:
	fatal("Unsupported version number (%d) on memo.db", ver);
    } /* switch (version) */
    close_db(f);
}

/*************************************************************************/

/* check_memos:  See if the given user has any unread memos, and send a
 *               NOTICE to that user if so (and if the appropriate flag is
 *               set).
 */

void check_memos(User *u)
{
    NickInfo *ni = u->ni;
    int i, newcnt = 0;

    if (!ni || !nick_recognized(u) || !(ni->flags & NI_MEMO_SIGNON))
	return;

    for (i = 0; i < ni->memos.memocount; i++) {
	if (ni->memos.memos[i].flags & MF_UNREAD)
	    newcnt++;
    }
    if (newcnt > 0) {
	notice_lang(s_MemoServ, u,
		newcnt==1 ? MEMO_HAVE_NEW_MEMO : MEMO_HAVE_NEW_MEMOS, newcnt);
	if (newcnt == 1 && (ni->memos.memos[i-1].flags & MF_UNREAD)) {
	    notice_lang(s_MemoServ, u, MEMO_TYPE_READ_LAST, s_MemoServ);
	} else if (newcnt == 1) {
	    for (i = 0; i < ni->memos.memocount; i++) {
		if (ni->memos.memos[i].flags & MF_UNREAD)
		    break;
	    }
	    notice_lang(s_MemoServ, u, MEMO_TYPE_READ_NUM, s_MemoServ,
			ni->memos.memos[i].number);
	} else {
	    notice_lang(s_MemoServ, u, MEMO_TYPE_LIST_NEW, s_MemoServ);
	}
    }
    if (ni->memos.memomax > 0 && ni->memos.memocount >= ni->memos.memomax) {
	if (ni->memos.memocount > ni->memos.memomax)
	    notice_lang(s_MemoServ, u, MEMO_OVER_LIMIT, ni->memos.memomax);
	else
	    notice_lang(s_MemoServ, u, MEMO_AT_LIMIT, ni->memos.memomax);
    }
}

/*************************************************************************/
/*********************** MemoServ private routines ***********************/
/*************************************************************************/

/* Return the MemoInfo corresponding to the given nick or channel name.
 * Return in `ischan' 1 if the name was a channel name, else 0.
 * Return in `error' a GMI_* error code if the return value is NULL.
 * Also set `error' to GMI_SUSPENDED if the nick/channel is suspended,
 * even though a valid MemoInfo is returned.
 */

static MemoInfo *getmemoinfo(const char *name, int *ischan, int *error)
{
    if (error)
	*error = 0;

    if (*name == '#') {
	ChannelInfo *ci;
	if (ischan)
	    *ischan = 1;
	ci = cs_findchan(name);

	if (ci) {
	    if (ci->flags & CI_VERBOTEN) {
		if (error)
		    *error = GMI_FORBIDDEN;
		return NULL;
	    } else {
		if (ci->suspendinfo && error)
		    *error = GMI_SUSPENDED;
		return &ci->memos;
	    }
	} else {
	    if (error)
		*error = GMI_NOTFOUND;
	    return NULL;
	}

    } else {
	NickInfo *ni;
	if (ischan)
	    *ischan = 0;
	ni = findnick(name);
	if (ni) {
	    if (ni->status & NS_VERBOTEN) {
		if (error)
		    *error = GMI_FORBIDDEN;
		return NULL;
	    } else {
		if (ni->suspendinfo && error)
		    *error = GMI_SUSPENDED;
		return &getlink(ni)->memos;
	    }
	} else {
	    if (error)
		*error = GMI_NOTFOUND;
	    return NULL;
	}
    }
}

/*************************************************************************/

/* Display a single memo entry, possibly printing the header first. */

static int list_memo(User *u, int index, MemoInfo *mi, int *sent_header,
			int new, const char *chan)
{
    Memo *m;
    char timebuf[64];
    struct tm tm;

    if (index < 0 || index >= mi->memocount)
	return 0;
    if (!*sent_header) {
	if (chan) {
	    notice_lang(s_MemoServ, u,
			new ? MEMO_LIST_CHAN_NEW_MEMOS : MEMO_LIST_CHAN_MEMOS,
			chan, s_MemoServ, chan);
	} else {
	    notice_lang(s_MemoServ, u,
			new ? MEMO_LIST_NEW_MEMOS : MEMO_LIST_MEMOS,
			u->nick, s_MemoServ);
	}
	notice_lang(s_MemoServ, u, MEMO_LIST_HEADER);
	*sent_header = 1;
    }
    m = &mi->memos[index];
    tm = *localtime(&m->time);
    strftime_lang(timebuf, sizeof(timebuf),
		u, STRFTIME_DATE_TIME_FORMAT, &tm);
    timebuf[sizeof(timebuf)-1] = 0;	/* just in case */
    notice_lang(s_MemoServ, u, MEMO_LIST_FORMAT,
		(m->flags & MF_UNREAD) ? '*' : ' ',
		m->number, m->sender, timebuf);
    return 1;
}

/* List callback. */

static int list_memo_callback(User *u, int num, va_list args)
{
    MemoInfo *mi = va_arg(args, MemoInfo *);
    int *sent_header = va_arg(args, int *);
    const char *chan = va_arg(args, const char *);
    int i;

    for (i = 0; i < mi->memocount; i++) {
	if (mi->memos[i].number == num)
	    break;
    }
    /* Range checking done by list_memo() */
    return list_memo(u, i, mi, sent_header, 0, chan);
}

/*************************************************************************/

/* Send a single memo to the given user. */

static int read_memo(User *u, int index, MemoInfo *mi, const char *chan)
{
    Memo *m;
    char timebuf[64];
    struct tm tm;

    if (index < 0 || index >= mi->memocount)
	return 0;
    m = &mi->memos[index];
    tm = *localtime(&m->time);
    strftime_lang(timebuf, sizeof(timebuf),
		u, STRFTIME_DATE_TIME_FORMAT, &tm);
    timebuf[sizeof(timebuf)-1] = 0;
    if (chan)
	notice_lang(s_MemoServ, u, MEMO_CHAN_HEADER, m->number,
		m->sender, timebuf, s_MemoServ, chan, m->number);
    else
	notice_lang(s_MemoServ, u, MEMO_HEADER, m->number,
		m->sender, timebuf, s_MemoServ, m->number);
    notice_lang(s_MemoServ, u, MEMO_TEXT, m->text);
    m->flags &= ~MF_UNREAD;
    return 1;
}

/* List callback. */

static int read_memo_callback(User *u, int num, va_list args)
{
    MemoInfo *mi = va_arg(args, MemoInfo *);
    const char *chan = va_arg(args, const char *);
    int i;

    for (i = 0; i < mi->memocount; i++) {
	if (mi->memos[i].number == num)
	    break;
    }
    /* Range check done in read_memo */
    return read_memo(u, i, mi, chan);
}

/*************************************************************************/

/* Delete a memo by number.  Return 1 if the memo was found, else 0. */

static int del_memo(MemoInfo *mi, int num)
{
    int i;

    for (i = 0; i < mi->memocount; i++) {
	if (mi->memos[i].number == num)
	    break;
    }
    if (i < mi->memocount) {
	free(mi->memos[i].text); /* Deallocate memo text memory */
	mi->memocount--;	 /* One less memo now */
	if (i < mi->memocount)	 /* Move remaining memos down a slot */
	    memmove(mi->memos + i, mi->memos + i+1,
				sizeof(Memo) * (mi->memocount - i));
	if (mi->memocount == 0) { /* If no more memos, free array */
	    free(mi->memos);
	    mi->memos = NULL;
	}
	return 1;
    } else {
	return 0;
    }
}

/* Delete a single memo from a MemoInfo. */

static int del_memo_callback(User *u, int num, va_list args)
{
    MemoInfo *mi = va_arg(args, MemoInfo *);
    int *last = va_arg(args, int *);

    if (del_memo(mi, num)) {
	*last = num;
	return 1;
    } else {
	return 0;
    }
}

/*************************************************************************/
/*********************** MemoServ command routines ***********************/
/*************************************************************************/

/* Return a help message. */

static void do_help(User *u)
{
    char *cmd = strtok(NULL, "");

    if (!cmd) {
	notice_help(s_MemoServ, u, MEMO_HELP, s_ChanServ);
    } else {
	help_cmd(s_MemoServ, u, cmds, cmd);
    }
}

/*************************************************************************/

/* Send a memo to a nick/channel. */

static void do_send(User *u)
{
    char *source = u->nick;
    int ischan, error;
    MemoInfo *mi;
    Memo *m;
    char *name = strtok(NULL, " ");
    char *text = strtok(NULL, "");
    time_t now = time(NULL);
    int is_servadmin = is_services_admin(u);

    if (!text) {
	syntax_error(s_MemoServ, u, "SEND", MEMO_SEND_SYNTAX);

    } else if (!nick_recognized(u)) {
	notice_lang(s_MemoServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);

    } else if (!(mi = getmemoinfo(name, &ischan, &error))) {
	if (error == GMI_FORBIDDEN)
	    notice_lang(s_MemoServ, u,
		ischan ? CHAN_X_FORBIDDEN: NICK_X_FORBIDDEN,
		name);
	else
	    notice_lang(s_MemoServ, u,
		ischan ? CHAN_X_NOT_REGISTERED : NICK_X_NOT_REGISTERED, name);

    } else if (error == GMI_SUSPENDED) {
	notice_lang(s_MemoServ, u,
	    ischan ? CHAN_X_SUSPENDED_MEMOS : NICK_X_SUSPENDED_MEMOS, name);

    } else if (MSSendDelay > 0 &&
		u && u->lastmemosend+MSSendDelay > now && !is_servadmin) {
	u->lastmemosend = now;
	notice_lang(s_MemoServ, u, MEMO_SEND_PLEASE_WAIT, MSSendDelay);

    } else if (mi->memomax == 0 && !is_servadmin) {
	notice_lang(s_MemoServ, u, MEMO_X_GETS_NO_MEMOS, name);

    } else if (mi->memomax > 0 && mi->memocount >= mi->memomax
		&& !is_servadmin) {
	notice_lang(s_MemoServ, u, MEMO_X_HAS_TOO_MANY_MEMOS, name);

    } else {
	u->lastmemosend = now;
	mi->memocount++;
	mi->memos = srealloc(mi->memos, sizeof(Memo) * mi->memocount);
	m = &mi->memos[mi->memocount-1];
	strscpy(m->sender, source, NICKMAX);
	if (mi->memocount > 1) {
	    m->number = m[-1].number + 1;
	    if (m->number < 1) {
		int i;
		for (i = 0; i < mi->memocount; i++)
		    mi->memos[i].number = i+1;
	    }
	} else {
	    m->number = 1;
	}
	m->time = time(NULL);
	m->text = sstrdup(text);
	m->flags = MF_UNREAD;
	notice_lang(s_MemoServ, u, MEMO_SENT, name);
	if (!ischan) {
	    NickInfo *ni = getlink(findnick(name));  /* cannot fail */
	    if (ni->flags & NI_MEMO_RECEIVE) {
		if (MSNotifyAll) {
		    for (u = firstuser(); u; u = nextuser()) {
			if (u->ni==ni && (u->real_ni->status & NS_RECOGNIZED)){
			    notice_lang(s_MemoServ, u, MEMO_NEW_MEMO_ARRIVED,
					source, s_MemoServ, m->number);
			}
		    }
		} else {
		    u = finduser(name);
		    if (u && (u->real_ni->status & NS_RECOGNIZED)) {
			notice_lang(s_MemoServ, u, MEMO_NEW_MEMO_ARRIVED,
					source, s_MemoServ, m->number);
		    }
		} /* if (MSNotifyAll) */
	    } /* if (flags & MEMO_RECEIVE) */
	} /* if (!ischan) */
    } /* if command is valid */
}

/*************************************************************************/

/* List memos for the source nick or given channel. */

static void do_list(User *u)
{
    char *param = strtok(NULL, " "), *chan = NULL;
    ChannelInfo *ci;
    MemoInfo *mi;
    Memo *m;
    int i;

    if (param && *param == '#') {
	chan = param;
	param = strtok(NULL, " ");
	if (!(ci = cs_findchan(chan))) {
	    notice_lang(s_MemoServ, u, CHAN_X_NOT_REGISTERED, chan);
	    return;
	} else if (ci->flags & CI_VERBOTEN) {
	    notice_lang(s_MemoServ, u, CHAN_X_FORBIDDEN, chan);
	    return;
	} else if (!check_access(u, ci, CA_MEMO)) {
	    notice_lang(s_MemoServ, u, ACCESS_DENIED);
	    return;
	}
	mi = &ci->memos;
    } else {
	if (!nick_identified(u)) {
	    notice_lang(s_MemoServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);
	    return;
	}
	mi = &u->ni->memos;
    }
    if (param && !isdigit(*param) && stricmp(param, "NEW") != 0) {
	syntax_error(s_MemoServ, u, "LIST", MEMO_LIST_SYNTAX);
    } else if (mi->memocount == 0) {
	if (chan)
	    notice_lang(s_MemoServ, u, MEMO_X_HAS_NO_MEMOS, chan);
	else
	    notice_lang(s_MemoServ, u, MEMO_HAVE_NO_MEMOS);
    } else {
	int sent_header = 0;
	if (param && isdigit(*param)) {
	    process_numlist(param, NULL, list_memo_callback, u,
					mi, &sent_header, chan);
	} else {
	    if (param) {
		for (i = 0, m = mi->memos; i < mi->memocount; i++, m++) {
		    if (m->flags & MF_UNREAD)
			break;
		}
		if (i == mi->memocount) {
		    if (chan)
			notice_lang(s_MemoServ, u, MEMO_X_HAS_NO_NEW_MEMOS,
					chan);
		    else
			notice_lang(s_MemoServ, u, MEMO_HAVE_NO_NEW_MEMOS);
		    return;
		}
	    }
	    for (i = 0, m = mi->memos; i < mi->memocount; i++, m++) {
		if (param && !(m->flags & MF_UNREAD))
		    continue;
		list_memo(u, i, mi, &sent_header, param != NULL, chan);
	    }
	}
    }
}

/*************************************************************************/

/* Read memos. */

static void do_read(User *u)
{
    MemoInfo *mi;
    ChannelInfo *ci;
    char *numstr = strtok(NULL, " "), *chan = NULL;
    int num, count;

    if (numstr && *numstr == '#') {
	chan = numstr;
	numstr = strtok(NULL, " ");
	if (!(ci = cs_findchan(chan))) {
	    notice_lang(s_MemoServ, u, CHAN_X_NOT_REGISTERED, chan);
	    return;
	} else if (ci->flags & CI_VERBOTEN) {
	    notice_lang(s_MemoServ, u, CHAN_X_FORBIDDEN, chan);
	    return;
	} else if (!check_access(u, ci, CA_MEMO)) {
	    notice_lang(s_MemoServ, u, ACCESS_DENIED);
	    return;
	}
	mi = &ci->memos;
    } else {
	if (!nick_identified(u)) {
	    notice_lang(s_MemoServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);
	    return;
	}
	mi = &u->ni->memos;
    }
    num = numstr ? atoi(numstr) : -1;
    if (!numstr || (stricmp(numstr,"LAST") != 0 && stricmp(numstr,"NEW") != 0
                    && num <= 0)) {
	syntax_error(s_MemoServ, u, "READ", MEMO_READ_SYNTAX);

    } else if (mi->memocount == 0) {
	if (chan)
	    notice_lang(s_MemoServ, u, MEMO_X_HAS_NO_MEMOS, chan);
	else
	    notice_lang(s_MemoServ, u, MEMO_HAVE_NO_MEMOS);

    } else {
	int i;

	if (stricmp(numstr, "NEW") == 0) {
	    int readcount = 0;
	    for (i = 0; i < mi->memocount; i++) {
		if (mi->memos[i].flags & MF_UNREAD) {
		    read_memo(u, i, mi, chan);
		    readcount++;
		}
	    }
	    if (!readcount) {
		if (chan)
		    notice_lang(s_MemoServ, u, MEMO_X_HAS_NO_NEW_MEMOS, chan);
		else
		    notice_lang(s_MemoServ, u, MEMO_HAVE_NO_NEW_MEMOS);
	    }
	} else if (stricmp(numstr, "LAST") == 0) {
	    for (i = 0; i < mi->memocount-1; i++)
		;
	    read_memo(u, i, mi, chan);
	} else {	/* number[s] */
	    if (!process_numlist(numstr, &count, read_memo_callback, u,
								mi, chan)) {
		if (count == 1)
		    notice_lang(s_MemoServ, u, MEMO_DOES_NOT_EXIST, num);
		else
		    notice_lang(s_MemoServ, u, MEMO_LIST_NOT_FOUND, numstr);
	    }
	}

    }
}

/*************************************************************************/

/* Delete memos. */

static void do_del(User *u)
{
    MemoInfo *mi;
    ChannelInfo *ci;
    char *numstr = strtok(NULL, ""), *chan = NULL;
    int last, i;
    int delcount, count;

    if (numstr && *numstr == '#') {
	chan = strtok(numstr, " ");
	numstr = strtok(NULL, "");
	if (!(ci = cs_findchan(chan))) {
	    notice_lang(s_MemoServ, u, CHAN_X_NOT_REGISTERED, chan);
	    return;
	} else if (ci->flags & CI_VERBOTEN) {
	    notice_lang(s_MemoServ, u, CHAN_X_FORBIDDEN, chan);
	    return;
	} else if (!check_access(u, ci, CA_MEMO)) {
	    notice_lang(s_MemoServ, u, ACCESS_DENIED);
	    return;
	}
	mi = &ci->memos;
    } else {
	if (!nick_identified(u)) {
	    notice_lang(s_MemoServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);
	    return;
	}
	mi = &u->ni->memos;
    }
    if (!numstr || (!isdigit(*numstr) && stricmp(numstr, "ALL") != 0)) {
	syntax_error(s_MemoServ, u, "DEL", MEMO_DEL_SYNTAX);
    } else if (mi->memocount == 0) {
	if (chan)
	    notice_lang(s_MemoServ, u, MEMO_X_HAS_NO_MEMOS, chan);
	else
	    notice_lang(s_MemoServ, u, MEMO_HAVE_NO_MEMOS);
    } else {
	if (isdigit(*numstr)) {
	    /* Delete a specific memo or memos. */
	    delcount = process_numlist(numstr, &count, del_memo_callback,
				       u, mi, &last);
	    if (delcount) {
		/* Some memos got deleted. */
		if (delcount > 1)
		    notice_lang(s_MemoServ, u, MEMO_DELETED_SEVERAL, delcount);
		else
		    notice_lang(s_MemoServ, u, MEMO_DELETED_ONE, last);
	    } else {
		/* No memos were deleted. */
		if (count == 1)
		    notice_lang(s_MemoServ, u, MEMO_DOES_NOT_EXIST,
				atoi(numstr));
		else
		    notice_lang(s_MemoServ, u, MEMO_DELETED_NONE);
	    }
	} else {
	    /* Delete all memos. */
	    for (i = 0; i < mi->memocount; i++)
		free(mi->memos[i].text);
	    free(mi->memos);
	    mi->memos = NULL;
	    mi->memocount = 0;
	    notice_lang(s_MemoServ, u, MEMO_DELETED_ALL);
	}
    }
}

/*************************************************************************/

static void do_set(User *u)
{
    char *cmd    = strtok(NULL, " ");
    char *param  = strtok(NULL, "");
    MemoInfo *mi = &u->ni->memos;

    if (readonly) {
	notice_lang(s_MemoServ, u, MEMO_SET_DISABLED);
	return;
    }
    if (!param) {
	syntax_error(s_MemoServ, u, "SET", MEMO_SET_SYNTAX);
    } else if (!nick_identified(u)) {
	notice_lang(s_MemoServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);
	return;
    } else if (stricmp(cmd, "NOTIFY") == 0) {
	do_set_notify(u, mi, param);
    } else if (stricmp(cmd, "LIMIT") == 0) {
	do_set_limit(u, mi, param);
    } else {
	notice_lang(s_MemoServ, u, MEMO_SET_UNKNOWN_OPTION, strupper(cmd));
	notice_lang(s_MemoServ, u, MORE_INFO, s_MemoServ, "SET");
    }
}

/*************************************************************************/

static void do_set_notify(User *u, MemoInfo *mi, char *param)
{
    if (stricmp(param, "ON") == 0) {
	u->ni->flags |= NI_MEMO_SIGNON | NI_MEMO_RECEIVE;
	notice_lang(s_MemoServ, u, MEMO_SET_NOTIFY_ON, s_MemoServ);
    } else if (stricmp(param, "LOGON") == 0) {
	u->ni->flags |= NI_MEMO_SIGNON;
	u->ni->flags &= ~NI_MEMO_RECEIVE;
	notice_lang(s_MemoServ, u, MEMO_SET_NOTIFY_LOGON, s_MemoServ);
    } else if (stricmp(param, "NEW") == 0) {
	u->ni->flags &= ~NI_MEMO_SIGNON;
	u->ni->flags |= NI_MEMO_RECEIVE;
	notice_lang(s_MemoServ, u, MEMO_SET_NOTIFY_NEW, s_MemoServ);
    } else if (stricmp(param, "OFF") == 0) {
	u->ni->flags &= ~(NI_MEMO_SIGNON | NI_MEMO_RECEIVE);
	notice_lang(s_MemoServ, u, MEMO_SET_NOTIFY_OFF, s_MemoServ);
    } else {
	syntax_error(s_MemoServ, u, "SET NOTIFY", MEMO_SET_NOTIFY_SYNTAX);
    }
}

/*************************************************************************/

/* Regular user parameters: [#channel] number
 * Services admin parameters: [#channel | nick] {number | NONE} [HARD]
 */

static void do_set_limit(User *u, MemoInfo *mi, char *param)
{
    char *p1 = strtok(param, " ");
    char *p2 = strtok(NULL, " ");
    char *user = NULL, *chan = NULL;
    int32 limit;
    NickInfo *ni = u->ni;
    ChannelInfo *ci = NULL;
    int is_servadmin = is_services_admin(u);

    if (p1 && *p1 == '#') {
	chan = p1;
	p1 = p2;
	p2 = strtok(NULL, " ");
	if (!(ci = cs_findchan(chan))) {
	    notice_lang(s_MemoServ, u, CHAN_X_NOT_REGISTERED, chan);
	    return;
	} else if (ci->flags & CI_VERBOTEN) {
	    notice_lang(s_MemoServ, u, CHAN_X_FORBIDDEN, chan);
	    return;
	} else if (!is_servadmin && !check_access(u, ci, CA_MEMO)) {
	    notice_lang(s_MemoServ, u, ACCESS_DENIED);
	    return;
	}
	mi = &ci->memos;
    }
    if (is_servadmin) {
	if (p2 && stricmp(p2, "HARD") != 0 && !chan) {
	    if (!(ni = findnick(p1))) {
		notice_lang(s_MemoServ, u, NICK_X_NOT_REGISTERED, p1);
		return;
	    }
	    ni = getlink(ni);
	    user = p1;
	    mi = &ni->memos;
	    p1 = p2;
	    p2 = strtok(NULL, " ");
	} else if (!p1) {
	    syntax_error(s_MemoServ, u, "SET LIMIT",
					MEMO_SET_LIMIT_SERVADMIN_SYNTAX);
	    return;
	}
	if ((!isdigit(*p1) && stricmp(p1, "NONE") != 0) ||
			(p2 && stricmp(p2, "HARD") != 0)) {
	    syntax_error(s_MemoServ, u, "SET LIMIT",
					MEMO_SET_LIMIT_SERVADMIN_SYNTAX);
	    return;
	}
	if (chan) {
	    if (p2)
		ci->flags |= CI_MEMO_HARDMAX;
	    else
		ci->flags &= ~CI_MEMO_HARDMAX;
	} else {
	    if (p2)
		ni->flags |= NI_MEMO_HARDMAX;
	    else
		ni->flags &= ~NI_MEMO_HARDMAX;
	}
	limit = atoi(p1);
	if (limit < 0 || limit > 32767) {
	    notice_lang(s_MemoServ, u, MEMO_SET_LIMIT_OVERFLOW, 32767);
	    limit = 32767;
	}
	if (stricmp(p1, "NONE") == 0)
	    limit = -1;
    } else {
	if (!p1 || p2 || !isdigit(*p1)) {
	    syntax_error(s_MemoServ, u, "SET LIMIT", MEMO_SET_LIMIT_SYNTAX);
	    return;
	}
	if (chan && (ci->flags & CI_MEMO_HARDMAX)) {
	    notice_lang(s_MemoServ, u, MEMO_SET_LIMIT_FORBIDDEN, chan);
	    return;
	} else if (!chan && (ni->flags & NI_MEMO_HARDMAX)) {
	    notice_lang(s_MemoServ, u, MEMO_SET_YOUR_LIMIT_FORBIDDEN);
	    return;
	}
	limit = atoi(p1);
	/* The first character is a digit, but we could still go negative
	 * from overflow... watch out! */
	if (limit < 0 || (MSMaxMemos > 0 && limit > MSMaxMemos)) {
	    if (chan) {
		notice_lang(s_MemoServ, u, MEMO_SET_LIMIT_TOO_HIGH,
			chan, MSMaxMemos);
	    } else {
		notice_lang(s_MemoServ, u, MEMO_SET_YOUR_LIMIT_TOO_HIGH,
			MSMaxMemos);
	    }
	    return;
	} else if (limit > 32767) {
	    notice_lang(s_MemoServ, u, MEMO_SET_LIMIT_OVERFLOW, 32767);
	    limit = 32767;
	}
    }
    mi->memomax = limit;
    if (limit > 0) {
	if (!chan && ni == u->ni)
	    notice_lang(s_MemoServ, u, MEMO_SET_YOUR_LIMIT, limit);
	else
	    notice_lang(s_MemoServ, u, MEMO_SET_LIMIT,
			chan ? chan : user, limit);
    } else if (limit == 0) {
	if (!chan && ni == u->ni)
	    notice_lang(s_MemoServ, u, MEMO_SET_YOUR_LIMIT_ZERO);
	else
	    notice_lang(s_MemoServ, u, MEMO_SET_LIMIT_ZERO, chan ? chan : user);
    } else {
	if (!chan && ni == u->ni)
	    notice_lang(s_MemoServ, u, MEMO_UNSET_YOUR_LIMIT);
	else
	    notice_lang(s_MemoServ, u, MEMO_UNSET_LIMIT, chan ? chan : user);
    }
}

/*************************************************************************/

static void do_info(User *u)
{
    MemoInfo *mi;
    NickInfo *ni = NULL;
    ChannelInfo *ci = NULL;
    char *name = strtok(NULL, " ");
    int is_servadmin = is_services_admin(u);
    int hardmax = 0;

    if (is_servadmin && name && *name != '#') {
	ni = findnick(name);
	if (!ni) {
	    notice_lang(s_MemoServ, u, NICK_X_NOT_REGISTERED, name);
	    return;
	} else if (ni->status & NS_VERBOTEN) {
	    notice_lang(s_MemoServ, u, NICK_X_FORBIDDEN, name);
	    return;
	}
	ni = getlink(ni);
	mi = &ni->memos;
	hardmax = ni->flags & NI_MEMO_HARDMAX ? 1 : 0;
    } else if (name && *name == '#') {
	ci = cs_findchan(name);
	if (!ci) {
	    notice_lang(s_MemoServ, u, CHAN_X_NOT_REGISTERED, name);
	    return;
	} else if (ci->flags & CI_VERBOTEN) {
	    notice_lang(s_MemoServ, u, CHAN_X_FORBIDDEN, name);
	    return;
	} else if (!check_access(u, ci, CA_MEMO)) {
	    notice_lang(s_MemoServ, u, ACCESS_DENIED);
	    return;
	}
	mi = &ci->memos;
	hardmax = ci->flags & CI_MEMO_HARDMAX ? 1 : 0;
    } else { /* !name */
	if (!nick_identified(u)) {
	    notice_lang(s_MemoServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);
	    return;
	}
	ni = u->ni;
	mi = &u->ni->memos;
    }

    if (name && ni != u->ni) {
	if (!mi->memocount) {
	    notice_lang(s_MemoServ, u, MEMO_INFO_X_NO_MEMOS, name);
	} else if (mi->memocount == 1) {
	    if (mi->memos[0].flags & MF_UNREAD)
		notice_lang(s_MemoServ, u, MEMO_INFO_X_MEMO_UNREAD, name);
	    else
		notice_lang(s_MemoServ, u, MEMO_INFO_X_MEMO, name);
	} else {
	    int count = 0, i;
	    for (i = 0; i < mi->memocount; i++) {
		if (mi->memos[i].flags & MF_UNREAD)
		    count++;
	    }
	    if (count == mi->memocount)
		notice_lang(s_MemoServ, u, MEMO_INFO_X_MEMOS_ALL_UNREAD,
			name, count);
	    else if (count == 0)
		notice_lang(s_MemoServ, u, MEMO_INFO_X_MEMOS,
			name, mi->memocount);
	    else if (count == 0)
		notice_lang(s_MemoServ, u, MEMO_INFO_X_MEMOS_ONE_UNREAD,
			name, mi->memocount);
	    else
		notice_lang(s_MemoServ, u, MEMO_INFO_X_MEMOS_SOME_UNREAD,
			name, mi->memocount, count);
	}
	if (mi->memomax >= 0) {
	    if (hardmax)
		notice_lang(s_MemoServ, u, MEMO_INFO_X_HARD_LIMIT,
			name, mi->memomax);
	    else
		notice_lang(s_MemoServ, u, MEMO_INFO_X_LIMIT,
			name, mi->memomax);
	} else {
	    notice_lang(s_MemoServ, u, MEMO_INFO_X_NO_LIMIT, name);
	}
	if (ni) {	/* only nicks are notified of new memos */
	    if ((ni->flags & NI_MEMO_RECEIVE) && (ni->flags & NI_MEMO_SIGNON)){
		notice_lang(s_MemoServ, u, MEMO_INFO_X_NOTIFY_ON, name);
	    } else if (ni->flags & NI_MEMO_RECEIVE) {
		notice_lang(s_MemoServ, u, MEMO_INFO_X_NOTIFY_RECEIVE, name);
	    } else if (ni->flags & NI_MEMO_SIGNON) {
		notice_lang(s_MemoServ, u, MEMO_INFO_X_NOTIFY_SIGNON, name);
	    } else {
		notice_lang(s_MemoServ, u, MEMO_INFO_X_NOTIFY_OFF, name);
	    }
	}

    } else { /* !name || ni == u->ni */

	if (!mi->memocount) {
	    notice_lang(s_MemoServ, u, MEMO_INFO_NO_MEMOS);
	} else if (mi->memocount == 1) {
	    if (mi->memos[0].flags & MF_UNREAD)
		notice_lang(s_MemoServ, u, MEMO_INFO_MEMO_UNREAD);
	    else
		notice_lang(s_MemoServ, u, MEMO_INFO_MEMO);
	} else {
	    int count = 0, i;
	    for (i = 0; i < mi->memocount; i++) {
		if (mi->memos[i].flags & MF_UNREAD)
		    count++;
	    }
	    if (count == mi->memocount)
		notice_lang(s_MemoServ, u, MEMO_INFO_MEMOS_ALL_UNREAD, count);
	    else if (count == 0)
		notice_lang(s_MemoServ, u, MEMO_INFO_MEMOS, mi->memocount);
	    else if (count == 1)
		notice_lang(s_MemoServ, u, MEMO_INFO_MEMOS_ONE_UNREAD,
			mi->memocount);
	    else
		notice_lang(s_MemoServ, u, MEMO_INFO_MEMOS_SOME_UNREAD,
			mi->memocount, count);
	}
	if (mi->memomax == 0) {
	    if (!is_servadmin && hardmax)
		notice_lang(s_MemoServ, u, MEMO_INFO_HARD_LIMIT_ZERO);
	    else
		notice_lang(s_MemoServ, u, MEMO_INFO_LIMIT_ZERO);
	} else if (mi->memomax > 0) {
	    if (!is_servadmin && hardmax)
		notice_lang(s_MemoServ, u, MEMO_INFO_HARD_LIMIT, mi->memomax);
	    else
		notice_lang(s_MemoServ, u, MEMO_INFO_LIMIT, mi->memomax);
	} else {
	    notice_lang(s_MemoServ, u, MEMO_INFO_NO_LIMIT);
	}
	if ((ni->flags & NI_MEMO_RECEIVE) && (ni->flags & NI_MEMO_SIGNON)) {
	    notice_lang(s_MemoServ, u, MEMO_INFO_NOTIFY_ON);
	} else if (ni->flags & NI_MEMO_RECEIVE) {
	    notice_lang(s_MemoServ, u, MEMO_INFO_NOTIFY_RECEIVE);
	} else if (ni->flags & NI_MEMO_SIGNON) {
	    notice_lang(s_MemoServ, u, MEMO_INFO_NOTIFY_SIGNON);
	} else {
	    notice_lang(s_MemoServ, u, MEMO_INFO_NOTIFY_OFF);
	}

    } /* if (name && ni != u->ni) */
}

/*************************************************************************/

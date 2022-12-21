/* Session Limiting functions.
 * by Andrew Kempe (TheShadow)
 *     E-mail: <theshadow@shadowfire.org>
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef STREAMLINED	/* applies to the whole file */

#include "services.h"
#include "pseudo.h"

/*************************************************************************/

/* SESSION LIMITING
 *
 * The basic idea of session limiting is to prevent one host from having more
 * than a specified number of sessions (client connections/clones) on the
 * network at any one time. To do this we have a list of sessions and
 * exceptions. Each session structure records information about a single host,
 * including how many clients (sessions) that host has on the network. When a
 * host reaches it's session limit, no more clients from that host will be
 * allowed to connect.
 *
 * When a client connects to the network, we check to see if their host has
 * reached the default session limit per host, and thus whether it is allowed
 * any more. If it has reached the limit, we kill the connecting client; all
 * the other clients are left alone. Otherwise we simply increment the counter
 * within the session structure. When a client disconnects, we decrement the
 * counter. When the counter reaches 0, we free the session.
 *
 * Exceptions allow one to specify custom session limits for a specific host
 * or a range thereof. The first exception that the host matches is the one
 * used.
 *
 * "Session Limiting" is likely to slow down services when there are frequent
 * client connects and disconnects. The size of the exception list can also
 * play a large role in this performance decrease. It is therefore recommened
 * that you keep the number of exceptions to a minimum. A very simple hashing
 * method is currently used to store the list of sessions. I'm sure there is
 * room for improvement and optimisation of this, along with the storage of
 * exceptions. Comments and suggestions are more than welcome!
 *
 * -TheShadow (02 April 1999)
 */

/*************************************************************************/

typedef struct session_ Session;
struct session_ {
    Session *prev, *next;
    char *host;
    int count;			/* Number of clients with this host */
    int killcount;		/* Number of kills for this session */
    time_t lastkill;		/* Time of last kill */
};

typedef struct exception_ Exception;
struct exception_ {
    char *mask;			/* Hosts to which this exception applies */
    int16 limit;		/* Session limit for exception */
    char who[NICKMAX];		/* Nick of person who added the exception */
    char *reason;		/* Reason for exception's addition */
    time_t time;		/* When this exception was added */
    time_t expires;		/* Time when it expires. 0 == no expiry */
    int num;			/* Position in exception list */
};


/* I'm sure there is a better way to hash the list of hosts for which we are
 * storing session information. This should be sufficient for the mean time.
 * -TheShadow */

#define HASH(host)      (((host)[0]&31)<<5 | ((host)[1]&31))

static Session *sessionlist[1024];
static int32 nsessions = 0;

static Exception *exceptions = NULL;
static int16 nexceptions = 0;

/*************************************************************************/

static Session *findsession(const char *host);

static Exception *find_host_exception(const char *host);
static int exception_add(const char *mask, const int limit, const char *reason,
			 const char *who, const time_t expires);

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_session_stats(long *nrec, long *memuse)
{
    Session *session;
    long mem;
    int i;

    mem = sizeof(Session) * nsessions;
    for (i = 0; i < 1024; i++) {
    	for (session = sessionlist[i]; session; session = session->next) {
	    mem += strlen(session->host)+1;
	}
    }

    *nrec = nsessions;
    *memuse = mem;
}

void get_exception_stats(long *nrec, long *memuse)
{
    long mem;
    int i;

    mem = sizeof(Exception) * nexceptions;
    for (i = 0; i < nexceptions; i++) {
	mem += strlen(exceptions[i].mask)+1;
	mem += strlen(exceptions[i].reason)+1;
    }
    *nrec = nexceptions;
    *memuse = mem;
}

/*************************************************************************/
/************************* Session List Display **************************/
/*************************************************************************/

/* Syntax: SESSION LIST threshold
 *	Lists all sessions with atleast threshold clients.
 *	The threshold value must be greater than 1. This is to prevent
 * 	accidental listing of the large number of single client sessions.
 *
 * Syntax: SESSION VIEW host
 *	Displays detailed session information about the supplied host.
 */

void do_session(User *u)
{
    Session *session;
    Exception *exception;
    char *cmd = strtok(NULL, " ");
    char *param1 = strtok(NULL, " ");
    int mincount;
    int i;

    if (!LimitSessions) {
	notice_lang(s_OperServ, u, OPER_SESSION_DISABLED);
	return;
    }

    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "LIST") == 0) {
	if (!param1) {
	    syntax_error(s_OperServ, u, "SESSION", OPER_SESSION_LIST_SYNTAX);

	} else if ((mincount = atoi(param1)) <= 1) {
	    notice_lang(s_OperServ, u, OPER_SESSION_INVALID_THRESHOLD);

	} else {
	    notice_lang(s_OperServ, u, OPER_SESSION_LIST_HEADER, mincount);
	    notice_lang(s_OperServ, u, OPER_SESSION_LIST_COLHEAD);
	    for (i = 0; i < 1024; i++) {
		for (session = sessionlist[i]; session; session=session->next){
		    if (session->count >= mincount)
			notice_lang(s_OperServ, u, OPER_SESSION_LIST_FORMAT,
				    session->count, session->host);
		}
    	    }
	}
    } else if (stricmp(cmd, "VIEW") == 0) {
	if (!param1) {
	    syntax_error(s_OperServ, u, "SESSION", OPER_SESSION_VIEW_SYNTAX);
	} else {
	    session = findsession(param1);
	    if (!session) {
		notice_lang(s_OperServ, u, OPER_SESSION_NOT_FOUND, param1);
	    } else {
		exception = find_host_exception(param1);
		notice_lang(s_OperServ, u, OPER_SESSION_VIEW_FORMAT,
			    param1, session->count,
			    exception ? exception->limit : DefSessionLimit);
	    }
	}
    } else {
	syntax_error(s_OperServ, u, "SESSION", OPER_SESSION_SYNTAX);
    }
}

/*************************************************************************/
/********************* Internal Session Functions ************************/
/*************************************************************************/

static Session *findsession(const char *host)
{
    Session *session;
    int i;

    if (!host)
	return NULL;

    i = HASH(host);
    for (session = sessionlist[i]; session; session = session->next) {
	if (stricmp(host, session->host) == 0) {
	    return session;
	}
    }

    return NULL;
}

/* Attempt to add a host to the session list. If the addition of the new host
 * causes the the session limit to be exceeded, kill the connecting user.
 * Returns 1 if the host was added or 0 if the user was killed.
 */

int add_session(const char *nick, const char *host)
{
    Session *session, **list;
    Exception *exception;
    int sessionlimit = 0;
    char buf[BUFSIZE];
    time_t now = time(NULL);

	if(is_net_closed()==1) {
		exception = find_host_exception(host);
		if (!exception) {
			send_cmd(s_OperServ, "KILL %s :%s (No more connections allowed)", nick, s_OperServ);
			return 0;
		}
	}

    session = findsession(host);

    if (session) {
	exception = find_host_exception(host);
	sessionlimit = exception ? exception->limit : DefSessionLimit;

	if (sessionlimit != 0 && session->count >= sessionlimit) {
   	    if (SessionLimitExceeded)
		notice(s_OperServ, nick, SessionLimitExceeded, host);
	    if (SessionLimitDetailsLoc)
		notice(s_OperServ, nick, SessionLimitDetailsLoc);

	    if (SessionLimitAkill) {
		if (now <= session->lastkill + SessionLimitMinKillTime) {
		    session->killcount++;
		    if (session->killcount >= SessionLimitMaxKillCount) {
			snprintf(buf, sizeof(buf), "*@%s", host);
			add_akill(buf, SessionLimitAkillReason, s_OperServ,
				  now + SessionLimitAkillExpiry);
			session->killcount = 0;
		    }
		} else {
		    session->killcount = 1;
		}
		session->lastkill = now;
	    }

	    /* We don't use kill_user() because a user stucture has not yet
	     * been created. Simply kill the user. -TheShadow
	     */
	    send_cmd(s_OperServ, "KILL %s :%s (Session limit exceeded)",
		     nick, s_OperServ);
	    return 0;
	} else {
	    session->count++;
	    return 1;
	}
	/* not reached */
    }

    /* Session does not exist, so create it */
    nsessions++;
    session = scalloc(sizeof(Session), 1);
    session->host = sstrdup(host);
    list = &sessionlist[HASH(session->host)];
    session->next = *list;
    if (*list)
	(*list)->prev = session;
    *list = session;
    session->count = 1;
    session->killcount = 0;
    session->lastkill = 0;

    return 1;
}

void del_session(const char *host)
{
    Session *session;

    if (debug >= 2)
	log("debug: del_session() called");

    session = findsession(host);
    if (!session) {
	wallops(s_OperServ,
		"WARNING: Tried to delete non-existant session: \2%s", host);
	log("session: Tried to delete non-existant session: %s", host);
	return;
    }

    if (session->count > 1) {
	session->count--;
	return;
    }
    if (session->prev)
	session->prev->next = session->next;
    else
	sessionlist[HASH(session->host)] = session->next;
    if (session->next)
	session->next->prev = session->prev;
    if (debug >= 2)
	log("debug: del_session(): free session structure");
    free(session->host);
    free(session);

    nsessions--;

    if (debug >= 2)
	log("debug: del_session() done");
}


/*************************************************************************/
/********************** Internal Exception Functions *********************/
/*************************************************************************/

void expire_exceptions(void)
{
    int i;
    time_t now = time(NULL);

    for (i = 0; i < nexceptions; i++) {
	if (exceptions[i].expires == 0 || now < exceptions[i].expires)
	    continue;
	if (WallExceptionExpire)
	    wallops(s_OperServ, "Session limit exception for %s has expired.",
		    exceptions[i].mask);
	free(exceptions[i].mask);
	free(exceptions[i].reason);
	nexceptions--;
	if (i < nexceptions)
	    memmove(exceptions+i, exceptions+i+1,
		    sizeof(Exception) * (nexceptions-i));
	exceptions = srealloc(exceptions, sizeof(Exception) * nexceptions);
	i--;
    }
}

/* Find the first exception this host matches and return it. */

Exception *find_host_exception(const char *host)
{
    int i;

    for (i = 0; i < nexceptions; i++) {
	if (match_wild_nocase(exceptions[i].mask, host)) {
	    return &exceptions[i];
	}
    }

    return NULL;
}

/*************************************************************************/
/*********************** Exception Load/Save *****************************/
/*************************************************************************/

#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", ExceptionDBName);	\
	nexceptions = i;				\
	break;						\
    }							\
} while (0)

void load_exceptions()
{
    dbFILE *f;
    int i;
    int16 n;
    int16 tmp16;
    int32 tmp32;

    if (!(f = open_db(s_OperServ, ExceptionDBName, "r")))
	return;
    switch (i = get_file_version(f)) {
      case 11:
      case 10:
      case 9:
      case 8:
      case 7:
	SAFE(read_int16(&n, f));
	nexceptions = n;
	if (!nexceptions) {
	    close_db(f);
	    return;
	}
	exceptions = smalloc(sizeof(Exception) * nexceptions);
	for (i = 0; i < nexceptions; i++) {
	    SAFE(read_string(&exceptions[i].mask, f));
	    SAFE(read_int16(&tmp16, f));
	    exceptions[i].limit = tmp16;
	    SAFE(read_buffer(exceptions[i].who, f));
	    SAFE(read_string(&exceptions[i].reason, f));
	    SAFE(read_int32(&tmp32, f));
	    exceptions[i].time = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    exceptions[i].expires = tmp32;
	    exceptions[i].num = i; /* Symbolic position, never saved. */
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", ExceptionDBName);

      default:
	fatal("Unsupported version (%d) on %s", i, ExceptionDBName);
    } /* switch (ver) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_exceptions()
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    if (!(f = open_db(s_OperServ, ExceptionDBName, "w")))
	return;
    SAFE(write_int16(nexceptions, f));
    for (i = 0; i < nexceptions; i++) {
	SAFE(write_string(exceptions[i].mask, f));
	SAFE(write_int16(exceptions[i].limit, f));
	SAFE(write_buffer(exceptions[i].who, f));
	SAFE(write_string(exceptions[i].reason, f));
	SAFE(write_int32(exceptions[i].time, f));
	SAFE(write_int32(exceptions[i].expires, f));
    }
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", ExceptionDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", ExceptionDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/************************ Exception Manipulation *************************/
/*************************************************************************/

static int exception_add(const char *mask, const int limit, const char *reason,
			const char *who, const time_t expires)
{
    int i;

    /* Check if an exception already exists for this mask */
    for (i = 0; i < nexceptions; i++)
	if (stricmp(mask, exceptions[i].mask) == 0)
	    return 0;

    /* i == nexceptions as a result of loop above; use it below */
    nexceptions++;
    exceptions = srealloc(exceptions, sizeof(Exception) * nexceptions);
    exceptions[i].mask = sstrdup(mask);
    exceptions[i].limit = limit;
    exceptions[i].reason = sstrdup(reason);
    exceptions[i].time = time(NULL);
    strscpy(exceptions[i].who, who, NICKMAX);
    exceptions[i].expires = expires;
    if (i > 0)
	exceptions[i].num = exceptions[i-1].num + 1;
    else
	exceptions[i].num = 1;
    return 1;
}

/*************************************************************************/

static int exception_del(const int index)
{
    free(exceptions[index].mask);
    free(exceptions[index].reason);
    nexceptions--;
    memmove(exceptions+index, exceptions+index+1,
		sizeof(Exception) * (nexceptions-index));
    exceptions = srealloc(exceptions,
		sizeof(Exception) * nexceptions);
    return 1;
}

static int exception_del_callback(User *u, int num, va_list args)
{
    int i;
    int *last = va_arg(args, int *);

    *last = num;
    for (i = 0; i < nexceptions; i++) {
	if (num == exceptions[i].num)
	    break;
    }
    if (i < nexceptions)
	return exception_del(i);
    else
	return 0;
}

/*************************************************************************/

static int exception_list(User *u, const int index, int *sent_header, int is_view)
{
    if (!*sent_header) {
	notice_lang(s_OperServ, u, OPER_EXCEPTION_LIST_HEADER);
	if (!is_view)
	    notice_lang(s_OperServ, u, OPER_EXCEPTION_LIST_COLHEAD);
	*sent_header = 1;
    }
    if (is_view) {
	char timebuf[BUFSIZE], expirebuf[BUFSIZE];
	strftime_lang(timebuf, sizeof(timebuf), u, STRFTIME_SHORT_DATE_FORMAT,
		      localtime(&exceptions[index].time));
	expires_in_lang(expirebuf, sizeof(expirebuf), u->ni,
			exceptions[index].expires);
	notice_lang(s_OperServ, u, OPER_EXCEPTION_VIEW_FORMAT,
		    exceptions[index].num, exceptions[index].mask,
		    *exceptions[index].who ?
			    exceptions[index].who : "<unknown>",
		    timebuf, expirebuf, exceptions[index].limit,
		    exceptions[index].reason);
    } else { /* list */
	notice_lang(s_OperServ, u, OPER_EXCEPTION_LIST_FORMAT,
		    exceptions[index].num, exceptions[index].limit,
		    exceptions[index].mask);
    }
    return 1;
}

static int exception_list_callback(User *u, int num, va_list args)
{
    int *sent_header = va_arg(args, int *);
    time_t expires = va_arg(args, time_t);
    int is_view = va_arg(args, int);
    int pos;

    for (pos = 0; pos < nexceptions; pos++)
	if (exceptions[pos].num == num)
	    break;
    if (pos >= nexceptions)
	return 0;
    else if (expires == -1 || exceptions[pos].expires == expires)
	return exception_list(u, pos, sent_header, is_view);
    else
	return 0;
}

/*************************************************************************/

/* Syntax: EXCEPTION ADD [+expiry] mask limit reason
 *	Adds mask to the exception list with limit as the maximum session
 *	limit and +expiry as an optional expiry time.
 *
 * Syntax: EXCEPTION DEL mask
 *	Deletes the first exception that matches mask exactly.
 *
 * Syntax: EXCEPTION LIST [mask]
 *	Lists all exceptions or those matching mask.
 *
 * Syntax: EXCEPTION VIEW [mask]
 *	Displays detailed information about each exception or those matching
 *	mask.
 *
 * Syntax: EXCEPTION MOVE num newnum
 *	Moves the exception with number num to have number newnum.
 */

void do_exception(User *u)
{
    char *cmd = strtok(NULL, " ");
    char *mask, *reason, *expiry, *limitstr;
    time_t expires;
    int limit, i;

    if (!LimitSessions) {
	notice_lang(s_OperServ, u, OPER_EXCEPTION_DISABLED);
	return;
    }

    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	time_t t = time(NULL);

	if (nexceptions >= 32767) {
	    notice_lang(s_OperServ, u, OPER_EXCEPTION_TOO_MANY);
	    return;
	}

	mask = strtok(NULL, " ");
	if (mask && *mask == '+') {
	    expiry = mask;
	    mask = strtok(NULL, " ");
	} else {
	    expiry = NULL;
	}
	limitstr = strtok(NULL, " ");
	reason = strtok(NULL, "");

	if (!reason) {
	    syntax_error(s_OperServ, u, "EXCEPTION", OPER_EXCEPTION_ADD_SYNTAX);
	    return;
	}

	expires = expiry ? dotime(expiry) : ExceptionExpiry;
	if (expires < 0) {
	    notice_lang(s_OperServ, u, BAD_EXPIRY_TIME);
	    return;
	} else if (expires > 0) {
	    expires += t;
	}

	limit = (limitstr && isdigit(*limitstr)) ? atoi(limitstr) : -1;

	if (limit < 0 || limit > MaxSessionLimit) {
	    notice_lang(s_OperServ, u, OPER_EXCEPTION_INVALID_LIMIT,
				MaxSessionLimit);
	    return;

	} else {
	    if (strchr(mask, '!') || strchr(mask, '@')) {
		notice_lang(s_OperServ, u, OPER_EXCEPTION_INVALID_HOSTMASK);
		return;
	    } else {
		strlower(mask);
	    }
	    if (exception_add(mask, limit, reason, u->nick, expires)) {
	    	notice_lang(s_OperServ, u, OPER_EXCEPTION_ADDED, mask, limit);
		if (WallOSException) {
		    char buf[128];
		    expires_in_lang(buf, sizeof(buf), NULL, expires);
		    wallops(s_OperServ, "%s added a session limit exception "
			    "of \2%d\2 for \2%s\2 (%s)",
			    u->nick, limit, mask, buf);
		}
	    } else {
		notice_lang(s_OperServ, u, OPER_EXCEPTION_ALREADY_PRESENT,
			    mask, limit);
	    }
	    if (readonly)
		notice_lang(s_OperServ, u, READ_ONLY_MODE);
	}

    } else if (stricmp(cmd, "DEL") == 0) {
	int deleted = 0;

	mask = strtok(NULL, " ");
	if (!mask) {
	    syntax_error(s_OperServ, u, "EXCEPTION", OPER_EXCEPTION_DEL_SYNTAX);
	    return;
	}
	if (isdigit(*mask) && strspn(mask, "1234567890,-") == strlen(mask)) {
	    int count, last = -1;
	    deleted = process_numlist(mask, &count, exception_del_callback, u,
				&last);
	    if (deleted == 0) {
		if (count == 1) {
		    notice_lang(s_OperServ, u, OPER_EXCEPTION_NO_SUCH_ENTRY,
				last);
		} else {
		    notice_lang(s_OperServ, u, OPER_EXCEPTION_NO_MATCH);
		}
	    } else if (deleted == 1) {
		notice_lang(s_OperServ, u, OPER_EXCEPTION_DELETED_ONE);
	    } else {
		notice_lang(s_OperServ, u, OPER_EXCEPTION_DELETED_SEVERAL,
				deleted);
	    }
	} else {
	    for (i = 0; i < nexceptions; i++) {
		if (stricmp(mask, exceptions[i].mask) == 0) {
		    exception_del(i);
		    notice_lang(s_OperServ, u, OPER_EXCEPTION_DELETED, mask);
		    deleted = 1;
		    break;
		}
	    }
	    if (deleted == 0)
		notice_lang(s_OperServ, u, OPER_EXCEPTION_NOT_FOUND, mask);
	}
	if (deleted && readonly)
	    notice_lang(s_OperServ, u, READ_ONLY_MODE);

	/* Renumber the exception list. I don't believe in having holes in
	 * lists - it makes code more complex, harder to debug and we end up
	 * with huge index numbers. Imho, fixed numbering is only beneficial
	 * when one doesn't have range capable manipulation. -TheShadow */

	/* That works fine up until two people do deletes at the same time
	 * and shoot themselves in the collective foot; and just because
	 * you have range handling doesn't mean someone won't do "DEL 5"
	 * followed by "DEL 7" and, again, shoot themselves in the foot.
	 * Besides, there's nothing wrong with complexity if it serves a
	 * purpose.  Removed. --AC */

    } else if (stricmp(cmd, "MOVE") == 0) {
	char *n1str = strtok(NULL, " ");	/* From index */
	char *n2str = strtok(NULL, " ");	/* To index */
	int n1, n2, n3, p1, p2, p3;

	if (!n2str) {
	    syntax_error(s_OperServ, u, "EXCEPTION",
			 OPER_EXCEPTION_MOVE_SYNTAX);
	    return;
	}
	n1 = atoi(n1str) - 1;
	n2 = atoi(n2str) - 1;
	if (n1 == n2) {
	    syntax_error(s_OperServ, u, "EXCEPTION",
			 OPER_EXCEPTION_MOVE_SYNTAX);
	    return;
	}
	p1 = -1;
	p2 = nexceptions;
	for (i = 0; i < nexceptions; i++) {
	    if (exceptions[i].num == n1)
		p1 = i;
	    else if (exceptions[i].num == n2)
		p2 = i;
	}
	if (p1 < 0) {
	    notice_lang(s_OperServ, u, OPER_EXCEPTION_NO_SUCH_ENTRY, n1);
	    return;
	}

	/* Bump numbers up if necessary */
	if (p1 < p2)
	    p3 = nexceptions;
	else
	    p3 = p1;	/* note if p1==p2 then p3==p1 and loop will not run */
	for (i = p2, n3 = n2; i < p3 && exceptions[i].num == n3; i++, n3++)
	    exceptions[i].num++;

	/* Actually move the entry */
	if (p1 != p2 && p1 != p2-1) {
	    Exception tmp;
	    memcpy(&tmp, &exceptions[p1], sizeof(Exception));
	    if (p1 < p2-1) {
		/* Shift upwards */
	    	memmove(&exceptions[p1], &exceptions[p1+1],
			sizeof(Exception) * ((p2-1)-p1));
	    	memcpy(&exceptions[p2-1], &tmp, sizeof(Exception));
	    } else {
		/* Shift downwards */
	    	memmove(&exceptions[p2+1], &exceptions[p2],
			sizeof(Exception) * (p1-p2));
	    	memcpy(&exceptions[p2], &tmp, sizeof(Exception));
	    }
	}
	notice_lang(s_OperServ, u, OPER_EXCEPTION_MOVED,
		    exceptions[n1].mask, n1, n2);
	if (readonly)
	    notice_lang(s_OperServ, u, READ_ONLY_MODE);

    } else if (stricmp(cmd, "LIST") == 0 || stricmp(cmd, "VIEW") == 0) {
	int sent_header = 0;
	int is_view = (stricmp(cmd, "VIEW") == 0);

	expire_exceptions();
	expires = -1;	/* Do not match on expiry time */

	mask = strtok(NULL, " ");
	if (mask)
	    strlower(mask);

	expiry = strtok(NULL, " ");
	/* This is a little longwinded for what it acheives - but we can
	 * expand it later to allow for user defined expiry times. */
	if (expiry && stricmp(expiry, "NOEXPIRE") == 0)
	    expires = 0;    /* Exceptions that never expire */

	if (mask && strspn(mask, "1234567890,-") == strlen(mask)) {
	    process_numlist(mask, NULL, exception_list_callback, u,
			    &sent_header, expires, is_view);
	} else {
	    for (i = 0; i < nexceptions; i++) {
		if ((!mask || match_wild(mask, exceptions[i].mask)) &&
			    (expires == -1 || exceptions[i].expires==expires))
		    exception_list(u, i, &sent_header, is_view);
	    }
	}
	if (!sent_header)
	    notice_lang(s_OperServ, u, OPER_EXCEPTION_NO_MATCH);

    } else {
	syntax_error(s_OperServ, u, "EXCEPTION", OPER_EXCEPTION_SYNTAX);
    }
}

/*************************************************************************/

#endif	/* !STREAMLINED */

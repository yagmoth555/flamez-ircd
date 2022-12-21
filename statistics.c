/* Statistics generation functions.
 * by Andrew Kempe (TheShadow)
 *     E-mail: <theshadow@shadowfire.org>
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "pseudo.h"

#ifdef STATISTICS

/*************************************************************************/

static ServerStats *serverstatslist;
static int16 nservers = 0;	/* Number of servers in Server list */

static int16 servercnt = 0;	/* Number of online servers */

/*************************************************************************/

static void do_help(User *u);
static void do_servers(User *u);
static void do_users(User *u);
#if 0
static void do_map(User *u);
#endif

/*************************************************************************/

static Command cmds[] = {
    { "HELP",        do_help,     NULL,  -1,                   -1,-1,-1,-1 },
    { "SERVERS",     do_servers,  NULL,  -1, STAT_HELP_SERVERS,
    		STAT_SERVROOT_HELP_SERVERS,
		STAT_SERVROOT_HELP_SERVERS,
		STAT_SERVROOT_HELP_SERVERS },
    { "USERS",       do_users,    NULL,  STAT_HELP_USERS,      -1,-1,-1,-1 },
#if 0
    { "MAP",	     do_map,	  NULL,  -1,		       -1,-1,-1,-1 },
#endif
    { NULL }
};

/*************************************************************************/

static ServerStats *new_serverstats(const char *servername);
static void delete_serverstats(ServerStats *server);

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

/* Return a help message. */

static void do_help(User *u)
{
    char *cmd = strtok(NULL, "");

    if (!cmd) {
	notice_help(s_StatServ, u, STAT_HELP, s_StatServ);
    } else {
	help_cmd(s_StatServ, u, cmds, cmd);
    }
}

/* Main StatServ routine. */

void statserv(const char *source, char *buf)
{
    char *cmd;
    char *s;
    User *u = finduser(source);

    if (!u) {
        log("%s: user record for %s not found", s_StatServ, source);
        notice(s_StatServ, source,
                getstring((NickInfo *)NULL, USER_RECORD_NOT_FOUND));
        return;
    }

    cmd = strtok(buf, " ");
    if (!cmd) {
        return;
    } else if (stricmp(cmd, "\1PING") == 0) {
        if (!(s = strtok(NULL, "")))
            s = "\1";
        notice(s_StatServ, source, "\1PING %s", s);
    } else {
        run_cmd(s_StatServ, u, cmds, cmd);
    }
}

/*************************************************************************/

/* Return information on memory use. Assumes pointers are valid. */

void get_statserv_stats(long *nrec, long *memuse)
{
    ServerStats *serverstats;
    long mem;

    mem = sizeof(ServerStats) * nservers;
    for (serverstats = serverstatslist; serverstats;
	 serverstats = serverstats->next
    ) {
	mem += strlen(serverstats->name)+1;
	if (serverstats->quit_message)
	    mem += strlen(serverstats->quit_message)+1;
    }

    *nrec = nservers;
    *memuse = mem;
}

/*************************************************************************/
/************************* Server Info Display ***************************/
/*************************************************************************/

void do_servers(User *u)
{
    ServerStats *serverstats;
    char *cmd = strtok(NULL, " ");
    char *mask = strtok(NULL, " ");
    struct tm *tm;
    int count = 0;

    if (!cmd)
        cmd = "";

    if (stricmp(cmd, "STATS") == 0) {
	ServerStats *serverstats_lastquit = NULL;
	int onlinecount = 0;
	char lastquit_buf[512];

	for (serverstats = serverstatslist; serverstats;
	     serverstats = serverstats->next
	) {
	    if (serverstats->t_quit > 0
		&& (!serverstats_lastquit
		    || serverstats->t_quit > serverstats_lastquit->t_quit))
		serverstats_lastquit = serverstats;
	    if (serverstats->t_join > serverstats->t_quit)
		onlinecount++;
	}

	notice_lang(s_StatServ, u, STAT_SERVERS_STATS_TOTAL, nservers);
	notice_lang(s_StatServ, u, STAT_SERVERS_STATS_ON_OFFLINE,
		    onlinecount, (onlinecount*100)/nservers,
		    nservers-onlinecount,
		    ((nservers-onlinecount)*100)/nservers);
	if (serverstats_lastquit) {
	    tm = localtime(&serverstats_lastquit->t_quit);
	    strftime_lang(lastquit_buf, sizeof(lastquit_buf), u,
			  STRFTIME_DATE_TIME_FORMAT, tm);
	    notice_lang(s_StatServ, u, STAT_SERVERS_LASTQUIT_WAS,
			serverstats_lastquit->name, lastquit_buf);
	}


    } else if (stricmp(cmd, "LIST") == 0) {
	int matchcount = 0;

	notice_lang(s_StatServ, u, STAT_SERVERS_LIST_HEADER);
	for (serverstats = serverstatslist; serverstats;
	     serverstats = serverstats->next
	) {
	    if (mask && !match_wild_nocase(mask, serverstats->name))
		continue;
	    matchcount++;
	    if (serverstats->t_join < serverstats->t_quit)
		continue;
	    count++;
	    notice(s_StatServ, u->nick, "%-30s %3d (%2d%%)  %3d (%2d%%)",
		   serverstats->name, serverstats->usercnt,
		   !usercnt ? 0 : (serverstats->usercnt*100)/usercnt,
		   serverstats->opercnt,
		   !opcnt ? 0 : (serverstats->opercnt*100)/opcnt);
	}
	notice_lang(s_StatServ, u, STAT_SERVERS_LIST_RESULTS,
			count, matchcount);

    } else if (stricmp(cmd, "VIEW") == 0) {
	char *param = strtok(NULL, " ");
	char join_buf[512];
	char quit_buf[512];
	int is_online;
	int limitto = 0;	/* 0 == none; 1 == online; 2 == offline */

	if (param) {
	    if (stricmp(param, "ONLINE") == 0) {
		limitto = 1;
	    } else if (stricmp(param, "OFFLINE") == 0) {
	    	limitto = 2;
	    }
	}

	for (serverstats = serverstatslist; serverstats;
	     serverstats = serverstats->next
	) {
	    if (mask && !match_wild_nocase(mask, serverstats->name))
		continue;
	    if (serverstats->t_join >= serverstats->t_quit)
		is_online = 1;
	    else
		is_online = 0;
	    if (limitto && !((is_online && limitto == 1) ||
			     (!is_online && limitto == 2)))
		continue;

	    count++;
	    tm = localtime(&serverstats->t_join);
	    strftime_lang(join_buf, sizeof(join_buf), u,
			  STRFTIME_DATE_TIME_FORMAT, tm);
	    if (serverstats->t_quit != 0) {
		tm = localtime(&serverstats->t_quit);
		strftime_lang(quit_buf, sizeof(quit_buf), u,
			      STRFTIME_DATE_TIME_FORMAT, tm);
	    }

	    notice_lang(s_StatServ, u,
	    		is_online ? STAT_SERVERS_VIEW_HEADER_ONLINE
				  : STAT_SERVERS_VIEW_HEADER_OFFLINE,
			serverstats->name);
	    notice_lang(s_StatServ, u, STAT_SERVERS_VIEW_LASTJOIN, join_buf);
	    if (serverstats->t_quit > 0)
		notice_lang(s_StatServ, u, STAT_SERVERS_VIEW_LASTQUIT,
			    quit_buf);
	    if (serverstats->quit_message)
		notice_lang(s_StatServ, u, STAT_SERVERS_VIEW_QUITMSG,
			    serverstats->quit_message);
	    if (is_online)
		notice_lang(s_StatServ, u, STAT_SERVERS_VIEW_USERS_OPERS,
			    serverstats->usercnt,
			    !usercnt ? 0 : (serverstats->usercnt*100)/usercnt,
			    serverstats->opercnt,
			    !opcnt ? 0 : (serverstats->opercnt*100)/opcnt);
	}
	notice_lang(s_StatServ, u, STAT_SERVERS_VIEW_RESULTS, count, nservers);

    } else if (!is_services_root(u)) {
	syntax_error(s_StatServ, u, "SERVERS", STAT_SERVERS_SYNTAX);

    /* Only the Services Root has access from here on! */

    } else if (stricmp(cmd, "DELETE") == 0) {
	if (!mask) {
	    syntax_error(s_StatServ, u, "SERVERS", STAT_SERVERS_DELETE_SYNTAX);
	} else if (!(serverstats = stats_findserver(mask))) {
	    notice_lang(s_StatServ, u, SERV_X_NOT_FOUND, mask);
	} else if (serverstats->t_join > serverstats->t_quit) {
	    notice_lang(s_StatServ, u, STAT_SERVERS_REMOVE_SERV_FIRST, mask);
     	} else {
	    delete_serverstats(serverstats);
	    notice_lang(s_StatServ, u, STAT_SERVERS_DELETE_DONE, mask);
	}

    } else if (stricmp(cmd, "COPY") == 0) {
	char *newname = strtok(NULL, " ");

	if (!newname) {
	    syntax_error(s_StatServ, u, "SERVERS", STAT_SERVERS_COPY_SYNTAX);
	} else if (!(serverstats = stats_findserver(mask))) {
	    notice_lang(s_StatServ, u, SERV_X_NOT_FOUND, mask);
	} else if (stats_findserver(newname)) {
	    notice_lang(s_StatServ, u, STAT_SERVERS_SERVER_EXISTS, newname);
     	} else {
	    serverstats = new_serverstats(newname);
	    notice_lang(s_StatServ, u, STAT_SERVERS_COPY_DONE, mask, newname);
	}

    } else if (stricmp(cmd, "RENAME") == 0) {
	char *newname = strtok(NULL, " ");

	if (!newname) {
	    syntax_error(s_StatServ, u, "SERVERS", STAT_SERVERS_RENAME_SYNTAX);
	} else if (!(serverstats = stats_findserver(mask))) {
	    notice_lang(s_StatServ, u, SERV_X_NOT_FOUND, mask);
	} else if (serverstats->t_join > serverstats->t_quit) {
	    notice_lang(s_StatServ, u, STAT_SERVERS_REMOVE_SERV_FIRST, mask);
	} else if (stats_findserver(newname)) {
	    notice_lang(s_StatServ, u, STAT_SERVERS_SERVER_EXISTS, newname);
     	} else {
	    free(serverstats->name);
	    serverstats->name = sstrdup(newname);
	    notice_lang(s_StatServ, u, STAT_SERVERS_RENAME_DONE, mask,newname);
	}

    } else {
	syntax_error(s_StatServ, u, "SERVERS", STAT_SERVERS_SYNTAX);
    }
}

/*************************************************************************/

/* FIXME: language strings */

void do_users(User *u)
{
    char *cmd = strtok(NULL, " ");
    int avgusers, avgopers;

    if (!cmd)
        cmd = "";

    if (stricmp(cmd, "STATS") == 0) {
	notice(s_StatServ, u->nick, "         Total users: %d", usercnt);
	notice(s_StatServ, u->nick, "         Total opers: %d", opcnt);
	avgusers = (usercnt + servercnt/2) / servercnt;
	avgopers = (opcnt*10 + servercnt/2) / servercnt;
	notice(s_StatServ, u->nick, "Avg users per server: %d", avgusers);
	notice(s_StatServ, u->nick, "Avg opers per server: %d.%d",
	       avgopers/10, avgopers%10);
    } else {
	syntax_error(s_StatServ, u, "USERS", STAT_USERS_SYNTAX);
    }
}

/*************************************************************************/

/* FIXME: not done */

#if 0
void dump_map(User *u, Server *parent, int length, int longest)
{
    Server *serverstats;
    static char buf[64];
    static int level = 0;

    level++;

    notice(s_StatServ, u->nick, "%s%s",
    		buf, parent->name);
    serverstats = parent->child;
    if (serverstats) {
	if (length > 0)
	    buf[length-1] = ' ';
	buf[length++] = '|';
	buf[length++] = '-';
	buf[length] = '\0';
    } else {

    }
    while (serverstats) {
	if (serverstats->child) {
	    dump_map(u, serverstats, length, longest);
	} else {
	    notice(s_StatServ, u->nick, "%s%s",
	    		buf, server->name);
	}
	serverstats = serverstats->sibling;
    }
    length -= 1;
    buf[length] = '\0';
    level--;
}

static void do_map(User *u)
{
    notice(s_StatServ, u->nick, "Command disabled.");
    return;
    dump_map(u, findserver("trinity.shadowfire.org"), 0, 30);
}
#endif

/*************************************************************************/
/************************* Statistics Load/Save **************************/
/*************************************************************************/

#define SAFE(x) do {                                    \
    if ((x) < 0) {                                      \
        if (!forceload)                                 \
            fatal("Read error on %s", StatDBName);  \
        nservers = i;                                   \
        break;                                          \
    }                                                   \
} while (0)

void load_ss_dbase()
{
    dbFILE *f;
    int i;
    int16 n;
    int32 tmp32;
    ServerStats *serverstats, *last;
    time_t def_quit = time(NULL)-1;  /* avoid join>quit staying true on load */

    if (!(f = open_db(s_StatServ, StatDBName, "r")))
        return;
    switch (i = get_file_version(f)) {
      case 11:
      case 10:
      case 9:
      case 8:
      case 7:
        SAFE(read_int16(&n, f));
        nservers = n;
	serverstats = NULL;
	last = NULL;
        for (i = 0; i < nservers; i++) {
	    serverstats = scalloc(sizeof(ServerStats), 1);
	    serverstats->next = last;
	    if (last)
		last->prev = serverstats;
	    last = serverstats;
            SAFE(read_string(&serverstats->name, f));
	    serverstats->usercnt = 0;
	    serverstats->opercnt = 0;
	    SAFE(read_int32(&tmp32, f));
	    serverstats->t_join = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    serverstats->t_quit = def_quit;
	    SAFE(read_string(&serverstats->quit_message, f));
        }
	if (serverstats)
	    serverstats->prev = NULL;
	serverstatslist = serverstats;
        break;

      case -1:
	fatal("Unable to read version number from %s", StatDBName);

      default:
        fatal("Unsupported version (%d) on %s", i, StatDBName);
    } /* switch (ver) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_ss_dbase()
{
    dbFILE *f;
    ServerStats *serverstats;
    static time_t lastwarn = 0;

    if (!(f = open_db(s_StatServ, StatDBName, "w")))
        return;
    SAFE(write_int16(nservers, f));
    for (serverstats = serverstatslist; serverstats;
	 serverstats = serverstats->next
    ) {
        SAFE(write_string(serverstats->name, f));
	SAFE(write_int32(serverstats->t_join, f));
	SAFE(write_int32(serverstats->t_quit, f));
	SAFE(write_string(serverstats->quit_message, f));
    }
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", StatDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", StatDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/*********************** Internal Stats Functions ************************/
/*************************************************************************/

static ServerStats *new_serverstats(const char *servername)
{
    ServerStats *serverstats;

    nservers++;
    serverstats = scalloc(sizeof(ServerStats), 1);
    serverstats->name = sstrdup(servername);
    serverstats->next = serverstatslist;
    if (serverstats->next)
	serverstats->next->prev = serverstats;
    serverstatslist = serverstats;

    return serverstats;
}

/* Remove and free a ServerStats structure. */

static void delete_serverstats(ServerStats *serverstats)
{
    if (debug >= 2)
        log("debug: delete_serverstats() called");

    nservers--;
    if (serverstats->prev)
	serverstats->prev->next = serverstats->next;
    else
	serverstatslist = serverstats->next;
    if (serverstats->next)
	serverstats->next->prev = serverstats->prev;
    if (debug >= 2)
        log("debug: delete_serverstats(): free ServerStats structure");
    free(serverstats->name);
    if (serverstats->quit_message)
	free(serverstats->quit_message);
    free(serverstats);

    if (debug >= 2)
        log("debug: delete_serverstats() done");
}

/*************************************************************************/
/*********************** External Stats Functions ************************/
/*************************************************************************/

ServerStats *stats_findserver(const char *servername)
{
    ServerStats *serverstats;

    if (!servername)
	return NULL;

    for (serverstats = serverstatslist; serverstats;
	 serverstats = serverstats->next
    ) {
	if (stricmp(servername, serverstats->name) == 0) {
	    return serverstats;
	}
    }

    return NULL;
}

/*************************************************************************/

/* Handle a server joining */

ServerStats *stats_do_server(const char *servername, const char *serverhub)
{
    ServerStats *serverstats;

    servercnt++;

    serverstats = stats_findserver(servername);
    if (serverstats) {
	/* Server has rejoined us */
	serverstats->usercnt = 0;
	serverstats->opercnt = 0;
	serverstats->t_join = time(NULL);
    } else {
	/* Totally new server */
	serverstats = new_serverstats(servername);  /* cleared to zero */
	serverstats->t_join = time(NULL);
    }

    if (*serverhub) {
	serverstats->hub = stats_findserver(serverhub);
	if (!serverstats->hub) {
	    /* Paranoia */
	    wallops(s_OperServ,
		    "WARNING: Could not find server \2%s\2 which is supposed"
		    " to be the hub for \2%s\2", serverhub, servername);
	    log("%s: could not find hub %s for %s",
		s_StatServ, serverhub, servername);
	}
    } else {
	serverstats->hub = NULL;
    }

    return serverstats;
}

/*************************************************************************/

/* Handle a user quitting */

void stats_do_quit(const User *user)
{
    ServerStats *serverstats = user->server->stats;

    serverstats->usercnt--;
    if (is_oper_u(user))
        serverstats->opercnt--;
}

/*************************************************************************/

/* Handle a server quitting */

void stats_do_squit(const Server *server, const char *quit_message)
{
    ServerStats *serverstats = server->stats;

    servercnt--;
    serverstats->t_quit = time(NULL);
    if (serverstats->quit_message)
	free(serverstats->quit_message);
    serverstats->quit_message = *quit_message ? sstrdup(quit_message) : NULL;
}

/*************************************************************************/

#endif /* STATISTICS */

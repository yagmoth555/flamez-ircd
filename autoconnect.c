/* Autoconnect.c
 *
 * Autoconnect is mainly a new option for OperServ
 * that allow Service Admin, and Service Root to put
 * C:N lines from server config's file in a database, 
 * and after the add-on is correctly configured, 
 * you just have to wait for the server to split, and
 * watch service to auto- reconnect the splitted server.
 * Copyright (c) 2001 Philippe Levesque <EMail: yagmoth555@yahoo.com>
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

typedef struct aconnect AConnect;
struct aconnect {
    char *servername;		/* Well, how we call that folk. */
    char *where;			/* Where the server connect to. */
    int16 port;				/* On wich port ? */
	int16 num;				/* Number of times the server splitted. */
	int16 numppl;			/* Number of peoples lost in the last split. */
    time_t splittimer;		/* When we reconnect the server? (time(null) + X) when the split occur */
	time_t timeadded;		/* When the server got added in the aconnect's list ? *used only for stat* */
};

static int32 naconnect = 0;
static struct aconnect *aconnects = NULL;

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

/*void get_nooper_stats(long *nrec, long *memuse)
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
}*/


int num_aconnect(void)
{
    return (int) naconnect;
}

/*************************************************************************/
/************************** INPUT/OUTPUT functions ***********************/
/*************************************************************************/
#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", AConnectDBName);	\
	naconnect = i;					\
	break;						\
    }							\
} while (0)

void load_aconnect(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;
    int32 tmp32;

    if (!(f = open_db("ACONNECT", AConnectDBName, "r")))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    naconnect = tmp16;
    aconnects = scalloc(sizeof(*aconnects), naconnect);

    switch (ver) {
      case 11:
	for (i = 0; i < naconnect; i++) {
	    SAFE(read_string(&aconnects[i].servername, f));
	    SAFE(read_string(&aconnects[i].where, f));
		SAFE(read_int16(&aconnects[i].port, f));
		SAFE(read_int16(&aconnects[i].num, f));
		SAFE(read_int16(&aconnects[i].numppl, f));
	    SAFE(read_int32(&tmp32, f));
	    aconnects[i].splittimer = tmp32;
		SAFE(read_int32(&tmp32, f));
	    aconnects[i].timeadded = tmp32;
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", AConnectDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, AConnectDBName);
    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_aconnect(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db("ACONNECT", AConnectDBName, "w");
    write_int16(naconnect, f);
    for (i = 0; i < naconnect; i++) {
		SAFE(write_string(aconnects[i].servername, f));
	    SAFE(write_string(aconnects[i].where, f));
		SAFE(write_int16(aconnects[i].port, f));
		SAFE(write_int16(aconnects[i].num, f));
		SAFE(write_int16(aconnects[i].numppl, f));
	    SAFE(write_int32(aconnects[i].splittimer, f));
		SAFE(write_int32(aconnects[i].timeadded, f));
    }
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", AConnectDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", AConnectDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

/*************************************************************************/
/************************** External functions ***************************/
/*************************************************************************/

/* Check if the ircd got a relink to do
 */
static void autoconnectrelink(Timeout *to)
{
	char *servername = to->data;
	int i = 0;

	for (i = 0; i < naconnect; i++) {
		if(strcmp(servername,aconnects[i].servername)==0) {
			aconnects[i].numppl = 0;
			if (WallOSAConnect) wallops(s_OperServ, "Connecting the lost server NOW");
			send_cmd(s_OperServ, "CONNECT %s %d %s", aconnects[i].servername, aconnects[i].port, aconnects[i].where);
		}
	}
}


/* Check if a Split happen
 * the quitmsg should always be like that: "where.servername.com lostserver.otherserver.com"
 */
void checkforsplit(const char *quitmsg)
{
	char *s, *where;
	int i = 0;
	int result;
	Timeout *t;
	int delay = 15;

	for (i = 0; i < naconnect; i++) {
		where = strstr(quitmsg, aconnects[i].where);
		if (where != NULL) {
			result = where - quitmsg;
			if (result==0) {
				s = strstr(quitmsg, aconnects[i].servername);
				if (s != NULL) {
					if (aconnects[i].numppl == 0) {
						aconnects[i].num += 1;
						aconnects[i].numppl += 1;
						t = add_timeout(delay, autoconnectrelink, 0);
						t->data = aconnects[i].servername;
					} else {
						aconnects[i].numppl += 1;
					}
				}
			}
		}
	}	
}


/*************************************************************************/
/************************** ACONNECT list editing ************************/
/*************************************************************************/

/* Note that all string parameters are assumed to be non-NULL.
 */

void add_aconnect(const char *servername, const char *where, int16 port)
{
    AConnect *aconnect;

    /* 100 aconnect should be enuff for any network in the world! -jabea */
	if (naconnect >= 100) {
	log("%s: Attempt to add a new ACONNECT to a full list!", s_OperServ);
	return;
    }

	aconnects = srealloc(aconnects, sizeof(*aconnects) * (naconnect + 1));

    aconnect = &aconnects[naconnect];
    aconnect->servername = sstrdup(servername);
    aconnect->where = sstrdup(where);
    aconnect->port = port;
	aconnect->num = 0;
	aconnect->numppl = 0;
	aconnect->timeadded = time(NULL);
    aconnect->splittimer = aconnect->timeadded;
	naconnect++;
}

/*************************************************************************/

/* Return whether the mask was found in the ACONNECT list. */

static int del_aconnect(const char *servername)
{
    int i;

    for (i = 0; i < naconnect && strcmp(aconnects[i].servername, servername) != 0; i++)
	;
    if (i < naconnect) {
	free(aconnects[i].servername);
	free(aconnects[i].where);
	naconnect--;
	if (i < naconnect)
	    memmove(aconnects+i, aconnects+i+1, sizeof(*aconnects) * (naconnect-i));
	return 1;
    } else {
	return 0;
    }
}

/*************************************************************************/

/* Handle an OperServ ACONNECT command. */

void do_aconnect(User *u)
{
    char *cmd, *servername, *where, *s_port, *s;
    int16 port = 0;
	int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {

	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
		}

	if (naconnect >= 100) {
	    return;
	}

	servername = strtok(NULL, " ");
	where = strtok(NULL, " ");
	s_port = strtok(NULL, " ");

	if ((!servername) || (!where) || (!s_port)) {
		send_cmd(s_OperServ, "NOTICE %s :ACONNECT ADD \2servername\2 \2where2connect\2 \2port\2", u->nick);
	    return;
	}
	
	port = atoi(s_port);
	/* usually, port under 1024 're reserved for standard deamon, so to be idiot proof i block all those ports 
	   from behing selected -jabea 
	if ((port < 1024) || (port > 65535)) {
		send_cmd(s_OperServ, "NOTICE %s :\2Notice\2: ACONNECT \2port\2 must be a legal port number (between 1024 and 65535)", u->nick);
		return;
		}
	*/
	/* aconnect on *.net, or thing like that is a badZ idea in my opinion -jabea */
	if (strchr(servername, '*') || strchr(where, '*') || strchr(servername, '?') || strchr(where, '?')) {
		send_cmd(s_OperServ, "NOTICE %s :\2Notice\2: ACONNECT address cannot contain \2wildcards\2.", u->nick);
	    return;
	}

	/* Make sure the server is not already in the list. */
	for (i = 0; i < naconnect && strcmp(aconnects[i].servername, servername) != 0; i++)
	    ;
	if (i < naconnect) {
	    send_cmd(s_OperServ, "NOTICE %s :ACONNECT server already exist!", u->nick);
	    return;
	}

	add_aconnect(servername, where, port);
	send_cmd(s_OperServ, "NOTICE %s :ACONNECT succesfully added \2%s\2", u->nick, servername);
	if (WallOSAConnect) {
	    wallops(s_OperServ, "%s added an AUTO-CONNECT for \2%s\2 -> \2%s\2:\2%s\2",
		    u->nick, servername, where, s_port);
	}
	if (readonly)
		notice_lang(s_OperServ, u, READ_ONLY_MODE);
    } else if (stricmp(cmd, "DEL") == 0) {
	
	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
		}	
	servername = strtok(NULL, " ");
	if (servername) {
	    if (del_aconnect(servername)) {
		send_cmd(s_OperServ, "NOTICE %s :ACONNECT succesfully removed \2%s\2", u->nick, servername);
		if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		send_cmd(s_OperServ, "NOTICE %s :ACONNECT not found for \2%s\2", u->nick, servername);
	    }
	} else {
	    send_cmd(s_OperServ, "NOTICE %s :\2%s\2 not found on the ACONNECT list", u->nick, servername);
	}

    } else if (stricmp(cmd, "LIST") == 0 || stricmp(cmd, "VIEW") == 0) {
	int is_view = stricmp(cmd,"VIEW")==0;

	s = strtok(NULL, " ");
	if (!s)
	    s = "*";

	send_cmd(s_OperServ, "NOTICE %s :Current ACONNECT list", u->nick);
	for (i = 0; i < naconnect; i++) {
	    if (!s || (match_wild(s, aconnects[i].servername))) {
		if (is_view) {
		    char timebuf[BUFSIZE];
		    struct tm tm;
		    time_t t = time(NULL);

		    tm = *localtime(aconnects[i].timeadded ? &aconnects[i].timeadded : &t);
		    strftime_lang(timebuf, sizeof(timebuf), u, STRFTIME_SHORT_DATE_FORMAT, &tm);
			send_cmd(s_OperServ, "NOTICE %s :%s --> %s:%d (Splitted %d time(s), Date added :%s)", u->nick, aconnects[i].servername,
				aconnects[i].where, aconnects[i].port, aconnects[i].num, timebuf);
		} else { /* !is_view */
			send_cmd(s_OperServ, "NOTICE %s :%s --> %s:%d", u->nick, aconnects[i].servername, aconnects[i].where, aconnects[i].port);
		}
	    }
	}

    } else if (stricmp(cmd, "COUNT") == 0) {
	send_cmd(s_OperServ, "NOTICE %s :There is %d servers on the auto-connect list.", u->nick, naconnect);

    } else {
	send_cmd(s_OperServ, "NOTICE %s :ACONNECT {ADD | DEL | LIST | VIEW | COUNT} [servername. [.where.][.port.]].", u->nick);
    }
}

/*************************************************************************/

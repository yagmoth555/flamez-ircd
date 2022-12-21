/* FloodServ core structures.
 *
 * Add an way to break flood attack,
 * -primary by checking flood from channel from a nick
 * -or from a host
 * -or from a ident
 * Copyright (c) 2001 Philippe Levesque <EMail: yagmoth555@yahoo.com>
 * See www.flamez.net for more info
 */

#include "services.h"
#include "pseudo.h"
#include "floodserv.h"

// current extern function: floodserv, privmsg_flood, check_grname, fs_init
//							fs_add_chan

/******************************************************************/
/* Local Functions declarations                                   */
/******************************************************************/
void fs_add_akill(time_t expires, TxtFloods *pnt);
void add_floodtxt(User *u, char *buf, int id);
void add_floodtxt_user(User *u, TxtFloods *pnt);
void expire_floodtxt();
char *strstrip(char *d, const char *s);
void do_chan(User *u);
static void do_help(User *u);
void do_grname(User *u);
void do_set(User *u);
void add_chan(const char *channame);
void add_grname(const char *rnmask);
static int del_chan(const char *channame);
static int del_grname(const char *rnmask);
void list_chan(User *u);
void list_grname(User *u);
void list_floodtxt(User *u);
void rejoin_chan(User *u);

/******************************************************************/
/* Declarations of our main list we will use                      */
/******************************************************************/
static int32	nchan = 0;
static int32	chan_size = 0;
static struct	chanprotected_ *chanprotected = NULL;
//static Timeout  *Expire_Timeout = NULL;

static int32	ngrname = 0;
static int32	grname_size	= 0;
static struct	grname *grnames = NULL;

/******************************************************************/
/* Cmd Struct Declaration                                         */
/******************************************************************/
static Command cmds[] = {
    { "HELP",		do_help,	NULL, -1, -1,-1,-1,-1 },
    { "CHAN",		do_chan,	is_services_oper, FLOOD_HELP_CHAN,		-1,-1,-1,-1 },
    { "SET",		do_set,		is_services_admin, FLOOD_HELP_SET,		-1,-1,-1,-1 },
	{ "GRNAME",		do_grname,	is_services_admin, FLOOD_HELP_GRNAME,	-1,-1,-1,-1 },
    { NULL }
};


/*******************************************************************/
/* CheckUp Routine                                                 */
/* Called of PRIVMSG Check -> m_privmsg>Message.c				   */
/* av[0] = channel name                                            */
/* av[1] and so on = the text writted                              */
/*******************************************************************/
void privmsg_flood(const char *source, int ac, char **av)
{
	char *text;
	//char buf[BUFSIZE];
	char text_d[BUFSIZE];
	TxtFloods *txt, *next;
	time_t now = time(NULL);
	time_t expires = FloodServAkillExpiry;
	int i = 0;

	User *u = finduser(source);
	if (!u) return;
	
	if (is_oper(source))
		return;

	text = av[1];
	strstrip(text_d, text);

	//if (!Expire_Timeout)
	//	Expire_Timeout = add_timeout((FloodServTFSecWarned + 2), expire_floodtxt_timeout, 0);
	expire_floodtxt();

	/* first check - does we monitor that channel ? - because oper can raw command a bot to join a channel. */
	for (i = 0; i < nchan; i++) {
		if(irc_stricmp(av[0],chanprotected[i].channame)==0) {
			txt = chanprotected[i].TxtFlood;
			while (txt) {
				next = txt->next;
				if(stricmp(text_d, txt->txtbuffer)==0) {
					add_floodtxt_user(u, txt);
					txt->repeat +=	1;
					if (txt->repeat >= FloodServTFNumLines) {
						 /* he repeated more than the limit, but we need to check the delay,
						    thrusting expire_floodtxt is not safe - jabea */
						expires += now;
						//snprintf(buf, sizeof(buf), "*@%s", u->host);
						if (now <= (txt->time + FloodServTFSec)) {
							if ((FloodServWarnFirst) && (!txt->warned)) {
								txt->warned = 1;
								wallops(s_FloodServ, "(FloodServ) Flood Detected: (Text: [%45s]) (In: [\2%s\2]) (Last Said by: [\2%s\2] (%s@%s)) has been said %d times in less than %d seconds", 
									text, av[0], u->nick, u->username, u->host, txt->repeat, FloodServTFSec);
								kill_user(s_FloodServ, source, FloodServWarnMsg);
							} 
							else {
								fs_add_akill(expires, txt);
							}
						} else if ((now <= (txt->time + FloodServTFSecWarned)) && (txt->warned) && (txt->repeat >= FloodServTFNLWarned)) {
							fs_add_akill(expires, txt);
						}
						
					}
					/* .... */
					return;
				}
				txt = next;
			}
			add_floodtxt(u, text_d, i);
			return;
		}
	}
	/* here, should part that channel */
	//if (is_on_chan(s_FloodServ, av[0]))
		//send_cmd(NULL, ":%s PART %s", s_FloodServ, av[0]);
		//send_cmd(s_FloodServ, "PART %s", av[0]);
	//do_part(s_FloodServ, 1, av[0]);
}



/*******************************************************************/
/* fs_add_akill : akill anyone that flooded (KEY by HOST)          */
/*******************************************************************/
void fs_add_akill(time_t expires, TxtFloods *pnt) 
{
	User *u, *unext;
	char buf[BUFSIZE];
	char timebuf[128];
	Flooders  *fpnt, *next;
	
	for (fpnt = pnt->flooder; fpnt; fpnt = next) {
			next = fpnt->next;
			if (!fpnt->akilled) {
				if (!is_akilled(fpnt->host)) {
					snprintf(buf, sizeof(buf), "*@%s", fpnt->host);
					add_akill(buf, FloodServAkillReason, s_FloodServ, expires);
					/* if ImmediatelySendAkill is off, that give us heachache there...
					   lets kill that poor guy & his bots with a homemade autokill, 
					   and hope he sign again to make the autokill *finally* active
					   argthh -jabea */
					if (!ImmediatelySendAkill) {
						/* here, we will try to find user matching that mask....  */
						/* if there is a better way to do that, let me know -jabea */
						u = firstuser();
						while (u)
						{
							unext = nextuser();
							if (stricmp(u->host, fpnt->host)==0) {
								kill_user(s_FloodServ, u->nick, FloodServAkillReason);
							}
							u = unext;
						}
						/* end of search */
					}
					if (WallOSAkill) {
						expires_in_lang(timebuf, sizeof(timebuf), NULL, expires);
						wallops(s_OperServ, "FloodServ added an AKILL for \2%s\2 (%s)", buf, timebuf);
					}
				}
				fpnt->akilled = 1;
			}
		}
}


/*******************************************************************/
/* add_floodtxt : link a msg from a channel to a channel struct    */
/*******************************************************************/
void add_floodtxt(User *u, char *buf, int id)
{
	TxtFloods *txt  = NULL;
	TxtFloods *pnt  = NULL;
	
	pnt = chanprotected[id].TxtFlood;
	txt = smalloc(sizeof(*txt));
	
	txt->repeat = 1;
	txt->warned = 0;
	txt->txtbuffer = sstrdup(buf);
	txt->time = time(NULL);
	txt->flooder = NULL;

	if (pnt) {
		pnt->prev = txt;
		txt->next = pnt;
	}
	else
		txt->next = NULL;
	txt->prev = NULL;
	chanprotected[id].TxtFlood = txt;
	
	add_floodtxt_user(u, txt);
}


/*******************************************************************/
/* add_floodtxt_user : link a user to a txtbuffer struct           */
/*******************************************************************/
void add_floodtxt_user(User *u, TxtFloods *txt)
{
	Flooders  *fdr, *fpnt, *fnext;
	
	for (fpnt = txt->flooder; fpnt; fpnt = fnext) {
		fnext = fpnt->next;
		if(stricmp(u->host, fpnt->host)==0) {
			return;
		}
	}
	
	fpnt = txt->flooder;
	fdr = smalloc(sizeof(*fdr));

	strscpy(fdr->nick, u->nick, NICKMAX);
	fdr->host = sstrdup(u->host);
	fdr->akilled = 0;

	if (fpnt) {
		fdr->next = fpnt;
	}
	else {
		fdr->next = NULL;
	}

	txt->flooder = fdr;
}


/*******************************************************************/
/* expire_floodtxt : expire all non-flood msg & free up some mems  */
/*******************************************************************/
void expire_floodtxt(void)
{
	TxtFloods *pnt, *next = NULL;
	Flooders  *fpnt, *fnext = NULL;
	time_t now = time(NULL);
	int i;

	for (i = 0; i < nchan; i++) {
		for (pnt = chanprotected[i].TxtFlood; pnt; pnt = next) {
			next = pnt->next;
			if (((!pnt->warned) && (now > (pnt->time + FloodServTFSec))) ||  ((pnt->warned) && (now > (pnt->time + FloodServTFSecWarned)))) {
				if (pnt->next)
					pnt->next->prev = pnt->prev;
				if (pnt->prev)
					pnt->prev->next = pnt->next;
				else
					chanprotected[i].TxtFlood = pnt->next;
				
				if (pnt->flooder) {
					for (fpnt = pnt->flooder->next; fpnt; fpnt = fnext) {
						fnext = fpnt->next;

						if (fpnt->host)
							free(fpnt->host);
						free(fpnt);
					}
					if (pnt->flooder->host)
						free(pnt->flooder->host);
					free(pnt->flooder);
				}

				free(pnt->txtbuffer);
				free(pnt);
			}
		}
	}
}


/*******************************************************************/
/* expire_floodtxt_timeout : expire all non-flood msg & free up mem*/
/*******************************************************************/
/*static void expire_floodtxt_timeout(Timeout *to)
//{
//	TxtFloods *pnt, *next = NULL;
//	Flooders  *fpnt, *fnext = NULL;
	time_t now = time(NULL);
	int i;

	for (i = 0; i < nchan; i++) {
		for (pnt = chanprotected[i].TxtFlood; pnt; pnt = next) {
			next = pnt->next;
			if (((!pnt->warned) && (now > (pnt->time + FloodServTFSec))) ||  ((pnt->warned) && (now > (pnt->time + FloodServTFSecWarned)))) {
				if (pnt->next)
					pnt->next->prev = pnt->prev;
				if (pnt->prev)
					pnt->prev->next = pnt->next;
				else
					chanprotected[i].TxtFlood = pnt->next;

				if (pnt->flooder) {
					for (fpnt = pnt->flooder->next; fpnt; fpnt = fnext) {
						fnext = fpnt->next;

						if (fpnt->host)
							free(fpnt->host);
						free(fpnt);
					}
					if (pnt->flooder->host)
						free(pnt->flooder->host);
					free(pnt->flooder);
				}

				free(pnt->txtbuffer);
				free(pnt);
			}
		}
	}
}*/


/*******************************************************************/
/* strstrip : strip anything from <= 0x32                          */
/*******************************************************************/
char *strstrip(char *d, const char *s)
{
    char *t = d;

    while (*s) {
		if (*s > '\040') {
			*d = *s;
			d++;
		}
		s++;
	}
    *d = 0;
    return t;
}


/*******************************************************************/
/* Main routine                                                    */
/*******************************************************************/
void floodserv(const char *source, char *buf)
{
    char *cmd;
    char *s;
    User *u = finduser(source);

    if (!u) {
		log("%s: user record for %s not found", s_FloodServ, source);
		notice(s_FloodServ, source, getstring((NickInfo *)NULL, USER_RECORD_NOT_FOUND));
		return;
	}

    log("%s: %s: %s", s_FloodServ, source, buf);
    
    cmd = strtok(buf, " ");
    if (!cmd) {
		return;
    } else if (stricmp(cmd, "\1PING") == 0) {
		if (!(s = strtok(NULL, "")))
			s = "\1";
		notice(s_FloodServ, source, "\1PING %s", s);
    } else {
		run_cmd(s_FloodServ, u, cmds, cmd);
    }
}

/*******************************************************************/
/* Handle a NOTICE sent to services							       */
/*******************************************************************/
void do_notice(const char *source, int ac, char **av)
{
    User *user;
    //char *s, *t;
    //struct u_chanlist *c;

    user = finduser(source);
    if (!user) {
		log("user: NOTICE from nonexistent user %s: %s", source, merge_args(ac, av));
		return;
    }


}


/*******************************************************************/
/* Handle directed channel commmand for floodserv			       */
/*******************************************************************/
void do_chan(User *u) {
	char *cmd;
	char *channelname;
	int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

	channelname = strtok(NULL, "");

	if (stricmp(cmd, "ADD") == 0) {
		if (!channelname) {
			send_cmd(s_FloodServ, "NOTICE %s :CHAN ADD \2ChannelName\2", u->nick);
			return;
		}
		/* Make sure mask does not already exist on the list. */
		for (i = 0; i < nchan && irc_stricmp(chanprotected[i].channame, channelname) != 0; i++)
	    ;
		if (i < nchan) {
			send_cmd(s_FloodServ, "NOTICE %s :Channel already exist on the list!", u->nick);
			return;
		}
		add_chan(channelname);
		send_cmd(s_FloodServ, "NOTICE %s :Channel \2%s\2 Succesfully added!", u->nick, channelname);
		if (readonly)
			notice_lang(s_FloodServ, u, READ_ONLY_MODE);
	} else if (stricmp(cmd, "DEL") == 0) {
		if (!channelname) {
			send_cmd(s_FloodServ, "NOTICE %s :CHAN DEL \2ChannelName\2", u->nick);
			return;
		}
		if (del_chan(channelname)) {
			send_cmd(s_FloodServ, "NOTICE %s :Channel \2%s\2 Succesfully deleted!", u->nick, channelname);
			if (readonly)
				notice_lang(s_FloodServ, u, READ_ONLY_MODE);
	    } else {
			send_cmd(s_FloodServ, "NOTICE %s :Channel \2%s\2 not found!", u->nick, channelname);
	    }
	} else if (stricmp(cmd, "LIST") == 0) {
		list_chan(u);
	} else if (stricmp(cmd, "LISTFLOODTEXT") == 0) {
		list_floodtxt(u);
	} else if (stricmp(cmd, "COUNT") == 0) {
		send_cmd(s_FloodServ, "NOTICE %s :Number of channel(s) monitored: \2%d\2", u->nick, nchan);
	} else if (stricmp(cmd, "REJOIN") == 0) {
		rejoin_chan(u);
	} else {
		send_cmd(s_FloodServ, "NOTICE %s :CHAN {ADD | DEL | LIST | COUNT | REJOIN } [channel name].", u->nick);
	}
}


/******************************************************************/
/* Help Function : Currently do *Nothing*                         */
/******************************************************************/
static void do_help(User *u)
{
    const char *cmd = strtok(NULL, "");

    if (!cmd) {
		notice_help(s_FloodServ, u, FLOOD_HELP);
    } else {
		help_cmd(s_FloodServ, u, cmds, cmd);
    }
}


/******************************************************************/
/* fs_init : currently only rejoin channel at start-up            */
/******************************************************************/
void fs_init(void)
{
	if (nchan > 0) {
		rejoin_chan(NULL);
	}
}


/*******************************************************************/
/* Handle directed grname commmand for floodserv			       */
/*******************************************************************/
void do_grname(User *u) {
	char *cmd;
	char *rnmask;
	int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

	rnmask = strtok(NULL, "");

	if (stricmp(cmd, "ADD") == 0) {
		if (!rnmask) {
			send_cmd(s_FloodServ, "NOTICE %s :GRNAME ADD \2real name\2", u->nick);
			return;
		}
		/* Make sure mask does not already exist on the list. */
		for (i = 0; i < ngrname && stricmp(grnames[i].mask, rnmask) != 0; i++)
	    ;
		if (i < ngrname) {
			send_cmd(s_FloodServ, "NOTICE %s :GRNAME already exist on the list!", u->nick);
			return;
		}
		add_grname(rnmask);
		send_cmd(s_FloodServ, "NOTICE %s :GRNAME \2%s\2 Succesfully added!", u->nick, rnmask);
		if (readonly)
			notice_lang(s_FloodServ, u, READ_ONLY_MODE);
	} else if (stricmp(cmd, "DEL") == 0) {
		if (!rnmask) {
			send_cmd(s_FloodServ, "NOTICE %s :GRNAME DEL \2real name\2", u->nick);
			return;
		}
		if (del_grname(rnmask)) {
			send_cmd(s_FloodServ, "NOTICE %s :GRNAME \2%s\2 Succesfully deleted!", u->nick, rnmask);
			if (readonly)
				notice_lang(s_FloodServ, u, READ_ONLY_MODE);
	    } else {
			send_cmd(s_FloodServ, "NOTICE %s :GRNAME \2%s\2 not found!", u->nick, rnmask);
	    }
	} else if (stricmp(cmd, "LIST") == 0) {
		list_grname(u);
	} else if (stricmp(cmd, "COUNT") == 0) {
		send_cmd(s_FloodServ, "NOTICE %s :Number of mask(s) added: \2%d\2", u->nick, ngrname);
	} else {
		send_cmd(s_FloodServ, "NOTICE %s :GRNAME {ADD | DEL | LIST | COUNT } [real name].", u->nick);
	}
}


/*******************************************************************/
/* Handle directed set commmand for floodserv			           */
/*******************************************************************/
void do_set(User *u) {
	char *cmd;
	char *s_value;
	int16 value;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

	s_value = strtok(NULL, " ");

	if (stricmp(cmd, "WARN") == 0) {
		if (!s_value) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2WARN\2 ON/OFF", u->nick);
			return;
		}
		if (stricmp(s_value, "ON") == 0) {
			FloodServWarnFirst = 1;
			send_cmd(s_FloodServ, "NOTICE %s :\2WARN\2 now ON", u->nick);
		} else if (stricmp(s_value, "OFF") == 0) {
			FloodServWarnFirst = 0;
			send_cmd(s_FloodServ, "NOTICE %s :\2WARN\2 now OFF", u->nick);
		} else
			send_cmd(s_FloodServ, "NOTICE %s :SET \2WARN\2 ON/OFF", u->nick);
	} else if (stricmp(cmd, "TXTFLOODLINE") == 0) {
		if (!s_value) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODLINE\2 [number >0]", u->nick);
			return;
		}
		value = atoi(s_value);
		if (value<=0) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODLINE\2 [number >0]", u->nick);
			return;
		}
		FloodServTFNumLines = value;
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODLINE \2%s\2 succesfully set!", u->nick, s_value);
	} else if (stricmp(cmd, "TXTFLOODSEC") == 0) {
		if (!s_value) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODSEC\2 [number >0]", u->nick);
			return;
		}
		value = atoi(s_value);
		if (value<=0) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODSEC\2 [number >0]", u->nick);
			return;
		}
		FloodServTFSec = value;
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODSEC \2%s\2 succesfully set!", u->nick, s_value);
	} else if (stricmp(cmd, "TXTFLOODLWN") == 0) {
		if (!s_value) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODLWN\2 [number >0]", u->nick);
			return;
		}
		value = atoi(s_value);
		if (value<=0) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODLWN\2 [number >0]", u->nick);
			return;
		}
		FloodServTFNLWarned = value;
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODLWN \2%s\2 succesfully set!", u->nick, s_value);
	} else if (stricmp(cmd, "TXTFLOODWARN") == 0) {
		if (!s_value) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODWARN\2 [number >0]", u->nick);
			return;
		}
		value = atoi(s_value);
		if (value<=0) {
			send_cmd(s_FloodServ, "NOTICE %s :SET \2TXTFLOODWARN\2 [number >0]", u->nick);
			return;
		}
		FloodServTFSecWarned = value;
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODWARN \2%s\2 succesfully set!", u->nick, s_value);
	} else if (stricmp(cmd, "VIEW") == 0) {
		send_cmd(s_FloodServ, "NOTICE %s :Current setting for \2%s\2", u->nick, s_FloodServ);
		if (FloodServWarnFirst == 0)
			send_cmd(s_FloodServ, "NOTICE %s :WARN         - Warn First \2OFF\2", u->nick);
		else 
			send_cmd(s_FloodServ, "NOTICE %s :WARN         - Warn First \2ON\2", u->nick);
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODLINE - Number of lines: \2%d\2", u->nick, FloodServTFNumLines);
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODSEC  - Number of seconds: \2%d\2", u->nick, FloodServTFSec);
		send_cmd(s_FloodServ, "NOTICE %s :[%d:%d lines/seconds]", u->nick, FloodServTFNumLines, FloodServTFSec);
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODLWN  - Number of lines(warned): \2%d\2", u->nick, FloodServTFNLWarned);
		send_cmd(s_FloodServ, "NOTICE %s :TXTFLOODWARN - Number of seconds(warned): \2%d\2", u->nick, FloodServTFSecWarned);
		send_cmd(s_FloodServ, "NOTICE %s :[%d:%d lines/seconds, the real value is currently %d:%d]", u->nick, 
			FloodServTFNLWarned, FloodServTFSecWarned, FloodServTFNLWarned - FloodServTFNumLines, FloodServTFSecWarned - FloodServTFSec);
		send_cmd(s_FloodServ, "NOTICE %s :End of setting list (use SET to change them).", u->nick);
	} else {
		send_cmd(s_FloodServ, "NOTICE %s :SET {OPTION | VIEW } [value].", u->nick);
	}
}


/*******************************************************************/
/* add_chan : modify the internal channel list to protect          */
/*******************************************************************/
void add_chan(const char *channame)
{
    ChanProtected *chan;

    if (nchan >= 32767) {
	log("%s: Attempt to add a FloodServ Channel to a full list!", s_FloodServ);
	return;
    }

	if (nchan >= chan_size) {
	if (chan_size < 8)
	    chan_size = 8;
	else if (chan_size >= 16384)
	    chan_size = 32767;
	else
	    chan_size *= 2;
	chanprotected = srealloc(chanprotected, sizeof(*chanprotected) * chan_size);
    }
    chan = &chanprotected[nchan];
    chan->channame = sstrdup(channame);
    chan->TxtFlood = NULL;
   
	nchan++;
	send_cmd(s_FloodServ, "JOIN %s", channame);
}


/*******************************************************************/
/* add_grname : modify the internal grname list			           */
/*******************************************************************/
void add_grname(const char *rnmask)
{
	User *u, *next;
    GrName *gr;
	char expiry[] = "10d";
	
    if (ngrname >= 32767) {
	log("%s: Attempt to add a FloodServ GrName to a full list!", s_FloodServ);
	return;
    }

	if (ngrname >= grname_size) {
	if (grname_size < 8)
	    grname_size = 8;
	else if (grname_size >= 16384)
	    grname_size = 32767;
	else
	    grname_size *= 2;
	grnames = srealloc(grnames, sizeof(*grnames) * grname_size);
    }
    gr = &grnames[ngrname];
    gr->mask = sstrdup(rnmask);
    gr->time = time(NULL);
	gr->expires = dotime(expiry) + time(NULL);
   
	ngrname++;

	/* here, we will try to find user matching that mask....  */
	/* if there is a better way to do that, let me know -jabea */
	u = firstuser();
	while (u)
	{
		next = nextuser();
		if (stricmp(u->realname, rnmask)==0) {
			kill_user(s_FloodServ, u->nick, GrNameAkillReason);
		}
		u = next;
	}
    /* end of search */
}


/*******************************************************************/
/* del_chan : modify the internal channel list to protect          */
/*******************************************************************/
static int del_chan(const char *channame)
{
    int i;

    for (i = 0; i < nchan && strcmp(chanprotected[i].channame, channame) != 0; i++)
	;
    if (i < nchan) {
		send_cmd(NULL, ":%s PART %s", s_FloodServ, chanprotected[i].channame);
		free(chanprotected[i].channame);
		nchan--;
		if (i < nchan)
			memmove(chanprotected+i, chanprotected+i+1, sizeof(*chanprotected) * (nchan-i));
		return 1;
    } else {
		return 0;
    }
}


/*******************************************************************/
/* del_grname : modify the internal grname list			           */
/*******************************************************************/
static int del_grname(const char *rnmask)
{
    int i;

	for (i = 0; i < ngrname && stricmp(grnames[i].mask, rnmask) != 0; i++)
	;
    if (i < ngrname) {
		free(grnames[i].mask);
		ngrname--;
		if (i < ngrname)
			memmove(grnames+i, grnames+i+1, sizeof(*grnames) * (ngrname-i));
		return 1;
    } else {
		return 0;
    }
}


/*******************************************************************/
/* list_chan : list channel that floodserv know about              */
/*******************************************************************/
void list_chan(User *u)
{
	int i;

	send_cmd(s_FloodServ, "NOTICE %s :Current list of Channel monitored by FloodServ", u->nick);
	for (i = 0; i < nchan; i++) {
		send_cmd(s_FloodServ, "NOTICE %s :\2[Channel]\2 %s", u->nick, chanprotected[i].channame);
	}
}


/*******************************************************************/
/* list_grname : list grname that floodserv know about             */
/*******************************************************************/
void list_grname(User *u)
{
	int i;
	char timebuf[128];

	send_cmd(s_FloodServ, "NOTICE %s :Current GRNAME list:", u->nick);
	for (i = 0; i < ngrname; i++) {
		expires_in_lang(timebuf, sizeof(timebuf), NULL, grnames[i].expires);
		send_cmd(s_FloodServ, "NOTICE %s :\2%s\2 %s", u->nick, grnames[i].mask, timebuf);
	}
}


/*******************************************************************/
/* list_floodtxt : list all msg stored in fs (for debugging mostly)*/
/*******************************************************************/
void list_floodtxt(User *u)
{
	Flooders  *fpnt, *fnext = NULL;
	TxtFloods *pnt, *next = NULL;
	time_t now = time(NULL);
	int i;

	send_cmd(s_FloodServ, "NOTICE %s :Current list of Text/Ctcp stored by FloodServ", u->nick);
	send_cmd(s_FloodServ, "NOTICE %s :---------------------------------------------", u->nick);
	for (i = 0; i < nchan; i++) {
		send_cmd(s_FloodServ, "NOTICE %s :\2[Channel]\2 | %s |", u->nick, chanprotected[i].channame);
		for (pnt = chanprotected[i].TxtFlood; pnt; pnt = next) {
			next = pnt->next;
			if (((!pnt->warned) && (now > (pnt->time + FloodServTFSec))) ||  ((pnt->warned) && (now > (pnt->time + FloodServTFSecWarned)))) {
				send_cmd(s_FloodServ, "NOTICE %s :Text: \2%s\2 Repeated: %d *should be expired*", u->nick, pnt->txtbuffer, pnt->repeat);
			} else
				send_cmd(s_FloodServ, "NOTICE %s :Text: \2%s\2 Repeated: %d", u->nick, pnt->txtbuffer, pnt->repeat);
			
			fpnt = pnt->flooder;
			while (fpnt) {
				fnext = fpnt->next;
				send_cmd(s_FloodServ, "NOTICE %s :Said by \2%s\2 With last Nick \2%s\2", u->nick, fpnt->host, fpnt->nick);
				fpnt = fnext;
			}
		}
	}
}


/*******************************************************************/
/* rejoin_chan : rejoin chan (if kicked, or anything else          */
/*******************************************************************/
void rejoin_chan(User *u)
{
	int i;

	for (i = 0; i < nchan; i++) {
		if (!is_on_chan(s_FloodServ, chanprotected[i].channame)) {
			send_cmd(s_FloodServ, "JOIN %s", chanprotected[i].channame);
		}
	}
}


/*******************************************************************/
/* fs_add_chan : Command called from chanserv.c->do_set_floodserv  */
/*******************************************************************/
void fs_add_chan(User *u, const char *name)
{
	int i;

	for (i = 0; i < nchan; i++) {
		if(irc_stricmp(name,chanprotected[i].channame)==0) {
			if (!is_on_chan(s_FloodServ, chanprotected[i].channame)) {
				send_cmd(s_FloodServ, "JOIN %s", chanprotected[i].channame);
			}
		return;
		}
	}
	add_chan(name);
}


/*******************************************************************/
/* fs_del_chan : Command called from chanserv.c->do_set_floodserv  */
/*******************************************************************/
void fs_del_chan(User *u, const char *name)
{
	int i;

	for (i = 0; i < nchan; i++) {
		if(irc_stricmp(name,chanprotected[i].channame)==0) {
			del_chan(name);
			return;
		}
	}
}


/*******************************************************************/
/* check_channel : check if and quit any empty room                */
/*******************************************************************/
void check_channel()
{
	int i, nu, nc;
	Channel *chan;
	struct c_userlist *cu;

	nc = nchan;
	for (i = 0; i < nc; i++) {
		nu = 0;
		chan = findchan(chanprotected[i].channame);
		wallops(s_FloodServ, "Now checking channel: %s", chanprotected[i].channame);
		for (cu = chan->users; cu; cu = cu->next)
			nu++;
		wallops(s_FloodServ, "->Number of user(s): %d", nu);
		if (nu <= 1) {
			wallops(s_FloodServ, "Deleting channel: %s from %s list Reason: Channel Empty", chanprotected[i].channame, s_FloodServ);
			del_chan(chanprotected[i].channame);
		}
   	}
}


/*******************************************************************/
/* check_grname : check if we ignore that login                    */
/*******************************************************************/
int check_grname(const char *nick, const char *realname, const char *host)
{
    int i;
	char buf[BUFSIZE];
	char msg[] = "RealName Banned from the Network - for more info please email kline@insiderz.net";

    for (i = 0; i < ngrname; i++) {
		if (stricmp(grnames[i].mask, realname)==0) {
			if (grnames[i].expires && grnames[i].expires <= time(NULL)) {
				if (WallAkillExpire)
					wallops(s_OperServ, "GRNAME on %s has expired", grnames[i].mask);
				free(grnames[i].mask);
				ngrname--;
				if (i < ngrname)
					memmove(grnames+i, grnames+i+1, sizeof(*grnames) * (ngrname-i));
				i--;
			} else {
				send_cmd(s_FloodServ, "KILL %s :%s (%s)", nick, s_FloodServ, msg);
				snprintf(buf, sizeof(buf), "*@%s", host);
				add_akill(buf, msg, s_FloodServ, time(NULL) + AutokillExpiry);
				if (WallOSAkill) {
					char buffer[128];
					expires_in_lang(buffer, sizeof(buffer), NULL, time(NULL) + AutokillExpiry);
					wallops(s_OperServ, "%s added an AKILL for \2%s\2 (%s)", s_FloodServ, host, buffer);
				}
				return 1;
			}
		}
    }
    return 0;
}

/*************************************************************************/
/************************** INPUT/OUTPUT functions ***********************/
/*************************************************************************/
#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", FloodServDBName);	\
	nchan = i;					\
	break;						\
    }							\
} while (0)

void load_fs_dbase(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;

    if (!(f = open_db(s_FloodServ, FloodServDBName, "r")))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    nchan = tmp16;
    if (nchan < 8)
	chan_size = 16;
    else if (nchan >= 16384)
	chan_size = 32767;
    else
	chan_size = 2*nchan;
    chanprotected = scalloc(sizeof(*chanprotected), chan_size);

    switch (ver) {
      case 11:
	for (i = 0; i < nchan; i++) {
	    SAFE(read_string(&chanprotected[i].channame, f));
		chanprotected[i].TxtFlood = NULL;
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", FloodServDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, FloodServDBName);
    } /* switch (version) */

    close_db(f);
}

void load_grname_dbase(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;
	int32 tmp32;

    if (!(f = open_db(s_FloodServ, GrNameDBName, "r")))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    ngrname = tmp16;
    if (ngrname < 8)
	grname_size = 16;
    else if (ngrname >= 16384)
	grname_size = 32767;
    else
	grname_size = 2*nchan;
    grnames = scalloc(sizeof(*grnames), grname_size);

    switch (ver) {
      case 11:
	for (i = 0; i < ngrname; i++) {
	    SAFE(read_string(&grnames[i].mask, f));
		SAFE(read_int32(&tmp32, f));
	    grnames[i].time = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    grnames[i].expires = tmp32;
	}
	break;

      case -1:
	fatal("Unable to read version number from %s", GrNameDBName);

      default:
	fatal("Unsupported version (%d) on %s", ver, GrNameDBName);
    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do { if ((x) < 0) goto fail; } while (0)

void save_fs_dbase(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db(s_FloodServ, FloodServDBName, "w");
    write_int16(nchan, f);
    for (i = 0; i < nchan; i++) {
	SAFE(write_string(chanprotected[i].channame, f));
	}
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", FloodServDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", FloodServDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

void save_grname_dbase(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db(s_FloodServ, GrNameDBName, "w");
    write_int16(ngrname, f);
    for (i = 0; i < ngrname; i++) {
	SAFE(write_string(grnames[i].mask, f));
	SAFE(write_int32(grnames[i].time, f));
	SAFE(write_int32(grnames[i].expires, f));
	}
    close_db(f);
    return;

  fail:
    restore_db(f);
    log_perror("Write error on %s", GrNameDBName);
    if (time(NULL) - lastwarn > WarningTimeout) {
	wallops(NULL, "Write error on %s: %s", GrNameDBName,
		strerror(errno));
	lastwarn = time(NULL);
    }
}

#undef SAFE

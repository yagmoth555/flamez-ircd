/* Online user data structure.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef USERS_H
#define USERS_H

/*************************************************************************/

struct user_ {
    User *next, *prev;
    char nick[NICKMAX];
    NickInfo *ni;			/* Effective NickInfo (not a link) */
    NickInfo *real_ni;			/* Real NickInfo (ni.nick==user.nick)*/
    Server *server;			/* Server user is on */
    char *username;
    char *host;				/* User's hostname */
    char *realname;
#ifdef IRC_UNREAL
    char *fakehost;			/* Hostname seen by other users */
#endif
    time_t signon;			/* Timestamp sent with nick when we
    					 *    first saw it.  Never changes! */
    time_t my_signon;			/* When did _we_ see the user with
    					 *    their current nickname? */
    uint32 services_stamp;		/* ID value for user; used in split
					 *    recovery */
    int32 mode;				/* UMODE_* user modes */
    struct u_chanlist {
	struct u_chanlist *next, *prev;
	Channel *chan;
    } *chans;				/* Channels user has joined */
    struct u_chaninfolist {
	struct u_chaninfolist *next, *prev;
	ChannelInfo *chan;
    } *founder_chans;			/* Channels user has identified for */
    short invalid_pw_count;		/* # of invalid password attempts */
    time_t invalid_pw_time;		/* Time of last invalid password */
    time_t lastmemosend;		/* Last time MS SEND command used */
    time_t lastnickreg;			/* Last time NS REGISTER cmd used */
};

/*************************************************************************/

#endif /* USERS_H */

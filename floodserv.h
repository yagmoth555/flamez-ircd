/* FloodServ structures.
 *
 * Add an way to break flood attack,
 * -primary by checking flood from channel from a nick
 * -or from a host
 * Copyright (c) 2001 Philippe Levesque <EMail: yagmoth555@yahoo.com>
 * See www.flamez.net for more info
 */

#ifndef FLOODSERV_H
#define FLOODSERV_H

/* Default value for the text-flood
 * 5 lines in 5 sec seem a good value =] -jabea.
 *
#define TXTFLOOD_LINE	5		Numeric value representing the number(s) of line(s) writted
#define TXTFLOOD_SEC	5		Numeric value representating the second(s)
#define TXTFLOOD_LWN	7   	Numeric value representing the number(s) of line(s) writted
#define TXTFLOOD_WARN  20		Numeric value representating the second(s)
*/

typedef struct chanprotected_ ChanProtected;
typedef struct txtflood_ TxtFloods;
typedef struct flooder_ Flooders;

struct flooder_ {
		Flooders *next;
		char nick[NICKMAX];			/* The *first nick* from the host we stopped on */
		char *host;					/* From what host he's on */
		int	 akilled;				/* AKILLED? */
};

struct txtflood_ {
		TxtFloods *next, *prev;
		Flooders *flooder;			/* Who triggered it [key of the struct] */
		char *txtbuffer;			/* TEXT / CTCP */
		time_t time;				/* When the txt was last said */
		int repeat;					/* How many time */
		int warned;					/* WARNED? */
};

struct chanprotected_ {
	char *channame;			/* Channel to watch */
	TxtFloods *TxtFlood;
};


typedef struct grname GrName;
struct grname {
    char *mask;
    char *reason;
    char who[NICKMAX];
    time_t time;
	time_t expires;
};

/*
some setting that i will maybe code l33ter
#define WARNNINGPSYCHO	0		/0/1 - Psycho setting, if 1, floodserv will akill any person(s)
								   that told the same txt trigger that floodserv warned on
#define CHANBITCH		1		After 1 warn, if someone else trigger a flood, it got akilled rigth now,
								   multiple flood from other nick is seen here as an takeover attempt.
#define CHANBITCHTIME	100		Time in milliseconds
*/

#endif	/* FLOODSERV_H */

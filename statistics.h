/* Statistical information.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef STATISTICS_H
#define STATISTICS_H

typedef struct minmax_ MinMax;
struct minmax_ {
        int min, max;
	time_t mintime, maxtime;
};

typedef struct minmaxhistory_ MinMaxHistory;
struct minmaxhistory_ {
        MinMax hour, today, week, month, ever;
};

struct serverstats_ {
    ServerStats *next, *prev;	/* Use to navigate the entire server list */
    ServerStats *hub;		/* Hub's statistics data (FIXME: unneeded?) */

    char *name;                 /* Server's name */

#if 0
    MinMaxHistory mm_users;
    MinMaxHistory mm_opers;
#endif

    int usercnt;		/* Current number of users on server */
    int opercnt;		/* Current number of opers on server */

    time_t t_join;		/* Time server joined us. 0 == not here. */
    time_t t_quit;		/* Time server quit. */

    char *quit_message;		/* Server's last quit message */

#if 0
    int indirectsplits;         /* Times this server has split from view due to
                                 * a split between two downstream servers. */
    int directsplits;           /* Times this server has split from view due to
                                 * a split between it and its hub. */
#endif
};

#endif	/* STATISTICS_H */

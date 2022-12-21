/* Online server data.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef SERVERS_H
#define SERVERS_H

/*************************************************************************/

struct server_ {
    Server *next, *prev;        /* Use to navigate the entire server list */
    Server *hub;
    Server *child, *sibling;

    char *name;                 /* Server's name */
    time_t t_join;		/* Time server joined us. 0 == not here. */

#ifdef STATISTICS
    ServerStats *stats;
#endif
};

/*************************************************************************/

#endif	/* SERVERS_H */

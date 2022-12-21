/* Time-delay routine include stuff.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <time.h>


/* Definitions for timeouts: */
typedef struct timeout_ Timeout;
struct timeout_ {
    Timeout *next, *prev;
    time_t settime;		/* Time timer was set (from time()) */
    uint32 timeout;		/* In milliseconds (time_msec()) */
    int repeat;			/* Does this timeout repeat indefinitely? */
    void (*code)(Timeout *);	/* This structure is passed to the code */
    void *data;			/* Can be anything */
};


/* Check the timeout list for any pending actions. */
extern void check_timeouts(void);

/* Add a timeout to the list to be triggered in `delay' seconds.  Any
 * timeout added from within a timeout routine will not be checked during
 * that run through the timeout list.  Always succeeds.
 */
extern Timeout *add_timeout(int delay, void (*code)(Timeout *), int repeat);

/* Add a timeout to the list to be triggered in `delay' milliseconds. */
extern Timeout *add_timeout_ms(uint32 delay, void (*code)(Timeout *),
			       int repeat);

/* Remove a timeout from the list (if it's there). */
extern void del_timeout(Timeout *t);

#ifdef DEBUG_COMMANDS
/* Send the list of timeouts to the given user. */
extern void send_timeout_list(User *u);
#endif


#endif	/* TIMEOUT_H */

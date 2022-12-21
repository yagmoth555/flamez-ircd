/* News data structures and constants.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef NEWS_H
#define NEWS_H

/*************************************************************************/

typedef struct newsitem_ NewsItem;
struct newsitem_ {
    int16 type;
    int32 num;		/* Numbering is separate for login and oper news */
    char *text;
    char who[NICKMAX];
    time_t time;
};

/*************************************************************************/

/* Constants for news types. */

#define NEWS_LOGON	0
#define NEWS_OPER	1

/*************************************************************************/

#endif  /* NEWS_H */

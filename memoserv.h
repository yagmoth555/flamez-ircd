/* MemoServ-related structures.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef MEMOSERV_H
#define MEMOSERV_H

/* Memo info structures.  Since both nicknames and channels can have memos,
 * we encapsulate memo data in a MemoList to make it easier to handle. */

typedef struct {
    uint32 number;	/* Index number -- not necessarily array position! */
    int16 flags;
    time_t time;	/* When it was sent */
    char sender[NICKMAX];
    char *text;
} Memo;

#define MF_UNREAD	0x0001	/* Memo has not yet been read */

struct memoinfo_ {
    int16 memocount, memomax;
    Memo *memos;
};

#endif	/* MEMOSERV_H */

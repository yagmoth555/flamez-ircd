/* ChanServ-related structures.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef CHANSERV_H
#define CHANSERV_H

#ifndef MEMOSERV_H
# include "memoserv.h"
#endif


/* Access levels for users. */
typedef struct {
    int16 in_use;	/* 1 if this entry is in use, else 0 */
    int16 level;
    NickInfo *ni;	/* Guaranteed to be non-NULL if in use, NULL if not */
} ChanAccess;

/* Note that these two levels also serve as exclusive boundaries for valid
 * access levels.  ACCLEV_FOUNDER may be assumed to be strictly greater
 * than any valid access level, and ACCLEV_INVALID may be assumed to be
 * strictly less than any valid access level.
 */
#define ACCLEV_FOUNDER	10000	/* Numeric level indicating founder access */
#define ACCLEV_INVALID	-10000	/* Used in levels[] for disabled settings */

/* Access levels used to represent AOP's, SOP's and VOP's in channel access
 * lists. */

#define ACCLEV_SOP	10
#define ACCLEV_AOP	5
#define ACCLEV_VOP	3
#ifdef HAVE_HALFOP
# define ACCLEV_HOP	4
#endif


/* AutoKick data. */
typedef struct {
    int16 in_use;
    int16 is_nick;	/* 1 if a regged nickname, 0 if a nick!user@host mask */
			/* Always 0 if not in use */
    union {
	char *mask;	/* Guaranteed to be non-NULL if in use, NULL if not */
	NickInfo *ni;	/* Same */
    } u;
    char *reason;
    char who[NICKMAX];
} AutoKick;


struct chaninfo_ {
    ChannelInfo *next, *prev;
    char name[CHANMAX];
    NickInfo *founder;
    NickInfo *successor;		/* Who gets the channel if the founder
					 * nick is dropped or expires */
    char founderpass[PASSMAX];
    char *desc;
    char *url;
    char *email;

    time_t time_registered;
    time_t last_used;
    char *last_topic;		/* Last topic on the channel */
    char last_topic_setter[NICKMAX];	/* Who set the last topic */
    time_t last_topic_time;	/* When the last topic was set */

    int32 flags;		/* See below */
    SuspendInfo *suspendinfo;	/* Non-NULL iff suspended */

    int16 *levels;		/* Access levels for commands */

    int16 accesscount;
    ChanAccess *access;		/* List of authorized users */
    int16 akickcount;
    AutoKick *akick;		/* List of users to kickban */

    int32 mlock_on, mlock_off;	/* See channel modes below */
    int32 mlock_limit;		/* 0 if no limit */
    char *mlock_key;		/* NULL if no key */

    char *entry_message;	/* Notice sent on entering channel */

    MemoInfo memos;

    struct channel_ *c;		/* Pointer to channel record (if   *
				 *    channel is currently in use) */

    int bad_passwords;		/* # of bad passwords since last good one */
};

/* Retain topic even after last person leaves channel */
#define CI_KEEPTOPIC	0x00000001
/* Don't allow non-authorized users to be opped */
#define CI_SECUREOPS	0x00000002
/* Hide channel from ChanServ LIST command */
#define CI_PRIVATE	0x00000004
/* Topic can only be changed by SET TOPIC */
#define CI_TOPICLOCK	0x00000008
/* Those not allowed ops are kickbanned */
#define CI_RESTRICTED	0x00000010
/* Don't auto-deop anyone */
#define CI_LEAVEOPS	0x00000020
/* Don't allow any privileges unless a user is IDENTIFY'd with NickServ */
#define CI_SECURE	0x00000040
/* Don't allow the channel to be registered or used */
#define CI_VERBOTEN	0x00000080
/* Channel password is encrypted */
#define CI_ENCRYPTEDPW	0x00000100
/* Channel does not expire */
#define CI_NOEXPIRE	0x00000200
/* Channel memo limit may not be changed */
#define CI_MEMO_HARDMAX	0x00000400
/* Send notice to channel on use of OP/DEOP */
#define CI_OPNOTICE	0x00000800
/* Enforce +o, +v modes (don't allow deopping) */
#define CI_ENFORCE	0x00001000

/* Indices for cmd_access[]: (DO NOT REORDER THESE unless you hack
 * load_cs_dbase to deal with them) */
#define CA_INVITE	0
#define CA_AKICK	1
#define CA_SET		2	/* but not FOUNDER or PASSWORD */
#define CA_UNBAN	3
#define CA_AUTOOP	4
#define CA_AUTODEOP	5	/* Maximum, not minimum */
#define CA_AUTOVOICE	6
#define CA_OPDEOP	7	/* ChanServ commands OP and DEOP */
#define CA_ACCESS_LIST	8
#define CA_CLEAR	9
#define CA_NOJOIN	10	/* Maximum */
#define CA_ACCESS_CHANGE 11
#define CA_MEMO		12
#define CA_VOICE	13	/* VOICE/DEVOICE commands */
#define CA_AUTOHALFOP	14
#define CA_HALFOP	15	/* HALFOP/DEHALFOP commands */
#define CA_AUTOPROTECT	16
#define CA_PROTECT	17

#define CA_SIZE		18


#endif	/* CHANSERV_H */

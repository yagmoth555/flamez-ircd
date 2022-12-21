/* Convert other programs' databases to Services format.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "datafiles.h"

/*************************************************************************/

struct akill {
    char *mask;
    char *reason;
    char who[NICKMAX];
    time_t time;
    time_t expires;
};
typedef struct {
    int16 type;
    int32 num;
    char *text;
    char who[NICKMAX];
    time_t time;
} NewsItem;
typedef struct {
    char *mask;			/* Hosts to which this exception applies */
    int16 limit;		/* Session limit for exception */
    char who[NICKMAX];		/* Nick of person who added the exception */
    char *reason;		/* Reason for exception's addition */
    time_t time;		/* When this exception was added */
    time_t expires;		/* Time when it expires. 0 == no expiry */
    int num;			/* Position in exception list */
} Exception;

/* All this is initialized to zeros */
NickInfo *nicklists[256];
ChannelInfo *chanlists[256];
NickInfo *services_admins[MAX_SERVADMINS];
NickInfo *services_opers[MAX_SERVOPERS];
int nakill;
struct akill *akills;
int nexceptions;
Exception *exceptions;
int nnews;
NewsItem *news;
int32 maxusercnt;
time_t maxusertime;
char supass[PASSMAX];
int no_supass = 1;

int32 char_modes[256] = {
    ['i'] = CMODE_i,
    ['m'] = CMODE_m,
    ['n'] = CMODE_n,
    ['p'] = CMODE_p,
    ['s'] = CMODE_s,
    ['t'] = CMODE_t,
    ['k'] = CMODE_k,
    ['l'] = CMODE_l,
#ifdef IRC_DAL4_4_15
    ['R'] = CMODE_R,
#endif
#if defined(IRC_BAHAMUT) || defined(IRC_UNREAL)
    ['c'] = CMODE_c,
    ['O'] = CMODE_O,
#endif
#ifdef IRC_UNREAL
    ['A'] = CMODE_A,
    ['z'] = CMODE_z,
    ['Q'] = CMODE_Q,
    ['K'] = CMODE_K,
    ['V'] = CMODE_V,
    ['H'] = CMODE_H,
    ['C'] = CMODE_C,
    ['N'] = CMODE_N,
    ['S'] = CMODE_S,
    ['G'] = CMODE_G,
    ['u'] = CMODE_u,
    ['f'] = CMODE_f,
#endif
#ifdef IRC_BAHAMUT
    ['M'] = CMODE_M,
#endif
};

/*************************************************************************/
/*************************************************************************/

/* Open a (Services-style) data file and check the version number.  Prints
 * an error message and exits with 1 if either the file cannot be opened or
 * the version number is wrong.  If `version_ret' is non-NULL, the version
 * number is stored there.
 */

dbFILE *open_db_ver(const char *dir, const char *name, int32 min_version,
		    int32 max_version, int32 *version_ret)
{
    char filename[PATH_MAX+1];
    dbFILE *f;
    int32 ver;

    snprintf(filename, sizeof(filename), "%s/%s", dir, name);
    f = open_db(NULL, filename, "r");
    if (!f) {
	fprintf(stderr, "Can't open %s for ", filename);
	perror("reading");
	exit(1);
    }
    if (read_int32(&ver, f) < 0) {
	fprintf(stderr, "Error reading version number on %s\n", filename);
	exit(1);
    }
    if (ver < min_version || ver > max_version) {
	fprintf(stderr, "Wrong version number on %s\n", filename);
	exit(1);
    }
    if (version_ret)
	*version_ret = ver;
    return f;
}

/*************************************************************************/

/* Generic routine to make a backup copy of a file. */

void make_backup(const char *name)
{
    char outname[PATH_MAX+1], buf[65536];
    FILE *in, *out;
    int n;

    snprintf(outname, sizeof(outname), "%s~", name);
    if (strcmp(outname, name) == 0) {
	fprintf(stderr, "Can't back up %s: Path too long\n", name);
	exit(1);
    }
    in = fopen(outname, "rb");
    if (in) {
	/* Don't overwrite an already-existing backup file */
	fclose(in);
	return;
    }
    in = fopen(name, "rb");
    if (!in) {
	if (errno == ENOENT) {
	    /* No file to back up, so just leave */
	    return;
	}
	fprintf(stderr, "Can't open %s for ", name);
	perror("reading");
	exit(1);
    }
    out = fopen(outname, "wb");
    if (!out) {
	fprintf(stderr, "Can't open %s for ", outname);
	perror("writing");
	exit(1);
    }
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
	if (fwrite(buf, 1, n, out) != n) {
	    fprintf(stderr, "Write error on ");
	    perror(outname);
	    exit(1);
	}
    }
    fclose(in);
    fclose(out);
}

/*************************************************************************/

/* Find a nickname or channel. */

NickInfo *findnick(const char *nick)
{
    NickInfo *ni;

    for (ni = nicklists[irc_tolower(*nick)]; ni; ni = ni->next) {
	if (stricmp(ni->nick, nick) == 0)
	    return ni;
    }
    return NULL;
}


ChannelInfo *cs_findchan(const char *chan)
{
    ChannelInfo *ci;

    for (ci = chanlists[irc_tolower(chan[1])]; ci; ci = ci->next) {
	if (stricmp(ci->name, chan) == 0)
	    return ci;
    }
    return NULL;
}

/*************************************************************************/

/* Add a nickname or channel to the appropriate list. */

void addnick(NickInfo *ni)
{
    int hash = irc_tolower(*ni->nick);

    ni->next = nicklists[hash];
    if (ni->next)
	ni->next->prev = ni;
    nicklists[hash] = ni;
}


void addchan(ChannelInfo *ci)
{
    int hash = irc_tolower(ci->name[1]);

    ci->next = chanlists[hash];
    if (ci->next)
	ci->next->prev = ci;
    chanlists[hash] = ci;
}

/*************************************************************************/

/* Adding stuff to Services admin/oper lists. */

#define ADD_ADMIN	0
#define ADD_OPER	1

static int counts[2] = {0,0};
static int maxes[2] = {MAX_SERVADMINS,MAX_SERVOPERS};
static NickInfo **lists[2] = {services_admins,services_opers};

void add_adminoper(int which, const char *nick)
{
    if (!nick)
	return;
    if (counts[which] < maxes[which]) {
	NickInfo *ni = findnick(nick);
	if (ni)
	    lists[which][counts[which]++] = ni;
    } else if (counts[which] == maxes[which]) {
	fprintf(stderr, "Warning: too many Services %s (maximum %d).\n",
		which==ADD_ADMIN ? "admins" : "opers", maxes[which]);
	counts[which]++;
    }
}

/*************************************************************************/

/* Safe memory allocation.  We also clear the memory just to be clean. */

void *smalloc(long size)
{
    void *ptr;
    if (!size)
	size = 1;
    ptr = malloc(size);
    if (!ptr) {
	fprintf(stderr, "Out of memory\n");
	exit(1);
    }
    memset(ptr, 0, size);
    return ptr;
}

#define scalloc(a,b) smalloc((a)*(b))

/*************************************************************************/

/* Initialize channel levels. */

void init_levels(ChannelInfo *ci)
{
    ci->levels = smalloc(CA_SIZE * sizeof(*ci->levels));
    ci->levels[CA_AUTOOP]	=  5;
    ci->levels[CA_AUTOVOICE]	=  3;
    ci->levels[CA_AUTODEOP]	= -1;
    ci->levels[CA_NOJOIN]	= -1;
    ci->levels[CA_INVITE]	=  5;
    ci->levels[CA_AKICK]	= 10;
    ci->levels[CA_SET]		= ACCLEV_INVALID;
    ci->levels[CA_CLEAR]	= ACCLEV_INVALID;
    ci->levels[CA_UNBAN]	=  5;
    ci->levels[CA_OPDEOP]	=  5;
    ci->levels[CA_ACCESS_LIST]	=  0;
    ci->levels[CA_ACCESS_CHANGE]=  1;
    ci->levels[CA_MEMO]		= 10;
    ci->levels[CA_VOICE]	=  3;
    ci->levels[CA_AUTOHALFOP]	=  4;
    ci->levels[CA_HALFOP]	=  4;
    ci->levels[CA_AUTOPROTECT]	= 10;
    ci->levels[CA_PROTECT]	= 10;
}

/*************************************************************************/
/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	fprintf(stderr, "Read error on %s\n", f->filename);	\
	exit(1);						\
    }								\
} while (0)

/*************************************************************************/
/************* Database loading: Magick 1.4b2 / Wrecked 1.2 **************/
/*************************************************************************/

static void m14_load_nick(const char *sourcedir, int32 version)
{
    char *s;
    dbFILE *f;
    int i, j;
    NickInfo *ni, *ni2, **last, *prev;
    struct oldni_ {
	struct oldni_ *next, *prev;
	char nick[32];
	char pass[32];
	char *email;
	char *url;
	char *usermask;
	char *realname;
	time_t reg;
	time_t seen;
	long naccess;
	char **access;
	long nignore;
	char **ignore;
	long flags;
	long resv[4];
    } oldni;

    f = open_db_ver(sourcedir, "nick.db", version, version, NULL);
    for (i = 33; i < 256; i++) {
	last = &nicklists[i];
	prev = NULL;
	while (getc_db(f)) {
	    SAFE(read_variable(oldni, f));
	    if (version == 6) {
		time_t last_signon;
		long uin;
		SAFE(read_variable(last_signon, f));
		SAFE(read_variable(uin, f));
	    }
	    if (oldni.email)
		SAFE(read_string(&oldni.email, f));
	    if (oldni.url)
		SAFE(read_string(&oldni.url, f));
	    SAFE(read_string(&oldni.usermask, f));
	    SAFE(read_string(&oldni.realname, f));
	    ni = smalloc(sizeof(*ni));
	    ni->next = NULL;
	    ni->prev = prev;
	    *last = ni;
	    last = &(ni->next);
	    prev = ni;
	    strscpy(ni->nick, oldni.nick, NICKMAX);
	    strscpy(ni->pass, oldni.pass, PASSMAX);
	    ni->url = oldni.url;
	    ni->email = oldni.email;
	    ni->last_usermask = oldni.usermask;
	    ni->last_realname = oldni.realname;
	    ni->last_quit = NULL;
	    ni->time_registered = oldni.reg;
	    ni->last_seen = oldni.seen;
	    ni->link = NULL;
	    ni->linkcount = 0;
	    ni->accesscount = oldni.naccess;
	    ni->memos.memocount = 0;
	    ni->memos.memomax = MSMaxMemos;
	    ni->memos.memos = NULL;
	    ni->channelcount = 0;
	    ni->channelmax = CSMaxReg;
	    ni->language = DEF_LANGUAGE;
	    ni->status = 0;
	    ni->flags = 0;
	    if (version == 5)
		oldni.flags &= 0x000000FF;
	    if (oldni.flags & 0x00000001)
		ni->flags |= NI_KILLPROTECT;
	    if (oldni.flags & 0x00000002)
		ni->flags |= NI_SECURE;
	    if (oldni.flags & 0x00000004)
		ni->status |= NS_VERBOTEN;
	    if (oldni.flags & 0x00004008)
		ni->status |= NS_NOEXPIRE;
	    if (oldni.flags & 0x00000010)
		ni->flags |= NI_PRIVATE;
	    if (oldni.flags & 0x00000020) {
		ni->suspendinfo = smalloc(sizeof(SuspendInfo));
		strcpy(ni->suspendinfo->who, "<unknown>");
		ni->suspendinfo->reason = "Unknown (imported from Wrecked IRC Services)";
		ni->suspendinfo->suspended = time(NULL);
		ni->suspendinfo->expires = 0;
	    }
	    if (oldni.flags & 0x00000080)
		ni->link = (NickInfo *) -1;  /* Flag: this is a linked nick */
	    if (oldni.flags & 0x00000100)
		ni->memos.memomax = 0;
	    if (oldni.flags & 0x00000200)
		ni->flags |= NI_HIDE_EMAIL;
	    if (ni->accesscount > NSAccessMax)
		ni->accesscount = NSAccessMax;
	    ni->access = smalloc(ni->accesscount * sizeof(char *));
	    for (j = 0; j < ni->accesscount; j++)
		SAFE(read_string(&ni->access[j], f));
	    while (j++ < oldni.naccess)
		SAFE(read_string(&s, f));
	    for (j = 0; j < oldni.nignore; j++)
		SAFE(read_string(&s, f));
	}
    }
    close_db(f);
    /* Resolve links */
    for (i = 33; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    if (ni->link) {
		int c = (unsigned char) irc_tolower(ni->last_usermask[0]);
		for (ni2 = nicklists[c]; ni2; ni2 = ni2->next) {
		    if (stricmp(ni2->nick, ni->last_usermask) == 0)
			break;
		}
		if (ni2) {
		    ni->link = ni2;
		    strscpy(ni->pass, ni2->pass, PASSMAX);
		} else {
		    fprintf(stderr, "Warning: dropping nick %s linked to nonexistent nick %s\n",
				ni->nick, ni->last_usermask);
		    if (ni->prev)
			ni->prev->next = ni->next;
		    else
			nicklists[i] = ni->next;
		    if (ni->next)
			ni->next->prev = ni->prev;
		}
		ni->last_usermask = NULL;
	    }
	}
    }
}

/*************************************************************************/

static void m14_load_chan(const char *sourcedir, int32 version)
{
    char *s;
    dbFILE *f;
    int i, j, reasoncount = 0;
    int16 tmp16;
    ChannelInfo *ci, **last, *prev;
    struct access_ {
	short level;
	short is_nick;
	char *name;
    } access;
    struct akick_ {
	short is_nick;
	short pad;
	char *name;
	char *reason;
    } akick;
    struct oldci_ {
	struct oldci_ *next, *prev;
	char name[64];
	char founder[32];
	char pass[32];
	char *desc;
	char *url;
	time_t reg;
	time_t used;
	long naccess;
	struct access_ *access;
	long nakick;
	struct akick_ *akick;
	char mlock_on[64], mlock_off[64];
	long mlock_limit;
	char *mlock_key;
	char *topic;
	char topic_setter[32];
	time_t topic_time;
	long flags;
	short *levels;
	long resv[3];
    } oldci;

    f = open_db_ver(sourcedir, "chan.db", version, version, NULL);
    for (i = 33; i < 256; i++) {
	last = &chanlists[i];
	prev = NULL;
	while (getc_db(f)) {
	    SAFE(read_variable(oldci, f));
	    SAFE(read_string(&oldci.desc, f));
	    if (oldci.url)
		SAFE(read_string(&oldci.url, f));
	    if (oldci.mlock_key)
		SAFE(read_string(&oldci.mlock_key, f));
	    if (oldci.topic)
		SAFE(read_string(&oldci.topic, f));
	    ci = smalloc(sizeof(*ci));
	    strscpy(ci->name, oldci.name, CHANMAX);
	    ci->founder = findnick(oldci.founder);
	    strscpy(ci->founderpass, oldci.pass, PASSMAX);
	    ci->desc = oldci.desc;
	    ci->url = oldci.url;
	    ci->time_registered = oldci.reg;
	    ci->last_used = oldci.used;
	    ci->accesscount = oldci.naccess;
	    ci->akickcount = oldci.nakick;
	    ci->mlock_limit = oldci.mlock_limit;
	    ci->mlock_key = oldci.mlock_key;
	    ci->last_topic = oldci.topic;
	    strscpy(ci->last_topic_setter, oldci.topic_setter, NICKMAX);
	    ci->last_topic_time = oldci.topic_time;
	    ci->memos.memocount = 0;
	    ci->memos.memomax = MSMaxMemos;
	    ci->memos.memos = NULL;
	    if (version == 5)
		oldci.flags &= 0x000003FF;
	    ci->flags = oldci.flags & 0x000000FF;
	    if (oldci.flags & 0x00000100) {
		ci->suspendinfo = smalloc(sizeof(SuspendInfo));
		strcpy(ci->suspendinfo->who, "<unknown>");
		ci->suspendinfo->reason =
		    version==6 ? "Unknown (imported from Wrecked IRC Services)"
		               : "Unknown (imported from Magick IRC Services)";
		ci->suspendinfo->suspended = time(NULL);
		ci->suspendinfo->expires = 0;
	    }
	    if (oldci.flags & 0x00000400)
		ci->flags |= CI_NOEXPIRE;
	    for (s = oldci.mlock_on; *s; s++)
		ci->mlock_on |= char_modes[(unsigned char)*s];
	    for (s = oldci.mlock_off; *s; s++)
		ci->mlock_off |= char_modes[(unsigned char)*s];
	    if (oldci.naccess > CSAccessMax)
		ci->accesscount = CSAccessMax;
	    else
		ci->accesscount = oldci.naccess;
	    if (oldci.nakick > CSAutokickMax)
		ci->akickcount = CSAutokickMax;
	    else
		ci->akickcount = oldci.nakick;
	    ci->access = smalloc(sizeof(ChanAccess) * ci->accesscount);
	    for (j = 0; j < oldci.naccess; j++) {
		SAFE(read_variable(access, f));
		if (j < ci->accesscount) {
		    ci->access[j].in_use = (access.is_nick == 1);
		    ci->access[j].level = access.level;
		}
	    }
	    for (j = 0; j < oldci.naccess; j++) {
		SAFE(read_string(&s, f));
		if (!s)
		    continue;
		if (j < ci->accesscount && ci->access[j].in_use) {
		    ci->access[j].ni = findnick(s);
		    if (!ci->access[j].ni)
			ci->access[j].in_use = 0;
		}
	    }
	    ci->akick = smalloc(sizeof(AutoKick) * ci->akickcount);
	    for (j = 0; j < oldci.nakick; j++) {
		SAFE(read_variable(akick, f));
		if (j < ci->akickcount) {
		    if (access.is_nick >= 0) {
			ci->akick[j].in_use = 1;
			ci->akick[j].is_nick = akick.is_nick;
		    } else {
			ci->akick[j].in_use = 0;
			ci->akick[j].is_nick = 0;
		    }
		    ci->akick[j].reason = akick.reason;
		} else if (akick.reason) {
		    reasoncount++;
		}
	    }
	    for (j = 0; j < oldci.nakick; j++) {
		SAFE(read_string(&s, f));
		if (s) {
		    if (j < ci->akickcount && ci->akick[j].in_use) {
			if (ci->akick[j].is_nick) {
			    ci->akick[j].u.ni = findnick(s);
			    if (!ci->akick[j].u.ni) {
				ci->akick[j].in_use = 0;
				ci->akick[j].is_nick = 0;
			    }
			} else {
			    ci->akick[j].u.mask = s;
			}
		    }
		}
		if (j < ci->akickcount && ci->akick[j].reason) {
		    SAFE(read_string(&ci->akick[j].reason, f));
		    if (!ci->akick[j].in_use && ci->akick[j].reason)
			ci->akick[j].reason = NULL;
		}
	    }
	    for (j = 0; j < reasoncount; j++)
		SAFE(read_string(&s, f));
	    ci->levels = smalloc(CA_SIZE * sizeof(*ci->levels));
	    init_levels(ci);
	    if (oldci.levels) {
		SAFE(read_int16(&tmp16, f));
		for (j = 0; j < tmp16; j++) {
		    short lev;
		    SAFE(read_variable(lev, f));
		    if (j < 100) switch (version*100+j) {
			case 500: ci->levels[CA_AUTODEOP]      = lev; break;
			case 501: ci->levels[CA_AUTOVOICE]     = lev; break;
			case 502: ci->levels[CA_AUTOOP]        = lev; break;
			case 506: ci->levels[CA_AKICK]         = lev; break;
			case 509: ci->levels[CA_ACCESS_CHANGE] = lev; break;
			case 510: ci->levels[CA_SET]           = lev; break;
			case 511: ci->levels[CA_INVITE]        = lev; break;
			case 512: ci->levels[CA_UNBAN]         = lev; break;
			case 514: ci->levels[CA_OPDEOP]        = lev; break;
			case 515: ci->levels[CA_CLEAR]         = lev; break;

			case 600: ci->levels[CA_AUTODEOP]      = lev;
			          break;
			case 601: ci->levels[CA_AUTOVOICE]     = lev;
			          ci->levels[CA_VOICE]         = lev;
			          ci->levels[CA_INVITE]        = lev;
			          ci->levels[CA_UNBAN]         = lev;
			          ci->levels[CA_ACCESS_LIST]   = lev;
			          break;
			case 602: ci->levels[CA_AUTOHALFOP]    = lev;
			          ci->levels[CA_HALFOP]        = lev;
			          break;
			case 603: ci->levels[CA_AUTOOP]        = lev;
			          ci->levels[CA_OPDEOP]        = lev;
			          break;
			case 604: ci->levels[CA_AKICK]         = lev;
			          ci->levels[CA_SET]           = lev;
			          ci->levels[CA_CLEAR]         = lev;
			          ci->levels[CA_ACCESS_CHANGE] = lev;
			          ci->levels[CA_AUTOPROTECT]   = lev;
			          ci->levels[CA_PROTECT]       = lev;
			          break;
		    } /* switch (version*100+j) */
		} /* for (j) */
	    } /* if (oldci.levels) */
	    if (oldci.flags & 0x00002000)
		ci->levels[CA_AUTOVOICE] = 0;
	    /* Only insert in list if founder is found */
	    if (ci->founder) {
		ci->prev = prev;
		ci->next = NULL;
		*last = ci;
		last = &(ci->next);
		prev = ci;
	    } else {
		/* Yeah, it's a memory leak, I know.  Shouldn't matter for
		 * this program. */
	    }
	} /* while more entries */
    } /* for 33..256 */
    close_db(f);
}

/*************************************************************************/

static void m14_load_memo(const char *sourcedir, int32 version)
{
    char *s;
    dbFILE *f;
    struct memo_ {
	char sender[32];
	long number;
	time_t time;
	char *text;
	long resv[4];
    } memo;
    struct memolist_ {
	struct memolist_ *next, *prev;
	char nick[32];
	long n_memos;
	Memo *memos;
	long resv[4];
    } memolist;
    NickInfo *ni;
    Memo *m = NULL;
    int i, j;
    long flags = 0;

    f = open_db_ver(sourcedir, "memo.db", version, version, NULL);
    for (i = 33; i < 256; i++) {
	while (getc_db(f)) {
	    SAFE(read_variable(memolist, f));
	    ni = findnick(memolist.nick);
	    if (ni) {
		ni->memos.memocount = memolist.n_memos;
		m = smalloc(sizeof(Memo) * ni->memos.memocount);
		ni->memos.memos = m;
	    }
	    for (j = 0; j < memolist.n_memos; j++) {
		SAFE(read_variable(memo, f));
		if (version == 6) {
		    SAFE(read_variable(flags, f));
		    flags = memo.resv[0] & 1;
		}
		if (ni) {
		    m[j].number = memo.number;
		    m[j].flags = flags;
		    m[j].time = memo.time;
		    strscpy(m[j].sender, memo.sender, NICKMAX);
		}
	    }
	    for (j = 0; j < memolist.n_memos; j++) {
		SAFE(read_string(&s, f));
		if (ni)
		    m[j].text = s;
	    }
	}
    }
    close_db(f);
}

/*************************************************************************/

static void m14_load_sop(const char *sourcedir, int32 version)
{
    char buf[32];
    dbFILE *f;
    int16 n, i;

    f = open_db_ver(sourcedir, "sop.db", version, version, NULL);
    SAFE(read_int16(&n, f));
    if (n > MAX_SERVOPERS)
	n = MAX_SERVOPERS;
    for (i = 0; i < n; i++) {
	SAFE(read_buffer(buf, f));
	add_adminoper(ADD_OPER, buf);
    }
    close_db(f);
}

/*************************************************************************/

static void m14_load_akill(const char *sourcedir, int32 version)
{
    dbFILE *f;
    int16 i, n;
    struct akill_ {
	char *mask;
	char *reason;
	char who[32];
	time_t time;
    } akill;

    f = open_db_ver(sourcedir, "akill.db", version, version, NULL);
    SAFE(read_int16(&n, f));
    nakill = n;
    akills = smalloc(n * sizeof(*akills));
    for (i = 0; i < n; i++) {
	SAFE(read_variable(akill, f));
	strscpy(akills[i].who, akill.who, NICKMAX);
	akills[i].time = akill.time;
	akills[i].expires = 0;
    }
    for (i = 0; i < n; i++) {
	SAFE(read_string(&akills[i].mask, f));
	SAFE(read_string(&akills[i].reason, f));
    }
    close_db(f);
}

/*************************************************************************/

static void m14_load_clone(const char *sourcedir, int32 version)
{
    dbFILE *f;
    int16 i, n;
    struct allow_ {
	char *host;
	int amount;
	char *reason;
	char who[32];
	time_t time;
    } allow;

    f = open_db_ver(sourcedir, "clone.db", version, version, NULL);
    SAFE(read_int16(&n, f));
    nexceptions = n;
    exceptions = smalloc(n * sizeof(*exceptions));
    for (i = 0; i < n; i++) {
	SAFE(read_variable(allow, f));
	strscpy(exceptions[i].who, allow.who, NICKMAX);
	exceptions[i].limit = allow.amount;
	exceptions[i].time = allow.time;
	exceptions[i].expires = 0;
	exceptions[i].num = i+1;
    }
    for (i = 0; i < n; i++) {
	SAFE(read_string(&exceptions[i].mask, f));
	SAFE(read_string(&exceptions[i].reason, f));
    }
    close_db(f);
}

/*************************************************************************/

static void m14_load_message(const char *sourcedir, int32 version)
{
    dbFILE *f;
    int16 i, n;
    struct message_ {
	char *text;
	int type;
	char who[32];
	time_t time;
    } msg;

    f = open_db_ver(sourcedir, "message.db", version, version, NULL);
    SAFE(read_int16(&n, f));
    nnews = n;
    news = smalloc(n * sizeof(*news));
    for (i = 0; i < n; i++) {
	SAFE(read_variable(msg, f));
	news[i].type = msg.type;
	strscpy(news[i].who, msg.who, NICKMAX);
	news[i].time = msg.time;
    }
    for (i = 0; i < n; i++)
	SAFE(read_string(&news[i].text, f));
    close_db(f);
}

/*************************************************************************/

void load_magick_14b2(const char *sourcedir, int verbose)
{
    if (verbose)
	printf("Loading nick.db...\n");
    m14_load_nick(sourcedir, 5);
    if (verbose)
	printf("Loading chan.db...\n");
    m14_load_chan(sourcedir, 5);
    if (verbose)
	printf("Loading memo.db...\n");
    m14_load_memo(sourcedir, 5);
    if (verbose)
	printf("Loading sop.db...\n");
    m14_load_sop(sourcedir, 5);
    if (verbose)
	printf("Loading akill.db...\n");
    m14_load_akill(sourcedir, 5);
    if (verbose)
	printf("Loading clone.db...\n");
    m14_load_clone(sourcedir, 5);
    if (verbose)
	printf("Loading message.db...\n");
    m14_load_message(sourcedir, 5);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/
/*************************************************************************/

void load_wrecked_1_2(const char *sourcedir, int verbose)
{
    if (verbose)
	printf("Loading nick.db...\n");
    m14_load_nick(sourcedir, 6);
    if (verbose)
	printf("Loading chan.db...\n");
    m14_load_chan(sourcedir, 6);
    if (verbose)
	printf("Loading memo.db...\n");
    m14_load_memo(sourcedir, 6);
    if (verbose)
	printf("Loading sop.db...\n");
    m14_load_sop(sourcedir, 6);
    if (verbose)
	printf("Loading akill.db...\n");
    m14_load_akill(sourcedir, 6);
    if (verbose)
	printf("Loading clone.db...\n");
    m14_load_clone(sourcedir, 6);
    if (verbose)
	printf("Loading message.db...\n");
    m14_load_message(sourcedir, 6);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/
/************************* Database loading: Sirv ************************/
/*************************************************************************/

static void sirv_load_nick(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    int32 version;
    int i, j;
    NickInfo *ni, *ni2, **last, *prev;
    struct oldni_ {
	struct oldni_ *next, *prev;
	char nick[32];
	char pass[32];
	char *usermask;
	char *realname;
	time_t reg;
	time_t seen;
	long naccess;
	char **access;
	long flags;
	time_t idstamp;
	unsigned short memomax;
	unsigned short channelcount;
	char *url;
	char *email;
	char *forward;
	char *hold;
	char *mark;
	char *forbid;
	int news;
	char *regemail;
	long icq;
	long resv[3];
    } oldni;

    f = open_db_ver(sourcedir, "nick.db", 5, 7, &version);
    for (i = 33; i < 256; i++) {
	last = &nicklists[i];
	prev = NULL;
	while (getc_db(f)) {
	    SAFE(read_variable(oldni, f));
	    if (oldni.url)
		SAFE(read_string(&oldni.url, f));
	    if (oldni.email)
		SAFE(read_string(&oldni.email, f));
	    if (oldni.forward)
		SAFE(read_string(&oldni.forward, f));
	    if (oldni.hold)
		SAFE(read_string(&oldni.hold, f));
	    if (oldni.mark)
		SAFE(read_string(&oldni.mark, f));
	    if (oldni.forbid)
		SAFE(read_string(&oldni.forbid, f));
	    if (oldni.regemail)
		SAFE(read_string(&oldni.regemail, f));
	    SAFE(read_string(&oldni.usermask, f));
	    SAFE(read_string(&oldni.realname, f));
	    ni = smalloc(sizeof(*ni));
	    ni->next = NULL;
	    ni->prev = prev;
	    *last = ni;
	    last = &(ni->next);
	    prev = ni;
	    strscpy(ni->nick, oldni.nick, NICKMAX);
	    strscpy(ni->pass, oldni.pass, PASSMAX);
	    ni->url = oldni.url;
	    ni->email = oldni.email;
	    ni->last_usermask = oldni.usermask;
	    ni->last_realname = oldni.realname;
	    ni->last_quit = NULL;
	    ni->time_registered = oldni.reg;
	    ni->last_seen = oldni.seen;
	    ni->link = NULL;
	    ni->linkcount = 0;
	    ni->accesscount = oldni.naccess;
	    ni->memos.memocount = 0;
	    ni->memos.memomax = oldni.memomax;
	    ni->memos.memos = NULL;
	    ni->channelcount = oldni.channelcount;
	    ni->channelmax = CSMaxReg;
	    ni->language = DEF_LANGUAGE;
	    ni->status = 0;
	    ni->flags = 0;
	    if (oldni.flags & 0x00000001)
		ni->flags |= NI_KILLPROTECT;
	    if (oldni.flags & 0x00000002)
		ni->flags |= NI_SECURE;
	    if (oldni.flags & 0x00000004)
		ni->status |= NS_VERBOTEN;
	    if (oldni.flags & 0x00000008)
		ni->status |= NS_ENCRYPTEDPW;
	    if (oldni.flags & 0x00000010)
		ni->flags |= NI_MEMO_SIGNON;
	    if (oldni.flags & 0x00000020)
		ni->flags |= NI_MEMO_RECEIVE;
	    if (oldni.flags & 0x00000040)
		ni->flags |= NI_PRIVATE;
	    if (oldni.flags & 0x00000080)
		ni->flags |= NI_HIDE_EMAIL;
	    if (oldni.flags & 0x00000200)
		ni->status |= NS_NOEXPIRE;
	    if (oldni.flags & 0x00001000)
		ni->memos.memomax = 0;
	    if (oldni.flags & 0x00002000)
		ni->flags |= NI_HIDE_MASK;
	    if (ni->accesscount > NSAccessMax)
		ni->accesscount = NSAccessMax;
	    ni->access = smalloc(ni->accesscount * sizeof(char *));
	    for (j = 0; j < ni->accesscount; j++)
		SAFE(read_string(&ni->access[j], f));
	    while (j++ < oldni.naccess)
		SAFE(read_string(&s, f));
	}
    }
    close_db(f);
    /* Resolve links */
    for (i = 33; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    if (ni->link) {
		int c = (unsigned char) irc_tolower(ni->last_usermask[0]);
		for (ni2 = nicklists[c]; ni2; ni2 = ni2->next) {
		    if (stricmp(ni2->nick, ni->last_usermask) == 0)
			break;
		}
		if (ni2) {
		    ni->link = ni2;
		    strscpy(ni->pass, ni2->pass, PASSMAX);
		} else {
		    fprintf(stderr, "Warning: dropping nick %s linked to nonexistent nick %s\n",
				ni->nick, ni->last_usermask);
		    if (ni->prev)
			ni->prev->next = ni->next;
		    else
			nicklists[i] = ni->next;
		    if (ni->next)
			ni->next->prev = ni->prev;
		}
		ni->last_usermask = NULL;
	    }
	}
    }
}

/*************************************************************************/

static struct {
    short old;
    int32 new;
} sirv_modes[] = {
    { 0x0001, CMODE_i },
    { 0x0002, CMODE_m },
    { 0x0004, CMODE_n },
    { 0x0008, CMODE_p },
    { 0x0010, CMODE_s },
    { 0x0020, CMODE_t },
    { 0x0040, CMODE_k },
    { 0x0080, CMODE_l },
#ifdef IRC_DAL4_4_15
    { 0x0100, 0 }, /* CMODE_r, never set in mlock */
    { 0x0200, 0 }, /* mode +J (what protocol uses this?) */
    { 0x0400, CMODE_R },
#endif
#if defined(IRC_BAHAMUT) || defined(IRC_UNREAL)
    { 0x0800, CMODE_c },
    { 0x1000, CMODE_O },
#endif
    { 0, 0 }
};

static void sirv_load_chan(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    int i, j, reasoncount = 0;
    int16 tmp16;
    ChannelInfo *ci, **last, *prev;
    struct access_ {
	int16 level;
	short in_use;
	char *name;
    } access;
    struct akick_ {
	short is_nick;
	short pad;
	char *name;
	char *reason;
    } akick;
    struct oldci_ {
	struct oldci_ *next, *prev;
	char name[64];
	char founder[32];
	char pass[32];
	char *desc;
	time_t reg;
	time_t used;
	long naccess;
	struct access_ *access;
	long nakick;
	struct akick_ *akick;
	short mlock_on, mlock_off;
	long mlock_limit;
	char *mlock_key;
	char *topic;
	char topic_setter[32];
	time_t topic_time;
	long flags;
	short *levels;
	char *url;
	char *email;
	char *welcome;
	char *hold;
	char *mark;
	char *freeze;
	char *forbid;
	int topic_allow;
	long resv[5];
    } oldci;

    f = open_db_ver(sourcedir, "chan.db", 5, 7, NULL);
    for (i = 33; i < 256; i++) {
	last = &chanlists[i];
	prev = NULL;
	while (getc_db(f)) {
	    SAFE(read_variable(oldci, f));
	    SAFE(read_string(&oldci.desc, f));
	    if (oldci.url)
		SAFE(read_string(&oldci.url, f));
	    if (oldci.email)
		SAFE(read_string(&oldci.email, f));
	    if (oldci.mlock_key)
		SAFE(read_string(&oldci.mlock_key, f));
	    if (oldci.topic)
		SAFE(read_string(&oldci.topic, f));
	    if (oldci.welcome)
		SAFE(read_string(&oldci.welcome, f));
	    if (oldci.hold)
		SAFE(read_string(&oldci.hold, f));
	    if (oldci.mark)
		SAFE(read_string(&oldci.mark, f));
	    if (oldci.freeze)
		SAFE(read_string(&oldci.freeze, f));
	    if (oldci.forbid)
		SAFE(read_string(&oldci.forbid, f));
	    ci = smalloc(sizeof(*ci));
	    strscpy(ci->name, oldci.name, CHANMAX);
	    ci->founder = findnick(oldci.founder);
	    strscpy(ci->founderpass, oldci.pass, PASSMAX);
	    ci->desc = oldci.desc;
	    ci->url = oldci.url;
	    ci->time_registered = oldci.reg;
	    ci->last_used = oldci.used;
	    ci->accesscount = oldci.naccess;
	    ci->akickcount = oldci.nakick;
	    ci->mlock_limit = oldci.mlock_limit;
	    ci->mlock_key = oldci.mlock_key;
	    ci->last_topic = oldci.topic;
	    strscpy(ci->last_topic_setter, oldci.topic_setter, NICKMAX);
	    ci->last_topic_time = oldci.topic_time;
	    ci->memos.memocount = 0;
	    ci->memos.memomax = MSMaxMemos;
	    ci->memos.memos = NULL;
	    ci->flags = oldci.flags & 0x000003FF;
	    if (oldci.flags & 0x04000000)
		ci->flags |= CI_ENFORCE;
	    if (oldci.flags & 0x08000000) {
		ci->suspendinfo = smalloc(sizeof(SuspendInfo));
		strcpy(ci->suspendinfo->who, "<unknown>");
		ci->suspendinfo->reason =
		    "Unknown (imported from SirvNET IRC Services)";
		ci->suspendinfo->suspended = time(NULL);
		ci->suspendinfo->expires = 0;
	    }
	    for (j = 0; sirv_modes[j].old != 0; j++) {
		if (oldci.mlock_on & sirv_modes[j].old)
		    ci->mlock_on |= sirv_modes[j].new;
		if (oldci.mlock_off & sirv_modes[j].old)
		    ci->mlock_off |= sirv_modes[j].new;
	    }
	    if (oldci.naccess > CSAccessMax)
		ci->accesscount = CSAccessMax;
	    else
		ci->accesscount = oldci.naccess;
	    if (oldci.nakick > CSAutokickMax)
		ci->akickcount = CSAutokickMax;
	    else
		ci->akickcount = oldci.nakick;
	    ci->access = smalloc(sizeof(ChanAccess) * ci->accesscount);
	    for (j = 0; j < oldci.naccess; j++) {
		SAFE(read_variable(access, f));
		if (j < ci->accesscount) {
		    ci->access[j].in_use = access.in_use;
		    ci->access[j].level = access.level;
		}
	    }
	    for (j = 0; j < oldci.naccess; j++) {
		SAFE(read_string(&s, f));
		if (!s) {
		    ci->access[j].in_use = 0;
		    continue;
		}
		if (j < ci->accesscount && ci->access[j].in_use) {
		    ci->access[j].ni = findnick(s);
		    if (!ci->access[j].ni)
			ci->access[j].in_use = 0;
		}
	    }
	    ci->akick = smalloc(sizeof(AutoKick) * ci->akickcount);
	    for (j = 0; j < oldci.nakick; j++) {
		SAFE(read_variable(akick, f));
		if (j < ci->akickcount) {
		    ci->akick[j].in_use = 1;
		    ci->akick[j].is_nick = akick.is_nick;
		    ci->akick[j].reason = akick.reason;
		} else if (akick.reason) {
		    reasoncount++;
		}
	    }
	    for (j = 0; j < oldci.nakick; j++) {
		SAFE(read_string(&s, f));
		if (s) {
		    if (j < ci->akickcount && ci->akick[j].in_use) {
			if (ci->akick[j].is_nick) {
			    ci->akick[j].u.ni = findnick(s);
			    if (!ci->akick[j].u.ni) {
				ci->akick[j].in_use = 0;
				ci->akick[j].is_nick = 0;
			    }
			} else {
			    ci->akick[j].u.mask = s;
			}
		    }
		} else {
		    ci->akick[j].in_use = 0;
		}
		if (j < ci->akickcount && ci->akick[j].reason) {
		    SAFE(read_string(&ci->akick[j].reason, f));
		    if (!ci->akick[j].in_use && ci->akick[j].reason)
			ci->akick[j].reason = NULL;
		}
	    }
	    for (j = 0; j < reasoncount; j++)
		SAFE(read_string(&s, f));
	    ci->levels = smalloc(CA_SIZE * sizeof(*ci->levels));
	    init_levels(ci);
	    if (oldci.levels) {
		SAFE(read_int16(&tmp16, f));
		for (j = 0; j < tmp16; j++) {
		    int16 lev;
		    SAFE(read_variable(lev, f));
		    switch (j) {
			case  0: ci->levels[CA_INVITE]        = lev; break;
			case  1: ci->levels[CA_AKICK]         = lev; break;
			case  2: ci->levels[CA_SET]           = lev; break;
			case  3: ci->levels[CA_UNBAN]         = lev; break;
			case  4: ci->levels[CA_AUTOOP]        = lev; break;
			case  5: ci->levels[CA_AUTODEOP]      = lev; break;
			case  6: ci->levels[CA_AUTOVOICE]     = lev; break;
			case  7: ci->levels[CA_OPDEOP]        = lev; break;
			case  8: ci->levels[CA_ACCESS_LIST]   = lev; break;
			case  9: ci->levels[CA_CLEAR]         = lev; break;
			case 10: ci->levels[CA_NOJOIN]        = lev; break;
			case 11: ci->levels[CA_ACCESS_CHANGE] = lev; break;
		    }
		}
	    }
	    /* Only insert in list if founder is found */
	    if (ci->founder) {
		ci->prev = prev;
		ci->next = NULL;
		*last = ci;
		last = &(ci->next);
		prev = ci;
	    } else {
		/* Yeah, it's a memory leak, I know.  Shouldn't matter for
		 * this program. */
	    }
	} /* while more entries */
    } /* for 33..256 */
    close_db(f);
}

/*************************************************************************/

static void sirv_load_memo(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    struct memo_ {
	char sender[32];
	long number;
	time_t time;
	char *text;
	char *chan;
	short flags;
	short pad;
	long resv[3];
    } memo;
    struct memolist_ {
	struct memolist_ *next, *prev;
	char nick[32];
	long n_memos;
	Memo *memos;
	long reserved[4];
    } memolist;
    NickInfo *ni;
    Memo *m = NULL;
    int i, j, chancount = 0;

    f = open_db_ver(sourcedir, "memo.db", 5, 7, NULL);
    for (i = 33; i < 256; i++) {
	while (getc_db(f)) {
	    SAFE(read_variable(memolist, f));
	    ni = findnick(memolist.nick);
	    if (ni) {
		ni->memos.memocount = memolist.n_memos;
		m = smalloc(sizeof(Memo) * ni->memos.memocount);
		ni->memos.memos = m;
	    }
	    for (j = 0; j < memolist.n_memos; j++) {
		SAFE(read_variable(memo, f));
		if (ni) {
		    m[j].number = memo.number;
		    m[j].flags = memo.flags & 1;
		    m[j].time = memo.time;
		    strscpy(m[j].sender, memo.sender, NICKMAX);
		    if (memo.chan)
			m[j].flags |= 0x8000;
		} else if (memo.chan) {
		    chancount++;
		}
	    }
	    for (j = 0; j < memolist.n_memos; j++) {
		SAFE(read_string(&s, f));
		if (ni) {
		    m[j].text = s;
		    if (m[j].flags & 0x8000) {
			m[j].flags &= ~0x8000;
			SAFE(read_string(&s, f));
		    }
		}
	    }
	    for (j = 0; j < chancount; j++)
		SAFE(read_string(&s, f));
	}
    }
    close_db(f);
}

/*************************************************************************/

static void sirv_load_os_sop(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    int16 n, i;

    f = open_db_ver(sourcedir, "os_sop.db", 5, 7, NULL);
    SAFE(read_int16(&n, f));
    if (n > MAX_SERVOPERS)
	n = MAX_SERVOPERS;
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	add_adminoper(ADD_OPER, s);
    }
    close_db(f);
}

/*************************************************************************/

static void sirv_load_os_sa(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    int16 n, i;

    f = open_db_ver(sourcedir, "os_sa.db", 5, 7, NULL);
    SAFE(read_int16(&n, f));
    if (n > MAX_SERVADMINS)
	n = MAX_SERVADMINS;
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	add_adminoper(ADD_ADMIN, s);
    }
    close_db(f);
}

/*************************************************************************/

static void sirv_load_akill(const char *sourcedir)
{
    dbFILE *f;
    int16 i, n;
    struct akill_ {
	char *mask;
	char *reason;
	char who[32];
	time_t time;
	time_t expires;
	long resv[4];
    } akill;

    f = open_db_ver(sourcedir, "akill.db", 5, 7, NULL);
    SAFE(read_int16(&n, f));
    nakill = n;
    akills = smalloc(n * sizeof(*akills));
    for (i = 0; i < n; i++) {
	SAFE(read_variable(akill, f));
	strscpy(akills[i].who, akill.who, NICKMAX);
	akills[i].time = akill.time;
	akills[i].expires = akill.expires;
    }
    for (i = 0; i < n; i++) {
	SAFE(read_string(&akills[i].mask, f));
	SAFE(read_string(&akills[i].reason, f));
    }
    close_db(f);
}

/*************************************************************************/

static void sirv_load_trigger(const char *sourcedir)
{
    dbFILE *f;
    int16 i, n;
    struct trigger_ {
	char *mask;
	long tvalue;
	char who[32];
	long resv[4];
    } trigger;

    f = open_db_ver(sourcedir, "trigger.db", 5, 7, NULL);
    SAFE(read_int16(&n, f));
    nexceptions = n;
    exceptions = smalloc(n * sizeof(*exceptions));
    for (i = 0; i < n; i++) {
	SAFE(read_variable(trigger, f));
	if (trigger.tvalue > 32767)
	    trigger.tvalue = 32767;
	exceptions[i].limit = trigger.tvalue;
	strscpy(exceptions[i].who, trigger.who, NICKMAX);
	exceptions[i].reason = "(unknown)";
	exceptions[i].time = time(NULL);
	exceptions[i].expires = 0;
    }
    for (i = 0; i < n; i++)
	SAFE(read_string(&exceptions[i].mask, f));
    close_db(f);
}

/*************************************************************************/

void load_sirv(const char *sourcedir, int verbose)
{
    if (verbose)
	printf("Loading nick.db...\n");
    sirv_load_nick(sourcedir);
    if (verbose)
	printf("Loading chan.db...\n");
    sirv_load_chan(sourcedir);
    if (verbose)
	printf("Loading memo.db...\n");
    sirv_load_memo(sourcedir);
    if (verbose)
	printf("Loading os_sa.db...\n");
    sirv_load_os_sa(sourcedir);
    if (verbose)
	printf("Loading os_sop.db...\n");
    sirv_load_os_sop(sourcedir);
    if (verbose)
	printf("Loading akill.db...\n");
    sirv_load_akill(sourcedir);
    if (verbose)
	printf("Loading trigger.db...\n");
    sirv_load_trigger(sourcedir);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/
/******************** Database loading: Auspice 2.5.x ********************/
/*************************************************************************/

static void aus_load_nick(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    int32 version;
    long i, j;
    NickInfo *ni, *ni2, **last, *prev;
    struct oldni_ {
	struct oldni_ *next, *prev;
	char nick[32];
	char pass[32];
	char *usermask;
	char *realname;
	time_t reg;
	time_t seen;
	long naccess;
	char **access;
	long flags;
	time_t idstamp;
	unsigned short memomax;
	unsigned short channelcount;
	char *url;
	char *email;
	char *forward;
	char *hold;
	char *mark;
	char *forbid;
	int news;
	char *uin;
	char *age;
	char *info;
	char *sex;
	char *mlock;
	char *last_quit;
	long eflags;
	long ajoincount;
	char **autojoin;
	long comline;
	char **comment;
	long noteline;
	char **note;
    } oldni;

    f = open_db_ver(sourcedir, "nick.db", 6, 6, &version);
    for (i = 33; i < 256; i++) {
	last = &nicklists[i];
	prev = NULL;
	while (getc_db(f)) {
	    SAFE(read_variable(oldni, f));
	    if (oldni.url)
		SAFE(read_string(&oldni.url, f));
	    if (oldni.email)
		SAFE(read_string(&oldni.email, f));
	    if (oldni.forward)
		SAFE(read_string(&oldni.forward, f));
	    if (oldni.hold)
		SAFE(read_string(&oldni.hold, f));
	    if (oldni.mark)
		SAFE(read_string(&oldni.mark, f));
	    if (oldni.forbid)
		SAFE(read_string(&oldni.forbid, f));
	    if (oldni.age)
		SAFE(read_string(&oldni.age, f));
	    if (oldni.info)
		SAFE(read_string(&oldni.info, f));
	    if (oldni.sex)
		SAFE(read_string(&oldni.sex, f));
	    if (oldni.mlock)
		SAFE(read_string(&oldni.mlock, f));
	    if (oldni.last_quit)
		SAFE(read_string(&oldni.last_quit, f));
	    if (oldni.usermask)
		SAFE(read_string(&oldni.usermask, f));
	    if (oldni.realname)
		SAFE(read_string(&oldni.realname, f));
	    ni = smalloc(sizeof(*ni));
	    ni->next = NULL;
	    ni->prev = prev;
	    *last = ni;
	    last = &(ni->next);
	    prev = ni;
	    strscpy(ni->nick, oldni.nick, NICKMAX);
	    strscpy(ni->pass, oldni.pass, PASSMAX);
	    ni->url = oldni.url;
	    ni->email = oldni.email;
	    ni->last_usermask = oldni.usermask;
	    ni->last_realname = oldni.realname;
	    ni->last_quit = oldni.last_quit;
	    ni->time_registered = oldni.reg;
	    ni->last_seen = oldni.seen;
	    ni->link = NULL;
	    ni->linkcount = 0;
	    ni->accesscount = oldni.naccess;
	    ni->memos.memocount = 0;
	    ni->memos.memomax = oldni.memomax;
	    ni->memos.memos = NULL;
	    ni->channelcount = oldni.channelcount;
	    ni->channelmax = CSMaxReg;
	    ni->language = DEF_LANGUAGE;
	    ni->status = 0;
	    ni->flags = 0;
	    if (oldni.flags & 0x00000001)
		ni->flags |= NI_KILLPROTECT;
	    if (oldni.flags & 0x00000002)
		ni->flags |= NI_SECURE;
	    if (oldni.flags & 0x00000004)
		ni->status |= NS_VERBOTEN;
	    if (oldni.flags & 0x00000008)
		ni->status |= NS_ENCRYPTEDPW;
	    if (oldni.flags & 0x00000010)
		ni->flags |= NI_MEMO_SIGNON;
	    if (oldni.flags & 0x00000020)
		ni->flags |= NI_MEMO_RECEIVE;
	    if (oldni.flags & 0x00000040)
		ni->flags |= NI_PRIVATE;
	    if (oldni.flags & 0x00000080)
		ni->flags |= NI_HIDE_EMAIL;
	    if (oldni.flags & 0x00000200)
		ni->status |= NS_NOEXPIRE;
	    if (oldni.flags & 0x00001000)
		ni->memos.memomax = 0;
	    if (oldni.flags & 0x00002000)
		ni->flags |= NI_HIDE_MASK;
	    if (ni->accesscount > NSAccessMax)
		ni->accesscount = NSAccessMax;
	    ni->access = smalloc(ni->accesscount * sizeof(char *));
	    for (j = 0; j < ni->accesscount; j++)
		SAFE(read_string(&ni->access[j], f));
	    while (j++ < oldni.naccess)
		SAFE(read_string(&s, f));
	    for (j = 0; j < oldni.ajoincount; j++)
		SAFE(read_string(&s, f));
	    for (j = 0; j < oldni.comline; j++)
		SAFE(read_string(&s, f));
	    for (j = 0; j < oldni.noteline; j++)
		SAFE(read_string(&s, f));
	}
    }
    close_db(f);
    /* Resolve links */
    for (i = 33; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    if (ni->link) {
		int c = (unsigned char) irc_tolower(ni->last_usermask[0]);
		for (ni2 = nicklists[c]; ni2; ni2 = ni2->next) {
		    if (stricmp(ni2->nick, ni->last_usermask) == 0)
			break;
		}
		if (ni2) {
		    ni->link = ni2;
		    strscpy(ni->pass, ni2->pass, PASSMAX);
		} else {
		    fprintf(stderr, "Warning: dropping nick %s linked to nonexistent nick %s\n",
				ni->nick, ni->last_usermask);
		    if (ni->prev)
			ni->prev->next = ni->next;
		    else
			nicklists[i] = ni->next;
		    if (ni->next)
			ni->next->prev = ni->prev;
		}
		ni->last_usermask = NULL;
	    }
	}
    }
}

/*************************************************************************/

static void aus_load_chan(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    long i, j, reasoncount = 0;
    int16 tmp16;
    ChannelInfo *ci, **last, *prev;
    char **adders;  /* for remembering which access entries had an adder */
    struct access_ {
	int16 level;
	short in_use;
	char *name;
	char *adder;
    } access;
    struct akick_ {
	short is_nick;
	short pad;
	char *name;
	char *reason;
    } akick;
    struct oldci_ {
	struct oldci_ *next, *prev;
	char name[64];
	char founder[32];
	char pass[32];
	char *desc;
	time_t reg;
	time_t used;
	long naccess;
	struct access_ *access;
	long nakick;
	struct akick_ *akick;
	char mlock_on[64], mlock_off[64];
	long mlock_limit;
	char *mlock_key;
	char *topic;
	char topic_setter[32];
	time_t topic_time;
	long flags;
	short *levels;
	char *url;
	char *email;
	char *welcome;
	char *hold;
	char *mark;
	char *freeze;
	char *forbid;
	int topic_allow;
	char *successor;
	char *mlock_link;
	char *mlock_flood;
	char *bot;
	long botflag;
	long newsline;
	char **news;
	long badwline;
	char **badwords;
	long resv[3];
    } oldci;

    f = open_db_ver(sourcedir, "chan.db", 7, 7, NULL);
    for (i = 33; i < 256; i++) {
	last = &chanlists[i];
	prev = NULL;
	while (getc_db(f)) {
	    SAFE(read_variable(oldci, f));
	    SAFE(read_string(&oldci.desc, f));
	    if (oldci.url)
		SAFE(read_string(&oldci.url, f));
	    if (oldci.email)
		SAFE(read_string(&oldci.email, f));
	    if (oldci.mlock_key)
		SAFE(read_string(&oldci.mlock_key, f));
	    if (oldci.topic)
		SAFE(read_string(&oldci.topic, f));
	    if (oldci.welcome)
		SAFE(read_string(&oldci.welcome, f));
	    if (oldci.hold)
		SAFE(read_string(&oldci.hold, f));
	    if (oldci.mark)
		SAFE(read_string(&oldci.mark, f));
	    if (oldci.freeze)
		SAFE(read_string(&oldci.freeze, f));
	    if (oldci.forbid)
		SAFE(read_string(&oldci.forbid, f));
	    if (oldci.successor)
		SAFE(read_string(&oldci.successor, f));
	    if (oldci.mlock_link)
		SAFE(read_string(&oldci.mlock_link, f));
	    if (oldci.mlock_flood)
		SAFE(read_string(&oldci.mlock_flood, f));
	    if (oldci.bot)
		SAFE(read_string(&oldci.bot, f));
	    ci = smalloc(sizeof(*ci));
	    strscpy(ci->name, oldci.name, CHANMAX);
	    ci->founder = findnick(oldci.founder);
	    ci->successor = oldci.successor ? findnick(oldci.successor) : NULL;
	    strscpy(ci->founderpass, oldci.pass, PASSMAX);
	    ci->desc = oldci.desc;
	    ci->url = oldci.url;
	    ci->time_registered = oldci.reg;
	    ci->last_used = oldci.used;
	    ci->accesscount = oldci.naccess;
	    ci->akickcount = oldci.nakick;
	    ci->mlock_limit = oldci.mlock_limit;
	    ci->mlock_key = oldci.mlock_key;
	    ci->last_topic = oldci.topic;
	    strscpy(ci->last_topic_setter, oldci.topic_setter, NICKMAX);
	    ci->last_topic_time = oldci.topic_time;
	    ci->memos.memocount = 0;
	    ci->memos.memomax = MSMaxMemos;
	    ci->memos.memos = NULL;
	    ci->flags = oldci.flags & 0x000003FF;
	    if (oldci.flags & 0x04000000)
		ci->flags |= CI_ENFORCE;
	    if (oldci.flags & 0x08000000) {
		ci->suspendinfo = smalloc(sizeof(SuspendInfo));
		strcpy(ci->suspendinfo->who, "<unknown>");
		ci->suspendinfo->reason =
		    "Unknown (imported from Auspice Services)";
		ci->suspendinfo->suspended = time(NULL);
		ci->suspendinfo->expires = 0;
	    }
	    for (s = oldci.mlock_on; *s; s++)
		ci->mlock_on |= char_modes[(unsigned char)*s];
	    for (s = oldci.mlock_off; *s; s++)
		ci->mlock_off |= char_modes[(unsigned char)*s];
	    if (oldci.naccess > CSAccessMax)
		ci->accesscount = CSAccessMax;
	    else
		ci->accesscount = oldci.naccess;
	    if (oldci.nakick > CSAutokickMax)
		ci->akickcount = CSAutokickMax;
	    else
		ci->akickcount = oldci.nakick;
	    ci->access = smalloc(sizeof(ChanAccess) * ci->accesscount);
	    adders = smalloc(sizeof(char *) * oldci.naccess);
	    for (j = 0; j < oldci.naccess; j++) {
		SAFE(read_variable(access, f));
		adders[j] = access.adder;
		if (j < ci->accesscount) {
		    ci->access[j].in_use = access.in_use;
		    ci->access[j].level = access.level;
		}
	    }
	    for (j = 0; j < oldci.naccess; j++) {
		SAFE(read_string(&s, f));
		if (adders[j])
		    SAFE(read_string(&adders[j], f));
		if (!s) {
		    ci->access[j].in_use = 0;
		    continue;
		}
		if (j < ci->accesscount && ci->access[j].in_use) {
		    ci->access[j].ni = findnick(s);
		    if (!ci->access[j].ni)
			ci->access[j].in_use = 0;
		}
	    }
	    ci->akick = smalloc(sizeof(AutoKick) * ci->akickcount);
	    for (j = 0; j < oldci.nakick; j++) {
		SAFE(read_variable(akick, f));
		if (j < ci->akickcount) {
		    ci->akick[j].in_use = 1;
		    ci->akick[j].is_nick = akick.is_nick;
		    ci->akick[j].reason = akick.reason;
		} else if (akick.reason) {
		    reasoncount++;
		}
	    }
	    for (j = 0; j < oldci.nakick; j++) {
		SAFE(read_string(&s, f));
		if (s) {
		    if (j < ci->akickcount && ci->akick[j].in_use) {
			if (ci->akick[j].is_nick) {
			    ci->akick[j].u.ni = findnick(s);
			    if (!ci->akick[j].u.ni) {
				ci->akick[j].in_use = 0;
				ci->akick[j].is_nick = 0;
			    }
			} else {
			    ci->akick[j].u.mask = s;
			}
		    } else {
			free(s);
		    }
		} else {
		    ci->akick[j].in_use = 0;
		}
		if (j < ci->akickcount && ci->akick[j].reason) {
		    SAFE(read_string(&ci->akick[j].reason, f));
		    if (!ci->akick[j].in_use && ci->akick[j].reason) {
			free(ci->akick[j].reason);
			ci->akick[j].reason = NULL;
		    }
		}
	    }
	    for (j = 0; j < reasoncount; j++)
		SAFE(read_string(&s, f));
	    ci->levels = smalloc(CA_SIZE * sizeof(*ci->levels));
	    init_levels(ci);
	    if (oldci.levels) {
		SAFE(read_int16(&tmp16, f));
		for (j = 0; j < tmp16; j++) {
		    int16 lev;
		    SAFE(read_variable(lev, f));
		    switch (j) {
			case  0: ci->levels[CA_INVITE]        = lev; break;
			case  1: ci->levels[CA_AKICK]         = lev; break;
			case  2: ci->levels[CA_SET]           = lev; break;
			case  3: ci->levels[CA_UNBAN]         = lev; break;
			case  4: ci->levels[CA_AUTOOP]        = lev; break;
			case  5: ci->levels[CA_AUTODEOP]      = lev; break;
			case  6: ci->levels[CA_AUTOVOICE]     = lev; break;
			case  7: ci->levels[CA_OPDEOP]        = lev; break;
			case  8: ci->levels[CA_ACCESS_LIST]   = lev; break;
			case  9: ci->levels[CA_CLEAR]         = lev; break;
			case 10: ci->levels[CA_NOJOIN]        = lev; break;
			case 11: ci->levels[CA_ACCESS_CHANGE] = lev; break;
			case 12: ci->levels[CA_AUTOHALFOP]    = lev;
				 ci->levels[CA_HALFOP]        = lev; break;
		    }
		}
	    }
	    for (j = 0; j < oldci.newsline; j++)
		SAFE(read_string(&s, f));
	    for (j = 0; j < oldci.badwline; j++)
		SAFE(read_string(&s, f));
	    /* Only insert in list if founder is found */
	    if (ci->founder) {
		ci->prev = prev;
		ci->next = NULL;
		*last = ci;
		last = &(ci->next);
		prev = ci;
	    } else {
		/* Yeah, it's a memory leak, I know.  Shouldn't matter for
		 * this program. */
	    }
	} /* while more entries */
    } /* for 33..256 */
    close_db(f);
}

/*************************************************************************/

static void aus_load_memo(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    struct memo_ {
	char sender[32];
	long number;
	time_t time;
	char *text;
	char *chan;
	short flags;
	short pad;
	long resv[3];
    } memo;
    struct memolist_ {
	struct memolist_ *next, *prev;
	char nick[32];
	long n_memos;
	Memo *memos;
	long reserved[4];
    } memolist;
    NickInfo *ni;
    Memo *m = NULL;
    long i, j, chancount = 0;

    f = open_db_ver(sourcedir, "memo.db", 6, 6, NULL);
    for (i = 33; i < 256; i++) {
	while (getc_db(f)) {
	    SAFE(read_variable(memolist, f));
	    ni = findnick(memolist.nick);
	    if (ni) {
		ni->memos.memocount = memolist.n_memos;
		m = smalloc(sizeof(Memo) * ni->memos.memocount);
		ni->memos.memos = m;
	    }
	    for (j = 0; j < memolist.n_memos; j++) {
		SAFE(read_variable(memo, f));
		if (ni) {
		    m[j].number = memo.number;
		    m[j].flags = memo.flags & 1;
		    m[j].time = memo.time;
		    strscpy(m[j].sender, memo.sender, NICKMAX);
		    if (memo.chan)
			m[j].flags |= 0x8000;
		} else if (memo.chan) {
		    chancount++;
		}
	    }
	    for (j = 0; j < memolist.n_memos; j++) {
		SAFE(read_string(&s, f));
		if (ni) {
		    m[j].text = s;
		    if (m[j].flags & 0x8000) {
			m[j].flags &= ~0x8000;
			SAFE(read_string(&s, f));
		    }
		}
	    }
	    for (j = 0; j < chancount; j++)
		SAFE(read_string(&s, f));
	}
    }
    close_db(f);
}

/*************************************************************************/

static void aus_load_admin(const char *sourcedir)
{
    char *s;
    dbFILE *f;
    long i, j;
    struct admin_ {
	struct admin_ *next, *prev;
	char *nick;
	char *host;
	char *who;	/* added by who */
	char *server;
	char **mark;
	long markline;
	long adflags;
	long flags;
	time_t added;
    } admin;

    f = open_db_ver(sourcedir, "admin.db", 1, 1, NULL);
    for (i = 33; i < 256; i++) {
	while (getc_db(f)) {
	    SAFE(read_variable(admin, f));
	    if (admin.nick)
		SAFE(read_string(&admin.nick, f));
	    if (admin.host)
		SAFE(read_string(&admin.host, f));
	    if (admin.who)
		SAFE(read_string(&admin.who, f));
	    if (admin.server)
		SAFE(read_string(&admin.server, f));
	    for (j = 0; j < admin.markline; j++)
		SAFE(read_string(&s, f));
	    if (admin.adflags & 4)
		add_adminoper(ADD_ADMIN, admin.nick);
	    else if (admin.adflags & 2)
		add_adminoper(ADD_OPER, admin.nick);
	}
    }
    close_db(f);
}

/*************************************************************************/

static void aus_load_akill(const char *sourcedir)
{
    dbFILE *f;
    int16 i, n;
    struct akill_ {
	char *mask;
	char *reason;
	char who[32];
	time_t time;
	time_t expires;
	long resv[4];
    } akill;

    f = open_db_ver(sourcedir, "akill.db", 6, 6, NULL);
    SAFE(read_int16(&n, f));
    nakill = n;
    akills = smalloc(n * sizeof(*akills));
    for (i = 0; i < n; i++) {
	SAFE(read_variable(akill, f));
	strscpy(akills[i].who, akill.who, NICKMAX);
	akills[i].time = akill.time;
	akills[i].expires = akill.expires;
    }
    for (i = 0; i < n; i++) {
	SAFE(read_string(&akills[i].mask, f));
	SAFE(read_string(&akills[i].reason, f));
    }
    close_db(f);
}

/*************************************************************************/

static void aus_load_trigger(const char *sourcedir)
{
    dbFILE *f;
    int16 i, n;
    struct trigger_ {
	char *mask;
	long tvalue;
	char who[32];
	long resv[4];
    } trigger;

    f = open_db_ver(sourcedir, "trigger.db", 6, 6, NULL);
    SAFE(read_int16(&n, f));
    nexceptions = n;
    exceptions = smalloc(n * sizeof(*exceptions));
    for (i = 0; i < n; i++) {
	SAFE(read_variable(trigger, f));
	if (trigger.tvalue > 32767)
	    trigger.tvalue = 32767;
	exceptions[i].limit = trigger.tvalue;
	strscpy(exceptions[i].who, trigger.who, NICKMAX);
	exceptions[i].reason = "(unknown)";
	exceptions[i].time = time(NULL);
	exceptions[i].expires = 0;
    }
    for (i = 0; i < n; i++)
	SAFE(read_string(&exceptions[i].mask, f));
    close_db(f);
}

/*************************************************************************/

void load_aus_2_5(const char *sourcedir, int verbose)
{
    if (verbose)
	printf("Loading nick.db...\n");
    aus_load_nick(sourcedir);
    if (verbose)
	printf("Loading chan.db...\n");
    aus_load_chan(sourcedir);
    if (verbose)
	printf("Loading memo.db...\n");
    aus_load_memo(sourcedir);
    if (verbose)
	printf("Loading admin.db...\n");
    aus_load_admin(sourcedir);
    if (verbose)
	printf("Loading akill.db...\n");
    aus_load_akill(sourcedir);
    if (verbose)
	printf("Loading trigger.db...\n");
    aus_load_trigger(sourcedir);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/
/*********************** Database loading: Daylight **********************/
/*************************************************************************/

void dayl_load_nick(const char *sourcedir)
{
    dbFILE *f;
    int i, j, c;
    int32 tmp32;
    NickInfo *ni, **last, *prev;

    f = open_db_ver(sourcedir, "nick.db", 8, 8, NULL);
    for (i = 0; i < 256; i++) {
	last = &nicklists[i];
	prev = NULL;
	while ((c = getc_db(f)) == 1) {
	    ni = scalloc(sizeof(NickInfo), 1);
	    *last = ni;
	    last = &ni->next;
	    ni->prev = prev;
	    prev = ni;
	    SAFE(read_buffer(ni->nick, f));
	    SAFE(read_buffer(ni->pass, f));
	    SAFE(read_string(&ni->url, f));
	    SAFE(read_string(&ni->email, f));
	    SAFE(read_string(&ni->last_usermask, f));
	    if (!ni->last_usermask)
		ni->last_usermask = "@";
	    SAFE(read_string(&ni->last_realname, f));
	    if (!ni->last_realname)
		ni->last_realname = "";
	    SAFE(read_string(&ni->last_quit, f));
	    SAFE(read_int32(&tmp32, f));
	    ni->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    ni->last_seen = tmp32;
	    SAFE(read_int16(&ni->status, f));
	    ni->status &= ~NS_TEMPORARY;
	    SAFE(read_string((char **)&ni->link, f));
	    SAFE(read_int16(&ni->linkcount, f));
	    if (ni->link) {
		SAFE(read_int16(&ni->channelcount, f));
		ni->flags = 0;
		ni->accesscount = 0;
		ni->access = NULL;
		ni->memos.memocount = 0;
		ni->memos.memomax = MSMaxMemos;
		ni->memos.memos = NULL;
		ni->channelmax = CSMaxReg;
		ni->language = DEF_LANGUAGE;
	    } else {
		SAFE(read_int32(&ni->flags, f));
		if (!NSAllowKillImmed)
		    ni->flags &= ~NI_KILL_IMMED;
		SAFE(read_int16(&ni->accesscount, f));
		if (ni->accesscount) {
		    char **access;
		    access = smalloc(sizeof(char *) * ni->accesscount);
		    ni->access = access;
		    for (j = 0; j < ni->accesscount; j++, access++)
			SAFE(read_string(access, f));
		}
		SAFE(read_int16(&ni->memos.memocount, f));
		SAFE(read_int16(&ni->memos.memomax, f));
		if (ni->memos.memocount) {
		    Memo *memos;
		    memos = smalloc(sizeof(Memo) * ni->memos.memocount);
		    ni->memos.memos = memos;
		    for (j = 0; j < ni->memos.memocount; j++, memos++) {
			SAFE(read_int32(&memos->number, f));
			SAFE(read_int16(&memos->flags, f));
			SAFE(read_int32(&tmp32, f));
			memos->time = tmp32;
			SAFE(read_buffer(memos->sender, f));
			SAFE(read_string(&memos->text, f));
		    }
		}
		SAFE(read_int16(&ni->channelcount, f));
		SAFE(read_int16(&ni->channelmax, f));
		SAFE(read_int16(&ni->language, f));
	    }
	    ni->channelcount = 0;
	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
	*last = NULL;
    } /* for (i) */
    close_db(f);

    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    if (ni->link)
		ni->link = findnick((char *)ni->link);
	}
    }
}

/*************************************************************************/

static struct {
    int32 old, new;
} daylight_modes[] = {
    { 0x00000001, CMODE_i },
    { 0x00000002, CMODE_m },
    { 0x00000004, CMODE_n },
    { 0x00000008, CMODE_p },
    { 0x00000010, CMODE_s },
    { 0x00000020, CMODE_t },
    { 0x00000040, CMODE_k },
    { 0x00000080, CMODE_l },
#ifdef IRC_DAL4_4_15
    { 0x00000100, CMODE_R },
    { 0x00000200, 0 }, /* CMODE_r, never set in mlock */
#endif
#if defined(IRC_BAHAMUT) || defined(IRC_UNREAL)
    { 0x00002000, CMODE_c },
    { 0x00004000, CMODE_O },
#endif
#ifdef IRC_UNREAL
    { 0x00000400, CMODE_K },
    { 0x00000800, CMODE_V },
    { 0x00001000, CMODE_Q },
    { 0x00008000, CMODE_A },
    { 0x00010000, CMODE_S },
    { 0x00020000, CMODE_H },
    { 0x00040000, CMODE_C },
    { 0x00080000, CMODE_u },
    { 0x00100000, CMODE_N },
    { 0x00200000, 0 }, /* CMODE_f, not currently supported */
    { 0x00400000, CMODE_z },
#endif
    { 0, 0 }
};

void dayl_load_chan(const char *sourcedir)
{
    dbFILE *f;
    int i, j, c;
    ChannelInfo *ci, **last, *prev;
    int32 tmp32, mlock_on, mlock_off;

    f = open_db_ver(sourcedir, "chan.db", 8, 9, NULL);

    for (i = 0; i < 256; i++) {
	int16 tmp16;
	int n_levels;
	char *s;

	last = &chanlists[i];
	prev = NULL;
	while ((c = getc_db(f)) == 1) {
	    ci = scalloc(sizeof(ChannelInfo), 1);
	    *last = ci;
	    last = &ci->next;
	    ci->prev = prev;
	    prev = ci;
	    SAFE(read_buffer(ci->name, f));
	    SAFE(read_string(&s, f));
	    if (s)
		ci->founder = findnick(s);
	    SAFE(read_string(&s, f));
	    if (s)
		ci->successor = findnick(s);
	    if (ci->founder == ci->successor)
		ci->successor = NULL;
	    if (ci->founder != NULL) {
		NickInfo *ni = ci->founder;
		while (ni) {
		    ni->channelcount++;
		    ni = ni->link;
		}
	    }
	    SAFE(read_buffer(ci->founderpass, f));
	    SAFE(read_string(&ci->desc, f));
	    if (!ci->desc)
		ci->desc = "";
	    SAFE(read_string(&ci->url, f));
	    SAFE(read_string(&ci->email, f));
	    SAFE(read_int32(&tmp32, f));
	    ci->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    ci->last_used = tmp32;
	    SAFE(read_string(&ci->last_topic, f));
	    SAFE(read_buffer(ci->last_topic_setter, f));
	    SAFE(read_int32(&tmp32, f));
	    ci->last_topic_time = tmp32;
	    SAFE(read_int32(&ci->flags, f));

	    SAFE(read_int16(&tmp16, f));
	    n_levels = tmp16;
	    init_levels(ci);
	    for (j = 0; j < n_levels; j++) {
		int16 lev;
		SAFE(read_int16(&lev, f));
		switch (j) {
		  case  0: ci->levels[CA_INVITE]        = lev; break;
		  case  1: ci->levels[CA_AKICK]         = lev; break;
		  case  2: ci->levels[CA_SET]           = lev; break;
		  case  3: ci->levels[CA_UNBAN]         = lev; break;
		  case  4: ci->levels[CA_AUTOOP]        = lev; break;
		  case  5: ci->levels[CA_AUTODEOP]      = lev; break;
		  case  6: ci->levels[CA_AUTOVOICE]     = lev; break;
		  case  7: ci->levels[CA_OPDEOP]        = lev; break;
		  case  8: ci->levels[CA_ACCESS_LIST]   = lev; break;
		  case  9: ci->levels[CA_CLEAR]         = lev; break;
		  case 10: ci->levels[CA_NOJOIN]        = lev; break;
		  case 11: ci->levels[CA_ACCESS_CHANGE] = lev; break;
		  case 12: ci->levels[CA_MEMO]          = lev; break;
		  case 13: ci->levels[CA_AUTOHALFOP]    = lev; break;
		}
	    }

	    SAFE(read_int16(&ci->accesscount, f));
	    if (ci->accesscount) {
		ci->access = scalloc(ci->accesscount, sizeof(ChanAccess));
		for (j = 0; j < ci->accesscount; j++) {
		    SAFE(read_int16(&ci->access[j].in_use, f));
		    if (ci->access[j].in_use) {
			SAFE(read_int16(&ci->access[j].level, f));
			SAFE(read_string(&s, f));
			if (s)
			    ci->access[j].ni = findnick(s);
			if (ci->access[j].ni == NULL)
			    ci->access[j].in_use = 0;
		    }
		}
	    }

	    SAFE(read_int16(&ci->akickcount, f));
	    if (ci->akickcount) {
		ci->akick = scalloc(ci->akickcount, sizeof(AutoKick));
		for (j = 0; j < ci->akickcount; j++) {
		    SAFE(read_int16(&ci->akick[j].in_use, f));
		    if (ci->akick[j].in_use) {
			SAFE(read_int16(&ci->akick[j].is_nick, f));
			SAFE(read_string(&s, f));
			if (ci->akick[j].is_nick) {
			    ci->akick[j].u.ni = findnick(s);
			    if (!ci->akick[j].u.ni)
				ci->akick[j].in_use = 0;
			} else {
			    ci->akick[j].u.mask = s;
			}
			SAFE(read_string(&s, f));
			if (ci->akick[j].in_use)
			    ci->akick[j].reason = s;
		    }
		}
	    }

	    SAFE(read_int32(&mlock_on, f));
	    SAFE(read_int32(&mlock_off, f));
	    for (j = 0; daylight_modes[j].old != 0; j++) {
		if (mlock_on & daylight_modes[j].old)
		    ci->mlock_on |= daylight_modes[j].new;
		if (mlock_off & daylight_modes[j].old)
		    ci->mlock_off |= daylight_modes[j].new;
	    }
	    SAFE(read_int32(&ci->mlock_limit, f));
	    SAFE(read_string(&ci->mlock_key, f));

	    SAFE(read_int16(&ci->memos.memocount, f));
	    SAFE(read_int16(&ci->memos.memomax, f));
	    if (ci->memos.memocount) {
		Memo *memos;
		memos = smalloc(sizeof(Memo) * ci->memos.memocount);
		ci->memos.memos = memos;
		for (j = 0; j < ci->memos.memocount; j++, memos++) {
		    SAFE(read_int32(&memos->number, f));
		    SAFE(read_int16(&memos->flags, f));
		    SAFE(read_int32(&tmp32, f));
		    memos->time = tmp32;
		    SAFE(read_buffer(memos->sender, f));
		    SAFE(read_string(&memos->text, f));
		}
	    }

	    SAFE(read_string(&ci->entry_message, f));

	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
	*last = NULL;
    } /* for (i) */
    close_db(f);

    /* Check for non-forbidden channels with no founder */
    for (i = 0; i < 256; i++) {
	ChannelInfo *next;
	for (ci = chanlists[i]; ci; ci = next) {
	    next = ci->next;
	    if (!(ci->flags & CI_VERBOTEN) && !ci->founder) {
		if (ci->next)
		    ci->next->prev = ci->prev;
		if (ci->prev)
		    ci->prev->next = ci->next;
		else
		    chanlists[i] = ci->next;
	    }
	}
    }

}

/*************************************************************************/

void dayl_load_oper(const char *sourcedir)
{
    dbFILE *f;
    int16 i, n;
    int32 tmp32;
    char *s;

    f = open_db_ver(sourcedir, "oper.db", 8, 8, NULL);
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	add_adminoper(ADD_ADMIN, s);
    }
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	add_adminoper(ADD_OPER, s);
    }
    SAFE(read_int32(&maxusercnt, f));
    SAFE(read_int32(&tmp32, f));
    maxusertime = tmp32;
    close_db(f);
}

/*************************************************************************/

void dayl_load_akill(const char *sourcedir)
{
    dbFILE *f;
    int i;
    int16 tmp16;
    int32 tmp32;

    f = open_db_ver(sourcedir, "akill.db", 8, 8, NULL);
    read_int16(&tmp16, f);
    nakill = tmp16;
    akills = scalloc(sizeof(*akills), nakill);
    for (i = 0; i < nakill; i++) {
	SAFE(read_string(&akills[i].mask, f));
	SAFE(read_string(&akills[i].reason, f));
	SAFE(read_buffer(akills[i].who, f));
	SAFE(read_int32(&tmp32, f));
	akills[i].time = tmp32;
	SAFE(read_int32(&tmp32, f));
	akills[i].expires = tmp32;
    }
    close_db(f);
}

/*************************************************************************/

void dayl_load_exception(const char *sourcedir)
{
    dbFILE *f;
    int i;
    int16 n;
    int16 tmp16;
    int32 tmp32;

    f = open_db_ver(sourcedir, "exception.db", 8, 8, NULL);
    SAFE(read_int16(&n, f));
    nexceptions = n;
    exceptions = smalloc(sizeof(Exception) * nexceptions);
    for (i = 0; i < nexceptions; i++) {
	SAFE(read_string(&exceptions[i].mask, f));
	SAFE(read_int16(&tmp16, f));
	exceptions[i].limit = tmp16;
	SAFE(read_buffer(exceptions[i].who, f));
	SAFE(read_string(&exceptions[i].reason, f));
	SAFE(read_int32(&tmp32, f));
	exceptions[i].time = tmp32;
	SAFE(read_int32(&tmp32, f));
	exceptions[i].expires = tmp32;
	exceptions[i].num = i;
    }
    close_db(f);
}

/*************************************************************************/

void dayl_load_news(const char *sourcedir)
{
    dbFILE *f;
    int i;
    int16 n;
    int32 tmp32;

    f = open_db_ver(sourcedir, "news.db", 8, 8, NULL);
    SAFE(read_int16(&n, f));
    nnews = n;
    news = smalloc(sizeof(*news) * nnews);
    for (i = 0; i < nnews; i++) {
	SAFE(read_int16(&news[i].type, f));
	SAFE(read_int32(&news[i].num, f));
	SAFE(read_string(&news[i].text, f));
	SAFE(read_buffer(news[i].who, f));
	SAFE(read_int32(&tmp32, f));
	news[i].time = tmp32;
    }
    close_db(f);
}

/*************************************************************************/

void load_daylight(const char *sourcedir, int verbose)
{
    if (verbose)
	printf("Loading nick.db...\n");
    dayl_load_nick(sourcedir);
    if (verbose)
	printf("Loading chan.db...\n");
    dayl_load_chan(sourcedir);
    if (verbose)
	printf("Loading oper.db...\n");
    dayl_load_oper(sourcedir);
    if (verbose)
	printf("Loading akill.db...\n");
    dayl_load_akill(sourcedir);
    if (verbose)
	printf("Loading exception.db...\n");
    dayl_load_exception(sourcedir);
    if (verbose)
	printf("Loading news.db...\n");
    dayl_load_news(sourcedir);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/
/************************ Database loading: Epona ************************/
/*************************************************************************/

void epona_load_nick(const char *sourcedir)
{
    dbFILE *f;
    int32 ver;
    int i, j, c;
    int32 tmp32;
    NickInfo *ni;
    char *s;

    f = open_db_ver(sourcedir, "nick.db", 13, 13, &ver);

    /* Nick cores */
    for (i = 0; i < 1024; i++) {
	while ((c = getc_db(f)) == 1) {
	    ni = scalloc(sizeof(NickInfo), 1);
	    SAFE(read_string(&s, f));
	    strscpy(ni->nick, s, NICKMAX);
	    addnick(ni);
	    SAFE(read_string(&s, f));
	    /* For some reason nick cores can get null passwords (???) */
	    if (!s) {
		fprintf(stderr, "Warning: nick `%s' has null password."
				"  Setting password to nickname.\n", ni->nick);
		s = strdup(ni->nick);
	    }
	    strscpy(ni->pass, s, PASSMAX);
	    SAFE(read_string(&ni->email, f));
	    SAFE(read_string(&s, f));  /* greet */
	    SAFE(read_int32(&tmp32, f));  /* icq */
	    SAFE(read_string(&ni->url, f));
	    SAFE(read_int32(&ni->flags, f));
	    if (ni->flags & 0x2000)		/* NI_SERVICES_ADMIN */
		add_adminoper(ADD_ADMIN, ni->nick);
	    else if (ni->flags & 0x1000)	/* NI_SERVICES_OPER */
		add_adminoper(ADD_OPER, ni->nick);
	    ni->flags &= 0xFFB;
	    if (!NSAllowKillImmed)
		ni->flags &= ~NI_KILL_IMMED;
	    SAFE(read_int16(&ni->language, f));
	    SAFE(read_int16(&ni->accesscount, f));
	    if (ni->accesscount) {
		char **access;
		access = smalloc(sizeof(char *) * ni->accesscount);
		ni->access = access;
		for (j = 0; j < ni->accesscount; j++, access++)
		    SAFE(read_string(access, f));
	    }
	    SAFE(read_int16(&ni->memos.memocount, f));
	    SAFE(read_int16(&ni->memos.memomax, f));
	    if (ni->memos.memocount) {
		Memo *memos;
		memos = smalloc(sizeof(Memo) * ni->memos.memocount);
		ni->memos.memos = memos;
		for (j = 0; j < ni->memos.memocount; j++, memos++) {
		    SAFE(read_int32(&memos->number, f));
		    SAFE(read_int16(&memos->flags, f));
		    SAFE(read_int32(&tmp32, f));
		    memos->time = tmp32;
		    SAFE(read_buffer(memos->sender, f));
		    SAFE(read_string(&memos->text, f));
		}
	    }
	    SAFE(read_int16(&ni->channelcount, f));
	    SAFE(read_int16(&ni->channelmax, f));
	    ni->channelcount = 0;
	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
    } /* for (i) */

    /* Nick aliases */
    for (i = 0; i < 1024; i++) {
	while ((c = getc_db(f)) == 1) {
	    int islink = 0;
	    SAFE(read_string(&s, f));
	    ni = findnick(s);
	    if (!ni) {
		islink = 1;
		ni = scalloc(sizeof(NickInfo), 1);
		strscpy(ni->nick, s, NICKMAX);
	    }
	    SAFE(read_string(&ni->last_usermask, f));
	    if (!ni->last_usermask)
		ni->last_usermask = "@";
	    SAFE(read_string(&ni->last_realname, f));
	    if (!ni->last_realname)
		ni->last_realname = "";
	    SAFE(read_string(&ni->last_quit, f));
	    SAFE(read_int32(&tmp32, f));
	    ni->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    ni->last_seen = tmp32;
	    SAFE(read_int16(&ni->status, f));
	    ni->status &= 6;
	    SAFE(read_string(&s, f));
	    if (islink) {
		NickInfo *root = findnick(s);
		if (!root) {
		    fprintf(stderr, "Warning: nick alias %s has no core, discarding\n",
			    ni->nick);
		    continue;
		    /* Yes, it's memory leakage, and no, we don't care */
		}
		ni->link = root;
		addnick(ni);
		root->linkcount++;
		ni->memos.memomax = MSMaxMemos;
		ni->channelmax = CSMaxReg;
		ni->language = DEF_LANGUAGE;
	    } else {
		if (irc_stricmp(s, ni->nick) != 0) {
		    fprintf(stderr, "Warning: display %s for nick alias %s different from nick core %s\n",
			    s, ni->nick, ni->nick);
		}
	    }
	}
	SAFE(c == 0);
    }

    close_db(f);
}

/*************************************************************************/

static struct {
    int32 old, new;
} epona_modes[] = {
    { 0x00000001, CMODE_i },
    { 0x00000002, CMODE_m },
    { 0x00000004, CMODE_n },
    { 0x00000008, CMODE_p },
    { 0x00000010, CMODE_s },
    { 0x00000020, CMODE_t },
    { 0x00000040, CMODE_k },
    { 0x00000080, CMODE_l },
#ifdef IRC_DAL4_4_15
    { 0x00000100, CMODE_R },
    { 0x00000200, 0 }, /* CMODE_r, never set in mlock */
#endif
#if defined(IRC_BAHAMUT) || defined(IRC_UNREAL)
    { 0x00000400, CMODE_c },
    { 0x00008000, CMODE_O },
#endif
#ifdef IRC_UNREAL
    { 0x00000800, CMODE_A },
    { 0x00001000, CMODE_H },
    { 0x00002000, CMODE_K },
    { 0x00004000, 0 }, /* CMODE_L, not currently supported */
    { 0x00010000, CMODE_Q },
    { 0x00020000, CMODE_S },
    { 0x00040000, CMODE_V },
    { 0x00080000, 0 }, /* CMODE_f, not currently supported */
    { 0x00100000, CMODE_G },
    { 0x00200000, CMODE_C },
    { 0x00400000, CMODE_u },
#endif
    { 0, 0 }
};

void epona_load_chan(const char *sourcedir)
{
    dbFILE *f;
    int32 ver;
    int i, j, c;
    ChannelInfo *ci, **last, *prev;
    int32 tmp32, mlock_on, mlock_off;

    f = open_db_ver(sourcedir, "chan.db", 14, 15, &ver);

    for (i = 0; i < 256; i++) {
	int16 tmp16;
	int n_levels;
	char *s;

	last = &chanlists[i];
	prev = NULL;
	while ((c = getc_db(f)) == 1) {
	    ci = scalloc(sizeof(ChannelInfo), 1);
	    *last = ci;
	    last = &ci->next;
	    ci->prev = prev;
	    prev = ci;
	    SAFE(read_buffer(ci->name, f));
	    SAFE(read_string(&s, f));
	    if (s)
		ci->founder = findnick(s);
	    SAFE(read_string(&s, f));
	    if (s)
		ci->successor = findnick(s);
	    if (ci->founder == ci->successor)
		ci->successor = NULL;
	    if (ci->founder != NULL) {
		NickInfo *ni = ci->founder;
		while (ni) {
		    ni->channelcount++;
		    ni = ni->link;
		}
	    }
	    SAFE(read_buffer(ci->founderpass, f));
	    SAFE(read_string(&ci->desc, f));
	    if (!ci->desc)
		ci->desc = "";
	    SAFE(read_string(&ci->url, f));
	    SAFE(read_string(&ci->email, f));
	    SAFE(read_int32(&tmp32, f));
	    ci->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    ci->last_used = tmp32;
	    SAFE(read_string(&ci->last_topic, f));
	    SAFE(read_buffer(ci->last_topic_setter, f));
	    SAFE(read_int32(&tmp32, f));
	    ci->last_topic_time = tmp32;
	    SAFE(read_int32(&ci->flags, f));
	    ci->flags &= 0xFDF;
	    SAFE(read_string(&s, f));		/* forbidby */
	    SAFE(read_string(&s, f));		/* forbidreason */
	    SAFE(read_int16(&tmp16, f));	/* bantype */

	    SAFE(read_int16(&tmp16, f));
	    n_levels = tmp16;
	    init_levels(ci);
	    for (j = 0; j < n_levels; j++) {
		int16 lev;
		SAFE(read_int16(&lev, f));
		switch (j) {
		  case  0: ci->levels[CA_INVITE]        = lev; break;
		  case  1: ci->levels[CA_AKICK]         = lev; break;
		  case  2: ci->levels[CA_SET]           = lev; break;
		  case  3: ci->levels[CA_UNBAN]         = lev; break;
		  case  4: ci->levels[CA_AUTOOP]        = lev; break;
		  case  5: ci->levels[CA_AUTODEOP]      = lev; break;
		  case  6: ci->levels[CA_AUTOVOICE]     = lev; break;
		  case  7: ci->levels[CA_OPDEOP]        = lev; break;
		  case  8: ci->levels[CA_ACCESS_LIST]   = lev; break;
		  case  9: ci->levels[CA_CLEAR]         = lev; break;
		  case 10: ci->levels[CA_NOJOIN]        = lev; break;
		  case 11: ci->levels[CA_ACCESS_CHANGE] = lev; break;
		  case 12: ci->levels[CA_MEMO]          = lev; break;
		  case 20: ci->levels[CA_VOICE]         = lev; break;
		  case 22: ci->levels[CA_AUTOHALFOP]    = lev; break;
		  case 23: ci->levels[CA_AUTOPROTECT]   = lev; break;
		  case 26: ci->levels[CA_HALFOP]        = lev; break;
		  case 28: ci->levels[CA_PROTECT]       = lev; break;
		}
	    }

	    SAFE(read_int16(&ci->accesscount, f));
	    if (ci->accesscount) {
		ci->access = scalloc(ci->accesscount, sizeof(ChanAccess));
		for (j = 0; j < ci->accesscount; j++) {
		    SAFE(read_int16(&ci->access[j].in_use, f));
		    if (ci->access[j].in_use) {
			SAFE(read_int16(&ci->access[j].level, f));
			SAFE(read_string(&s, f));
			SAFE(read_int32(&tmp32, f));	/* last used */
			if (s)
			    ci->access[j].ni = findnick(s);
			if (ci->access[j].ni == NULL)
			    ci->access[j].in_use = 0;
		    }
		}
	    }

	    SAFE(read_int16(&ci->akickcount, f));
	    if (ci->akickcount) {
		ci->akick = scalloc(ci->akickcount, sizeof(AutoKick));
		for (j = 0; j < ci->akickcount; j++) {
		    SAFE(read_int16(&ci->akick[j].in_use, f));
		    if (ver == 14) {
			SAFE(read_int16(&ci->akick[j].is_nick, f));
		    } else {
			ci->akick[j].is_nick = (ci->akick[j].in_use&2) ? 1 : 0;
			ci->akick[j].in_use &= 1;
		    }
		    if (ci->akick[j].in_use) {
			SAFE(read_string(&s, f));
			if (ci->akick[j].is_nick) {
			    ci->akick[j].u.ni = findnick(s);
			    if (!ci->akick[j].u.ni)
				ci->akick[j].in_use = 0;
			} else {
			    ci->akick[j].u.mask = s;
			}
			SAFE(read_string(&s, f));
			if (ci->akick[j].in_use)
			    ci->akick[j].reason = s;
			SAFE(read_string(&s, f));	/* setter */
			SAFE(read_int32(&tmp32, f));	/* addtime */
		    }
		}
	    }

	    SAFE(read_int32(&mlock_on, f));
	    SAFE(read_int32(&mlock_off, f));
	    for (j = 0; epona_modes[j].old != 0; j++) {
		if (mlock_on & epona_modes[j].old)
		    ci->mlock_on |= epona_modes[j].new;
		if (mlock_off & epona_modes[j].old)
		    ci->mlock_off |= epona_modes[j].new;
	    }
	    SAFE(read_int32(&ci->mlock_limit, f));
	    SAFE(read_string(&ci->mlock_key, f));
	    SAFE(read_string(&s, f));	/* mlock_flood */
	    SAFE(read_string(&s, f));	/* mlock_redirect */

	    SAFE(read_int16(&ci->memos.memocount, f));
	    SAFE(read_int16(&ci->memos.memomax, f));
	    if (ci->memos.memocount) {
		Memo *memos;
		memos = smalloc(sizeof(Memo) * ci->memos.memocount);
		ci->memos.memos = memos;
		for (j = 0; j < ci->memos.memocount; j++, memos++) {
		    SAFE(read_int32(&memos->number, f));
		    SAFE(read_int16(&memos->flags, f));
		    SAFE(read_int32(&tmp32, f));
		    memos->time = tmp32;
		    SAFE(read_buffer(memos->sender, f));
		    SAFE(read_string(&memos->text, f));
		}
	    }

	    SAFE(read_string(&ci->entry_message, f));

	    /* BotServ-related */
	    SAFE(read_string(&s, f));
	    SAFE(read_int32(&tmp32, f));
	    SAFE(read_int16(&tmp16, f));
	    for (j = tmp16; j > 0; j--)
		SAFE(read_int16(&tmp16, f));
	    SAFE(read_int16(&tmp16, f));
	    SAFE(read_int16(&tmp16, f));
	    SAFE(read_int16(&tmp16, f));
	    SAFE(read_int16(&tmp16, f));
	    SAFE(read_int16(&tmp16, f));
	    SAFE(read_int16(&tmp16, f));
	    for (j = tmp16; j > 0; j--) {
		SAFE(read_int16(&tmp16, f));
		if (tmp16) {
		    SAFE(read_string(&s, f));
		    SAFE(read_int16(&tmp16, f));
		}
	    }

	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
	*last = NULL;
    } /* for (i) */
    close_db(f);

    /* Check for non-forbidden channels with no founder */
    for (i = 0; i < 256; i++) {
	ChannelInfo *next;
	for (ci = chanlists[i]; ci; ci = next) {
	    next = ci->next;
	    if (!(ci->flags & CI_VERBOTEN) && !ci->founder) {
		if (ci->next)
		    ci->next->prev = ci->prev;
		if (ci->prev)
		    ci->prev->next = ci->next;
		else
		    chanlists[i] = ci->next;
	    }
	}
    }

}

/*************************************************************************/

void epona_load_oper(const char *sourcedir)
{
    dbFILE *f;
    int32 ver;
    int16 i, n, tmp16;
    int32 tmp32;
    char *s;

    f = open_db_ver(sourcedir, "oper.db", 11, 13, &ver);
    if (ver == 12) {
	fprintf(stderr, "Unsupported version number (%d) on oper.db.\n"
			"Are you using a beta version of Epona?\n", ver);
	exit(1);
    }

    /* stats */
    SAFE(read_int32(&maxusercnt, f));
    SAFE(read_int32(&tmp32, f));
    maxusertime = tmp32;
    /* akills */
    SAFE(read_int16(&n, f));
    nakill = n;
    akills = smalloc(sizeof(*akills) * n);
    for (i = 0; i < n; i++) {
	char *user, *host;
	SAFE(read_string(&user, f));
	SAFE(read_string(&host, f));
	s = smalloc(strlen(user)+strlen(host)+1);
	sprintf(s, "%s@%s", user, host);
	akills[i].mask = s;
	SAFE(read_string(&s, f));
	strscpy(akills[i].who, s, NICKMAX);
	SAFE(read_string(&akills[i].reason, f));
	SAFE(read_int32(&tmp32, f));
	akills[i].time = tmp32;
	SAFE(read_int32(&tmp32, f));
	akills[i].expires = tmp32;
    }
    /* sglines */
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));  /* mask */
	SAFE(read_string(&s, f));  /* by */
	SAFE(read_string(&s, f));  /* reason */
	SAFE(read_int32(&tmp32, f));  /* seton */
	SAFE(read_int32(&tmp32, f));  /* expires */
    }
    if (ver >= 13) {
	/* sqlines */
	SAFE(read_int16(&n, f));
	for (i = 0; i < n; i++) {
	    SAFE(read_string(&s, f));
	    SAFE(read_string(&s, f));
	    SAFE(read_string(&s, f));
	    SAFE(read_int32(&tmp32, f));
	    SAFE(read_int32(&tmp32, f));
	}
    }
    /* szlines */
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	SAFE(read_string(&s, f));
	SAFE(read_string(&s, f));
	SAFE(read_int32(&tmp32, f));
	SAFE(read_int32(&tmp32, f));
    }
    if (ver >= 13) {
	/* proxy host cache */
	for (i = 0; i < 1024; i++) {
	    char c;
	    SAFE(read_int8(&c, f));
	    while (c) {
		SAFE(read_string(&s, f));  /* host */
		SAFE(read_int16(&tmp16, f));  /* status */
		SAFE(read_int32(&tmp32, f));  /* used */
		SAFE(read_int8(&c, f));
	    }
	}
    }

    close_db(f);
}

/*************************************************************************/

void epona_load_exception(const char *sourcedir)
{
    dbFILE *f;
    int32 ver;
    int i;
    int16 n;
    int16 tmp16;
    int32 tmp32;

    f = open_db_ver(sourcedir, "exception.db", 9, 9, &ver);
    SAFE(read_int16(&n, f));
    nexceptions = n;
    exceptions = smalloc(sizeof(Exception) * nexceptions);
    for (i = 0; i < nexceptions; i++) {
	SAFE(read_string(&exceptions[i].mask, f));
	SAFE(read_int16(&tmp16, f));
	exceptions[i].limit = tmp16;
	SAFE(read_buffer(exceptions[i].who, f));
	SAFE(read_string(&exceptions[i].reason, f));
	SAFE(read_int32(&tmp32, f));
	exceptions[i].time = tmp32;
	SAFE(read_int32(&tmp32, f));
	exceptions[i].expires = tmp32;
	exceptions[i].num = i;
    }
    close_db(f);
}

/*************************************************************************/

void epona_load_news(const char *sourcedir)
{
    dbFILE *f;
    int32 ver;
    int i;
    int16 n;
    int32 tmp32;

    f = open_db_ver(sourcedir, "news.db", 9, 9, &ver);
    SAFE(read_int16(&n, f));
    nnews = n;
    news = smalloc(sizeof(*news) * nnews);
    for (i = 0; i < nnews; i++) {
	SAFE(read_int16(&news[i].type, f));
	SAFE(read_int32(&news[i].num, f));
	SAFE(read_string(&news[i].text, f));
	SAFE(read_buffer(news[i].who, f));
	SAFE(read_int32(&tmp32, f));
	news[i].time = tmp32;
    }
    close_db(f);
}

/*************************************************************************/

void load_epona(const char *sourcedir, int verbose)
{
    if (verbose)
	printf("Loading nick.db...\n");
    epona_load_nick(sourcedir);
    if (verbose)
	printf("Loading chan.db...\n");
    epona_load_chan(sourcedir);
    if (verbose)
	printf("Loading oper.db...\n");
    epona_load_oper(sourcedir);
    if (verbose)
	printf("Loading exception.db...\n");
    epona_load_exception(sourcedir);
    if (verbose)
	printf("Loading news.db...\n");
    epona_load_news(sourcedir);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/
/******************** Database loading: PTlink 2.18.x ********************/
/*************************************************************************/

void pt218_load_nick(const char *sourcedir)
{
    char filename[PATH_MAX+1];
    dbFILE *f;
    int i, j, c;
    int16 tmp16;
    int32 tmp32, total, count;
    NickInfo *ni, **last, *prev;
    char *s, ch;

    snprintf(filename, sizeof(filename), "%s/nick.db", sourcedir);
    if (!(f = open_db(NULL, filename, "r")))
	return;
    SAFE(read_int8(&ch, f));
    SAFE(read_int16(&tmp16, f));
    if (ch != -1 || tmp16 != 6) {
	fprintf(stderr, "Wrong version number on %s\n", filename);
	exit(1);
    }

    SAFE(read_int32(&total, f));
    count = 0;
    for (i = 0; i < 256; i++) {
	last = &nicklists[i];
	prev = NULL;
	while ((c = getc_db(f)) == 1) {
	    ni = scalloc(sizeof(NickInfo), 1);
	    *last = ni;
	    last = &ni->next;
	    ni->prev = prev;
	    prev = ni;
	    SAFE(read_buffer(ni->nick, f));
	    SAFE(read_buffer(ni->pass, f));
	    SAFE(read_string(&ni->url, f));
	    SAFE(read_string(&ni->email, f));
	    SAFE(read_string(&s, f));  /* icq_number */
	    SAFE(read_string(&s, f));  /* location */
	    SAFE(read_string(&ni->last_usermask, f));
	    if (!ni->last_usermask)
		ni->last_usermask = "@";
	    SAFE(read_string(&ni->last_realname, f));
	    if (!ni->last_realname)
		ni->last_realname = "";
	    SAFE(read_string(&ni->last_quit, f));
	    SAFE(read_int32(&tmp32, f));
	    ni->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));  /* last_identify */
	    SAFE(read_int32(&tmp32, f));
	    ni->last_seen = tmp32;
	    SAFE(read_int32(&tmp32, f));  /* birth_date */
	    SAFE(read_int16(&ni->status, f));
	    ni->status &= ~(NS_TEMPORARY | NS_ENCRYPTEDPW);
	    SAFE(read_int16(&tmp16, f));  /* crypt_method */
	    if (tmp16 == 3)
		ni->status |= NS_ENCRYPTEDPW;
	    else if (tmp16 != 0) {
		fprintf(stderr, "%s: password encrypted with unsupported"
				" method %d, aborting\n", filename, tmp16);
		exit(1);
	    }
	    SAFE(read_int32(&tmp32, f));  /* news_mask */
	    SAFE(read_int16(&tmp16, f));  /* news_status */
	    SAFE(read_string((char **)&ni->link, f));
	    SAFE(read_int16(&ni->linkcount, f));
	    if (ni->link) {
		SAFE(read_int16(&ni->channelcount, f));
		ni->flags = 0;
		ni->accesscount = 0;
		ni->access = NULL;
		ni->memos.memocount = 0;
		ni->memos.memomax = MSMaxMemos;
		ni->memos.memos = NULL;
		ni->channelmax = CSMaxReg;
		ni->language = DEF_LANGUAGE;
	    } else {
		SAFE(read_int32(&ni->flags, f));
		SAFE(read_int32(&tmp32, f));  /* online */
		if (ni->flags & 0x4002) {  /* NI_[O]SUSPENDED */
		    ni->suspendinfo = scalloc(sizeof(SuspendInfo), 1);
		    strcpy(ni->suspendinfo->who, "<unknown>");
		    ni->suspendinfo->reason = "<unknown>";
		    SAFE(read_int32(&tmp32, f));
		    ni->suspendinfo->expires = tmp32;
		}
		ni->flags &= 0xFF9;
		if (!NSAllowKillImmed)
		    ni->flags &= ~NI_KILL_IMMED;
		SAFE(read_int16(&tmp16, f));  /* ajoincount */
		for (j = 0; j < tmp16; j++)   /* ajoin[] */
		    SAFE(read_string(&s, f));
		ni->accesscount = 0;
		ni->access = NULL;
		SAFE(read_int16(&ni->memos.memocount, f));
		SAFE(read_int16(&ni->memos.memomax, f));
		if (ni->memos.memocount) {
		    Memo *memos;
		    memos = smalloc(sizeof(Memo) * ni->memos.memocount);
		    ni->memos.memos = memos;
		    for (j = 0; j < ni->memos.memocount; j++, memos++) {
			SAFE(read_int32(&memos->number, f));
			SAFE(read_int16(&memos->flags, f));
			SAFE(read_int32(&tmp32, f));
			memos->time = tmp32;
			SAFE(read_buffer(memos->sender, f));
			SAFE(read_string(&memos->text, f));
		    }
		}
		SAFE(read_int16(&tmp16, f));  /* notes.count */
		j = tmp16;
		SAFE(read_int16(&tmp16, f));  /* notes.max */
		while (j--)  /* notes.note[] */
		    SAFE(read_string(&s, f));
		SAFE(read_int16(&ni->channelcount, f));
		SAFE(read_int16(&ni->channelmax, f));
		SAFE(read_int16(&tmp16, f));
		switch (tmp16) {
		  case 0:  ni->language = LANG_EN_US;   break;
		  case 1:  ni->language = LANG_PT;      break;
		  case 2:  ni->language = LANG_TR;      break;
		  case 3:  ni->language = LANG_DE;      break;
		  case 4:  ni->language = LANG_IT;      break;
		  default: ni->language = DEF_LANGUAGE; break;
		}
	    }
	    ni->channelcount = 0;
	    count++;
	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
	*last = NULL;
    } /* for (i) */
    close_db(f);
    if (count != total) {
	fprintf(stderr, "%s: error: expected %d nicks, got %d\n",
		filename, total, count);
	exit(1);
    }

    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    if (ni->link)
		ni->link = findnick((char *)ni->link);
	}
    }
}

/*************************************************************************/

static struct {
    int32 old, new;
} pt218_modes[] = {
    { 0x00000001, CMODE_i },
    { 0x00000002, CMODE_m },
    { 0x00000004, CMODE_n },
    { 0x00000008, CMODE_p },
    { 0x00000010, CMODE_s },
    { 0x00000020, CMODE_t },
    { 0x00000040, CMODE_k },
    { 0x00000080, CMODE_l },
#ifdef IRC_DAL4_4_15
    { 0x00000200, CMODE_R },
#endif
#if defined(IRC_BAHAMUT) || defined(IRC_UNREAL)
    { 0x00000400, CMODE_c },
    { 0x00001000, CMODE_O },
#endif
#ifdef IRC_UNREAL
    { 0x00002000, CMODE_A },
    { 0x00008000, 0 }, /* CMODE_f equivalent (no dup lines within 10 secs) */
#endif
    { 0, 0 }
};

void pt218_load_chan(const char *sourcedir)
{
    char filename[PATH_MAX+1];
    dbFILE *f;
    int i, j, c;
    ChannelInfo *ci, **last, *prev;
    char ch;
    int16 tmp16, mlock_on, mlock_off;
    int32 tmp32;

    snprintf(filename, sizeof(filename), "%s/chan.db", sourcedir);
    if (!(f = open_db(NULL, filename, "r")))
	return;
    SAFE(read_int8(&ch, f));
    SAFE(read_int16(&tmp16, f));
    if (ch != -1 || tmp16 != 7) {
	fprintf(stderr, "Wrong version number on %s\n", filename);
	exit(1);
    }

    for (i = 0; i < 256; i++) {
	int n_levels;
	char *s;

	last = &chanlists[i];
	prev = NULL;
	while ((c = getc_db(f)) == 1) {
	    ci = scalloc(sizeof(ChannelInfo), 1);
	    *last = ci;
	    last = &ci->next;
	    ci->prev = prev;
	    prev = ci;
	    SAFE(read_buffer(ci->name, f));
	    SAFE(read_string(&s, f));
	    if (s)
		ci->founder = findnick(s);
	    SAFE(read_string(&s, f));
	    if (s)
		ci->successor = findnick(s);
	    if (ci->founder == ci->successor)
		ci->successor = NULL;
	    if (ci->founder != NULL) {
		NickInfo *ni = ci->founder;
		while (ni) {
		    ni->channelcount++;
		    ni = ni->link;
		}
	    }
	    SAFE(read_int16(&tmp16, f));  /* maxusers */
	    SAFE(read_int32(&tmp32, f));  /* maxtime */
	    SAFE(read_buffer(ci->founderpass, f));
	    SAFE(read_string(&ci->desc, f));
	    if (!ci->desc)
		ci->desc = "";
	    SAFE(read_string(&ci->url, f));
	    SAFE(read_string(&ci->email, f));
	    SAFE(read_int32(&tmp32, f));
	    ci->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    ci->last_used = tmp32;
	    SAFE(read_string(&ci->last_topic, f));
	    SAFE(read_buffer(ci->last_topic_setter, f));
	    SAFE(read_int32(&tmp32, f));
	    ci->last_topic_time = tmp32;
	    SAFE(read_int32(&ci->flags, f));
	    SAFE(read_int16(&tmp16, f));  /* crypt_method */
	    if (ci->flags & 0x1000)
		SAFE(read_int32(&tmp32, f));  /* drop_time */
	    ci->flags &= 0xEBF;
	    if (tmp16 == 3)
		ci->flags |= CI_ENCRYPTEDPW;
	    else if (tmp16 != 0) {
		fprintf(stderr, "%s: password encrypted with unsupported"
				" method %d, aborting\n", filename, tmp16);
		exit(1);
	    }

	    SAFE(read_int16(&tmp16, f));
	    n_levels = tmp16;
	    init_levels(ci);
	    for (j = 0; j < n_levels; j++) {
		int16 lev;
		SAFE(read_int16(&lev, f));
		switch (j) {
		  case  0: ci->levels[CA_INVITE]        = lev; break;
		  case  1: ci->levels[CA_AKICK]         = lev; break;
		  case  2: ci->levels[CA_SET]           = lev; break;
		  case  3: ci->levels[CA_UNBAN]         = lev; break;
		  case  4: ci->levels[CA_AUTOOP]        = lev; break;
		  case  5: ci->levels[CA_AUTODEOP]      = lev; break;
		  case  6: ci->levels[CA_AUTOVOICE]     = lev; break;
		  case  7: ci->levels[CA_OPDEOP]        = lev; break;
		  case  8: ci->levels[CA_ACCESS_LIST]   = lev; break;
		  case  9: ci->levels[CA_CLEAR]         = lev; break;
		  case 10: ci->levels[CA_NOJOIN]        = lev; break;
		  case 11: ci->levels[CA_ACCESS_CHANGE] = lev; break;
		  case 12: ci->levels[CA_MEMO]          = lev; break;
		  case 13: ci->levels[CA_PROTECT]       = lev; break;
		}
	    }

	    SAFE(read_int16(&ci->accesscount, f));
	    if (ci->accesscount) {
		ci->access = scalloc(ci->accesscount, sizeof(ChanAccess));
		for (j = 0; j < ci->accesscount; j++) {
		    SAFE(read_int16(&ci->access[j].in_use, f));
		    if (ci->access[j].in_use) {
			SAFE(read_int16(&ci->access[j].level, f));
			SAFE(read_string(&s, f));
			if (s)
			    ci->access[j].ni = findnick(s);
			if (ci->access[j].ni == NULL)
			    ci->access[j].in_use = 0;
			SAFE(read_string(&s, f));  /* who */
		    }
		}
	    }

	    SAFE(read_int16(&ci->akickcount, f));
	    if (ci->akickcount) {
		ci->akick = scalloc(ci->akickcount, sizeof(AutoKick));
		for (j = 0; j < ci->akickcount; j++) {
		    SAFE(read_int16(&ci->akick[j].in_use, f));
		    if (ci->akick[j].in_use) {
			ci->akick[j].is_nick = 0;
			SAFE(read_string(&ci->akick[j].u.mask, f));
			SAFE(read_string(&ci->akick[j].reason, f));
			SAFE(read_string(&s, f));	/* who */
			SAFE(read_int32(&tmp32, f));	/* last_kick */
		    }
		}
	    }

	    SAFE(read_int16(&mlock_on, f));
	    SAFE(read_int16(&mlock_off, f));
	    for (j = 0; pt218_modes[j].old != 0; j++) {
		if (mlock_on & pt218_modes[j].old)
		    ci->mlock_on |= pt218_modes[j].new;
		if (mlock_off & pt218_modes[j].old)
		    ci->mlock_off |= pt218_modes[j].new;
	    }
	    SAFE(read_int32(&ci->mlock_limit, f));
	    SAFE(read_string(&ci->mlock_key, f));

	    SAFE(read_int16(&ci->memos.memocount, f));
	    SAFE(read_int16(&ci->memos.memomax, f));
	    if (ci->memos.memocount) {
		Memo *memos;
		memos = smalloc(sizeof(Memo) * ci->memos.memocount);
		ci->memos.memos = memos;
		for (j = 0; j < ci->memos.memocount; j++, memos++) {
		    SAFE(read_int32(&memos->number, f));
		    SAFE(read_int16(&memos->flags, f));
		    SAFE(read_int32(&tmp32, f));
		    memos->time = tmp32;
		    SAFE(read_buffer(memos->sender, f));
		    SAFE(read_string(&memos->text, f));
		}
	    }

	    SAFE(read_string(&ci->entry_message, f));

	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
	*last = NULL;
    } /* for (i) */
    close_db(f);

    /* Check for non-forbidden channels with no founder */
    for (i = 0; i < 256; i++) {
	ChannelInfo *next;
	for (ci = chanlists[i]; ci; ci = next) {
	    next = ci->next;
	    if (!(ci->flags & CI_VERBOTEN) && !ci->founder) {
		if (ci->next)
		    ci->next->prev = ci->prev;
		if (ci->prev)
		    ci->prev->next = ci->next;
		else
		    chanlists[i] = ci->next;
	    }
	}
    }

}

/*************************************************************************/

void pt218_load_oper(const char *sourcedir)
{
    char filename[PATH_MAX+1];
    dbFILE *f;
    int16 i, n, tmp16;
    int32 tmp32;
    char *s, ch;

    snprintf(filename, sizeof(filename), "%s/oper.db", sourcedir);
    if (!(f = open_db(NULL, filename, "r")))
	return;
    SAFE(read_int8(&ch, f));
    SAFE(read_int16(&tmp16, f));
    if (ch != -1 || tmp16 < 1 || tmp16 > 2) {
	fprintf(stderr, "Wrong version number on %s\n", filename);
	exit(1);
    }
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	add_adminoper(ADD_ADMIN, s);
    }
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	add_adminoper(ADD_OPER, s);
    }
    SAFE(read_int32(&maxusercnt, f));
    SAFE(read_int32(&tmp32, f));
    maxusertime = tmp32;
    close_db(f);
}

/*************************************************************************/

void pt218_load_akill(const char *sourcedir)
{
    char filename[PATH_MAX+1];
    dbFILE *f;
    int i;
    int16 tmp16, n;
    int32 tmp32;
    char ch;

    snprintf(filename, sizeof(filename), "%s/akill.db", sourcedir);
    if (!(f = open_db(NULL, filename, "r")))
	return;
    SAFE(read_int8(&ch, f));
    SAFE(read_int16(&tmp16, f));
    if (ch != -1 || tmp16 != 1) {
	fprintf(stderr, "Wrong version number on %s\n", filename);
	exit(1);
    }
    SAFE(read_int16(&n, f));
    nakill = n;
    akills = smalloc(sizeof(*akills) * nakill);
    for (i = 0; i < nakill; i++) {
	SAFE(read_string(&akills[i].mask, f));
	SAFE(read_string(&akills[i].reason, f));
	SAFE(read_buffer(akills[i].who, f));
	SAFE(read_int32(&tmp32, f));
	akills[i].time = tmp32;
	SAFE(read_int32(&tmp32, f));
	akills[i].expires = tmp32;
    }
    close_db(f);
}

/*************************************************************************/

void pt218_load_news(const char *sourcedir)
{
    char filename[PATH_MAX+1];
    dbFILE *f;
    int i;
    int16 tmp16, n;
    int32 tmp32;
    char ch;

    snprintf(filename, sizeof(filename), "%s/news.db", sourcedir);
    if (!(f = open_db(NULL, filename, "r")))
	return;
    SAFE(read_int8(&ch, f));
    SAFE(read_int16(&tmp16, f));
    if (ch != -1 || tmp16 != 1) {
	fprintf(stderr, "Wrong version number on %s\n", filename);
	exit(1);
    }
    SAFE(read_int16(&n, f));
    nnews = n;
    news = smalloc(sizeof(*news) * nnews);
    for (i = 0; i < nnews; i++) {
	SAFE(read_int16(&news[i].type, f));
	SAFE(read_int32(&news[i].num, f));
	SAFE(read_string(&news[i].text, f));
	SAFE(read_buffer(news[i].who, f));
	SAFE(read_int32(&tmp32, f));
	news[i].time = tmp32;
    }
    close_db(f);
}

/*************************************************************************/

void load_ptlink_2_18(const char *sourcedir, int verbose)
{
    if (verbose)
	printf("Loading nick.db...\n");
    pt218_load_nick(sourcedir);
    if (verbose)
	printf("Loading chan.db...\n");
    pt218_load_chan(sourcedir);
    if (verbose)
	printf("Loading oper.db...\n");
    pt218_load_oper(sourcedir);
    if (verbose)
	printf("Loading akill.db...\n");
    pt218_load_akill(sourcedir);
    if (verbose)
	printf("Loading news.db...\n");
    pt218_load_news(sourcedir);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/
/*********************** Database loading: IRCS 1.2 **********************/
/*************************************************************************/

void ircs12_load_nick(const char *sourcedir)
{
    dbFILE *f;
    int i, j, c;
    int32 tmp32;
    NickInfo *ni, **last, *prev;

    f = open_db_ver(sourcedir, "nick.db", 8, 8, NULL);
    for (i = 0; i < 256; i++) {
	last = &nicklists[i];
	prev = NULL;
	while ((c = getc_db(f)) == 1) {
	    char passbuf[16];
	    ni = scalloc(sizeof(NickInfo), 1);
	    *last = ni;
	    last = &ni->next;
	    ni->prev = prev;
	    prev = ni;
	    SAFE(read_buffer(ni->nick, f));
	    SAFE(read_buffer(passbuf, f));
	    memcpy(ni->pass, passbuf, sizeof(passbuf));
	    SAFE(read_string(&ni->url, f));
	    SAFE(read_string(&ni->email, f));
	    SAFE(read_string(&ni->last_usermask, f));
	    if (!ni->last_usermask)
		ni->last_usermask = "@";
	    SAFE(read_string(&ni->last_realname, f));
	    if (!ni->last_realname)
		ni->last_realname = "";
	    SAFE(read_string(&ni->last_quit, f));
	    SAFE(read_int32(&tmp32, f));
	    ni->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    ni->last_seen = tmp32;
	    SAFE(read_int16(&ni->status, f));
	    ni->status &= ~NS_TEMPORARY;
	    SAFE(read_string((char **)&ni->link, f));
	    SAFE(read_int16(&ni->linkcount, f));
	    if (ni->link) {
		SAFE(read_int16(&ni->channelcount, f));
		ni->flags = 0;
		ni->accesscount = 0;
		ni->access = NULL;
		ni->memos.memocount = 0;
		ni->memos.memomax = MSMaxMemos;
		ni->memos.memos = NULL;
		ni->channelmax = CSMaxReg;
		ni->language = DEF_LANGUAGE;
	    } else {
		SAFE(read_int32(&ni->flags, f));
		ni->flags &= 0xFFF;
		if (!NSAllowKillImmed)
		    ni->flags &= ~NI_KILL_IMMED;
		SAFE(read_int16(&ni->accesscount, f));
		if (ni->accesscount) {
		    char **access;
		    access = smalloc(sizeof(char *) * ni->accesscount);
		    ni->access = access;
		    for (j = 0; j < ni->accesscount; j++, access++)
			SAFE(read_string(access, f));
		}
		SAFE(read_int16(&ni->memos.memocount, f));
		SAFE(read_int16(&ni->memos.memomax, f));
		if (ni->memos.memocount) {
		    Memo *memos;
		    memos = smalloc(sizeof(Memo) * ni->memos.memocount);
		    ni->memos.memos = memos;
		    for (j = 0; j < ni->memos.memocount; j++, memos++) {
			SAFE(read_int32(&memos->number, f));
			SAFE(read_int16(&memos->flags, f));
			SAFE(read_int32(&tmp32, f));
			memos->time = tmp32;
			SAFE(read_buffer(memos->sender, f));
			SAFE(read_string(&memos->text, f));
		    }
		}
		SAFE(read_int16(&ni->channelcount, f));
		SAFE(read_int16(&ni->channelmax, f));
		SAFE(read_int16(&ni->language, f));
	    }
	    ni->channelcount = 0;
	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
	*last = NULL;
    } /* for (i) */
    close_db(f);

    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    if (ni->link)
		ni->link = findnick((char *)ni->link);
	}
    }
}

/*************************************************************************/

void ircs12_load_chan(const char *sourcedir)
{
    dbFILE *f;
    int i, j, c;
    ChannelInfo *ci, **last, *prev;
    int32 tmp32;

    f = open_db_ver(sourcedir, "chan.db", 8, 8, NULL);

    for (i = 0; i < 256; i++) {
	int16 tmp16;
	int n_levels;
	char *s;

	last = &chanlists[i];
	prev = NULL;
	while ((c = getc_db(f)) == 1) {
	    char channame[204];
	    char passbuf[16];
	    ci = scalloc(sizeof(ChannelInfo), 1);
	    SAFE(read_buffer(channame, f));
	    if (strlen(channame) >= CHANMAX) {
		static int warned = 0;
		fprintf(stderr, "Warning: Channel %s has name longer than %d"
				" characters; deleting it.\n",
			channame, CHANMAX);
		if (!warned) {
		    fprintf(stderr, "*** If you want to keep channels with"
				    " long names, change CHANMAX to 204 in\n"
				    "config.h and recompile Services and"
				    " import-db.\n");
		    warned = 1;
		}
		/* Don't link it into the list.  This wastes memory, but oh
		 * well. */
	    } else {
		strcpy(ci->name, channame);
		*last = ci;
		last = &ci->next;
		ci->prev = prev;
		prev = ci;
	    }
	    SAFE(read_string(&s, f));
	    if (s)
		ci->founder = findnick(s);
	    ci->successor = NULL;
	    if (ci->founder != NULL) {
		NickInfo *ni = ci->founder;
		while (ni) {
		    ni->channelcount++;
		    ni = ni->link;
		}
	    }
	    SAFE(read_buffer(passbuf, f));
	    memcpy(ci->founderpass, passbuf, sizeof(passbuf));
	    SAFE(read_string(&ci->desc, f));
	    if (!ci->desc)
		ci->desc = "";
	    SAFE(read_string(&ci->url, f));
	    SAFE(read_string(&ci->email, f));
	    SAFE(read_int16(&tmp16, f));  /* autoop */
	    SAFE(read_int32(&tmp32, f));
	    ci->time_registered = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    ci->last_used = tmp32;
	    SAFE(read_string(&ci->last_topic, f));
	    SAFE(read_buffer(ci->last_topic_setter, f));
	    SAFE(read_int32(&tmp32, f));
	    ci->last_topic_time = tmp32;
	    SAFE(read_int32(&ci->flags, f));
	    ci->flags &= 0x7FF;

	    SAFE(read_int16(&tmp16, f));
	    n_levels = tmp16;
	    init_levels(ci);
	    for (j = 0; j < n_levels; j++) {
		int16 lev;
		SAFE(read_int16(&lev, f));
		if (lev == 10)
		    lev = ACCLEV_FOUNDER;
		else if (lev == -2)
		    lev = ACCLEV_INVALID;
		else if (lev >= 7)  /* 7 == SOP */
		    lev += 3;
		switch (j) {
		  case  0: ci->levels[CA_INVITE]        = lev; break;
		  case  1: ci->levels[CA_AKICK]         = lev; break;
		  case  2: ci->levels[CA_SET]           = lev; break;
		  case  3: ci->levels[CA_UNBAN]         = lev; break;
		  case  4: ci->levels[CA_AUTOOP]        = lev; break;
		  case  5: ci->levels[CA_AUTODEOP]      = lev; break;
		  case  6: ci->levels[CA_AUTOVOICE]     = lev; break;
		  case  7: ci->levels[CA_OPDEOP]        = lev; break;
		  case  8: ci->levels[CA_ACCESS_LIST]   = lev; break;
		  case  9: ci->levels[CA_CLEAR]         = lev; break;
		  case 10: ci->levels[CA_NOJOIN]        = lev; break;
		  case 11: ci->levels[CA_ACCESS_CHANGE] = lev; break;
		  case 12: ci->levels[CA_MEMO]          = lev; break;
		}
	    }
	    if (ci->levels[CA_AUTOOP] == 0)
		ci->levels[CA_AUTOOP] = ACCLEV_INVALID;
	    if (ci->levels[CA_AUTOVOICE] == 0)
		ci->levels[CA_AUTOVOICE] = ACCLEV_INVALID;

	    SAFE(read_int16(&ci->accesscount, f));
	    if (ci->accesscount) {
		ci->access = scalloc(ci->accesscount, sizeof(ChanAccess));
		for (j = 0; j < ci->accesscount; j++) {
		    SAFE(read_int16(&ci->access[j].in_use, f));
		    if (ci->access[j].in_use) {
			SAFE(read_int16(&ci->access[j].level, f));
			if (ci->access[j].level >= 7)
			    ci->access[j].level += 3;
			SAFE(read_int16(&tmp16, f));  /* autoop */
			SAFE(read_string(&s, f));
			if (s)
			    ci->access[j].ni = findnick(s);
			if (ci->access[j].ni == NULL)
			    ci->access[j].in_use = 0;
		    }
		}
	    }

	    SAFE(read_int16(&ci->akickcount, f));
	    if (ci->akickcount) {
		ci->akick = scalloc(ci->akickcount, sizeof(AutoKick));
		for (j = 0; j < ci->akickcount; j++) {
		    SAFE(read_int16(&ci->akick[j].in_use, f));
		    if (ci->akick[j].in_use) {
			SAFE(read_int16(&ci->akick[j].is_nick, f));
			SAFE(read_string(&s, f));
			if (ci->akick[j].is_nick) {
			    ci->akick[j].u.ni = findnick(s);
			    if (!ci->akick[j].u.ni)
				ci->akick[j].in_use = 0;
			} else {
			    ci->akick[j].u.mask = s;
			}
			SAFE(read_string(&s, f));
			if (ci->akick[j].in_use)
			    ci->akick[j].reason = s;
		    }
		}
	    }

	    SAFE(read_int16(&tmp16, f));
	    ci->mlock_on = tmp16 & 0x00FF;
	    SAFE(read_int16(&tmp16, f));
	    ci->mlock_off = tmp16 & 0x00FF;
	    SAFE(read_int32(&ci->mlock_limit, f));
	    SAFE(read_string(&ci->mlock_key, f));

	    SAFE(read_int16(&ci->memos.memocount, f));
	    SAFE(read_int16(&ci->memos.memomax, f));
	    if (ci->memos.memocount) {
		Memo *memos;
		memos = smalloc(sizeof(Memo) * ci->memos.memocount);
		ci->memos.memos = memos;
		for (j = 0; j < ci->memos.memocount; j++, memos++) {
		    SAFE(read_int32(&memos->number, f));
		    SAFE(read_int16(&memos->flags, f));
		    SAFE(read_int32(&tmp32, f));
		    memos->time = tmp32;
		    SAFE(read_buffer(memos->sender, f));
		    SAFE(read_string(&memos->text, f));
		}
	    }

	    SAFE(read_string(&ci->entry_message, f));

	} /* while (getc_db(f) == 1) */
	SAFE(c == 0);
	*last = NULL;
    } /* for (i) */
    close_db(f);

    /* Check for non-forbidden channels with no founder */
    for (i = 0; i < 256; i++) {
	ChannelInfo *next;
	for (ci = chanlists[i]; ci; ci = next) {
	    next = ci->next;
	    if (!(ci->flags & CI_VERBOTEN) && !ci->founder) {
		if (ci->next)
		    ci->next->prev = ci->prev;
		if (ci->prev)
		    ci->prev->next = ci->next;
		else
		    chanlists[i] = ci->next;
	    }
	}
    }

}

/*************************************************************************/

void ircs12_load_oper(const char *sourcedir)
{
    dbFILE *f;
    int16 i, n;
    char *s;

    f = open_db_ver(sourcedir, "oper.db", 8, 8, NULL);
    /* servadmin */
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	if (s)
	    add_adminoper(ADD_ADMIN, s);
    }
    /* senior */
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	if (s)
	    add_adminoper(ADD_ADMIN, s);
    }
    /* junior */
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	if (s)
	    add_adminoper(ADD_OPER, s);
    }
    /* helper */
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	if (s)
	    add_adminoper(ADD_OPER, s);
    }
    /* servoper */
    SAFE(read_int16(&n, f));
    for (i = 0; i < n; i++) {
	SAFE(read_string(&s, f));
	if (s)
	    add_adminoper(ADD_OPER, s);
    }
    SAFE(read_int32(&maxusercnt, f));
    maxusertime = 0;
    close_db(f);
}

/*************************************************************************/

void ircs12_load_gline(const char *sourcedir)
{
    dbFILE *f;
    int i;
    int16 tmp16;
    int32 tmp32;

    f = open_db_ver(sourcedir, "gline.db", 8, 8, NULL);
    read_int16(&tmp16, f);
    nakill = tmp16;
    akills = scalloc(sizeof(*akills), nakill);
    for (i = 0; i < nakill; i++) {
	char *user, *host;
	SAFE(read_string(&user, f));
	SAFE(read_string(&host, f));
	if (user && host) {
	    akills[i].mask = smalloc(strlen(user)+strlen(host)+2);
	    sprintf(akills[i].mask, "%s@%s", user, host);
	} else {
	    akills[i].mask = NULL;
	}
	SAFE(read_string(&akills[i].reason, f));
	SAFE(read_buffer(akills[i].who, f));
	SAFE(read_int32(&tmp32, f));
	akills[i].time = tmp32;
	SAFE(read_int32(&tmp32, f));
	akills[i].expires = tmp32;
    }
    close_db(f);
}

/*************************************************************************/

void load_ircs_1_2(const char *sourcedir, int verbose)
{
#if PASSMAX < 16
    fprintf(stderr, "PASSMAX in config.h must be at least 16.  Aborting.\n");
    exit(1);
#endif
    if (verbose)
	printf("Loading nick.db...\n");
    ircs12_load_nick(sourcedir);
    if (verbose)
	printf("Loading chan.db...\n");
    ircs12_load_chan(sourcedir);
    if (verbose)
	printf("Loading oper.db...\n");
    ircs12_load_oper(sourcedir);
    if (verbose)
	printf("Loading gline.db...\n");
    ircs12_load_gline(sourcedir);
    if (verbose)
	printf("Data files successfully loaded.\n");
}

/*************************************************************************/

#undef SAFE

/*************************************************************************/
/***************************** Database saving ***************************/
/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	fprintf(stderr, "Write error on " SERVICES_DIR "/");	\
	perror(NickDBName);					\
	exit(1);						\
    }								\
} while (0)

void save_ns_dbase(void)
{
    char buf[PATH_MAX+1];
    int a;
    dbFILE *f;
    int i;
    NickInfo *ni;
    char **access;
    Memo *memos;

    snprintf(buf, sizeof(buf), "%s/%s", SERVICES_DIR, NickDBName);
    make_backup(buf);
    f = open_db(s_NickServ, buf, "w");
    SAFE(f ? 0 : -1);
    for (a = 0; a < 256; a++) for (ni = nicklists[a]; ni; ni = ni->next) {
	SAFE(write_int8(1, f));
	SAFE(write_buffer(ni->nick, f));
	SAFE(write_buffer(ni->pass, f));
	SAFE(write_string(ni->url, f));
	SAFE(write_string(ni->email, f));
	SAFE(write_string(ni->last_usermask, f));
	SAFE(write_string(ni->last_realname, f));
	SAFE(write_string(ni->last_quit, f));
	SAFE(write_int32(ni->time_registered, f));
	SAFE(write_int32(ni->last_seen, f));
	SAFE(write_int16(ni->status, f));
	if (ni->link) {
	    SAFE(write_string(ni->link->nick, f));
	    SAFE(write_int16(ni->linkcount, f));
	    SAFE(write_int16(ni->channelcount, f));
	} else {
	    SAFE(write_string(NULL, f));
	    SAFE(write_int16(ni->linkcount, f));
	    SAFE(write_int32(ni->flags, f));
	    SAFE(write_ptr(ni->suspendinfo, f));
	    if (ni->suspendinfo) {
		SAFE(write_buffer(ni->suspendinfo->who, f));
		SAFE(write_string(ni->suspendinfo->reason, f));
		SAFE(write_int32(ni->suspendinfo->suspended, f));
		SAFE(write_int32(ni->suspendinfo->expires, f));
	    }
	    SAFE(write_int16(ni->accesscount, f));
	    for (i=0, access=ni->access; i<ni->accesscount; i++, access++)
		SAFE(write_string(*access, f));
	    SAFE(write_int16(ni->memos.memocount, f));
	    SAFE(write_int16(ni->memos.memomax, f));
	    memos = ni->memos.memos;
	    for (i = 0; i < ni->memos.memocount; i++, memos++) {
		SAFE(write_int32(memos->number, f));
		SAFE(write_int16(memos->flags, f));
		SAFE(write_int32(memos->time, f));
		SAFE(write_buffer(memos->sender, f));
		SAFE(write_string(memos->text, f));
	    }
	    SAFE(write_int16(ni->channelcount, f));
	    SAFE(write_int16(ni->channelmax, f));
	    SAFE(write_int16(ni->language, f));
	}
    } /* for (ni) */
    {
	/* This is an UGLY HACK but it simplifies loading.  It will go away
	 * in the next file version */
	static char buf[256];
	SAFE(write_buffer(buf, f));
    }
    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	fprintf(stderr, "Write error on " SERVICES_DIR "/");	\
	perror(ChanDBName);					\
	exit(1);						\
    }								\
} while (0)

void save_cs_dbase(void)
{
    char buf[256];
    dbFILE *f;
    int a, i;
    int16 tmp16;
    ChannelInfo *ci;
    Memo *memos;

    snprintf(buf, sizeof(buf), "%s/%s", SERVICES_DIR, ChanDBName);
    make_backup(buf);

    f = open_db(s_ChanServ, buf, "w");
    SAFE(f ? 0 : -1);

    for (a = 0; a < 256; a++) for (ci = chanlists[a]; ci; ci = ci->next) {
	SAFE(write_int8(1, f));
	SAFE(write_buffer(ci->name, f));
	if (ci->founder)
	    SAFE(write_string(ci->founder->nick, f));
	else
	    SAFE(write_string(NULL, f));
	if (ci->successor)
	    SAFE(write_string(ci->successor->nick, f));
	else
	    SAFE(write_string(NULL, f));
	SAFE(write_buffer(ci->founderpass, f));
	SAFE(write_string(ci->desc, f));
	SAFE(write_string(ci->url, f));
	SAFE(write_string(ci->email, f));
	SAFE(write_int32(ci->time_registered, f));
	SAFE(write_int32(ci->last_used, f));
	SAFE(write_string(ci->last_topic, f));
	SAFE(write_buffer(ci->last_topic_setter, f));
	SAFE(write_int32(ci->last_topic_time, f));
	SAFE(write_int32(ci->flags, f));
	SAFE(write_ptr(ci->suspendinfo, f));
	if (ci->suspendinfo) {
	    SAFE(write_buffer(ci->suspendinfo->who, f));
	    SAFE(write_string(ci->suspendinfo->reason, f));
	    SAFE(write_int32(ci->suspendinfo->suspended, f));
	    SAFE(write_int32(ci->suspendinfo->expires, f));
	}

	tmp16 = CA_SIZE;
	SAFE(write_int16(tmp16, f));
	for (i = 0; i < CA_SIZE; i++)
	    SAFE(write_int16(ci->levels[i], f));

	SAFE(write_int16(ci->accesscount, f));
	for (i = 0; i < ci->accesscount; i++) {
	    SAFE(write_int16(ci->access[i].in_use, f));
	    if (ci->access[i].in_use) {
		SAFE(write_int16(ci->access[i].level, f));
		SAFE(write_string(ci->access[i].ni->nick, f));
	    }
	}

	SAFE(write_int16(ci->akickcount, f));
	for (i = 0; i < ci->akickcount; i++) {
	    SAFE(write_int16(ci->akick[i].in_use, f));
	    if (ci->akick[i].in_use) {
		SAFE(write_int16(ci->akick[i].is_nick, f));
		if (ci->akick[i].is_nick)
		    SAFE(write_string(ci->akick[i].u.ni->nick, f));
		else
		    SAFE(write_string(ci->akick[i].u.mask, f));
		SAFE(write_string(ci->akick[i].reason, f));
		SAFE(write_buffer(ci->akick[i].who, f));
	    }
	}

	SAFE(write_int32(ci->mlock_on, f));
	SAFE(write_int32(ci->mlock_off, f));
	SAFE(write_int32(ci->mlock_limit, f));
	SAFE(write_string(ci->mlock_key, f));

	SAFE(write_int16(ci->memos.memocount, f));
	SAFE(write_int16(ci->memos.memomax, f));
	memos = ci->memos.memos;
	for (i = 0; i < ci->memos.memocount; i++, memos++) {
	    SAFE(write_int32(memos->number, f));
	    SAFE(write_int16(memos->flags, f));
	    SAFE(write_int32(memos->time, f));
	    SAFE(write_buffer(memos->sender, f));
	    SAFE(write_string(memos->text, f));
	}

	SAFE(write_string(ci->entry_message, f));

    } /* for (ci) */

    {
	/* This is an UGLY HACK but it simplifies loading.  It will go away
	 * in the next file version */
	static char buf[256];
	SAFE(write_buffer(buf, f));
    }

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	fprintf(stderr, "Write error on " SERVICES_DIR "/");	\
	perror(OperDBName);					\
	exit(1);						\
    }								\
} while (0)

void save_os_dbase(void)
{
    char buf[256];
    dbFILE *f;
    int16 i, count = 0;

    snprintf(buf, sizeof(buf), "%s/%s", SERVICES_DIR, OperDBName);
    make_backup(buf);
    f = open_db(NULL, buf, "w");
    SAFE(f ? 0 : -1);
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i])
	    count++;
    }
    SAFE(write_int16(count, f));
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i])
	    SAFE(write_string(services_admins[i]->nick, f));
    }
    count = 0;
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i])
	    count++;
    }
    SAFE(write_int16(count, f));
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i])
	    SAFE(write_string(services_opers[i]->nick, f));
    }
    SAFE(write_int32(maxusercnt, f));
    SAFE(write_int32(maxusertime, f));
    SAFE(write_int8(no_supass, f));
    if (!no_supass)
	SAFE(write_buffer(supass, f));
    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	fprintf(stderr, "Write error on " SERVICES_DIR "/");	\
	perror(AutokillDBName);					\
	exit(1);						\
    }								\
} while (0)

void save_akill(void)
{
    char buf[256];
    dbFILE *f;
    int i;

    snprintf(buf, sizeof(buf), "%s/%s", SERVICES_DIR, AutokillDBName);
    make_backup(buf);
    f = open_db(NULL, buf, "w");
    SAFE(f ? 0 : -1);
    write_int16(nakill, f);
    for (i = 0; i < nakill; i++) {
	SAFE(write_string(akills[i].mask, f));
	SAFE(write_string(akills[i].reason, f));
	SAFE(write_buffer(akills[i].who, f));
	SAFE(write_int32(akills[i].time, f));
	SAFE(write_int32(akills[i].expires, f));
    }
    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	fprintf(stderr, "Write error on " SERVICES_DIR "/");	\
	perror(ExceptionDBName);				\
	exit(1);						\
    }								\
} while (0)

void save_exceptions()
{
    char buf[256];
    dbFILE *f;
    int i;

    snprintf(buf, sizeof(buf), "%s/%s", SERVICES_DIR, ExceptionDBName);
    make_backup(buf);
    f = open_db(NULL, buf, "w");
    SAFE(f ? 0 : -1);
    SAFE(write_int16(nexceptions, f));
    for (i = 0; i < nexceptions; i++) {
	SAFE(write_string(exceptions[i].mask, f));
	SAFE(write_int16(exceptions[i].limit, f));
	SAFE(write_buffer(exceptions[i].who, f));
	SAFE(write_string(exceptions[i].reason, f));
	SAFE(write_int32(exceptions[i].time, f));
	SAFE(write_int32(exceptions[i].expires, f));
    }
    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	fprintf(stderr, "Write error on " SERVICES_DIR "/");	\
	perror(NewsDBName);					\
	exit(1);						\
    }								\
} while (0)

void save_news()
{
    char buf[256];
    dbFILE *f;
    int i;

    snprintf(buf, sizeof(buf), "%s/%s", SERVICES_DIR, NewsDBName);
    make_backup(buf);
    f = open_db(NULL, buf, "w");
    SAFE(f ? 0 : -1);
    SAFE(write_int16(nnews, f));
    for (i = 0; i < nnews; i++) {
	SAFE(write_int16(news[i].type, f));
	SAFE(write_int32(news[i].num, f));
	SAFE(write_string(news[i].text, f));
	SAFE(write_buffer(news[i].who, f));
	SAFE(write_int32(news[i].time, f));
    }
    close_db(f);
}

#undef SAFE

/*************************************************************************/
/****************************** Main program *****************************/
/*************************************************************************/

void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s [-v] [+program-name] sourcedir\n"
		    "The following program names are known:\n"
		    "    auspice-2.5\n"
		    "    daylight\n"
		    "    epona\n"
		    "    ircs-1.2\n"
		    "    magick-1.4b2\n"
		    "    ptlink-2.18\n"
		    "    sirv\n"
		    "    wrecked-1.2\n"
	    , progname);
    exit(1);
}

/*************************************************************************/

typedef void (*loadfunc_t)(const char *dir, int verbose);

static loadfunc_t check_type(const char *sourcedir)
{
    FILE *f;
    char buf[PATH_MAX+1];

    if (access(sourcedir, R_OK) < 0) {
	perror(sourcedir);
	exit(1);
    }

    snprintf(buf, sizeof(buf), "%s/message.db", sourcedir);
    f = fopen(buf, "r");
    if (f) {
	int ver;
	ver  = fgetc(f)<<24;
	ver |= fgetc(f)<<16;
	ver |= fgetc(f)<<8;
	ver |= fgetc(f);
	fclose(f);
	if (ver == 5) {
	    printf("Found Magick 1.4b2 databases\n");
	    return load_magick_14b2;
	} else if (ver == 6) {
	    printf("Found Wrecked 1.2.0 databases\n");
	    return load_wrecked_1_2;
	}
    }

    snprintf(buf, sizeof(buf), "%s/services.conn", sourcedir);
    if (access(buf, R_OK) == 0) {
	printf("Found Daylight databases\n");
	return load_daylight;
    }

    snprintf(buf, sizeof(buf), "%s/bot.db", sourcedir);
    if (access(buf, R_OK) == 0) {
	printf("Found Epona databases\n");
	return load_epona;
    }

    snprintf(buf, sizeof(buf), "%s/admin.db", sourcedir);
    if (access(buf, R_OK) == 0) {
	printf("Found Auspice 2.5.x databases\n");
	return load_aus_2_5;
    }

    snprintf(buf, sizeof(buf), "%s/trigger.db", sourcedir);
    f = fopen(buf, "r");
    if (f) {
	int ver;
	ver  = fgetc(f)<<24;
	ver |= fgetc(f)<<16;
	ver |= fgetc(f)<<8;
	ver |= fgetc(f);
	fclose(f);
	if (ver == 5) {
	    printf("Found SirvNET 1.x databases\n");
	    return load_sirv;
	} else if (ver == 6) {
	    printf("Found SirvNET 2.0.0-2.2.0 databases\n");
	    return load_sirv;
	} else if (ver == 7) {
	    printf("Found SirvNET 2.2.1+ databases\n");
	    return load_sirv;
	}
    }

    snprintf(buf, sizeof(buf), "%s/vline.db", sourcedir);
    if (access(buf, R_OK) == 0) {
	printf("Found PTlink 2.18 databases\n");
	return load_ptlink_2_18;
    }

    snprintf(buf, sizeof(buf), "%s/gline.db", sourcedir);
    if (access(buf, R_OK) == 0) {
	printf("Found IRCS 1.2 databases\n");
	return load_ircs_1_2;
    }

    return NULL;
}

/*************************************************************************/

int main(int ac, char **av)
{
    char *sourcedir = NULL;	/* Source data file directory */
    int verbose = 0;		/* Verbose output? */
    loadfunc_t load = NULL;
    int i;
    char oldpath[PATH_MAX+1], newpath[PATH_MAX+1];

    for (i = 1; i < ac; i++) {
	if (av[i][0] == '-') {
	    if (av[i][1] == 'v') {
		verbose++;
	    } else {
		if (av[i][1] != 'h')
		    fprintf(stderr, "Unknown option -%c\n", av[i][1]);
		usage(av[0]);
	    }
	} else if (av[i][0] == '+') {
	    if (strcmp(av[i]+1, "magick-1.4b2") == 0)
		load = load_magick_14b2;
	    else if (strcmp(av[i]+1, "wrecked-1.2") == 0)
		load = load_wrecked_1_2;
	    else if (strcmp(av[i]+1, "sirv") == 0)
		load = load_sirv;
	    else if (strcmp(av[i]+1, "auspice-2.5") == 0)
		load = load_aus_2_5;
	    else if (strcmp(av[i]+1, "daylight") == 0)
		load = load_daylight;
	    else if (strcmp(av[i]+1, "epona") == 0)
		load = load_epona;
	    else if (strcmp(av[i]+1, "ptlink-2.18") == 0)
		load = load_ptlink_2_18;
	    else if (strcmp(av[i]+1, "ircs-1.2") == 0)
		load = load_ircs_1_2;
	    else {
		fprintf(stderr, "Unknown program name `%s'\n", av[i]+1);
		usage(av[0]);
	    }
	} else {
	    if (sourcedir) {
		fprintf(stderr, "Only one source directory may be specified\n");
		usage(av[0]);
	    }
	    sourcedir = av[i];
	}
    }
    if (!sourcedir) {
	fprintf(stderr, "Directory name must be specified\n");
	usage(av[0]);
    }

    if (*sourcedir != '/' && !getcwd(oldpath, sizeof(oldpath))) {
	perror("Unable to read current directory name");
	fprintf(stderr, "Try using an absolute pathname for the source directory.\n");
	return 1;
    }
    chdir(SERVICES_DIR);
    if (!read_config())
	return 1;
    if (*sourcedir != '/') {
	if (strlen(oldpath) + 1 + strlen(sourcedir) + 1 > sizeof(newpath)) {
	    fprintf(stderr, "Source directory pathname too long\n");
	    return 1;
	}
	sprintf(newpath, "%s/%s", oldpath, sourcedir);
	sourcedir = newpath;
    }

    if (!load) {
	load = check_type(sourcedir);
	if (!load) {
	    fprintf(stderr, "Can't determine data file type; use +name option\n");
	    usage(av[0]);
	}
    }

    load(sourcedir, verbose);
    if (verbose)
	printf("Saving new NickServ database\n");
    save_ns_dbase();
    if (verbose)
	printf("Saving new ChanServ database\n");
    save_cs_dbase();
    if (verbose)
	printf("Saving new OperServ database\n");
    save_os_dbase();
    if (verbose)
	printf("Saving new AKILL database\n");
    save_akill();
    if (verbose)
	printf("Saving new exception database\n");
    save_exceptions();
    if (verbose)
	printf("Saving new news database\n");
    save_news();
    return 0;
}

/*************************************************************************/

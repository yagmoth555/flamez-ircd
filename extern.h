/* Prototypes and external variable declarations.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef EXTERN_H
#define EXTERN_H


#define E extern


/**** actions.c ****/

E void bad_password(const char *service, User *u, const char *what);
E void clear_channel(Channel *chan, int what, const void *param);
E void kill_user(const char *source, const char *user, const char *reason);
E void set_topic(Channel *c, const char *topic, const char *setter,
		 time_t time);
E void send_cmode(const char *sender, ...);


/**** akill.c ****/

E void get_akill_stats(long *nrec, long *memuse);
E int num_akills(void);
E void load_akill(void);
E void save_akill(void);
E int check_akill(const char *nick, const char *username, const char *host);
E void expire_akills(void);
#ifdef IRC_UNREAL
E void m_tkl(char *source, int ac, char **av);
#endif
E void do_akill(User *u);
E void add_akill(char *mask, const char *reason, const char *who,
		 const time_t expiry);
E int is_akilled(const char *mask);

/**** nooper.c ****/
E void get_nooper_stats(long *nrec, long *memuse);
E int num_noopers(void);
E void load_nooper(void);
E void save_nooper(void);
E int check_nooper(const char *nick, const char *username, const char *host);
E int is_nooper(const char *nick, const char *username, const char *host);
E void do_nooper(User *u);
E void add_nooper(const char *mask, const char *reason, const char *who);

/**** snooper.c ****/
E void get_snooper_stats(long *nrec, long *memuse);
E int num_snoopers(void);
E void load_snooper(void);
E void save_snooper(void);
E int check_snooper(const char *nick, const char *username, const char *host);
E int is_snooper(const char *nick, const Server *server);
E void do_snooper(User *u);
E void add_snooper(const char *mask, const char *reason, const char *who);

/**** autoconnect.c ****/
E int num_aconnect(void);
E void load_aconnect(void);
E void save_aconnect(void);
E void add_aconnect(const char *servername, const char *where, int16 port);
E void do_aconnect(User *u);
E void checkforsplit(const char *quitmsg);

/**** nakill.c ****/
E int check_nakill(const char *nick, const char *host);
E int is_nakill(const char *host, const char *nick);
E void load_nakill(void);
E void save_nakill(void);
E void do_nakill(User *u);

/**** floodserv.c ****/
E void fs_init(void);
E void fs_add_chan(User *u, const char *name);
E void fs_del_chan(User *u, const char *name);
E void floodserv(const char *source, char *buf);
E void privmsg_flood(const char *source, int ac, char **av);
E int check_grname(const char *nick, const char *realname, const char *host);
E void load_fs_dbase(void);
E void load_grname_dbase(void);
E void save_fs_dbase(void);
E void save_grname_dbase(void);


/**** channels.c ****/

#ifdef DEBUG_COMMANDS
E void send_channel_list(User *user);
E void send_channel_users(User *user);
#endif

E void get_channel_stats(long *nrec, long *memuse);
E Channel *findchan(const char *chan);
E Channel *firstchan(void);
E Channel *nextchan(void);

E Channel *chan_adduser(User *user, const char *chan, int32 modes);
E void chan_deluser(User *user, Channel *c);
E int chan_has_ban(const char *chan, const char *ban);

E void do_cmode(const char *source, int ac, char **av);
E void do_topic(const char *source, int ac, char **av);


/**** chanserv.c ****/

E void cs_init(void);
E void chanserv(const char *source, char *buf);
E ChannelInfo *cs_findchan(const char *chan);
E ChannelInfo *cs_firstchan(void);
E ChannelInfo *cs_nextchan(void);
E void get_chanserv_stats(long *nrec, long *memuse);

E void check_modes(const char *chan);
E int check_chan_user_modes(const char *source, User *user, const char *chan,
			    int32 modes);
E int check_kick(User *user, const char *chan);
E void record_topic(Channel *c);
E void restore_topic(Channel *c);
E int check_topiclock(const char *chan);
E void expire_chans(void);
E void cs_remove_nick(const NickInfo *ni);
E int check_access(User *user, ChannelInfo *ci, int what);
E int check_channel_limit(NickInfo *ni);
E char *chanopts_to_string(ChannelInfo *ci, NickInfo *ni);


/**** compat.c ****/

#if !HAVE_SNPRINTF
# if BAD_SNPRINTF
#  define snprintf my_snprintf
# endif
# define vsnprintf my_vsnprintf
E int vsnprintf(char *buf, size_t size, const char *fmt, va_list args);
E int snprintf(char *buf, size_t size, const char *fmt, ...);
#endif
#if !HAVE_STRTOK
# undef strtok
E char *strtok(char *str, const char *delim);
#endif
#if !HAVE_STRICMP && !HAVE_STRCASECMP
# undef stricmp
# undef strnicmp
E int stricmp(const char *s1, const char *s2);
E int strnicmp(const char *s1, const char *s2, size_t len);
#endif
#if !HAVE_STRDUP
# undef strdup
E char *strdup(const char *s);
#endif
#if !HAVE_STRSPN
# undef strspn
# undef strcspn
E size_t strspn(const char *s, const char *accept);
E size_t strcspn(const char *s, const char *reject);
#endif
#if !HAVE_STRERROR
# undef strerror
E char *strerror(int errnum);
#endif
#if !HAVE_STRSIGNAL
# undef strsignal
E char *strsignal(int signum);
#endif


/**** config.c ****/

E char *RemoteServer;
E int   RemotePort;
E char *RemotePassword;
E char *LocalHost;
E int   LocalPort;

E char *ServerName;
E char *ServerDesc;
E char *ServiceUser;
E char *ServiceHost;
E int   ServerNumeric;

E char *s_NickServ;
E char *s_ChanServ;
E char *s_MemoServ;
E char *s_HelpServ;
E char *s_OperServ;
E char *s_StatServ;
E char *s_GlobalNoticer;
E char *s_IrcIIHelp;
E char *s_DevNull;
E char *s_FloodServ;
E char *desc_NickServ;
E char *desc_ChanServ;
E char *desc_MemoServ;
E char *desc_HelpServ;
E char *desc_OperServ;
E char *desc_StatServ;
E char *desc_GlobalNoticer;
E char *desc_IrcIIHelp;
E char *desc_DevNull;
E char *desc_FloodServ;

E char *PIDFilename;
E char *MOTDFilename;
E char *HelpDir;
E char *NickDBName;
E char *ChanDBName;
E char *OperDBName;
E char *StatDBName;
E char *AutokillDBName;
E char *NooperDBName;
E char *SNooperDBName;
E char *AConnectDBName;
E char *NakillDBName;
E char *FloodServDBName;
E char *GrNameDBName;
E char *NewsDBName;

E int   NoBackupOkay;
E int   NoBouncyModes;
E int   NoSplitRecovery;
E int   StrictPasswords;
E int   BadPassLimit;
E int   BadPassTimeout;
E int   BadPassWarning;
E int   BadPassSuspend;
E int   UpdateTimeout;
E int   ExpireTimeout;
E int   ReadTimeout;
E int   WarningTimeout;
E int   TimeoutCheck;
E int   PingFrequency;
E int   MergeChannelModes;

E int   NSForceNickChange;
E char *NSGuestNickPrefix;
E int   NSDefFlags;
E int   NSRegDelay;
E int   NSRequireEmail;
E int   NSExpire;
E int   NSExpireWarning;
E int   NSAccessMax;
E char *NSEnforcerUser;
E char *NSEnforcerHost;
E int   NSReleaseTimeout;
E int   NSAllowKillImmed;
E int   NSMaxLinkDepth;
E int   NSListOpersOnly;
E int   NSListMax;
E int   NSSecureAdmins;
E int   NSSuspendExpire;
E int   NSSuspendGrace;

E int   CSMaxReg;
E int   CSExpire;
E int   CSAccessMax;
E int   CSAutokickMax;
E char *CSAutokickReason;
E int   CSInhabit;
E int   CSRestrictDelay;
E int   CSListOpersOnly;
E int   CSListMax;
E int   CSSuspendExpire;
E int   CSSuspendGrace;

E int   MSMaxMemos;
E int   MSSendDelay;
E int   MSNotifyAll;

E char *ServicesRoot;
E int   LogMaxUsers;
E char *StaticAkillReason;
E int   ImmediatelySendAkill;
E int   AutokillExpiry;
E int   WallOper;
E int   WallBadOS;
E int   WallOSChannel;
E int	WallOSException;
E int   WallOSAkill;
E int	WallOSSNooper;
E int	WallOSNooper;
E int	WallOSAConnect;
E int   WallOSNakill;
E int   WallSU;
E int   WallAkillExpire;
E int   WallExceptionExpire;
E int   WallGetpass;
E int   WallSetpass;
E int   CheckClones;
E int   CloneMinUsers;
E int   CloneMaxDelay;
E int   CloneWarningDelay;
E int   KillClones;

E int   KillClonesAkillExpire;

E int   SSOpersOnly;

E int   LimitSessions;
E int   DefSessionLimit;
E int   ExceptionExpiry;
E int   MaxSessionLimit;
E char *ExceptionDBName;
E char *SessionLimitAkillReason;
E int   SessionLimitAkill;
E int   SessionLimitMaxKillCount;
E int   SessionLimitMinKillTime;
E int   SessionLimitAkillExpiry;
E char *SessionLimitDetailsLoc;
E char *SessionLimitExceeded;

E int   FloodServAkillExpiry;
E char *FloodServAkillReason;
E int   FloodServTFNumLines;
E int   FloodServTFSec;
E int   FloodServTFNLWarned;
E int   FloodServTFSecWarned;
E int   FloodServWarnFirst;
E char *FloodServWarnMsg;

E char *GrNameAkillReason;

E int read_config(void);


/**** cs-loadsave.c ****/

E void load_cs_dbase(void);
E void save_cs_dbase(void);


/**** helpserv.c ****/

E void helpserv(const char *whoami, const char *source, char *buf);


/**** init.c ****/

E void introduce_user(const char *user);
E int init(int ac, char **av);


/**** language.c ****/

E char **langtexts[NUM_LANGS];
E char *langnames[NUM_LANGS];
E int langlist[NUM_LANGS];

E void lang_init(void);
#define getstring(ni,index) \
	(langtexts[((ni)?((NickInfo*)ni)->language:DEF_LANGUAGE)][(index)])
E int strftime_lang(char *buf, int size, User *u, int format, struct tm *tm);
E void expires_in_lang(char *buf, int size, NickInfo *ni, time_t seconds);
E void syntax_error(const char *service, User *u, const char *command,
		int msgnum);


/**** list.c ****/

E void listnicks(int ac, char **av);
E void listchans(int ac, char **av);


/**** log.c ****/

E int open_log(void);
E void close_log(void);
E void log(const char *fmt, ...)		FORMAT(printf,1,2);
E void log_perror(const char *fmt, ...)		FORMAT(printf,1,2);
E void fatal(const char *fmt, ...)		FORMAT(printf,1,2);
E void fatal_perror(const char *fmt, ...)	FORMAT(printf,1,2);


/**** main.c ****/

E const char version_branchstatus[];
E const char version_number[];
E const char version_build[];
E const char version_protocol[];
E const char *info_text[];

E char *services_dir;
E char *log_filename;
E int   debug;
E int   readonly;
E int   skeleton;
E int   nofork;
E int   forceload;
E int	noexpire;
E int	noakill;

E int   quitting;
E int   delayed_quit;
E char *quitmsg;
E char  inbuf[BUFSIZE];
E int   servsock;
E int   save_data;
E int   got_alarm;
E time_t start_time;

E void weirdsig_handler(int signum);


/**** memoserv.c ****/

E void ms_init(void);
E void memoserv(const char *source, char *buf);
E void get_memoserv_stats(long *nrec, long *memuse);
E void load_old_ms_dbase(void);
E void check_memos(User *u);


/**** misc.c ****/

E unsigned char irc_toupper(char c);
E unsigned char irc_tolower(char c);
E int irc_stricmp(const char *s1, const char *s2);
E char *strscpy(char *d, const char *s, size_t len);
E char *stristr(char *s1, char *s2);
E char *strupper(char *s);
E char *strlower(char *s);
E char *strnrepl(char *s, int32 size, const char *old, const char *new);

E char *merge_args(int argc, char **argv);

E int match_wild(const char *pattern, const char *str);
E int match_wild_nocase(const char *pattern, const char *str);

E int valid_domain(const char *str);
E int valid_email(const char *str);
E int valid_url(const char *str);

typedef int (*range_callback_t)(User *u, int num, va_list args);
E int process_numlist(const char *numstr, int *count_ret,
		range_callback_t callback, User *u, ...);

E uint32 time_msec(void);
E int dotime(const char *s);


/**** modes.c ****/

E int32 mode_char_to_flag(char c, int which);
E char mode_flag_to_char(int32 f, int which);
E int32 mode_string_to_flags(char *s, int which);
E char *mode_flags_to_string(int32 flags, int which);
E int32 cumode_prefix_to_flag(char c);


/**** news.c ****/

E void get_news_stats(long *nrec, long *memuse);
E void load_news(void);
E void save_news(void);
E void display_news(User *u, int16 type);
E void do_logonnews(User *u);
E void do_opernews(User *u);


/**** nickserv.c ****/

E void ns_init(void);
E void nickserv(const char *source, char *buf);
E NickInfo *findnick(const char *nick);
E NickInfo *getlink(NickInfo *ni);
E NickInfo *firstnick(void);
E NickInfo *nextnick(void);
E void get_nickserv_stats(long *nrec, long *memuse);

E void load_ns_dbase(void);
E void save_ns_dbase(void);
E int check_on_access(User *u);
E int validate_user(User *u);
E void cancel_user(User *u);
E int nick_identified(User *u);
E int nick_recognized(User *u);
E void expire_nicks(void);
E void expire_nicksuspends(void);


/**** operserv.c ****/

E void operserv(const char *source, char *buf);

E void os_init(void);
E void load_os_dbase(void);
E void save_os_dbase(void);
E int is_services_root(User *u);
E int is_services_admin(User *u);
E int is_services_oper(User *u);
E int nick_is_services_admin(NickInfo *ni);
E void os_remove_nick(const NickInfo *ni);

E void check_clones(User *user);
E int is_net_closed(void);


/**** process.c ****/

E int allow_ignore;

E IgnoreData *first_ignore(void);
E IgnoreData *next_ignore(void);
E void add_ignore(const char *nick, time_t delta);
E IgnoreData *get_ignore(const char *nick);

E int split_buf(char *buf, char ***argv, int colon_special);
E void process(void);


/**** send.c ****/

E time_t last_send;

E void send_cmd(const char *source, const char *fmt, ...)
	FORMAT(printf,2,3);
E void vsend_cmd(const char *source, const char *fmt, va_list args)
	FORMAT(printf,2,0);
E void wallops(const char *source, const char *fmt, ...)
	FORMAT(printf,2,3);
E void notice(const char *source, const char *dest, const char *fmt, ...)
	FORMAT(printf,3,4);
E void notice_list(const char *source, const char *dest, const char **text);
E void notice_lang(const char *source, User *dest, int message, ...);
E void notice_help(const char *source, User *dest, int message, ...);
E void privmsg(const char *source, const char *dest, const char *fmt, ...)
	FORMAT(printf,3,4);
E void send_nick(const char *nick, const char *user, const char *host,
                const char *server, const char *name, int32 modes);
E void send_server(void);
E void send_server_remote(const char *server, const char *reason);


/**** servers.c ****/

#ifdef DEBUG_COMMANDS
E void send_server_list(User *user);
#endif

E void get_server_stats(long *nservers, long *memuse);
E Server *findserver(const char *servername);
E void do_server(const char *source, int ac, char **av);
E void do_squit(const char *source, int ac, char **av);


/**** sessions.c ****/

#ifndef STREAMLINED
E void get_session_stats(long *nrec, long *memuse);
E void get_exception_stats(long *nrec, long *memuse);

E void do_session(User *u);
E int add_session(const char *nick, const char *host);
E void del_session(const char *host);

E void load_exceptions(void);
E void save_exceptions(void);
E void do_exception(User *u);
E void expire_exceptions(void);
#endif	/* !STREAMLINED */


/**** sockutil.c ****/

E int32 total_read, total_written;
E int32 read_buffer_len(void);
E int32 write_buffer_len(void);

E int sgetc(int s);
E char *sgets(char *buf, int len, int s);
E char *sgets2(char *buf, int len, int s);
E int sread(int s, char *buf, int len);
E int sputs(char *str, int s);
E int sockprintf(int s, char *fmt,...);
E int conn(const char *host, int port, const char *lhost, int lport);
E void disconn(int s);
E const char *hstrerror(int h_errnum);


/**** statistics.c ****/

#ifdef STATISTICS
E void statserv(const char *source, char *buf);
E void get_statserv_stats(long *nrec, long *memuse);
E void load_ss_dbase(void);
E void save_ss_dbase(void);
E ServerStats *stats_findserver(const char *servername);
E ServerStats *stats_do_server(const char *servername, const char *serverhub);
E void stats_do_quit(const User *user);
E void stats_do_squit(const Server *server, const char *quit_message);
#endif


/**** users.c ****/

E int32 usercnt, opcnt, maxusercnt;
E time_t maxusertime;

#ifdef DEBUG_COMMANDS
E void send_user_list(User *user);
E void send_user_info(User *user);
#endif

E void get_user_stats(long *nusers, long *memuse);
E User *finduser(const char *nick);
E User *firstuser(void);
E User *nextuser(void);

E int do_nick(const char *source, int ac, char **av);
E void do_join(const char *source, int ac, char **av);
#if defined(IRC_BAHAMUT) || defined(IRC_UNREAL)
E void do_sjoin(const char *source, int ac, char **av);
#endif
E void do_part(const char *source, int ac, char **av);
E void do_kick(const char *source, int ac, char **av);
E void do_umode(const char *source, int ac, char **av);
E void do_quit(const char *source, int ac, char **av);
E void do_kill(const char *source, int ac, char **av);

E int is_oper(const char *nick);
#define is_oper_u(user) ((user)->mode & UMODE_o)
E int is_on_chan(const char *nick, const char *chan);
E int is_chanop(const char *nick, const char *chan);
E int is_voiced(const char *nick, const char *chan);

E int match_usermask(const char *mask, User *user);
E void split_usermask(const char *mask, char **nick, char **user, char **host);
E char *create_mask(User *u, int use_fakehost);


#endif	/* EXTERN_H */

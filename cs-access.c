/* Access list, SOP/AOP/VOP handling for ChanServ.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

/*************************************************************************/

/* Return values for add/delete/list functions.  Success > 0, failure < 0. */
#define RET_ADDED	1
#define RET_CHANGED	2
#define RET_UNCHANGED	3
#define RET_DELETED	4
#define RET_LISTED	5
#define RET_PERMISSION	-1
#define RET_NOSUCHNICK	-2
#define RET_NICKFORBID	-3
#define RET_LISTFULL	-4
#define RET_NOENTRY	-5

/* Return the name of the list or the syntax message number corresponding
 * to the given level.  Does no error checking. */
#ifdef HAVE_HALFOP
# define XOP_LISTNAME(level) \
    ((level)==ACCLEV_SOP ? "SOP" : (level)==ACCLEV_AOP ? "AOP" : \
     (level)==ACCLEV_HOP ? "HOP" : "VOP")
# define XOP_SYNTAX(level) \
    ((level)==ACCLEV_SOP ? CHAN_SOP_SYNTAX : \
     (level)==ACCLEV_AOP ? CHAN_AOP_SYNTAX : \
     (level)==ACCLEV_HOP ? CHAN_HOP_SYNTAX : CHAN_VOP_SYNTAX)
#else
# define XOP_LISTNAME(level) \
    ((level)==ACCLEV_SOP ? "SOP" : (level)==ACCLEV_AOP ? "AOP" : "VOP")
# define XOP_SYNTAX(level) \
    ((level)==ACCLEV_SOP ? CHAN_SOP_SYNTAX : \
     (level)==ACCLEV_AOP ? CHAN_AOP_SYNTAX : CHAN_VOP_SYNTAX)
#endif

/*************************************************************************/

static int access_add(ChannelInfo *ci, const char *nick, int level, int uacc)
{
    int i;
    ChanAccess *access;
    NickInfo *ni;

    if (level >= uacc)
	return RET_PERMISSION;
    ni = findnick(nick);
    if (!ni)
	return RET_NOSUCHNICK;
    else if (ni->status & NS_VERBOTEN)
	return RET_NICKFORBID;
    for (access = ci->access, i = 0; i < ci->accesscount; access++, i++) {
	if (access->ni == ni) {
	    /* Don't allow lowering from a level >= uacc */
	    if (access->level >= uacc)
		return RET_PERMISSION;
	    if (access->level == level)
		return RET_UNCHANGED;
	    access->level = level;
	    return RET_CHANGED;
	}
    }
    for (i = 0; i < ci->accesscount; i++) {
	if (!ci->access[i].in_use)
	    break;
    }
    if (i == ci->accesscount) {
	if (i < CSAccessMax) {
	    ci->accesscount++;
	    ci->access =
		srealloc(ci->access, sizeof(ChanAccess) * ci->accesscount);
	} else {
	    return RET_LISTFULL;
	}
    }
    access = &ci->access[i];
    access->ni = ni;
    access->in_use = 1;
    access->level = level;
    return RET_ADDED;
}


static int access_del(ChannelInfo *ci, int num, int uacc)
{
    ChanAccess *access = &ci->access[num];
    if (!access->in_use)
	return RET_NOENTRY;
    if (uacc <= access->level)
	return RET_PERMISSION;
    access->ni = NULL;
    access->in_use = 0;
    return RET_DELETED;
}

/* `last' is set to the last valid index seen
 * `perm' is incremented whenever a permission-denied error occurs
 */
static int access_del_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *last = va_arg(args, int *);
    int *perm = va_arg(args, int *);
    int uacc = va_arg(args, int);
    if (num < 1 || num > ci->accesscount)
	return 0;
    *last = num;
    switch (access_del(ci, num-1, uacc)) {
      case RET_DELETED:
	return 1;
      case RET_PERMISSION:
	(*perm)++;
	/* fall through */
      default:
	return 0;
    }
}


static int access_list(User *u, int index, ChannelInfo *ci, int *sent_header)
{
    ChanAccess *access = &ci->access[index];
    NickInfo *ni = access->ni;
    char *s;

    if (!access->in_use)
	return RET_NOENTRY;
    if (!*sent_header) {
	notice_lang(s_ChanServ, u, CHAN_ACCESS_LIST_HEADER, ci->name);
	*sent_header = 1;
    }
    if (!(getlink(ni)->flags & NI_HIDE_MASK))
	s = ni->last_usermask;
    else
	s = NULL;
    notice_lang(s_ChanServ, u, CHAN_ACCESS_LIST_FORMAT,
		index+1, access->level, access->ni->nick,
		s ? " (" : "", s ? s : "", s ? ")" : "");
    return RET_LISTED;
}

static int access_list_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *sent_header = va_arg(args, int *);
    if (num < 1 || num > ci->accesscount)
	return 0;
    return access_list(u, num-1, ci, sent_header) > 0;
}

/*************************************************************************/

static void do_access(User *u)
{
    char *chan = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    char *nick = strtok(NULL, " ");
    char *s    = strtok(NULL, " ");
    ChannelInfo *ci;
    NickInfo *ni;
    short level = 0;
    int i;
    int is_list;  /* Is true when command is either LIST or COUNT */

    is_list = (cmd && (stricmp(cmd, "LIST")==0 || stricmp(cmd, "COUNT")==0));

    /* If LIST/COUNT, we don't *require* any parameters, but we can take any.
     * If DEL, we require a nick and no level.
     * Else (ADD), we require a level (which implies a nick). */
    if (!cmd || (is_list ? 0 :
			(stricmp(cmd,"DEL")==0) ? (!nick || s) : !s)) {
	syntax_error(s_ChanServ, u, "ACCESS", CHAN_ACCESS_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (((is_list && !check_access(u, ci, CA_ACCESS_LIST))
                || (!is_list && !check_access(u, ci, CA_ACCESS_CHANGE)))
               && !is_services_admin(u))
    {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);

    } else if (stricmp(cmd, "ADD") == 0) {

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_DISABLED);
	    return;
	}

	level = atoi(s);
	if (level == 0) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_NONZERO);
	    return;
	} else if (level <= ACCLEV_INVALID || level >= ACCLEV_FOUNDER) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_RANGE,
			ACCLEV_INVALID+1, ACCLEV_FOUNDER-1);
	    return;
	}
	switch (access_add(ci, nick, level, get_access(u,ci))) {
	  case RET_ADDED:
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_ADDED, nick, chan, level);
	    break;
	  case RET_CHANGED:
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_CHANGED,
			nick, chan, level);
	    break;
	  case RET_UNCHANGED:
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_UNCHANGED,
			nick, chan, level);
	    break;
	  case RET_LISTFULL:
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_REACHED_LIMIT, CSAccessMax);
	    break;
	  case RET_NOSUCHNICK:
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_NICKS_ONLY);
	    break;
	  case RET_NICKFORBID:
	    notice_lang(s_ChanServ, u, NICK_X_FORBIDDEN, nick);
	    break;
	  case RET_PERMISSION:
	    notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	    break;
	}

    } else if (stricmp(cmd, "DEL") == 0) {

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_DISABLED);
	    return;
	}

	/* Special case: is it a number/list? */
	if (isdigit(*nick) && strspn(nick, "1234567890,-") == strlen(nick)) {
	    int count, deleted, last = -1, perm = 0;
	    deleted = process_numlist(nick, &count, access_del_callback, u,
					ci, &last, &perm, get_access(u, ci));
	    if (!deleted) {
		if (perm) {
		    notice_lang(s_ChanServ, u, PERMISSION_DENIED);
		} else if (count == 1) {
		    notice_lang(s_ChanServ, u, CHAN_ACCESS_NO_SUCH_ENTRY,
				last, ci->name);
		} else {
		    notice_lang(s_ChanServ, u, CHAN_ACCESS_NO_MATCH, ci->name);
		}
	    } else if (deleted == 1) {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_DELETED_ONE, ci->name);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_DELETED_SEVERAL,
				deleted, ci->name);
	    }
	} else { /* Not a number/list; search for it as a nickname. */
	    ni = findnick(nick);
	    if (!ni) {
		notice_lang(s_ChanServ, u, NICK_X_NOT_REGISTERED, nick);
		return;
	    }
	    for (i = 0; i < ci->accesscount; i++) {
		if (ci->access[i].ni == ni)
		    break;
	    }
	    if (i == ci->accesscount) {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_NOT_FOUND, nick, chan);
		return;
	    }
	    switch (access_del(ci, i, get_access(u,ci))) {
	      case RET_DELETED:
		notice_lang(s_ChanServ, u, CHAN_ACCESS_DELETED,
			    ni->nick, ci->name);
		break;
	      case RET_PERMISSION:
		notice_lang(s_ChanServ, u, PERMISSION_DENIED);
		break;
	    }
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	int sent_header = 0;

	if (ci->accesscount == 0) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LIST_EMPTY, chan);
	    return;
	}
	if (nick && strspn(nick, "1234567890,-") == strlen(nick)) {
	    process_numlist(nick,NULL,access_list_callback,u,ci,&sent_header);
	} else {
	    for (i = 0; i < ci->accesscount; i++) {
		if (nick && ci->access[i].ni
			 && !match_wild_nocase(nick, ci->access[i].ni->nick))
		    continue;
		access_list(u, i, ci, &sent_header);
	    }
	}
	if (!sent_header)
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_NO_MATCH, chan);

    } else if (stricmp(cmd, "COUNT") == 0) {
	int count = 0;
	for (i = 0; i < ci->accesscount; i++) {
	    if (ci->access[i].in_use)
		count++;
	}
	notice_lang(s_ChanServ, u, CHAN_ACCESS_COUNT, ci->name, count);

    } else { /* Unknown command */
	syntax_error(s_ChanServ, u, "ACCESS", CHAN_ACCESS_SYNTAX);
    }
}

/*************************************************************************/
/*************************************************************************/

/* Delete the num'th access list entry with access level oplevel.
 * Note: Permission checking is assumed to have been done.
 */

static int xop_del_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *offset = va_arg(args, int *);
    int *last = va_arg(args, int *);
    int oplevel = va_arg(args, int);
    int i, j;

    *last = num;
    num -= *offset; /* compensate for deleted items */
    if (num < 1)
	return 0;
    if (num > ci->accesscount)
	return -1; /* num is out of range. stop processing the list. */

    for (i = 0, j = num; i < ci->accesscount && j > 0; i++) {
	if (ci->access[i].in_use && ci->access[i].level == oplevel)
	    j--;
    }
    if (j > 0)
	return -1; /* no more entries to process. stop processing the list. */
    i--;
    ci->access[i].ni = NULL;
    ci->access[i].in_use = 0;
    (*offset)++;
    return 1;
}

static int xop_list(User *u, int index, ChannelInfo *ci, int *sent_header,
	int relindex)
{
    ChanAccess *access = &ci->access[index];
    NickInfo *ni = access->ni;
    char *s;

    if (!*sent_header) {
	notice_lang(s_ChanServ, u, CHAN_XOP_LIST_HEADER,
		    XOP_LISTNAME(access->level), ci->name);
	*sent_header = 1;
    }
    if (!(getlink(ni)->flags & NI_HIDE_MASK))
	s = ni->last_usermask;
    else
	s = NULL;
    notice_lang(s_ChanServ, u, CHAN_XOP_LIST_FORMAT, relindex, ni->nick,
		s ? " (" : "", s ? s : "", s ? ")" : "");
    return 1;
}

static int xop_list_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *sent_header = va_arg(args, int *);
    int oplevel = va_arg(args, int);
    int i, j;

    if (num < 1 || num > ci->accesscount)
	return 0;
    for (i = 0, j = num; i < ci->accesscount && j > 0; i++) {
	if (ci->access[i].in_use && ci->access[i].level == oplevel)
	    j--;
    }
    i--;
    return j ? 0 : xop_list(u, i, ci, sent_header, num);
}

/*************************************************************************/

/* Central handler for all SOP, AOP and VOP commands. */

static void handle_xop(User *u, int level)
{
    char *chan = strtok(NULL, " ");
    char *cmd = strtok(NULL, " ");
    char *nick = strtok(NULL, " ");
    ChannelInfo *ci;
    NickInfo *ni;
    int i;
    const char *listname = XOP_LISTNAME(level);
    int is_list = (cmd && (stricmp(cmd,"LIST")==0 || stricmp(cmd,"COUNT")==0));

    if (!cmd || (!is_list && !nick) || (stricmp(cmd,"COUNT")==0 && nick)) {
	syntax_error(s_ChanServ, u, listname, XOP_SYNTAX(level));
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (((is_list && !check_access(u, ci, CA_ACCESS_LIST))
		|| (!is_list && !check_access(u, ci, CA_ACCESS_CHANGE)))
	       && !is_services_admin(u))
    {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);

    } else if (stricmp(cmd, "ADD") == 0) {
	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_DISABLED);
	    return;
	}
	switch (access_add(ci, nick, level, get_access(u,ci))) {
	  case RET_ADDED:
	    notice_lang(s_ChanServ, u, CHAN_XOP_ADDED, nick, chan, listname);
	    break;
	  case RET_CHANGED:
	    notice_lang(s_ChanServ, u, CHAN_XOP_LEVEL_CHANGED,
			nick, chan, listname);
	    break;
	  case RET_UNCHANGED:
	    notice_lang(s_ChanServ, u, CHAN_XOP_LEVEL_UNCHANGED,
			nick, chan, listname);
	    break;
	  case RET_LISTFULL:
#ifdef HAVE_HALFOP
	    notice_lang(s_ChanServ, u, CHAN_XOP_REACHED_LIMIT_HOP, CSAccessMax);
#else
	    notice_lang(s_ChanServ, u, CHAN_XOP_REACHED_LIMIT, CSAccessMax);
#endif
	    break;
	  case RET_NOSUCHNICK:
#ifdef HAVE_HALFOP
	    notice_lang(s_ChanServ, u, CHAN_XOP_NICKS_ONLY_HOP);
#else
	    notice_lang(s_ChanServ, u, CHAN_XOP_NICKS_ONLY);
#endif
	    break;
	  case RET_NICKFORBID:
	    notice_lang(s_ChanServ, u, NICK_X_FORBIDDEN, nick);
	    break;
	  case RET_PERMISSION:
	    notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	    break;
	}

    } else if (stricmp(cmd, "DEL") == 0) {
	if (level >= get_access(u, ci)) {
	    notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	    return;
	} else if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_DISABLED);
	    return;
	}

	if (isdigit(*nick) && strspn(nick, "1234567890,-") == strlen(nick)) {
	    int count, deleted, last;
	    int offset = 0; /* used internally by the deletion routine. */
	    deleted = process_numlist(nick, &count, xop_del_callback, u,
			ci, &offset, &last, level);
	    if (!deleted) {
		if (count == 1) {
		    notice_lang(s_ChanServ, u, CHAN_XOP_NO_SUCH_ENTRY,
				last, ci->name, listname);
		} else {
		    notice_lang(s_ChanServ, u, CHAN_XOP_NO_MATCH,
		    		ci->name, listname);
		}
	    } else if (deleted == 1) {
		notice_lang(s_ChanServ, u, CHAN_XOP_DELETED_ONE,
				ci->name, listname);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_XOP_DELETED_SEVERAL,
				deleted, ci->name, listname);
	    }
	} else {
	    ni = findnick(nick);
	    if (!ni) {
		notice_lang(s_ChanServ, u, NICK_X_NOT_REGISTERED, nick);
		return;
	    }
	    for (i = 0; i < ci->accesscount; i++) {
		if (ci->access[i].in_use && ci->access[i].ni == ni)
		    break;
	    }
	    if (i == ci->accesscount || ci->access[i].level != level) {
		notice_lang(s_ChanServ, u, CHAN_XOP_NOT_FOUND,
				nick, chan, listname);
		return;
	    }
	    notice_lang(s_ChanServ, u, CHAN_XOP_DELETED,
			    ci->access[i].ni->nick, ci->name, listname);
	    ci->access[i].ni = NULL;
	    ci->access[i].in_use = 0;
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	int sent_header = 0;
	int relindex = 0;

	if (ci->accesscount == 0) {
	    notice_lang(s_ChanServ, u, CHAN_XOP_LIST_EMPTY, chan, listname);
	    return;
	}
	if (nick && strspn(nick, "1234567890,-") == strlen(nick)) {
	    process_numlist(nick, NULL, xop_list_callback, u, ci,
						    &sent_header, level);
	} else {
	    for (i = 0; i < ci->accesscount; i++) {
		if (!ci->access[i].in_use || ci->access[i].level != level)
		    continue;
		relindex++;
		if (nick && ci->access[i].ni
			 && !match_wild_nocase(nick, ci->access[i].ni->nick))
		    continue;
		xop_list(u, i, ci, &sent_header, relindex);
	    }
	}
	if (!sent_header)
	    notice_lang(s_ChanServ, u, CHAN_XOP_NO_MATCH, chan, listname);

    } else if (stricmp(cmd, "COUNT") == 0) {
	int count = 0;

	if (ci->accesscount == 0) {
	    notice_lang(s_ChanServ, u, CHAN_XOP_LIST_EMPTY, chan, listname);
	    return;
	}
	for (i = 0; i < ci->accesscount; i++) {
	    if (ci->access[i].in_use && ci->access[i].level == level)
		count++;
	}
	if (count)
	    notice_lang(s_ChanServ, u, CHAN_XOP_COUNT, chan, listname, count);
	else
	    notice_lang(s_ChanServ, u, CHAN_XOP_LIST_EMPTY, chan, listname);

    } else {
	syntax_error(s_ChanServ, u, listname, XOP_SYNTAX(level));
    }
}

/* SOP, VOP, AOP wrappers. */

static void do_sop(User *u)
{
    handle_xop(u, ACCLEV_SOP);
}

static void do_aop(User *u)
{
    handle_xop(u, ACCLEV_AOP);
}

#ifdef HAVE_HALFOP
static void do_hop(User *u)
{
    handle_xop(u, ACCLEV_HOP);
}
#endif

static void do_vop(User *u)
{
    handle_xop(u, ACCLEV_VOP);
}

/*************************************************************************/

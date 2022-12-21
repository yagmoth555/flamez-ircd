# Emacs mode: -*- text -*-

# United States English language file.
#
# IRC Services is copyright (c) 1996-2001 Andrew Church.
#     E-mail: <achurch@achurch.org>
# Parts copyright (c) 1999-2000 Andrew Kempe and others.
# This program is free but copyrighted software; see the file COPYING for
# details.

# When translating this file to another language, keep in mind that the
# order of parameters for sprintf() is fixed in the source code, so your
# messages need to take the same parameters in the same order as the
# English messages do.  (Obviously, this doesn't hold for the strftime()
# format lines immediately below.)  If you can't get a natural translation
# of a message without changing the order of the parameters, please inform
# the Services developers.
#
# In help messages, "%S" (capital S, not lowercase) refers to the name of
# the service sending the message; for example, in NickServ help messages,
# "%S" is replaced by "NickServ" (or whatever it is renamed to in
# config.h).  The %S's do not count as sprintf() parameters, so they can be
# rearranged, removed, or added as necessary.
#
# Also in help messages, please try to limit line lengths to 60 characters
# of text (not including the leading tab).  This length was chosen because
# it does not cause line wrap under default settings on most current IRC
# clients.  Remember that format characters (control-B, control-_) are not
# included in that 60-character limit (since they don't show on the user's
# screen).  Also remember that format specifiers (%S, etc.) will expand
# when displayed, so remember to take this into account; you can assume
# that the length of a pseudoclient name (%S replacement) will be eight
# characters, so reduce the maximum line length by 6 for every %S on a
# line.
#
# Finally, remember to put a tab at the beginning of every line of text
# (including empty lines).  This has to be a tab, not spaces.

###########################################################################
#
# Name of this language
#
###########################################################################

# For languages other than English, this string should have the following
# format:
#     language-name-in-language (language-name-in-English)
# For example, "Español (Spanish)" or "Français (French)".

LANG_NAME
	English

###########################################################################
#
# General messages
#
###########################################################################

# strftime() format strings.  man 3 strftime for information on the
# meanings of the format specifiers.  Short version:
#	%a = weekday name (short)	%H = hour
#	%b = month name (short)		%M = minute
#	%d = day of month		%S = second
#	%Y = year			%Z = time zone

# This is used as the format string for strftime() for a date and time
# together.
STRFTIME_DATE_TIME_FORMAT
	%b %d %H:%M:%S %Y %Z
# This is used as the format string for strftime() for a date alone in long
# format (English: including weekday).
STRFTIME_LONG_DATE_FORMAT
	%a %b %d %Y
# This is used as the format string for strftime() for a date alone in
# short format (English: without weekday).
STRFTIME_SHORT_DATE_FORMAT
	%b %d %Y

# These tell our strftime() what the names of months and days are.  If you
# don't use %a, %A, %b, or %B in your strftime() strings above, you can
# leave these empty.  However, if you enter names, they MUST stay in order,
# one per line, and the list MUST be complete!

# %a
STRFTIME_DAYS_SHORT
	Sun
	Mon
	Tue
	Wed
	Thu
	Fri
	Sat
# %A
STRFTIME_DAYS_LONG
	Sunday
	Monday
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
# %b
STRFTIME_MONTHS_SHORT
	Jan
	Feb
	Mar
	Apr
	May
	Jun
	Jul
	Aug
	Sep
	Oct
	Nov
	Dec
# %B
STRFTIME_MONTHS_LONG
	January
	February
	March
	April
	May
	June
	July
	August
	September
	October
	November
	December


# "day", "hour", "minute", and "second" in singular and plural.
STR_DAY
	day
STR_DAYS
	days
STR_HOUR
	hour
STR_HOURS
	hours
STR_MINUTE
	minute
STR_MINUTES
	minutes
STR_SECOND
	second
STR_SECONDS
	seconds


# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	, 


# Various error messages.
USER_RECORD_NOT_FOUND
	Internal error - unable to process request.
UNKNOWN_COMMAND
	Unknown command %s.
UNKNOWN_COMMAND_HELP
	Unknown command %s.  Type /msg %s HELP for help.
SYNTAX_ERROR
	Syntax: %s
MORE_INFO
	Type /msg %s HELP %s for more information.
NO_HELP_AVAILABLE
	No help available for %s.

BAD_EMAIL
	E-mail addresses must be in the form username@hostname.  You may not use colors, bold, underline, or reverse, or any of these characters: , : ; | \ " ( ) < >
BAD_URL
	URLs must be in the form http://hostname[:port]/... (or ftp://, etc.).
BAD_USERHOST_MASK
	Mask must be in the form user@host.
BAD_EXPIRY_TIME
	Invalid expiry time.

SERVICE_OFFLINE
	%s is currently offline.
READ_ONLY_MODE
	Notice: Services is in read-only mode; changes will not be saved!
PASSWORD_INCORRECT
	Password incorrect.

# What's the difference between "Access denied" and "Permission denied"?
# Very little; you can safely make them the same message with no real loss
# of meaning.  If you want to make a distinction, "Access denied" is
# usually used more generally; for example, a non-oper trying to access
# OperServ gets "Access denied", while a non-Services admin trying to use
# NickServ SET NOEXPIRE gets "Permission denied".
ACCESS_DENIED
	Access denied.
PERMISSION_DENIED
	Permission denied.

MORE_OBSCURE_PASSWORD
	Please try again with a more obscure password.  Passwords should be at least five characters long, should not be something easily guessed (e.g. your real name or your nick), and cannot contain the space or tab characters.
PASSWORD_TRUNCATED
	Notice:  Your password has been truncated to %d characters.

NICK_NOT_REGISTERED
	Your nick isn't registered.
NICK_NOT_REGISTERED_HELP
	Your nick isn't registered.  Type /msg %s HELP for information on registering your nickname.
NICK_X_NOT_REGISTERED
	Nick %s isn't registered.
NICK_X_NOT_IN_USE
	Nick %s isn't currently in use.
NICK_X_FORBIDDEN
	Nick %s may not be registered or used.
NICK_X_SUSPENDED
	Nick %s is suspended and may not be used or identified for.
NICK_X_SUSPENDED_MEMOS
	Nick %s is suspended and may not receive memos.
NICK_IDENTIFY_REQUIRED
	Password authentication required for that command.
	Retry after typing /msg %s IDENTIFY password.
NICK_X_NOT_ON_CHAN_X
	Nick %s isn't currently on channel %s.

CHAN_X_NOT_REGISTERED
	Channel %s isn't registered.
CHAN_X_NOT_IN_USE
	Channel %s isn't currently in use.
CHAN_X_FORBIDDEN
	Channel %s may not be registered or used.
CHAN_X_SUSPENDED
	Channel %s is suspended and may not be used or identified for.
CHAN_X_SUSPENDED_MEMOS
	Channel %s is suspended and may not receive memos.
CHAN_IDENTIFY_REQUIRED
	Password authentication required for that command.
	Retry after typing /msg %s IDENTIFY %s password.

SERV_X_NOT_FOUND
	Server %s not found.

EXPIRES_NONE
	does not expire
EXPIRES_SOON
	expires at next database update
EXPIRES_M
	expires in %d minutes
EXPIRES_1M
	expires in %d minute
EXPIRES_HM
	expires in %d hours, %d minutes
EXPIRES_H1M
	expires in %d hours, %d minute
EXPIRES_1HM
	expires in %d hour, %d minutes
EXPIRES_1H1M
	expires in %d hour, %d minute
EXPIRES_D
	expires in %d days
EXPIRES_1D
	expires in %d day

###########################################################################
#
# NickServ messages
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	This nick is owned by someone else.  Please choose another.
	(If this is your nick, type /msg %s IDENTIFY password.)
NICK_IS_SECURE
	This nickname is registered and protected.  If it is your
	nick, type /msg %s IDENTIFY password.  Otherwise,
	please choose a different nick.
NICK_MAY_NOT_BE_USED
	This nickname may not be used. Please choose another one.
DISCONNECT_IN_1_MINUTE
	If you do not change within one minute, you will be disconnected.
DISCONNECT_IN_20_SECONDS
	If you do not change within 20 seconds, you will be disconnected.
DISCONNECT_NOW
	This nickname has been registered; you may not use it. Please
	choose another nickname before reconnecting.
FORCENICKCHANGE_IN_1_MINUTE
	If you do not change within one minute, I will change your nick.
FORCENICKCHANGE_IN_20_SECONDS
	If you do not change within 20 seconds, I will change your nick.
FORCENICKCHANGE_NOW
	This nickname has been registered; you may not use it.
	Your nickname is now being changed to %s.
NICK_EXPIRES_SOON
	Notice: Your nickname's registration will expire in %d %s.  If you want to continue using your nickname, please identify to %s by typing: /msg %s IDENTIFY password
NICK_EXPIRED
	Notice: Your nickname's registration has expired.  Please re-register your nickname if you want to continue using it.

# REGISTER responses
NICK_REGISTER_SYNTAX
	REGISTER password [email]
NICK_REGISTER_REQ_EMAIL_SYNTAX
	REGISTER password email
NICK_REGISTRATION_DISABLED
	Sorry, nickname registration is temporarily disabled.
NICK_REGISTRATION_FAILED
	Sorry, registration failed.
NICK_REG_PLEASE_WAIT
	Please wait %d seconds before using the REGISTER command again.
NICK_CANNOT_BE_REGISTERED
	Nickname %s may not be registered.
NICK_ALREADY_REGISTERED
	Nickname %s is already registered!
NICK_REGISTERED
	Nickname %s registered under your account: %s
NICK_PASSWORD_IS
	Your password is %s - remember this for later use.

# IDENTIFY responses
NICK_IDENTIFY_SYNTAX
	IDENTIFY password
NICK_IDENTIFY_FAILED
	Sorry, identification failed.
NICK_IDENTIFY_SUCCEEDED
	Password accepted - you are now recognized.

# DROP responses
NICK_DROP_SYNTAX
	DROP
NICK_DROP_DISABLED
	Sorry, nickname de-registration is temporarily disabled.
NICK_DROPPED
	Your nickname has been dropped.
NICK_X_DROPPED
	Nickname %s has been dropped.

# SET responses
NICK_SET_SYNTAX
	SET option parameters
NICK_SET_SERVADMIN_SYNTAX
	SET [nick] option parameters
NICK_SET_DISABLED
	Sorry, nickname option setting is temporarily disabled.
NICK_SET_UNKNOWN_OPTION
	Unknown SET option %s.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	Unknown SET option %s, or nickname not registered.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	Sorry, couldn't change password.
NICK_SET_PASSWORD_CHANGED
	Password changed.
NICK_SET_PASSWORD_CHANGED_TO
	Password changed to %s.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_SYNTAX
	SET LANGUAGE number
NICK_SET_LANGUAGE_UNKNOWN
	Unknown language number %d.  Type /msg %s HELP SET LANGUAGE for a list of languages.
NICK_SET_LANGUAGE_CHANGED
	Language changed to English.

# SET URL responses
NICK_SET_URL_CHANGED
	URL for %s changed to %s.

# SET EMAIL responses
NICK_SET_EMAIL_CHANGED
	E-mail address for %s changed to %s.

# SET KILL responses
NICK_SET_KILL_SYNTAX
	SET KILL {ON | QUICK | OFF}
NICK_SET_KILL_IMMED_SYNTAX
	SET KILL {ON | QUICK | IMMED | OFF}
NICK_SET_KILL_ON
	Kill protection is now ON.
NICK_SET_KILL_QUICK
	Kill protection is now ON, with a reduced kill delay.
NICK_SET_KILL_IMMED
	Kill protection is now ON, with no kill delay.
NICK_SET_KILL_IMMED_DISABLED
	The IMMED option is not available on this network.
NICK_SET_KILL_OFF
	Kill protection is now OFF.

# SET SECURE responses
NICK_SET_SECURE_SYNTAX
	SET SECURE {ON | OFF}
NICK_SET_SECURE_ON
	Secure option is now ON.
NICK_SET_SECURE_OFF
	Secure option is now OFF.

# SET PRIVATE responses
NICK_SET_PRIVATE_SYNTAX
	SET PRIVATE {ON | OFF}
NICK_SET_PRIVATE_ON
	Private option is now ON.
NICK_SET_PRIVATE_OFF
	Private option is now OFF.

# SET HIDE responses
NICK_SET_HIDE_SYNTAX
	SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
NICK_SET_HIDE_EMAIL_ON
	Your E-mail address will now be hidden from %s INFO displays.
NICK_SET_HIDE_EMAIL_OFF
	Your E-mail address will now be shown in %s INFO displays.
NICK_SET_HIDE_MASK_ON
	Your last seen user@host mask will now be hidden from %s INFO displays.
NICK_SET_HIDE_MASK_OFF
	Your last seen user@host mask will now be shown in %s INFO displays.
NICK_SET_HIDE_QUIT_ON
	Your last quit message will now be hidden from %s INFO displays.
NICK_SET_HIDE_QUIT_OFF
	Your last quit message will now be shown in %s INFO displays.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_SYNTAX
	SET [nickname] NOEXPIRE {ON | OFF}
NICK_SET_NOEXPIRE_ON
	Nick %s will not expire.
NICK_SET_NOEXPIRE_OFF
	Nick %s will expire.

# UNSET responses
NICK_UNSET_SYNTAX
	UNSET {URL | EMAIL}
NICK_UNSET_SYNTAX_REQ_EMAIL
	UNSET URL
NICK_UNSET_URL
	URL for %s unset.
NICK_UNSET_EMAIL
	E-mail address for %s unset.
NICK_UNSET_EMAIL_BAD
	You may not clear your E-mail address.
NICK_UNSET_EMAIL_OTHER_BAD
	Nickname E-mail addresses may not be cleared.

# ACCESS responses
NICK_ACCESS_SYNTAX
	ACCESS {ADD | DEL | LIST} [mask]
NICK_ACCESS_ALREADY_PRESENT
	Mask %s already present on your access list.
NICK_ACCESS_REACHED_LIMIT
	Sorry, you can only have %d access entries for a nickname.
NICK_ACCESS_ADDED
	%s added to your access list.
NICK_ACCESS_NOT_FOUND
	%s not found on your access list.
NICK_ACCESS_DELETED
	%s deleted from your access list.
NICK_ACCESS_LIST
	Access list:
NICK_ACCESS_LIST_X
	Access list for %s:

# LINK responses
NICK_LINK_SYNTAX
	LINK nick password
NICK_LINK_DISABLED
	The LINK command is not available.
NICK_LINK_FAILED
	Sorry, linking failed.
NICK_NO_LINK_SAME
	You can't link to your current nick!
NICK_LINK_CIRCULAR
	Can't link to nick %s: circular link detected.
NICK_LINK_TOO_DEEP
	You can't create a link more than %d levels deep.
NICK_LINK_TOO_MANY_CHANNELS
	Can't link to nick %s: too many channels registered (combined maximum %d).
NICK_LINKED
	Your nick has been linked to %s.

# UNLINK responses
NICK_UNLINK_SYNTAX
	UNLINK [nick password]
NICK_UNLINK_FAILED
	Sorry, unlinking failed.
NICK_NOT_LINKED
	Your nick isn't linked.
NICK_UNLINKED
	Your nick has been unlinked from %s.
NICK_X_NOT_LINKED
	Nick %s isn't linked.
NICK_X_UNLINKED
	Nick %s has been unlinked from %s.

# LISTLINKS responses
NICK_LISTLINKS_SYNTAX
	LISTLINKS nick [ALL]
NICK_LISTLINKS_HEADER
	List of nicknames linked to %s:
NICK_LISTLINKS_FOOTER
	%d linked nicknames.
NICK_X_IS_LINKED
	    %s
NICK_X_IS_LINKED_VIA_X
	    %-20s (via %s)

# INFO responses
NICK_INFO_SYNTAX
	INFO nick [ALL]
NICK_INFO_REALNAME
	%s is %s
NICK_INFO_ADDRESS
	Last seen address: %s
NICK_INFO_ADDRESS_ONLINE
	   Is online from: %s
NICK_INFO_ADDRESS_ONLINE_NOHOST
	%s is currently online.
NICK_INFO_TIME_REGGED
	  Time registered: %s
NICK_INFO_LAST_SEEN
	   Last seen time: %s
NICK_INFO_LAST_QUIT
	Last quit message: %s
NICK_INFO_URL
	              URL: %s
NICK_INFO_EMAIL
	   E-mail address: %s
NICK_INFO_OPTIONS
	          Options: %s
NICK_INFO_LINKED_TO
	        Linked to: %s
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	Kill protection
NICK_INFO_OPT_SECURE
	Security
NICK_INFO_OPT_PRIVATE
	Private
NICK_INFO_OPT_NONE
	None
NICK_INFO_NO_EXPIRE
	This nickname will not expire.
NICK_INFO_SUSPEND_DETAILS
	Suspended by %s on %s (%s).
NICK_INFO_SUSPEND_REASON
	Reason: %s
NICK_INFO_SHOW_ALL
	For more information, type: /msg %s INFO %s ALL

# LISTCHANS responses
NICK_LISTCHANS_SYNTAX
	LISTCHANS
NICK_LISTCHANS_SERVADMIN_SYNTAX
	LISTCHANS [nickname]
NICK_LISTCHANS_NONE
	%s has not registered any channels.
NICK_LISTCHANS_HEADER
	Channels registered by %s:
NICK_LISTCHANS_ENTRY
	    %s
NICK_LISTCHANS_END
	End of list (%d channels registered).

# LIST responses
NICK_LIST_SYNTAX
	LIST pattern
NICK_LIST_SERVADMIN_SYNTAX
	LIST pattern [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
NICK_LIST_HEADER
	List of entries matching %s:
NICK_LIST_RESULTS
	End of list - %d/%d matches shown.

# RECOVER responses
NICK_RECOVER_SYNTAX
	RECOVER nickname [password]
NICK_NO_RECOVER_SELF
	You can't recover yourself!
NICK_RECOVERED
	User claiming your nick has been killed.
	/msg %s RELEASE %s to get it back before the one-minute timeout.

# RELEASE responses
NICK_RELEASE_SYNTAX
	RELEASE nickname [password]
NICK_RELEASE_NOT_HELD
	Nick %s isn't being held.
NICK_RELEASED
	Services' hold on your nick has been released.

# GHOST responses
NICK_GHOST_SYNTAX
	GHOST nickname [password]
NICK_NO_GHOST_SELF
	You can't ghost yourself!
NICK_GHOST_KILLED
	Ghost with your nick has been killed.

# GETPASS responses
NICK_GETPASS_SYNTAX
	GETPASS nickname
NICK_GETPASS_UNAVAILABLE
	GETPASS command unavailable because encryption is in use.
NICK_GETPASS_PASSWORD_IS
	Password for %s is %s.

# FORBID responses
NICK_FORBID_SYNTAX
	FORBID nickname
NICK_FORBID_SUCCEEDED
	Nick %s is now forbidden.
NICK_FORBID_FAILED
	Couldn't forbid nick %s!

# SUSPEND responses
NICK_SUSPEND_SYNTAX
	SUSPEND [+expiry] nickname reason
NICK_SUSPEND_SUCCEEDED
	Nick %s, and all nicks with the same root nick, have been suspended.
NICK_SUSPEND_ALREADY_SUSPENDED
	Nick %s is already suspended.

# UNSUSPEND responses
NICK_UNSUSPEND_SYNTAX
	UNSUSPEND nickname
NICK_UNSUSPEND_SUCCEEDED
	Nick %s has been unsuspended.
NICK_SUSPEND_NOT_SUSPENDED
	Nick %s is not suspended.

###########################################################################
#
# ChanServ messages
#
###########################################################################

# Access level descriptions
CHAN_LEVEL_AUTOOP
	Automatic channel operator status
CHAN_LEVEL_AUTOVOICE
	Automatic mode +v
CHAN_LEVEL_AUTODEOP
	Channel operator status disallowed
CHAN_LEVEL_AUTODEOP_HALFOP
	Channel operator/halfop status disallowed
CHAN_LEVEL_NOJOIN
	Not allowed to join channel if RESTRICTED
CHAN_LEVEL_INVITE
	Allowed to use INVITE command
CHAN_LEVEL_AKICK
	Allowed to use AKICK command
CHAN_LEVEL_SET
	Allowed to use SET command (not FOUNDER/PASSWORD)
CHAN_LEVEL_CLEAR
	Allowed to use CLEAR command
CHAN_LEVEL_UNBAN
	Allowed to use UNBAN command
CHAN_LEVEL_OPDEOP
	Allowed to use OP/DEOP commands
CHAN_LEVEL_ACCESS_LIST
	Allowed to view the access list
CHAN_LEVEL_ACCESS_CHANGE
	Allowed to modify the access list
CHAN_LEVEL_MEMO
	Allowed to list/read channel memos
CHAN_LEVEL_VOICE
	Allowed to use VOICE/DEVOICE commands
CHAN_LEVEL_AUTOHALFOP
	Automatic halfop (+h) status
CHAN_LEVEL_HALFOP
	Allowed to use HALFOP/DEHALFOP commands
CHAN_LEVEL_AUTOPROTECT
	Automatic channel protect (+a) status
CHAN_LEVEL_PROTECT
	Allowed to use PROTECT/DEPROTECT commands

# Automatic responses
CHAN_IS_REGISTERED
	This channel has been registered with %s.
CHAN_NOT_ALLOWED_OP
	You are not allowed chanop status on channel %s.
CHAN_MAY_NOT_BE_USED
	This channel may not be used.
CHAN_NOT_ALLOWED_TO_JOIN
	You are not permitted to be on this channel.

# Multi-purpose responses
CHAN_BOUNCY_MODES
	Sorry, the %s command is temporarily unavailable.

# REGISTER responses
CHAN_REGISTER_SYNTAX
	REGISTER channel password description
CHAN_REGISTER_DISABLED
	Sorry, channel registration is temporarily disabled.
CHAN_REGISTER_NOT_LOCAL
	Local channels cannot be registered.
CHAN_MUST_REGISTER_NICK
	You must register your nickname first.  Type /msg %s HELP for information on registering nicknames.
CHAN_MUST_IDENTIFY_NICK
	Please identify with %s first, using the command:
	/msg %s IDENTIFY password
CHAN_MAY_NOT_BE_REGISTERED
	Channel %s may not be registered.
CHAN_ALREADY_REGISTERED
	Channel %s is already registered!
CHAN_MUST_BE_CHANOP
	You must be a channel operator to register the channel.
CHAN_REACHED_CHANNEL_LIMIT
	Sorry, you have already reached your limit of %d channels.
CHAN_EXCEEDED_CHANNEL_LIMIT
	Sorry, you have already exceeded your limit of %d channels.
CHAN_REGISTRATION_FAILED
	Sorry, registration failed.
CHAN_REGISTERED
	Channel %s registered under your nickname: %s
CHAN_PASSWORD_IS
	Your channel password is %s - remember it for later use.

# IDENTIFY responses
CHAN_IDENTIFY_SYNTAX
	IDENTIFY channel password
CHAN_IDENTIFY_FAILED
	Sorry, identification failed.
CHAN_IDENTIFY_SUCCEEDED
	Password accepted - you now have founder-level access to %s.

# DROP responses
CHAN_DROP_SYNTAX
	DROP channel
CHAN_DROP_DISABLED
	Sorry, channel de-registration is temporarily disabled.
CHAN_DROPPED
	Channel %s has been dropped.

# SET responses
CHAN_SET_SYNTAX
	SET channel option parameters
CHAN_SET_DISABLED
	Sorry, channel option setting is temporarily disabled.
CHAN_SET_UNKNOWN_OPTION
	Unknown SET option %s.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	%s has too many channels registered.
CHAN_FOUNDER_CHANGED
	Founder of %s changed to %s.

# SET SUCCESSOR responses
CHAN_SUCCESSOR_CHANGED
	Successor for %s changed to %s.
CHAN_SUCCESSOR_IS_FOUNDER
	You can't make the founder of a channel the successor too.

# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Sorry, couldn't set password.
CHAN_PASSWORD_CHANGED
	%s password changed.
CHAN_PASSWORD_CHANGED_TO
	%s password changed to %s.

# SET DESC responses
CHAN_DESC_CHANGED
	Description of %s changed to %s.

# SET URL responses
CHAN_URL_CHANGED
	URL for %s changed to %s.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	E-mail address for %s changed to %s.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	Entry message for %s changed.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Sorry, can't set topic.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	Parameter required for MLOCK +k.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	Parameter required for MLOCK +l.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	Parameter for MLOCK +l must be a positive number.
CHAN_SET_MLOCK_MODE_REG_BAD
	Mode +%c is always set on registered channels, and cannot be used with MLOCK.
CHAN_SET_MLOCK_MODE_F_BAD
	Mode +f cannot be locked.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Unknown mode character %c ignored.
CHAN_MLOCK_CHANGED
	Mode lock on channel %s changed to %s.
CHAN_MLOCK_REMOVED
	Mode lock on channel %s removed.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_SYNTAX
	SET channel KEEPTOPIC {ON | OFF}
CHAN_SET_KEEPTOPIC_ON
	Topic retention option is now ON.
CHAN_SET_KEEPTOPIC_OFF
	Topic retention option is now OFF.

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_SYNTAX
	SET channel TOPICLOCK {ON | OFF}
CHAN_SET_TOPICLOCK_ON
	Topic lock option is now ON.
CHAN_SET_TOPICLOCK_OFF
	Topic lock option is now OFF.

# SET PRIVATE responses
CHAN_SET_PRIVATE_SYNTAX
	SET channel PRIVATE {ON | OFF}
CHAN_SET_PRIVATE_ON
	Private option is now ON.
CHAN_SET_PRIVATE_OFF
	Private option is now OFF.

# SET SECUREOPS responses
CHAN_SET_SECUREOPS_SYNTAX
	SET channel SECUREOPS {ON | OFF}
CHAN_SET_SECUREOPS_ON
	Secure ops option is now ON.
CHAN_SET_SECUREOPS_OFF
	Secure ops option is now OFF.

# SET LEAVEOPS responses
CHAN_SET_LEAVEOPS_SYNTAX
	SET channel LEAVEOPS {ON | OFF}
CHAN_SET_LEAVEOPS_ON
	Leave ops option is now ON.
CHAN_SET_LEAVEOPS_OFF
	Leave ops option is now OFF.

# SET RESTRICTED responses
CHAN_SET_RESTRICTED_SYNTAX
	SET channel RESTRICTED {ON | OFF}
CHAN_SET_RESTRICTED_ON
	Restricted access option is now ON.
CHAN_SET_RESTRICTED_OFF
	Restricted access option is now OFF.

# SET SECURE responses
CHAN_SET_SECURE_SYNTAX
	SET channel SECURE {ON | OFF}
CHAN_SET_SECURE_ON
	Secure option is now ON.
CHAN_SET_SECURE_OFF
	Secure option is now OFF.

# SET OPNOTICE responses
CHAN_SET_OPNOTICE_SYNTAX
	SET channel OPNOTICE {ON | OFF}
CHAN_SET_OPNOTICE_ON
	Op-notice option is now ON.
CHAN_SET_OPNOTICE_OFF
	Op-notice option is now OFF.

# SET ENFORCE responses
CHAN_SET_ENFORCE_SYNTAX
	SET channel ENFORCE {ON | OFF}
CHAN_SET_ENFORCE_ON
	Enforce option is now ON.
CHAN_SET_ENFORCE_OFF
	Enforce option is now OFF.

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_SYNTAX
	SET channel NOEXPIRE {ON | OFF}
CHAN_SET_NOEXPIRE_ON
	Channel %s will not expire.
CHAN_SET_NOEXPIRE_OFF
	Channel %s will expire.

# UNSET responses
CHAN_UNSET_SYNTAX
	UNSET channel {SUCCESSOR | URL | EMAIL | ENTRYMSG}
CHAN_SUCCESSOR_UNSET
	Successor for %s unset.
CHAN_URL_UNSET
	URL for %s unset.
CHAN_EMAIL_UNSET
	E-mail address for %s unset.
CHAN_ENTRY_MSG_UNSET
	Entry message for %s unset.

# ACCESS messages
CHAN_ACCESS_SYNTAX
	ACCESS channel {ADD | DEL | LIST | COUNT} [nick [level] | entry-list]
CHAN_ACCESS_DISABLED
	Sorry, channel access list modification is temporarily disabled.
CHAN_ACCESS_LEVEL_NONZERO
	Access level must be non-zero.
CHAN_ACCESS_LEVEL_RANGE
	Access level must be between %d and %d inclusive.
CHAN_ACCESS_NICKS_ONLY
	Channel access lists may only contain registered nicknames.
CHAN_ACCESS_REACHED_LIMIT
	Sorry, you can only have %d access entries on a channel.
CHAN_ACCESS_LEVEL_UNCHANGED
	Access level for %s on %s unchanged from %d.
CHAN_ACCESS_LEVEL_CHANGED
	Access level for %s on %s changed to %d.
CHAN_ACCESS_ADDED
	%s added to %s access list at level %d.
CHAN_ACCESS_NO_SUCH_ENTRY
	No such entry (#%d) on %s access list.
CHAN_ACCESS_NOT_FOUND
	%s not found on %s access list.
CHAN_ACCESS_NO_MATCH
	No matching entries on %s access list.
CHAN_ACCESS_DELETED
	%s deleted from %s access list.
CHAN_ACCESS_DELETED_ONE
	Deleted 1 entry from %s access list.
CHAN_ACCESS_DELETED_SEVERAL
	Deleted %d entries from %s access list.
CHAN_ACCESS_LIST_EMPTY
	%s access list is empty.
CHAN_ACCESS_LIST_HEADER
	Access list for %s:
	  Num   Lev  Nick
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s
CHAN_ACCESS_COUNT
	The %s access list has %d entries.

# XOP (AOP/SOP/VOP) responses
CHAN_SOP_SYNTAX
	SOP channel {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_AOP_SYNTAX
	AOP channel {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_HOP_SYNTAX
	HOP channel {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_VOP_SYNTAX
	VOP channel {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_XOP_ADDED
	%s added to %s %s list.
CHAN_XOP_LEVEL_CHANGED
	%s moved to %s %s list.
CHAN_XOP_LEVEL_UNCHANGED
	%s is already on the %s %s list.
CHAN_XOP_NICKS_ONLY
	SOP, AOP, and VOP lists may only contain registered nicknames.
CHAN_XOP_NICKS_ONLY_HOP
	SOP, AOP, HOP, and VOP lists may only contain registered nicknames.
CHAN_XOP_REACHED_LIMIT
	Sorry, the number of entries on your SOP, AOP and VOP lists
	may not total more than %d entries.  Limit exceeded.
CHAN_XOP_REACHED_LIMIT_HOP
	Sorry, the number of entries on your SOP, AOP, HOP and VOP
	lists may not total more than %d entries.  Limit exceeded.
CHAN_XOP_NOT_FOUND
	%s not found on %s %s list.
CHAN_XOP_NO_SUCH_ENTRY
	No such entry (#%d) on %s %s list.
CHAN_XOP_NO_MATCH
	No matching entries on %s %s list.
CHAN_XOP_DELETED
	%s deleted from %s %s list.
CHAN_XOP_DELETED_ONE
	Deleted 1 entry from %s %s list.
CHAN_XOP_DELETED_SEVERAL
	Deleted %d entries from %s %s list.
CHAN_XOP_LIST_EMPTY
	%s %s list is empty.
CHAN_XOP_LIST_HEADER
	%s list for %s:
	  Num   Nick
CHAN_XOP_LIST_FORMAT
	  %3d   %s%s%s%s
CHAN_XOP_COUNT
	The %s %s list has %d entries.

# AKICK responses
CHAN_AKICK_SYNTAX
	AKICK channel {ADD | DEL | LIST | VIEW | ENFORCE | COUNT} [mask | list]
CHAN_AKICK_DISABLED
	Sorry, channel autokick list modification is temporarily disabled.
CHAN_AKICK_ALREADY_EXISTS
	%s already exists on %s autokick list.
CHAN_AKICK_REACHED_LIMIT
	Sorry, you can only have %d autokick masks on a channel.
CHAN_AKICK_ADDED
	%s added to %s autokick list.
CHAN_AKICK_NO_SUCH_ENTRY
	No such entry (#%d) on %s autokick list.
CHAN_AKICK_NOT_FOUND
	%s not found on %s autokick list.
CHAN_AKICK_NO_MATCH
	No matching entries on %s autokick list.
CHAN_AKICK_DELETED
	%s deleted from %s autokick list.
CHAN_AKICK_DELETED_ONE
	Deleted 1 entry from %s autokick list.
CHAN_AKICK_DELETED_SEVERAL
	Deleted %d entries from %s autokick list.
CHAN_AKICK_LIST_EMPTY
	%s autokick list is empty.
CHAN_AKICK_LIST_HEADER
	Autokick list for %s:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s
CHAN_AKICK_VIEW_FORMAT
	  %3d %s (by %s)
	    %s
CHAN_AKICK_ENFORCE_DONE
	AKICK ENFORCE for %s complete; %d users were affected.
CHAN_AKICK_COUNT
	%s has %d entries on its AKICK list.

# LEVELS responses
CHAN_LEVELS_SYNTAX
	LEVELS channel {SET | DIS[ABLE] | LIST | RESET} [item [level]]
CHAN_LEVELS_RANGE
	Level must be between %d and %d inclusive.
CHAN_LEVELS_CHANGED
	Level for %s on channel %s changed to %d.
CHAN_LEVELS_UNKNOWN
	Setting %s not known.  Type /msg %s HELP LEVELS DESC for a list of valid settings.
CHAN_LEVELS_DISABLED
	%s disabled on channel %s.
CHAN_LEVELS_LIST_HEADER
	Access level settings for channel %s:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (disabled)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (founder only)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	Access levels for %s reset to defaults.

# INFO responses
CHAN_INFO_SYNTAX
	INFO channel [ALL]
CHAN_INFO_HEADER
	Information for channel %s:
CHAN_INFO_FOUNDER
	        Founder: %s (%s)
CHAN_INFO_NO_FOUNDER
	        Founder: %s
CHAN_INFO_SUCCESSOR
	      Successor: %s (%s)
CHAN_INFO_NO_SUCCESSOR
	      Successor: %s
CHAN_INFO_DESCRIPTION
	    Description: %s
CHAN_INFO_ENTRYMSG
	  Entry message: %s
CHAN_INFO_TIME_REGGED
	     Registered: %s
CHAN_INFO_LAST_USED
	      Last used: %s
CHAN_INFO_LAST_TOPIC
	     Last topic: %s
CHAN_INFO_TOPIC_SET_BY
	   Topic set by: %s
CHAN_INFO_URL
	            URL: %s
CHAN_INFO_EMAIL
	 E-mail address: %s
CHAN_INFO_OPTIONS
	        Options: %s
CHAN_INFO_OPT_PRIVATE
	Private
CHAN_INFO_OPT_KEEPTOPIC
	Topic Retention
CHAN_INFO_OPT_TOPICLOCK
	Topic Lock
CHAN_INFO_OPT_SECUREOPS
	Secure Ops
CHAN_INFO_OPT_LEAVEOPS
	Leave Ops
CHAN_INFO_OPT_RESTRICTED
	Restricted Access
CHAN_INFO_OPT_SECURE
	Secure
CHAN_INFO_OPT_OPNOTICE
	Op-Notice
CHAN_INFO_OPT_ENFORCE
	Enforce
CHAN_INFO_OPT_NONE
	None
CHAN_INFO_MODE_LOCK
	      Mode lock: %s
CHAN_INFO_NO_EXPIRE
	This channel will not expire.
CHAN_INFO_SUSPEND_DETAILS
	Suspended by %s on %s (%s).
CHAN_INFO_SUSPEND_REASON
	Reason: %s
CHAN_INFO_SHOW_ALL
	For more information, type: /msg %s INFO %s ALL

# LIST responses
CHAN_LIST_SYNTAX
	LIST pattern
CHAN_LIST_SERVADMIN_SYNTAX
	LIST pattern [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
CHAN_LIST_HEADER
	List of entries matching %s:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	End of list - %d/%d matches shown.

# INVITE responses
CHAN_INVITE_SYNTAX
	INVITE channel
CHAN_INVITE_OK
	Inviting %s to channel %s.

# OP/DEOP/VOICE/DEVOICE responses
CHAN_OPVOICE_SYNTAX
	%s channel nick
CHAN_OP_SUCCEEDED
	Opped %s on channel %s.
CHAN_OP_FAILED
	Unable to op %s on channel %s.
CHAN_DEOP_SUCCEEDED
	Deopped %s on channel %s.
CHAN_DEOP_FAILED
	Unable to deop %s on channel %s.
CHAN_VOICE_SUCCEEDED
	Voiced %s on channel %s.
CHAN_VOICE_FAILED
	Unable to voice %s on channel %s.
CHAN_DEVOICE_SUCCEEDED
	Devoiced %s on channel %s.
CHAN_DEVOICE_FAILED
	Unable to devoice %s on channel %s.
CHAN_HALFOP_SUCCEEDED
	Halfopped %s on channel %s.
CHAN_HALFOP_FAILED
	Unable to halfop %s on channel %s.
CHAN_DEHALFOP_SUCCEEDED
	Dehalfopped %s on channel %s.
CHAN_DEHALFOP_FAILED
	Unable to dehalfop %s on channel %s.
CHAN_PROTECT_SUCCEEDED
	Protected %s on channel %s.
CHAN_PROTECT_FAILED
	Unable to protect %s on channel %s.
CHAN_DEPROTECT_SUCCEEDED
	Deprotected %s on channel %s.
CHAN_DEPROTECT_FAILED
	Unable to deprotect %s on channel %s.

# UNBAN responses
CHAN_UNBAN_SYNTAX
	UNBAN channel
CHAN_UNBANNED
	You have been unbanned from %s.

# CLEAR responses
CHAN_CLEAR_SYNTAX
	CLEAR channel what
CHAN_CLEARED_BANS
	All bans on channel %s have been removed.
CHAN_CLEARED_EXCEPTIONS
	All exceptions on channel %s have been removed.
CHAN_CLEARED_MODES
	All modes on channel %s have been reset.
CHAN_CLEARED_OPS
	Mode +o has been cleared from channel %s.
CHAN_CLEARED_HALFOPS
	Mode +h has been cleared from channel %s.
CHAN_CLEARED_VOICES
	Mode +v has been cleared from channel %s.
CHAN_CLEARED_USERS
	All users have been kicked from channel %s.

# GETPASS responses
CHAN_GETPASS_SYNTAX
	GETPASS channel
CHAN_GETPASS_UNAVAILABLE
	GETPASS command unavailable because encryption is in use.
CHAN_GETPASS_PASSWORD_IS
	Password for channel %s is %s.

# FORBID responses
CHAN_FORBID_SYNTAX
	FORBID channel
CHAN_FORBID_SUCCEEDED
	Channel %s is now forbidden.
CHAN_FORBID_FAILED
	Couldn't forbid channel %s!

# SUSPEND responses
CHAN_SUSPEND_SYNTAX
	SUSPEND [+expiry] channel reason
CHAN_SUSPEND_SUCCEEDED
	Channel %s has been suspended.
CHAN_SUSPEND_ALREADY_SUSPENDED
	Channel %s is already suspended.

# UNSUSPEND responses
CHAN_UNSUSPEND_SYNTAX
	UNSUSPEND channel
CHAN_UNSUSPEND_SUCCEEDED
	Channel %s has been unsuspended.
CHAN_SUSPEND_NOT_SUSPENDED
	Channel %s is not suspended.

###########################################################################
#
# MemoServ messages
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	You have 1 new memo.
MEMO_HAVE_NEW_MEMOS
	You have %d new memos.
MEMO_TYPE_READ_LAST
	Type /msg %s READ LAST to read it.
MEMO_TYPE_READ_NUM
	Type /msg %s READ %d to read it.
MEMO_TYPE_LIST_NEW
	Type /msg %s LIST NEW to list them.
MEMO_AT_LIMIT
	Warning: You have reached your maximum number of memos (%d).  You will be unable to receive any new memos until you delete some of your current ones.
MEMO_OVER_LIMIT
	Warning: You are over your maximum number of memos (%d).  You will be unable to receive any new memos until you delete some of your current ones.
MEMO_NEW_MEMO_ARRIVED
	You have a new memo from %s.
	Type /msg %s READ %d to read it.

# Multi-use responses
MEMO_HAVE_NO_MEMOS
	You have no memos.
MEMO_X_HAS_NO_MEMOS
	%s has no memos.
MEMO_DOES_NOT_EXIST
	Memo %d does not exist!
MEMO_LIST_NOT_FOUND
	No matching memos found.

# SEND responses
MEMO_SEND_SYNTAX
	SEND {nick | channel} memo-text
MEMO_SEND_DISABLED
	Sorry, memo sending is temporarily disabled.
MEMO_SEND_PLEASE_WAIT
	Please wait %d seconds before using the SEND command again.
MEMO_X_GETS_NO_MEMOS
	%s cannot receive memos.
MEMO_X_HAS_TOO_MANY_MEMOS
	%s currently has too many memos and cannot receive more.
MEMO_SENT
	Memo sent to %s.

# LIST responses
MEMO_LIST_SYNTAX
	LIST [channel] [list | NEW]
MEMO_HAVE_NO_NEW_MEMOS
	You have no new memos.
MEMO_X_HAS_NO_NEW_MEMOS
	%s has no new memos.
MEMO_LIST_MEMOS
	Memos for %s.  To read, type: /msg %s READ num
MEMO_LIST_NEW_MEMOS
	New memos for %s.  To read, type: /msg %s READ num
MEMO_LIST_CHAN_MEMOS
	Memos for %s.  To read, type: /msg %s READ %s num
MEMO_LIST_CHAN_NEW_MEMOS
	New memos for %s.  To read, type: /msg %s READ %s num
MEMO_LIST_HEADER
	 Num  Sender            Date/Time
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_READ_SYNTAX
	READ [channel] {list | LAST | NEW}
MEMO_HEADER
	Memo %d from %s (%s).  To delete, type: /msg %s DEL %d
MEMO_CHAN_HEADER
	Memo %d from %s (%s).  To delete, type: /msg %s DEL %s %d
MEMO_TEXT
	%s

# DEL responses
MEMO_DEL_SYNTAX
	DEL [channel] {num | list | ALL}
MEMO_DELETED_NONE
	No memos were deleted.
MEMO_DELETED_ONE
	Memo %d has been deleted.
MEMO_DELETED_SEVERAL
	%d memos have been deleted.
MEMO_DELETED_ALL
	All of your memos have been deleted.

# SET responses
MEMO_SET_SYNTAX
	SET option parameters
MEMO_SET_DISABLED
	Sorry, memo option setting is temporarily disabled.
MEMO_SET_UNKNOWN_OPTION
	Unknown SET option %s.

# SET NOTIFY responses
MEMO_SET_NOTIFY_SYNTAX
	SET NOTIFY {ON | LOGON | NEW | OFF}
MEMO_SET_NOTIFY_ON
	%s will now notify you of memos when you log on and when they are sent to you.
MEMO_SET_NOTIFY_LOGON
	%s will now notify you of memos when you log on or unset /AWAY.
MEMO_SET_NOTIFY_NEW
	%s will now notify you of memos when they are sent to you.
MEMO_SET_NOTIFY_OFF
	%s will not send you any notification of memos.

# SET LIMIT responses
MEMO_SET_LIMIT_SYNTAX
	SET LIMIT [channel] limit
MEMO_SET_LIMIT_SERVADMIN_SYNTAX
	SET LIMIT [nick | channel] {limit | NONE} [HARD]
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	You are not permitted to change your memo limit.
MEMO_SET_LIMIT_FORBIDDEN
	The memo limit for %s may not be changed.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	You cannot set your memo limit higher than %d.
MEMO_SET_LIMIT_TOO_HIGH
	You cannot set the memo limit for %s higher than %d.
MEMO_SET_LIMIT_OVERFLOW
	Memo limit too large; limiting to %d instead.
MEMO_SET_YOUR_LIMIT
	Your memo limit has been set to %d.
MEMO_SET_YOUR_LIMIT_ZERO
	You will no longer be able to receive memos.
MEMO_UNSET_YOUR_LIMIT
	Your memo limit has been disabled.
MEMO_SET_LIMIT
	Memo limit for %s set to %d.
MEMO_SET_LIMIT_ZERO
	Memo limit for %s set to 0.
MEMO_UNSET_LIMIT
	Memo limit disabled for %s.

# INFO responses
MEMO_INFO_SYNTAX
	INFO [channel]
MEMO_INFO_SERVADMIN_SYNTAX
	INFO [nick | channel]
MEMO_INFO_NO_MEMOS
	You currently have no memos.
MEMO_INFO_MEMO
	You currently have 1 memo.
MEMO_INFO_MEMO_UNREAD
	You currently have 1 memo, and it has not yet been read.
MEMO_INFO_MEMOS
	You currently have %d memos.
MEMO_INFO_MEMOS_ONE_UNREAD
	You currently have %d memos, of which 1 is unread.
MEMO_INFO_MEMOS_SOME_UNREAD
	You currently have %d memos, of which %d are unread.
MEMO_INFO_MEMOS_ALL_UNREAD
	You currently have %d memos; all of them are unread.
MEMO_INFO_LIMIT
	Your memo limit is %d.
MEMO_INFO_HARD_LIMIT
	Your memo limit is %d, and may not be changed.
MEMO_INFO_LIMIT_ZERO
	Your memo limit is 0; you will not receive any new memos.
MEMO_INFO_HARD_LIMIT_ZERO
	Your memo limit is 0; you will not receive any new memos.  You cannot change this limit.
MEMO_INFO_NO_LIMIT
	You have no limit on the number of memos you may keep.
MEMO_INFO_NOTIFY_OFF
	You will not be notified of new memos.
MEMO_INFO_NOTIFY_ON
	You will be notified of new memos at logon and when they arrive.
MEMO_INFO_NOTIFY_RECEIVE
	You will be notified when new memos arrive.
MEMO_INFO_NOTIFY_SIGNON
	You will be notified of new memos when you log on to IRC.
MEMO_INFO_X_NO_MEMOS
	%s currently has no memos.
MEMO_INFO_X_MEMO
	%s currently has 1 memo.
MEMO_INFO_X_MEMO_UNREAD
	%s currently has 1 memo, and it has not yet been read.
MEMO_INFO_X_MEMOS
	%s currently has %d memos.
MEMO_INFO_X_MEMOS_ONE_UNREAD
	%s currently has %d memos, of which 1 is unread.
MEMO_INFO_X_MEMOS_SOME_UNREAD
	%s currently has %d memos, of which %d are unread.
MEMO_INFO_X_MEMOS_ALL_UNREAD
	%s currently has %d memos; all of them are unread.
MEMO_INFO_X_LIMIT
	%s's memo limit is %d.
MEMO_INFO_X_HARD_LIMIT
	%s's memo limit is %d, and may not be changed.
MEMO_INFO_X_NO_LIMIT
	%s has no memo limit.
MEMO_INFO_X_NOTIFY_OFF
	%s is not notified of new memos.
MEMO_INFO_X_NOTIFY_ON
	%s is notified of new memos at logon and when they arrive.
MEMO_INFO_X_NOTIFY_RECEIVE
	%s is notified when new memos arrive.
MEMO_INFO_X_NOTIFY_SIGNON
	%s is notified of new memos at logon.

###########################################################################
#
# OperServ messages
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	Services is unable to change modes.  Are your servers configured correctly?
OPER_BOUNCY_MODES_U_LINE
	Services is unable to change modes.  Are your servers' U:lines configured correctly?
OPER_SKELETON_MODE
	This function is unavailable in skeleton mode.

# GLOBAL responses
OPER_GLOBAL_SYNTAX
	GLOBAL message

# STATS responses
OPER_STATS_UNKNOWN_OPTION
	Unknown STATS option %s.
OPER_STATS_RESET_USER_COUNT
	The maximum user count has been reset.
OPER_STATS_CURRENT_USERS
	Current users: %d (%d ops)
OPER_STATS_MAX_USERS
	Maximum users: %d (%s)
OPER_STATS_UPTIME_DHMS
	Services up %d %s, %02d:%02d
# If >= 1 hour, hours and minutes; if < 1 hour, minutes and seconds
OPER_STATS_UPTIME_HM_MS
	Services up %d %s, %d %s
OPER_STATS_BYTES_READ
	Bytes read: %5d kB
OPER_STATS_BYTES_WRITTEN
	Bytes sent: %5d kB
OPER_STATS_USER_MEM
	User    : %6d records, %5d kB
OPER_STATS_SERVER_MEM
	Server  : %6d records, %5d kB
OPER_STATS_CHANNEL_MEM
	Channel : %6d records, %5d kB
OPER_STATS_NICKSERV_MEM
	NickServ: %6d records, %5d kB
OPER_STATS_CHANSERV_MEM
	ChanServ: %6d records, %5d kB
OPER_STATS_MEMOSERV_MEM
	MemoServ: %6d records, %5d kB
OPER_STATS_STATSERV_MEM
	StatServ: %6d records, %5d kB
OPER_STATS_OPERSERV_MEM
	OperServ: %6d records, %5d kB
OPER_STATS_AKILL_COUNT
	Current number of AKILLs: %d
OPER_STATS_AKILL_EXPIRE_DAYS
	Default AKILL expiry time: %d days
OPER_STATS_AKILL_EXPIRE_DAY
	Default AKILL expiry time: 1 day
OPER_STATS_AKILL_EXPIRE_HOURS
	Default AKILL expiry time: %d hours
OPER_STATS_AKILL_EXPIRE_HOUR
	Default AKILL expiry time: 1 hour
OPER_STATS_AKILL_EXPIRE_MINS
	Default AKILL expiry time: %d minutes
OPER_STATS_AKILL_EXPIRE_MIN
	Default AKILL expiry time: 1 minute
OPER_STATS_AKILL_EXPIRE_NONE
	Default AKILL expiry time: No expiration
OPER_STATS_SESSIONS_MEM
	Sessions: %6d records, %5d kB

# MODE responses
OPER_MODE_SYNTAX
	MODE channel modes

# CLEARMODES responses
OPER_CLEARMODES_SYNTAX
	CLEARMODES channel [ALL]
OPER_CLEARMODES_DONE
	Binary modes and bans cleared from channel %s.
OPER_CLEARMODES_ALL_DONE
	All modes cleared from channel %s.

# CLEARCHAN responses
OPER_CLEARCHAN_SYNTAX
	CLEARCHAN channel
OPER_CLEARCHAN_DONE
	All users removed from channel %s.

# KICK responses
OPER_KICK_SYNTAX
	KICK channel user reason

# ADMIN responses
OPER_ADMIN_SYNTAX
	ADMIN {ADD | DEL | LIST} [nick]
OPER_ADMIN_ADD_SYNTAX
	ADMIN ADD nick
OPER_ADMIN_DEL_SYNTAX
	ADMIN DEL nick
OPER_ADMIN_SKELETON
	Services is in skeleton mode; the ADMIN command is unavailable.
OPER_ADMIN_EXISTS
	%s already exists on Services admin list.
OPER_ADMIN_ADDED
	%s added to Services admin list.
OPER_ADMIN_TOO_MANY
	Too many entries (%d) on Services admin list; cannot add more.
OPER_ADMIN_REMOVED
	%s removed from Services admin list.
OPER_ADMIN_NOT_FOUND
	%s not found on Services admin list.
OPER_ADMIN_LIST_HEADER
	Services admin list:

# OPER responses
OPER_OPER_SYNTAX
	OPER {ADD | DEL | LIST} [nick]
OPER_OPER_ADD_SYNTAX
	OPER ADD nick
OPER_OPER_DEL_SYNTAX
	OPER DEL nick
OPER_OPER_SKELETON
	Services is in skeleton mode; the OPER command is unavailable.
OPER_OPER_EXISTS
	%s already exists on Services operator list.
OPER_OPER_ADDED
	%s added to Services operator list.
OPER_OPER_TOO_MANY
	Too many entries (%d) on Services operator list; cannot add more.
OPER_OPER_REMOVED
	%s removed from Services operator list.
OPER_OPER_NOT_FOUND
	%s not found on Services operator list.
OPER_OPER_LIST_HEADER
	Services operator list:

# AKILL responses
OPER_AKILL_SYNTAX
	AKILL {ADD | DEL | LIST | VIEW | COUNT} [[+expiry] mask [reason]]
OPER_AKILL_ADD_SYNTAX
	AKILL ADD [+expiry] mask reason
OPER_AKILL_DEL_SYNTAX
	AKILL DEL mask
OPER_TOO_MANY_AKILLS
	AKILL list is full!
OPER_AKILL_EXISTS
	%s already exists on AKILL list.
OPER_AKILL_NO_NICK
	Notice: AKILL masks cannot contain nicknames; make sure you have not included a nick portion in your mask.
OPER_AKILL_MASK_TOO_GENERAL
	The AKILL mask is too general.
OPER_AKILL_ADDED
	%s added to AKILL list.
OPER_AKILL_REMOVED
	%s removed from AKILL list.
OPER_AKILL_NOT_FOUND
	%s not found on AKILL list.
OPER_AKILL_LIST_HEADER
	Current AKILL list:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, reason
OPER_AKILL_VIEW_FORMAT
	%s (by %s on %s; %s)
	    %s
OPER_AKILL_COUNT
	There are %d host masks on the AKILL list.

# SU responses
OPER_SU_SYNTAX
	SU password
OPER_SU_NO_PASSWORD
	The SU command is unavailable because no super-user password has been set.
OPER_SU_SUCCEEDED
	You now have Services super-user privileges.
OPER_SU_FAILED
	Unable to verify password.

# SET responses
OPER_SET_SYNTAX
	SET option setting
OPER_SET_IGNORE_ON
	Ignore code will be used.
OPER_SET_IGNORE_OFF
	Ignore code will not be used.
OPER_SET_IGNORE_ERROR
	Setting for IGNORE must be ON or OFF.
OPER_SET_READONLY_ON
	Services is now in read-only mode.
OPER_SET_READONLY_OFF
	Services is now in read-write mode.
OPER_SET_READONLY_ERROR
	Setting for READONLY must be ON or OFF.
OPER_SET_DEBUG_ON
	Services is now in debug mode.
OPER_SET_DEBUG_OFF
	Services is now in non-debug mode.
OPER_SET_DEBUG_LEVEL
	Services is now in debug mode (level %d).
OPER_SET_DEBUG_ERROR
	Setting for DEBUG must be ON, OFF, or a positive number.
OPER_SET_SUPASS_FAILED
	Unable to set Services super-user password.
OPER_SET_SUPASS_OK
	Services super-user password has been changed.
OPER_SET_SUPASS_NONE
	Services super-user password has been disabled.
OPER_SET_UNKNOWN_OPTION
	Unknown option %s.

# JUPE responses
OPER_JUPE_SYNTAX
	JUPE servername [reason]

# RAW responses
OPER_RAW_SYNTAX
	RAW text

# UPDATE responses
OPER_UPDATING
	Updating databases.

# LISTIGNORE responses
OPER_IGNORE_LIST
	Services ignore list:
OPER_IGNORE_LIST_EMPTY
	Ignore list is empty.

# KILLCLONES responses
OPER_KILLCLONES_SYNTAX
	KILLCLONES nick
OPER_KILLCLONES_UNKNOWN_NICK
	Could not find user %s.

###########################################################################
#
# Session Limiting and Exception messages
#
###########################################################################

# EXCEPTION responses
OPER_EXCEPTION_SYNTAX
	EXCEPTION {ADD | DEL | MOVE | LIST | VIEW} [params]
OPER_EXCEPTION_ADD_SYNTAX
	EXCEPTION ADD [+expiry] mask limit reason
OPER_EXCEPTION_DEL_SYNTAX
	EXCEPTION DEL {mask | list}
OPER_EXCEPTION_MOVE_SYNTAX
	EXCEPTION MOVE num newnum
OPER_EXCEPTION_DISABLED
	Session limiting is disabled.
OPER_EXCEPTION_ALREADY_PRESENT
	Mask %s already present on exception list.
OPER_EXCEPTION_TOO_MANY
	Session-limit exception list is full!
OPER_EXCEPTION_ADDED
	Session limit for %s set to %d.
OPER_EXCEPTION_MOVED
	Exception for %s (#%d) moved to number %d.
OPER_EXCEPTION_NO_SUCH_ENTRY
	No such entry (#%d) session-limit exception list.
OPER_EXCEPTION_NOT_FOUND
	%s not found on session-limit exception list.
OPER_EXCEPTION_NO_MATCH
	No matching entries on session-limit exception list.
OPER_EXCEPTION_DELETED
	%s deleted from session-limit exception list.
OPER_EXCEPTION_DELETED_ONE
	Deleted 1 entry from session-limit exception list.
OPER_EXCEPTION_DELETED_SEVERAL
	Deleted %d entries from session-limit exception list.
OPER_EXCEPTION_LIST_HEADER
	Current session-limit exception list:
# mask, limit
OPER_EXCEPTION_LIST_FORMAT
	%3d  %4d   %s
OPER_EXCEPTION_LIST_COLHEAD
	Num  Limit  Host
# mask, set-by, set-time, expires, limit, reason
OPER_EXCEPTION_VIEW_FORMAT
	%3d.  %s  (by %s on %s; %s)
	    Limit: %-4d  - %s
OPER_EXCEPTION_INVALID_LIMIT
	Invalid session limit; limit must be at least zero and no greater than %d.
OPER_EXCEPTION_INVALID_HOSTMASK
	Invalid hostmask. Only real hostmasks are valid as exceptions are not matched against nicks or usernames.

# SESSION responses
OPER_SESSION_SYNTAX
	SESSION {LIST limit | VIEW host}
OPER_SESSION_LIST_SYNTAX
	SESSION LIST limit
OPER_SESSION_VIEW_SYNTAX
	SESSION VIEW host
OPER_SESSION_DISABLED
	Session limiting is disabled.
OPER_SESSION_INVALID_THRESHOLD
	Invalid threshold value; threshold must be an integer greater than 1.
OPER_SESSION_NOT_FOUND
	%s not found on session list.
OPER_SESSION_LIST_HEADER
	Hosts with at least %d sessions:
OPER_SESSION_LIST_COLHEAD
	Sessions  Host
# limit, host
OPER_SESSION_LIST_FORMAT
	%6d    %s
# host, sessions, limit
OPER_SESSION_VIEW_FORMAT
	The host %s currently has %d sessions with a limit of %d.

###########################################################################
#
# StatServ messages
#
############################################################################

# General SERVERS responses
STAT_SERVERS_REMOVE_SERV_FIRST
	Server %s is online. Remove it from the the network and try again.
STAT_SERVERS_SERVER_EXISTS
	Server %s already exists.

# SERVERS command syntax
STAT_SERVERS_SYNTAX
	SERVERS option parameters

# STATS responses
STAT_SERVERS_STATS_TOTAL
	Total Servers: %2d
STAT_SERVERS_STATS_ON_OFFLINE
	       Online: %2d (%d%%)  Offline: %2d (%d%%)
STAT_SERVERS_LASTQUIT_WAS
	    Last Quit: %-30s  %s

# LIST responses
STAT_SERVERS_LIST_HEADER
	Server Name                    Users      Opers
STAT_SERVERS_LIST_RESULTS
	End of list -- %d/%d online servers shown.

# VIEW responses
STAT_SERVERS_VIEW_HEADER_ONLINE
	%-30s  (online)
STAT_SERVERS_VIEW_HEADER_OFFLINE
	%-30s  (offline)
STAT_SERVERS_VIEW_LASTJOIN
	    Last join: %s
STAT_SERVERS_VIEW_LASTQUIT
	    Last quit: %s
STAT_SERVERS_VIEW_QUITMSG
	 Quit message: %s
STAT_SERVERS_VIEW_USERS_OPERS
	        Users: %3d (%2d%%)  Opers: %3d (%2d%%)
STAT_SERVERS_VIEW_RESULTS
	End of list -- %d/%d servers shown.

# DELETE responses
STAT_SERVERS_DELETE_SYNTAX
	SERVERS DELETE server
STAT_SERVERS_DELETE_DONE
	Statistics for server %s have been deleted.

# COPY responses
STAT_SERVERS_COPY_SYNTAX
	SERVERS COPY server newname
STAT_SERVERS_COPY_DONE
	Statistics for server %s copied to %s

# RENAME responses
STAT_SERVERS_RENAME_SYNTAX
	SERVERS RENAME server newname
STAT_SERVERS_RENAME_DONE
	Statistics for server %s renamed to %s

# USERS command syntax
STAT_USERS_SYNTAX
	USERS option parameters

###########################################################################
#
# News system messages
#
###########################################################################

NEWS_LOGON_TEXT
	[Logon News - %s] %s
NEWS_OPER_TEXT
	[Oper News - %s] %s

NEWS_LOGON_SYNTAX
	LOGONNEWS {ADD|DEL|LIST} [text|num]
NEWS_LOGON_LIST_HEADER
	Logon news items:
NEWS_LOGON_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_LOGON_LIST_NONE
	There is no logon news.
NEWS_LOGON_ADD_SYNTAX
	LOGONNEWS ADD text
NEWS_LOGON_ADD_FULL
	News list is full!
NEWS_LOGON_ADDED
	Added new logon news item (#%d).
NEWS_LOGON_DEL_SYNTAX
	LOGONNEWS DEL {num | ALL}
NEWS_LOGON_DEL_NOT_FOUND
	Logon news item #%d not found!
NEWS_LOGON_DELETED
	Logon news item #%d deleted.
NEWS_LOGON_DEL_NONE
	No logon news items to delete!
NEWS_LOGON_DELETED_ALL
	All logon news items deleted.

NEWS_OPER_SYNTAX
	OPERNEWS {ADD|DEL|LIST} [text|num]
NEWS_OPER_LIST_HEADER
	Oper news items:
NEWS_OPER_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_OPER_LIST_NONE
	There is no oper news.
NEWS_OPER_ADD_SYNTAX
	OPERNEWS ADD text
NEWS_OPER_ADD_FULL
	News list is full!
NEWS_OPER_ADDED
	Added new oper news item (#%d).
NEWS_OPER_DEL_SYNTAX
	OPERNEWS DEL {num | ALL}
NEWS_OPER_DEL_NOT_FOUND
	Oper news item #%d not found!
NEWS_OPER_DELETED
	Oper news item #%d deleted.
NEWS_OPER_DEL_NONE
	No oper news items to delete!
NEWS_OPER_DELETED_ALL
	All oper news items deleted.

NEWS_HELP_LOGON
	Syntax: LOGONNEWS ADD text
	        LOGONNEWS DEL {num | ALL}
	        LOGONNEWS LIST
	
	Edits or displays the list of logon news messages.  When a
	user connects to the network, these messages will be sent
	to them.  (However, no more than three messages will be
	sent in order to avoid flooding the user.  If there are
	more than three news messages, only the three most recent
	will be sent.)
	
	LOGONNEWS LIST may be used by any IRC operator to list the
	current news messages.  ADD and DEL may only be used by
	Services admins.

NEWS_HELP_OPER
	Syntax: OPERNEWS ADD text
	        OPERNEWS DEL {num | ALL}
	        OPERNEWS LIST
	
	Edits or displays the list of oper news messages.  When a
	user opers up (with the /OPER command), these messages will
	be sent to them.  (However, no more than three messages will
	be sent in order to avoid flooding the user.  If there are
	more than three news messages, only the three most recent
	will be sent.)
	
	OPERNEWS LIST may be used by any IRC operator to list the
	current oper news messages.  ADD and DEL may only be used by
	Services admins.

###########################################################################
#
# NickServ help messages
#
###########################################################################

NICK_HELP
	%S allows you to "register" a nickname and
	prevent others from using it.  If the nick is not used for
	%d days, the registration will expire.  The following
	commands allow for registration and maintenance of
	nicknames; to use them, type /msg %S command.
	For more information on a specific command, type
	/msg %S HELP command.
	
	    REGISTER   Register a nickname
	    IDENTIFY   Identify yourself with your password
	    ACCESS     Modify the list of authorized addresses
	    LINK       Make your nick an alias for another
	    SET        Set options, including kill protection
	    DROP       Cancel the registration of a nickname
	    RECOVER    Kill another user who has taken your nick
	    RELEASE    Regain custody of your nick after RECOVER
	
	Other commands: UNLINK, UNSET, GHOST, INFO, LIST, LISTCHANS,
	                STATUS
	
	NOTICE: This service is intended to provide a way for
	IRC users to ensure their identity is not compromised.
	It is NOT intended to facilitate "stealing" of
	nicknames or other malicious actions.  Abuse of %S
	will result in, at minimum, loss of the abused
	nickname(s).

NICK_HELP_EXPIRE_ZERO
	%S allows you to "register" a nickname and
	prevent others from using it.  The following commands allow
	for registration and maintenance of nicknames; to use them,
	type /msg %S command. For more information on a
	specific command, type /msg %S HELP command.
	
	    REGISTER   Register a nickname
	    IDENTIFY   Identify yourself with your password
	    ACCESS     Modify the list of authorized addresses
	    LINK       Make your nick an alias for another
	    SET        Set options, including kill protection
	    DROP       Cancel the registration of a nickname
	    RECOVER    Kill another user who has taken your nick
	    RELEASE    Regain custody of your nick after RECOVER
	
	Other commands: UNLINK, UNSET, GHOST, INFO, LIST, LISTCHANS,
	                STATUS
	
	NOTICE: This service is intended to provide a way for
	IRC users to ensure their identity is not compromised.
	It is NOT intended to facilitate "stealing" of
	nicknames or other malicious actions.  Abuse of %S
	will result in, at minimum, loss of the abused
	nickname(s).

NICK_HELP_REGISTER
	Syntax: REGISTER password [email]
	
	Registers your nickname in the %S database.  Once
	your nick is registered, you can use the SET and ACCESS
	commands to configure your nick's settings as you like
	them.  Make sure you remember the password you use when
	registering - you'll need it to make changes to your nick
	later.  (Note that case matters!  FIDO, Fido, and fido
	are all different passwords!)
	
	You may include an E-mail address when registering your
	nickname; you may also set one later using the SET EMAIL
	command.
	
	Guidelines on choosing passwords:
	
	Passwords should not be easily guessable.  For example,
	using your real name as a password is a bad idea.  Using
	your nickname as a password is a much worse idea ;) and,
	in fact, %S will not allow it.  Also, short
	passwords are vulnerable to trial-and-error searches, so
	you should choose a password at least 5 characters long.
	Finally, the space character cannot be used in passwords.

NICK_HELP_REGISTER_REQ_EMAIL
	Syntax: REGISTER password email
	
	Registers your nickname in the %S database.  Once
	your nick is registered, you can use the SET and ACCESS
	commands to configure your nick's settings as you like
	them.  Make sure you remember the password you use when
	registering - you'll need it to make changes to your nick
	later.  (Note that case matters!  FIDO, Fido, and fido
	are all different passwords!)
	
	You must include an E-mail address when registering your
	nickname.  You can prevent your E-mail address from being
	shown to other users with the SET HIDE command (type
	/msg %S HELP SET HIDE for more information).
	
	Guidelines on choosing passwords:
	
	Passwords should not be easily guessable.  For example,
	using your real name as a password is a bad idea.  Using
	your nickname as a password is a much worse idea ;) and,
	in fact, %S will not allow it.  Also, short
	passwords are vulnerable to trial-and-error searches, so
	you should choose a password at least 5 characters long.
	Finally, the space character cannot be used in passwords.

NICK_HELP_IDENTIFY
	Syntax: IDENTIFY password
	
	Tells %S that you are really the owner of this
	nick.  Many commands require you to authenticate yourself
	with this command before you use them.  The password
	should be the same one you sent with the REGISTER
	command.

NICK_HELP_DROP
	Syntax: DROP
	
	Drops your nickname from the %S database.  A nick
	that has been dropped is free for anyone to re-register.
	
	In order to use this command, you must first identify
	with your password (/msg %S HELP IDENTIFY for more
	information).

NICK_HELP_ACCESS
	Syntax: ACCESS ADD mask
	        ACCESS DEL mask
	        ACCESS LIST
	
	Modifies or displays the access list for your nick.  This
	is the list of addresses which will be automatically
	recognized by %S as allowed to use the nick.  If
	you want to use the nick from a different address, you
	need to send an IDENTIFY command to make %S
	recognize you.
	
	Examples:
	
	    ACCESS ADD achurch@*.dragonfire.net
	        Allows access to user achurch from any machine in
	        the dragonfire.net domain.
	
	    ACCESS DEL achurch@*.dragonfire.net
	        Reverses the previous command.
	
	    ACCESS LIST
	        Displays the current access list.

NICK_HELP_LINK
	Syntax: LINK nick password
	
	Links your nickname to another, effectively making the nick
	you are currently using an alias for the given nick.  When
	you give this command, the access list for the nick you are
	using is deleted and replaced by that of the nick you are
	linking to; all memos for your current nick are added to
	the list of memos for the target nick (this may cause the
	nick to exceed its limit of memos, in which case you will
	need to delete some before you can receive more for either
	nick).
	
	Once the link has been established, your nick will be
	transparently converted into the target nick everywhere in
	Services, except for the %S UNLINK and DROP commands.  For
	example, you can use either nick to read the same set of
	memos (and memos sent to either nick will go into the same
	list).  If either nick is on a channel's access list, then
	both nicks will get the same access privileges.  However,
	the nicks will expire independently; if you only use one of
	a set of linked nicks, all the rest will expire.
	
	In order to use this command, you must identify for your
	current nick (using the IDENTIFY command), and you must
	supply the password for the nick you wish to link to.

NICK_HELP_UNLINK
	Syntax: UNLINK [nick pass]
	
	Removes a link from your nick to another.  When the link is
	removed, the nickname flags and access list of the
	previously linked nick are copied to your current nick and
	can then be independently changed.  Memos are not copied;
	all memos will remain stored with the previously linked
	nick.
	
	By giving a nickname and password as parameters, you can
	unlink a nick besides the one you are currently using.

NICK_HELP_SET
	Syntax: SET option parameters
	
	Sets various nickname options.  option can be one of:
	
	    PASSWORD   Set your nickname password
	    LANGUAGE   Set the language Services will use when
	                   sending messages to you
	    URL        Associate a URL with your nickname
	    EMAIL      Associate an E-mail address with your nickname
	    KILL       Turn kill protection on or off
	    SECURE     Turn nickname security on or off
	    PRIVATE    Prevent your nickname from appearing in a
	                   /msg %S LIST
	    HIDE       Hide certain pieces of nickname information
	
	In order to use this command, you must first identify
	with your password (/msg %S HELP IDENTIFY for more
	information).
	
	Type /msg %S HELP SET option for more information
	on a specific option.

NICK_HELP_SET_PASSWORD
	Syntax: SET PASSWORD new-password
	
	Changes the password used to identify you as the nick's
	owner.

NICK_HELP_SET_LANGUAGE
	Syntax: SET LANGUAGE number
	
	Changes the language Services uses when sending messages to
	you (for example, when responding to a command you send).
	number should be chosen from the following list of
	supported languages:
	

NICK_HELP_SET_URL
	Syntax: SET URL url
	
	Associates the given URL with your nickname.  This URL
	will be displayed whenever someone requests information
	on your nick with the INFO command.

NICK_HELP_SET_EMAIL
	Syntax: SET EMAIL address
	
	Associates the given E-mail address with your nickname.
	This address will be displayed whenever someone requests
	information on the channel with the INFO command.

NICK_HELP_SET_KILL
	Syntax: SET KILL {ON | QUICK | IMMED | OFF}
	
	Turns the automatic kill protection option for your nick
	on or off.  With kill protection on, if another user
	tries to take your nick, they will be given one minute to
	change to another nick, after which they will be forcibly
	removed from IRC by %S.
	
	If you select QUICK, the user will be given only 20 seconds
	to change nicks instead of the usual 60.  If you select
	IMMED, the user will be killed immediately without being
	warned first or given a chance to change their nick; please
	do not use this option unless necessary.  Also, your
	network's administrators may have disabled this option.

NICK_HELP_SET_SECURE
	Syntax: SET SECURE {ON | OFF}
	
	Turns %S's security features on or off for your
	nick.  With SECURE set, you must enter your password
	before you will be recognized as the owner of the nick,
	regardless of whether your address is on the access
	list.  However, if you are on the access list, %S
	will not auto-kill you regardless of the setting of the
	KILL option.

NICK_HELP_SET_PRIVATE
	Syntax: SET PRIVATE {ON | OFF}
	
	Turns %S's privacy option on or off for your nick.
	With PRIVATE set, your nickname will not appear in
	nickname lists generated with %S's LIST command.
	(However, anyone who knows your nickname can still get
	information on it using the INFO command.)

NICK_HELP_SET_HIDE
	Syntax: SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	
	Allows you to prevent certain pieces of information from
	being displayed when someone does a %S INFO on your
	nick.  You can hide your E-mail address (EMAIL), last seen
	user@host mask (USERMASK), and last quit message (QUIT).
	The second parameter specifies whether the information should
	be displayed (OFF) or hidden (ON).

NICK_HELP_UNSET
	Syntax: UNSET {URL | EMAIL}
	
	Allows you to clear the URL or E-mail address associated
	with your nickname.  Use the URL parameter to clear the
	URL, or the EMAIL parameter to clear the E-mail address.
	You cannot clear both at the same time.

NICK_HELP_UNSET_REQ_EMAIL
	Syntax: UNSET URL
	
	Allows you to clear the URL associated with your
	nickname.  The URL parameter must be given.

NICK_HELP_RECOVER
	Syntax: RECOVER nickname [password]
	
	Allows you to recover your nickname if someone else has
	taken it; this does the same thing that %S does
	automatically if someone tries to use a kill-protected
	nick.
	
	When you give this command, %S will bring a fake
	user online with the same nickname as the user you're
	trying to recover your nick from.  This causes the IRC
	servers to disconnect the other user.  This fake user will
	will remain online for one minute to ensure that the other
	user does not immediately reconnect; after that minute, you
	can reclaim your nick.  Alternatively, use the RELEASE
	command (/msg %S HELP RELEASE) to get the nick
	back sooner.
	
	In order to use the RECOVER command for a nick, your
	current address as shown in /WHOIS must be on that nick's
	access list, or you must supply the correct password for
	the nickname.

NICK_HELP_RELEASE
	Syntax: RELEASE nickname [password]
	
	Instructs %S to remove any hold on your nickname
	caused by automatic kill protection or use of the RECOVER
	command.  By default, such holds last for one minute;
	this command gets rid of them sooner.
	
	In order to use the RELEASE command for a nick, your
	current address as shown in /WHOIS must be on that nick's
	access list, or you must supply the correct password for
	the nickname.

NICK_HELP_GHOST
	Syntax: GHOST nickname [password]
	
	Terminates a "ghost" IRC session using your nick.  A
	"ghost" session is one which is not actually connected,
	but which the IRC server believes is still online for one
	reason or another.  Typically, this happens if your
	computer crashes or your Internet or modem connection
	goes down while you're on IRC.
	
	In order to use the GHOST command for a nick, your
	current address as shown in /WHOIS must be on that nick's
	access list, or you must supply the correct password for
	the nickname.

NICK_HELP_INFO
	Syntax: INFO nickname [ALL]
	
	Displays information about the given nickname, such as
	the nick's owner, last seen address and time, and nick
	options. If you are identified for the nick you're
	getting information for and ALL is specified, you will
	be shown all the information; regardless of whether
	it's hidden or not.

NICK_HELP_LISTCHANS
	Syntax: LISTCHANS
	
	Lists the names and the total number of channels you have
	registered under your nickname.

NICK_HELP_LIST
	Syntax: LIST pattern
	
	Lists all registered nicknames which match the given
	pattern, in nick!user@host format.  Nicks with the
	PRIVATE option set will not be displayed.
	
	Examples:
	
	    LIST *!joeuser@foo.com
	        Lists all nicks owned by joeuser@foo.com.
	
	    LIST *Bot*!*@*
	        Lists all registered nicks with Bot in their
	        names (case insensitive).
	
	    LIST *!*@*.bar.org
	        Lists all nicks owned by users in the bar.org
	        domain.

NICK_HELP_STATUS
	Syntax: STATUS nickname...
	
	Returns whether the user using the given nickname is
	recognized as the owner of the nickname.  The response has
	this format:
	
	    nickname status-code
	
	where nickname is the nickname sent with the command, and
	status-code is one of the following:
	
	    0 - no such user online or nickname not registered
	    1 - user not recognized as nickname's owner
	    2 - user recognized as owner via access list only
	    3 - user recognized as owner via password identification
	
	Up to sixteen nicknames may be sent with each command; the
	rest will be ignored.  No error message is generated if no
	nickname is given.

NICK_SERVADMIN_HELP
	
	The following commands are available to Services admins:
	
	    GETPASS     Retrieve the password for a nickname
	                    (only if encryption is disabled)
	    SUSPEND     Prevent a nick from being identified for
	    FORBID      Prevent a nick from being used/registered
	    LISTLINKS   Lists nicknames linked to a nickname
	
	Services admins can also use the following commands on any
	nickname without needing to identify for it:
	
	    DROP, SET, ACCESS LIST, INFO ALL

	See the help for each command for specific details.

NICK_SERVADMIN_HELP_DROP
	Syntax: DROP [nickname]
	
	Without a parameter, drops your nickname from the
	%S database.
	
	With a parameter, drops the named nick from the database.
	This use limited to Services admins.

NICK_SERVADMIN_HELP_SET
	
	Services admins can also set the option NOEXPIRE, with
	which nicknames can be prevented from expiring.
	Additionally, Services admins can set options for any
	nickname without entering a password, using the format
	SET nickname option parameters.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Syntax: SET [nickname] NOEXPIRE {ON | OFF}
	
	Sets whether the given nickname will expire.  Setting this
	to ON prevents the nickname from expiring.  If no
	nickname is given, sets the no-expire flag for your nick.
	
	Limited to Services admins.

NICK_SERVADMIN_HELP_UNSET
	
	Services admins may use the UNSET command on any nickname by
	including the nickname before the option name, as with the
	SET command.

NICK_SERVADMIN_HELP_UNLINK
	
	Services admins may unlink any nick without entering a
	password.

NICK_SERVADMIN_HELP_LISTLINKS
	Syntax: LISTLINKS nick [ALL]
	
	Lists nicks which are linked to the given nick.  If ALL is
	specified, lists all nicks with the same privileges as the
	given nick; otherwise, lists only those nicks which are
	directly linked to the given nick.
	
	Limited to Services admins.

NICK_SERVADMIN_HELP_ACCESS
	
	Services admins may give a nickname parameter to the LIST
	command to display the access list for any nickname.

NICK_SERVADMIN_HELP_INFO
	
	Services admins may use the ALL parameter with any nick.

NICK_SERVADMIN_HELP_LISTCHANS
	
	Services admins may list channels for any nickname by
	giving the nickname with the command (for example,
	/msg NickServ LISTCHANS OtherNick).

NICK_SERVADMIN_HELP_LIST
	Syntax: LIST pattern [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
	
	Lists all registered nicknames which match the given
	pattern, in nick!user@host format.  Nicks with the PRIVATE
	option set will only be displayed to Services admins. For
	Services admins, nicks with the NOEXPIRE option set will
	have a ! prepended to the nickname and those that are
	SUSPENDed will be prepended by a *.
	
	If the FORBIDDEN, SUSPENDED or NOEXPIRE options are given,
	only nicks which, respectively, are FORBIDden, SUSPENDed or
	have the NOEXPIRE flag set will be displayed. The options can
	be used in any order and in any combination. These options
	are limited to Services admins.
	
	Examples:
	
	    LIST *!joeuser@foo.com
	        Lists all registered nicks owned by joeuser@foo.com.
	
	    LIST *Bot*!*@*
	        Lists all registered nicks with Bot in their
	        names (case insensitive).
	
	    LIST * NOEXPIRE
	        Lists all registered nicks which have been set to
	        not expire.

NICK_SERVADMIN_HELP_GETPASS
	Syntax: GETPASS nickname
	
	Returns the password for the given nickname.  Note that
	whenever this command is used, a message including the
	person who issued the command and the nickname it was used
	on will be logged and sent out as a WALLOPS/GLOBOPS.
	
	Limited to Services admins.
	
	This command is unavailable when encryption is enabled.

NICK_SERVADMIN_HELP_FORBID
	Syntax: FORBID nickname
	
	Disallows a nickname from being registered or used by
	anyone.  May be cancelled by dropping the nick.
	
	Limited to Services admins.

NICK_SERVADMIN_HELP_SUSPEND
	Syntax: SUSPEND [+expiry] nickname reason
	
	Prevents a nickname, and all those nicknames with the
	same root nickname, from being used or identified for
	by anyone. A nickname can be unsuspended with the
	UNSUSPEND command.
	
	Unlike a forbidden nickname, a suspended one does not
	lose its information and will expire!
	
	Limited to Services admins.

NICK_SERVADMIN_HELP_UNSUSPEND
	Syntax: UNSUSPEND nickname
	
	Allows people to use and identify for a previously
	SUSPENDed nickname.
	
	Limited to Services admins.


###########################################################################
#
# ChanServ help messages
#
###########################################################################

CHAN_HELP
	%S allows you to register and control various
	aspects of channels.  %S can often prevent
	malicious users from "taking over" channels by limiting
	who is allowed channel operator privileges.  Available
	commands are listed below; to use them, type
	/msg %S command.  For more information on a
	specific command, type /msg %S HELP command.
	
	    REGISTER   Register a channel
	    IDENTIFY   Identify yourself with your password
	    DROP       Cancel the registration of a channel
	    INFO       Show channel options and information
	    SET        Set channel options and information
	    ACCESS     Maintain the overall channel access list
	    SOP        Maintain the SuperOp list
	    AOP        Maintain the AutoOp list
	    VOP        Maintain the AutoVoice list
	    AKICK      Maintain the AutoKick list

CHAN_HELP_OTHERS
	
	Other commands: UNSET, LIST, INVITE, UNBAN, CLEAR,
	                LEVELS, OP, DEOP, VOICE, DEVOICE

CHAN_HELP_OTHERS_HALFOP_CHANPROT
	
	Other commands: UNSET, LIST, INVITE, UNBAN, CLEAR,
	                LEVELS, OP, DEOP, VOICE, DEVOICE,
	                HALFOP, DEHALFOP, PROTECT, DEPROTECT,
	                HOP

CHAN_HELP_EXPIRES
	
	Note that any channel which is not used for %d days
	(i.e. which no user on the channel's access list enters
	for that period of time) will be automatically dropped.

CHAN_HELP_REGISTER
	Syntax: REGISTER channel password description
	
	Registers a channel in the %S database.  In order
	to use this command, you must first be a channel operator
	on the channel you're trying to register.  The password
	is used with the IDENTIFY command to allow you to
	make changes to the channel settings at a later time.
	The last parameter, which must be included, is a
	general description of the channel's purpose.
	
	When you register a channel, you are recorded as the
	"founder" of the channel.  The channel founder is allowed
	to change all of the channel settings for the channel;
	%S will also automatically give the founder
	channel-operator privileges when s/he enters the channel.
	See the ACCESS command (/msg %S HELP ACCESS) for
	information on giving a subset of these privileges to
	other channel users.
	
	NOTICE: In order to register a channel, you must have
	first registered your nickname.  If you haven't,
	/msg %s HELP for information on how to do so.

CHAN_HELP_IDENTIFY
	Syntax: IDENTIFY channel password
	
	Authenticates you to %S as the founder of the given
	channel.  Many commands require you to use this command
	before using them.  The password should be the same one
	you sent with the REGISTER command.

CHAN_HELP_DROP
	Syntax: DROP channel
	
	Unregisters the named channel.  Can only be used by
	channel founder, who must use the IDENTIFY command first.

CHAN_HELP_SET
	Syntax: SET channel option parameters
	
	Allows the channel founder to set various channel options
	and other information.  The founder must use the IDENTIFY
	command before using SET.
	
	Available options:
	
	    FOUNDER     Set the founder of a channel
	    SUCCESSOR   Set the successor for a channel
	    PASSWORD    Set the founder password
	    DESC        Set the channel description
	    URL         Associate a URL with the channel
	    EMAIL       Associate an E-mail address with the channel
	    ENTRYMSG    Set a message to be sent to users when they
	                   enter the channel
	    TOPIC       Change the topic on the channel
	    KEEPTOPIC   Retain topic when channel is not in use
	    TOPICLOCK   Topic can only be changed with SET TOPIC
	    MLOCK       Lock channel modes on or off
	    PRIVATE     Hide channel from LIST command
	    RESTRICTED  Restrict access to the channel
	    SECURE      Activate %S security features
	    SECUREOPS   Stricter control of chanop status
	    LEAVEOPS    Do not de-op users on channel entry
	    OPNOTICE    Send a notice when OP/DEOP commands are used
	    ENFORCE     Enforce auto-op, auto-voice status
	    FLOODSERV   Enable/Disable Channel Flood protection
	
	Type /msg %S HELP option for more information on a
	particular option.

CHAN_HELP_SET_FOUNDER
	Syntax: SET channel FOUNDER nick
	
	Changes the founder of a channel.  The new nickname must
	be a registered one.

CHAN_HELP_SET_SUCCESSOR
	Syntax: SET channel SUCCESSOR nick
	
	Changes the successor of a channel.  If the founder's
	nickname expires or is dropped while the channel is still
	registered, the successor will become the new founder of the
	channel.  However, if the successor already has too many
	channels registered (%d), the channel will be dropped
	instead, just as if no successor had been set.  The new
	nickname must be a registered one.

CHAN_HELP_SET_PASSWORD
	Syntax: SET channel PASSWORD password
	
	Sets the password used to identify as the founder of the
	channel.

CHAN_HELP_SET_DESC
	Syntax: SET channel DESC description
	
	Sets the description for the channel, which shows up with
	the LIST and INFO commands.

CHAN_HELP_SET_URL
	Syntax: SET channel URL url
	
	Associates the given URL with the channel.  This URL will
	be displayed whenever someone requests information on the
	channel with the INFO command.

CHAN_HELP_SET_EMAIL
	Syntax: SET channel EMAIL address
	
	Associates the given E-mail address with the channel.
	This address will be displayed whenever someone requests
	information on the channel with the INFO command.

CHAN_HELP_SET_ENTRYMSG
	Syntax: SET channel ENTRYMSG message
	
	Sets the message which will be sent via /notice to users
	when they enter the channel.

CHAN_HELP_SET_TOPIC
	Syntax: SET channel TOPIC topic
	
	Causes %S to set the channel topic to the one
	specified.  This command is most useful in conjunction
	with SET TOPICLOCK.

CHAN_HELP_SET_KEEPTOPIC
	Syntax: SET channel KEEPTOPIC {ON | OFF}
	
	Enables or disables the topic retention option for a
	channel.  When topic retention is set, the topic for the
	channel will be remembered by %S even after the
	last user leaves the channel, and will be restored the
	next time the channel is created.

CHAN_HELP_SET_TOPICLOCK
	Syntax: SET channel TOPICLOCK {ON | OFF}
	
	Enables or disables the topic lock option for a channel.
	When topic lock is set, %S will not allow the
	channel topic to be changed except via the SET TOPIC
	command.

CHAN_HELP_SET_MLOCK
	Syntax: SET channel MLOCK modes
	
	Sets the mode-lock parameter for the channel.  %S
	allows you to define certain channel modes to be always
	on (or off).  The modes that can be locked are i, k, l,
	m, n, p, s, and t; each of these modes can be locked on,
	locked off, or not locked.  The modes parameter is
	constructed exactly the same way as a /MODE command; that
	is, modes followed by a + are locked on, and modes
	followed by a - are locked off.
	
	Warning:  If you set a mode-locked key, as in the second
	example below, you should also set the RESTRICTED option for
	the channel (see HELP SET RESTRICTED), or anyone entering
	the channel when it is empty will be able to see the key!
	
	Examples:
	
	    SET #channel MLOCK +nt-iklps
	        Forces modes n and t on, and modes i, k, l, p, and
	        s off.  Mode m is left free to be either on or off.
	
	    SET #channel MLOCK +knst-ilmp my-key
	        Forces modes k, n, s, and t on, and modes i, l, m,
	        and p off.  Also forces the channel key to be
	        "my-key".
	
	    SET #channel MLOCK +
	        Removes the mode lock; all channel modes are free
	        to be either on or off.

CHAN_HELP_SET_PRIVATE
	Syntax: SET channel PRIVATE {ON | OFF}
	
	Enables or disables the private option for a channel.
	When private is set, a /msg %S LIST will not
	include the channel in any lists.

CHAN_HELP_SET_RESTRICTED
	Syntax: SET channel RESTRICTED {ON | OFF}
	
	Enables or disables the restricted access option for a
	channel.  When restricted access is set, users who would
	normally be disallowed from having channel operator
	privileges (users with negative access levels and, if
	secure ops is set, users not on the access list) will
	instead be kicked and banned from the channel.

CHAN_HELP_SET_SECURE
	Syntax: SET channel SECURE {ON | OFF}
	
	Enables or disables %S's security features for a
	channel. When SECURE is set, only users who have registered
	their nicknames with %s and IDENTIFY'd with their
	password will be given privileges on the channel as
	controlled by the access list.

CHAN_HELP_SET_SECUREOPS
	Syntax: SET channel SECUREOPS {ON | OFF}
	
	Enables or disables the secure ops option for a channel.
	When secure ops is set, users who are not on the userlist
	will not be allowed chanop status.

CHAN_HELP_SET_LEAVEOPS
	Syntax: SET channel LEAVEOPS {ON | OFF}
	
	Enables or disables the leave ops option for a channel.
	When leave ops is set, %S will leave server ops (+o for
	the first person in the channel) in place even if the user
	would not normally get auto-opped.  The SECUREOPS option
	and AUTODEOP access level will still be enforced.
	Notice:  This can allow users to "steal" ops during a
	netsplit.

CHAN_HELP_SET_OPNOTICE
	Syntax: SET channel OPNOTICE {ON | OFF}
	
	Enables or disables the op-notice option for a channel.
	When op-notice is set, %S will send a notice to the
	channel whenever the OP or DEOP commands are used for a user
	in the channel.

CHAN_HELP_SET_ENFORCE
	Syntax: SET channel ENFORCE {ON | OFF}
	
	Enables or disables the enforce option for a channel.
	When enforce is set, %S will enforce the auto-op and
	auto-voice levels for all users.  For example, if a user
	with auto-op privileges is deopped, %S will
	automatically op the user again, and %S will also
	not allow the DEOP command to be used on that user.

CHAN_HELP_UNSET
	Syntax: UNSET channel {SUCCESSOR | URL | EMAIL | ENTRYMSG}
	
	Clears the given setting for a channel.

CHAN_HELP_SOP
	Syntax: SOP channel ADD nick
	        SOP channel DEL nick
	        SOP channel LIST [mask | list]
	        SOP channel COUNT
	
CHAN_HELP_SOP_NOPROT
	Maintains the SuperOp (SOP) list for a channel.
	Users with SOP status are automatically opped (set
	mode +o) when they join the channel.
CHAN_HELP_SOP_PROT
	Maintains the SuperOp (SOP) list for a channel.
	Users with SOP status are automatically opped (set
	mode +o) and protected (mode +a) when they join the
	channel.
CHAN_HELP_SOP_END
	
	An SOP can modify the AOP and VOP lists. Only
	a channel's founder can modify the SOP list.
	
	The SOP LIST command displays the SOP list.  If
	a wildcard mask is given, only those entries matching the
	mask are displayed.  If a list of entry numbers is given,
	only those entries are shown; for example:
	
	   SOP #channel LIST 2-5,7-9
	      Lists SOP list entries numbered 2 through 5 and
	      7 through 9.
	
	The SOP COUNT command returns the number of entries
	there are on the SOP list.

CHAN_HELP_AOP
	Syntax: AOP channel ADD nick
	        AOP channel DEL nick
	        AOP channel LIST [mask | list]
	        AOP channel COUNT
	
	Maintains the AutoOp (AOP) list for a channel.
	Users with AOP status are automatically opped (set
	mode +o) when they join the channel.
	
	An AOP can modify the VOP list.
	
	The AOP LIST command displays the AOP list.  If
	a wildcard mask is given, only those entries matching the
	mask are displayed.  If a list of entry numbers is given,
	only those entries are shown; for example:
	
	   AOP #channel LIST 2-5,7-9
	      Lists AOP list entries numbered 2 through 5 and
	      7 through 9.
	
	The AOP COUNT command returns the number of entries
	there are on the AOP list.

CHAN_HELP_HOP
	Syntax: HOP channel ADD nick
	        HOP channel DEL nick
	        HOP channel LIST [mask | list]
	        HOP channel COUNT
	
	Maintains the HalfOp (HOP) list for a channel.
	Users with HOP status are automatically halfopped
	(set mode +h) when they join the channel.
	
	An HOP can modify the VOP list; SOPs and AOPs can
	modify the HOP list.
	
	The HOP LIST command displays the HOP list.  If
	a wildcard mask is given, only those entries matching the
	mask are displayed.  If a list of entry numbers is given,
	only those entries are shown; for example:
	
	   HOP #channel LIST 2-5,7-9
	      Lists HOP list entries numbered 2 through 5 and
	      7 through 9.
	
	The HOP COUNT command returns the number of entries
	there are on the HOP list.

CHAN_HELP_VOP
	Syntax: VOP channel ADD nick
	        VOP channel DEL nick
	        VOP channel LIST [mask | list]
	        VOP channel COUNT
	
	Maintains the VoiceOp (VOP) list for a channel.
	Users with VOP status are automatically voiced (set
	mode +v) when they join the channel.
	
	The VOP LIST command displays the VOP list.  If
	a wildcard mask is given, only those entries matching the
	mask are displayed.  If a list of entry numbers is given,
	only those entries are shown; for example:
	
	   VOP #channel LIST 2-5,7-9
	      Lists VOP list entries numbered 2 through 5 and
	      7 through 9.
	
	The VOP COUNT command returns the number of entries
	there are on the VOP list.

CHAN_HELP_ACCESS
	Syntax: ACCESS channel ADD nick level
	        ACCESS channel DEL {nick | entry-num | list}
	        ACCESS channel LIST [mask | list]
	        ACCESS channel COUNT
	
	Maintains the access list for a channel.  The access
	list specifies which users are allowed chanop status or
	access to %S commands on the channel.  Different
	user levels allow for access to different subsets of
	privileges; /msg %S HELP ACCESS LEVELS for more
	specific information.  Any nick not on the access list has
	a user level of 0.
	
	Note that the access list may also be manipulated with the
	SOP, AOP, and VOP commands, which correspond to
	levels of %d, %d, and %d respectively.
	
	The ACCESS ADD command adds the given nickname to the
	access list with the given user level; if the nick is
	already present on the list, its access level is changed to
	the level specified in the command.  The level specified
	must be less than that of the user giving the command, and
	if the nick is already on the access list, the current
	access level of that nick must be less than the access level
	of the user giving the command.
	
	The ACCESS DEL command removes the given nick from the
	access list.  If a list of entry numbers is given, those
	entries are deleted.  (See the example for LIST below.)
	
	The ACCESS LIST command displays the access list.  If
	a wildcard mask is given, only those entries matching the
	mask are displayed.  If a list of entry numbers is given,
	only those entries are shown; for example:

	   ACCESS #channel LIST 2-5,7-9
	      Lists access entries numbered 2 through 5 and
	      7 through 9.
	
	The ACCESS COUNT command returns the number of entries
	there are on the access list.

CHAN_HELP_ACCESS_LEVELS
	User access levels
	
	By default, the following access levels are defined:
	
	   Founder   Full access to %S functions; automatic
	                     opping upon entering channel.  Note
	                     that only one person may have founder
	                     status (it cannot be given using the
	                     ACCESS command).
	      %4d   Access to AKICK command; automatic opping.
	      %4d   Automatic opping.
	      %4d   Automatic voicing.
	         0   No special privileges; can be opped by other
	                     ops (unless SECUREOPS is set).
	        <0   May not be opped.
	
	These levels may be changed, or new ones added, using the
	LEVELS command; type /msg %S HELP LEVELS for
	information.

CHAN_HELP_AKICK
	Syntax: AKICK channel ADD mask [reason]
	        AKICK channel DEL mask
	        AKICK channel LIST [mask | list]
	        AKICK channel VIEW [mask | list]
	        AKICK channel ENFORCE
	        AKICK channel COUNT
	
	Maintains the AutoKick list for a channel.  If a user
	on the AutoKick list attempts to join the channel,
	%S will ban that user from the channel, then kick
	the user.
	
	The AKICK ADD command adds the given nick or usermask
	to the AutoKick list.  If a reason is given with
	the command, that reason will be used when the user is
	kicked; if not, the default reason is "You have been
	banned from the channel".
	
	The AKICK DEL command removes the given nick or mask
	from the AutoKick list.  It does not, however, remove any
	bans placed by an AutoKick; those must be removed
	manually.
	
	The AKICK LIST command displays the AutoKick list, or
	optionally only those AutoKick entries which match the
	given mask. AKICK VIEW simply shows more details.
	
	The AKICK ENFORCE command causes %S to enforce the
	current AKICK list by removing those users who match an
	AKICK mask.
	
	The AKICK COUNT command returns how many entries there
	are on the AutoKick list.

CHAN_HELP_LEVELS
	Syntax: LEVELS channel SET type level
	        LEVELS channel {DIS | DISABLE} type
	        LEVELS channel LIST
	        LEVELS channel RESET
	
	The LEVELS command allows fine control over the meaning of
	the numeric access levels used by the ACCESS command.  With
	this command, you can define the access level required for
	most of %S's functions.  (The SET FOUNDER and SET PASSWORD
	commands, as well as this command, are always restricted to
	the channel founder.)
	
	Caution:  This command is for advanced users only!  Changing
	level settings with this command may cause the SOP, AOP, and
	VOP commands to stop working correctly.
	
	LEVELS SET allows the access level for a function or group of
	functions to be changed.  LEVELS DISABLE (or DIS for short)
	disables an automatic feature or disallows access to a
	function by anyone other than the channel founder.
	LEVELS LIST shows the current levels for each function or
	group of functions.  LEVELS RESET resets the levels to the
	default levels of a newly-created channel (see
	HELP ACCESS LEVELS).
	
	For a list of the features and functions whose levels can be
	set, see HELP LEVELS DESC.

CHAN_HELP_LEVELS_DESC
	The following feature/function names are understood.  Note
	that the levels for AUTODEOP and NOJOIN are maximum levels,
	while all others are minimum levels.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Syntax: INFO channel [ALL]
	
	Lists information about the named registered channel,
	including its founder, time of registration, last time
	used, description, and mode lock, if any.  If you are
	identified as the founder of the channel you're getting
	information for and ALL is specified, the entry message
	and successor will also be displayed.

CHAN_HELP_LIST
	Syntax: LIST pattern
	
	Lists all registered channels matching the given pattern.
	(Channels with the PRIVATE option set are not listed.)

CHAN_HELP_OP
	Syntax: OP #channel nick
	
	Ops a selected nick on a channel.  By default, limited to
	those with level 5 access and above on the channel.

CHAN_HELP_DEOP
	Syntax: DEOP #channel nick
	
	Deops a selected nick on a channel.  By default, limited to
	those with level 5 access and above on the channel.

CHAN_HELP_VOICE
	Syntax: VOICE #channel nick
	
	Voices a selected nick on a channel.  By default, limited to
	those with level 3 access and above on the channel.

CHAN_HELP_DEVOICE
	Syntax: DEVOICE #channel nick
	
	Devoices a selected nick on a channel.  By default, limited
	to those with level 3 access and above on the channel.

CHAN_HELP_HALFOP
	Syntax: HALFOP #channel nick
	
	Gives halfop access to a selected nick on a channel.  By
	default, limited to those with level 4 access and above on
	the channel.

CHAN_HELP_DEHALFOP
	Syntax: DEHALFOP #channel nick
	
	Removes halfop access from a selected nick on a channel.
	By default, limited to those with level 4 access and above
	on the channel.

CHAN_HELP_PROTECT
	Syntax: PROTECT #channel nick
	
	Gives channel protection (mode +a) to a selected nick on a
	channel.  By default, limited to those with level 10 access
	and above on the channel.

CHAN_HELP_DEPROTECT
	Syntax: DEPROTECT #channel nick
	
	Removes channel protection (mode +a) from a selected nick
	on a channel.  By default, limited to those with level 10
	access and above on the channel.

CHAN_HELP_INVITE
	Syntax: INVITE channel
	
	Tells %S to invite you into the given channel.  By
	default, only works if your access level on that channel is
	at least 5.

CHAN_HELP_UNBAN
	Syntax: UNBAN channel
	
	Tells %S to remove all bans preventing you from
	entering the given channel.  By default, only works if your
	access level on that channel is at least 5.

CHAN_HELP_CLEAR
	Syntax: CLEAR channel what
	
	Tells %S to clear certain settings on a channel.  what
	can be any of the following:
	
	     MODES       Clears all modes on the channel except those
	                     set in the channel's mode lock.
	     BANS        Clears all bans on the channel.
CHAN_HELP_CLEAR_EXCEPTIONS
	     EXCEPTIONS  Clears all exceptions on the channel.
CHAN_HELP_CLEAR_MID
	     OPS         Removes channel-operator status (mode +o) from
	                     all users.
CHAN_HELP_CLEAR_HALFOPS
	     HALFOPS     Removes halfop status (mode +h) from all users.
CHAN_HELP_CLEAR_END
	     VOICES      Removes "voice" status (mode +v) from all users.
	     USERS       Removes (kicks) all users from the channel.
	
	By default, your access level on the channel must be at
	least 10 to use this command.

CHAN_SERVADMIN_HELP
	
	The following commands are available to Services admins:
	
	    GETPASS   Retrieve the founder password for a channel
	                  (only if encryption is disabled)
	    FORBID    Prevent a channel from being registered/used
	    SUSPEND   Prevent a registered channel from being used
	    STATUS    Returns the current access level of a user
	                  on a channel
	
	Services admins can also drop any channel without needing
	to identify via password, and may view the access, AKICK,
	and level setting lists for any channel.

CHAN_SERVADMIN_HELP_DROP
	Syntax: DROP channel
	
	Unregisters the named channel.  Only Services admins
	can drop a channel for which they have not identified.

CHAN_SERVADMIN_HELP_SET
	
	Services admins can also set the option NOEXPIRE, with
	which channels can be prevented from expiring.
	Additionally, Services admins can set options for any
	channel without identifying by password for the channel.

CHAN_SERVADMIN_HELP_UNSET
	
	As with the SET command, Services admins can clear settings
	for any channel without identifying for the channel.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Syntax: SET channel NOEXPIRE {ON | OFF}
	
	Sets whether the given channel will expire.  Setting this
	to ON prevents the channel from expiring.
	
	Limited to Services admins.

CHAN_SERVADMIN_HELP_INFO
	
	Services admins can use the ALL parameter with any channel.

CHAN_SERVADMIN_HELP_LIST
	Syntax: LIST pattern [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
	
	Lists all registered channels matching the given pattern.
	Channels with the PRIVATE option set will only be displayed
	to Services admins. Channels with the NOEXPIRE option set
	will have a ! prepended to the channel name for Services
	admins.
	
	If the FORBIDDEN, SUSPENDED or NOEXPIRE options are given,
	only channels which, respectively, are FORBIDden, SUSPENDed or
	have the NOEXPIRE flag set will be displayed. The options can
	be used in any order and in any combination. These options
	are limited to Services admins.

CHAN_SERVADMIN_HELP_GETPASS
	Syntax: GETPASS channel
	
	Returns the password for the given channel.  Note that
	whenever this command is used, a message including the
	person who issued the command and the channel it was used
	on will be logged and sent out as a WALLOPS/GLOBOPS.
	
	Limited to Services admins.

CHAN_SERVADMIN_HELP_FORBID
	Syntax: FORBID channel
	
	Disallows anyone from registering or using the given
	channel.  May be cancelled by dropping the channel.
	
	Limited to Services admins.

CHAN_SERVADMIN_HELP_SUSPEND
	Syntax: SUSPEND [+expiry] channel reason
	
	Prevents a channel from being used or identified for
	by anyone. A channel can be unsuspended with the
	UNSUSPEND command.
	
	Unlike a forbidden channel, a suspended one does not
	lose its information and will expire!
	
	Limited to Services admins.

CHAN_SERVADMIN_HELP_UNSUSPEND
	Syntax: UNSUSPEND channel
	
	Allows people to use and identify for a previously
	SUSPENDed channel.
	
	Limited to Services admins.

CHAN_SERVADMIN_HELP_STATUS
	Syntax: STATUS channel nickname
	
	Returns the current access level of the given nick on the
	given channel.  The reply is of the form:
	
	    STATUS channel nickname access-level
	
	If an error occurs, the reply will be in the form:
	
	    STATUS ERROR error-message
	
	Limited to Services admins.


###########################################################################
#
# MemoServ help messages
#
###########################################################################

MEMO_HELP
	%S is a utility allowing IRC users to send short
	messages to other IRC users, whether they are online at
	the time or not, or to channels(*).  Both the sender's
	nickname and the target nickname or channel must be
	registered in order to send a memo.
	
	%S's commands include:
	
	    SEND   Send a memo to a nick or channel
	    LIST   List your memos
	    READ   Read a memo or memos
	    DEL    Delete a memo or memos
	    SET    Set options related to memos
	    INFO   Display information related to memos
	
	Type /msg %S HELP command for help on any of the
	above commands.
	
	(*) By default, any user with at least level 10 access on a
	    channel can read that channel's memos.  This can be
	    changed with the %s LEVELS command.

MEMO_HELP_SEND
	Syntax: SEND {nick | channel} memo-text
	
	Sends the named nick or channel a memo containing
	memo-text.  When sending to a nickname, the recipient will
	receive a notice that he/she has a new memo.  The target
	nickname/channel must be registered.

MEMO_HELP_LIST
	Syntax: LIST [channel] [list | NEW]
	
	Lists any memos you currently have.  With NEW, lists only
	new (unread) memos.  Unread memos are marked with a "*"
	to the left of the memo number.  You can also specify a list
	of numbers, as in the example below:

	   LIST 2-5,7-9
	      Lists memos numbered 2 through 5 and 7 through 9.

MEMO_HELP_READ
	Syntax: READ [channel] {num | list | LAST | NEW}
	
	Sends you the text of the memos specified.  If LAST is
	given, sends you the memo you most recently received.  If
	NEW is given, sends you all of your new memos.  Otherwise,
	sends you memo number num.  You can also give a list of
	numbers, as in this example:
	
	   READ 2-5,7-9
	      Displays memos numbered 2 through 5 and 7 through 9.

MEMO_HELP_DEL
	Syntax: DEL [channel] {num | list | ALL}
	
	Deletes the specified memo or memos.  You can supply
	multiple memo numbers or ranges of numbers instead of a
	single number, as in the second example below.
	
	If ALL is given, deletes all of your memos.
	
	Examples:
	
	   DEL 1
	      Deletes your first memo.
	
	   DEL 2-5,7-9
	      Deletes memos numbered 2 through 5 and 7 through 9.

MEMO_HELP_SET
	Syntax: SET option parameters
	
	Sets various memo options.  option can be one of:
	
	    NOTIFY      Changes when you will be notified about
	                    new memos (only for nicknames)
	    LIMIT       Sets the maximum number of memos you can
	                    receive
	
	Type /msg %S HELP SET option for more information
	on a specific option.

MEMO_HELP_SET_NOTIFY
	Syntax: SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Changes when you will be notified about new memos:
	
	    ON      You will be notified of memos when you log on,
	               when you unset /AWAY, and when they are sent
	               to you.
	    LOGON   You will only be notified of memos when you log
	               on or when you unset /AWAY.
	    NEW     You will only be notified of memos when they
	               are sent to you.
	    OFF     You will not receive any notification of memos.
	
	ON is equivalent to LOGON and NEW combined.
	
	Note that if your nickname has the "secure" setting on, you
	will only be notified of new memos (for LOGON or ON) after
	you identify to %S.

MEMO_HELP_SET_LIMIT
	Syntax: SET LIMIT [channel] limit
	
	Sets the maximum number of memos you (or the given channel)
	are allowed to have. If you set this to 0, no one will be
	able to send any memos to you.  However, you cannot set
	this any higher than %d.

MEMO_HELP_INFO
	Syntax: INFO [channel]
	
	Displays information on the number of memos you have, how
	many of them are unread, how many total memos you can
	receive and when you are notified of new ones. With a
	parameter, displays the same information for the given
	channel.

MEMO_SERVADMIN_HELP_SET_LIMIT
	Syntax: SET LIMIT [user | channel] {limit | NONE} [HARD]
	
	Sets the maximum number of memos a user or channel is
	allowed to have.  Setting the limit to 0 prevents the user
	from receiving any memos; setting it to NONE allows the
	user to receive and keep as many memos as they want.  If
	you do not give a nickname or channel, your own limit is
	set.
	
	Adding HARD prevents the user from changing the limit.  Not
	adding HARD has the opposite effect, allowing the user to
	change the limit (even if a previous limit was set with
	HARD).
	
	This use of the SET LIMIT command is limited to Services
	admins.  Other users may only enter a limit for themselves
	or a channel on which they have such privileges, may not
	remove their limit, may not set a limit above %d, and may
	not set a hard limit.

MEMO_SERVADMIN_HELP_INFO
	Syntax: INFO [nick | channel]
	
	Without a parameter, displays information on the number of
	memos you have, how many of them are unread, how many
	total memos you can receive and when you are notified of
	new ones.
	
	With a channel parameter, displays the same information for
	the given channel.
	
	With a nickname parameter, displays the same information
	for the given nickname.  This use limited to Services
	admins.

###########################################################################
#
# OperServ help messages
#
###########################################################################

OPER_HELP
	%S commands:
	    GLOBAL      Send a message to all users
	    STATS       Show status of Services and network
	    OPER LIST   List all Services operators
	    ADMIN LIST  List all Services admins
	
	Commands available to Services operators and admins only:
	    MODE        Change a channel's modes
	    KICK        Kick a user from a channel
	    CLEARMODES  Removes certain modes from a channel
	    CLEARCHAN   Removes all users from a channel (masskick)
	    KILLCLONES  Kill all users that have a certain host
	    AKILL       Manipulate the AKILL list
	    SESSION     View the list of host sessions
	    EXCEPTION   Modify the session-limit exception list
	    LOGONNEWS   Define messages to be shown to users at logon
	    OPERNEWS    Define messages to be shown to users who oper
	
	Commands available to Services admins only:
	    ACONNECT    Modify the server autoconnect list
	    CLOSENET    Close the network (Used to prevent mass cloning.)
	    NAKILL      Manipulate the NICK AKILL list
	    OPER        Modify the Services operator list
	    JUPE        "Jupiter" a server
	    RAW         Send a raw string to the IRC server
	    SET         Set various global Services options
	    UPDATE      Force the Services databases to be
	                    updated on disk immediately
	    SHUTDOWN    Save databases and stop the Services
	    QUIT        Terminate Services without saving databases
	    RESTART     Save databases and restart Services
	    SU          Obtain Services super-user privileges
	
	Commands available to the Services super-user only:
	    ADMIN       Modify the Services admin list
	    NOOPER      Manipulate the NOOPER list
	    SNOOPER     Manipulate the SNOOPER list
	
	Notice: All commands sent to %S are logged!

OPER_HELP_GLOBAL
	Syntax: GLOBAL message
	
	Allows IRCops to send messages to all users on the network.
	The message will be sent from the nick %s.

OPER_HELP_STATS
	Syntax: STATS [RESET | AKILL | ALL]
	
	Without any option, shows the current number of users and
	IRCops online (excluding Services), the highest number of
	users online since Services was started, and the length of
	time Services has been running.
	
	With the RESET option, resets the maximum user count to
	the number of users currently online.
	
	With the AKILL option, displays the current size of the
	AKILL list and the current default expiry time.
	
	The ALL option is available only to Services admins, and
	displays information on Services' memory usage.  Using this
	option can freeze Services for a short period of time on
	large networks, so don't overuse it!
	
	UPTIME may be used as a synonym for STATS.

OPER_HELP_OPER
	Syntax: OPER ADD nick
	        OPER DEL nick
	        OPER LIST
	
	Allows Services admins to add or remove nicknames to or from
	the Services operator list.  A user whose nickname is on the
	Services operator list and who has identified to %s
	will be able to access Services operator commands.
	
	Any IRC operator may use the OPER LIST form of the command.
	All other use limited to Services admins.

OPER_HELP_ADMIN
	Syntax: ADMIN ADD nick
	        ADMIN DEL nick
	        ADMIN LIST
	
	Allows the Services super-user to add or remove nicknames
	to or from the Services admin list.  A user whose nickname
	is on the Services admin list and who has identified to
	%s will be able to access Services admin commands.
	
	Any IRC operator may use the ADMIN LIST form of the command.
	All other use limited to Services super-user.

OPER_HELP_MODE
	Syntax: MODE channel modes
	
	Allows Services operators to set channel modes for any
	channel.  Parameters are the same as for the standard /MODE
	command.
	
	Limited to Services operators.

OPER_HELP_CLEARMODES
	Syntax: CLEARMODES channel [ALL]
	
	Clears all binary modes (i,k,l,m,n,p,s,t) and bans from a
	channel.  If ALL is given, also clears all ops and
	voices (+o and +v modes) from the channel.
	
	Limited to Services operators.

OPER_HELP_CLEARCHAN
	Syntax: CLEARCHAN channel
	
	Removes all users from a channel (masskick).
	
	Limited to Services operators.

OPER_HELP_KICK
	Syntax: KICK channel user reason
	
	Allows IRCops to kick a user from any channel.
	Parameters are the same as for the standard /KICK
	command.  The kick message will have the nickname of the
	IRCop sending the KICK command prepended; for example:
	
	*** SpamMan has been kicked off channel #my_channel by %S (Alcan (Flood))
	
	Limited to Services operators.

OPER_HELP_AKILL
	Syntax: AKILL ADD [+expiry] mask reason
	        AKILL DEL mask
	        AKILL LIST [mask] [NOEXPIRE]
	        AKILL VIEW [mask] [NOEXPIRE]
	        AKILL COUNT
	
	Allows Services operators to manipulate the AKILL list.  If
	a user matching an AKILL mask attempts to connect, Services
	will issue a KILL for that user and, on supported server
	types, will instruct all servers to add a ban (K-line) for
	the mask which the user matched.
	
	AKILL ADD adds the given user@host mask to the AKILL
	list for the given reason (which must be given).
	AKILL DEL removes the given mask from the AKILL list if it
	is present.  AKILL LIST shows all current AKILLs; if the
	optional mask is given, the list is limited to those
	AKILLs matching the mask.  AKILL VIEW is a more verbose
	version of AKILL LIST, and will show who added an AKILL,
	the date it was added, and when it expires, as well as the
	user@host mask and reason. If the NOEXPIRE option is given,
	then only AKILLs that will not expire, and match the given
	user@host mask, will be displayed. AKILL COUNT simply
	returns the number of AKILLs in the AKILL list.
	
	Optionally, an expiry time can be given with the AKILL ADD
	command.  The expiry time precedes the user@host mask, and
	is specified as an integer followed by one of d (days),
	h (hours), or m (minutes).  Combinations (such as 1h30m)
	are not permitted.  If a unit specifier is not included,
	the default is days (so +30 by itself means 30 days).  To
	add an AKILL which does not expire, use +0.  If the
	usermask to be added starts with a +, an expiry time must
	be given, even if it is the same as the default.  The
	current AKILL default expiry time can be found with the
	STATS AKILL command.
	
	The reason is intended for use by IRC operators only, and
	will not be displayed to users in KILL messages.
	
	Limited to Services operators.

OPER_HELP_EXCEPTION
	Syntax: EXCEPTION ADD [+expiry] mask limit reason
	        EXCEPTION DEL {mask | list}
	        EXCEPTION MOVE num newnum
	        EXCEPTION LIST [mask | list]
	        EXCEPTION VIEW [mask | list]
	
	Allows Services admins to manipulate the list of hosts that
	have specific session limits - allowing certain machines,
	such as shell servers, to carry more than the default number
	of clients at a time. Once a host reaches it's session limit,
	all clients attempting to connect from that host will be
	killed. Before the user is killed, they are notified, via a
	/NOTICE from %S, of a source of help regarding session
	limiting. The content of this notice is a config setting.
	
	EXCEPTION ADD adds the given host mask to the exception list.
	Note that nick!user@host and user@host masks are invalid!
	Only real host masks, such as box.host.dom and *.host.dom,
	are allowed because sessions limiting does not take nick or
	user names into account. limit must be a number greater than
	or equal to zero. This determines how many sessions this host
	may carry at a time. A value of zero means the host has an
	unlimited session limit. See the AKILL help for details about
	the format of the optional expiry parameter.
	EXCEPTION DEL removes the given mask from the exception list.
	EXCEPTION MOVE moves exception num to newnum. If newnum
	is already used by another exception, its number will be shifted
	upward to make room.
	EXCEPTION LIST and EXCEPTION VIEW show all current exceptions;
	if the optional mask is given, the list is limited to those
	exceptions matching the mask. The difference is that EXCEPTION
	VIEW is more verbose, displaying the name of the person who
	added the exception, its session limit, reason, host mask and
	the expiry date and time.
	
	Note that a connecting client will "use" the first exception
	their host matches. Large exception lists and widely matching
	exception masks are likely to degrade services' performance.
	
	Limited to Services admins.

OPER_HELP_SESSION
	Syntax: SESSION LIST threshold
	        SESSION VIEW host
	
	Allows Services admins to view the session list.
	
	SESSION LIST lists hosts with at least threshold sessions.
	The threshold must be a number greater than 1. This is to
	prevent accidental listing of the large number of single
	session hosts.
	SESSION VIEW displays detailed information about a specific
	host - including the current session count and session limit.
	The host value may not include wildcards.
	
	See the EXCEPTION help for more information about session
	limiting and how to set session limits specific to certain
	hosts and groups thereof.
	
	Limited to Services admins.

OPER_HELP_SU
	Syntax: SU password
	
	Allows access to functions which require Services super-user
	privileges.  The password is the same as that set with the
	SET SUPASS command; note that the password must be set once
	before using this command.  Super-user privileges last until
	you change nicknames or quit IRC.
	
	WARNING: If you enter an incorrect password, Services will
	broadcast a warning message to all IRC operators.
	
	Limited to Services admins.

OPER_HELP_SET
	Syntax: SET option setting
	
	Sets various global Services options.  Option names
	currently defined are:
	    READONLY   Set read-only or read-write mode
	    DEBUG      Activate or deactivate debug mode
	    SUPASS     Set password for SU command (super-user)
	
	Limited to Services admins.

OPER_HELP_SET_READONLY
	Syntax: SET READONLY {ON | OFF}
	
	Sets read-only mode on or off.  In read-only mode, normal
	users will not be allowed to modify any Services data,
	including channel and nickname access lists, etc.  IRCops
	with sufficient Services privileges will be able to modify
	Services' AKILL list and drop or forbid nicknames and
	channels, but any such changes will not be saved unless
	read-only mode is deactivated before Services is terminated
	or restarted.
	
	This option is equivalent to the command-line option
	-readonly.

OPER_HELP_SET_DEBUG
	Syntax: SET DEBUG {ON | OFF | num}
	
	Sets debug mode on or off.  In debug mode, all data sent to
	and from Services as well as a number of other debugging
	messages are written to the log file.  If num is
	given, debug mode is activated, with the debugging level set
	to num.
	
	This option is equivalent to the command-line option
	-debug.

OPER_HELP_SET_SUPASS
	Syntax: SET SUPASS [password]
	
	Sets the password to be used for the SU command.  The
	password must be set once before using the SU command for
	the first time.  If no password is given, the SU command
	will be unavailable.
	
	This option may only be set by the Services super-user.

OPER_HELP_JUPE
	Syntax: JUPE server [reason]
	
	Tells Services to jupiter a server -- that is, to create
	a fake "server" connected to Services which prevents
	the real server of that name from connecting.  The jupe
	may be removed using a standard SQUIT.  If a reason is
	given, it is placed in the server information field;
	otherwise, the server information field will contain the
	text "Jupitered by <nick>", showing the nickname of the
	person who jupitered the server.
	
	Limited to Services admins.

OPER_HELP_RAW
	Syntax: RAW text
	
	Sends a string of text directly to the server to which
	Services is connected.  This command has a very limited
	range of uses, and can wreak havoc on a network or cause
	Services to crash if used improperly.  DO NOT USE THIS
	COMMAND unless you are absolutely certain you know what you
	are doing!
	
	Limited to Services admins.

OPER_HELP_UPDATE
	Syntax: UPDATE
	
	Causes Services to update all database files as soon as you
	send the command.
	
	Limited to Services admins.

OPER_HELP_QUIT
	Syntax: QUIT
	
	Causes Services to do an immediate shutdown; databases are
	not saved.  This command should not be used unless
	damage to the in-memory copies of the databases is feared
	and they should not be saved.  For normal shutdowns, use the
	SHUTDOWN command.
	
	Limited to Services admins.

OPER_HELP_SHUTDOWN
	Syntax: SHUTDOWN
	
	Causes Services to save all databases and then shut down.
	
	Limited to Services admins.

OPER_HELP_RESTART
	Syntax: RESTART
	
	Causes Services to save all databases and then restart
	(i.e. exit and immediately re-run the executable).
	
	Limited to Services admins.	

OPER_HELP_KILLCLONES
	Syntax: KILLCLONES nick
	
	Kills all users who have the same hostname as nick. A
	temporary AKILL, in the form *@host, is added to
	prevent the offending clients from immediately
	reconnecting. A wallops is also sent indicating who
	used the command, which host was affected and how many
	users were killed. It's useful for removing numerous
	clones from the network.
	
	Limited to Services operators.


###########################################################################
#
# StatServ help messages
#
############################################################################

STAT_HELP
	%S provides statistical information about the
	IRC network, its servers and its users. For information
	on a specific command, type /msg %S HELP command.
	
	    SERVERS     Server statistics
	    USERS       User statistics

STAT_HELP_SERVERS
	Syntax: SERVERS STATS
	        SERVERS LIST [mask]
	        SERVERS VIEW [mask] [ONLINE | OFFLINE]
	
	Displays statistics relating to the network's servers.
	
	SERVERS STATS displays a brief summary of the servers
	currently visible (online) and invisible (offline) to
	Services.
	SERVERS LIST displays a list of online servers and
	current statistics about each.
	SERVERS VIEW displays a list of online and offline
	servers with detailed statistics about each. The
	ONLINE and OFFLINE options cause, respectively,
	only online or offline servers to be shown.
	
	Use the mask option to limit which servers'
	statistics are shown.

STAT_HELP_USERS
	Syntax: USERS STATS
	
	Displays statistics relating to the network's users.

STAT_SERVROOT_HELP_SERVERS
	Syntax: SERVERS STATS
	        SERVERS LIST [mask]
	        SERVERS VIEW [mask] [ONLINE | OFFLINE]
	        SERVERS DELETE server
	        SERVERS COPY server newname
	        SERVERS RENAME server newname
	
	Displays statistics relating to the network's servers.
	
	SERVERS STATS displays a brief summary of the servers
	currently visible (online) and invisible (offline) to
	Services.
	SERVERS LIST displays a list of online servers and
	current statistics about each.
	SERVERS VIEW displays a list of online and offline
	servers with detailed statistics about each. The
	ONLINE and OFFLINE options cause, respectively,
	only online or offline servers to be shown.
	
	Use the mask option to limit which servers'
	statistics are shown.
	
	DELETE deletes the specified server's statistics.
	COPY duplicates a set of server statistics.
	RENAME rename's a set of server statistics.
	These three commands are limited to the Services super-user.

###########################################################################
#
# FloodServ help messages
#
###########################################################################

FLOOD_HELP
	%S Commands:
	CHAN        Manipulate channel table
	SET         Set various global Services options
	GRNAME      Manipulate the GRNAME list

	Limited to Services admins.

FLOOD_HELP_CHAN
	CHAN ADD channel
	CHAN DEL channel
	CHAN LIST
	CHAN REJOIN
	CHAN COUNT
	CHAN LISTFLOODTEXT
	
	Allows Services admins to add or remove channel from the 
	%S list. A channel on the %S list will be scanned for flood, 
	as defined in the options set in the configuration files or
	via the set command.

	CHAN ADD    adds the given channel to the database.
	CHAN DEL    deletes the given channel from the database.
	CHAN LIST   will display the contents of the %S channel database.
	CHAN REJOIN will make %S join all channels in the channel
	database.
	CHAN COUNT  will display the numbers of channel(s)
	that are in the channel database.
	CHAN LISTFLOODTEXT will display the flood text currently
	in the textflood database. *NOTE*: Running this command on a
	large network may not be a good idea.

	Limited to Services admin.

FLOOD_HELP_SET
	Syntax: SET option parameters
	
	Allows Services admins to set various %S options
	and other information.
	
	Available options:

	WARN  Set if you wish to warn before akilling.
	TXTFLOODLINE Set the number of lines to trigger flood protection.
	TXTFLOODSEC Set the number of seconds in which to scan for a flood.
	TXTFLOODLWN Set the numbers of lines written to trigger
	flood protection after being warned. IMPORTANT: cumulative with TXTFLOODLINE
	TXTFLOODWARN Set the ration of seconds to lines to trigger
	flood protection after being warned. IMPORTANT: cumulative with TXTFLOODSEC

	Limited to Services admin.

FLOOD_HELP_GRNAME
	
	Syntax:     GRNAME ADD name
	            GRNAME DEL name
			     GRNAME LIST
	
	Allows Services admins to add or remove a GRNAME from the
	database. Any GRNAME in the database will be autokilled
	as the client joins the network.
	
	Limited to Services admin


###########################################################################
#
# Misc help messages (added by jabea)
#
###########################################################################

OPER_HELP_NOOPER
	Syntax: NOOPER ADD mask reason
	        NOOPER DEL mask
	        NOOPER LIST [mask]
	        NOOPER VIEW [mask]
	        NOOPER COUNT
	
	Allow Services root to restrict operator lines on any server.
	When a mask is placed on the NOOPER list, that operator's 
	modes will be removed after their oper attempt. A globop will
	will be sent upon removing the operator modes.
	
	NOOPER ADD adds the given user@host mask to the NOOPER
	list for the given reason (which must be given).
	NOOPER DEL delete the given user@host mask from the NOOPER
	list.
	NOOPER LIST will display the entire NOOPER list or only
	the nooper coresponding to the mask.
	NOOPER VIEW will display the entire NOOPER list or only
	the nooper coresponding to the mask.
	NOOPER COUNT will display the numbers of people(s)
	that are on the NOOPER's list.
	
	Limited to Services root.

OPER_HELP_SNOOPER
	Syntax: SNOOPER ADD server_name reason
	        SNOOPER DEL server_name
	        SNOOPER LIST
	        SNOOPER COUNT
	
	Allow Services root to restrict all operator lines on any 
	given server. When the server name is placed on the SNOOPER 
	list, any one who opers on that server will have their operator 
	modes after their oper attempt. A globop will be sent upon 
	removing the operator modes.
	
	SNOOPER ADD adds the given server name to the SNOOPER
	list for the given reason (which must be given).
	SNOOPER DEL delete the given server name from the SNOOPER
	list.
	SNOOPER LIST will display the entire SNOOPER list.
	SNOOPER COUNT will display the numbers of server(s)
	that are on the SNOOPER's list.
	
	Limited to Services root.

OPER_HELP_ACONNECT
	Syntax: ACONNECT ADD server_name server_to_connect_2 port
	        ACONNECT DEL server_name
	        ACONNECT LIST
	        ACONNECT VIEW
	        ACONNECT COUNT
	
	Allows Services admins to add or remove servers from the 
	autoconnect list. A server on the autoconnect list will be
	automatically relinked to its hub server, as defined in the 
	autoconnect list, upon a netsplit.
	
		
	ACONNECT ADD adds the given server name to the ACONNECT
	list.
	ACONNECT DEL delete the given server name from the ACONNECT
	list.
	ACONNECT LIST will display the entire ACONNECT list.
	ACONNECT VIEW will display the entire ACONNECT list.
	ACONNECT COUNT will display the numbers of server(s)
	that are on the ACONNECT's list.
	
	Limited to Services admin.

OPER_HELP_CLOSENET
	Syntax: CLOSENET [time in second]
	        CLOSENET, With no argument to cancel a called CLOSENET.
	
	Allows Services admins to close the network for a limited
	time only, between 1 seconds to 10 minutes (600seconds) to
	prevent the loading of clones. All connect attemps will be /kill'ed
	in that time when CLOSENET is in effect. Only special case is the people
	on the exeption list that can enter the network surpassing the CLOSENET.
	
	Limited to Services admin.

CHAN_HELP_SET_FLOODSERV
	Syntax: SET channel FLOODSERV ON/OFF
	
	Activate FloodServ to monitor the channel, must be 
	the founder to set it.
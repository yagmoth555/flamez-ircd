/* Version information for IRC Services.
 *
 * IRC Services is copyright (c) 1996-2002 Andrew Church.
 *     E-mail: <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#define BUILD	"8"

const char version_number[] = "4.5.41";
const char version_build[] = "build #" BUILD ", compiled Wed Aug 21 23:37:17 CDT 2002";
const char version_protocol[] =
#if defined(IRC_BAHAMUT)
	"ircd.dal Bahamut"
#elif defined(IRC_UNREAL)
	"Unreal"
#elif defined(IRC_DAL4_4_15)
	"ircd.dal 4.4.15+"
#elif defined(IRC_DALNET)
	"ircd.dal 4.4.13-"
#elif defined(IRC_UNDERNET_NEW)
	"ircu 2.10+"
#elif defined(IRC_UNDERNET)
	"ircu 2.9.32-"
#elif defined(IRC_TS8)
	"RFC1459 + TS8"
#elif defined(IRC_CLASSIC)
	"RFC1459"
#else
	"unknown"
#endif
	;


/* Look folks, please leave this INFO reply intact and unchanged. If you do
 * have the urge to mention yourself, please simply add your name to the list.
 * The other people listed below have just as much right, if not more, to be
 * mentioned. Leave everything else untouched. Thanks.
 */

const char *info_text[] =
    {
	"Flamez-Services developed by and copyright (c) 2001-2002",
	"",
	"We would like to thank all the users who have stuck",
	"by us and continue to help us with improving these",
	"services. Many thanks to all who have helped make",
	"another services release a possibility. Please visit",
	"us on http://www.flamez.net and report any bugs or new",
	"ideas to development@flamez.net",
	"",
	"Author: jabea - jabea@insiderz.net",
	"",
	"Project leader: gcc - gcc@insiderz.net",
	"",
	"NOTE: These services are a modification of ircservices",
	"by A. Church. Special thanks go to him for his inspiration",
	"to open source his services.",
	0,
    };

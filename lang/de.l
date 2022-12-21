# Emacs mode: -*- text -*-¡¡

# Services is copyright (c) 1996-2001 Andy Church.
#     E-mail: <achurch@dragonfire.net>
# This program is free but copyrighted software; see the file COPYING for
# details.

LANG_NAME
	Deutsch (German)
#########################################################
# Translated by TimeMr14C (uhc0@stud.uni-karlsruhe.de)  #
# Translated by freenet.de (www.freenet.de)             #
# Put together, corrected by jacek.margos@freenet-ag.de #
#########################################################

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
	%d. %b %H:%M:%S %Y %Z
# This is used as the format string for strftime() for a date alone in long
# format (English: including weekday).
STRFTIME_LONG_DATE_FORMAT
	%a %d.%b.%Y
# This is used as the format string for strftime() for a date alone in
# short format (English: without weekday).
STRFTIME_SHORT_DATE_FORMAT
	%d.%b.%Y

# These tell our strftime() what the names of months and days are.  If you
# don't use %a, %A, %b, or %B in your strftime() strings above, you can
# leave these empty.  However, if you enter names, they MUST stay in order,
# one per line, and the list MUST be complete!

# %a
STRFTIME_DAYS_SHORT
	So
	Mo
	Di
	Mi
	Do
	Fr
	Sa
# %A
STRFTIME_DAYS_LONG
	Sonntag
	Montag
	Dienstag
	Mittwoch
	Donnerstag
	Freitag
	Samstag
# %b
STRFTIME_MONTHS_SHORT
	Jan
	Feb
	Mrz
	Apr
	Mai
	Jun
	Jul
	Aug
	Sep
	Okt
	Nov
	Dez	
# %B
STRFTIME_MONTHS_LONG
	Januar
	Februar 	
	März
	April
	Mai
	Juni
	Juli
	August
	September
	Oktober
	November
	Dezember

# "day", "hour", "minute", and "second" in singular and plural.
STR_DAY
	Tag
STR_DAYS
	Tage
STR_HOUR
	Stunde
STR_HOURS
	Stunden
STR_MINUTE
	Minute
STR_MINUTES
	Minuten
STR_SECOND
	Sekunde
STR_SECONDS
	Sekunden


# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	,

# Various error messages.
USER_RECORD_NOT_FOUND
	Interner Fehler - Verarbeitung der Anfrage nicht möglich.	
UNKNOWN_COMMAND
	Unbekannter Befehl %s.
UNKNOWN_COMMAND_HELP
	Unbekannter Befehl %s. "/msg %s HELP" für Hilfe.
SYNTAX_ERROR
	Syntax: %s
MORE_INFO
	/msg %s HELP %s für weitere Informationen.
NO_HELP_AVAILABLE
	Keine Hilfe verfügbar für %s.

BAD_EMAIL
	Email Adressen müssen der Form benutzer@domain sein. Es dürfen keine Kontrol-Charaktere oder keine dieser Zeichen benutzt werden: , : ; | \ " ( ) < >
BAD_URL
	Eine URL muß der Form http://hostname[:port]/... (oder ftp://, etc.) entsprechen.
BAD_USERHOST_MASK
	Maske muß folgendes Format haben: user@host.
BAD_EXPIRY_TIME
	Ungültige Verfallsdauer.

SERVICE_OFFLINE
	%s ist momentan nicht verfügbar.
READ_ONLY_MODE
	Hinweis: Services ist im schreibgeschützten Modus; 
	Änderungen werden nicht gespeichert !
PASSWORD_INCORRECT
	Falsches Passwort.
# What's the difference between "Access denied" and "Permission denied"?
# Very little; you can safely make them the same message with no real loss
# of meaning.  If you want to make a distinction, "Access denied" is
# usually used more generally; for example, a non-oper trying to access
# OperServ gets "Access denied", while a non-Services admin trying to use
# NickServ SET NOEXPIRE gets "Permission denied".
ACCESS_DENIED
	Zugriff verweigert.
PERMISSION_DENIED
	Zugriff verweigert.

MORE_OBSCURE_PASSWORD
	Versuchen Sie es erneut mit einem ungewöhnlicheren Passwort.
	Passwörter sollten mindestens fünf Zeichen lang sein und
	nicht zu leicht zu erraten
	(z.B. nicht Ihr wirklicher Name oder Ihr Chatname).
	Leerzeichen und Tabulatoren dürfen nicht verwendet werden.
PASSWORD_TRUNCATED
	Hinweis:  Ihr Passwort ist auf %d Zeichen verkürzt worden,
	die letzten Zeichen wurden abgeschnitten.

NICK_NOT_REGISTERED
	Ihr Chatname ist nicht registriert.
NICK_NOT_REGISTERED_HELP
	Ihr Chatname ist nicht registriert.
	Für weitere Informationen zur Chatnamen-Registrierung
	bitte /msg %s HELP eingeben.
NICK_X_NOT_REGISTERED
	Der Chatname %s ist nicht registriert.
NICK_X_NOT_IN_USE
	Der Chatname %s ist momentan nicht in Benutzung
NICK_X_FORBIDDEN
	Der Name %s darf weder genutzt noch registriert werden
NICK_X_SUSPENDED
	Der Chatname %s ist suspendiert, und kann nicht benutzt werden.
NICK_X_SUSPENDED_MEMOS
	Der Chatname %s ist suspendiert, und kann keine Memos erhalten.
NICK_IDENTIFY_REQUIRED
	Dieser Befehl benötigt eine Passwort-Authentizierung.
	Bitte versuchen Sie es erneut nach der Eingabe von
	/msg %s IDENTIFY Passwort.
NICK_X_NOT_ON_CHAN_X
	Der Chatname %s ist im Moment nicht im Raum %s.

CHAN_X_NOT_REGISTERED
	Der Raum %s ist nicht registriert.
CHAN_X_NOT_IN_USE
	Der Raum %s wird momentan nicht benutzt.
CHAN_X_FORBIDDEN
	Der Raum %s darf weder genutzt noch registriert werden.
CHAN_X_SUSPENDED
	Der Raum %s ist suspendiert, und kann nicht benutzt werden.
CHAN_X_SUSPENDED_MEMOS
	Der Raum %s ist suspendiert, und kann keine Memos erhalten.
CHAN_IDENTIFY_REQUIRED
	Dieser Befehl benötigt eine Passwort-Authentizierung.
	Bitte versuchen Sie es erneut nach der Eingabe von
	/msg %s IDENTIFY %s Passwort.
	
SERV_X_NOT_FOUND
	Server %s wurde gefunden.

EXPIRES_NONE
	Wird nicht verfallen.
EXPIRES_SOON
	Verfällt beim nächsten Update. 
EXPIRES_M
	Verfällt in %d Minuten. 
EXPIRES_1M
	Verfällt in %d Minute. 
EXPIRES_HM
	Verfällt in %d Stunden und %d Minuten.
EXPIRES_H1M
	Verfällt in %d Stunden und %d Minute.
EXPIRES_1HM
	Verfällt ind %d Stunde und %d Minuten. 
EXPIRES_1H1M
	Verfällt ind %d Stunde und %d Minute. 
EXPIRES_D
	Verfällt in %d Tage. 
EXPIRES_1D
	Verfällt in %d Tag.

###########################################################################
#
# NickServ messages
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	Dieser Chatname wird von jemand anderem benutzt.
	Bitte wählen Sie einen anderen.
	(Falls dies Ihr Chatname ist, geben Sie bitte
	/msg %s IDENTIFY Passwort ein.)
NICK_IS_SECURE
	Dieser Chatname ist registriert und geschützt.
	Falls dies Ihr Chatname ist, geben Sie bitte
	/msg %s IDENTIFY Passwort ein.
	Wählen Sie anderenfalls einen neuen Chatnamen.
NICK_MAY_NOT_BE_USED
	Dieser Chatname darf nicht genutzt werden.
	Wählen Sie bitte einen anderen.
DISCONNECT_IN_1_MINUTE
	Falls Sie nicht innerhalb der nächsten Minute
	Ihren Chatnamen ändern, werden Sie vom Server getrennt.
DISCONNECT_IN_20_SECONDS
	Falls Sie nicht innerhalb der nächsten 20 Sekunden
	Ihren Chatnamen ändern, werden Sie vom Server getrennt.
DISCONNECT_NOW
	Dieser Chatname ist bereits registriert;
	Sie dürfen ihn nicht benutzen.
	Wählen Sie einen anderen, bevor Sie sich neu verbinden.
FORCENICKCHANGE_IN_1_MINUTE
	Falls Sie nicht innerhalb der nächsten Minute
	Ihren Chatnamen ändern, wird er automatisch geändert.
FORCENICKCHANGE_IN_20_SECONDS
	Falls Sie nicht innerhalb der nächsten 20 Sekunden
	Ihren Chatnamen ändern, wird er automatisch geändert.
FORCENICKCHANGE_NOW
	Dieser Chatname ist bereits registriert;
	Sie dürfen Ihn nicht benutzen.
	Ihr Chatname wird jetzt in %s geändert.
NICK_EXPIRES_SOON
	Warnung: Ihre Chatnamen-Registrierung wird in %d %s
	verfallen. Wenn Sie weiterhinn Ihren Chatnamen werwenden
	wollen, müssen Sie sich durch folgendes identifizieren:
	/msg %s IDENTIFY Passwort
NICK_EXPIRED
	Warnung: Ihre Chatnamen-Registrierung ist bereits
	verfallen. Bitte registrieren Sie den Chatnamen neu,
	wenn sie Ihn weiter verwenden wollen.


# REGISTER responses
NICK_REGISTER_SYNTAX
	REGISTER Password [Email]
NICK_REGISTER_REQ_EMAIL_SYNTAX
	REGISTER Password Email
NICK_REGISTRATION_DISABLED
	Die Chatnamen-Registrierung ist temporär nicht verfügbar.
NICK_REGISTRATION_FAILED
	Die Registrierung hat nicht funktioniert.
NICK_REG_PLEASE_WAIT
	Bitte warten Sie %d Sekunden,
	bevor Sie den REGISTER-Befehl erneut benutzen.
NICK_CANNOT_BE_REGISTERED
	Chatname %s darf nicht registriert werden.
NICK_ALREADY_REGISTERED
	Der Chatname %s ist bereits registriert.
NICK_REGISTERED
	Der Chatname %s ist für Sie registriert: %s
NICK_PASSWORD_IS
	Ihr Passwort lautet: %s. Bitte merken Sie es sich.

# IDENTIFY responses
NICK_IDENTIFY_SYNTAX
	IDENTIFY Password
NICK_IDENTIFY_FAILED
	Leider schlug Ihre Identifikation fehl.
NICK_IDENTIFY_SUCCEEDED
	Passwort akzeptiert - Sie sind identifiziert worden.

# DROP responses
NICK_DROP_SYNTAX
	DROP
NICK_DROP_DISABLED
	Die Chatnamen-Deregistrierung ist temporär nicht verfügbar.
NICK_DROPPED
	Ihr Chatname ist wieder freigegeben worden.
NICK_X_DROPPED
	Der Chatname %s ist wieder freigegeben worden

# SET responses
NICK_SET_SYNTAX
	SET Option Parameter
NICK_SET_SERVADMIN_SYNTAX
	SET [Chatname] Option Parameter
NICK_SET_DISABLED
	Leider ist die Chatname-Option temporär nicht verfügbar.
NICK_SET_UNKNOWN_OPTION
	Unbekannte SET-Option: %s.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	Unbekannte SET Option: %s oder Chatname ist nicht registriert.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	Das Passwort konnte nicht geändert werden.
NICK_SET_PASSWORD_CHANGED
	Das Passwort wurde geändert.
NICK_SET_PASSWORD_CHANGED_TO
	Das Passwort wurde in %s geändert.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_SYNTAX
	SET LANGUAGE Nummer
NICK_SET_LANGUAGE_UNKNOWN
	Unbekannte Sprachen-Nummer %d.
	Geben Sie für eine Liste aller Sprachen bitte
	/msg %s HELP SET LANGUAGE ein
NICK_SET_LANGUAGE_CHANGED
	Die Sprache wurde in Deutsch geändert.

# SET URL responses
NICK_SET_URL_CHANGED
	URL für %s wurde zu %s geändert.

# SET EMAIL responses
NICK_SET_EMAIL_CHANGED
	Email-Adresse für %s wurde zu %s geändert.

# SET KILL responses
NICK_SET_KILL_SYNTAX
	SET KILL {ON | QUICK | OFF}
NICK_SET_KILL_IMMED_SYNTAX
	SET KILL {ON | QUICK | IMMED | OFF}
NICK_SET_KILL_ON
	Der Chatnamen-Übernahmeschutz steht jetzt auf:
	ON (eingeschaltet).
NICK_SET_KILL_QUICK
	Der Chatnamen-Übernahmeschutz steht jetzt auf:
	QUICK (eingeschaltet mit kurzer Warnzeit,
	diese Option wird nicht empfohlen).
NICK_SET_KILL_IMMED
	Der Chatnamen-Übernahmeschutz steht jetzt auf:
	IMMED (eingeschaltet mit keiner Warnzeit,
	diese Option wird nicht empfohlen).
NICK_SET_KILL_IMMED_DISABLED
	Die IMMED-Option ist nicht verfügbar.
NICK_SET_KILL_OFF
	Der Chatnamen-Übernahmeschutz steht jetzt auf:
	OFF (ausgeschaltet).

# SET SECURE responses
NICK_SET_SECURE_SYNTAX
	SET SECURE {ON | OFF}
NICK_SET_SECURE_ON
	Die Secure-Option steht jetzt auf:
	ON (eingeschaltet).
NICK_SET_SECURE_OFF
	Die Secure-Option steht jetzt auf:
	OFF (ausgeschaltet).

# SET PRIVATE responses
NICK_SET_PRIVATE_SYNTAX
	SET PRIVATE {ON | OFF}
NICK_SET_PRIVATE_ON
	Die Privat-Option steht jetzt auf:
	ON (eingeschaltet).
NICK_SET_PRIVATE_OFF
	Die Privat-Option steht jetzt auf:
	OFF (ausgeschaltet).

# SET HIDE responses
NICK_SET_HIDE_SYNTAX
	SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
NICK_SET_HIDE_EMAIL_ON
	Ihre Email-Adresse wird nun bei einer '%s INFO'-Anfrage
	nicht angezeigt.
NICK_SET_HIDE_EMAIL_OFF
	Ihre Email-Adresse wird nun bei einer '%s INFO'-Anfrage
	angezeigt.
NICK_SET_HIDE_MASK_ON
	Ihre last seen user@host mask wird nun bei einer
	'%s INFO'-Anfrage nicht angezeigt.
NICK_SET_HIDE_MASK_OFF
	Ihre last seen user@host mask wird nun bei einer
	'%s INFO'-Anfrage angezeigt.
NICK_SET_HIDE_QUIT_ON
	Ihre Abschlussnachricht (QUIT) wird nun bei einer
	%s INFO'-Abfrage nicht angezeigt.
NICK_SET_HIDE_QUIT_OFF
	Ihre Abschlussnachricht (QUIT) wird nun bei einer
	'%s INFO'-Abfrage angezeigt.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_SYNTAX
	SET [Chatname] NOEXPIRE {ON | OFF}
NICK_SET_NOEXPIRE_ON
	Der Chatname %s wird nicht verfallen
NICK_SET_NOEXPIRE_OFF
	Der Chatname %s wird verfallen .

# UNSET responses
NICK_UNSET_SYNTAX
	UNSET {URL | EMAIL}
NICK_UNSET_SYNTAX_REQ_EMAIL
	UNSET URL
NICK_UNSET_URL
	URL für %s wurde zurückgesetzt.
NICK_UNSET_EMAIL
	Email Adresse für %s wurde zurückgesetzt.
NICK_UNSET_EMAIL_BAD
	Email Adresse kann nicht zurückgesetzt werden. 
NICK_UNSET_EMAIL_OTHER_BAD
	Email-Adressen können nicht zurückgesetzt werden. 

# ACCESS responses
NICK_ACCESS_SYNTAX
	ACCESS {ADD | DEL | LIST} [Maske]
NICK_ACCESS_ALREADY_PRESENT
	Die Maske %s steht bereits auf Ihrer Zugriffsliste.
NICK_ACCESS_REACHED_LIMIT
	Limit der %d Einträge der Zugriffsliste erschöpft.
NICK_ACCESS_ADDED
	Maske %s wurde zu Ihrer Zugriffsliste eingetragen.
NICK_ACCESS_NOT_FOUND
	Maske %s wurde in Ihrer Zugriffsliste nicht gefunden.
NICK_ACCESS_DELETED
	Maske %s wurde von Ihrer Zugriffsliste gelöscht.
NICK_ACCESS_LIST
	Zugriffsliste:
NICK_ACCESS_LIST_X
	Zugriffsliste für %s:

# LINK responses
NICK_LINK_SYNTAX
	LINK Chatname Passwort
NICK_LINK_DISABLED
	Der Link-Befehl ist deaktiviert.
NICK_LINK_FAILED
	Der Link konnte nicht erzeugt werden.
NICK_NO_LINK_SAME
	Ein Link zum selben Chatnamen ist unmöglich!
NICK_LINK_CIRCULAR
	Ein Link zum %s unmöglich (es würde eine Schleife entstehen).
NICK_LINK_TOO_DEEP
	Sie können keine Links über %d Stufen erzeugen.
NICK_LINK_TOO_MANY_CHANNELS
	Kann keinen Link zu %s nicht erzeugen:
	Zu viele registrierte Räume (zusammen %d).
NICK_LINKED
	Der Link zu %s wurde erzeugt.

# UNLINK responses
NICK_UNLINK_SYNTAX
	UNLINK [Chatname Passwort]
NICK_UNLINK_FAILED
	Der Link konnte nicht gelöscht werden.
NICK_NOT_LINKED
	Der Chatname hat keinen Link.
NICK_UNLINKED
	Der Link zu %s wurde gelöscht.
NICK_X_NOT_LINKED
	Der Chatname %s hat keinen Link.
NICK_X_UNLINKED
	Der Link vom Chatnamen %s zu %s wurde gelöscht.

# LISTLINKS responses
NICK_LISTLINKS_SYNTAX
	LISTLINKS Chatname [ALL]
NICK_LISTLINKS_HEADER
	Links zum Chatnamen %s:
NICK_LISTLINKS_FOOTER
	%d Chatnamen mit Link.
NICK_X_IS_LINKED
	%s
NICK_X_IS_LINKED_VIA_X
	%-20s (via %s)

# INFO responses
NICK_INFO_SYNTAX
	INFO Chatname [ALL]
NICK_INFO_REALNAME
	%s ist %s
NICK_INFO_ADDRESS
	   Last-seen Adresse: %s
NICK_INFO_ADDRESS_ONLINE
	      Ist online von: %s
NICK_INFO_ADDRESS_ONLINE_NOHOST
	%s ist momentan online.
NICK_INFO_TIME_REGGED
	  Registrationsdatum: %s
NICK_INFO_LAST_SEEN
	      Last-seen Zeit: %s
NICK_INFO_LAST_QUIT
	Letzte QUIT-Nachricht: %s
NICK_INFO_URL
	                  URL: %s
NICK_INFO_EMAIL
	       Email Addresse: %s
NICK_INFO_OPTIONS
	             Optionen: %s
NICK_INFO_LINKED_TO
	              Link zu: %s
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	Chatnamen-Übernahmeschutz
NICK_INFO_OPT_SECURE
	Secure Option
NICK_INFO_OPT_PRIVATE
	Privat
NICK_INFO_OPT_NONE
	Keine
NICK_INFO_NO_EXPIRE
	Dieser Chatname wird nicht verfallen.
NICK_INFO_SUSPEND_DETAILS
	Suspendiert von %s am %s (%s).
NICK_INFO_SUSPEND_REASON
	Grund: %s
NICK_INFO_SHOW_ALL
	/msg %s INFO %s ALL für weitere Informationen

# LISTCHANS responses
NICK_LISTCHANS_SYNTAX
	LISTCHANS
NICK_LISTCHANS_SERVADMIN_SYNTAX
	LISTCHANS [Chatname]
NICK_LISTCHANS_NONE
	%s hat keine registrierten Räume.
NICK_LISTCHANS_HEADER
	Registrierte Räume von %s:
NICK_LISTCHANS_ENTRY
	%s
NICK_LISTCHANS_END
	Ende der Liste (%d registrierte Räume)

# LIST responses
NICK_LIST_SYNTAX
	LIST Muster
NICK_LIST_SERVADMIN_SYNTAX
	LIST Muster [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
NICK_LIST_HEADER
	Liste aller Einträge, auf die %s zutrifft:
NICK_LIST_RESULTS
	Ende der Liste - es wurden %d/%d Treffer angezeigt

# RECOVER responses
NICK_RECOVER_SYNTAX
	RECOVER Chatname [Passwort]
NICK_NO_RECOVER_SELF
	Sie können sich selbst nicht killen!
NICK_RECOVERED
	Der User mit Ihrem Chatnamen wurde aus dem Network gekillt.
	Mit /msg %s RELEASE %s können Sie Ihren Chatnamen vor
	der Zeit von 1 Minute zurückerhalten.

# RELEASE responses
NICK_RELEASE_SYNTAX
	RELEASE Chatname [Passwort]
NICK_RELEASE_NOT_HELD
	Chatname %s wird nicht eibehalten.
NICK_RELEASED
	Chatname wurde freigestellt.

# GHOST responses
NICK_GHOST_SYNTAX
	GHOST Chatname [Passwort]
NICK_NO_GHOST_SELF
	Sie können sich selbst nicht killen!
NICK_GHOST_KILLED
	Verbindung des hängengebliebenen Chatname wurde unterbrochen.

# GETPASS responses
NICK_GETPASS_SYNTAX
	GETPASS Chatname
NICK_GETPASS_UNAVAILABLE
	Aufgrund der Nutzung von Verschlüsselung
	ist der GETPASS-Befehl ist nicht verfügbar.
NICK_GETPASS_PASSWORD_IS
	Das Passwort des für %s lautet %s.

# FORBID responses
NICK_FORBID_SYNTAX
	FORBID Chatname
NICK_FORBID_SUCCEEDED
	Der Chatname %s ist jetzt gesperrt.
NICK_FORBID_FAILED
	Der Chatname %s konnte nicht gesperrt werden!

# SUSPEND responses
NICK_SUSPEND_SYNTAX
	SUSPEND [+Dauer] Chatname Grund
NICK_SUSPEND_SUCCEEDED
	Der Chatname %s und alle damit verbundene
	Chatnamen sind suspendiert. 
NICK_SUSPEND_ALREADY_SUSPENDED
	Der Chatname %s ist bereits suspendiert.

# UNSUSPEND responses
NICK_UNSUSPEND_SYNTAX
	UNSUSPEND Chatname
NICK_UNSUSPEND_SUCCEEDED
	Suspend von %s ist jetzt aufgehoben.
NICK_SUSPEND_NOT_SUSPENDED
	Der Chatname %s ist nicht suspendiert.

###########################################################################
#
# ChanServ messages
#
###########################################################################

# Access level descriptions
CHAN_LEVEL_AUTOOP
	Automatischer Raumoperator-Status
CHAN_LEVEL_AUTOVOICE
	Automatischer Moderator-Status
CHAN_LEVEL_AUTODEOP
	Der automatische Raumoperator-Status nicht erlaubt
CHAN_LEVEL_AUTODEOP_HALFOP
	Der automatische Raumoperator-Status (HalfOp) nicht erlaubt
CHAN_LEVEL_NOJOIN
	Der Raum darf nicht betreten werden,
	falls er RESTRICTED ist.
CHAN_LEVEL_INVITE
	Der INVITE-Befehl darf benutzt werden
CHAN_LEVEL_AKICK
	Der AKICK-Befehl darf benutzt werden
CHAN_LEVEL_SET
	Der SET-Befehl darf benutzt werden (bis auf FOUNDER/PASSWORD)
CHAN_LEVEL_CLEAR
	Der CLEAR-Befehl darf benutzt werden
CHAN_LEVEL_UNBAN
	Der UNBAN-Befehl darf benutzt werden
CHAN_LEVEL_OPDEOP
	Die OP/DEOP-Befehle dürfen benutzt werden
CHAN_LEVEL_VOICE
	Die VOICE/DEVOICE-Befehle dürfen benutzt werden
CHAN_LEVEL_ACCESS_LIST
	Die Zugriffsliste darf angezeigt werden
CHAN_LEVEL_ACCESS_CHANGE
	Die Zugriffsliste darf modifiziert werden
CHAN_LEVEL_MEMO
	Raum-Memos dürfen aufgelistet/gelesen werden
CHAN_LEVEL_AUTOHALFOP
	Automatischer Raumoperator-Status (HalfOp +h)
CHAN_LEVEL_HALFOP
	Die HALFOP/DEHALFOP-Befehle dürfen benutzt werden
CHAN_LEVEL_AUTOPROTECT
	Automatischer Raum-Schutz-Status (+a)
CHAN_LEVEL_PROTECT
	Die PROTECT/DEPROTECT-Befehle dürfen benutzt werden

# Automatic responses
CHAN_IS_REGISTERED
	Dieser Raum ist mit %s registriert worden.
CHAN_NOT_ALLOWED_OP
	Sie dürfen nicht Raum-Operator in Raum %s sein.
CHAN_MAY_NOT_BE_USED
	Dieser Raum darf nicht benutzt werden.
CHAN_NOT_ALLOWED_TO_JOIN
	Ihnen ist der Aufenthalt in diesem Raum untersagt.

# Multi-purpose responses
CHAN_BOUNCY_MODES
	Der %s-Befehl kann zur Zeit nicht benutzt werden.


# REGISTER responses
CHAN_REGISTER_SYNTAX
	REGISTER Raum Passwort Beschreibung
CHAN_REGISTER_DISABLED
	Leider ist die Raum-Registrierung temporär nicht verfügbar.
CHAN_REGISTER_NOT_LOCAL
	Lokale Räume können nicht registriert werden.
CHAN_MUST_REGISTER_NICK
	Sie müssen zuerst Ihren Chatnamen registrieren.
	Für weitere Informationen zur Chatnamen-Registrierung
	bitte /msg %s HELP eingeben.
CHAN_MUST_IDENTIFY_NICK
	Bitte identifzieren Sie sich zuerst mit %s. Befehl:
	/msg %s IDENTIFY Passwort
CHAN_MAY_NOT_BE_REGISTERED
	Der Raum %s darf nicht registriert werden.
CHAN_ALREADY_REGISTERED
	Der Raum %s ist bereits registriert!
CHAN_MUST_BE_CHANOP
	Sie müssen Raumoperator sein um diesen Raum zu registrieren.
CHAN_REACHED_CHANNEL_LIMIT
	Limit der %d registrierten Räume erreicht.
CHAN_EXCEEDED_CHANNEL_LIMIT
	Limit der %d registrierten Räume überschritten.
CHAN_REGISTRATION_FAILED
	Die Registrierung ist leider fehlgeschlagen.
CHAN_REGISTERED
	Der Raum %s ist auf Sie registriert: %s
CHAN_PASSWORD_IS
	Ihr Raum-Passwort lautet %s,
	bitte nicht vergessen.

# IDENTIFY responses
CHAN_IDENTIFY_SYNTAX
	IDENTIFY Raum Passwort
CHAN_IDENTIFY_FAILED
	Leider schlug die Identifizierung fehl.
CHAN_IDENTIFY_SUCCEEDED
	Passwort korrekt - Sie haben jetzt Zugriff
	auf Gründer-Stufe zu %s.

# DROP responses
CHAN_DROP_SYNTAX
	DROP Raum
CHAN_DROP_DISABLED
	Die Raum-Deregistrierung ist temporär nicht verfügbar.
CHAN_DROPPED
	Der Raum %s wurde freigegeben.

# SET responses
CHAN_SET_SYNTAX
	SET Raum Option Parameter
CHAN_SET_DISABLED
	Die Raum-Option ist temporär nicht verfügbar.
CHAN_SET_UNKNOWN_OPTION
	Unbekannte SET-Option %s.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	%s hat zu viele Räume registriert.
CHAN_FOUNDER_CHANGED
	Der Gründer vom Raum %s wurde zu %s geändert.

# SET SUCCESSOR responses
CHAN_SUCCESSOR_CHANGED
	Der Nachfolger für %s hat sich in %s geändert.
CHAN_SUCCESSOR_IS_FOUNDER
	Der Nachfolger kann nicht gleichzeitig Gründer sein.

# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Das Passwort konnte nicht gesetzt werden.
CHAN_PASSWORD_CHANGED
	Das Passwort von %s wurde geändert.
CHAN_PASSWORD_CHANGED_TO
	Das Passwort von %s wurde in %s geändert.

# SET DESC responses
CHAN_DESC_CHANGED
	Die Beschreibung von %s wurde in %s geändert.

# SET URL responses
CHAN_URL_CHANGED
	URL für %s wurde zu %s geändert.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	Die EMail-Adresse für %s wurde in %s geändert.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	Die Begrüßungsnachricht für %s wurde geändert.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Leider konnte das Thema nicht gesetzt werden.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	MLOCK +k benötigt einen Parameter.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	MLOCK +l benötigt einen Parameter.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	Der Parameter für MLOCK +l muß eine positive Zahl sein.
CHAN_SET_MLOCK_MODE_REG_BAD
	Modus +%c kann mit MLOCK nicht benutzt werden. 
CHAN_SET_MLOCK_MODE_F_BAD
	Modus +f kann nicht gespeichert werden.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Unbekanntes Modus-Zeichen %c wird ignoriert.
CHAN_MLOCK_CHANGED
	Der Sperr-Modus für Raum %s wurde in %s geändert.
CHAN_MLOCK_REMOVED
	Der Sperr-Modus für Raum %s wurde zurückgenommen.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_SYNTAX
	SET Raum KEEPTOPIC {ON | OFF}
CHAN_SET_KEEPTOPIC_ON
	Die Option zur Beibehaltung des Themas steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_KEEPTOPIC_OFF
	Die Option zur Beibehaltung des Themas steht jetzt auf:
	OFF (ausgeschaltet).

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_SYNTAX
	SET Raum TOPICLOCK {ON | OFF}
CHAN_SET_TOPICLOCK_ON
	Die Option zur Sperrung des Themas steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_TOPICLOCK_OFF
	Die Option zur Sperrung des Themas steht jetzt auf:
	OFF (ausgeschaltet).

# SET PRIVATE responses
CHAN_SET_PRIVATE_SYNTAX
	SET Raum PRIVATE {ON | OFF}
CHAN_SET_PRIVATE_ON
	Die Privat-Option steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_PRIVATE_OFF
	Die Privat-Option steht jetzt auf:
	OFF (ausgeschaltet).

# SET SECUREOPS responses
CHAN_SET_SECUREOPS_SYNTAX
	SET Raum SECUREOPS {ON | OFF}
CHAN_SET_SECUREOPS_ON
	Die Secure ops option steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_SECUREOPS_OFF
	Die Secure ops option steht jetzt auf:
	OFF (ausgeschaltet).

# SET LEAVEOPS responses
CHAN_SET_LEAVEOPS_SYNTAX
	SET Raum LEAVEOPS {ON | OFF}
CHAN_SET_LEAVEOPS_ON
	Die Leave ops option steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_LEAVEOPS_OFF
	Die Leave ops option steht jetzt auf:
	OFF (ausgeschaltet).

# SET RESTRICTED responses
CHAN_SET_RESTRICTED_SYNTAX
	SET Raum RESTRICTED {ON | OFF}
CHAN_SET_RESTRICTED_ON
	Die Zugangsbeschränkungs-Option steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_RESTRICTED_OFF
	Die Zugangsbeschränkungs-Option steht jetzt auf:
	OFF (ausgeschaltet).

# SET SECURE responses
CHAN_SET_SECURE_SYNTAX
	SET Raum SECURE {ON | OFF}
CHAN_SET_SECURE_ON
	Secure-Option steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_SECURE_OFF
	Secure-Option steht jetzt auf:
	OFF (ausgeschaltet).

# SET OPNOTICE responses
CHAN_SET_OPNOTICE_SYNTAX
	SET Raum OPNOTICE {ON | OFF}
CHAN_SET_OPNOTICE_ON
	Op-Notice-Option steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_OPNOTICE_OFF
	Op-Notice-Option steht jetzt auf:
	OFF (ausgeschaltet).

# SET ENFORCE responses
CHAN_SET_ENFORCE_SYNTAX
	SET Raum ENFORCE {ON | OFF}
CHAN_SET_ENFORCE_ON
	Enforce-Option steht jetzt auf:
	ON (eingeschaltet).
CHAN_SET_ENFORCE_OFF
	Enforce-Option steht jetzt auf:
	OFF (ausgeschaltet).

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_SYNTAX
	SET Raum NOEXPIRE {ON | OFF}
CHAN_SET_NOEXPIRE_ON
	Der Raum %s wird nicht verfallen.
CHAN_SET_NOEXPIRE_OFF
	Der Raum %s wird verfallen.

# UNSET responses
CHAN_UNSET_SYNTAX
	UNSET Raum {SUCCESSOR | URL | EMAIL | ENTRYMSG}
CHAN_SUCCESSOR_UNSET
	Der Nachfolger für %s wurde zurückgesetzt.
CHAN_URL_UNSET
	URL für %s wurde zurückgesetzt.
CHAN_EMAIL_UNSET
	Die EMail-Adresse für %s wurde zurückgesetzt.
CHAN_ENTRY_MSG_UNSET
	Die Begrüßungsnachricht für %s wurde zurückgesetzt.



# ACCESS messages
CHAN_ACCESS_SYNTAX
	ACCESS Raum {ADD | DEL | LIST | COUNT} [Chatname [Stufe] | Eintragsliste]
CHAN_ACCESS_DISABLED
	Leider können Zugriffslisten der Räume Zeit nicht modifiziert werden.
CHAN_ACCESS_LEVEL_NONZERO
	Zugriffsstufe muß eine Zahl ausser 0 (Null) sein.
CHAN_ACCESS_LEVEL_RANGE
	Zugriffsstufe muß zwischen %d und %d sein (einschließlich).
CHAN_ACCESS_NICKS_ONLY
	Die Zugriffslisten für Räume
	können nur registrierte Chatnamen enthalten.
CHAN_ACCESS_REACHED_LIMIT
	Limit der %d Einträge in der Zugriffsliste erreicht.
CHAN_ACCESS_LEVEL_UNCHANGED
	Zugriffsstufe von %s in der Zugriffsliste von %s
	war bereits %d (blieb unverändert).
CHAN_ACCESS_LEVEL_CHANGED
	Zugriffsstufe von %s in der Zugriffsliste von %s
	wurde in %d geändert.
CHAN_ACCESS_ADDED
	%s wurde zur %s-Zugriffsliste
	mit Stufe %d hinzugefügt.
CHAN_ACCESS_NO_SUCH_ENTRY
	Kein derartiger Eintrag (#%d) auf der Zugriffsliste von %s.
CHAN_ACCESS_NOT_FOUND
	Der Chatname %s steht nicht auf der Zugriffsliste von %s.
CHAN_ACCESS_NO_MATCH
	Keine passenden Einträge auf der Zugriffsliste von %s.
CHAN_ACCESS_DELETED
	Der Chatname %s wurde von der Zugriffsliste von %s entfernt.
CHAN_ACCESS_DELETED_ONE
	Ein Eintrag aus der Zugriffsliste von %s wurde entfernt. 
CHAN_ACCESS_DELETED_SEVERAL
	%d Einträge aus der Zugriffsliste von %s wurden entfernt.
CHAN_ACCESS_LIST_EMPTY
	Die Zugriffsliste von %s ist leer.
CHAN_ACCESS_LIST_HEADER
	Zugriffsliste von %s:
	  Nr.  St.   Chatname
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s
CHAN_ACCESS_COUNT
	Die Zugriffsliste von %s hat %d Einträge.

# XOP (AOP/SOP/VOP) responses
CHAN_SOP_SYNTAX
	SOP Raum {ADD | DEL | LIST | COUNT} [Chatname | Eintragsliste]
CHAN_AOP_SYNTAX
	AOP Raum {ADD | DEL | LIST | COUNT} [Chatname | Eintragsliste]
CHAN_HOP_SYNTAX
	HOP Raum {ADD | DEL | LIST | COUNT} [Chatname | Eintragsliste]
CHAN_VOP_SYNTAX
	VOP Raum {ADD | DEL | LIST | COUNT} [Chatname | Eintragsliste]
CHAN_XOP_ADDED
	%s wurde zu %s %s-Liste hinzugefügt.
CHAN_XOP_LEVEL_CHANGED
	%s wurde von %s %s-Liste entfernt.
CHAN_XOP_LEVEL_UNCHANGED
	%s ist bereits auf %s %s-Liste.
CHAN_XOP_NICKS_ONLY
	Die SOP-, AOP-, und VOP-Listen können nur
	registrierte Chatnamen enthalten.
CHAN_XOP_NICKS_ONLY_HOP
	Die SOP-, AOP-, HOP-, und VOP-Listen können nur
	registrierte Chatnamen enthalten.
CHAN_XOP_REACHED_LIMIT
	Die AOP-, SOP- oder VOP-Listen können nicht mehr
	als %d Einträge haben.
CHAN_XOP_REACHED_LIMIT_HOP
	Die AOP-, SOP-, HOP- oder VOP-Listen können nicht mehr
	als %d Einträge haben.
CHAN_XOP_NOT_FOUND
	%s wurde in der %s %s-Liste nicht gefunden.
CHAN_XOP_NO_SUCH_ENTRY
	Kein derartiger Eintrag (#%d) in der %s %s-Liste.
CHAN_XOP_NO_MATCH
	Keine passenden Einträge in %s %s-Liste.
CHAN_XOP_DELETED
	%s wurde von der %s %s-Liste entfernt.
CHAN_XOP_DELETED_ONE
	Ein Eintrag vom %s %s-Liste entfernt.
CHAN_XOP_DELETED_SEVERAL
	%d Einträge von %s %s-Liste entfernt.
CHAN_XOP_LIST_EMPTY
	Die %s %s-Liste ist leer.
CHAN_XOP_LIST_HEADER
	%s-Liste für %s:
	  Nr.   Chatname
CHAN_XOP_LIST_FORMAT
	  %3d   %s%s%s%s
CHAN_XOP_COUNT
	%s %s-Liste hat %d Einträge.

# AKICK responses
CHAN_AKICK_SYNTAX
	AKICK Raum {ADD | DEL | LIST | VIEW | ENFORCE | COUNT} [Maske | Liste]
CHAN_AKICK_DISABLED
	Autokick-Listen der Räume können zur Zeit nicht modifiziert werden.
CHAN_AKICK_ALREADY_EXISTS
	Der Eintrag %s ist in der Autokick-Liste
	von %s bereits enthalten.
CHAN_AKICK_REACHED_LIMIT
	In der Autokick-Liste können maximal %d Einträge existieren.
CHAN_AKICK_ADDED
	Der Eintrag %s wurde in die Autokick-Liste von %s eingetragen.
CHAN_AKICK_NO_SUCH_ENTRY
	Kein derartiger Eintrag (#%d) in der Autokick-Liste von %s.
CHAN_AKICK_NOT_FOUND
	Der Eintrag %s steht nicht in der Autokick-Liste von %s.
CHAN_AKICK_NO_MATCH
	Ein passender Eintrag ist in der Autokick-Liste
	von %s nicht zu finden.
CHAN_AKICK_DELETED
	Der Eintrag %s wurde von der Autokick-Liste von %s entfernt.
CHAN_AKICK_DELETED_ONE
	Ein Eintrag wurde von der Autokick-Liste von %s entfernt.
CHAN_AKICK_DELETED_SEVERAL
	%d Einträge sind von der Autokick-Liste von %s entfernt.
CHAN_AKICK_LIST_EMPTY
	Die Autokick-Liste von %s ist leer.
CHAN_AKICK_LIST_HEADER
	Autokick-Liste von %s:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s
CHAN_AKICK_VIEW_FORMAT
	  %3d %s (bei %s)
	    %s
CHAN_AKICK_ENFORCE_DONE
	AKICK ENFORCE für %s beendet; %d Benutzer waren betroffen.
CHAN_AKICK_COUNT
	%s hat %d Einträge in der Autokick-Liste.

# LEVELS responses
CHAN_LEVELS_SYNTAX
	LEVELS Raum {SET | DIS[ABLE] | LIST | RESET} [Einstellung [Stufe]]
CHAN_LEVELS_RANGE
	Die Stufe muß zwischen %d und %d liegen (einschließlich).
CHAN_LEVELS_CHANGED
	Die Stufe für %s im Raum %s wurde in %d geändert.
CHAN_LEVELS_UNKNOWN
	Die Einstellung %s ist unbekannt.
	Geben Sie /msg %s HELP LEVELS DESC
	für eine Liste gültiger Einstellungen ein.
CHAN_LEVELS_DISABLED
	%s wurde im Raum %s ausgeschaltet.
CHAN_LEVELS_LIST_HEADER
	Zugriffsstufen-Einstellungen für Raum %s:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (ausgeschaltet)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (nur für Gründer)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	Die Zugriffsstufen für %s
	wurden auf die Standardwerte zurückgesetzt.

# INFO responses
CHAN_INFO_SYNTAX
	INFO Raum [ALL]
CHAN_INFO_HEADER
	Information über Raum %s:
CHAN_INFO_FOUNDER
	            Gründer: %s (%s)
CHAN_INFO_NO_FOUNDER
	            Gründer: %s
CHAN_INFO_SUCCESSOR
	         Nachfolger: %s (%s)
CHAN_INFO_NO_SUCCESSOR
	         Nachfolger: %s
CHAN_INFO_DESCRIPTION
	       Beschreibung: %s
CHAN_INFO_ENTRYMSG
	Begrüßungsnachricht: %s
CHAN_INFO_TIME_REGGED
	Registrierungsdatum: %s
CHAN_INFO_LAST_USED
	     Letzte Nutzung: %s
CHAN_INFO_LAST_TOPIC
	      Letztes Thema: %s
CHAN_INFO_TOPIC_SET_BY
	  Thema gesetzt von: %s
CHAN_INFO_URL
	                URL: %s
CHAN_INFO_EMAIL
	      Email-Adresse: %s
CHAN_INFO_OPTIONS
	           Optionen: %s
CHAN_INFO_OPT_PRIVATE
	Privat (Mit LIST Befehl unsichtbar)
CHAN_INFO_OPT_KEEPTOPIC
	Beibehaltung des Themas
CHAN_INFO_OPT_TOPICLOCK
	Sperrung des Themas
CHAN_INFO_OPT_SECUREOPS
	Secure Ops
CHAN_INFO_OPT_LEAVEOPS
	Leave Ops
CHAN_INFO_OPT_RESTRICTED
	beschränkter Zugang
CHAN_INFO_OPT_SECURE
	Secure
CHAN_INFO_OPT_OPNOTICE
	Op-Notice
CHAN_INFO_OPT_ENFORCE
	Enforce
CHAN_INFO_OPT_NONE
	Keine
CHAN_INFO_MODE_LOCK
	        Sperr-Modus: %s
CHAN_INFO_NO_EXPIRE
	Dieser Raum wird nicht verfallen.
CHAN_INFO_SUSPEND_DETAILS
	Suspendiert von %s am %s (%s).
CHAN_INFO_SUSPEND_REASON
	Begründung: %s
CHAN_INFO_SHOW_ALL
	/msg %s INFO %s ALL für weitere informationen

# LIST responses
CHAN_LIST_SYNTAX
	LIST Muster
CHAN_LIST_SERVADMIN_SYNTAX
	LIST Muster [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
CHAN_LIST_HEADER
	Liste der zu %s passenden Einträge:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	Ende der Liste - %d/%d Treffer.

# INVITE responses
CHAN_INVITE_SYNTAX
	INVITE Raum
CHAN_INVITE_OK
	Lade %s zum Raum %s ein.

# OP/DEOP/VOICE/DEVOICE responses
CHAN_OPVOICE_SYNTAX
	%s Raum Chatname
CHAN_OP_SUCCEEDED
	%s wurde im Raum %s geopt.
CHAN_OP_FAILED
	Konnte %s im Raum %s nicht oppen.
CHAN_DEOP_SUCCEEDED
	%s wurde im Raum %s gedeopt.
CHAN_DEOP_FAILED
	Konnte %s im Raum %s nicht deoppen.
CHAN_VOICE_SUCCEEDED
	%s erhielt im Raum %s ein Voice.
CHAN_VOICE_FAILED
	Konnte %s im Raum %s kein Voice geben.
CHAN_DEVOICE_SUCCEEDED
	%s verlor im Raum %s das Voice.
CHAN_DEVOICE_FAILED
	Konnte %s im Raum %s nicht devoicen.
CHAN_HALFOP_SUCCEEDED
	%s wurde im Raum %s gehalfopt.
CHAN_HALFOP_FAILED
	Konnte %s im Raum %s nicht halfoppen.
CHAN_DEHALFOP_SUCCEEDED
	%s erhielt im Raum %s ein Halfop.
CHAN_DEHALFOP_FAILED
	Konnte %s im Raum %s nicht dehalfoppen.
CHAN_PROTECT_SUCCEEDED
	%s wurde im Raum %s geprotectet.
CHAN_PROTECT_FAILED
	Konnte %s im Raum %s nicht protecten.
CHAN_DEPROTECT_SUCCEEDED
	%s verlor im Raum %s das Protect.
CHAN_DEPROTECT_FAILED
	Konnte %s im Raum %s nicht deprotecten.

# UNBAN responses
CHAN_UNBAN_SYNTAX
	UNBAN channel
CHAN_UNBANNED
	Ban im Raum %s wurde behoben.

# CLEAR responses
CHAN_CLEAR_SYNTAX
	CLEAR Raum Eintragtyp
CHAN_CLEARED_BANS
	Alle bans (+b) im Raum %s wurden aufbehoben.
CHAN_CLEARED_EXCEPTIONS
	Alle exceptions im Raum %s wurden zurückgesetzt.
CHAN_CLEARED_MODES
	Alle Modi (+ovbntispklm) im Raum %s wurden zurückgesetzt.
CHAN_CLEARED_OPS
	Der Modus +o im Raum %s wurde entfernt (massdeop).
CHAN_CLEARED_HALFOPS
	Der Modus +h im Raum %s wurden entfernt.
CHAN_CLEARED_VOICES
	Der Modus +v im Raum %s wurden entfernt (massdevoice).
CHAN_CLEARED_USERS
	Alle Benutzer wurden aus dem Raum %s gekickt (masskick).

# GETPASS responses
CHAN_GETPASS_SYNTAX
	GETPASS Raum
CHAN_GETPASS_UNAVAILABLE
	Aufgrund der Nutzung von Verschlüsselung
	ist der GETPASS-Befehl ist nicht verfügbar.
CHAN_GETPASS_PASSWORD_IS
	Das Passwort für Raum %s lautet %s.

# FORBID responses
CHAN_FORBID_SYNTAX
	FORBID Raum
CHAN_FORBID_SUCCEEDED
	Der Zugang zu Raum %s ist ab sofort verboten.
CHAN_FORBID_FAILED
	Der Zugang zu Raum %s kann nicht verboten werden!

# SUSPEND responses
CHAN_SUSPEND_SYNTAX
	SUSPEND [+Dauer] Raum Grund
CHAN_SUSPEND_SUCCEEDED
	Der Raum %s wurde suspendiert.
CHAN_SUSPEND_ALREADY_SUSPENDED
	Der Raum %s ist bereits suspendiert.

# UNSUSPEND responses
CHAN_UNSUSPEND_SYNTAX
	UNSUSPEND Raum
CHAN_UNSUSPEND_SUCCEEDED
	Suspend von %s ist jetzt aufgehoben.
CHAN_SUSPEND_NOT_SUSPENDED
	Der Raum %s ist nicht suspendiert.

###########################################################################
#
# MemoServ messages
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	Sie haben ein neues Memo.
MEMO_HAVE_NEW_MEMOS
	Sie haben %d neue Memos.
MEMO_TYPE_READ_LAST
	Zum Lesen /msg %s READ LAST eingeben.
MEMO_TYPE_READ_NUM
	Zum Lesen /msg %s READ %d eingeben.
MEMO_TYPE_LIST_NEW
	Zum auflisten /msg %s LIST NEW eingeben.
MEMO_AT_LIMIT
	Warnung: Sie haben Ihr Limit an Memos erreicht (%d).
	Sie werden keine weiteren Memos empfangen können,
	solange Sie nicht einige Ihrer alten löschen.
MEMO_OVER_LIMIT
	Warnung: Sie haben Ihr Limit an Memos überschritten (%d).
	Sie werden keine weiteren Memos empfangen können,
	solange Sie nicht einige Ihrer alten löschen.
MEMO_NEW_MEMO_ARRIVED
	Sie haben ein neues Memo von %s.
	Zum Lesen /msg %s READ %d eingeben.

# Multi-use responses
MEMO_HAVE_NO_MEMOS
	Sie haben keine Memos.
MEMO_X_HAS_NO_MEMOS
	%s hat keine Memos.
MEMO_DOES_NOT_EXIST
	Memo %d existiert nicht!
MEMO_LIST_NOT_FOUND
	Es wurde kein zutreffendes Memo gefunden.

# SEND responses
MEMO_SEND_SYNTAX
	SEND {chatname | Raum} Memo-Text
MEMO_SEND_DISABLED
	Das Versenden von Memos ist temporär nicht verfügbar.
MEMO_SEND_PLEASE_WAIT
	Bitte warten Sie %d Sekunden,
	bevor Sie den SEND-Befehl erneut benutzen.
MEMO_X_GETS_NO_MEMOS
	%s kann keine Memos empfangen.
MEMO_X_HAS_TOO_MANY_MEMOS
	%s hat momentan zu viele Memos
	und kann daher keine weiteren empfangen.
MEMO_SENT
	Memo wurde an %s gesendet.

# LIST responses
MEMO_LIST_SYNTAX
	LIST [Raum] [Liste | NEW]
MEMO_HAVE_NO_NEW_MEMOS
	Sie haben keine neuen Memos.
MEMO_X_HAS_NO_NEW_MEMOS
	%s hat keine neuen Memos.
MEMO_LIST_MEMOS
	Memos für %s.
	Zum Lesen /msg %s READ Nummer eingeben.
MEMO_LIST_NEW_MEMOS
	Neue Memos für %s.
	Zum Lesen /msg %s READ Nummer eingeben.
MEMO_LIST_CHAN_MEMOS
	Memos für %s.
	Zum Lesen /msg %s READ %s Nummer eingeben.
MEMO_LIST_CHAN_NEW_MEMOS
	Neue Memos für %s.
	Zum Lesen /msg %s READ %s Nummer eingeben.
MEMO_LIST_HEADER
	 Nummer  Sender            Datum/Uhrzeit
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_READ_SYNTAX
	READ [Raum] {Liste | LAST | NEW}
MEMO_HEADER
	Memo %d von %s (%s).
	Zum Löschen /msg %s DEL %d eingeben.
MEMO_CHAN_HEADER
	Memo %d von %s (%s).
	Zum Löschen /msg %s DEL %s %d eingeben.
MEMO_TEXT
	%s

# DEL responses
MEMO_DEL_SYNTAX
	DEL [Raum] {Nummer | Liste | ALL}
MEMO_DELETED_NONE
	Es wurden keine Memos gelöscht.
MEMO_DELETED_ONE
	Memo %d wurde gelöscht.
MEMO_DELETED_SEVERAL
	%d Memos wurden gelöscht.
MEMO_DELETED_ALL
	Alle Memos wurden gelöscht.

# SET responses
MEMO_SET_SYNTAX
	SET Option Parameter
MEMO_SET_DISABLED
	Der MemoServ SET-Befehl ist temporär nicht verfügbar.
MEMO_SET_UNKNOWN_OPTION
	Unbekannte SET-Option %s.

# SET NOTIFY responses
MEMO_SET_NOTIFY_SYNTAX
	SET NOTIFY {ON | LOGON | NEW | OFF}
MEMO_SET_NOTIFY_ON
	%s wird Sie beim Anmelden über Memos benachrichtigen.
	Desweiteren bekommen Sie bei jeder eingehenden Memo
	eine Benachrichtigung.
MEMO_SET_NOTIFY_LOGON
	%s wird Sie beim Anmelden über Memos benachrichtigen.
	Desweiteren bekommen Sie bei jeder eingehenden Memo
	eine Benachrichtigung, sofern Ihr Status nicht /AWAY ist.
MEMO_SET_NOTIFY_NEW
	%s wird Sie jetzt benachrichtigen,
	wenn Ihnen Memos geschickt wurden.
MEMO_SET_NOTIFY_OFF
	%s wird Ihnen keine Memo-Benachrichtigungen schicken.

# SET LIMIT responses
MEMO_SET_LIMIT_SYNTAX
	SET LIMIT [Raum] Limit
MEMO_SET_LIMIT_SERVADMIN_SYNTAX
	SET LIMIT [Chatname | Raum] {Limit | NONE} [HARD]
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	Sie dürfen Ihr Memo-Limit nicht ändern.
MEMO_SET_LIMIT_FORBIDDEN
	Das Memo-Limit für %s darf nicht geändert werden.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	Sie können Ihr Memo-Limit nicht größer als %d setzen.
MEMO_SET_LIMIT_TOO_HIGH
	Sie können das Memo-Limit für %s größer als %d setzen.
MEMO_SET_LIMIT_OVERFLOW
	Das Memo-Limit ist zu groß;
	es wird statt dessen auf %d begrenzt.
MEMO_SET_YOUR_LIMIT
	Ihr Memo-Limit wurde auf %d gesetzt.
MEMO_SET_YOUR_LIMIT_ZERO
	Sie können keine Memos mehr empfangen (Memo-Limit = 0).
MEMO_UNSET_YOUR_LIMIT
	Ihr Memo-Limit wurde ausgeschaltet.
MEMO_SET_LIMIT
	Das Memo-Limit für %s wurde auf %d gesetzt.
MEMO_SET_LIMIT_ZERO
	Das Memo-Limit für %s wurde auf 0 gesetzt.
MEMO_UNSET_LIMIT
	Das Memo-Limit für %s wurde ausgeschaltet.

# INFO responses
MEMO_INFO_SYNTAX
	INFO [Raum]
MEMO_INFO_SERVADMIN_SYNTAX
	INFO [Chatname | Raum]
MEMO_INFO_NO_MEMOS
	Momentan haben Sie keine Memos.
MEMO_INFO_MEMO
	Momentan haben Sie 1 Memo.
MEMO_INFO_MEMO_UNREAD
	Momentan haben Sie 1 ungelesenes Memo.
MEMO_INFO_MEMOS
	Momentan haben Sie %d Memos.
MEMO_INFO_MEMOS_ONE_UNREAD
	Momentan haben Sie %d Memos (1 ungelesenes).
MEMO_INFO_MEMOS_SOME_UNREAD
	Momentan haben Sie %d Memos (%d ungelesene).
MEMO_INFO_MEMOS_ALL_UNREAD
	Momentan haben Sie %d Memos (alle ungelesen).
MEMO_INFO_LIMIT
	Ihr Memo-Limit ist %d.
MEMO_INFO_HARD_LIMIT
	Ihr Memo-Limit ist %d, es darf nicht geändert werden.
MEMO_INFO_LIMIT_ZERO
	Ihr Memo-Limit ist 0;
	Sie werden keine neuen Memos empfangen können.
MEMO_INFO_HARD_LIMIT_ZERO
	Ihr Memo-Limit ist 0;
	Sie werden keine neuen Memos empfangen können.
MEMO_INFO_NO_LIMIT
	Sie haben kein Limit für die Anzahl Ihrer Memos.
MEMO_INFO_NOTIFY_OFF
	Sie werden über neue Memos nicht informiert.
MEMO_INFO_NOTIFY_ON
	Sie werden beim Anmelden über neue Memos benachrichtigt.
	Desweiteren bekommen Sie bei jedem eingehenden Memo
	eine Benachrichtigung.
MEMO_INFO_NOTIFY_RECEIVE
	Sie bekommen bei jedem eingehenden Memo
	eine Benachrichtigung.
MEMO_INFO_NOTIFY_SIGNON
	Sie werden beim Anmelden über neue Memos benachrichtigt.
MEMO_INFO_X_NO_MEMOS
	%s hat keine Memos.
MEMO_INFO_X_MEMO
	%s hat 1 Memo.
MEMO_INFO_X_MEMO_UNREAD
	%s hat 1 nicht gelesenes Memo.
MEMO_INFO_X_MEMOS
	%s hat %d nicht gelesene Memos.
MEMO_INFO_X_MEMOS_ONE_UNREAD
	%s hat %d Memos (1 ungelesenes).
MEMO_INFO_X_MEMOS_SOME_UNREAD
	%s hat %d Memos (%d ungelesene).
MEMO_INFO_X_MEMOS_ALL_UNREAD
	%s hat %d Memos (alle ungelesen).
MEMO_INFO_X_LIMIT
	Memo-Limit von %s: %d.
MEMO_INFO_X_HARD_LIMIT
	Memo-Limit von %s: %d.
MEMO_INFO_X_NO_LIMIT
	%s hat kein Memo-Limit.
MEMO_INFO_X_NOTIFY_OFF
	%s wird über neue Memos nicht informiert.
MEMO_INFO_X_NOTIFY_ON
	%s wird beim Anmelden über neue Memos benachrichtigt.
	Desweiteren bei jedem eingehenden Memo.
MEMO_INFO_X_NOTIFY_RECEIVE
	%s wird überbei jedem eingehenden Memo benachrichtigt.
MEMO_INFO_X_NOTIFY_SIGNON
	%s wird beim Anmelden über neue Memos benachrichtigt.

###########################################################################
#
# OperServ messages
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	Services kann keine Modi setzen, sind Ihre Servers richtig konfiguriert?
OPER_BOUNCY_MODES_U_LINE
	Services kann keine Modi setzen, überprüfen Sie die U-Lines der Servers.
OPER_SKELETON_MODE
	Diese Funktion steht in diesem Modus nicht zur Verfügung. (Skeleton)

# GLOBAL responses
OPER_GLOBAL_SYNTAX
	GLOBAL Nachricht

# STATS responses
OPER_STATS_UNKNOWN_OPTION
	Unbekannte STATS-Option %s.
OPER_STATS_RESET_USER_COUNT
	Die maximale Anzahl der Benutzer ist zurückgesetzt.
OPER_STATS_CURRENT_USERS
	Momentane Benutzer: %d (%d ops)
OPER_STATS_MAX_USERS
	Maximum an Benutzern: %d (%s)
OPER_STATS_UPTIME_DHMS
	Services up %d %s, %02d:%02d
# If >= 1 hour, hours and minutes; if < 1 hour, minutes and seconds
OPER_STATS_UPTIME_HM_MS
	Services up %d %s, %d %s
OPER_STATS_BYTES_READ
	Bytes gelesen: %5d kB
OPER_STATS_BYTES_WRITTEN
	Bytes geschrieben: %5d kB
OPER_STATS_USER_MEM
	Benutzer : %6d Datensätze, %5d kB
OPER_STATS_SERVER_MEM
	Server   : %6d Datensätze, %5d kB
OPER_STATS_CHANNEL_MEM
	Räume    : %6d Datensätze, %5d kB
OPER_STATS_NICKSERV_MEM
	NickServ : %6d Datensätze, %5d kB
OPER_STATS_CHANSERV_MEM
	ChanServ : %6d Datensätze, %5d kB
OPER_STATS_MEMOSERV_MEM
	MemoServ : %6d Datensätze, %5d kB
OPER_STATS_STATSERV_MEM
	StatServ : %6d Datensätze, %5d kB
OPER_STATS_OPERSERV_MEM
	OperServ : %6d Datensätze, %5d kB
OPER_STATS_AKILL_COUNT
	Anzahl der Autokills : %d
OPER_STATS_AKILL_EXPIRE_DAYS
	Normale Gültigkeitsdauer von Autokills: %d Tage
OPER_STATS_AKILL_EXPIRE_DAY
	Normale Gültigkeitsdauer von Autokills: 1 Tag
OPER_STATS_AKILL_EXPIRE_HOURS
	Normale Gültigkeitsdauer von Autokills: %d Stunden
OPER_STATS_AKILL_EXPIRE_HOUR
	Normale Gültigkeitsdauer von Autokills: 1 Stunde
OPER_STATS_AKILL_EXPIRE_MINS
	Normale Gültigkeitsdauer von Autokills: %d Minuten
OPER_STATS_AKILL_EXPIRE_MIN
	Normale Gültigkeitsdauer von Autokills: 1 Minute
OPER_STATS_AKILL_EXPIRE_NONE
	Normale Gültigkeitsdauer von Autokills: Keine
OPER_STATS_SESSIONS_MEM
	Sitzungen: %6d Datensätze, %5d kB

# MODE responses
OPER_MODE_SYNTAX
	MODE Raum Modi

# CLEARMODES responses
OPER_CLEARMODES_SYNTAX
	CLEARMODES Raum [ALL]
OPER_CLEARMODES_DONE
	Alle Modi und Bans im Raum %s wurden entfernt.
OPER_CLEARMODES_ALL_DONE
	Alle Modi im Raum %s wurden entfernt.

# CLEARCHAN responses
OPER_CLEARCHAN_SYNTAX
	CLEARCHAN Raum
OPER_CLEARCHAN_DONE
	Alle Benutzer wurden aus dem Raum %s gekickt (masskick).

# KICK responses
OPER_KICK_SYNTAX
	KICK Raum Benutzer Grund

# ADMIN responses
OPER_ADMIN_SYNTAX
	ADMIN {ADD | DEL | LIST} [Chatname]
OPER_ADMIN_ADD_SYNTAX
	ADMIN ADD Chatname
OPER_ADMIN_DEL_SYNTAX
	ADMIN DEL Chatname
OPER_ADMIN_SKELETON
	Im Skeleton-Modus ist kein ADMIN Befehl verfügbar.
OPER_ADMIN_EXISTS
	%s steht bereits in der Services-Adminliste.
OPER_ADMIN_ADDED
	%s wurde zur Services-Adminliste hinzugefügt.
OPER_ADMIN_TOO_MANY
	Zu viele Einträge (%d) in der Services-Adminliste;
	weitere können nicht hinzugefügt werden.
OPER_ADMIN_REMOVED
	%s wurde aus der Services-Adminliste herausgenommen.
OPER_ADMIN_NOT_FOUND
	%s wurde in der Services-Adminliste nicht gefunden.
OPER_ADMIN_LIST_HEADER
	Services-Adminliste:

# OPER responses
OPER_OPER_SYNTAX
	OPER {ADD | DEL | LIST} [Chatname]
OPER_OPER_ADD_SYNTAX
	OPER ADD Chatname
OPER_OPER_DEL_SYNTAX
	OPER DEL Chatname
OPER_OPER_SKELETON
	Im Skeleton-Modus ist kein OPER Befehl verfügbar.
OPER_OPER_EXISTS
	%s steht bereits in der Services-Operatorenliste.
OPER_OPER_ADDED
	%s wurde zur Services-Operatorenliste hinzugefügt.
OPER_OPER_TOO_MANY
	Zu viele Einträge (%d) in der Services-Operatorenliste;
	weitere können nicht hinzugefügt werden.
OPER_OPER_REMOVED
	%s wurde aus der Services-Operatorenliste herausgenommen.
OPER_OPER_NOT_FOUND
	%s wurde in der Services-Operatorenliste nicht gefunden.
OPER_OPER_LIST_HEADER
	Services-Operatorenliste:
	
# AKILL responses
OPER_AKILL_SYNTAX
	AKILL {ADD | DEL | LIST | VIEW | COUNT} [[+Dauer] Maske [Grund]]
OPER_AKILL_ADD_SYNTAX
	AKILL ADD [+Dauer] Maske Grund
OPER_AKILL_DEL_SYNTAX
	AKILL DEL Maske
OPER_TOO_MANY_AKILLS
	Die Autokill Liste ist voll!
OPER_AKILL_EXISTS
	%s gibt es bereits.
OPER_AKILL_NO_NICK
	Errinnerung: Autokill Masken können keine NICKs enthalten.
OPER_AKILL_MASK_TOO_GENERAL
	Die Maske ist zu allgemein.
OPER_AKILL_ADDED
	%s wurde in die AKILL-Liste eingetragen.
OPER_AKILL_REMOVED
	%s wurde von der AKILL-Liste gelöscht.
OPER_AKILL_NOT_FOUND
	%s wurde in der AKILL-Liste nicht gefunden.
OPER_AKILL_LIST_HEADER
	Derzeitige AKILL-Liste:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, reason
OPER_AKILL_VIEW_FORMAT
	%s (von %s am %s; %s)
	    %s
OPER_AKILL_COUNT
	Es gibt %d Einträge in der AKILL-Liste.

# SU responses
OPER_SU_SYNTAX
	SU Passwort
OPER_SU_NO_PASSWORD
	Der SU-Befehl kann nicht ausgeführt werden,
	kein SU Passwort wurde gesetzt.
OPER_SU_SUCCEEDED
	Sie haben jetzt Services-Root Rechte.
OPER_SU_FAILED
	Kann das Passwort nicht verifizieren.

# SET responses
OPER_SET_SYNTAX
	SET Option Setting
OPER_SET_IGNORE_ON
	Ignore AKTIV.
OPER_SET_IGNORE_OFF
	Ignore INAKTIV.
OPER_SET_IGNORE_ERROR
	IGNORE sollte entweder ON oder OFF sein.
OPER_SET_READONLY_ON
	Services momentan im read-only-Modus.
OPER_SET_READONLY_OFF
	Services momentan im read-write-Modus.
OPER_SET_READONLY_ERROR
	READONLY sollte entweder ON oder OFF sein.
OPER_SET_DEBUG_ON
	Services momentan im Debug-Modus.
OPER_SET_DEBUG_OFF
	Services momentan nicht im Debug-Modus.
OPER_SET_DEBUG_LEVEL
	Services momentan im Debug-Modus (Level %d).
OPER_SET_DEBUG_ERROR
	DEBUG sollte entweder ON, OFF oder eine postive Zahl sein.
OPER_SET_SUPASS_FAILED
	Kann das SU-Passwort der Services nicht setzen.
OPER_SET_SUPASS_OK
	Das SU-Passwort der Services wurde gesetzt.
OPER_SET_SUPASS_NONE
	Das SU-Passwort der Services wurde deaktiviert.
OPER_SET_UNKNOWN_OPTION
	Unbekannte Option %s.

# JUPE responses
OPER_JUPE_SYNTAX
	JUPE ServerName [Grund]

# RAW responses
OPER_RAW_SYNTAX
	RAW Text

# UPDATE responses
OPER_UPDATING
	Datenbank wird aktualisiert.

# RESTART responses

# LISTIGNORE responses
OPER_IGNORE_LIST
	Services Ignore-Liste:
OPER_IGNORE_LIST_EMPTY
	Ignore-Liste ist leer.

# KILLCLONES responses
OPER_KILLCLONES_SYNTAX
	KILLCLONES Chatname
OPER_KILLCLONES_UNKNOWN_NICK
	Could not find user %s.

###########################################################################
#
# Session Limiting and Exception messages
#
###########################################################################

# EXCEPTION responses
OPER_EXCEPTION_SYNTAX
	EXCEPTION {ADD | DEL | MOVE | LIST | VIEW} [Param]
OPER_EXCEPTION_ADD_SYNTAX
	EXCEPTION ADD [+Dauer] Maske Limit Grund
OPER_EXCEPTION_DEL_SYNTAX
	EXCEPTION DEL {Maske | Liste}
OPER_EXCEPTION_MOVE_SYNTAX
	EXCEPTION MOVE Nummer Position
OPER_EXCEPTION_DISABLED
	Sitzungslimit-Option ist inaktiv.
OPER_EXCEPTION_ALREADY_PRESENT
	Mask %s ist schon in der Ausnahme Liste eingetragen.
OPER_EXCEPTION_TOO_MANY
	Ausnahme-Liste ist voll.
OPER_EXCEPTION_ADDED
	Sitzungs Limit für %s auf %d gesetzt.
OPER_EXCEPTION_MOVED
	Ausnahme für %s (#%d) wurde auf Position %d
	geschoben.
OPER_EXCEPTION_NO_SUCH_ENTRY
	Der Eintrag (#%d) konnte in der Sitzung-Limit-Liste
	nicht gefunden werden.
OPER_EXCEPTION_NOT_FOUND
	%s konnte in der Sitzungs-Limit-Liste nicht gefunden werden.
OPER_EXCEPTION_NO_MATCH
	Keine passenden Einträge in der Ausnahme-Liste
OPER_EXCEPTION_DELETED
	%s wurde aus der Ausnahme-Liste gelöscht.
OPER_EXCEPTION_DELETED_ONE
	Ein Eintrag wurde aus der Ausnahme-Liste gelöscht.
OPER_EXCEPTION_DELETED_SEVERAL
	%d Einträge wurden aus der Ausnahme-Liste gelöscht.
OPER_EXCEPTION_LIST_HEADER
	Derzeitige Sitzungslimit Ausnahmen-Liste:
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
	Falsche Limitangabe. Limit muß eine Zahl
	grössergleich Null und kleiner %d sein.
OPER_EXCEPTION_INVALID_HOSTMASK
	Falsche Hostmaske. Nur reale Hostmasken werden
	als gültige Ausnahmen behandelt, keine
	UserID oder Chatnamen.

# SESSION responses
OPER_SESSION_SYNTAX
	SESSION {LIST Limit | VIEW Host}
OPER_SESSION_LIST_SYNTAX
	SESSION LIST Limit
OPER_SESSION_VIEW_SYNTAX
	SESSION VIEW Host
OPER_SESSION_DISABLED
	Sitzungs-Limit-Option ist inaktiv.
OPER_SESSION_INVALID_THRESHOLD
	Der Eintrag muß grösser 1 sein.
OPER_SESSION_NOT_FOUND
	%s wurde in der Sitzungsliste nicht gefunden.
OPER_SESSION_LIST_HEADER
	Hosts mit mindestens %d Sitzungen:
OPER_SESSION_LIST_COLHEAD
	Sitzungen  Host
# limit, host
OPER_SESSION_LIST_FORMAT
	%6d    %s
# host, sessions, limit
OPER_SESSION_VIEW_FORMAT
	Der Host %s hat momentan %d Sitzungen
	mit einem Limit von %d.


###########################################################################
#
# StatServ messages
#
############################################################################

# General SERVERS responses
STAT_SERVERS_REMOVE_SERV_FIRST
	Server %s ist online. Entfernen Sie es, und versuchen dann erneut.
STAT_SERVERS_SERVER_EXISTS
	Server %s existiert bereits.

# SERVERS command syntax
STAT_SERVERS_SYNTAX
	SERVERS Option Parameter

# STATS responses
STAT_SERVERS_STATS_TOTAL
	 Server gesamt: %2d
STAT_SERVERS_STATS_ON_OFFLINE
	        Online: %2d (%d%%)  Offline: %2d (%d%%)
STAT_SERVERS_LASTQUIT_WAS
	  Letzter Quit: %-30s  

# LIST responses
STAT_SERVERS_LIST_HEADER
	Server Name                    Users      Opers
STAT_SERVERS_LIST_RESULTS
	Ende der Liste -- %d von %d Server wurden angezeigt.

# VIEW responses
STAT_SERVERS_VIEW_HEADER_ONLINE
	%-30s  (online)
STAT_SERVERS_VIEW_HEADER_OFFLINE
	%-30s  (offline)
STAT_SERVERS_VIEW_LASTJOIN
	  Letzter Join: %s
STAT_SERVERS_VIEW_LASTQUIT
	  Letzter Quit: %s
STAT_SERVERS_VIEW_QUITMSG
	Quit-Nachricht: %s
STAT_SERVERS_VIEW_USERS_OPERS
	        Users: %3d (%2d%%)  Opers: %3d (%2d%%)
STAT_SERVERS_VIEW_RESULTS
	Ende der Liste -- %d von %d Server wurden angezeigt.

# DELETE responses
STAT_SERVERS_DELETE_SYNTAX
	SERVERS DELETE Server
STAT_SERVERS_DELETE_DONE
	Statistiken für %s sind gelöscht.

# COPY responses
STAT_SERVERS_COPY_SYNTAX
	SERVERS COPY Server NeuerName
STAT_SERVERS_COPY_DONE
	Statistiken für %s sind auf %s kopiert.

# RENAME responses
STAT_SERVERS_RENAME_SYNTAX
	SERVERS RENAME Server NeuerName
STAT_SERVERS_RENAME_DONE
	Statistiken für server %s sind zu %s umbenannt.

# USERS responses
STAT_USERS_SYNTAX
	USERS Option Parameter

###########################################################################
#
# News system messages
#
###########################################################################

NEWS_LOGON_TEXT
	[Nachrichten - %s] %s
NEWS_OPER_TEXT
	[Oper Nachrichten - %s] %s

NEWS_LOGON_SYNTAX
	LOGONNEWS {ADD|DEL|LIST} [Text|Nummer]
NEWS_LOGON_LIST_HEADER
	Logon-News-Einträge:
NEWS_LOGON_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_LOGON_LIST_NONE
	Keine Logon-Nachrichten.
NEWS_LOGON_ADD_SYNTAX
	LOGONNEWS ADD Text
NEWS_LOGON_ADD_FULL
	Logon-Nachrichtenliste ist voll!
NEWS_LOGON_ADDED
	Neue Logon-Nachricht eingetragen (#%d).
NEWS_LOGON_DEL_SYNTAX
	LOGONNEWS DEL {Nummer | ALL}
NEWS_LOGON_DEL_NOT_FOUND
	Logon-Nachricht #%d konnte nicht gefunden werden!
NEWS_LOGON_DELETED
	Logon-Nachricht #%d wurde gelöscht.
NEWS_LOGON_DEL_NONE
	Keine Logon-Nachrichten zum Löschen sind da!
NEWS_LOGON_DELETED_ALL
	Alle Nachrichten sind gelöscht.

NEWS_OPER_SYNTAX
	OPERNEWS {ADD|DEL|LIST} [Text|Nummer]
NEWS_OPER_LIST_HEADER
	Oper-News-Nachrichten:
NEWS_OPER_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_OPER_LIST_NONE
	Keine Oper-News-Nachrichten.
NEWS_OPER_ADD_SYNTAX
	OPERNEWS ADD Text
NEWS_OPER_ADD_FULL
	Oper-News-Nachrichtenliste ist voll!
NEWS_OPER_ADDED
	Neue Oper-News-Nachricht eingetragen (#%d).
NEWS_OPER_DEL_SYNTAX
	OPERNEWS DEL {Nummer | ALL}
NEWS_OPER_DEL_NOT_FOUND
	Oper Oper-News-Nachricht #%d konnte nicht gefunden werden!
NEWS_OPER_DELETED
	Oper Oper-News-Nachricht #%d wurde gelöscht.
NEWS_OPER_DEL_NONE
	Keine Oper-News-Nachrichten zum löschen!
NEWS_OPER_DELETED_ALL
	Alle Oper-News-Nachrichten sind gelöscht.

NEWS_HELP_LOGON
	Syntax: LOGONNEWS ADD Text
	        LOGONNEWS DEL {Nummer | ALL}
	        LOGONNEWS LIST
	
	Bearbeitet die Liste der Logon-Nachrichten. Wenn ein Benutzer
	sich mit dem Server verbindet, werden diese Nachrichten an ihm
	geschickt.  (Um ein Flood zu vermeiden werden nicht mehr als
	3 Nachrichten geleichzeitig geschickt: wenn es mehr als 3
	Nachrichten gibt, werden nur die neuesten 3 geschickt.)
	
	LOGONNEWS LIST kann jeder Oper benutzen, um die Nachrichten zu
	sehen, ADD und DEL können nur die Services-Admins benutzen.
	
NEWS_HELP_OPER
	Syntax: OPERNEWS ADD Text
	        OPERNEWS DEL {Nummer | ALL}
	        OPERNEWS LIST
	
	Bearbeitet die Liste der Oper-Nachrichten. Wenn ein Benutzer 
	Oper wird (per /oper), erhält er dann diese Nachrichten.
	(Um ein Flood zu vermeiden werden nicht mehr als 3 Nachrichten
	geleichzeitig geschick:, wenn es mehr als 3 Nachrichten gibt, 
	werden nur die neuesten 3 geschickt.)
	
	OPERNEWS LIST kann jeder Oper benutzen, um die Nachrichten zu
	sehen, ADD und DEL können nur die Services-Admins benutzen.

###########################################################################
#
# NickServ help messages
#
###########################################################################

NICK_HELP
	%S ermöglicht es Ihnen einen Chatnamen zu registrieren,
	so daß es für andere unmöglich wird, diesen Chatnamen zu benutzen.
	Wenn ein Chatname %d Tage nicht benutzt wird, dann wird der
	Eintrag gelöscht. Die Registrierung verfällt somit und der Chatname
	wird für andere wieder frei.
	Die folgenden Befehle sind für die die Registrierung und
	Verwaltung der Chatnamen: /msg %S Befehl.
	/msg %S HELP Befehl für weitere Informationen zu
	einem bestimmten Befehl.
	
	    REGISTER   Zum Registrieren des aktuellen Chatnames.
	    IDENTIFY   Zur Identifizierung des Chatnames.
	    ACCESS     Zum Bearbeiten der Zugriffsliste des Chatnames.
	    LINK       Um einen Link zu einem anderen Chatnamen zu machen.
	    SET        Verschiedene Optionen werden gesetzt.
	    DROP       Zum Löschen des Chatnamens.
	    RECOVER    Entfernt unbefugte Personen die Ihren Chatname benutzen.
	    RELEASE    Gibt Chatnames frei nach RECOVER.	
	
	Andere Befehle: UNLINK, GHOST, INFO, LIST, STATUS, LISTCHANS, UNSET
	
	WICHTIG: %S Ist nur dazu da, daß es im IRC einen gewissen Schutz
	für Identität der Personen zu gewährleisten. Es ist nicht dazu da, 
	daß man andere Leute die Chatnames stiehlt. %S darf nicht für andere 
	Zwecke benutzt werden, und falls so etwas entdeckt werden sollte, 
	kann es dazu führen, daß Chatnames und Räume unter Ihrem Namen 
	verboten werden.

NICK_HELP_EXPIRE_ZERO
	%S ermöglicht es Ihnen einen Chatnamen zu registrieren,
	so daß es für andere unmöglich wird, diesen Chatnamen zu benutzen.
	Die folgenden Befehle sind für die die Registrierung und
	Verwaltung der Chatnamen: /msg %S Befehl.
	/msg %S HELP Befehl für weitere Informationen zu
	einem bestimmten Befehl.
	
	    REGISTER   Zum Registrieren des aktuellen Chatnames.
	    IDENTIFY   Zur Identifizierung des Chatnames.
	    ACCESS     Zum Bearbeiten der Zugriffsliste des Chatnames.
	    LINK       Um einen Link zu einem anderen Chatnamen zu machen.
	    SET        Verschiedene Optionen werden gesetzt.
	    DROP       Zum Löschen des Chatnamens.
	    RECOVER    Entfernt unbefugte Personen die Ihren Chatname benutzen.
	    RELEASE    Gibt Chatnames frei nach RECOVER.	
	
	Andere Befehle: UNLINK, GHOST, INFO, LIST, STATUS, LISTCHANS, UNSET
	
	WICHTIG: %S Ist nur dazu da, daß es im IRC einen gewissen Schutz
	für Identität der Personen zu gewährleisten. Es ist nicht dazu da, 
	daß man andere Leute die Chatnames stiehlt. %S darf nicht für andere 
	Zwecke benutzt werden, und falls so etwas entdeckt werden sollte, 
	kann es dazu führen, daß Chatnames und Räume unter Ihrem Namen 
	verboten werden.

NICK_HELP_REGISTER
	Syntax: REGISTER Passwort [Email]
	
	Der Chatname wird in die %S-Datenbank eingetragen. Danach können
	Sie mit den Befehlen SET und ACCESS Ihre eigenen Optionen
	bestimmen. Das Passwort, das Sie beim Registrieren benutzt haben,
	sollte nicht vergessen werden. Auch zu beachten ist die Groß- und
	Kleinschreibung.

	Sie können eine Emailadresse angeben, wenn Sie den Chatnamen
	registrieren. Mit dem Befehl SET HIDE können Sie verhindern,
	daß diese Emailadresse von anderen gelesen wird. Mit dem Befehl
	SET EMAIL können Sie die Emailadresse später setzen.
	/msg %S HELP SET HIDE für weitere Informationen.

	Vorschläge für das Passwort:
	
	Beim Wählen eines Passwortes ist davon abzuraten, ein leicht
	auszudenkendes Passwort zu benutzen. Kürzere Passwörter sind auch
	nicht gut geeignet. Ein gutes Passwort enthält mindestens 5
	Buchstaben und es ist auch zu empfehlen, Ziffer im Passwort zu
	benutzen.

NICK_HELP_REGISTER_REQ_EMAIL
	Syntax: REGISTER Passwort Email
	
	Der Chatname wird in der %S-Datenbank eingetragen. Danach können
	Sie mit den Befehlen SET und ACCESS Ihre eigenen Optionen
	bestimmen. Das Passwort, das Sie beim Registrieren benutzt haben,
	sollte nicht vergessen werden. Auch zu beachten ist die Groß- und
	Kleinschreibung.

	Sie können eine Emailadresse angeben, wenn Sie den Chatnamen
	registrieren. Mit dem Befehl SET HIDE können Sie verhindern,
	daß diese Emailadresse von anderen gelesen wird. Mit dem Befehl
	SET EMAIL können Sie die Emailadresse später setzen.
	/msg %S HELP SET HIDE für weitere Informationen.

	Vorschläge für das Passwort:
	
	Beim Wählen eines Passwortes ist davon abzuraten, ein leicht
	auszudenkendes Passwort zu benutzen. Kürzere Passwörter sind auch
	nicht gut geeignet. Ein gutes Passwort enthält mindestens 5
	Buchstaben und es ist auch zu empfehlen, Ziffer im Passwort zu
	benutzen.


NICK_HELP_IDENTIFY
	Syntax: IDENTIFY Passwort
	
	Dieser Befehl ermöglicht es Ihnen, daß Sie vom %S erkannt
	werden. Es ist unbedingt erforderlich, um weitere Befehle zu
	benutzen. Das Passwort ist das Passwort, das Sie beim 
	Registrieren mit REGISTER benutzt haben.

NICK_HELP_DROP
	Syntax: DROP
	
	Ihr Chatname wird aus der %S-Datenbank gelöscht. Der Chatname
	wird für andere frei. Um diesen Befehl zu benutzen müssen Sie
	sich identifiziert haben.
	/msg %S HELP IDENTIFY für weitere Informationen.

NICK_HELP_ACCESS
	Syntax: ACCESS ADD Maske
	        ACCESS DEL Maske
	        ACCESS LIST
	
	Die Zugriffsliste für den Chatnamen wird mit diesen Befehlen
	bearbeitet. Diese sind die Adressen, welche vom %S automatisch
	erkannt werden. Falls sie sich von einer anderen Adresse verbinden,
	wird von Ihnen verlangt, den  IDENTIFY-Befehl zu benutzen. 
	
	Beispiele:
	
	    ACCESS ADD time@*.ira.uka.de
	      Der User time wird von allen Domänen unter
	      uni-karlsruhe.de anerkannt.
	
	    ACCESS DEL time@*.ira.uka.de
	        Das vorherige Befehl wird rückgängig gemacht.
	
	    ACCESS LIST
	        Die aktuelle Zugriffsliste wird gezeigt.

NICK_HELP_LINK
	Syntax: LINK Chatname Passwort
	
	Der Chatname wird praktisch mit dem anderen Chatname überall
	unter Services gleichgesetzt. Die Aktuelle Zugriffsliste wird
	mit der des anderen Chatnames ersetzt, die Memos werden zu denen
	des neuen Chatnames hinzugefügt. Es kann vorkommen, daß Sie
	einige Ihrer Memos löschen müssen, weil es die Limit vielleicht
	überschreitet. Zum Beispiel haben gelinkte Chatnames gleiche   
	Rechte in den Access-Listen der Räume. Zu Beachten ist, daß
	die unbenutzten Chatnames ablaufen konnen, wenn diese nicht
	benutzt werden.

	Der Link ist für "UNLINK" und "DROP" Befehle aber irrelevant.
	Das heißt, mit DROP löschen sie nur den aktuellen Chatnamen. 
	
	Um diesen Befehl zu benutzen, müssen Sie sich Identifizieren,
	und auch das Passwort des zu linkenden Chatnamen geben.

NICK_HELP_UNLINK
	Syntax: UNLINK [Chatname Passwort]
	
	Der Link zu einem Chatname wird aufgehoben. Obwohl dadurch
	beide Chatnamen die gleiche Zugriffsliste erhalten, werden
	die Memos bei dem Chatnamen gelassen, von welchem der 
	Link getrennt wurde.

	Wenn sie einen Chatnamen und ein Passwort eingeben, können
	Sie den Link von einem anderen Chatnamen trennen.

NICK_HELP_SET
	Syntax: SET Option Parameter
	
	Verschiedene %S Optionen werden gesetzt. Diese sind:
	
	    PASSWORD   Um das Passwort des Chatnames zu ändern.
	    LANGUAGE   Um die Sprache von Services zu bestimmen.
	    URL        Um die gegebene URL zu Ihrem Chatnamen-Eintrag
	               zuzufügen.
	    EMAIL      Um die gegebene Emailadresse zu Ihrem
	               Chatnamen-Eintrag zuzufügen.
	    KILL       Um die Kill Sicherheitsfunktion ein/auszuschalten.
	    SECURE     Um die Sicherheitsoption ein/auszuschalten.
	    PRIVATE    Um den Chatname auf jener Liste mit 
	               /msg %S LIST zu verstecken.
	    HIDE       Um verschiedene Attribute in INFO-Anzeigen
	               zu verstecken.

	Um diesen Befehl auszuführen, müssen Sie sich identifiziert
	haben.  /msg %S HELP IDENTIFY für weitere Informationen.
	
	/msg %S HELP SET Option für weitere Information einer
	bertimmten Option.

NICK_HELP_SET_PASSWORD
	Syntax: SET PASSWORD neues-Passwort
	
	Das Passwort des Chatnames wird dadurch neu gesetzt.

NICK_HELP_SET_LANGUAGE
	Syntax: SET LANGUAGE Nummer
	
	Bestimmt für Sie die Sprache für Services. Die Nummer
	muß einer der unterstützten Sprachen entsprechen.

NICK_HELP_SET_URL
	Syntax: SET URL URL
	
	Die angegebene URL wird zu dem Chatnamen-Eintrag zugefügt.
	Diese URL wird in den INFO Anzeigen dann mitgezeigt.

NICK_HELP_SET_EMAIL
	Syntax: SET EMAIL Adresse
	
	Die angegebene Emailadresse wird zu dem Chatnamen-Eintrag
	zugefügt. Dies wird dadurch in den INFO Anzeigen 
	mitgezeigt.

NICK_HELP_SET_KILL
	Syntax: SET KILL {ON | QUICK | IMMED | OFF}
	
	Die Kill Sicherheitsfunktion wird ein oder ausgeschaltet. 
	Wenn eingeschaltet, dann wird es von jedem gewünscht, der 
	Ihren Chatname benutzt, sich per Passwort zu identifizieren.
	Wenn dieser in einer Minute sich nicht identifiziert, oder
	den Chatname verändert, wird dessen IRC Verbindung mit %S
	unterbrochen. 
	
	Die QUICK Option bewirkt, daß diese Person statt 
	in einer Minute, in 20 Sekunden das Passwort tippen muß, 
	bevor seine Verbindung getrennt wird. Die IMMED 
	Option bewirkt, daß es keine Warnung gibt, bevor die 
	Verbindung getrennt wird.
	Es ist davon abzuraten, dieses Befehl einzusetzten, 
	außerdem kann der Administrator es auch deaktiviert 
	haben. 

NICK_HELP_SET_SECURE
	Syntax: SET SECURE {ON | OFF}
	
	Die Sicherheits Optionen von %S werden ein/ausgeschaltet.
	Wenn eingeschaltet, wird es von Ihnen erwartet, das
	Passwort zu tippen, obwohl Ihre hostmask in der Access-Liste
	eingetragen sein kann. Aber, wenn Ihre hostmark dort 
	eingetragen ist, dann wird Ihre Verbindung nicht getrennt.

NICK_HELP_SET_PRIVATE
	Syntax: SET PRIVATE {ON | OFF}
	
	Der Chatname erscheint auf der Liste mit /msg %S LIST
	nicht mehr, aber das INFO kann immer aufgerufen werden

NICK_HELP_SET_HIDE
	Syntax: SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	
	Verschiedene Attribute Ihres Chatnames werden in der Info
	Anzeige mit "/msg %S INFO" versteckt. Diese sind die
	email Adresse (EMAIL), user@host Maske (USERMASK) 
	und die letzte Quit Message (QUIT). Per (OFF) 
	oder (ON) werden diese Versteckoptionen deaktiviert/aktiviert.

NICK_HELP_UNSET
	Syntax: UNSET {URL | EMAIL}
	
	Ermöglicht, die URL die Emailadresse aus Ihrem Eintrag
	zu entfernen. Der URL Parameter entfernt die URL, der 
	EMAIL Parameter die Email Adresse. Sie können nicht
	beide gleichzeitig entfernen.

NICK_HELP_UNSET_REQ_EMAIL
	Syntax: UNSET URL
	
	Ermöglicht, die URL von Ihrem Eintrag zu entfernen.

NICK_HELP_RECOVER
	Syntax: RECOVER Chatname [Passwort]
	
	Ermöglicht die Verbindung einer Person, die Ihren Chatnamen
	benutzt, zu trennen. Wenn die KILL Sicherheitsfunktion aktiv
	wäre, würde %S das auch automatisch tun.
	
	Mit diesem Befehl, verbindet %S einen Klon mit ihrem Chatnamen
	zum Server, und das führt dazu, daß die Verbindung vom anderen
	Benutzer getrennt wird. Dieser Klon bleibt eine Minute online.
	Sie können nach einer Minute Ihren Chatnamen zurückhaben, Mit
	RELEASE Befehl wäre es möglich, den Chatnamen früher
	freizugeben (/msg %S HELP RELEASE).
	
	Um den RECOVER-Befehl zu benutzen, müssten Sie entweder auf der
	Zugriffsliste des Chatnames sein, oder sie müssen das Passwort
	angeben.

NICK_HELP_RELEASE
	Syntax: RELEASE Chatname [Passwort]
	
	Gibt den Chatname früher frei, der von %S gehalten ist. 
	
	Um RELEASE zu benutzen, müssten Sie entweder in der Zugriffsliste
	des Chatnames sein, oder sie müssen das Passwort angeben.

NICK_HELP_GHOST
	Syntax: GHOST Chatname [Passwort]
	
	Trennt die nicht mehr aktive Verbindung eines Chatnames, die
	vom Server noch als aktiv gehalten wird. Der GHOST-Befehl wird
	z.B. gelegentlich dann eingesetzt, wenn der Client-Computer
	abgestürzt ist oder Ihre Internet-Verbindung unerwartet getrennt
	wird. Diese verursachen, daß der Chatname immer noch im IRC ist,
	also ein Geist (Engl. GHOST) ist.  
	
	Um den GHOST-Befehl zu benutzen, müssten Sie entweder in der
	Zugriffsliste des Chatnames sein, oder sie müssen das Passwort
	angeben.

NICK_HELP_INFO
	Syntax: INFO Chatname [ALL]
	
	Zeigt Information über den gegebenen Chatnamen. So wie wem
	der Nick gehört, letzte gesehene Adresse und Zeit und eingestellte
	Optionen.  Wenn der Nick Ihnen gehört und sie ALL auch mit
	spezifizieren, dann werden alle Informationen gezeigt, auch wenn
	sie versteckt sind.

NICK_HELP_LIST
	Syntax: LIST Parameter
	
	Zeigt alle Chatnamen an, die zu den gegebenen Parametern 
	passen. Chatnames mit PRIVATE Option werden nicht gezeigt.
	
	Beispiele:
	
	    LIST *!Joseph_14@*.ira.uka.de
	         Chatnames, dessen Besitzer von *!Joseph_14@*.ira.uka.de	 
		 kommen, werden gelistet.
	
	    LIST *Bot*!*@*
	        Chatnames, die die Buchstaben BOT haben, werden
		aufgelistet. Gross Kleinschreibung ist unwichtig.
	
	    LIST *!*@*.ira.uka.de
	        Chatnames vom Domäne der ira.uka.de werden
	        aufgelistet.

NICK_HELP_LISTCHANS
	Syntax: LISTCHANS
	
	Zeigt die Namen der Räume an, die Sie registriert haben.

NICK_HELP_STATUS
	Syntax: STATUS [Chatname]
	
	Zeigt einen Code an, um herauszufinden, ob dieser Chatname
	dieser Person gehört. Antwort ist in dieser Form :
	
	    Chatname   Status-Code
	
	Chatname ist der, welchen sie gegeben haben, Status-Code
	ist einer von diesen:

	    0 - Chatname ist nicht registriert/user ist offline.
	    1 - Chatname wurde nicht identifiziert mit.
	    2 - Die Adresse dieser Benutzer ist auf der Access-Liste
	        des Chatnames.
	    3 - Der Benutzer wurde identifiziert.
	
	Sie können bis zu 16 Chatnames angeben, die weiteren werden
	ingoriert. Keine Fehlermeldung wird angezeigt, wenn der
	Chatname nicht angegeben wird.

NICK_SERVADMIN_HELP
	
	Diese Befehls stehen nur den Services-Admins zur Verfügung:
	
	    GETPASS    Zeigt das Passwort des gegebenen Chatnamens.
	    FORBID     Verbietet die Syntax des gegebenen Chatnamens.
	    SUSPEND    Suspendiert die Benutzung des gegebenen Chatnamens.
	    LISTLINKS  Zeigt die aktuellen Links zu einem Chatnamen.
	
	Services-Admins können andere Chatnamen mit folgenden Befehlen
	manipulieren, ohne sich für den Betroffenen Chatnamen zu
	identifizieren:
	    DROP, SET, ACCESS LIST, INFO ALL

NICK_SERVADMIN_HELP_DROP
	Syntax: DROP Chatname
	
	Ohne Parameter wird ihr aktueller Chatname aus der Datenbank
	gelöscht.
	Mit Parameter wird der angegebene Chatname aus der Datenbank
	gelöscht.
	Dies steht nur den Services-Admins zur Verfügung.	

NICK_SERVADMIN_HELP_SET
	
	Services-Admins können die Option NOEXPIRE setzen, so daß
	eine Chatnamenregistrierung nicht verfällt. Services-Admins
	können desweiteren Optionen sämtlicher Chatnamen, ohne das
	Passwort anzugeben, mit dem forgendem Befehl setzen: 
	SET Chatname Option Parameter.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Syntax: SET Chatname NOEXPIRE {ON | OFF}
	
	Bestimmt, ob die Registrierung des Chatnamen verfällt.
	Wenn ON angegeben wird, wird der angegebene Chatname
	nicht verfallen und nicht aus der Datenbank gelöscht.

	Dieser Befehl steht nur den Services-Admins zur Verfügung.	

NICK_SERVADMIN_HELP_UNSET
	
	Services-Admins können auch den UNSET-Befehl für jeden
	Chatnamen benutzen, ohne das Passwort anzugeben.

NICK_SERVADMIN_HELP_UNLINK
	
	Services-Admins können von jedem Chatnamen einen Link aufheben,
	ohne Passwort anzugeben.

NICK_SERVADMIN_HELP_LISTLINKS
	Syntax: LISTLINKS Chatname [ALL]
	
	Zeigt alle Links zu dem gegebenen Chatnamen an. Wenn ALL auch
	angegeben ist, werden alle Chatnamen mit den gleichen Rechten
	gezeigt, sonst werden nur die direkten Links gezeigt.

	Dieser Befehl steht nur den Services-Admins zur Verfügung.	

NICK_SERVADMIN_HELP_ACCESS

	Services-Admins können mit einem Chatnamen-Parameter zu
	LIST die Zugriffsliste von jedem Chatnamen anzeigen.

NICK_SERVADMIN_HELP_INFO
	
	Services-Admins können den ALL Parameter für alle Chatnamen
	benutzen.

NICK_SERVADMIN_HELP_LIST
	Syntax: LIST Parameter [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
	
	Zeigt alle Chatnamen an, die zu den angegebenen Parametern 
	passen. Chatnamen mit PRIVATE Option werden auch gezeigt.
	Die NOEXPIRE Nicks werden mit einem !, die suspendierten mit einem
	* markiert.
	
	Wenn  FORBIDDEN, SUSPENDED oder NOEXPIRE angegeben sind,
	werden nur verbotene, suspendierte, oder noexpire Chatnamen angezeigt.
	Diese Optionen können in beliebiger Reihenfolge oder Kombination
	gegeben werden. Sie sind nur von den Services-Admins anwendbar.
	
	Beispiele:
	
	    LIST *!Joseph_14@*.ira.uka.de
	         Chatnamen, dessen Besitzer von *!Joseph_14@*.ira.uka.de	 
		 kommen, werden gelistet.
	
	    LIST *Bot*!*@*
	        Chatnamen, die die Buchstaben BOT haben, werden
		aufgelistet. Gross Kleinschreibung ist unwichtig.
	
	    LIST * NOEXPIRE
	        Chatnamen, die nicht verfallen, werden aufgelistet.

NICK_SERVADMIN_HELP_LISTCHANS
	
	Services-Admins können jederzeit die Liste der registrierten Räume
	von einem Chatnamen erhalten:
	/msg NickServ LISTCHANS Chatname).

NICK_SERVADMIN_HELP_GETPASS
	Syntax: GETPASS Chatname
	
	Zeigt das Passwort des angegebenen Chatnamens. Ein WALLOPS
	oder ein GLOBOPS wird weitergeleitet mit dem Chatnamen des
	Admins, der GETPASS benutzt hat.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.	

	Dieser Befehl ist nicht aufrufbar, wenn Verschlüsselung aktiv ist.

NICK_SERVADMIN_HELP_FORBID
	Syntax: FORBID Chatname
	
	Verbietet die Benutzung des gegebenen Chatnames. Der Verbot
	wird nur mit DROP aufgehoben.

	Dieser Befehl steht nur den Services-Admins zur Verfügung.	

NICK_SERVADMIN_HELP_SUSPEND
	Syntax: SUSPEND [+Dauer] Chatname Grund
	
	Verhindert, daß der Chatname, und alle damit verbundenen,
	benutzt, oder identifiziert werden.
	UNSUSPEND hebt die Suspendierung auf.
	
	Im Gegensatz zu Verbot (FORBID), verliert der Chatname
	seine Information nicht. Die Registrierung kann ebenfalls
	verfallen.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.	

NICK_SERVADMIN_HELP_UNSUSPEND
	Syntax: UNSUSPEND Chatname
	
	Hebt die Suspendierung des Chatnamens auf.

	Dieser Befehl steht nur den Services-Admins zur Verfügung.	


###########################################################################
#
# ChanServ help messages
#
###########################################################################

CHAN_HELP
	%S ermöglicht es Ihnen, einen Raum zu registrieren
	und selbst zu kontrollieren. %S kann verhindern, daß ihr
	Raum von unbefügten übernommen wird. 
	Die verfügbaren Befehle sind unten aufgelistet. Um sie zu
	benutzen, versuchen Sie /msg %S Befehl. Für Hilfe
	über einen bestimmten Befehl, versuchen Sie
	/msg %S HELP Befehl .
	
	    REGISTER   Der Raum wird für Sie registriert.
	    IDENTIFY   Indentifiziert Sie als Eigentümer des Raumes.
	    DROP       Löscht den Raum aus der Datenbank.
	    INFO       Zeigt Optionen und Informationen über den Raum.
	    SET        Setzt Optionen und Informationen für den Raum.
	    ACCESS     Modifiziert die Zugriffsliste.
	    SOP        Modifiziert die SuperOp-Liste
	    AOP        Modifiziert die AutoOp-Liste
	    VOP        Modifiziert die VoiceOp-Liste
	    AKICK      Modifiziert die AutoKick-Liste.
	
CHAN_HELP_OTHERS
	
	Weitere Befehle: UNSET, LIST, INVITE, UNBAN, CLEAR,
	                 LEVELS, OP, DEOP, VOICE, DEVOICE

CHAN_HELP_OTHERS_HALFOP_CHANPROT
	
	Weitere Befehle: UNSET, LIST, INVITE, UNBAN, CLEAR,
	                 LEVELS, OP, DEOP, VOICE, DEVOICE,
	                 HALFOP, DEHALFOP, PROTECT, DEPROTECT,
	                 HOP

CHAN_HELP_EXPIRES

	Vergessen Sie Bitte nicht, daß Räume, die %d Tage nicht
	benutzt werden, automatisch verfallen und gelöscht werden.
	Zum Beispiel solche Räume, die niemand aus der Zugriffsliste
	besucht hat.

CHAN_HELP_REGISTER
	Syntax: REGISTER Raum Passwort Beschreibung
	
	Registriert ein Raum unter Ihrem Chatnamen. Um überhaupt
	diesen Befehl ausführen zu können, müssen sie ein ChanOp sein. 
	Das Passwort brauchen Sie später um sich als "Gründer" zu
	identifizieren (^BIDENTIFY^B).
	Die Beschreibung (letzter Parameter) muß angegeben werden.
	Das Passwort sollten Sie nicht vergessen. Dem Gründer gibt
	%S jedesmal automatisch das +o Modus (AutoOp).
	Mit Hilfe der Befehle ACCESS und LEVELS können
	Zugriffsrechte anderer Benutzer/Chatnamen modifiziert werden.
	
	WICHTIG: Um ein Raum überhaupt registrieren zu können,
	müssen Sie einen registrierten Chatnamen haben.
	/msg %s HELP für weitere Informationen.

CHAN_HELP_IDENTIFY
	Syntax: IDENTIFY Raum Passwort
	
	Sie indentifizieren sich dem %S gegenüber als Gründer des Raumes.
	Das Passwort ist das, das Sie beim Registrieren benutzt haben.
	Viele Befehle setzen voraus, daß Sie die Identifikation ausfühen,
	bevor sie diese nutzen können.

CHAN_HELP_DROP
	Syntax: DROP Raum

	Der gegebene Raum wird aus der Datenbank gelöscht. Nur der
	Gründer darf diesen Befehl nach dem IDENTIFY benutzen. 

CHAN_HELP_SET
	Syntax: SET Raum Optionen Parameter
	
	Bestimmt sämtliche Raum-Optionen. Dafür muß der Gründer
	mit IDENTIFY sich dem %S gegenüber identifiziert haben.
	
	Optionen:
	
	    FOUNDER     Bestimmt einen neuen Gründer.
	    SUCCESSOR   Bestimmt einen neuen Nachfolger.
	    PASSWORD    Bestimmt ein neues Raum-Passwort.
	    DESC        Bestimmt eine neue Beschreibung.
	    URL         Fügt eine URL dem Raum-Eintrag hinzu.
	    EMAIL       Fügt eine Emailadresse dem Raum-Eintrag hinzu.
	    ENTRYMSG    Ändert die Begrüßungsnachricht.
	    TOPIC       Ändert das Thema des Raumes.
	    KEEPTOPIC   Ändert die Option zur Beibehaltung des Themas.
	    TOPICLOCK   Ändert die Option zur Sperrung des Themas.
	    MLOCK       Setzt neues Sperr-Modus.
	    PRIVATE     In %S Listen wird der Raum nicht angezeigt.
	    SECUREOPS   Bis auf Chatnamen in der Zugriffsliste kann
	                niemand Op werden.
	    RESTRICTED  Bis auf Chatnamen in der Zugriffsliste kann
	                niemand den Raum betreten.
	    SECURE      %S Sicherheitsfunktionen werden aktiviert.
	    LEAVEOPS    Niemandem beim JOIN deoppen.
	    OPNOTICE    Eine NOTICE schicken, wenn OP/DEOP Befehle
	                benutzt werden.
	    ENFORCE     Zwingt die Autoop und Autovoice status.
	
	/msg %S HELP Option für weitere Informationen.

CHAN_HELP_SET_FOUNDER
	Syntax: SET Raum FOUNDER Chatname
	
	Setzt den Chatnamen als neuen Gründer des Raumes.
	Der Gründer muß einen registrierten Chatnamen haben.

CHAN_HELP_SET_SUCCESSOR
	Syntax: SET Raum SUCCESSOR Chatname
	
	Ändert den Nachfolger des Raumes. Wenn der Chatname des
	Gründers abläuft, oder gedropped wird, bekommt der Nachfolger
	den Gründerstatus. Dies erfolgt aber nicht, wenn des Nachfolger
	bereits %d registrierte Räume hat. Dann wird der Raum gelöscht,
	auch, wenn ein Nachfolger gesetzt war. Das Nachfolger muß ein
	registrierter Chatname sein.

CHAN_HELP_SET_PASSWORD
	Syntax: SET Raum PASSWORD neues_Passwort
	
	Setzt ein neues Raum-Passwort für den Gründer-Zugriff.

CHAN_HELP_SET_DESC
	Syntax: SET Raum DESC Beschreibung
	
	Setzt eine neue Beschreibung für den Raum, die bei LIST und
	INFO gezeigt wird. Man muß den Gründer-Zugriff haben,
	um dies zu benutzen.

CHAN_HELP_SET_URL
	Syntax: SET Raum URL [URL]
	
	Fügt URL dem Raum-Eintrag hinzu. Diese URL wird bei INFO
	angezeigt. Wenn keine URL angegeben ist, wird die aktuelle
	gelöscht.

CHAN_HELP_SET_EMAIL
	Syntax: SET Raum EMAIL [Adresse]
	
	Fügt dem Raum-Eintrag eine Emailadresse hinzu. Die wird bei
	INFO angezeigt. Wenn keine Adresse angegeben ist, wird die
	aktuelle gelöscht.

CHAN_HELP_SET_ENTRYMSG
	Syntax: SET Raum ENTRYMSG text
	
	Settz eine neue Begrüßungsnachricht, die man als /NOTICE
	erhält, wenn man diesen Raum betritt.

CHAN_HELP_SET_TOPIC
	Syntax: SET Raum TOPIC Topic
	
	Bewirkt, daß %S das Thema für den Raum setzt.
	Besonders nützlich, wenn TOPICLOCK aktiv ist.

CHAN_HELP_SET_KEEPTOPIC
	Syntax: SET Raum KEEPTOPIC {ON|OFF}
	
	Bewirkt, daß das Thema, nich verlorengeht, wenn niemand im
	Raum ist. Wenn topic retention aktiv ist, wird der Topic
	gespeichert, und, wenn jemand den Raum betritt, wird er gesetzt.

CHAN_HELP_SET_TOPICLOCK
	Syntax: SET Raum TOPICLOCK {ON|OFF}
	
	Die Topic Lock Option wird aktivert/deaktiviert.
	Wenn aktiv, verhindert %S, daß jemand das Thema ändert, 
	sofern SET TOPIC nicht benutzt ist.

CHAN_HELP_SET_MLOCK
	Syntax: SET Raum MLOCK Modi
	
	Aktiviert/deaktiviert die Mode-Lock Option für den Raum.
	%S ermöglicht, daß bestimmte Modi (Raumoptionen) immer
	eingeschaltet werden.
	Diese sind  i, k, l, m, n, p, s und t.
	Die Modi sind ähnlich dem /MODE-Befehl aufgebaut: die
	Modi, die einem + folgem werden aktiviert, die einem -
	folgen, werden deaktiviert.

	Warnung: Falls Sie, wie im zweiten Beispiel ein ModeLock 
	setzen wollen, dann sollten sie die RESTRICTED-Option 
	auch setzen, so daß wenn jemand den leeren Raum betritt, den 
	Schlüssel nicht sieht. (siehe HELP SET RESTRICTED).
	
	Beispiele:
	
	    SET #Raum MLOCK +nt-iklps
		Die Modes +tn sind aktiv, die iklps sind inaktiv, und
		%S wird verhindern, daß Sie gesetzt werden. Aber Mode
		m kann gesetzt werden.  
	
	    SET #Raum MLOCK +knst-ilmp schlüssel
		Die Modes +knst sind aktiv, mit schlüssel für k, und
		die Modes ilmp sind inaktiv.
	
	    SET #kanal MLOCK +
	        Deaktiviert ModeLock, alle Modes werden frei setzbar sein.

CHAN_HELP_SET_PRIVATE
	Syntax: SET Raum PRIVATE {ON|OFF}
	
	Setzt die private-Option für den Raum. Wenn aktiv, wird der
	Raum auf der Liste mit /msg %S LIST nicht erscheinen.
	
CHAN_HELP_SET_RESTRICTED
	Syntax: SET Raum RESTRICTED {ON|OFF}
	
	Setzt die RESTRICTED Option für den Raum. Wenn aktiv,
	kann niemand den Raum betreten, wenn er nicht in der
	Zugriffsliste eingetragen ist.

CHAN_HELP_SET_SECURE
	Syntax: SET Raum SECURE {ON|OFF}
	
	Aktiviert/deaktiviert %S Sicherheitsfunktionen für den Raum.
	Wenn aktiv, können nur die, die ihren Chatnamen mit %s
	registriert haben und sich mit IDENTIFY identifiziert haben,
	besondere Rechte zum Raum erhalten, folgend der Zugriffsliste.

CHAN_HELP_SET_SECUREOPS
	Syntax: SET Raum SECUREOPS {ON|OFF}
	
	Aktiviert/deaktiviert die Secureops-Option, so daß Benutzer,
	die nicht in der Zugriffsliste vermerkt sind, den Op-Status
	nicht erhalten können.

CHAN_HELP_SET_LEAVEOPS
	Syntax: SET Raum LEAVEOPS {ON | OFF}
	
	Aktiviert/deaktiviert die Leaveops-Option. Wenn aktiv, wird
	%S die erste Person im Raum nicht deoppen. Die Optionen
	SECUREOPS und AUTODEOP werden trotzdem beachtet.

CHAN_HELP_SET_OPNOTICE
	Syntax: SET Raum OPNOTICE {ON | OFF}
	
	Aktiviert/deaktiviert die OP-Notice-Option. Wenn aktiv, wird
	%S ein Notice zum Raum schicken, wo steht, wer für wen
	den OP oder DEOP-Befehl benutzt hat.

CHAN_HELP_SET_ENFORCE
	Syntax: SET Raum ENFORCE {ON | OFF}
	
	Aktiviert/deaktiviert die Zwangsoption für Auto-Op und
	Auto-Voice. Wenn aktiv, überprüft %S die Auto-Op und
	Auto-Voice Privilegien. Das bedeutet, wenn ein Benutzer mit
	Auto-Op Status gedeopped wird, wird %S ihn wieder oppen, und
	auch verhindern, daß der DEOP Befehl für den Benutzer
	eingesetzt wird.

CHAN_HELP_UNSET
	Syntax: UNSET Raum {SUCCESSOR | URL | EMAIL | ENTRYMSG}
	
	Löscht die gegebene Information von dem Raum-Eintrag.

CHAN_HELP_SOP
	Syntax: SOP Raum ADD Chatname
	        SOP Raum DEL Chatname
	        SOP Raum LIST [Maske | Liste]
	        SOP Raum COUNT
	
CHAN_HELP_SOP_NOPROT
	Modifiziert die SuperOp-Liste (SOP) des Raums.
	Benutzer mit SOP Status werden automatisch geopt (+o),
	wenn sie den Raum betreten.
CHAN_HELP_SOP_PROT
	Modifiziert die SuperOp-Liste (SOP) des Raums.
	Benutzer mit SOP-Status werden automatisch geopt (+o),
	und auch geschützt (+a), wenn sie das Raum betreten.
CHAN_HELP_SOP_END
	
	Ein SOP kann die AOP- und VOP-Listen bearbeiten, nur
	der Gründer kann die SOP-Liste bearbeiten.
	
	SOP LIST zeigt die SOP-Liste. Wenn eine Maske angegeben ist,
	werden nur die passenden Einträge angezeigt.
	Wenn ein Bereich angegeben ist, werden nur enthaltene Einträge
	angezeigt.
	
	   SOP #channel LIST 2-5,7-9
	      Zeigt SOP-Einträge zwischen 2 und 5, und 7 und 9
	
	SOP COUNT gibt die Anzahl der SOP-Einträge an.

CHAN_HELP_AOP
	Syntax: AOP Raum ADD Chatnam
	        AOP Raum DEL Chatnam
	        AOP Raum LIST [Maske | Liste]
	        AOP Raum COUNT
	
	Modifiziert die AutoOp-Liste (AOP) des Raums.
	Alle Benutzer mit AOP-Status werden automatisch geopt (+o),
	wenn sie den Raum betreten.
	
	Ein AOP kann die VOP-Liste bearbeiten.
	
	AOP LIST zeigt die AOP-Liste.  Wenn eie Maske angegeben ist,
	werden nur die passenden Einträge angezeigt.
	Wenn ein Bereich angegeben ist, werden nur enthaltene Einträge
	angezeigt.
	
	   AOP #channel LIST 2-5,7-9
	      Listet AOPs zwischen 2 und 5, und 7 und 9
	
	AOP COUNT gibt die Anzahl der AOP-Einträge an.

CHAN_HELP_HOP
	Syntax: HOP Raum ADD Chatname
	        HOP Raum DEL Chatname
	        HOP Raum LIST [Maske | Liste]
	        HOP Raum COUNT
	
	Modifiziert die HalfOp-Liste (HOP) des Raums.
	Alle Benutzer mit HOP-Status erhalten ein Halfop (+h),
	wenn sie den Raum betreten.
	
	Ein HOP kann die VOP-Liste bearbeiten, (SOP und
	AOPs ebenfalls).

	HOP LIST listet die Halfops auf.  Wenn eie Maske angegeben ist,
	werden nur die passende Einträge angezeigt.
	Wenn ein Bereich angegeben ist, werden nur enthaltene Einträge
	angezeigt.
	
	   HOP #channel LIST 2-5,7-9
	      Listet HOPs zwischen 2 und 5, und 7 und 9
	
	HOP COUNT gibt die Anzahl der HOP-Einträge an.

CHAN_HELP_VOP
	Syntax: VOP Raum ADD Chatname
	        VOP Raum DEL Chatname
	        VOP Raum LIST [Maske | Liste]
	        VOP Raum COUNT
	
	Modifiziert die VoiceOp-Liste (VOP) des Raums.
	Benutzer mit VOP-Status erhalten ein Voice (+v),
	wenn sie den Raum betreten.

	VOP LIST zeigt die Auto-Voices.  Wenn eine Maske angegeben
	ist, werden nur die passende Einträge angezeigt.
	Wenn ein Bereich angegeben ist, werden nur enthaltene Einträge
	angezeigt.
	
	   VOP #channel LIST 2-5,7-9
	      Listet VOPs zwischen 2 und 5, und 7 und 9
	
	VOP COUNT gibt die Anzahl der VOP-Einträge an.
	
CHAN_HELP_ACCESS
	Syntax: ACCESS Raum ADD [Chatname] Stufe}
	        ACCESS Raum DEL {Chatname | Nummer | Liste}
	        ACCESS Raum LIST [Maske]
	        ACCESS Raum COUNT

	Verwaltet die Zugriffsliste des Raumes. In dieser Liste sind
	die Chatnamen eingetragen, die autoop werden können, oder
	Zugriff auf andere %S Befehls habee können. Die Stufe bestimmt
	die verschiedenen Zugriffsrechte. Die Standarteinstellungen
	können natürlich von dem Gründer geändert werden. (siehe 
	/msg %S HELP ACCESS LEVELS) 
	Jeder Chatname, der nicht eingetragen ist, hat die Stufe 0.
	
	ACCESS ADD trägt den gegebenen Chatnamen in die Zugriffsliste
	mit der gegebenen Stufe ein. Die Stufe muß kleiner als Stufe von
	der Person sein, die diesen Befehl ausführen will. Außerdem kann
	man keine niedrigere Stufe für einen Chatnamen setzen, der mit
	einer höheren Stufe eingetragen ist, als die vom aktuellen
	Benutzer.
	
	ACCESS DEL löscht den angegebenen Chatnamen von der Liste.
	
	ACCESS LIST zeigt die Zugriffsliste; wenn ein Parameter
	angegeben worden ist, werden nur die Chatnamen angezeigt,
	die dem Parameter entsprechen.

	ACCESS COUNT gibt die Anzahl der VOP-Einträge an.

CHAN_HELP_ACCESS_LEVELS
	Die Zugriffsstufen
	
	Die Standarteinstellungen:      
	
	   Gründer  Als der Besitzer des Raums hat der Gründer 
	                vollständigen Zugriff auf alle %S-Befehle und
	                Auto-Op, wenn er den Raum betritt. Zu beachten
	                ist, daß es keinen zweiten Gründer geben kann.
	        10  Kann AKICK Befehl aufrufen.
	         5  Auto-Op (+o).
	         3  Auto-Voice (+v).
	         0  Normaler Benutzer.Wenn Secureops nicht 
	   			aktiv ist kann, normal op werden.
	        <0  Benutzer kann kein Op werden.
	
	Mit dem LEVELS-Befehl können diese Werte geändert, und neue
	hinzugefügt werden.
	/msg %S HELP LEVELS für weitere Informationen.

CHAN_HELP_AKICK
	Syntax: AKICK Raum ADD Maske [Grund]
	        AKICK Raum DEL Maske
	        AKICK Raum LIST	
	
	Bearbeitet die AutoKick-Liste eines Raumes. Wenn jemand,
	der in diese Liste eingeragen ist, den Raum betritt, wird
	er vom %S sofort gebannt und gekickt.
	
	AKICK ADD trägt die Maske oder den Chatnamen in diese Liste
	ein. Wenn ein Grund spezifiziert wurde, wird dieser als
	Kick-Grund benutzt.
	
	AKICK DEL löscht die Maske oder den Chatnamen von der Liste,
	aber falls es existierende Bans im Raum gibt, sollten diese durch
	einen Raum-Op aufgehoben werden. 
	
	AKICK LIST gibt die AutoKick Liste wieder, falls mit einem
	Parameter aufgerufen, werden die Einträge gezeigt,
	die dem Parameter entsprechen.

CHAN_HELP_LEVELS
	Syntax: LEVELS Raum SET Option Level
	        LEVELS Raum {DIS | DISABLE} Option
	        LEVELS Raum LIST
	        LEVELS Raum RESET
	
	LEVELS setzt die benötigten Zugriffsstufen für bestimmte
	Operationen neu (ACCESS LEVELS). Die Befehle SET FOUNDER,
	SET PASSWORD und dieser (LEVELS) stehen ausschließlich
	dem Gründer zur verfügung.

	Warnung: Dieser Befehl ist für erfahrene Benutzer. Das
	Ändern der Stufen kann dazu führen, daß die Befehle SOP,
	AOP und HOP nicht mehr richtig funktionieren.
	
	LEVELS SET setzt eine neue Stufe für die angegebene Option.
	LEVELS DISABLE oder DIS deaktiviert diese Option 
	für normale Benutzer (bis auf den Gründer).
	
	LEVELS LIST zeigt die aktuelle Stufenliste.
	LEVELS RESET ersetzt die Stufen mit den Standarteinstellungen.

	HELP ACCESS LEVELS für die Beschreibung der Standardeinstellungen.
	HELP LEVELS DESC für die Beschreibung der Optionen.

CHAN_HELP_LEVELS_DESC
	Folgende Optionen können mit LEVELS SET gesetzt werden.
	Zu beachten ist, daß die Stufen für AUTOOP und NOJOIN maximale,
	die anderen minimale Werte beschreiben.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Syntax: INFO Raum [ALL]
	
	Zeigt Information über einen registrierten Raum, so wie den
	Gründer, Registrierungsdatum, letzte Benutzung, Sperr-Modi.
	Wenn Sie auch der Gründer sind, können Sie mit ALL alle
	Information wie Begrüßungstext und Nachfolger erhalten.
	
CHAN_HELP_LIST
	Syntax: LIST Parameter
	
	Zeigt alle Räume, die dem gegebenen Parameter entsprechen
	(bis auf die, die die PRIVATE-Option haben).

CHAN_HELP_OP
	Benuzung: OP Raum Chatname
	
	Gibt dem angegebenen Chatnamen den Raum-Op-Status (+o).
	Standardmäßig eingeschränkt zu den Personen, die in der
	Zugriffsliste die Stufe 5 oder höher haben.

CHAN_HELP_DEOP
	Syntax: DEOP Raum Chatname
	
	Entzieht dem Chatnamen den Raum-Op-Status (-o).
	Standardmäßig eingeschränkt zu den Personen, die in der
	Zugriffsliste die Stufe 5 oder höher haben.

CHAN_HELP_VOICE
	Syntax: VOICE Raum Chatname
	
	Gibt dem angegebenen Chatnamen den Voice-Status (+v).
	Standardmäßig eingeschränkt zu den Personen, die in der
	Zugriffsliste die Stufe 3 oder höher haben.

CHAN_HELP_DEVOICE
	Syntax: DEVOICE Raum Chatname
	
	Entzieht dem Chatnamen den Voide-Status (-v).
	Standardmäßig eingeschränkt zu den Personen, die in der
	Zugriffsliste die Stufe 3 oder höher haben.

CHAN_HELP_HALFOP
	Syntax: HALFOP Raum Chatname
	
	Gibt dem angegebenen Chatnamen den Halfop-Status (+h).
	Standardmäßig eingeschränkt zu den Personen, die in der
	Zugriffsliste die Stufe 4 oder höher haben.

CHAN_HELP_DEHALFOP
	Syntax: DEHALFOP Raum Chatname
	
	Entzieht dem Chatnamen den Halfop-Status (-h).
	Standardmäßig eingeschränkt zu den Personen, die in der
	Zugriffsliste die Stufe 4 oder höher haben.

CHAN_HELP_PROTECT
	Syntax: PROTECT Raum Chatname
	
	Gibt dem angegebenen Chatnamen den Protect-Status (+a).
	Standardmäßig eingeschränkt auf die Personen, die in der
	Zugriffsliste die Stufe 10 oder höher haben.

CHAN_HELP_DEPROTECT
	Syntax: DEPROTECT Raum Chatname
	
	Entzieht dem Chatnamen den Protect-Status (-a).
	Standardmäßig eingeschränkt auf die Personen, die in der
	Zugriffsliste die Stufe 10 oder höher haben.

CHAN_HELP_INVITE
	Syntax: INVITE Raum
	
	Lässt %S Sie zum angegebenen Raum einladen (invite). 
	Standardmäßig eingeschränkt auf die Personen, die in der
	Zugriffsliste die Stufe 5 oder höher haben.

CHAN_HELP_UNBAN
	Syntax: UNBAN Raum
	
	Lässt %S alle Bans aufheben, die Sie daran hindern den Raum
	zu betreten.
	Standardmäßig eingeschränkt auf die Personen, die in der
	Zugriffsliste die Stufe 5 oder höher haben.

CHAN_HELP_CLEAR
	Syntax: CLEAR Raum Einstellung
	
	Lässt %S bestimmte Typen von Einstellungen vom Raum entfernen.
	Die Einstellung kann eine der folgenden sein:
	
	     MODES       Alle Modi bis auf Mlock entfernen.
	     BANS        Alle Bans entfernen
CHAN_HELP_CLEAR_EXCEPTIONS
	     EXCEPTIONS  Alle Exceptions entfernen
CHAN_HELP_CLEAR_MID
	     OPS         Ein Massdeop ausführen.
CHAN_HELP_CLEAR_HALFOPS
	     HALFOPS     Ein Mass-de-halfop ausführen.
CHAN_HELP_CLEAR_END
	     VOICES      Ein Massdevoice ausführen.
	     USERS       Ein Masskick ausführen.
	
	Standardmäßig eingeschränkt auf die Personen, die in der
	Zugriffsliste die Stufe 10 oder höher haben.
	
CHAN_SERVADMIN_HELP
	
	Diese Befehle können nur Services-Admins benutzen:
	
	    GETPASS   Gibt das Passwort des gegebenen Raums.
	    FORBID    Verbietet die Benutzung des gegebenen Raums.
	    STATUS    Gibt die Stufe der Benutzers in der Zugriffsliste
	              des Raumes.
	    SUSPEND   Suspendiert die Benutzung eines Raums.
	
	Services-Admins können ohne IDENTIFY ein Raum-Eintrag
	löschen (DROP), das Passwort neu setzen, oder die Zugriffsliste 
	bearbeiten (/msg %S ACCESS Raum {ADD | DEL | LIST}) .

CHAN_SERVADMIN_HELP_DROP
	Syntax: DROP Raum
	
	Löscht den Raum Eintrag, ohne das Passwort geben zu müssen.

CHAN_SERVADMIN_HELP_SET
	
	Services-Admins können NOEXPIRE für einen Raum setzen,
	so daß die Raumregistrierung nicht verfällt. Services-Admins
	können desweiteren Optionen sämtlicher Räume setzen, ohne das
	Passwort anzugeben.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Syntax: SET Raum NOEXPIRE {ON | OFF}
	
	Bestimmt, ob die Raumregistrierung verfällt.
	Wenn On angegeben wird, wird der Raum nicht
	verfallen  und nicht aus der Datenbank gelöscht..
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.
	
CHAN_SERVADMIN_HELP_UNSET
	
	Services-Admins können auch den UNSET-Befehl für jeden
	Raum benutzen, ohne das Passwort anzugeben.

CHAN_SERVADMIN_HELP_INFO
	
	Services-Admins können den ALL Parameter für alle Räume
	benutzen.

CHAN_SERVADMIN_HELP_LIST
	Syntax: LIST Parameter
	
	Zeigt alle Räume, die dem Parameter entsprechen.

CHAN_SERVADMIN_HELP_GETPASS
	Syntax: GETPASS Raum
	
	Zeigt das Passwort für den angegebenen Raum. Ein WALLOPS
	oder ein GLOBOPS wird weitergeleitet mit dem Chatnamen des
	Admins, der GETPASS benutzt hat.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.
	
	Dieser Befehl ist nicht aufrufbar, wenn Verschlüsselung aktiv ist.

CHAN_SERVADMIN_HELP_FORBID
	Syntax: FORBID Raum
	
	Verbietet die Benutzung des angegebenen Raumes. Der Verbot
	wird nur mit DROP aufgehoben.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

CHAN_SERVADMIN_HELP_SUSPEND
	Syntax: SUSPEND [+Dauer] Raum Grund
	
	Verhindert, daß der Raum benutzt wird.
	UNSUSPEND hebt die Suspendierung auf.
	
	Im Gegensatz zu Verbot (FORBID), verliert der Raum seine
	Information nicht. Die Registrierung kann ebenfalls verfallen.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

CHAN_SERVADMIN_HELP_UNSUSPEND
	Syntax: UNSUSPEND Raum
	
	Hebt die Suspension eines Raums auf.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.


CHAN_SERVADMIN_HELP_STATUS
	Syntax: STATUS Raum Chatname
	
	Gibt den Stufe des Chatnamens in der Zugfiffsliste vom Raum.
	Die Antwort hat die Form:
	
	    STATUS Raum Chatname Access-Level
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

###########################################################################
#
# MemoServ help messages
#
###########################################################################

MEMO_HELP
	Mit Hilfe von %S können Sie kleine Nachrichten zu anderen
	Personen schicken, unabhängid davon, ob die Person sich im
	Moment im IRC befindet oder nicht. Desweiteren können Memos
	an Räume(*) geschickt werden.
	Es ist erforderlich, daß Sie und der Empfänger einen
	registrierten Chatnamen haben (bzw. registrierten Raum).

	%S Befehle:
	
	    SEND   Schickt das Memo zum gegebenen Chatnamen.
	    LIST   Zeigt die eigenen Memos.
	    READ   Zeigt ein Memo zum lesen.
	    DEL    Löscht ein oder mehrere Memos.
	    SET    Setzt Optionen für Memos.
	    INFO   Zeigt Informationen und Einstellungen für Memos.
	
	/msg %S HELP Befehl für weitere Information für einen
	bestimmten Befehl
	
	(*) Standardeinstellung ist, daß Chatnamen mit Stufe 10 in
	der Zugriffsliste des Raumes die Raum-Memos lesen können.
	Diese Einstellung kann man mit LEVELS ändern.

MEMO_HELP_SEND
	Syntax: SEND {Chatname | Raum} Text
	
	Schickt ein Memo (den Text) zum gegebenen Chatnamen oder Raum.
	Beim schicken an einen Chatnamen wird der Empfänger über
	das eintreffen des Memos informiert.

MEMO_HELP_LIST
	Syntax: LIST [Raum] [Liste | NEW]
	
	Zeigt die derzeitigen Memos. Wird der NEW Parameter
	geben, weden nur die neuen, nicht gelesenen Memos angezeigt.
	Diese sind mit einem "*" versehen. Eine Liste kann die Auswahl
	der anzuzeigenden Memos einschränken, wie in dem Beispiel:
	    LIST 2-5.7-9
	       Übersicht über Memos 1 bis 5 und 7 bis 9 wird angezeigt.

MEMO_HELP_READ
	Syntax: READ [Raum] {Nummer | Liste | LAST | NEW}
	
	Zeigt Ihnen das spezifizierte Memo an. Wenn sie LAST benutzen,
	wird das neueste Memo gezeigt. Wenn sie NEW benutzen,
	werden alle nicht gelesenen Memos gezeigt. Sonst können
	Sie die Nummer des zu lesenden Memos geben. Wenn Sie eine
	Liste benutzen, werden die Memos gezeigt, die dem 
	Listenparameter entsprechen. Beispiel:
	
	   READ 2-5,7-9
	      Alle Memos von 2 bis 5 und von 7 bis 9 werden gezeigt.

MEMO_HELP_DEL
	Syntax: DEL [Raum] {Nummer | Liste | ALL}
	
	Löscht das angegebene Memo oder die angegebenen Memos.
	Sie können über eine Liste mehrere Memos spezifizieren,
	die Sie löschen wollen, oder mit ALL alle Memos löschen.
	Beispiele:
	
	   DEL 1
	      Löscht das erste Memos.
	
	   DEL 2-5
	      Löscht Memos von 2 bis 5.

MEMO_HELP_SET
	Syntax: SET Option Parameter
	
	Setzt verschiedene Optionen. Option ist ein Wert von:
	
	    NOTIFY      Bestimmt, wann man bei einem neuen
	                    Memo benachrichtigt wird.
	    LIMIT       Bestimmt die maximale Anzahl der Memos
	                    die man kriegen möchte.
	
	/msg %S HELP SET Option für weitere Informationen
	über ein Befehl.	

MEMO_HELP_SET_NOTIFY
	Syntax: SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Bestimmt, wann Sie über neue Memos benachrichtigt werden.
	
	    ON      Beim Anmelden, beim Beenden von /AWAY und
	            wenn neue Memos eintreffen.
	    LOGON   Beim Anmelden und beim Beenden von /AWAY.
	    NEW     Beim eintreffen neuer Memos.
	    OFF     Keine Benachrichtigung.
	
	ON ist beiden LOGON und NEW gleich.
	
	Hinweis: wenn Ihr Chatname die Option SECURE hat, werden
	Sie erst dann benachrichtigt, wenn sie sicht dem %S
	gegenüber identifiziert haben.

MEMO_HELP_SET_LIMIT
	Syntax: SET LIMIT [Raum] Limit
	
	Bestimmt die maximale Anzahl von Memos, die Sie oder
	der Raum haben kann. Wenn Sie das auf 0 setzen,
	erhalten Sie keine Memos.
	Diese Zahl kann nicht grösser als %d sein.      

MEMO_HELP_INFO
	Syntax: INFO [Raum]

	Zeigt die Anzahl der Memos (gelesen und ungelesen),
	wie viele Memos Sie noch empfangen können und die
	Benachrichtigungsoption.
	Wenn der Raumparameter angegeben wird, werden die
	Informationen über den Raum angezeigt.

MEMO_SERVADMIN_HELP_SET_LIMIT
	Syntax: SET LIMIT [Chatname | Raum] {Limit | NONE} [HARD]
	
	Setzt die maximale Anzahl der Memos für einen Chatnamen oder
	Raum. Wenn auf 0 gesetzt, kann der Benutzer oder Raum keine
	Memos erhalten. Wenn auf NONE gesetzt, dann gibt es keinen 
	Limit. Ohne Angabe des Chatnamens oder Raumes setzen Sie die
	Optionen für Ihren eigenen Chatnamen.
	
	HARD Parameter führt dazu, daß der Benutzer diese nicht
	eigenmächtig verändern kann.
	
	Diese Version des Befehls steht nur den Services-Admins
	zur Verfügung.
	Andere Benutzer können nur Limits für eigene Chatnamen oder
	Räume setzen, diese aber NICHT aufheben und keine Limits
	grösser als %d setzen.

MEMO_SERVADMIN_HELP_INFO
	Syntax: INFO [Chatname | Raum]
	
	Zeigt Information über die gelesenen und nicht gelesenen Memos
	und über MemoServ-relevanten Einstellungen. Wenn Sie einen Raum
	angeben, werden Information über diesen Raum gezeigt. 
	Wenn Sie einen Chatnameen angeben, werden Information über
	diesen Chatnamen gezeigt. Diese Version des Befehls steht nur
	den Services-Admins zur Verfügung.

###########################################################################
#
# OperServ help messages
#
###########################################################################

OPER_HELP
	%S Befehle:
	    GLOBAL      Schickt ein Notice zu allen Benutzern.
	    STATS       Statistiken über Services und Netzwerk.
	    OPER LIST   Liste der Services-Operatoren.
	    ADMIN LIST  Liste der Services-Admins.
	
	Befehle nur für Services-Operatoren und Services-Admins:
	    MODE        Setzt Modi für dem Raum.
	    KICK        Kickt Benutzer aus dem Raum.
	    CLEARMODES  Setzt alle Modes von einem Raum neu.
	    CLEARCHAN   Ein Masskick für den Raum.
	    KILLCLONES	Killt alle Benutzer von einem Host.
	    AKILL       Bearbeitet die Akill-Liste.
	    SESSION	Zeigt die Liste der Host-Sitzungen
	    EXCEPTION	Bearbeitet die Sitzungslimit-Ausnahmen.
	    LOGONNEWS	Bearbeitet die Liste der Logon-News.
	    OPERNEWS	Bearbeitet die Liste der Oper-News.
	
	Befehle nur für Services-Admins:
	    OPER        Bearbeitet die Liste der Services-Operatoren.
	    JUPE        Setzt ein Jupiter über ein Server.
	    RAW         Schickt ein RAW Befehl zum IRC server.
	    SET         Setzt Services-Optionen.
	    UPDATE      Speichert die Services-Datenbank.
	    QUIT        Beendet Services.
	    SHUTDOWN   	Speichert die Datenbank und beendet Services.
	    RESTART     Speichert die Datenbank und startet Services neu.
	    SU          Gibt einem Admin Services-Root Rechte.

	Befehle nur für den Services-Root:
	    ADMIN       Bearbeitet die Liste der Services-Admins.

	Hinweis: Alle Befehle zu %S werden geloggt!

OPER_HELP_GLOBAL
	Syntax: GLOBAL Text
	
	Ermöglicht IRC-Operatoren die Nachricht an jeden
	im IRC-Netz zu schicken.
	Der Text ist ein Notice vom Chatnamen %s.

OPER_HELP_STATS
	Syntax: STATS [RESET | AKILL | ALL]
	
	Ohne Parameter gibt dieses Befehl die Anzahl der Opers und
	Benutzer, die Maximale Anzahl von Benutzer und die Daten, wann
	Services gestartet war und für wie lange Services aktiv ist.
	
	RESET-Option setzt die maximale Anzahl der Benutzer
	auf die aktuelle Anzahl.
	
	AKILL-Option gibt den Zustand der AKILL Liste und die 
	aktuelle Ablaufzeit für ein Autokill.
	
	ALL-Option steht nur Services-Admins zur verfügung und
	zeigt Information über Speicherbenutzung von Services.
	In großen Netzwerken kann dieses Services für kurze Zeiten
	anhalten (einfrieren), daher muß man diesen Befehl nicht
	ungeachtet benutzen.
	
	Anstatt STATS kann UPTIME auch benutzt werden.

OPER_HELP_OPER
	Syntax: OPER ADD Chatname
	        OPER DEL Chatname
	        OPER LIST
	
	Ermöglicht die Listen der Services-Admins und Services-Operator
	zu bearbeiten. Alle Benutzer in dieser Liste können die Befehle
	der Services-Operatoren benutzen, sofern sie sich dem %s
	gegenüber identifiziert haben.
	
	OPER LIST kann jeder IRC-Oper benutzen. Die anderen
	stehen nur den Services-Admins zur Verfügung.

OPER_HELP_ADMIN
	Syntax: ADMIN ADD Chatname
	        ADMIN DEL Chatname
	        ADMIN LIST
	
	Erlaubt dem Services-Root, die Liste der Services-Admins zu
	bearbeiten. Alle Benutzer in dieser Liste können die Befehle
	der Services-Admins benutzen, sofern sie sich dem %s
	gegenüber identifiziert haben.
	
	ADMIN LIST kann jeder IRC-Oper benutzen. Die anderen
	stehen nur dem Services-Root zur Verfügung.

OPER_HELP_MODE
	Syntax: MODE Raum Mode
	
	Erlaubt Services-Operatoren, Modi für den Raum zu setzen.
	Die Parameter sind die gleichen wie bei den normalen /MODE
	Befehl.
	
	Dieser Befehl steht nur den Services-Operatoren zur Verfügung.

OPER_HELP_CLEARMODES
	Syntax: CLEARMODES Raum [ALL]
	
	Setzt alle Modes im Raum zurück. Diese sind i,k,l,m,n,t,p,s
	und alle Bans. Die ALL Option führt dazu, daß alle Op
	und Voices (+o und +v) gelöscht werden.
		
	Dieser Befehl steht nur den Services-Operatoren zur Verfügung.

OPER_HELP_CLEARCHAN
	Syntax: CLEARCHAN Raum
	
	Führt ein Masskick auf den gegebenen Raum aus. 
	
	Dieser Befehl steht nur den Services-Operatoren zur Verfügung.

OPER_HELP_KICK
	Syntax: KICK Raum Chatname Grund
	
	Ermöglicht IRC-Operatoren einen Benutzer aus einem Raum
	zu kicken.
	Die Parameter sind die selben wie bei /KICK. Der Grund
	erscheint im Kick-Text mit dem Chatname des Opers, der
	dieses Befehl benutzt hat. Zum Beispiel :
	
	*** SpamMan has been kicked off channel #kanal by %S
	(Enygma (Floodder!))
	
	Dieser Befehl steht nur den Services-Operatoren zur Verfügung.

OPER_HELP_AKILL
	Syntax: AKILL ADD [+Dauer] Mask Grund
	        AKILL DEL Mask
	        AKILL LIST [Mask] [NOEXPIRE]
	        AKILL VIEW [Mask] [NOEXPIRE]
	
	Erlaubt Services-Operatoren die Autokill-Liste zu bearbeiten.
	Wenn ein Benutzer in der AKILL Liste sich mit dem IRC-Server
	verbinden möchte, wird Services den Benutzer per KILL entfernen,
	und ein Ban (K-Line) setzen.
	
	AKILL ADD trägt die user@host Maske in die AKILL-Liste
	mit dem zu erwähnenden Grund ein. Der Grund muß angegeben
	werde.
	AKILL DEL löscht den AKILL-Eintrag aus der Liste.
	AKILL LIST allein listet die komplette AKILL Liste, mit einem
	Parameter werden nur die passenden Einträge gelistet.
	AKILL VIEW zeigt zusätzlich zu LIST auch, wer diesen AKILL
	ausgeführt hat, und wann der AKILL ablaufen wird. 
	Wenn die NOEXPIRE-Option angegeben worden ist, werden nur die
	Einträge angezeigt, die nicht ablaufen.
	Mit AKILL ADD kann eine Dauer angegeben, die besagt,
	wann der Autokill ablaufen wird. Diese sollte mit einer
	Zeiteinheit versehen werden: d (Tage), h (Stunden)
	oder m (Minuten). Eine Kombination (z.B. 1h30m) ist
	nicht erlaubt. Der Standardeinheit ist ein Tag, +30
	bedeutet somit 30 Tage. Ein Autokill, der nicht ablaufen
	soll, muß mit einer Zeitangabe von +0 versehen werden.
	Die Standardzeit für AKILL kann vom Server mit dem
	Befehl STATS AKILL abgefragt werden.
	
	Der Grund ist nur für andere IRC-Operatoren gedacht, und
	wird nicht bei den KILL-Nachrichten geschickt.
	
	Dieser Befehl steht nur den Services-Operatoren zur Verfügung.

OPER_HELP_EXCEPTION
	Syntax: EXCEPTION ADD [+Dauer] Maske Limit Grund
	        EXCEPTION DEL {Mask | Liste}
	        EXCEPTION MOVE Nummer Position
	        EXCEPTION LIST [Mask | Liste]
	        EXCEPTION VIEW [Mask | Liste]
	
	Erlaubt Services-Admins die Liste der Hosts mit spezifischen 
	Sitzungslimits zu bearbeiten (z.B. Shell Servers). Wenn ein Host
	seinen Sitzungslimit erreicht hat, werden alle weiteren Benutzer
	gekillt.  Bevor ein Benutzer gekillt ist, wird er per /NOTICE vom
	%S über Sitzungslimits informiert.  Der Inhalt dieser Nachricht
	ist eine Konfigurationseinstellung.
	
	EXCEPTION ADD trägt die Hostmaske in die Ausnahme-Liste ein.
	Beachten Sie, daß nick!user@host und user@host nicht
	gültig sind, weil Chatnamen und UserIDs dabei nicht relevant sind.
	Limit muß eine Zahl grösser oder gleich Null sein, und zeigt,
	wieviele Benutzer von diesem Host erlaubt sind. Die Zahl 0 bedeutet
	keine Begrenzung.
	Über die Zeitangabe sollte man die AKILL Hilfe durchlesen. 
	EXCEPTION DEL löscht den Host von der Ausnahme-Liste.
	EXCEPTION MOVE schiebt die Ausnahme Nummer nach Position. 
	Die Ausnahmen dazwischen werden hoch oder runtergeschoben.
	EXCEPTION LIST und EXCEPTION VIEW zeigen alle aktuellen
	Ausnahmen. Bei der Angame der Maske werden nur die angezeigt, die
	dieser entsprechen.
	Der Unterschied von EXCEPTION VIEW ist, daß VIEW mehr informativ
	ist und enthält die Angaben daüber, wer die Ausnahme eingetragen hat
	und wann die Ausnahme ablaufen wird.
	
	Zu beachten ist, daß der Server den ersten passenden Eintrag
	aus der Liste benutzt. Lange Ausnahme-Listen beeinflußen die
	Performance der Services.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_SESSION
	Syntax: SESSION LIST Grenzwert
	        SESSION VIEW Host
	
	Zeigt den Services-Admins die Sitzungs-Liste.
	
	SESSION LIST zeigt Hosts mit mindestens Grenzwert 
	Sitzungen. Der Grenzwert ist eine Zahl gröser als 1. Dies
	sollte verhindern, daß versehentlich alle Hosts mit einer
	Sitzung aufgelistet werden. 
	
	SESSION VIEW zeigt detailierte Information über eine
	Sitzung, sowie wieviele Sitzungen aktiv sind und Sitzungs-Limits.
	
	Host darf keine Platzhalter beinhalten.
	
	Konsultieren Sie Hilfe für EXCEPTION für weitere
	Informationen über Sitzungslimits und deren Bearbeitung.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_SU
	Syntax: SU Passwort
	
	Gibt einem Services-Admin, Services-Root Rechte. Das Passwort
	wird mit dem Befehl SET SUPASS gesetzt, und muß gesetzt sein,
	bevor man SU Benutzen kann. Die Services-Root Rechte bleiben erhalten,
	bis der Chatname geändert, oder die IRC Sitzung beendet wird.
	
	WARNUNG: Wenn ein falsches Passwort angegeben wird, wird eine
	Warnmeldung an alle IRC-Operatoren geschickt.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_JUPE
	Syntax: JUPE Server [Grund]
	
	Setzt ein Jupiter auf den gegebenen Server, indem Services einen
	fake Server zum Netz verbindet, damit der tatsächliche Server
	mit dem selben namen sich nicht mehr verbinden kann. Der Jupiter
	kann per SQUIT entfernt werden.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_RAW
	Syntax: RAW [Text]
	
	Schickt eine Zeichenkette direkt zum Server, zu dem Services
	verbunden ist (RAW). Dieser Befehl sollte NICHT benutzt werden,
	wenn man nicht sicher ist, was man tut.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.
	
OPER_HELP_SET
	Syntax: SET Option Parameter
	
	Setzt verschiedene Optionen. Diese sind:
	
	    READONLY   Modi Read-Only und Read-Write.
	    DEBUG      (De)Aktivierung von Debug Modus.
	    SUPASS     Setzt das Passwort für den SU-Befehl
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_SET_READONLY
	Syntax: SET READONLY {ON | OFF}
	
	Aktiviert und deaktiviert das Read-Only Modus. Im Read-Only-Modus
	können normale Benutzer die Services-Daten nicht modifizieren,
	inkl. Die Zugriffslisten, etc. IRC-Operatoren mit entsprechenden
	Zugriffsrechten können Chatnamen und Räume verbieten (FORBID) und
	löschen (DROP) und die AKILL-Liste modifizieren. Die Daten werden
	jedoch nicht gespeichert, wenn man vor dem Shutdown oder Restart
	den Read-Only-Modus nicht deaktiviert hat.
	
	Äquivalent zu der Komandozeilenoption readonly.

OPER_HELP_SET_DEBUG
	Syntax: SET DEBUG {ON | OFF | Nummer}
	
	Aktivert das Debug-Modus. Wenn aktiv, werden alle Daten, die zum
	oder vom Server gesendet werden und eine anzahl anderer Debug-Infos
	in die Log-Datei gespeichert. Die Nummer, wenn angegeben, steuert
	die Option Debug-Level.
	
	Äquivalent zu der Komandozeilenoption debug.

OPER_HELP_SET_SUPASS
	Syntax: SET SUPASS [Passwort]
	
	Setzt das Services-Root-Passwort. Das Passwort muß gesetzt
	werden, bevor man den SU-Befehl zum ersten mal nutzt.
	Wenn das Passwort nicht gesetzt ist, ist der SU-Befehl
	deaktiviert.
	
	Diese Option steht nur dem Services-Root zur Verfügung.

OPER_HELP_UPDATE
	Syntax: UPDATE
	
	Speichert die Services-Datenbank.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_QUIT
	Syntax: QUIT
	
	Beendet Services ohne die Datenbank zu speichern.
	Dieser Befehl sollte nur dann benutzt werden, wenn die
	Daten im Huptspeicher korrupt sind und man die korrupten
	Daten nicht speichern möchte.
	Für das normale beenden der Services sollen die den Befehl
	SHUTDOWN benutzen.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_SHUTDOWN
	Syntax: SHUTDOWN
	
	Im Gegensatz zu QUIT speichert die Datenbank, 
	und dann beendet Services.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_RESTART
	Syntax: RESTART
	
	Speichert die Datenbank und startet Services neu.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

OPER_HELP_KILLCLONES
	Syntax: KILLCLONES Chatname
	
	Killt alle Benutzer von einem und demselben Host. Ein 
	temporärer AKILl der Form *@host, wird aktiviert,
	um sofortige Versuche des Verbindens zu hindern. Ausserdem
	wird ein Wallops gesendet, wo steht, wer den Befehl benutzt
	hat, welcher Host mit ins Leidenschaft gezogen ist und wieviele
	Benutzer gekillt werden. Um Klone lostzuwerden, ist es sehr
	hilfsreich.
	
	Dieser Befehl steht nur den Services-Admins zur Verfügung.

###########################################################################
#
# StatServ help messages
#
############################################################################

STAT_HELP
	%S gibt statistische Information über das IRC Network, die Server
	und die Benutzer. Für Information können Sie /msg %S HELP Befehl
	benutzen.
	
	    SERVERS     Server-Statistiken
	    USERS       Benutzer-Statistiken

STAT_HELP_SERVERS
	Syntax: SERVERS STATS
	        SERVERS LIST [Maske]
	        SERVERS VIEW [Maske] [ONLINE | OFFLINE]
	
	Zeigt statistische Information über die Server im Network an.
	
	SERVERS STATS zeigt eine kurze Zusammenfassung der verfügbaren
	(online) und der unsichtbaren (offline) Server an.

	SERVERS LIST zeigt eine Liste der verfügbaren Server und kurze
	Statistik über diese Server an.

	SERVERS VIEW zeigt eine Liste der verfügbaren Server und eine
	detailierte Statistik über diese Server an. Die ONLINE und
	OFFLINE Optionen bewirken, daß die verfügbaren, oder die offline
	gegangenen Server angezeigt werden.
	
	Die Maske bewirkt, daß nur passende Server angezeigt werden.

STAT_HELP_USERS
	Syntax: USERS STATS
	
	Zeigt Statistik über die Benutzer des Netzwerks.

STAT_SERVROOT_HELP_SERVERS
	Syntax: SERVERS STATS
	        SERVERS LIST [Maske]
	        SERVERS VIEW [Maske] [ONLINE | OFFLINE]
	        SERVERS DELETE Server
	        SERVERS COPY Server NeuerName
	        SERVERS RENAME Server NeuerName
	
	Zeigt statistische Information über die Server im Network an.
	
	SERVERS STATS zeigt eine kurze Zusammenfassung der verfügbaren
	(online) und der unsichtbaren (offline) Server an.

	SERVERS LIST zeigt eine Liste der verfügbaren Server und kurze
	Statistik über diese Server an.

	SERVERS VIEW zeigt eine Liste der verfügbaren Server und eine
	detailierte Statistik über diese Server an. Die ONLINE und
	OFFLINE Optionen bewirken, daß die verfügbaren, oder die offline
	gegangenen Server angezeigt werden.
	
	Die maske bewirkt, daß nur passende Server angezeigt werden.
	
	DELETE löscht gespeicherte Statistiken über den gegebenen Server.
	COPY dupliziert die Statistiken über den gegebenen Server.
	RENAME benennt Statistiken über den gegebenen Server um.

	Diese drei Befehle stehen nur dem Services-Root zur Verfügung.


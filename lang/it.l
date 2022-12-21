# Emacs mode: -*- text -*-

# Italian language file.
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
# of a message without changing the order of the parameters, let me know
# (achurch@dragonfire.net) which message is causing a problem and I'll see
# what I can do.
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
	Italian

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
	Lun
	Mar
	Mer
	Gio
	Ven
	Sab
	Dom
# %A
STRFTIME_DAYS_LONG
	Domenica
	Lunedì
	Martedì
	Mercoledì
	Giovedì
	Venerdì
	Sabato
# %b
STRFTIME_MONTHS_SHORT
	Gen
	Feb
	Mar
	Apr
	Mag
	Giu
	Lug
	Ago
	Set
	Ott
	Nov
	Dic
# %B
STRFTIME_MONTHS_LONG
	Gennaio
	Febbraio
	Marzo
	Aprile
	Maggio
	Giugno
	Luglio
	Agosto
	Settembre
	Ottobre
	Novembre
	Dicembre


# "day", "hour", "minute", and "second" in singular and plural.
STR_DAY
	giorno
STR_DAYS
	giorni
STR_HOUR
	ora
STR_HOURS
	ore
STR_MINUTE
	minuto
STR_MINUTES
	minuti
STR_SECOND
	secondo
STR_SECONDS
	secondi


# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	, 


# Various error messages.
USER_RECORD_NOT_FOUND
	Errore Interno - Impossibile procedere.
UNKNOWN_COMMAND
	Comando sconosciuto %s.
UNKNOWN_COMMAND_HELP
	Comando sconosciuto %s.  "/msg %s HELP" per un aiuto..
SYNTAX_ERROR
	Sintassi: %s
MORE_INFO
	/msg %s HELP %s per maggiori informazioni.
NO_HELP_AVAILABLE
	Nessun aiuto disponibile per %s.

BAD_USERHOST_MASK
	La maschere deve essere nel formato user@host.

SERVICE_OFFLINE
	%s non e' online adesso.
READ_ONLY_MODE
	Notice: Servizi in modalita' sola lettura. Impossibilitato a salvare i cambiamenti.
PASSWORD_INCORRECT
	Password non corretta.

# What's the difference between "Access denied" and "Permission denied"?
# Very little; you can safely make them the same message with no real loss
# of meaning.  If you want to make a distinction, "Access denied" is
# usually used more generally; for example, a non-oper trying to access
# OperServ gets "Access denied", while a non-Services admin trying to use
# NickServ SET NOEXPIRE gets "Permission denied".
ACCESS_DENIED
	Accesso negato.
PERMISSION_DENIED
	Permesso negato.

MORE_OBSCURE_PASSWORD
	Usa una password più sicura.  La password deve essere lunga almeno cinque caratteri e non puo' contenere spazi. Ti consiglio di non usare come password il tuo vero nome o il tuo nick.
PASSWORD_TRUNCATED
	Notice:  La tua password e' stata troncata a %d caratteri.

NICK_NOT_REGISTERED
	Il tuo nick non e' registrato.
NICK_NOT_REGISTERED_HELP
	Il tuo nick non e' registrato.  Scrivi /msg %s HELP per maggiori informazioni su come registrarlo.
NICK_X_NOT_REGISTERED
	il nick %s non e' registrato.
NICK_X_NOT_IN_USE
	Il nick %s non e' in uso.
NICK_X_FORBIDDEN
	Nick %s may not be registered or used.
CHAN_X_NOT_REGISTERED
	Il canale %s non e' registrato.
CHAN_X_NOT_IN_USE
	Il canale %s non esiste.
CHAN_X_FORBIDDEN
	Il canale %s non puo' essere registrato o usato.
NICK_IDENTIFY_REQUIRED
	Identificazione richiesta per questo comando.
	Riprova dopo aver scritto /msg %s IDENTIFY password.
CHAN_IDENTIFY_REQUIRED
	Identificazione richiesta per questo comando.
	Riprova dopo aver scritto /msg %s IDENTIFY %s password.

EXPIRES_NONE
	infinita
EXPIRES_SOON
	scade al prossimo update del database
EXPIRES_M
	scade tra %d minuti
EXPIRES_1M
	scade tra %d minuto
EXPIRES_HM
	scade tra %d ore, %d minuti
EXPIRES_H1M
	scade tra %d ore, %d minuto
EXPIRES_1HM
	scade tra %d ora, %d minuti
EXPIRES_1H1M
	scade tra %d ora, %d minuto
EXPIRES_D
	scade tra %d giorni
EXPIRES_1D
	scade tra %d giorno

###########################################################################
#
# NickServ messages
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	Questo nick lo possiede gia' qualcun altro. Per favore usane un altro.
	(Se questo e' il tuo nick scrivi /msg %s IDENTIFY password.)
NICK_IS_SECURE
	Questo nick e' registrato e protetto. Se e' il tuo nick scrivi /msg %s IDENTIFY password.  
	Altrimenti scegline un altro.
NICK_MAY_NOT_BE_USED
	Questo nick non puo' essere usato.  Per favore scegline un altro.
DISCONNECT_IN_1_MINUTE
	Se non lo cambi entro 1 minuto sarai disconnesso.
DISCONNECT_IN_20_SECONDS
	Se non lo cambi entro 20 secondi sarai disconnesso.
DISCONNECT_NOW
	Questo nick e' registrato quindi non lo puoi usare.  
	Scegline un altro prima di riconnetterti.

# REGISTER responses
#NICK_REGISTER_SYNTAX
#	REGISTER password
NICK_REGISTRATION_DISABLED
	La resgistrazione dei nickname e' sospesa temporaneamente. Ci scusiamo.
NICK_REGISTRATION_FAILED
	Registrazione fallita.
NICK_REG_PLEASE_WAIT
	Aspetta %d secondi prima di riutilizzare il comando REGISTER.
NICK_CANNOT_BE_REGISTERED
	Il Nick %s non puo' essere registrato.
NICK_ALREADY_REGISTERED
	Il nick %s e' gia registrato.
NICK_REGISTERED
	Nick %s registrato con questo account: %s
NICK_PASSWORD_IS
	La tua password e' %s . Ricordala.

# IDENTIFY responses
NICK_IDENTIFY_SYNTAX
	IDENTIFY password
NICK_IDENTIFY_FAILED
	Identificazione fallita.
NICK_IDENTIFY_SUCCEEDED
	Password accettata. Da adesso sei riconosciuto.

# DROP responses
NICK_DROP_SYNTAX
	DROP
NICK_DROP_DISABLED
	La deregistrazione del nickname e' temporaneamente disabilitata. Ci scusiamo.
NICK_DROPPED
	Il tuo nick e' stato rilasciato.
NICK_X_DROPPED
	Il nick %s e' stato rilasciato.

# SET responses
NICK_SET_SYNTAX
	SET opzioni parametri
NICK_SET_SERVADMIN_SYNTAX
	SET [nick] opzioni parametri
NICK_SET_DISABLED
	Il settaggio delle preferenze e' temporaneamente disabilitato. Ci scusiamo.
NICK_SET_UNKNOWN_OPTION
	Sconosciuta opzione di SET, %s.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	Sconosciuta opzione di SET,  %s, o il tuo nick non e' registrato.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	Non si puo' cambiare la password.
NICK_SET_PASSWORD_CHANGED
	Password cambiata.
NICK_SET_PASSWORD_CHANGED_TO
	Password cambiata a %s.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_SYNTAX
	SET LANGUAGE numero
NICK_SET_LANGUAGE_UNKNOWN
	Linguaggio numero %d sconosciuto.  Scrivi /msg %s HELP SET LANGUAGE per una lista di linguaggi supportati.
NICK_SET_LANGUAGE_CHANGED
	Linguaggio cambiato a Italiano.

# SET URL responses
#NICK_SET_URL_CHANGED
#	URL cambiata a %s.

# SET EMAIL responses
#NICK_SET_EMAIL_CHANGED
#	Indirizzo email cambiato a %s.

# SET KILL responses
NICK_SET_KILL_SYNTAX
	SET KILL {ON | QUICK | OFF}
NICK_SET_KILL_IMMED_SYNTAX
	SET KILL {ON | QUICK | IMMED | OFF}
NICK_SET_KILL_ON
	Protezione KILL settata a ON.
NICK_SET_KILL_QUICK
	Protezione KILL settata a ON, con una riduzione di tempo per il kill.
NICK_SET_KILL_IMMED
	Protezione KILL settata a ON, senza ritardo.
NICK_SET_KILL_IMMED_DISABLED
	L'opzione IMMED non e' disponibile su questo network.
NICK_SET_KILL_OFF
	Protezione KILL OFF.

# SET SECURE responses
NICK_SET_SECURE_SYNTAX
	SET SECURE {ON | OFF}
NICK_SET_SECURE_ON
	L'opzione SECURE e' adesso ATTIVATA.
NICK_SET_SECURE_OFF
	L'opzione SECURE adesso DISATTIVATA.

# SET PRIVATE responses
NICK_SET_PRIVATE_SYNTAX
	SET PRIVATE {ON | OFF}
NICK_SET_PRIVATE_ON
	L'opzione PRIVATE e' adesso ATTIVATA.
NICK_SET_PRIVATE_OFF
	L'opzione PRIVATE e' adesso DISATTIVATA.

# SET HIDE responses
NICK_SET_HIDE_SYNTAX
	SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
NICK_SET_HIDE_EMAIL_ON
	La tua email sara' nascosta a %s.
NICK_SET_HIDE_EMAIL_OFF
	La tua email sara' visibile a  %s.
NICK_SET_HIDE_MASK_ON
	La tua ultima maschera user@host sara' nascosta a %s.
NICK_SET_HIDE_MASK_OFF
	La tua ultima maschera user@host sara' visibile a %s.
NICK_SET_HIDE_QUIT_ON
	Il tuo ultimo messaggio di quit sara' nascosto a %s.
NICK_SET_HIDE_QUIT_OFF
	Il tuo ultimo messaggio di quit sara' visibile a %s.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_SYNTAX
	SET [nickname] NOEXPIRE {ON | OFF}
NICK_SET_NOEXPIRE_ON
	Il nick %s non scadra'.
NICK_SET_NOEXPIRE_OFF
	Il nick %s potra' scadere.

# ACCESS responses
NICK_ACCESS_SYNTAX
	ACCESS {ADD | DEL | LIST} [mask]
NICK_ACCESS_ALREADY_PRESENT
	La maschera %s e' gia' presente nella tua lista di accessi.
NICK_ACCESS_REACHED_LIMIT
	Puoi avere solo %d accessi per nickname.
NICK_ACCESS_ADDED
	%s aggiunto alla tua lista di accessi.
NICK_ACCESS_NOT_FOUND
	%s non presente nella tua lista di accessi.
NICK_ACCESS_DELETED
	%s cancellato dalla tua lista di accessi.
NICK_ACCESS_LIST
	Lista di accessi:
NICK_ACCESS_LIST_X
	Lista di accesso per %s:

# LINK responses
NICK_LINK_SYNTAX
	LINK nick password
NICK_LINK_DISABLED
	Il comando LINK non e' disponibile.
NICK_LINK_FAILED
	LINK fallito.
NICK_NO_LINK_SAME
	Non puoi usare LINK con il tuo stesso nick!
NICK_LINK_CIRCULAR
	Impossibile linkarsi a %s: rilevato un linkaggio circolare.
NICK_LINKED
	Il tuo nick e' stato linkato a %s.

# UNLINK responses
NICK_UNLINK_FAILED
	UNLINK fallito.
NICK_NOT_LINKED
	Il tuo nick non e' linkato con nessuno.
NICK_UNLINKED
	Il tuo nick e' stato unlinkato da %s.
NICK_X_NOT_LINKED
	Il nick %s non e' linkato.
NICK_X_UNLINKED
	Il nick %s e' stato unlinkato da %s.

# LISTLINKS responses
NICK_LISTLINKS_SYNTAX
	LISTLINKS nick [ALL]
NICK_LISTLINKS_HEADER
	Lista i nick linkati a %s:
NICK_LISTLINKS_FOOTER
	%d nick linkati.

# INFO responses
NICK_INFO_SYNTAX
	INFO nick [ALL]
NICK_INFO_REALNAME
	%s e' %s
NICK_INFO_ADDRESS
		Ultimo indirizzo: %s
NICK_INFO_TIME_REGGED
	  Tempo di registrazione: %s
NICK_INFO_LAST_SEEN
	    Visto l'ultima volta: %s
NICK_INFO_LAST_QUIT
	Ultimo messaggio di quit: %s
NICK_INFO_URL
		      URL: %s
NICK_INFO_EMAIL
	  Indirizzo email: %s
NICK_INFO_OPTIONS
		  Opzioni: %s
NICK_INFO_NO_EXPIRE
	Questo nickname non ha scadenza.
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	Protezione KILL
NICK_INFO_OPT_SECURE
	Sicurezza
NICK_INFO_OPT_PRIVATE
	Privato
NICK_INFO_OPT_NONE
	Nessuna

# LIST responses
NICK_LIST_SYNTAX
	LIST pattern
NICK_LIST_SERVADMIN_SYNTAX
	LIST pattern [FORBID] [NOEXPIRE]
NICK_LIST_HEADER
	Lista delle degli accessi corrispondenti a %s:
NICK_LIST_RESULTS
	Fine della lista - %d/%d corrispondenze trovate.

# RECOVER responses
NICK_RECOVER_SYNTAX
	RECOVER nickname [password]
NICK_NO_RECOVER_SELF
	Non puoi usare RECOVER sul tuo setsso nick!
NICK_RECOVERED
	Chi usava il tuo nick e' stato killato. Scrivi
	/msg %s RELEASE %s per riaverlo prima del timeout di un minuto.

# RELEASE responses
NICK_RELEASE_SYNTAX
	RELEASE nickname [password]
NICK_RELEASE_NOT_HELD
	Il nick %s non e' usatoda nessuno.
NICK_RELEASED
	Il tuo nick e' stato rilasciato.

# GHOST responses
NICK_GHOST_SYNTAX
	GHOST nickname [password]
NICK_NO_GHOST_SELF
	Non puoi usare GHOST su di te!
NICK_GHOST_KILLED
	Il ghost con il tuo nick e' stato killato.

# GETPASS responses
NICK_GETPASS_SYNTAX
	GETPASS nickname
NICK_GETPASS_UNAVAILABLE
	GETPASS non disponibile a causa della criptazione delle password abilitata.
NICK_GETPASS_PASSWORD_IS
	La password di %s e'  %s.

# FORBID responses
NICK_FORBID_SYNTAX
	FORBID nickname
NICK_FORBID_SUCCEEDED
	Il nick %s da adesso e' proibito.
NICK_FORBID_FAILED
	Impossibile trovare il nick vietato %s!

###########################################################################
#
# ChanServ messages
#
###########################################################################

# Access level descriptions
CHAN_LEVEL_AUTOOP
	OP automatico
CHAN_LEVEL_AUTOVOICE
	VOICE automatico
CHAN_LEVEL_AUTODEOP
	Nessun OP e' accetato
CHAN_LEVEL_NOJOIN
	Non e' permesso entrare nei canali se sono RESTRICTED
CHAN_LEVEL_INVITE
	Permesso l'uso di INVITE
CHAN_LEVEL_AKICK
	Permesso l'uso di AKICK
CHAN_LEVEL_SET
	Permesso l'uso del comando SET (non per la password del fondatore)
CHAN_LEVEL_CLEAR
	Permesso l'uso di CLEAR
CHAN_LEVEL_UNBAN
	Permesso l'uso di UNBAN
CHAN_LEVEL_OPDEOP
	Permesso l'uso di OP/DEOP
CHAN_LEVEL_ACCESS_LIST
	Permessa la visione della lista di accessi
CHAN_LEVEL_ACCESS_CHANGE
	Permessa la modifica della lista di accessi
CHAN_LEVEL_MEMO
	Permesso a usare list/read per i mode del canale 
# Automatic responses
CHAN_IS_REGISTERED
	Questo canale e' stato registrato con %s.
CHAN_NOT_ALLOWED_OP
	Non ti e' permesso lo stato di OP su %s.
CHAN_MAY_NOT_BE_USED
	Questo canale non puo' essere usato.
CHAN_NOT_ALLOWED_TO_JOIN
	Non hai il permesso di entrare in questo canale.

# REGISTER responses
CHAN_REGISTER_SYNTAX
	REGISTER canale password descrizione
CHAN_REGISTER_DISABLED
	Il servizio di registrazione dei canali e' temporaneamente disabilitato.
CHAN_REGISTER_NOT_LOCAL
	I canale locali non possono essere registrati.
CHAN_MUST_REGISTER_NICK
	Devi prima registrare il tuo nick.  Scrivi /msg %s HELP per informazioni su come farlo.
CHAN_MUST_IDENTIFY_NICK
	Prima identificati con %s , usando il comando:
	/msg %s IDENTIFY password
CHAN_MAY_NOT_BE_REGISTERED
	Il canale %s non puo' essere registrato.
CHAN_ALREADY_REGISTERED
	Il canale %s e' gia' registrato!
CHAN_MUST_BE_CHANOP
	Devi essere OP per registrare il canale.
CHAN_REACHED_CHANNEL_LIMIT
	Hai raggiunto il limite di %d canali.
CHAN_EXCEEDED_CHANNEL_LIMIT
	Hai gia' raggiunto il limite di %d canali.
CHAN_REGISTRATION_FAILED
	Registrazione fallita..
CHAN_REGISTERED
	Il canale %s e' registrato con il tuo nickname: %s
CHAN_PASSWORD_IS
	La tua password per il canale e' %s. Ricordala.

# IDENTIFY responses
CHAN_IDENTIFY_SYNTAX
	IDENTIFY canale password
CHAN_IDENTIFY_FAILED
	Identificazione fallita.
CHAN_IDENTIFY_SUCCEEDED
	Identificazione riuscita, adesso hai il livello di accesso FONDATORE per  %s.

# DROP responses
CHAN_DROP_SYNTAX
	DROP canale
CHAN_DROP_DISABLED
	La deregistrazione del canale e' temporaneamente disabilitata. Ci scusiamo.
CHAN_DROPPED
	Il canale %s e' stato rilasciato.

# SET responses
CHAN_SET_SYNTAX
	SET canale opzioni parametri
CHAN_SET_DISABLED
	Le opzioni dei canali sono temporaneamente disabilitate. Ci scusiamo.
CHAN_SET_UNKNOWN_OPTION
	Opzione SET sconosciuta: %s.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	%s ha troppi canali registrati.
CHAN_FOUNDER_CHANGED
	Fondatore di %s cambiato con %s.

# SET SUCCESSOR responses
CHAN_SUCCESSOR_CHANGED
	Suuccessore di %s cambiato a %s.

# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Non puoi settarti la password.
CHAN_PASSWORD_CHANGED
	%s password cambiata.
CHAN_PASSWORD_CHANGED_TO
	%s password cambiata a %s.

# SET DESC responses
CHAN_DESC_CHANGED
	Descrizione di %s cambiata a %s.

# SET URL responses
CHAN_URL_CHANGED
	URL per %s cambiata a %s.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	Indirizzo email per %s cambiato a %s.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	Messaggio di entrata per %s cambiato.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Impossibile settare il topic.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	Parametro richiesto per MLOCK +k.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	Parametro richiesto perMLOCK +l.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	Il parametro per  MLOCK +l deve essere un numero positivo.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Sconosciuta modalita' %c ignorata.
CHAN_MLOCK_CHANGED
	Modalita' di chiusura di  %s cambiata a %s.
CHAN_MLOCK_REMOVED
	Modalita' di chiusura di %s rimossa.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_SYNTAX
	SET canale KEEPTOPIC {ON | OFF}
CHAN_SET_KEEPTOPIC_ON
	Ritenzione del topic ATTIVATA.
CHAN_SET_KEEPTOPIC_OFF
	Ritenzione del topic DISATTIVATA.

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_SYNTAX
	SET canale TOPICLOCK {ON | OFF}
CHAN_SET_TOPICLOCK_ON
	Chiusura del topic ATTIVATA.
CHAN_SET_TOPICLOCK_OFF
	Chiusura del topic DISATTIVATA.

# SET PRIVATE responses
CHAN_SET_PRIVATE_SYNTAX
	SET canale PRIVATE {ON | OFF}
CHAN_SET_PRIVATE_ON
	Modalita' PRIVATE ATTIVATA.
CHAN_SET_PRIVATE_OFF
	Modalita' privata DISATTIVATA.

# SET SECUREOPS responses
CHAN_SET_SECUREOPS_SYNTAX
	SET canale SECUREOPS {ON | OFF}
CHAN_SET_SECUREOPS_ON
	Opzione di sicurezzaper gli OP ATTIVATA.
CHAN_SET_SECUREOPS_OFF
	Opzione di sicuurezza degli OP DISATTIVATA.

# SET LEAVEOPS responses
CHAN_SET_LEAVEOPS_SYNTAX
	SET canale LEAVEOPS {ON | OFF}
CHAN_SET_LEAVEOPS_ON
	Opzione LEAVE OP ATTIVATA.
CHAN_SET_LEAVEOPS_OFF
	Opzione LEAVE OP DISATTIVATA.

# SET RESTRICTED responses
CHAN_SET_RESTRICTED_SYNTAX
	SET canale RESTRICTED {ON | OFF}
CHAN_SET_RESTRICTED_ON
	Opzione di accesso ristretto ATTIVATA.
CHAN_SET_RESTRICTED_OFF
	Opzione di accesso ristretto DISATTIVATA.

# SET SECURE responses
CHAN_SET_SECURE_SYNTAX
	SET canale SECURE {ON | OFF}
CHAN_SET_SECURE_ON
	Opzione di sicurezza ATTIVATA.
CHAN_SET_SECURE_OFF
	Opzione di sicurezza DISATTIVATA.

# SET OPNOTICE responses
CHAN_SET_OPNOTICE_SYNTAX
	SET canale OPNOTICE {ON | OFF}
CHAN_SET_OPNOTICE_ON
	Opzione OP-NOTICE ATTIVATA.
CHAN_SET_OPNOTICE_OFF
	Opzione OP-NOTICE DISATTIVATA.

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_SYNTAX
	SET canale NOEXPIRE {ON | OFF}
CHAN_SET_NOEXPIRE_ON
	Il canale %s non scadra'.
CHAN_SET_NOEXPIRE_OFF
	Il canale %s potra' scadere.

# UNSET responses
CHAN_SUCCESSOR_UNSET
	Successore di %s non settato.
CHAN_URL_UNSET
	URL for %s non settata.
CHAN_EMAIL_UNSET
	Indirizzo email per %s non settato.
CHAN_ENTRY_MSG_UNSET
	Messaggio di entrata per  %s non settato.

# ACCESS messages
CHAN_ACCESS_SYNTAX
	ACCESS canale {ADD|DEL|LIST} [nick [livello] | lista-di-entrata]
CHAN_ACCESS_DISABLED
	La modifica della ACCESS-LIST e' temporaneamente disattivata. Ci scusiamo.
CHAN_ACCESS_LEVEL_NONZERO
	Il livello di accesso non deve essere zero..
CHAN_ACCESS_LEVEL_RANGE
	Il livello di accesso deve variare solo tra %d e %d inclusi.
CHAN_ACCESS_NICKS_ONLY
	La lista di accesso puo' contenere solo nick registrati.
CHAN_ACCESS_REACHED_LIMIT
	Puoi avere solo %d registrazioni nella lista di accessi.
CHAN_ACCESS_LEVEL_UNCHANGED
	Livello di accesso per %s su %s invariata per %d.
CHAN_ACCESS_LEVEL_CHANGED
	Livello di accesso per %s su %s cambiata a %d.
CHAN_ACCESS_ADDED
	%s aggiunto alla lista di accessi di %s nel livello  %d.
CHAN_ACCESS_NO_SUCH_ENTRY
	Accesso (#%d) non trovato sulla lista di accessi di %s.
CHAN_ACCESS_NOT_FOUND
	%s non trovato nella lista di accessi di %s.
CHAN_ACCESS_NO_MATCH
	Nessun accesso corrispondente nella lista di accessi di %s.
CHAN_ACCESS_DELETED
	%s cancellato dalla lista di accessi di %s.
CHAN_ACCESS_DELETED_ONE
	Cancellato un acceesso dalla lista di accessi di %s.
CHAN_ACCESS_DELETED_SEVERAL
	Cancellati %d accessi dalla lista di accessi di %s.
CHAN_ACCESS_LIST_EMPTY
	La lista di accesso su %s e' vuota.
CHAN_ACCESS_LIST_HEADER
	Lista di accesso per %s:
	  Num   Lev  Nick
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s

# AKICK responses
CHAN_AKICK_SYNTAX
	AKICK canale {ADD | DEL | LIST | ENFORCE} [nick-o-maschera]
CHAN_AKICK_DISABLED
	La modifica della lista di autokick e' temporaneamente disabilitata. Ci scusiamo.
CHAN_AKICK_ALREADY_EXISTS
	%s e' gia' nella lista di autokick di %s.
CHAN_AKICK_REACHED_LIMIT
	Puoi avere solo %d maschere di autokick su un canale.
CHAN_AKICK_ADDED
	%s aggiunto alla autokick list di %s.
CHAN_AKICK_NO_SUCH_ENTRY
	Nessun accesso (#%d) nella autokick list di %s.
CHAN_AKICK_NOT_FOUND
	%s non trovato nella autokick list di %s.
CHAN_AKICK_NO_MATCH
	Nessuna corrispondenza per la autokick list di %s.
CHAN_AKICK_DELETED
	%s cancellato dalla autokick list di %s.
CHAN_AKICK_DELETED_ONE
	Cancellato un utente dalla autokick list di %s.
CHAN_AKICK_DELETED_SEVERAL
	Cancellati %d utenti dalla autokick list di %s.
CHAN_AKICK_LIST_EMPTY
	La autokick list su %s e' vuota.
CHAN_AKICK_LIST_HEADER
	Autokick list per %s:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s

# LEVELS responses
CHAN_LEVELS_SYNTAX
	LEVELS canale {SET | DIS[ABLE] | LIST | RESET} [item [livello]]
CHAN_LEVELS_RANGE
	Il livello deve essere compresi tra %d e %d inclusi.
CHAN_LEVELS_CHANGED
	Livello per %s sul canale %s cambiato a %d.
CHAN_LEVELS_UNKNOWN
	Setting %s not known.  Type /msg %s HELP LEVELS DESC for a list of valid settings.
CHAN_LEVELS_DISABLED
	%s disabilitato sul canale %s.
CHAN_LEVELS_LIST_HEADER
	Livello di accessi per %s:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (disabilitato)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (solo fondatore)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	Livelli di accesso per %s portati sui valori standard.

# INFO responses
CHAN_INFO_SYNTAX
	INFO canale [ALL]
CHAN_INFO_HEADER
	Informazioni per il canale %s:
CHAN_INFO_FOUNDER
	      Fondatore: %s (%s)
CHAN_INFO_NO_FOUNDER
	      Fondatore: %s
CHAN_INFO_DESCRIPTION
	    Descrizione: %s
CHAN_INFO_TIME_REGGED
	     Registrato: %s
CHAN_INFO_LAST_USED
	 Ultimo accesso: %s
CHAN_INFO_LAST_TOPIC
	   Ultimo topic: %s
CHAN_INFO_TOPIC_SET_BY
	     Settato da: %s
CHAN_INFO_URL
		    URL: %s
CHAN_INFO_EMAIL
	Indirizzo email: %s
CHAN_INFO_OPTIONS
		Opzioni: %s
CHAN_INFO_OPT_PRIVATE
	Privato
CHAN_INFO_OPT_KEEPTOPIC
	Ritenzione del Topic
CHAN_INFO_OPT_TOPICLOCK
	Topic protetto
CHAN_INFO_OPT_SECUREOPS
	Secure Ops
CHAN_INFO_OPT_LEAVEOPS
	Leave Ops
CHAN_INFO_OPT_RESTRICTED
	Accesso ristretto
CHAN_INFO_OPT_SECURE
	Secure
CHAN_INFO_OPT_NONE
	Nessuna
CHAN_INFO_MODE_LOCK
	Modo di sicurezza: %s

# LIST responses
CHAN_LIST_SYNTAX
	LIST pattern
CHAN_LIST_HEADER
	Lista di utenti corrispondenti a %s:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	Fine della lista - %d/%d match trovati.

# INVITE responses
CHAN_INVITE_SYNTAX
	INVITE canale

# OP/DEOP/VOICE/DEVOICE responses
CHAN_OPVOICE_SYNTAX
	%s canale nick

# UNBAN responses
CHAN_UNBAN_SYNTAX
	UNBAN channel
CHAN_UNBANNED
	Sei stao sbannato da %s.

# CLEAR responses
CHAN_CLEAR_SYNTAX
	CLEAR canale cosa
CHAN_CLEARED_BANS
	Tutti i ban di %s rimossi.
CHAN_CLEARED_MODES
	Tutti i mode di %s rimossi.
CHAN_CLEARED_OPS
	OP puliti dal canale %s.
CHAN_CLEARED_VOICES
	VOICE puliti dal canale %s.
CHAN_CLEARED_USERS
	Tutti gli utenti kikkati da %s.

# GETPASS responses
CHAN_GETPASS_SYNTAX
	GETPASS canale
CHAN_GETPASS_UNAVAILABLE
	GETPASS non disponibile causa criptaggio delle password.
CHAN_GETPASS_PASSWORD_IS
	La password del canale %s e' %s.

# FORBID responses
CHAN_FORBID_SYNTAX
	FORBID canale
CHAN_FORBID_SUCCEEDED
	Il canale %s e' vietato.
CHAN_FORBID_FAILED
	Impossibile vietare il canale %s!

###########################################################################
#
# MemoServ messages
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	Hai un nuovo memo.
MEMO_HAVE_NEW_MEMOS
	Hai %d nuovi memo.
MEMO_TYPE_READ_LAST
	Scrivi /msg %s READ LAST per leggerlo.
MEMO_TYPE_READ_NUM
	Scrivi /msg %s READ %d per leggerlo.
MEMO_TYPE_LIST_NEW
	Scrivi /msg %s LIST NEW per vederli.
MEMO_AT_LIMIT
	Attenzione: Hai raggiunto il massimo numero di memo (%d).  Non ne potrai ricevere altri finche' non ne cancelli qualcuno.
MEMO_OVER_LIMIT
	Attenzione: Sei oltre il massimo numero di memo (%d). Non ne potrai ricevere altri finche' non ne cancelli qualcuno.
MEMO_NEW_MEMO_ARRIVED
	Hai un nuovo memo da %s.
	Scrivi /msg %s READ %d per leggerla.

# Multi-use responses
MEMO_HAVE_NO_MEMOS
	Non hai nuovi memo.
MEMO_X_HAS_NO_MEMOS
	%s non ha memo.
MEMO_DOES_NOT_EXIST
	Non esiste la memo %d!
MEMO_LIST_NOT_FOUND
	Nessuna memo corrispondente trovata.

# SEND responses
MEMO_SEND_SYNTAX
	SEND {nick | canale} testo-del-memo
MEMO_SEND_DISABLED
	La spedizione di memo e' temporaneamente disabilitata. Ci scusiamo.
MEMO_SEND_PLEASE_WAIT
	Aspetta %d secondi prima di usare SEND di nuovo.
MEMO_X_GETS_NO_MEMOS
	%s non puo' ricevere memo.
MEMO_X_HAS_TOO_MANY_MEMOS
	%s ha troppi memo e non ne puo' ricevere altri..
MEMO_SENT
	Memo spedita a %s.

# LIST responses
MEMO_LIST_SYNTAX
	LIST [canale] [list | NEW]
MEMO_HAVE_NO_NEW_MEMOS
	Non hai nuovi memo.
MEMO_X_HAS_NO_NEW_MEMOS
	%s ha nuovi memo.
MEMO_LIST_MEMOS
	Memo per %s.  Per leggerli scrivi: /msg %s READ num
MEMO_LIST_NEW_MEMOS
	Nuovi memo per %s.  Per leggerli scrivi: /msg %s READ num
MEMO_LIST_CHAN_MEMOS
	Memo per %s.  Per leggerli scrivi: /msg %s READ %s num
MEMO_LIST_CHAN_NEW_MEMOS
	Nuovi memo per %s.  Per leggerli scrivi: /msg %s READ %s num
MEMO_LIST_HEADER
	 Num  Mittente          Data/Ora
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_READ_SYNTAX
	READ [canale] {list | LAST | NEW}
MEMO_HEADER
	Memo %d da %s (%s).  Per cancellarlo scrivi: /msg %s DEL %d
MEMO_CHAN_HEADER
	Memo %d da %s (%s).  Per cancellarlo scrivi: /msg %s DEL %s %d
MEMO_TEXT
	%s

# DEL responses
MEMO_DEL_SYNTAX
	DEL [canale] {num | list | ALL}
MEMO_DELETED_NONE
	Nessun memo cancellato.
MEMO_DELETED_ONE
	Memo %d cancellato.
#MEMO_DELETED_SEVERAL
#	Memo %s cancellati.
MEMO_DELETED_ALL
	Tutti i tuoi memo cancellati.

# SET responses
MEMO_SET_SYNTAX
	SET opzione parametro
MEMO_SET_DISABLED
	Il settaggio di opzioni dei memo e' temporaneamente disabilitato. Ci scusiamo.
MEMO_SET_UNKNOWN_OPTION
	Opzione di SET sconosciuta %s.

# SET NOTIFY responses
MEMO_SET_NOTIFY_SYNTAX
	SET NOTIFY {ON | LOGON | NEW | OFF}
MEMO_SET_NOTIFY_ON
	%s ti avvertira' dell arrivo di nuovi memo a ogni logon e appena ne riceverai una.
MEMO_SET_NOTIFY_LOGON
	%s ti avvertira' dell arrivo di nuove memo a ogni logon e ogni volta che usciray dall AWAY .
MEMO_SET_NOTIFY_NEW
	%s ti avvertira' dell arivo di nuove memo quando queste ti saranno spedite.
MEMO_SET_NOTIFY_OFF
	%s non ti avvertira' dell arrivi di nuove memo.

# SET LIMIT responses
MEMO_SET_LIMIT_SYNTAX
	SET LIMIT [canale] limit
MEMO_SET_LIMIT_SERVADMIN_SYNTAX
	SET LIMIT [user | canale] {limite | NONE} [HARD]
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	Non hai il permesso di cambiarti il limite di memo memorizzabili.
MEMO_SET_LIMIT_FORBIDDEN
	Il limite di memo memorizzabili per %s non puo' essere cambiato.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	Non puoi aumentare il tuo limite di memo memorizzabili a piu' di %d.
MEMO_SET_LIMIT_TOO_HIGH
	Non puoi aumentare il limite di memo per %s piu' di %d.
MEMO_SET_LIMIT_OVERFLOW
	Limite di memo memorizzabile troppo elevato, limite abbassato a %d.
MEMO_SET_YOUR_LIMIT
	Limite di memo memorizzabili: %d.
MEMO_SET_YOUR_LIMIT_ZERO
	Non potrai ricevere memo.
MEMO_UNSET_YOUR_LIMIT
	Limite di memo memorizzabili disattivato.
MEMO_SET_LIMIT
	Limite di memo memorizzabili per %s portato a %d.
MEMO_SET_LIMIT_ZERO
	Limite di memo memorizzabili per %s portato a 0.
MEMO_UNSET_LIMIT
	Limite di memo memorizzabili DISABILITATO per %s.

# INFO responses
MEMO_INFO_SYNTAX
	INFO [canale]
MEMO_INFO_SERVADMIN_SYNTAX
	INFO [nick | canale]
MEMO_INFO_NO_MEMOS
	Non hai memo.
MEMO_INFO_MEMO
	Hai 1 memo.
MEMO_INFO_MEMO_UNREAD
	Hai 1 memo non letto.
MEMO_INFO_MEMOS
	Hai %d memo.
MEMO_INFO_MEMOS_ONE_UNREAD
	Hai %d memo, delle quali 1 non letta.
MEMO_INFO_MEMOS_SOME_UNREAD
	Hai %d memo, delle quali %d non lette.
MEMO_INFO_MEMOS_ALL_UNREAD
	Hai %d memo non lette.
MEMO_INFO_LIMIT
	Il tuo limite di memo memorizzabili e' %d.
MEMO_INFO_HARD_LIMIT
	Il tuo limite di memo memorizzabili e'%d e non puoi cambiarlo.
MEMO_INFO_LIMIT_ZERO
	Il tuo limite di memo memorizzabili e'0, non potrai quindi ricevere nuovi messaggi.
MEMO_INFO_HARD_LIMIT_ZERO
	Il tuo limite di memo memorizzabili e' 0, non potrai quindi ricevere nuovi messaggi e cambiare questo limite..
MEMO_INFO_NO_LIMIT
	Non hai limiti di memo memorizzabili.
MEMO_INFO_X_NO_MEMOS
	%s non ha memo.
MEMO_INFO_X_MEMO
	%s ha 1 memo.
MEMO_INFO_X_MEMO_UNREAD
	%s ha 1 memo e non lo ha ancora letto.
MEMO_INFO_X_MEMOS
	%s ha %d memo.
MEMO_INFO_X_MEMOS_ONE_UNREAD
	%s ha %d memo delle quali 1 non letta.
MEMO_INFO_X_MEMOS_SOME_UNREAD
	%s ha %d memos delle quali %d non lette.
MEMO_INFO_X_MEMOS_ALL_UNREAD
	%s ha %d memo, tutte non lette.
MEMO_INFO_X_LIMIT
	Il limite di memo memorizzabili di %s e' %d.
MEMO_INFO_X_HARD_LIMIT
	Il limite di memo memorizzabili di %s e' %d.
MEMO_INFO_X_NO_LIMIT
	%s non ha limite di memo memorizzabili.

###########################################################################
#
# OperServ messages
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	I servizi non possono cambiare i mode.  Hai il server configurato correttamente?
OPER_BOUNCY_MODES_U_LINE
	I servizi non possono cambiare i mode. Le U:lines del tuo server sono corrette?

# GLOBAL responses
OPER_GLOBAL_SYNTAX
	GLOBAL message

# STATS responses
OPER_STATS_UNKNOWN_OPTION
	Opzione di STATS sconosciuta: %s.
OPER_STATS_CURRENT_USERS
	Utenti correnti: %d (%d ops)
OPER_STATS_MAX_USERS
	Picco di utenti: %d (%s)
OPER_STATS_UPTIME_DHMS
	Servizi online da %d %s, %02d:%02d
OPER_STATS_UPTIME_HM_MS
	Servizi online da %d %s, %d %s
OPER_STATS_USER_MEM
	Utente  : %6d records, %5d kB
OPER_STATS_CHANNEL_MEM
	Canale  : %6d records, %5d kB
OPER_STATS_NICKSERV_MEM
	NickServ: %6d records, %5d kB
OPER_STATS_CHANSERV_MEM
	ChanServ: %6d records, %5d kB
OPER_STATS_OPERSERV_MEM
	OperServ: %6d records, %5d kB
OPER_STATS_AKILL_COUNT
	Numero di AKILLs         : %d
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

# MODE responses
OPER_MODE_SYNTAX
	MODE canale mode

# CLEARMODES responses
OPER_CLEARMODES_SYNTAX
	CLEARMODES canali [ALL]
OPER_CLEARMODES_DONE
	Mdalita' binarie e ban cancellati dal canale %s.
OPER_CLEARMODES_ALL_DONE
	Tutti i mode del canale %s resettati.


# KICK responses
OPER_KICK_SYNTAX
	KICK canale user ragione

# ADMIN responses
OPER_ADMIN_SYNTAX
	ADMIN {ADD | DEL | LIST} [nick]
OPER_ADMIN_ADD_SYNTAX
	ADMIN ADD nick
OPER_ADMIN_DEL_SYNTAX
	ADMIN DEL nick
OPER_ADMIN_SKELETON
	Servizi in modalita' scheletro; comando ADMIN non disponibile.
OPER_ADMIN_EXISTS
	%s e' gia' nella service admin list.
OPER_ADMIN_ADDED
	%s aggiunto alla service Admin list.
OPER_ADMIN_TOO_MANY
	Troppi utenti (%d) nella Admin list; impossibile aggiungere altri.
OPER_ADMIN_REMOVED
	%s rimosso dalla Admin list..
OPER_ADMIN_NOT_FOUND
	%s non presente nella Admin list.
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
	Servizi in modalita' scheletro: comando OPER non disponibile.
OPER_OPER_EXISTS
	%s gia' presente nella Operator list.
OPER_OPER_ADDED
	%s aggiunto alla Operator list.
OPER_OPER_TOO_MANY
	Troppi utenti (%d) nella Operator list; impossibile aggiungere altri.
OPER_OPER_REMOVED
	%s rimosso dalla Operator list.
OPER_OPER_NOT_FOUND
	%s non presente nella Operator list.
OPER_OPER_LIST_HEADER
	Services operator list:

# AKILL responses
OPER_AKILL_SYNTAX
	AKILL {ADD | DEL | LIST | VIEW} [[+expiry] mask [reason]]
OPER_AKILL_ADD_SYNTAX
	AKILL ADD [+expiry] maschera ragione
OPER_AKILL_DEL_SYNTAX
	AKILL DEL maschera
OPER_TOO_MANY_AKILLS
	AKILL list piena!
OPER_AKILL_NO_NICK
	Ricorda: la maschera di AKILL non puo' contenere nick, assicurati di non averne incluso uno nella maschera.
OPER_AKILL_ADDED
	%s aagiunto alla AKILL list.
OPER_AKILL_REMOVED
	%s rimosso dalla AKILL list.
OPER_AKILL_NOT_FOUND
	%s non presente nella AKILL list.
OPER_AKILL_LIST_HEADER
	AKILL list:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, ragione
OPER_AKILL_VIEW_FORMAT
	%s (by %s on %s; %s)
	    %s

# SET responses
OPER_SET_SYNTAX
	SET opzione settaggio
OPER_SET_IGNORE_ON
	Il codice di ignore verra' usato.
OPER_SET_IGNORE_OFF
	Il codice di ignore non verra' usato.
OPER_SET_IGNORE_ERROR
	La modalita' dell ignore deve essere ON o OFF.
OPER_SET_READONLY_ON
	I servizi sono in modalita' sola lettura.
OPER_SET_READONLY_OFF
	I servizi sono in modalita' lettura scrittura.
OPER_SET_READONLY_ERROR
	READONLY puo' essere solo ON o OFF.
OPER_SET_DEBUG_ON
	I servizi sono in debug mode.
OPER_SET_DEBUG_OFF
	I servizi non sono piu' in debug mode.
OPER_SET_DEBUG_LEVEL
	I servizi sono in debug mode (level %d).
OPER_SET_DEBUG_ERROR
	DEBUG puo' essere soloON, OFF, o un numero positivo.
OPER_SET_UNKNOWN_OPTION
	Opzione sconosciuta %s.

# JUPE responses
OPER_JUPE_SYNTAX
	JUPE nome-del-server [ragione]

# RAW responses
OPER_RAW_SYNTAX
	RAW testo

# UPDATE responses
OPER_UPDATING
	Database aggiornato.

# LISTIGNORE responses
OPER_IGNORE_LIST
	Lisat di ignore per i servizi:
OPER_IGNORE_LIST_EMPTY
	Lista di ignore vuota.

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
	LOGONNEWS {ADD|DEL|LIST} [testo|num]
NEWS_LOGON_LIST_HEADER
	Parti del logon:
NEWS_LOGON_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_LOGON_LIST_NONE
	Nessuna news di logon.
NEWS_LOGON_ADD_SYNTAX
	LOGONNEWS ADD text
NEWS_LOGON_ADD_FULL
	Lista delle news piena!
NEWS_LOGON_ADDED
	Aggiunto un nuovo elemento di logon (#%d).
NEWS_LOGON_DEL_SYNTAX
	LOGONNEWS DEL {num | ALL}
NEWS_LOGON_DEL_NOT_FOUND
	Elemento #%d non trovato!
NEWS_LOGON_DELETED
	Elemento #%d cacellato.
NEWS_LOGON_DEL_NONE
	Nessun elemento da cancellare!
NEWS_LOGON_DELETED_ALL
	Tutti gli elementi cancellati.

NEWS_OPER_SYNTAX
	OPERNEWS {ADD|DEL|LIST} [testo|num]
NEWS_OPER_LIST_HEADER
	Elementi delle news per operatori:
NEWS_OPER_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_OPER_LIST_NONE
	Nessuna news per operatori.
NEWS_OPER_ADD_SYNTAX
	OPERNEWS ADD testo
NEWS_OPER_ADD_FULL
	Lista delle news piena!
NEWS_OPER_ADDED
	Aggiunto nuovo elemento alle news (#%d).
NEWS_OPER_DEL_SYNTAX
	OPERNEWS DEL {num | ALL}
NEWS_OPER_DEL_NOT_FOUND
	Elemento di news #%d non trovato!
NEWS_OPER_DELETED
	Elemento #%d cancellato.
NEWS_OPER_DEL_NONE
	Nessun elemento da cancellare!
NEWS_OPER_DELETED_ALL
	All oper news items deleted.

NEWS_HELP_LOGON
	Sintassi: LOGONNEWS ADD text
		  LOGONNEWS DEL {num | ALL}
		  LOGONNEWS LIST
	
	Edita e mostra la lista dei messaggi di logon. Quando un 
	utente si collega questi messaggi gli verranno inviati.
	Comunque non piu' di tre messaggi saranno spediti per
	evitare di floodare l'utente. Se ci sono tre messaggi di
	logon ne verranno inviati solo i tre piu' nuovi.
	
	LOGONNEWS LIST puo' essere usato da tutti gli operatori
	per avere la lista dei messaggi correnti. ADD e DEL 
	possono essere usati dagli amministratori dei servizi.

NEWS_HELP_OPER
	Sintassi: OPERNEWS ADD text
		  OPERNEWS DEL {num | ALL}
		  OPERNEWS LIST
	
	Edita o mostra la lista delle oper news. Quando un utente si
	opera (con l'uso di /OPER), questi messaggi gli verranno
	spediti. (Nel caso ce ne siano piu' di 3 verranno spediti solo
	i tre piu' recenti)
	
	OPERNEWS LIST puo' essere usato da tutti gli IRCop per listare
	le correnti news. ADD e DEL possono essere usati solo dagli
	amministratori dei servizi.

###########################################################################
#
# NickServ help messages
#
###########################################################################

NICK_HELP
	%S Ti permette di registrare il tuo nickname
	e impedire a chiccessia di usarlo al posto tuo. Se il
	nick non viene usato per %d giorni la registrazione 
	scade.
	I comandi seguenti ti permettono di registrare e 
	mantenere il tuo nickname. Per usarli scrivi
	/msg %S command.
	Per maggiori informazioni su come usarli scrivi invece
	/msg %S HELP command.
	
	    REGISTER   Registra un nick
	    IDENTIFY   Identificazione con password per il nick
	    ACCESS     Modifica la lista di indirizzi permessi
	    LINK       Usa il tuo nick come un alias per un altro
	    SET        Seta le opzioni di manutenzione
	    DROP       Deregistra il nick
	    RECOVER    Killa chi usa il tuo nick senza autorizzazione
	    RELEASE    Riprende il controllo del tuo nick dopo RECOVER
	
	Altri comandi: UNLINK, UNSET, GHOST, INFO, LIST, LISTCHANS,
	               STATUS
	
	NOTICE: Questo servizio e' progettato in modo che gli
	altri sappiano con sicurezza che "tu sei tu".
	Non e' da indendersi come un modo di "rubare" dei nick
	ad altri o per altri usi maliziosi.  Gli abusi di %S si
	traducono, come minimo, con la perdita dei nick registrati
	indebitamente.
	
NICK_HELP_EXPIRE_ZERO
	^B%S^B Ti permette di registrare il tuo nickname
	e impedire a chiccessia di usarlo al posto tuo.
	I comandi seguenti ti permettono di registrare e
	mantenere il tuo nickname. Per usarli scrivi
	^B/msg %S ^_command^_^B.
	Per maggiori informazioni su come usarli scrivi invece
	^B/msg %S HELP ^_command^_^B.

	    REGISTER   Registra un nick
	    IDENTIFY   Identificazione con password per il nick
	    ACCESS     Modifica la lista di indirizzi permessi
	    LINK       Usa il tuo nick come un alias per un altro
	    SET        Seta le opzioni di manutenzione
	    DROP       Deregistra il nick
	    RECOVER    Killa chi usa il tuo nick senza autorizzazione
	    RELEASE    Riprende il controllo del tuo nick dopo RECOVER

	Altri comandi: UNLINK, UNSET, GHOST, INFO, LIST, LISTCHANS,
	               STATUS

	^BNOTICE:^B Questo servizio e' progettato in modo che gli
	altri sappiano con sicurezza che "tu sei tu".
	Non e' da indendersi come un modo di "rubare" dei nick
	ad altri o per altri usi maliziosi.  Gli abusi di %S si
	traducono, come minimo, con la perdita dei nick registrati
	indebitamente.

#NICK_HELP_REGISTER
#	Sintassi: REGISTER password
#	
#	Registra il tuo nick. Dopo averlo fatto potrai usare i 
#	comandi SET e ACCESS per configurare il tuo nick.
#	Ti raccomandiamo di ricordarti la password. Nota: la
#	password e case-insensitive
#	
#	Miniguida sulla scelta della password:
#	
#	La pawword non dovrebbe essere indovinabile facilmente,
#	quindi non usare ne il tuo nick come password ne il tuo
#	nome e ne password con meno di 5 caratteri. Il carattere
#	di spazio non e' accettato
	
NICK_HELP_IDENTIFY
	Sintassi: IDENTIFY password
	
	Dice a %S che tu sei veramente il proprietario del nick
	che stai usando. La password e' quella che hai usato
	con il comando REGISTER

NICK_HELP_DROP
	Syntax: DROP
	
	Deregistra il tuo nick da %S. Un nick deregistrato
	risulta disponibile a chiunque. Prima di usare DROP
	devi prima identificarti con la tua password. 
	(/msg %S HELP IDENTIFY per piu' informazioni).

NICK_HELP_ACCESS
	Sintassi: ACCESS ADD maschera
		ACCESS DEL maschera
		ACCESS LIST
	
	Modifica o cisualizza la lista di accesso per il tuo
	nick. Questa e' la lista di indirizzi che saranno 
	automaticamente associati a te e quindi non dovrai ogni
	volta usare IDENTIFY. Nel caso che tu usi il tuo nick
	da un altro indirizzo devi usare IDENTIFY.
	
	Esempi:
	
	    ACCESS ADD achurch@*.dragonfire.net
		Permette l'accesso al nick "achurch" da una qualsiasi
		macchina con qualsiasi host nel dominio dragonfire.net.
	
	    ACCESS DEL achurch@*.dragonfire.net
		Il contrario del comando precedente.
	
	    ACCESS LIST
		Visualizza la ACCESS LIST corrente.

#NICK_HELP_LINK
#	Sintassi: LINK nick password
#	
#	Linka il tuo nick ad un altro, ovvero fa in modo che il nick
#	che stai usando adesso diventi un alias del nick passato 
#	come parametro. Quando usi questo comando l' ACCESS LIST del
#	nick che stai usando viene cancellata e cambiata con quella
#	del nick passato come parametro. I memo vengono invece 
#	aggiunti al nick linkato, quindi assicurati prima di linkare 
#	che il nick bersaglio non abbia troppi memo.
#	
#	Dopo il linkaggio il tuo nick viene convertito in tutti i 
#	servizi, esclusi %S UNLINK and DROP commands. 
#	Anche le liste di CHANSERV vengono convertite e il nick
#	bersaglio guadagna tutti i privilegi del nick linkato.
#	
#	Prima di usare questo comande devi identificarti con la tua
#	password, (usando il comando IDENTIFY ), e devi comunque
#	dare la password del nick a cui ti vuoi linkare.

NICK_HELP_UNLINK
	Sintassi: UNLINK [nick password]
	
	Rimuove un link precedentemente fatto. Tutti i flag di 
	CHANSERV sono copiati nei due nick. I memo non vengono
	copiati, rimangono del nick a cui ci si unlinka.

NICK_HELP_SET
	Sintassi: SET opzione parametri
	
	Setta varie opzioni per il tuo nickname. opzione puo'
	essere una delle seguenti:
	
	    PASSWORD   Cambia la password
	    LANGUAGE   CAmbia il linguaggio dei servizi
	    URL        Associa una URL al tuo nick
	    EMAIL      Associa una email al tuo nick
	    KILL       Abilita disabilita la PROTEZIONE KILL
	    SECURE     Abilita o disabilita' l'opzione SECURE
	    PRIVATE    Evita che tu appaia in un /msg %S LIST
	    HIDE       Nascondi alcune informazioni sul tuo nick
	
	Prima di usare questo comando devi identificarti.
	(/msg %S HELP IDENTIFY per piu' informazioni).
	
	Scrivi /msg %S HELP SET opzione per maggiori
	informazioni su una singola opzione.

NICK_HELP_SET_PASSWORD
	Sintassi: SET PASSWORD nuova-password
	
	Cambia la tua password. Semplice no?

NICK_HELP_SET_LANGUAGE
	Sintassi: SET LANGUAGE numero
	
	Cambia il linguaggio con il quale i servizi comunicano
	con te.	numero deve essere scelto dalla lista di
	linguaggi supportati:
	

NICK_HELP_SET_URL
	Sintassi: SET URL url
	
	Associa al tuo nickname una URL. Questa URL verra'
	mostrata quando qualcuno chiedera' informazioni sul tuo
	nick con il comando INFO

NICK_HELP_SET_EMAIL
	Sintassi: SET EMAIL indirizzo@in.questo.formato
	
	Associa una email al tuo nickname. Questa email verra'	
	mostrata quando qualcuno chiedera' informazioni sul tuo
	nick con il comando ^BINFO^B

NICK_HELP_SET_KILL
	Sintassi: SET KILL {ON | QUICK | IMMED | OFF}
	
	Abilita o disabilita la PROTEZIONE KILL per il tuo nick.
	Con la protezione attivata se uno sconosciuto usa il tuo 
	nick verra' sconnesso entro 60 secondi se non conosce
	la password. 	
	
	Se selezioni QUICK, lo sconosciuto avra' solo 20
	secondi.
	
	Se selezioni IMMED, lo sconosciuto veraa' sconnesso
	senza venire avvertito prima. Per favore non usare questa
	opzione se non necessario.

NICK_HELP_SET_SECURE
	Sintassi: SET SECURE {ON | OFF}
	
	Abilita le funzioni di sicurezza di %S per il tuo nick.
	Con questa opzione devi immettere la password prima di 
	essere riconosciuto come il proprietario del nick.
	In ogni caso, se sei sulla ACCESS LIST, %S non ti auto
	killera' da IRC.

NICK_HELP_SET_PRIVATE
	Sintassi: SET PRIVATE {ON | OFF}
	
	Abiita o disabilita l'opzione di privacy per il tuo
	nick. Se abilitata il tuo nick non apparira' nela lista
	di %S generata dal comando LIST.
	(In ogni caso, se qualcuno conosce esattamente il tuo nick
	puo' avere delle informazioni con il comando di %SINFO.)

NICK_HELP_SET_HIDE
	Sintassi: SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	
	Ti permette di nascondere alcune informazioni se qualcuno
	fara' un %S INFO sul tuo nick.Puoi nascondere la tua
	email (EMAIL), ultima maschera user@host vista (USERMASK),
	e l'ultimo messaggio di uscita (QUIT).
	Il secondo parametro dice se le informazioni devono essere
	mostrate (OFF) o nascoste (ON).

NICK_HELP_RECOVER
	Sintassi: RECOVER nickname [password]
	
	Ti permette di riavere il tuo nick se qualcuno te lo ruba.
	
	Dopo che lo sconosciuto e' stato sconnesso il tuo nick
	non sara' disponibile entro il primo minuto. Per ovviare
	a questa situazione usa il comando RELEASE 
	(/msg %S HELP RELEASE).
	
	Per usare RECOVER devi usare la tua password.

NICK_HELP_RELEASE
	Sintassi: RELEASE nickname [password]
	
	Dice a %S di rimuovere l'impedimento che ti impediva di
	riavere il tuo nick. Di default l'utilizzo del tuo nick
	viene impedito per 1 minuto dopo l'uso di RECOVER.
	
	Per utilizzare questo comando devi usare la tua password.

NICK_HELP_GHOST
	Sintassi: GHOST nick [password]
	
	Termina una connessione fantasma che usa il tuo nick.
	Una sessione ghost avviene quando ad esempio il tuo
	computer crasha mentre sei su IRC.	
	
	Per utilizzare questo comando devi usare la tua password.

NICK_HELP_INFO
	Sintassi: INFO nickname [ALL]
	
	Visualizza le informazioni su un certo nick, come l'URL,
	l' email e l'ultimo messaggio di uscita.

NICK_HELP_LIST
	Sintassi: LIST pattern
	
	Visualizza tutti i nick registrati che ccorrispondono alla
	maschera passata, nel formato nick!user@host. I nick
	con l'opzione PRIVATE abilitata non verranno visualizzati.
	
	Esempi:
	
	    LIST *!joeuser@foo.com
		Lista dei nick usati dalla maschera *!joeuser@foo.com
	
	    LIST *Bot*!*@*
		Lista dei nick con la parola BOT nell username	
	    LIST *!*@*.bar.org
		Lista dei nick nel dominio *.bar.org

NICK_HELP_STATUS
	Sintassi: STATUS nickname...
	
		
	Visualizza un responso per il nick dato,in questo
	formato:
	
	    nickname status-code
	
	dove nickname e' quello passato come parametro e 
	status-code e' uno dei seguenti:
	
	    0 - nessun user online o nick non registrato
	    1 - user non riconosciuto come proprietario del nick
	    2 - user riconosciuto come proprietario via access list
	    3 - user riconosciuto dalla password
	
	Possono essere passati come parametro fino a 16 nick, verranno
	ignorati quelli dopo.
	Nessun messaggio di errore verra' generato nel caso nessun
	nick sara' passato come parametro

NICK_SERVADMIN_HELP
	
	I comandi seguenti sono disponibili agli amministratori
	dei servizi:
	
	    GETPASS    Da' la password di quel nick
			   (solo se la cryptazione e' disabilitata)
	    FORBID     Impedisce a un nickname di essere usato
	
	Gli amministratori posso deregistrare qualsiasi nick senza
	essere a conoscenza della password e possono vederne anche
	la access list (/msg %S ACCESS LIST nick).

NICK_SERVADMIN_HELP_DROP
	Sintassi: DROP [nickname]
	
	Senza parametri deregistra il tuo nickname da %S.
	
	Con un nick come parametro lo deregistra senza il
	bisogno della password.
	Solo gli amministratori dei servizi possono farlo.

NICK_SERVADMIN_HELP_SET
	
	Gli amministratori posono anche settare l'opzione
	NOEXPIRE, con la quale si previene la scadenza
	di un nick.
	Gli amministratori possono anche settare una password
	per un qualsiasi nick con il seguente comando:
	SET nickname option parameters.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Sintassi: SET [nickname] NOEXPIRE {ON | OFF}
	
	Impedise a un nickname di scadere.
	
	Uso limitato agli amministratori dei servizi.

NICK_SERVADMIN_HELP_UNLINK
	
	Gli amministratori dei servizi possono unlinkare un 
	nick senza bisogno della password.	

NICK_SERVADMIN_HELP_LISTLINKS
	Sintassi: LISTLINKS nick [ALL]
	
	Visualizza i nick linkati con il nick passato come
	parametro. Se specificato ALL vengono visualizzati
	i nick con gli stessi privilegi.	
	
	Limitato agli amministratori dei servizi

NICK_SERVADMIN_HELP_LIST
	Sintassi: LIST pattern [FORBIDDEN] [NOEXPIRE]
	
	Visualizza tutti i nick che corrispondono al campione 
	dato, nel formato nick!user@host. I nick con 
	l'opzione  PRIVATE attivata vengono visualizzati
	solo agli amministratori dei servizi. I nick con l'opzione
	NOEXPIRE attivata verranno listati con un ! davanti.
	
	Se l'opzione FORBIDDEN o NOEXPIRE e' data, solo i nick
	che rispettivamente sono vietati o non hanno scadenza	
	verranno visualizzati.
	Opzione limitata agli amministratori dei servizi
	
	Examples:
	
	    LIST *!joeuser@foo.com
		Lista dei nick che corrispondono a *!joeuser@foo.com
	
	    LIST *Bot*!*@*
		Lista dei nick che hanno la parola Bot nel loro nome.
	
	    LIST * NOEXPIRE
		Lista dei nick senza scadenza.

NICK_SERVADMIN_HELP_GETPASS
	Sintassi: GETPASS nickname
	
	DA la password per il nickname passato come parametro.	
	Nota: quendo questo comando e' usato un globop viene 
	emesso.
	
	Riservato agli amministratori dei servizi.
	
	Questo comando non e' disponibile se la criptazione e'
	abilitata

NICK_SERVADMIN_HELP_FORBID
	Sintassi: FORBID nickname
	
	Impedisce uso e registrazione di un nickname
	
	Riservato agli amministratori dei servizi.

###########################################################################
#
# ChanServ help messages
#
###########################################################################

#CHAN_HELP
#	%S ti permette di registrare i tuoi canali.  %S puo'
#	anche prevenire che un canale venga "takeoverato" .
#	I comandi disponibili sono visualizzati di seguente:
#
#	    REGISTER   Registra un canale
#	    IDENTIFY   Ti identifica con la tua password
#	    SET        Setta le opzioni e le informazioni del canale
#	    ACCESS     Modifica la lista degli utenti privilegiati
#	    LEVELS     Ridefinisce la lista dei livelli di accesso
#	    AKICK      Mantiene la AutoKICK list
#	    DROP       Deregistra un canale
#	
#	Altri comandi: INFO, LIST, INVITE, OP, DEOP, UNBAN,
#	               CLEAR

CHAN_HELP_EXPIRES
	
	Da notare che i canali non usati per %d giorni (cioe' 
	che nessun utente registrato nella access list ci entra)
	il canale viene automaticamente deregistrato perdendo
	la lista di accesso.	

CHAN_HELP_REGISTER
	Sintassi: REGISTER canale password descrizione
	
	Registra un canale con %S. Per farlo devi essere OP in 
	quel canale. La password e' usata con il comando 
	IDENTIFY per permetterti di cambiare le opzioni
	del canale.L'ultimo parametro, che deveessere incluso,
	e' una descrizione generale degli scopi del canale.
	
	Quando registri un canale sei visto come il fondatore, al
	quale e' permesso cambiare tutte le opzioni relative al 
	proprio canale.	
	%S da al fondatore l'op automaticamente in un canale
	registrato. Guarda il comando ACCESS (/msg %S HELP ACCESS)
	per informazioni su come dare agli altri utenti alcuni
	di questi privilegi.
	
	NOTICE: Per registrare un canale devi prima registrare 
	il tuo nick, per farlo scrivi /msg %s HELP per informazioni
	su come farlo.

CHAN_HELP_IDENTIFY
	Sintassi: IDENTIFY canale password
	
	Fa in modo che %S ti riconosca come fondatore del canale.
	Molti comandi chiedono prima che tu usi IDENTIFY prima
	di poterli usare.	
	La password e' quella che hai usato con il comando
	REGISTER

CHAN_HELP_DROP
	Sintassi: DROP canale
	
	Deregistra un canale. Puo' essere usato solo dal 
	fondatore, che deve usare prima il comando
	IDENTIFY.

#CHAN_HELP_SET
#	Sintassi: SET canale opzione parametri
#	
#	Fa modo che il fondatore del canale possa settare delle
#	opzioni riguardanti lo stesso. Il fondatore deve prima
#	identificarsi con IDENTIFY prima di usare SET.
#	
#	Opzioni disponibili:
#	
#	    FOUNDER     Setta il fondatore del canale
#	    SUCCESSOR   Setta il successore del canale
#	    PASSWORD    Setta la password del fondatore
#	    DESC        Setta la descrizione del canale
#	    URL         Associa una URL al canale
#	    EMAIL       Associa una email al canale
#	    ENTRYMSG    Setta un messaggio di benvenuto per chi entra
#	    TOPIC       Cambia il topic
#	    KEEPTOPIC   Lascia il topic anche quando non c'e' nessuno
#	    TOPICLOCK   Si puo' cambiare il topic solo con SET TOPIC
#	    MLOCK       Blocca i mode del canale
#	    PRIVATE     Nasconde il canale al comando LIST
#	    RESTRICTED  Restringe l'accesso al canale
#	    SECURE      Attiva le opzioni di sicurezza di %S
#	    SECUREOPS   Alto controllo per gli operatori
#	    LEAVEOPS    Non deoppare mai gli user
#	    OPNOTICE	Manda un notice agli OP
#	
#	Scrivi /msg %S HELP opzione per maggiori informazioni.

CHAN_HELP_SET_FOUNDER
	Sintassi: SET canale FOUNDER nick
	
	Cambia il fondatore del canale, che puo' essere solo un
	nick registrato

CHAN_HELP_SET_SUCCESSOR
	Sintassi: SET canale SUCCESSOR nick
	
	Cambia il successore del canale. Se il nick del fondatore
	scade o viene deregistrato il successore diventa il nuovo
	fondatore. In ogni caso, se il fondatore ha troppi canali
	registrati (%d), il canale viene deregistrato subito, 
	e il successore ne diventa fondatore. Il nick deve essere
	registrato.

CHAN_HELP_SET_PASSWORD
	Sintassi: SET canale PASSWORD password
	
	Setta la password che permette l'identificazione come
	fondatore del canale.

CHAN_HELP_SET_DESC
	Sintassi: SET canale DESC descrizione
	
	Setta la descrizione per il canale che viene mostrata
	con i comandi LIST e INFO.

#CHAN_HELP_SET_URL
#	Sintassi: SET canale URL [url]
#	
#	Associa una URL al canale che viene mostrata con il
#	comando INFO. Se non viene dato nessun parametro
#	cancella l'URL corrente.

#CHAN_HELP_SET_EMAIL
#	Sintassi: SET canale EMAIL [indirizzo]
#	
#	Associa un email al canale che viene mostrata con il
#	comando INFO command. Se non viene dato nessun
#	parametro cancella l'email corrente.

#CHAN_HELP_SET_ENTRYMSG
#	Sintassi: SET canale ENTRYMSG [messaggio]
#	
#	Setta un messaggio che viene mandato come NOTICE a
#	chiunque entra il canale. Se non viene passato nessun
#	parametro cancella il messaggio corrente.

CHAN_HELP_SET_TOPIC
	Sintassi: SET canale TOPIC topic
	
	Fa in modo che %S setti un topic per il canale. Molto
	utile insieme al comando SET TOPICLOCK.

CHAN_HELP_SET_KEEPTOPIC
	Sintassi: SET canale KEEPTOPIC {ON | OFF}
	
	Attiva o disattiva la ritenzione del topic per un
	canale. Quando la ritenzione e' attivata il topic viene
	ricordato da %S anche quando non ci sono user nel
	canale, e viene risettato appena entra qualcuno.

CHAN_HELP_SET_TOPICLOCK
	Sintassi: SET canale TOPICLOCK {ON | OFF}
	
	Attiva o disattiva il blocco del topic per un canale.
	Con il blocco attivato %S non permette di cambiare il 
	topic tranne che con il comando SET TOPIC.

CHAN_HELP_SET_MLOCK
	Sintassi: SET canale MLOCK mode
	
	Setta il blocco dei mode per un canale. %S ti permette
	di definire che certi mode per il tuo canale siano 
	sempre attivati o disattivati. I mode che possono essere
	bloccati sono i, k, l, m, n, p, 
	s, e t; ognuno di questi puo' essere bloccato o
	no. I parametri hanno la stessa sintassi del comando di
	molti client IRC /MODE che e', mode preceduti da un
	+ sono bloccati e quelli preceduti da un - sono sbloccati.
	
	Attenzione:  Se setti una chiave per il canale, come 
	nel secondo esempio devi anche settare la modalita'
	RESTRICTED (guarda HELP SET RESTRICTED), o chiunque
	entri nel canale quando e' vuoto possono vedere la chiave!
	
	Esempi:
	
	    SET #canale MLOCK +nt-iklps
		Forza i mode n e t on, e i mode i, k, l, p, and
		s off.  Mode m e' lasciato libero di essere on o off
	
	    SET #canale MLOCK +knst-ilmp padanialibera
		Forza i mode k, n, s, e t on, e i mode i, l, m,
		e p off.  Forza anche la chiave del canale a 
		essere "padanialibera".
	
	    SET #canale MLOCK +
		Rimuove il blocco dei mode; tutti i mode saranno
		liberi di essere cambiati da chiunque.	        

CHAN_HELP_SET_PRIVATE
	Sintassi: SET canale PRIVATE {ON | OFF}
	
	Abilita o disabilita l'opzione private per un canale.
	Quando private e' abilitata, un /msg %S LIST non 
	includera' questo canale nella lista.

CHAN_HELP_SET_RESTRICTED
	Sintassi: SET canale RESTRICTED {ON | OFF}
	
	Abilita o disabilita l' accesso ristretto per un canale.
	Quando l'opzione accesso ristretto e' settata, gli user
	che normalmente non sarebbero OP saranno kikkati e bannati
	dal canale immediatamente.

CHAN_HELP_SET_SECURE
	Sintassi: SET canale SECURE {ON | OFF}
	
	Abilita le opzioni di sicurezza di %S per un canale.
	Quando SECURE e' settato, solo gli utenti che hanno
	un nick registrato con %s e si sono identificati con la
	loro password potranno entrare nel canale.

CHAN_HELP_SET_SECUREOPS
	Sintassi: SET canale SECUREOPS {ON | OFF}
	
	Abilita o disabilita l'opzione op sicuri per un canale.
	Con l'opzione op sicuri settata, gli user che non sono
	nella userlist non avranno l'OP nel canale.

#CHAN_HELP_SET_LEAVEOPS
#	Sintassi: SET canale LEAVEOPS {ON | OFF}
#	
#	Abilita o disabilita l'opzione lascia gli opper un canale.
#	Con l'opzione lascia gli op settata, ChanServ non
#	deoppera' mai nessuno se non con il comando DEOP.

CHAN_HELP_SET_OPNOTICE
	Sintassi: SET canale OPNOTICE {ON | OFF}
	
	Abilita o disabilita l'opzione op-notice per un canale.
	Con l'opzione op-notice settata, ChanServ mandera' un 
	notice a tutti gli OP quando i comandi OP o DEOP 
	saranno usati.

CHAN_HELP_ACCESS
	Sintassi: ACCESS canale ADD nick livello
		  ACCESS canale DEL {nick | entry-num | list}
		  ACCESS canale LIST [maschera | list]
	
	Mantiene una lista di accessi per un canale. Questa lista
	specifica gli user abilitati ad avere l'OP o ad accedere
	alle funzioni di %S. Livelli di accesso differenti permettono
	di avere molta flessibilita' per gli accessi. 
	/msg %S HELP ACCESS LEVELS per piu' informazioni. Ogni
	nick non nella lista di accesso ha un livello di accesso 0.
	
	ACCESS ADD aggiunge il nickname dato alla lista di 
	accessi con il livello specificato. Se il nick e' gia' 
	presente nella lista il suo livello everra' cambiato a
	quello dato.Il livello deve essere minore di quello 
	dell'utente che lo usa.

	ACCESS DEL rimuove qualcuno dalla lista di accesso.
	
	ACCESS LIST visualizza la lista di accessi corrente.
	Se e' data una maschera verranno mostrati gli user 
	corrispondenti. E' possibile specificare anche dei numeri
	che corrisponderanno ai membri con quel numero. Ad esempio

	   ACCESS #canale LIST 2-5,7-9
		Mostra i membri dal numero 2 al 5 e dal 7 al 9.	      

CHAN_HELP_ACCESS_LEVELS
	Livelli di accesso per gli user
	
	Di default sono definiti i seguenti livelli:
	
	   Founder   Fondatore: Completo controllo delle
			 funzioni di %S e op automatico nel canale
			 (non puo' essere conferito con il comando ACCESS command).
	        10   Accesso alla lista AutoKICK. Auto op.
	         5   Auto op.
	         3   Auto voice.
	         0   Nessun privilegio speciale, puo' essere oppato
			 dagli altri user. (se secure-ops e' disabilitata).
	        <0   Non puo' essere oppata.
	
	Questi livelli possono essere cambiati e possono esserne
	aggiunti altri usando il comando LEVELS; scrivi /msg %S
	HELP LEVELS per informazioni.

CHAN_HELP_AKICK
	Sintassi: AKICK canale ADD maschera [ragione]
		  AKICK canale DEL mashera
		  AKICK canale LIST [maschera]
		  ^BAKICK ^_canale^_ ENFORCE^B
	
	Mantiene la AutoKick list per un canale. Se qualcuno
	nella AKICK list joina il canale, %S lo kickbannera'.
	
	AKICK ADD aggiunge il nick dato o la maschera alla
	AutoKick list. Se viene specificata una ragione questa
	verra' specificata quando si kikkera' l'user.
	
	AKICK DEL rimuove il nick o la maschera data dalla
	AutoKick list.
	
	AKICK LIST visualizza la AKICK list del canale.

	^BAKICK ENFORCE^B fara' in modo che ChanServ rimuova dal canale
	chiunque sia nell AKICK list.

CHAN_HELP_LEVELS
	Sintassi: LEVELS canale SET tipo livello
		  LEVELS canale {DIS | DISABLE} tipo
		  LEVELS canale LIST
		  LEVELS canale RESET
	
	Il comando LEVELS ti permette di controllare in un modo
	migliore i livelli di accesso per un canale. Con questo
	comando puoi definire un accesso per la maggior parte dei
	comandi di %S.  (Esclusi SET FOUNDER e SET PASSWORD
	riservati al fondatore.)
	
	LEVELS SET ti permette di cambiare un livello di accesso.
	LEVELS DISABLE disabilita una funzione automatica o
	impedisce l'accesso a qualche funzione a tutti tranne che 
	al fondatore.
	LEVELS LIST visualizza i livelli correntemente
	disponibili.
	LEVELS RESET riporta i livelli a quelli di default
	(guarda anche HELP ACCESS LEVELS).
	
	Per una lista di funzioni di tutti i livelli usa HELP LEVELS DESC.

CHAN_HELP_LEVELS_DESC
	Le funzioni seguenti sono quelle usate:
	Nota che i livelli per AUTODEOP e NOJOIN sono i piu' grandi,
	mentre gli altri sono piu' piccoli.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Sintassi: INFO canale [ALL]
	
	Visualizza delle informazioni come URL email Fondatore, data
	di fondazione eccetera. Se richiedi anche l'opzione ALL e sei
	identificato come il fondatore del canale ti verra' mostrato
	anche il successore e il messaggio di benvenuto.

CHAN_HELP_LIST
	Sintassi: LIST pattern
	
	Visualizza i canali corrispondenti al campione dato.	
	(I canali con l'opzione PRIVATE non sono listati.)

CHAN_HELP_OP
	Sintassi: OP #canale nick
	
	Oppa un nick nel canale. Normalmente limitato agli
	user con almeno 5 come livello di accesso.	

CHAN_HELP_DEOP
	Sintassi: DEOP #canale nick
	
	Deoppa un nick nel canale. Normalmente limitato agli
	user con almeno 5 come livello di accesso.Deops a

#CHAN_HELP_INVITE
#	Sintassi: INVITE canale
#	
#	Dice a %S di invitarti nel canale. Funziona solo se il tuo
#	livello di accesso per quel canale e' superiore a 0.

#CHAN_HELP_UNBAN
#	Sintassi: UNBAN canale
#	
#	Dice a %S di rimuovere tutti i ban che ti impediscono di
#	entrare nel canale.Funziona solo se il tuo livello di accesso
#	e' superiore a 0.

#CHAN_HELP_CLEAR
#	Sintassi: CLEAR canale cosa
#	
#	Dice a %S di cancellare certi settaggi del canale. cosa
#	puo' essere uno dei seguenti.
#	
#	     MODES    Resetta i mode del canale.
#	     BANS     Pulisce tutti i ban del canale.
#	     OPS      Deoppa tutti.
#	     VOICES   Toglie il +v a chiunque lo abbia.
#	     USERS    Removes (kicks) all users from the channel.
#	
#	Funziona solo con un livello di accesso superiore a 10.	

#CHAN_SERVADMIN_HELP
#	
#	I comandi seguenti sono disponibili sono agli amministratori
#	dei servizi:
#	
#	    GETPASS    Da la pass del fondatore
#			   (solo con la cryptazione disabilitata)
#	    FORBID     Impedisce a un canale di venire usato
#	    STATUS     Visualizza il livello di accesso per un user su un
#		       canale
#			
#	
#	Gli amministrator i possono anche deregistrare qualunque
#	canale, vedere la access-list e la AKICK list senza
#	bisogno di sapere la password.

CHAN_SERVADMIN_HELP_DROP
	Sintassi: DROP canale
	
	Deregistra un canale. Disponibile solo agli amministratori
	dei servizi.

CHAN_SERVADMIN_HELP_SET
	
	Gli amministratori dei servizi possono anche settare
	l'opzione NOEXPIRE, con la quale si previene 
	la scadenza di un canale. In piu' gli amministratori
	possono settare qualunque opzione senza bisogno della
	password.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Sintassi: SET canale NOEXPIRE {ON | OFF}
	
	Setta se il canale dato puo' scadere (OFF) o no (ON)	
	
	Limitato agli amministratori dei servizi.

CHAN_SERVADMIN_HELP_LIST
	Sintassi: LIST pattern
	
	Lista di tutti i canali registrati. I canali con 
	l'opzione  PRIVATE saranno mostrati solo agli
	amministratori dei servizi.

CHAN_SERVADMIN_HELP_GETPASS
	Sintassi: GETPASS canale
	
	Da la password del fondatore per il canale specificato.
	Nota che quando questo comando e' usato un GLOBOP
	viene spedito a tutti gli IRCops.
	
	Limitato agli amministratori dei servizi.

CHAN_SERVADMIN_HELP_FORBID
	Sintassi: FORBID canale
	
	Impedisce a chiunque di usare uno specifico canale.
	Puo' essere cancellato usando il comando DROP:	
	
	Limitato agli amministratori dei servizi.

CHAN_SERVADMIN_HELP_STATUS
	Sintassi: STATUS canale nick
	
	Visualizza il livello di accesso per chiunque su
	un qualsiasi canale.	
	Il reply sara' nella forma:
	
	    STATUS canale nick livello-di-accesso
	
	Se accade qualche errore il reply sara' cosi':	
	
	    STATUS ERROR messaggio-di-errore
	
	Limitato agli amministratori dei servizi.

###########################################################################
#
# MemoServ help messages
#
###########################################################################

#MEMO_HELP
#	%S e' un utility che ti permette di spedire brevi
#	messaggi ad altri utenti o a interi canali(*).
#	Sia il mittente che il destinatario devono essere 
#	registrati
#	
#	I comandi di %S sono:
#	
#	    SEND   Spedisce un memo a un nick o a un canale
#	    LIST   Visualizza i tuoi memo
#	    READ   Legge uno o piu' memo
#	    DEL    Cancella un memo o piu' memo
#	    SET    Setta le opzioni relative ai memo
#	
#	Scrivi /msg %S HELP comando per piu' informazioni
#	su uno dei comando sopraccitati.
#	
#	(*) Di default solo gli user con un livello di accesso
#	di 10 possono leggere i messaggi.

MEMO_HELP_SEND
	Sintassi: SEND {nick | canale} testo
	
	Spedisce al nick o al canale un memo contenente
	testo.  Il destinatario sara' avvertito con un notice.
	Il destinatario deve essere un nick o un canale registrato.

MEMO_HELP_LIST
	Sintassi: LIST [canale] [list | NEW]
	
	Visualizza tutti i memo che hai. Con l'opzione NEW
	visualizza solo i memo non letti, marcati con un "*".
	Puoi anche specificare una lista di numeri, come nell esempio:

	   LIST 2-5,7-9
		Visualizza i memo da 2 a 5 e da 7 a 9
MEMO_HELP_READ
	Sintassi: READ [canale] {num | list | LAST | NEW}
	
	Riceve il testo del memo selezionato. Se LAST e' dato
	ti fa ricevere il tuo ultimo memo. Se NEW e' dato ti manda
	tutti i memo non letti. Oppure ti manda il memo numero num.  
	Puoi anche dare una lista di numeri, come queto esempio:	

	   READ 2-5,7-9
		Ti fa vedere i memo dal 2 al 5 e dal 7 al 9

MEMO_HELP_DEL
	Sintassi: DEL [canale] {num | list | ALL}
	
	Cancella il specifico memo. Puoi dare una lista di numeri
	al posto di un numero solo, come nel secondo esempio qua
	sotto.	
	Se ALL e' dato, cancella tutti i tuoi memo.
	
	Esempi:
	
	   DEL 1
	      Cancella la tua prima memo.
	
	   DEL 2-5,7-9
	      Cancella i memo dal 2 al 5 e dal 7 al 9.

MEMO_HELP_SET
	Sintassi: SET opzione parametri
	
	Setta le opzioni per le tue memo. option puo' essere:
	
	    NOTIFY      Ti dice quando ricevi un nuovo memo.
				(solo per i nick)
	    LIMIT       Setta il massimo numero di memo che puoi
			ricevere.
	
	Scrivi /msg %S HELP SET opzione per piu' 
	informazioni su una singola opzione.

MEMO_HELP_SET_NOTIFY
	Sintassi: SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Ti avverte quando ricevi nuovi memo. Puo' essere:
	
	    ON      Sarai avvisato quando effettui il logon nella rete,
		    quando esci dall' /AWAY e quando i memo ti
		    saranno spediti.
	    LOGON   Sarai avvisato quando effettui logon nella rete e
		    quando esci dall' /AWAY.
	    NEW     Sarai avvisato solo quando ricevi nuove memo.
	    OFF     Non sarai avvisato se ricevi nuove memo.
	
	ON e' essenzialmente LOGON e NEW combinate.

MEMO_HELP_SET_LIMIT
	Sintassi: SET LIMIT [canale] limite
	
	Setta il massimo numero di memo che puoi ricevere.	
	Il massimo di memo ricevibili e' %d.

MEMO_HELP_INFO
	Sintassi: INFO [canale]
	
	Visualizza informazioni sul numero di memo in giacenza,
	quanti sono stati letti ,quanti sono nuovi e quanti memo
	puoi ancora ricevere.
	
MEMO_SERVADMIN_HELP_SET_LIMIT
	Sintassi: SET LIMIT [user | canale] {limit | NONE} [HARD]
	
	Setta il massimo numero di memo che un canale o un user
	sono abilitati a ricevere. Settare il limite a 0 vuol dire
	non ricevere memo e settarlo a NONE ti permette di
	riceveerne quante ne vuoi.
	
	Aggiungere HARD impedisce agli user di cambiarsi il 
	limite delle memo.
	
	HARD e' limitato agli amministratori dei servizi.
	Gli altri user possono limitare solo il proprio limite
	o quello del proprio canale, che in ogni caso non deve
	superare %d.

MEMO_SERVADMIN_HELP_INFO
	Sintassi: INFO [nick | canale]
	
	Senza parametri ti da informazioni sul nuemro di memo
	in giacenza, quante sono lette quante sono nuove e qual'e'
	il tuo limite di memo ricevibili.	
	
	Con un canale come parametro visualizza le stesse informazioni
	per un canale.
	
	Con un nick come parametro visualizza le stesse informazioni
	per uno specifico nick.

	Limitato agli amministratori dei servizi.
###########################################################################
#
# OperServ help messages
#
###########################################################################

#OPER_HELP
#	Comandi di %S:
#	    GLOBAL      Spedisce un messaggio a chiunque
#	    STATS       Visualizza lo status dei servizi e del network
#	    OPER LIST   Lista degli operatori dei servizi
#	    ADMIN LIST  Lista degli amministratori dei servizi
#	
#	Comandi disponibili agli operatori e amministratori:
#	    MODE        Cambia i mode di un canale
#	    KICK        Kikka un user dal canale
#	    AKILL       Manipolazione della AKILL list
#	
#	Comandi disponibili solo agli amministratori:
#	    SESSION     Guarda la lista di sessioni di un host
#	    EXCEPTION   Modifica la lista di eccezioni alla
#			session-limit list
#	    KILLCLONES  Killa tutti gli user con una certa maschera
#	    OPER        Modifica della lista di operatori
#	    LOGONNEWS   Definisce un messaggio di benvenuto
#	    OPERNEWS    Definisce un messaggio per gli IRCops
#	    JUPE        Crea un finto server un server
#	    RAW         Manda una stringa raw al server
#	    SET         Setta delle opzioni
#	    UPDATE      Forza l'updating del database
#	    QUIT       	Termina i servizi
#	    RESTART     Salva il database e riparte
#	
#	Comandi disponibili ai root dei servizi:
#	    ADMIN       Modifica la lista di amministratori
#	
#	Notice: Tutti i comandi mandati a %S sono loggati!

OPER_HELP_GLOBAL
	Sintassi: GLOBAL messaggio
	
	Permette agli IRCops di mandare un messaggio a tutti gli
	user del network.
	Questo messaggi viene mandato dal nick %s.

OPER_HELP_STATS
	Sintassi: STATS [AKILL | ALL]
	
	Senza opzioni visualizza il numero corrente di utenti
	e di IRCops online (servizi esclusi), il picco di utenti
	e l'uptime dei servizi.	
	
	Con l'opzione AKILL mostra la dimensione della AKILL
	list e il default expiry time.
	
	L'opzione ALL e' disponibile solo agli amministratori,
	e permette di vedere l'occupazione di memoria dei servizi.
	Nei network grandi questa opzione puo' bloccare per un po'
	i servizi, quindi non usarla spesso.
	
	UPTIME e' un sinonimo di  STATS.

OPER_HELP_OPER
	Sintassi: OPER ADD nick
		  OPER DEL nick
		  OPER LIST
	
	Permette agli amministratori dei servizi di aggiungere
	o rimuovere un operatore dei servizi. Un utente che e'
	nella SOP e si e' identificato con %s puo' usare i 
	comandi di SOP.	
	
	Qualunque IRCop puo' usare OPER LIST.
	Tutti gli altri usi sono limitati agli amministratori.

OPER_HELP_ADMIN
	Sintassi: ADMIN ADD nick
		  ADMIN DEL nick
		  ADMIN LIST
	
	Permette ai root di aggiungere o rimuovere nick dalla
	service admin list. Un utente che si e' identificato con %s
	ed e' presente nella AOP puo' usare i comandi da
	amministratore.
	
	Qualunque IRCop puo' usare il comando ADMIN LIST.
	Tutti gli altri usi sono limitati ai root.

OPER_HELP_MODE
	Sintassi: MODE canale mode
	
	Permette ai SOP di settare dei mode per un canale.
	Funziona come il comando /MODE di qualsiasi client IRC.
	
	Limitato ai SOP.

OPER_HELP_CLEARMODES
	Sintassi: CLEARMODES canale [ALL]
	
	Cancella i mode (i,k,l,m,n,p,s,t) e i ban da un canale.
	Se ALL e' dato deoppa e togli il +v a tutti.
	
	Limitato ai SOP.

OPER_HELP_KICK
	Sintassi: KICK canale user ragione
	
	Permette agli IRCop di kikkare un user da un canale.
	Funziona come il comando /KICK della maggior parte di
	client IRC.	
	Il messaggio di kick avra' all interno  il nick dell'
	IRCop richiedente, ad esempio:
		
	*** Stato_Italiano has been kicked off channel #padania by %S (Duro (non esisti piu'))
	
	Limitato ai SOP.

OPER_HELP_AKILL
	Sintassi: AKILL ADD [+expiry] maschera ragione
		  AKILL DEL maschera
		  AKILL LIST [maschera]
		  AKILL VIEW [maschera]
	
	Permette ai SOP di manipolare la AKILL list. Se un user
	corrispondente a una AKILL tentera' il logon verra' killato
	e, sui server adatti, verra' aggiunta una Kline per la
	maschera dell utente.
	
	AKILL ADD aggiunge la maschera user@host alla AKILL
	list con la ragione data (che deve essere data).
	AKILL DEL rimuove una machera dalla AKILL list
	AKILL LIST visualizza la AKILL list corrente, se la
	maschera opzionale viene data la lista viene limitata
	agli user corrispondenti.
	AKILL VIEW e' un altra versione diAKILL LIST, e
	mostrera' chi ha fatto un AKILL, quando, e quando scadra'.
	
	Opzionalmente un expiry time puo' essere dato con l'opzione
	AKILL ADD. L' expiry time precede la maschera user@host, 
	e deve essere un numero intero seguito da una d (giorni),
	h (ore), o m (minuti). Le combinazioni (come 1h30m)
	non sono permesse. Se non e' specificata una unita' di default
	si useranno i giorni (quindi +30 significa 30 giorni). Per
	Aggiungere una AKILL che non deve scadere usa +0. Se la
	maschera da aggiungere inizia con un +, un expiry time deve
	essere dato.
	L' expiry time corrente puo' essere trovato con il comando
	STATS AKILL.
	
	La ragione e' intesa come uso per soli IRCop e non sara'
	visualizzata nel messaggio di KILL.
	
	Limitato ai SOP.

#OPER_HELP_SET
#	Sintassi: SET opzione settaggio
#	
#	Setta delle opzioni per i servizi. Le opzioni correnti sono:	
#
#	    READONLY   Setta la modalita' READONLY o READWRITE
#	    DEBUG      Attiva o disattiva la modalita' di DEBUG
#	
#	Limitato agli AOP.

OPER_HELP_SET_READONLY
	Sintassi: SET READONLY {ON | OFF}
	
	Setta la modalita' read-only off e on. Nella modalita'
	read-only gli uteniti non possono modificare nessun dato
	dei servizi, incluso registrare nuovi nick ecc..
	Gli IRCop con abbastanza privilegi potranno modificare la
	AKILL list e deregeistrare o vietare nickname e canali, ma 
	nessuna modifica sara' salvata.
	
	Questa opzione e' equivalente alla opzione da linea di 
	comando -readonly.

OPER_HELP_SET_DEBUG
	Sintassi: SET DEBUG {ON | OFF | num}
	
	Setta la modalita' di debug on o off. Con il DEBUG attivato
	*ogni* messaggio sara' trascritto nei logs.	
	Se num e' dato il debug si attivera' con il livello
	specificato.
	
	Questa opzione e' equivalente alla opzione da line di
	comando	-debug.

OPER_HELP_JUPE
	Sintassi: JUPE server [ragione]
	
	Dice ai servizi di jupiterare un server, ovvero di creare
	un fake-server e linkarlo, impedendo al vero server di 
	linkarsi a sua volta. Il jupe puo' essere rimosso usando 
	il comando SQUIT. Se viene data una ragione e' messa
	nella descrizione del server, al posto dello standard
	"Jupitered by <nick>".
	
	Limitato agli AOP.

OPER_HELP_RAW
	Sintassi: RAW testo
	
	Manda una stringa raw al server al quale i servizi sono
	connessi.	
	Questo comando e' molto limitato ma puo' creare situazioni
	pericolose se usato malamente. NON USARLO se non sei
	veramente certo delle conseguenze che avra'.
	
	Limitato agli AOP.

OPER_HELP_UPDATE
	Sintassi: UPDATE
	
	Fa in modo che i servizi scrivano immediatamente il loro
	database sul server.
	
	Limitato agli AOP.

OPER_HELP_QUIT
	Sintassi: QUIT
	
	Fa in modo che i servizi terminino immediatamente.
	Il databse non viene salvato. Questo comando dovrebbe
	essere usato solo in caso ci siano problemi a scrivere
	i dati sul disco fisso. Per un normale shutdown usare
	SHUTDOWN.
	
	Limitato agli AOP.

OPER_HELP_SHUTDOWN
	Syntax: SHUTDOWN
	
	Fa in modo che i servizi terminino salvando il database.
	
	Limitato agli AOP.

OPER_HELP_RESTART
	Sintassi: RESTART
	
	Fa in modo che i servizi termino salvando il database
	e quindi ripartano immediatamente.	
	
	limitato agli AOP.

# New strings

BAD_EXPIRY_TIME
	Scadenza non corretta.

FORCENICKCHANGE_IN_1_MINUTE
	Se non cambi o ti identifichi in un minuto ti cambiero' il nick.
FORCENICKCHANGE_IN_20_SECONDS
	Se non cambi o ti identifichi in 20 secondi ti cambiero' il nick.
FORCENICKCHANGE_NOW
	Questo nick e' stato registrato, quindi non puoi usarlo.
	Il tuo nick verra' cambiato a ^B%s^B
NICK_INFO_ADDRESS_ONLINE
	E' online da: %s
NICK_INFO_ADDRESS_ONLINE_NOHOST
	%s e' online.
CHAN_AKICK_ENFORCE_DONE
	AKICK ENFORCE per ^B%s^B completato; ^B%d^B utenti compromessi.
CHAN_INFO_SUCCESSOR
	      Successore: %s (%s)
CHAN_INFO_NO_SUCCESSOR
	      Successore: %s
CHAN_INFO_ENTRYMSG
	  Messaggio di benvenuto: %s
CHAN_INFO_NO_EXPIRE
	Questo canale non ha scadenza.
OPER_STATS_BYTES_READ
	Bytes letti   : %5d kB
OPER_STATS_BYTES_WRITTEN
	Bytes scritti : %5d kB
OPER_STATS_SESSIONS_MEM
	Sessioni: ^B%6d^B record, ^B%5d^B kB
OPER_KILLCLONES_SYNTAX
	KILLCLONES ^_nick^_
OPER_KILLCLONES_UNKNOWN_NICK
	Impossibile trovare l'utente ^B%s^B.
OPER_EXCEPTION_SYNTAX
	EXCEPTION {ADD | DEL | MOVE | LIST | VIEW} [^_parametri^_]
OPER_EXCEPTION_ADD_SYNTAX
	EXCEPTION ADD [+^_scadenza^_] ^_maschera^_ ^_limite^_ ^_ragione^_
OPER_EXCEPTION_DEL_SYNTAX
	EXCEPTION DEL {^_maschera^_ | ^_lista^_}
OPER_EXCEPTION_MOVE_SYNTAX
	EXCEPTION MOVE ^_num^_ ^_posizione^_
OPER_EXCEPTION_DISABLED
	Limitazione delle sessioni disabilitata.
OPER_EXCEPTION_ALREADY_PRESENT
	La maschera ^B%s^B e' gia' presente nella lista di eccezioni.
OPER_EXCEPTION_TOO_MANY
	Lista di eccezioni sulla limitazione di sessione piena!
OPER_EXCEPTION_ADDED
	Limitazione di sessione per ^B%s^B settata a ^B%d^B.
OPER_EXCEPTION_MOVED
	Eccezione per ^B%s^B (#%d) mossa alla posizione ^B%d^B.
OPER_EXCEPTION_NO_SUCH_ENTRY
	Entry non trovata (#%d).
OPER_EXCEPTION_NOT_FOUND
	^B%s^B non trovata nella lista di eccezioni.
OPER_EXCEPTION_NO_MATCH
	Nessun match nella lista di eccezioni.
OPER_EXCEPTION_DELETED
	^B%s^B canellato dalla lista di eccezioni.
OPER_EXCEPTION_DELETED_ONE
	1 registrazione cancellata dalla lista di eccezioni.
OPER_EXCEPTION_DELETED_SEVERAL
	%d registrazioni cancellate dalla lista di eccezioni.
OPER_EXCEPTION_LIST_HEADER
	Lista di eccezioni ai limiti di sessioni corrente:
# mask, limit
OPER_EXCEPTION_LIST_FORMAT
	%3d  %4d   %s
OPER_EXCEPTION_LIST_COLHEAD
	Num  Limite  Host
# mask, set-by, set-time, expires, limit, reason
OPER_EXCEPTION_VIEW_FORMAT
	%3d.  %s  (by %s on %s; %s)
	    Limite: %-4d  - %s
OPER_EXCEPTION_INVALID_LIMIT
	Limite non valido. Deve essere un intero maggiore o uguale a zero
	e minore di ^B%d^B.
OPER_EXCEPTION_INVALID_HOSTMASK
	Maschera non valida. Solo maschere reali sono valide perche' le
	eccezioni non sono contate sui nick o usernames.
OPER_SESSION_SYNTAX
	SESSION {LIST ^_limite^_ | VIEW ^_host^_}
OPER_SESSION_LIST_SYNTAX
	SESSION LIST ^_limite^_
OPER_SESSION_VIEW_SYNTAX
	SESSION VIEW ^_host^_
OPER_SESSION_DISABLED
	Limitazione di sessioni non disabilitata.
OPER_SESSION_INVALID_THRESHOLD
	Soglia non valida, deve essere un intero maggiore di 1.
OPER_SESSION_NOT_FOUND
	^B%s^B non trovato nella lista di sessioni.
OPER_SESSION_LIST_HEADER
	Hosts con almeno ^B%d^B sessioni:
OPER_SESSION_LIST_COLHEAD
	Sessioni  Host
# limit, host
OPER_SESSION_LIST_FORMAT
	%6d    %s
# host, sessions, limit
OPER_SESSION_VIEW_FORMAT
	L' host ^B%s^B ha ^B%d^B sessioni con un limite di ^B%d^B.
OPER_HELP_EXCEPTION
	Sintassi: ^BEXCEPTION ADD [^_+scadenza^_] ^_maschera^_ ^_limite^_ ^_ragione^_^B
		^BEXCEPTION DEL {^_maschera^_ | ^_list^_}^B
		^BEXCEPTION MOVE ^_num^_ ^_posizione^_^B
		^BEXCEPTION LIST [^_maschera^_ | ^_list^_]^B
		^BEXCEPTION VIEW [^_maschera^_ | ^_list^_]^B

	Fa in modo che i Services Admin possano manipolare la lista degli
	host che hanno specifiche limitazioni sul numero di sessioni, e
	fa in modo che certe macchine, come dei shell servers, possano
	avere piu' sessioni nello stesso momento di un utente normale.
	Dopo che un host raggiunge il limite tutti i clients che 
	provassero a connettersi da quell host verrebbero automaticamente
	killati.
	Prima del kill sono avvisato, tramite un /NOTICE di OperServ, che
	hanno raggiunto il limite. Il contenuto di questo notice dipende
	dalla configurazione dei servizi.

	^BEXCEPTION ADD^B aggiunge l'host dato alla lista di eccezioni. Da
	notare che maschere del tipo ^Bnick!user@host^B e ^Buser@host^B 
	non sono valide!
	Solo hostname reali, come ^Bbox.host.dom^B e ^B*.host.dom^B,
	sono autorizzati, dato che la limitazione non lavora tenendo
	conto dei nick o degli usernames. ^_limite^_ Deve essere un numero
	maggiore o uguale a zero. Questo determina quante sessioni 
	provenienti da quell host sono autorizzate. Il valore 0 significa
	che quell host non ha limiti. Guarda l'help di^BAKILL^B per 
	dettagli sul formato della ^_scadenza^_ .
	^BEXCEPTION DEL^B rimuove qualcuno dalla lista di eccezioni.
	^BEXCEPTION MOVE^B muove l'eccezione numero ^_num^_ alla 
	^_posizione^_. Le eccezioni tra queste due saranno automaticamante
	cambiate per riempire lo spazio.
	^BEXCEPTION LIST^B e ^BEXCEPTION VIEW^B mostrano tutte le 
	eccezioni correnti; se la maschera opzionale viene data la lista
	verra' limitata solo agli host che combaciano.
	La differenza e' che  ^BEXCEPTION VIEW^B e' piu' preciso,dato che
	mostra chi ha messo quella eccezione, qual'e' il limite, 
	la ragione, l'hostmask e la scadenza.

	Da notare cheun client "usera'" la prima eccezione che combaciera'
	con il suo client. Grandi liste poco precise degraderanno le
	performance dei servizi.

	Limitato ai ^BServices admins^B.

OPER_HELP_SESSION
	Syntax: ^BSESSION LIST ^_numero^_^B
		^BSESSION VIEW ^_host^_^B

	Fa in modo che i Services admins vedano la session list.

	^BSESSION LIST^B mostra gli hosts con almeno ^_numero^_
	sessioni.
	Il numero deve essere maggiore di 1. Questo per prevenire
	acciedentali liste di un grande numero di persone.
	^BSESSION VIEW^B mostra specifiche informazioni su un host
	specifico, includendo il numero di sessioni corrente e il
	limite. Il parametro ^_host^_ non deve includere delle
	wildcards (* oppure ?).

	Guarda l'help di ^BEXCEPTION^B per informazioni piu'
	dettagliate sulla limitazione di sessioni e su come
	settare delle specifiche limitazioni.

	Limitato ai ^BServices admins^B.

NICK_SERVADMIN_HELP_INFO

	I Services admins possono usare il parametro ^BALL^B con
	qualsiasi nick.

CHAN_SERVADMIN_HELP_INFO

	I Services admins possono usare il parametro  ^BALL^B con
	qualsiasi canale.

OPER_HELP_KILLCLONES
	Sintassi: ^BKILLCLONES ^_nick^_^B

	Killa tutti gli utenti con lo stesso hostname di ^_nick^_.
	Una AKILL temporanea, nel formato ^B*@host^B, e' aggiunta
	per prevenire i cloni di riconnettersi immediatamente.
	Viene anche mandato un wallop indicante chi ha usato il
	comando, quele host e' stato colpito e quanti utenti sono
	stati killati. 
	E' utile per rimuovere numerosi utenti da network.

	Limitato ai ^BServices admins^B.

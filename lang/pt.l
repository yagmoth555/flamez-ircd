# Emacs mode: -*- text -*-$B!!(B

# Arquivo do idioma Portugues (do Brasil).
#
# Services eh protegido por direitos autorais (c) 1996-2001 Andrew Church.
#     E-mail: <achurch@achurch.org>
# Este programa eh gratis porem registrado; veja o arquivo COPYING
# para detalhes.

# Quando traduzindo este programa para outra idioma, lembre-se que a
# ordem dos parametros para sprintf() eh fixado no codigo de fonte, entao
# suas mensagens precisam ter os mesmos parametros nos mesmos padroes das
# mensagens em ingles.  (Obviamente, isto nao eh valido para linhas no formato
# strftime() que ficam uma abaixo das outras).  Se voce nao pode adquirir uma
# traducao das mensagens naturalmente sem mudar as ordens dos parametros, me
# avise (achurch@dragonfire.net) qual mensagem esta causando o problema e eu
# verei o que posso fazer.
#
# Nas mensagens de ajuda, "%S" (S maiusculo, nao minusculo) se refere ao nome
# do servico que envia a mensagem; por exemplo, na mensagem de ajuda do
# Nickserv, "%S" eh substituido por "NickServ" (ou outro nome definido
# no config.h).  Os %S's nao contam como sendo parametros de sprintf(),
# assim podem ser reorganizados, removidos, ou adicionados se necessario.
#
# Finalmente, lembre-se de colocar TAB no comeco de toda linha do texto
# (incluindo linhas vazias). Tem que ser TAB, nao espacos.

###########################################################################
#
# Nome deste idioma
#
###########################################################################

# Para idiomas diferentes do ingles, essa string deve ter o seguinte formato:
#     language-name-in-language (language-name-in-English)
# Por exemplo, "Español (Spanish)" or "Français (French)".

LANG_NAME
	Portugues (Portuguese)

###########################################################################
#
# Mensagens Gerais
#
###########################################################################

# Strings no formato strftime(). "man 3 strftime" para informacoes sobre o
# significado da especificacao do formato.  Versao pequena:
#	%a = nome do dia da semana (pequeno)	%H = hora
#	%b = nome do mes (pequeno)		%M = minuto
#	%d = dia do mes				%S = segundo
#	%Y = ano				%Z = zona de fuso horario

# O seguinte eh usado para o formato de uma string da strftime(), com uma
# data e horario mostrados juntamente.
STRFTIME_DATE_TIME_FORMAT
	%d %b %H:%M:%S %Y %Z
# O seguinte eh usado para o formato de uma string da strftime(), com uma
# data sozinha de formato longo (Para o ingles inclui-se o dia da semana).
STRFTIME_LONG_DATE_FORMAT
	%a %d %b %Y
# O seguinte eh usado para o formato de uma string da strftime(), com apenas
# a data em formato curto (Para o ingles: sem o dia da semana).
STRFTIME_SHORT_DATE_FORMAT
	%d %b %Y

# Estes especificam para a strftime() quais sao os nomes dos dias e meses.
# Se voce nao usar %a, %A, %b, or %B nas suas strings da strftime(), pode
# deixar essas partes vazias.  No entanto, se voce colocar nomes, eles DEVEM ficar
# ordenados, um por linha, e a lista DEVE estar completa!

# %a
STRFTIME_DAYS_SHORT
	Dom
	Seg
	Ter
	Qua
	Qui
	Sex
	Sab
# %A
STRFTIME_DAYS_LONG
	Domingo
	Segunda
	Terca
	Quarta
	Quinta
	Sexta
	Sabado
# %b
STRFTIME_MONTHS_SHORT
	Jan
	Fev
	Mar
	Abr
	Mai
	Jun
	Jul
	Ago
	Set
	Out
	Nov
	Dez
# %B
STRFTIME_MONTHS_LONG
	Janeiro
	Fevereiro
	Marco
	Abril
	Maio
	Junho
	Julho
	Agosto
	Setembro
	Outubro
	Novembro
	Dezembro


# "day", "hour", "minute", and "second" in singular and plural.
STR_DAY
	dia
STR_DAYS
	dias
STR_HOUR
	hora
STR_HOURS
	horas
STR_MINUTE
	minuto
STR_MINUTES
	minutos
STR_SECOND
	segundo
STR_SECONDS
	segundos


# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	,


# Various error messages.
USER_RECORD_NOT_FOUND
	Erro interno - impossivel processar o pedido.
UNKNOWN_COMMAND
	Comando %s desconhecido.
UNKNOWN_COMMAND_HELP
	Comando %s desconhecido.  Digite /msg %s HELP para ajuda.
SYNTAX_ERROR
	Sintaxe: %s
MORE_INFO
	Digite /msg %s HELP %s para maiores informacoes.
NO_HELP_AVAILABLE
	Ajuda nao disponivel para %s.

BAD_EMAIL
	Enderecos de e-mail precisam ser no formato username@hostname.  Voce nao pode usar cores, negrito, sublinhado, reverso ou os caracteres: , : ; \ " ( ) < >
BAD_URL
	URLs precisam ser no formato http://hostname[:port]/... (ou ftp://, etc.).
BAD_USERHOST_MASK
	Mascaras devem estar no formato ident@host.
BAD_EXPIRY_TIME
	Tempo de expiracao invalido.

SERVICE_OFFLINE
	%s esta atualmente desligado.
READ_ONLY_MODE
	Atencao: Services esta no modo read-only; mudancas nao serao salvas!
PASSWORD_INCORRECT
	Senha incorreta.

ACCESS_DENIED
	Acesso negado.
PERMISSION_DENIED
	Permissao negada.

MORE_OBSCURE_PASSWORD
	Tente novamente com uma senha mais dificil.  As senhas devem ter no minimo cinco caracteres, nao devem ser algo deduzivel (ex: seu nome ou nick) e nao podem conter espacos ou TAB.
PASSWORD_TRUNCATED
	Notice:  Sua senha foi limitada a %d caracteres.

NICK_NOT_REGISTERED
	Seu nick nao esta registrado.
NICK_NOT_REGISTERED_HELP
	Seu nick nao esta registrado.  Digite /msg %s HELP para mais informacoes sobre como registra-lo.
NICK_X_NOT_REGISTERED
	Nick %s nao esta registrado.
NICK_X_NOT_IN_USE
	Nick %s nao esta em uso no momento.
NICK_X_FORBIDDEN
	Nick %s nao pode ser utilizado ou registrado.
NICK_X_SUSPENDED
	Nick %s esta suspenso e nao pode ser utilizado ou identificado.
NICK_X_SUSPENDED_MEMOS
	Nick %s esta suspenso e nao pode receber memos.
NICK_IDENTIFY_REQUIRED
	Autenticacao de senha eh necessaria para este comando.
	Tente novamente apos digitar /msg %s IDENTIFY senha.
NICK_X_NOT_ON_CHAN_X
	Nick %s nao esta no %s no momento.

CHAN_X_NOT_REGISTERED
	Canal %s nao esta registrado.
CHAN_X_NOT_IN_USE
	Canal %s nao existe.
CHAN_X_FORBIDDEN
	Canal %s nao pode ser utilizado ou registrado.
CHAN_X_SUSPENDED
	Canal %s esta suspenso e nao pode ser utilizado ou identificado.
CHAN_X_SUSPENDED_MEMOS
	Canal %s esta suspenso e nao pode receber memos.
CHAN_IDENTIFY_REQUIRED
	Autenticacao de senha eh necessaria para este comando.
	Tente novamente apos digitar /msg %s IDENTIFY %s senha.

SERV_X_NOT_FOUND
	Servidor %s nao encontrado.

EXPIRES_NONE
	nao expira
EXPIRES_SOON
	expira na proxima atualizacao do banco de dados
EXPIRES_M
	expira em %d minutos
EXPIRES_1M
	expira em %d minuto
EXPIRES_HM
	expira em %d horas, %d minutos
EXPIRES_H1M
	expira em %d horas, %d minuto
EXPIRES_1HM
	expira em %d hora, %d minutos
EXPIRES_1H1M
	expira em %d hora, %d minuto
EXPIRES_D
	expira em %d dias
EXPIRES_1D
	expira in %d dia

###########################################################################
#
# Mensagens do NickServ
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	Este nick pertence a outra pessoa.  Por favor escolha outro.
	(Se o nick pertence a voce, /msg %s IDENTIFY senha.)
NICK_IS_SECURE
	Este nick esta registrado e protegido.  Se o nick pertence
	a voce, digite /msg %s IDENTIFY senha. Caso contrario,
	escolha um nick diferente.
NICK_MAY_NOT_BE_USED
	Este nick nao pode ser utilizado.  Por favor escolha outro.
DISCONNECT_IN_1_MINUTE
	Se voce nao troca-lo em 1 minuto, sera desconectado.
DISCONNECT_IN_20_SECONDS
	Se voce nao troca-lo em 20 segundos, sera desconectado.
DISCONNECT_NOW
	Este nick esta registrado; voce nao pode usa-lo.  Por favor
	escolha um outro nick antes de reconectar.
FORCENICKCHANGE_IN_1_MINUTE
	Se voce nao troca-lo em 1 minuto, seu nick sera automaticamente trocado.
FORCENICKCHANGE_IN_20_SECONDS
	Se voce nao troca-lo em 20 segundos, seu nick sera automaticamente trocado.
FORCENICKCHANGE_NOW
	Este nick jah esta registrado; voce nao pode usa-lo.
	Seu nick foi mudado para %s.

# REGISTER responses
NICK_REGISTER_SYNTAX
	REGISTER senha [email]
NICK_REGISTER_REQ_EMAIL_SYNTAX
	REGISTER senha email
NICK_REGISTRATION_DISABLED
	Desculpe, registro de nicks esta temporariamente desativado.
NICK_REGISTRATION_FAILED
	Desculpe, falha na hora de registrar.
NICK_REG_PLEASE_WAIT
	Aguarde %d segundos antes de usar o comando REGISTER novamente.
NICK_CANNOT_BE_REGISTERED
	Nick %s nao pode ser registrado.
NICK_ALREADY_REGISTERED
	Nick %s ja esta registrado!
NICK_REGISTERED
	Nick %s registrado a partir de sua conta: %s
NICK_PASSWORD_IS
	Sua senha eh %s - lembre-se dela para uso posterior.

# IDENTIFY responses
NICK_IDENTIFY_SYNTAX
	IDENTIFY senha
NICK_IDENTIFY_FAILED
	Desculpe, identificacao sem sucesso.
NICK_IDENTIFY_SUCCEEDED
	Senha aceita - voce esta reconhecido.

# DROP responses
NICK_DROP_SYNTAX
	DROP
NICK_DROP_DISABLED
	Desculpe, cancelamento do registro de nicks esta temporariamente desativado.
NICK_DROPPED
	Seu nick teve o registro cancelado.
NICK_X_DROPPED
	Nick %s teve o registro cancelado.

# SET responses
NICK_SET_SYNTAX
	SET opcao parametros
NICK_SET_SERVADMIN_SYNTAX
	SET [nick] opcao parametros
NICK_SET_DISABLED
	Desculpe, configuracao de opcoes do nick esta temporariamente desativada.
NICK_SET_UNKNOWN_OPTION
	Opcao SET %s desconhecida.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	Opcao SET %s desconhecida, ou nick nao registrado.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	Desculpe, impossivel trocar senha.
NICK_SET_PASSWORD_CHANGED
	Senha alterada.
NICK_SET_PASSWORD_CHANGED_TO
	Senha alterada para %s.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_SYNTAX
	SET LANGUAGE numero
NICK_SET_LANGUAGE_UNKNOWN
	Numero de linguagem %d desconhecido.  Digite /msg %s HELP SET LANGUAGE para uma lista de linguagens.
NICK_SET_LANGUAGE_CHANGED
	Linguagem modificada para Portugues.

# SET URL responses
NICK_SET_URL_CHANGED
	URL de %s trocada para %s.

# SET EMAIL responses
NICK_SET_EMAIL_CHANGED
	E-mail de %s trocado para %s.

# SET KILL responses
NICK_SET_KILL_SYNTAX
	SET KILL {ON | QUICK | OFF}
NICK_SET_KILL_IMMED_SYNTAX
	SET KILL {ON | QUICK | IMMED | OFF}
NICK_SET_KILL_ON
	Protecao de KILL ativada.
NICK_SET_KILL_QUICK
	Protecao de KILL ativada, com uma espera reduzida.
NICK_SET_KILL_IMMED
	Protecao de KILL ativada, sem espera.
NICK_SET_KILL_IMMED_DISABLED
	A opcao IMMED nao esta disponivel nesta rede.
NICK_SET_KILL_OFF
	Protecao de KILL desativada.

# SET SECURE responses
NICK_SET_SECURE_SYNTAX
	SET SECURE {ON | OFF}
NICK_SET_SECURE_ON
	Opcao SECURE ativada.
NICK_SET_SECURE_OFF
	Opcao SECURE desativada.

# SET PRIVATE responses
NICK_SET_PRIVATE_SYNTAX
	SET PRIVATE {ON | OFF}
NICK_SET_PRIVATE_ON
	Opcao PRIVATE ativada.
NICK_SET_PRIVATE_OFF
	Opcao PRIVATE desativada.

# SET HIDE responses
NICK_SET_HIDE_SYNTAX
	SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
NICK_SET_HIDE_EMAIL_ON
	Seu endereco de e-mail esta agora oculto na exibicao no %s INFO.
NICK_SET_HIDE_EMAIL_OFF
	Seu endereco de e-mail esta agora visivel para exibicao no %s INFO.
NICK_SET_HIDE_MASK_ON
	Sua ultima mascara ident@host esta agora oculta para exibicao no %s INFO.
NICK_SET_HIDE_MASK_OFF
	Sua ultima mascara ident@host esta visivel para exibicao no %s INFO.
NICK_SET_HIDE_QUIT_ON
	Sua ultima mensagem de quit esta agora oculta para exibicao no %s INFO.
NICK_SET_HIDE_QUIT_OFF
	Sua ultima mensagem de quit esta agora visivel para exibicao no %s INFO.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_SYNTAX
	SET [nick] NOEXPIRE {ON | OFF}
NICK_SET_NOEXPIRE_ON
	Nick %s nao ira expirar.
NICK_SET_NOEXPIRE_OFF
	Nick %s ira expirar.

# UNSET responses
NICK_UNSET_SYNTAX
	UNSET {URL | EMAIL}
NICK_UNSET_SYNTAX_REQ_EMAIL
	UNSET URL
NICK_UNSET_URL
	URL de %s apagada.
NICK_UNSET_EMAIL
	E-mail de %s apagado.
NICK_UNSET_EMAIL_BAD
	Voce nao pode apagar seu E-mail.
NICK_UNSET_EMAIL_OTHER_BAD
	E-mail do nick nao pode ser apagado.

# ACCESS responses
NICK_ACCESS_SYNTAX
	ACCESS {ADD | DEL | LIST} [mascara]
NICK_ACCESS_ALREADY_PRESENT
	Mascara %s ja existe na sua lista de acesso.
NICK_ACCESS_REACHED_LIMIT
	Desculpe, voce soh pode ter %d entradas de acesso para um nick.
NICK_ACCESS_ADDED
	%s adicionado na sua lista de acesso.
NICK_ACCESS_NOT_FOUND
	%s nao encontrado na sua lista de acesso.
NICK_ACCESS_DELETED
	%s excluido da sua lista de acesso.
NICK_ACCESS_LIST
	Lista de acesso:
NICK_ACCESS_LIST_X
	Lista de acesso para %s:

# LINK responses
NICK_LINK_SYNTAX
	LINK nick senha
NICK_LINK_DISABLED
	O comando LINK nao esta disponivel.
NICK_LINK_FAILED
	Desculpe, ligacao falhou.
NICK_NO_LINK_SAME
	Voce nao pode fazer uma uma ligacao para o seu nick atual!
NICK_LINK_CIRCULAR
	Impossivel ligar o nick %s: ligacao circular detectada.
NICK_LINK_TOO_DEEP
	Voce nao pode criar um link com mais de %d niveis de profundidade.
NICK_LINK_TOO_MANY_CHANNELS
	Impossivel linkar ao nick %s: muitos canais registrados (combinacao maxima: %d).
NICK_LINKED
	Seu nick foi ligado ao nick %s.

# UNLINK responses
NICK_UNLINK_SYNTAX
	UNLINK [nick senha]
NICK_UNLINK_FAILED
	Desculpe, desligamento de nicks falhou.
NICK_NOT_LINKED
	Seu nick nao esta ligado.
NICK_UNLINKED
	Seu nick foi desligado do nick %s.
NICK_X_NOT_LINKED
	Nick %s nao esta ligado.
NICK_X_UNLINKED
	Nick %s foi desligado do nick %s.

# LISTLINKS responses
NICK_LISTLINKS_SYNTAX
	LISTLINKS nick [ALL]
NICK_LISTLINKS_HEADER
	Lista de nicks ligados ao nick %s:
NICK_LISTLINKS_FOOTER
	%d nicks ligados.
NICK_X_IS_LINKED
	    %s
NICK_X_IS_LINKED_VIA_X
	    %-20s (via %s)

# INFO responses
NICK_INFO_SYNTAX
	INFO nick [ALL]
NICK_INFO_REALNAME
	%s eh %s
NICK_INFO_ADDRESS
	         Ultimo endereco: %s
NICK_INFO_ADDRESS_ONLINE
	 Esta online no endereco: %s
NICK_INFO_ADDRESS_ONLINE_NOHOST
	%s esta online.
NICK_INFO_TIME_REGGED
	     Horario do registro: %s
NICK_INFO_LAST_SEEN
	    Ultimo horario visto: %s
NICK_INFO_LAST_QUIT
	Ultima mensagem de saida: %s
NICK_INFO_URL
	                     URL: %s
NICK_INFO_EMAIL
	                  E-mail: %s
NICK_INFO_OPTIONS
	                  Opcoes: %s
NICK_INFO_LINKED_TO
	               Linkado a: %s
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	Protecao de Kill
NICK_INFO_OPT_SECURE
	Seguranca
NICK_INFO_OPT_PRIVATE
	Privado
NICK_INFO_OPT_NONE
	Nenhuma
NICK_INFO_NO_EXPIRE
	O registro deste nick nao ira expirar.
NICK_INFO_SUSPEND_DETAILS
	Suspenso por %s em %s (%s).
NICK_INFO_SUSPEND_REASON
	Razao: %s
NICK_INFO_SHOW_ALL
	Para maiores informacoes, digite: /msg %s INFO %s ALL

# LISTCHANS responses
NICK_LISTCHANS_SYNTAX
	LISTCHANS
NICK_LISTCHANS_SERVADMIN_SYNTAX
	LISTCHANS [nickname]
NICK_LISTCHANS_NONE
	%s não tem nenhum canal registrado.
NICK_LISTCHANS_HEADER
	Canais registrados por %s:
NICK_LISTCHANS_ENTRY
	    %s
NICK_LISTCHANS_END
	Fim da lista (%d canais registrados).

# LIST responses
NICK_LIST_SYNTAX
	LIST padrao
NICK_LIST_SERVADMIN_SYNTAX
	LIST padrao [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
NICK_LIST_HEADER
	Lista das entradas que satisfazem %s:
NICK_LIST_RESULTS
	Fim da listagem - %d/%d entradas mostradas.

# RECOVER responses
NICK_RECOVER_SYNTAX
	RECOVER nick [senha]
NICK_NO_RECOVER_SELF
	Voce nao pode recuperar o seu proprio nick!
NICK_RECOVERED
	Usuario que voce reinvidicou o nick foi derrubado.
	Digite /msg %s RELEASE %s para pegar o nick antes da espera de 1 minuto.

# RELEASE responses
NICK_RELEASE_SYNTAX
	RELEASE nick [senha]
NICK_RELEASE_NOT_HELD
	Nick %s nao esta sendo protegido neste momento.
NICK_RELEASED
	A protecao dos Services no seu nick foi desfeita.

# GHOST responses
NICK_GHOST_SYNTAX
	GHOST nick [senha]
NICK_NO_GHOST_SELF
	Voce nao pode aplicar um ghost em voce mesmo!
NICK_GHOST_KILLED
	Nick onde o ghost foi aplicado esta derrubado.

# GETPASS responses
NICK_GETPASS_SYNTAX
	GETPASS nick
NICK_GETPASS_UNAVAILABLE
	Comando invalido porque encriptacao esta em uso.
NICK_GETPASS_PASSWORD_IS
	Senha para %s eh %s.

# FORBID responses
NICK_FORBID_SYNTAX
	FORBID nick
NICK_FORBID_SUCCEEDED
	Nick %s esta proibido de ser usado.
NICK_FORBID_FAILED
	Nao se pode bloquear o uso do nick %s!

# SUSPEND responses
NICK_SUSPEND_SYNTAX
	SUSPEND [+expiracao] nickname razao
NICK_SUSPEND_SUCCEEDED
	Nick %s, e todos os nicks do mesmo dono, foram suspensos.
NICK_SUSPEND_ALREADY_SUSPENDED
	Nick %s jah esta suspenso.

# UNSUSPEND responses
NICK_UNSUSPEND_SYNTAX
	UNSUSPEND nickname
NICK_UNSUSPEND_SUCCEEDED
	Nick %s foi reestabelecido.
NICK_SUSPEND_NOT_SUSPENDED
	Nick %s nao esta suspenso.

###########################################################################
#
# Mensagens do ChanServ
#
###########################################################################

# Access level descriptions
CHAN_LEVEL_AUTOOP
	Status de operador de canal automatico
CHAN_LEVEL_AUTOVOICE
	Modo +v automatico
CHAN_LEVEL_AUTODEOP
	Nao pode ser operador de canal
CHAN_LEVEL_AUTODEOP_HALFOP
	Status de operator/halfop de canal desabilitado
CHAN_LEVEL_NOJOIN
	Nao pode entrar no canal se este estiver restrito (opcao RESTRICTED)
CHAN_LEVEL_INVITE
	Liberado a usar o comando INVITE
CHAN_LEVEL_AKICK
	Liberado a usar o comando AKICK
CHAN_LEVEL_SET
	Liberado a usar o comando SET (nao sendo FUNDADOR)
CHAN_LEVEL_CLEAR
	Liberado a usar o comando CLEAR
CHAN_LEVEL_UNBAN
	Liberado a usar o comando UNBAN
CHAN_LEVEL_OPDEOP
	Liberado a usar os comandos OP/DEOP
CHAN_LEVEL_ACCESS_LIST
	Liberado a ver a lista de acesso
CHAN_LEVEL_ACCESS_CHANGE
	Liberado a modificar a lista de acesso
CHAN_LEVEL_MEMO
	Liberado a listar/ler as mensagens do canal
CHAN_LEVEL_VOICE
	Permitido usar comandos VOICE/DEVOICE
CHAN_LEVEL_AUTOHALFOP
	Status halfop (+h) automatico
CHAN_LEVEL_HALFOP
	Permitido usar comandos HALFOP/DEHALFOP
CHAN_LEVEL_AUTOPROTECT
	Status de protecao de canal (+a) automatico
CHAN_LEVEL_PROTECT
	Permitido usar os comandos PROTECT/DEPROTECT

# Automatic responses
CHAN_IS_REGISTERED
	Este canal esta registrado com %s.
CHAN_NOT_ALLOWED_OP
	Voce nao esta com permissao de ser operador do canal %s.
CHAN_MAY_NOT_BE_USED
	Este canal nao pode ser usado.
CHAN_NOT_ALLOWED_TO_JOIN
	Voce nao esta com permissao para permanecer neste canal.

# Multi-purpose responses
CHAN_BOUNCY_MODES
	Desculpe, o comando %s temporariamente indisponivel.

# REGISTER responses
CHAN_REGISTER_SYNTAX
	REGISTER canal senha descricao
CHAN_REGISTER_DISABLED
	Desculpe, registro de canal esta temporariamente desativado.
CHAN_REGISTER_NOT_LOCAL
	Canais locais nao podem ser registrados.
CHAN_MUST_REGISTER_NICK
	Voce deve primeiro registrar seu nick.  Digite /msg %s HELP para obter informacao sobre o registro de nicks.
CHAN_MUST_IDENTIFY_NICK
	Por favor, identique-se com %s primeiro usando o comando:
	/msg %s IDENTIFY senha
CHAN_MAY_NOT_BE_REGISTERED
	Canal %s nao pode ser registrado.
CHAN_ALREADY_REGISTERED
	Canal %s ja esta registrado!
CHAN_MUST_BE_CHANOP
	Voce deve ser operador de canal para registrar o canal.
CHAN_REACHED_CHANNEL_LIMIT
	Desculpe, voce ja alcancou seu limite de %d canais.
CHAN_EXCEEDED_CHANNEL_LIMIT
	Desculpe, voce ja ultrapassou seu limite de %d canais.
CHAN_REGISTRATION_FAILED
	Desculpe, registro falhou.
CHAN_REGISTERED
	Canal %s registrado com o seu nick: %s
CHAN_PASSWORD_IS
	A senha do seu canal eh %s - lembre-se dela para uso posterior.

# IDENTIFY responses
CHAN_IDENTIFY_SYNTAX
	IDENTIFY canal senha
CHAN_IDENTIFY_FAILED
	Desculpe, identificacao falhou.
CHAN_IDENTIFY_SUCCEEDED
	Senha aceita - voce agora esta reconhecido como fundador do %s.

# DROP responses
CHAN_DROP_SYNTAX
	DROP canal
CHAN_DROP_DISABLED
	Desculpe, cancelamento do registro de canal esta temporariamente desabilitado.
CHAN_DROPPED
	Canal %s teve seu registro desfeito.

# SET responses
CHAN_SET_SYNTAX
	SET canal opcao parametros
CHAN_SET_DISABLED
	Desculpe, opcao de ajuste das opcoes do canal esta temporariamente desativada.
CHAN_SET_UNKNOWN_OPTION
	Opcao SET %s desconhecida.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	%s tem canais registrados em excesso.
CHAN_FOUNDER_CHANGED
	Fundador do canal %s alterado para %s.

# SET SUCCESSOR responses
CHAN_SUCCESSOR_CHANGED
	Sucessor de %s mudado para %s.
CHAN_SUCCESSOR_IS_FOUNDER
	Voce nao pode fazer o fundador do canal ser tambem o sucessor.

# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Desculpe, nao foi possivel alterar a senha.
CHAN_PASSWORD_CHANGED
	%s senha trocada.
CHAN_PASSWORD_CHANGED_TO
	Senha do canal %s mudada para %s.

# SET DESC responses
CHAN_DESC_CHANGED
	Descricao do canal %s alterada para %s.

# SET URL responses
CHAN_URL_CHANGED
	URL do canal %s alterada para %s.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	Endereco do e-mail d do canal %s mudado para %s.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	Mensagem de entrada do canal %s alterada.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Desculpe, nao foi possivel por o topico.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	Parametro requerido para MLOCK +k.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	Parametro requerido para MLOCK +l.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	Parametro para MLOCK +l deve ser um numero positivo.
CHAN_SET_MLOCK_MODE_REG_BAD
	Modo +%c sempre eh colocado em canais registrados, e nao pode ser usado com MLOCK.
CHAN_SET_MLOCK_MODE_F_BAD
	Modo +f nao pode ser travado.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Modo %c eh desconhecido e foi ignorado.
CHAN_MLOCK_CHANGED
	Trava dos modos do canal %s alterada para %s.
CHAN_MLOCK_REMOVED
	Trava dos modos do canal %s removida.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_SYNTAX
	SET canal KEEPTOPIC {ON | OFF}
CHAN_SET_KEEPTOPIC_ON
	Opcao de retencao de topico esta ativada.
CHAN_SET_KEEPTOPIC_OFF
	Opcao de retencao de topico esta desativada.

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_SYNTAX
	SET canal TOPICLOCK {ON | OFF}
CHAN_SET_TOPICLOCK_ON
	Opcao de trava do topico esta ativada.
CHAN_SET_TOPICLOCK_OFF
	Opcao de trava do topico esta desativada.

# SET PRIVATE responses
CHAN_SET_PRIVATE_SYNTAX
	SET canal PRIVATE {ON | OFF}
CHAN_SET_PRIVATE_ON
	Opcao private esta ativada.
CHAN_SET_PRIVATE_OFF
	opcao private esta desativada.

# SET SECUREOPS responses
CHAN_SET_SECUREOPS_SYNTAX
	SET canal SECUREOPS {ON | OFF}
CHAN_SET_SECUREOPS_ON
	Opcao Secure ops esta ativada.
CHAN_SET_SECUREOPS_OFF
	Opcao Secure ops esta desativada.

# SET LEAVEOPS responses
CHAN_SET_LEAVEOPS_SYNTAX
	SET canal LEAVEOPS {ON | OFF}
CHAN_SET_LEAVEOPS_ON
	Opcao LEAVE OPS esta ativada.
CHAN_SET_LEAVEOPS_OFF
	Opcao LEAVE OPS esta desativada.

# SET RESTRICTED responses
CHAN_SET_RESTRICTED_SYNTAX
	SET canal RESTRICTED {ON | OFF}
CHAN_SET_RESTRICTED_ON
	Opcao de acesso restrito esta ativada.
CHAN_SET_RESTRICTED_OFF
	Opcao de acesso restrito esta desativada.

# SET SECURE responses
CHAN_SET_SECURE_SYNTAX
	SET canal SECURE {ON | OFF}
CHAN_SET_SECURE_ON
	Opcao secure esta ativada.
CHAN_SET_SECURE_OFF
	Opcao secure esta desativada.

# SET OPNOTICE responses
CHAN_SET_OPNOTICE_SYNTAX
	SET canal OPNOTICE {ON | OFF}
CHAN_SET_OPNOTICE_ON
	Opcao Op-Notice esta ativada.
CHAN_SET_OPNOTICE_OFF
	Opcao Op-Notice esta desativada.

# SET ENFORCE responses
CHAN_SET_ENFORCE_SYNTAX
	SET canal ENFORCE {ON | OFF}
CHAN_SET_ENFORCE_ON
	Op$Bgc(Bo Enforce esta agora LIGADA.
CHAN_SET_ENFORCE_OFF
	Op$Bgc(Bo Enforce esta agora DESLIGADA.

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_SYNTAX
	SET canal NOEXPIRE {ON | OFF}
CHAN_SET_NOEXPIRE_ON
	Canal %s nao ira expirar.
CHAN_SET_NOEXPIRE_OFF
	Canal %s ira expirar.

# UNSET responses
CHAN_UNSET_SYNTAX
	UNSET canal {SUCCESSOR | URL | EMAIL | ENTRYMSG}
CHAN_SUCCESSOR_UNSET
	Sucessor para %s retirado.
CHAN_URL_UNSET
	Associacao a URL para o canal %s foi desfeita.
CHAN_EMAIL_UNSET
	Associacao ao e-mail do canal %s foi desfeita.
CHAN_ENTRY_MSG_UNSET
	A designacao atual da mensagem de entrada do canal %s foi desfeita.

# ACCESS messages
CHAN_ACCESS_SYNTAX
	ACCESS canal {ADD | DEL | LIST | COUNT} [nick [nivel] | entry-list]
CHAN_ACCESS_DISABLED
	Desculpe, modificacao da lista de acesso do canal esta temporariamente desativada.
CHAN_ACCESS_LEVEL_NONZERO
	Nivel de acesso deve ser diferente de zero.
CHAN_ACCESS_LEVEL_RANGE
	Nivel de acesso deve estar entre %d e %d .
CHAN_ACCESS_NICKS_ONLY
	Listas de acesso de canais devem conter apenas nicks registrados.
CHAN_ACCESS_REACHED_LIMIT
	Desculpe, voce soh pode ter %d entradas de acesso en um canal.
CHAN_ACCESS_LEVEL_UNCHANGED
	Nivel de acesso de %s no canal %s nao foi mudado de %d.
CHAN_ACCESS_LEVEL_CHANGED
	Nivel de acesso para %s no canal %s mudado para %d.
CHAN_ACCESS_ADDED
	%s adicionado na lista de acesso do canal %s no nivel %d.
CHAN_ACCESS_NO_SUCH_ENTRY
	Entrada desconhecida (#%d) na lista de acesso do canal %s.
CHAN_ACCESS_NOT_FOUND
	%s nao foi encontrado na lista de acesso do canal %s.
CHAN_ACCESS_NO_MATCH
	Nenhuma entrada encontrada na lista de acesso do %s.
CHAN_ACCESS_DELETED
	%s apagado da lista de acesso do canal %s.
CHAN_ACCESS_DELETED_ONE
	Apagada uma entrada da lista de acesso do %s.
CHAN_ACCESS_DELETED_SEVERAL
	Apagada %d entradas da lista de acesso do %s.
CHAN_ACCESS_LIST_EMPTY
	Lista de acesso do %s esta vazia.
CHAN_ACCESS_LIST_HEADER
	Lista de acesso do canal %s:
	  Num   Niv  Nick
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s
CHAN_ACCESS_COUNT
	%s tem %d entradas na lista de acesso.

# XOP (AOP/SOP/VOP) responses
CHAN_SOP_SYNTAX
	SOP canal {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_AOP_SYNTAX
	AOP canal {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_HOP_SYNTAX
	HOP canal {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_VOP_SYNTAX
	VOP canal {ADD | DEL | LIST | COUNT} [nick | entry-list]
CHAN_XOP_ADDED
	%s adicionado ao %s na lista de %s
CHAN_XOP_LEVEL_CHANGED
	%s movido no %s para a lista de %s
CHAN_XOP_LEVEL_UNCHANGED
	%s jah esta no %s na lista de %s
CHAN_XOP_NICKS_ONLY
	As lista de SOP, AOP e VOP soh podem conter nicknames registrados.
CHAN_XOP_NICKS_ONLY_HOP
	As lista de SOP, AOP, HOP e VOP soh podem conter nicknames registrados.
CHAN_XOP_REACHED_LIMIT
	Desculpe, o numero de entradas na suas listas de SOP, AOP e VOP
	nao podem ter um total de mais de %d entradas. Limete excedido.
CHAN_XOP_REACHED_LIMIT_HOP
	Desculpe, o numero de entradas na suas listas de SOP, AOP, HOP e VOP
	nao podem ter um total de mais de %d entradas. Limete excedido.
CHAN_XOP_NOT_FOUND
	%s nao encontrado no %s na lista de %s.
CHAN_XOP_NO_SUCH_ENTRY
	Nenhuma entrada (#%d) no %s na lista de %s.
CHAN_XOP_NO_MATCH
	Nenhuma entrada similar no %s na lista de %s.
CHAN_XOP_DELETED
	%s apagado do %s da lista de %s.
CHAN_XOP_DELETED_ONE
	Apagada 1 entrada do %s da lista de %s.
CHAN_XOP_DELETED_SEVERAL
	Apagadas %d entradas do %s da lista de %s.
CHAN_XOP_LIST_EMPTY
	%s %s list is empty.
CHAN_XOP_LIST_HEADER
	%s list for %s:
	  Num   Nick
CHAN_XOP_LIST_FORMAT
	  %3d   %s%s%s%s
CHAN_XOP_COUNT
	O %s na lista de %s tem %d entradas.

# AKICK responses
CHAN_AKICK_SYNTAX
	AKICK canal {ADD | DEL | LIST | VIEW | ENFORCE | COUNT} [nick | mascara]
CHAN_AKICK_DISABLED
	Desculpe, modificacao da lista de autokicks do canal esta temporariamente desativado.
CHAN_AKICK_ALREADY_EXISTS
	%s ja existe na lista de autokicks do canal %s.
CHAN_AKICK_REACHED_LIMIT
	Desculpe, voce so deve ter %d mascaras na lista de autokicks do canal.
CHAN_AKICK_ADDED
	%s adicionado na lista de autokicks do canal  %s.
CHAN_AKICK_NO_SUCH_ENTRY
	Entrada desconhecida (#%d) na lista de autokicks do canal %s.
CHAN_AKICK_NOT_FOUND
	%s nao encontrado na lista de autokicks do canal %s.
CHAN_AKICK_NO_MATCH
	Nenhuma entrada encontrada na lista de autokick do %s.
CHAN_AKICK_DELETED
	%s retirado da lista de autokicks do canal %s.
CHAN_AKICK_DELETED_ONE
	Apagada uma entrada da lista de autokick do %s.
CHAN_AKICK_DELETED_SEVERAL
	Apagada %d entradas da lista de autokick do %s.
CHAN_AKICK_LIST_EMPTY
	Lista de autokick do %s esta vazia.
CHAN_AKICK_LIST_HEADER
	Lista de Autokicks do canal %s:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s
CHAN_AKICK_VIEW_FORMAT
	  %3d %s (por %s)
	    %s
CHAN_AKICK_ENFORCE_DONE
	AKICK ENFORCE para %s feito; %d usuarios foram afetados.
CHAN_AKICK_COUNT
	%s tem %d entradas na lista de AKICK.

# LEVELS responses
CHAN_LEVELS_SYNTAX
	LEVELS canal {SET | DIS[ABLE] | LIST | RESET} [item [nivel]]
CHAN_LEVELS_RANGE
	Nivel deve estar entre %d e %d.
CHAN_LEVELS_CHANGED
	Nivel de %s no canal %s alterado para %d.
CHAN_LEVELS_UNKNOWN
	Opcao %s desconhecida. Digite /msg %s HELP LEVELS DESC para uma lista valida de opcoes.
CHAN_LEVELS_DISABLED
	%s desabilitado no canal %s.
CHAN_LEVELS_LIST_HEADER
	Configuracao dos niveis de acesso do canal %s:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (desabilitado)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (somente fundador)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	Niveis de acesso do canal %s foi refeita usando os padroes.

# INFO responses
CHAN_INFO_SYNTAX
	INFO canal [ALL]
CHAN_INFO_HEADER
	Informacao sobre o canal %s:
CHAN_INFO_FOUNDER
	           Fundador: %s (%s)
CHAN_INFO_NO_FOUNDER
	           Fundador: %s
CHAN_INFO_SUCCESSOR
	           Sucessor: %s (%s)
CHAN_INFO_NO_SUCCESSOR
	           Sucessor: %s
CHAN_INFO_DESCRIPTION
	          Descricao: %s
CHAN_INFO_ENTRYMSG
	Mensagem de entrada: %s
CHAN_INFO_TIME_REGGED
	         Registrado: %s
CHAN_INFO_LAST_USED
	         Ultimo uso: %s
CHAN_INFO_LAST_TOPIC
	      Ultimo topico: %s
CHAN_INFO_TOPIC_SET_BY
	Topico ajustado por: %s
CHAN_INFO_URL
	                URL: %s
CHAN_INFO_EMAIL
	             E-mail: %s
CHAN_INFO_OPTIONS
	             Opcoes: %s
CHAN_INFO_OPT_PRIVATE
	Privado
CHAN_INFO_OPT_KEEPTOPIC
	Retencao de topico
CHAN_INFO_OPT_TOPICLOCK
	Trava do topico
CHAN_INFO_OPT_SECUREOPS
	Protecao de ops
CHAN_INFO_OPT_LEAVEOPS
	LEAVE OPS
CHAN_INFO_OPT_RESTRICTED
	Acesso restrito
CHAN_INFO_OPT_SECURE
	Seguranca
CHAN_INFO_OPT_OPNOTICE
	Op-Notice
CHAN_INFO_OPT_ENFORCE
	Enforce
CHAN_INFO_OPT_NONE
	Nenhuma
CHAN_INFO_MODE_LOCK
	    Trava dos modos: %s
CHAN_INFO_NO_EXPIRE
	Este canal nao vai expirar.
CHAN_INFO_SUSPEND_DETAILS
	Suspenso por %s em %s (%s).
CHAN_INFO_SUSPEND_REASON
	Razao: %s
CHAN_INFO_SHOW_ALL
	Para maiores informacoes, digite: /msg %s INFO %s ALL

# LIST responses
CHAN_LIST_SYNTAX
	LIST padrao
CHAN_LIST_SERVADMIN_SYNTAX
	LIST modelo [FORBIDDEN] [NOEXPIRE] [SUSPENDED]
CHAN_LIST_HEADER
	Listas das entradas que satisfazem %s:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	Fim da listagem - %d/%d entradas mostradas.

# INVITE responses
CHAN_INVITE_SYNTAX
	INVITE canal
CHAN_INVITE_OK
	Convidando %s  para o canal %s.

# OP/DEOP/VOICE/DEVOICE responses
CHAN_OPVOICE_SYNTAX
	%s canal nick
CHAN_OP_SUCCEEDED
	Dado op a %s no %s.
CHAN_OP_FAILED
	Impossivel dar op a %s no %s.
CHAN_DEOP_SUCCEEDED
	Retirado op de %s no %s.
CHAN_DEOP_FAILED
	Impossivel tirar op de %s no %s.
CHAN_VOICE_SUCCEEDED
	Dado voice a %s no %s.
CHAN_VOICE_FAILED
	Impossivel dar voice a %s no %s.
CHAN_DEVOICE_SUCCEEDED
	Retirado voice de %s no %s.
CHAN_DEVOICE_FAILED
	Impossivel tirar voice de %s no %s.
CHAN_HALFOP_SUCCEEDED
	Dado halfop a %s no %s.
CHAN_HALFOP_FAILED
	Incapaz de dar halfop %s no %s.
CHAN_DEHALFOP_SUCCEEDED
	Tirado halfop de %s no %s.
CHAN_DEHALFOP_FAILED
	Impossivel retirar halfop de %s no %s.
CHAN_PROTECT_SUCCEEDED
	%s protegido no canal %s.
CHAN_PROTECT_FAILED
	Incapaz de proteger %s no canal %s.
CHAN_DEPROTECT_SUCCEEDED
	%s desprotegido no canal %s.
CHAN_DEPROTECT_FAILED
	Incapaz de desproteger %s no canal %s.

# UNBAN responses
CHAN_UNBAN_SYNTAX
	UNBAN canal
CHAN_UNBANNED
	Voce foi desbanido do %s.

# CLEAR responses
CHAN_CLEAR_SYNTAX
	CLEAR canal tipo
CHAN_CLEARED_BANS
	Todos os bans do canal %s foram removidos.
CHAN_CLEARED_EXCEPTIONS
	Todas as excecoes do canal %s foram removidas.
CHAN_CLEARED_MODES
	Todos os modos do canal %s foram removidos.
CHAN_CLEARED_OPS
	Modo +o dos Operadores do canal %s foi retirado.
CHAN_CLEARED_HALFOPS
	Modo +h foi removido do canal %s.
CHAN_CLEARED_VOICES
	Modo +v de alguns usuarios do canal %s foi retirado.
CHAN_CLEARED_USERS
	Todos os usuarios foram kickados do canal %s.

# GETPASS responses
CHAN_GETPASS_SYNTAX
	GETPASS canal
CHAN_GETPASS_UNAVAILABLE
	Comando GETPASS nao esta disponivel porque a encriptacao esta em uso.
CHAN_GETPASS_PASSWORD_IS
	Senha do canal %s eh %s.

# FORBID responses
CHAN_FORBID_SYNTAX
	FORBID canal
CHAN_FORBID_SUCCEEDED
	Canal %s esta agora proibido de ser utilizado.
CHAN_FORBID_FAILED
	Nao foi possivel bloquear o uso do canal %s!

# SUSPEND responses
CHAN_SUSPEND_SYNTAX
	SUSPEND [+expiracao] canal razao
CHAN_SUSPEND_SUCCEEDED
	Canal %s foi suspenso.
CHAN_SUSPEND_ALREADY_SUSPENDED
	Canal %s jah esta suspenso.

# UNSUSPEND responses
CHAN_UNSUSPEND_SYNTAX
	UNSUSPEND channel
CHAN_UNSUSPEND_SUCCEEDED
	Canal %s foi reativado.
CHAN_SUSPEND_NOT_SUSPENDED
	Canal %s nao esta suspenso.

###########################################################################
#
# Mensagens do MemoServ
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	Voce tem uma mensagem nova.
MEMO_HAVE_NEW_MEMOS
	Voce tem %d mensagens novas.
MEMO_TYPE_READ_LAST
	Digite /msg %s READ LAST parar ler.
MEMO_TYPE_READ_NUM
	Digite /msg %s READ %d para ler.
MEMO_TYPE_LIST_NEW
	Digite /msg %s LIST NEW para lista-las.
MEMO_AT_LIMIT
	Atencao: Voce atingiu o limite maximo de mensagens (%d).  Voce nao podera receber nenhuma mensagem antes de deletar alguma das suas atuais.
MEMO_OVER_LIMIT
	Atencao: Voce esta acima do limite maximo de mensagens (%d).  Voce nao podera receber nenhuma mensagem antes de deletar alguma das suas atuais.
MEMO_NEW_MEMO_ARRIVED
	Voce tem uma mensagem nova de %s.
	Digite /msg %s READ %d para ler.

# Multi-use responses
MEMO_HAVE_NO_MEMOS
	Voce nao tem mensagens.
MEMO_X_HAS_NO_MEMOS
	%s nao tem mensagens.
MEMO_DOES_NOT_EXIST
	Mensagem %d nao existe!
MEMO_LIST_NOT_FOUND
	Nenhuma mensagem encontrada.

# SEND responses
MEMO_SEND_SYNTAX
	SEND {nick | canal} mensagem-texto
MEMO_SEND_DISABLED
	Desculpe, envio de mensagens temporariamente desativado.
MEMO_SEND_PLEASE_WAIT
	Por favor espere %d segundos antes de usar o comando SEND novamente.
MEMO_X_GETS_NO_MEMOS
	%s nao pode receber mensagens.
MEMO_X_HAS_TOO_MANY_MEMOS
	%s atualmente tem muitas mensagens e nao pode receber mais.
MEMO_SENT
	Mensagem enviada para %s.

# LIST responses
MEMO_LIST_SYNTAX
	LIST [canal] [list | NEW]
MEMO_HAVE_NO_NEW_MEMOS
	Voce nao tem mensagens novas.
MEMO_X_HAS_NO_NEW_MEMOS
	%s nao tem mensagens novas.
MEMO_LIST_MEMOS
	Mensagens para %s.  Para ler, digite: /msg %s READ numero
MEMO_LIST_NEW_MEMOS
	Novas mensagens para %s. Para ler, digite: /msg %s READ numero
MEMO_LIST_CHAN_MEMOS
	Mensagens para o canal %s.  Para ler, digite: /msg %s READ %s numero
MEMO_LIST_CHAN_NEW_MEMOS
	Novas mensagens para o canal %s.  Para ler, digite: /msg %s READ %s numero
MEMO_LIST_HEADER
	 Num  Remetente         Data/Hora
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_READ_SYNTAX
	READ [canal] {list | LAST | NEW}
MEMO_HEADER
	Mensagem %d de %s (%s).  Para apagar, digite: /msg %s DEL %d
MEMO_CHAN_HEADER
	Mensagem %d de %s (%s).  Para apagar, digite: /msg %s DEL %s %d
MEMO_TEXT
	%s

# DEL responses
MEMO_DEL_SYNTAX
	DEL [canal] {num | list | ALL}
MEMO_DELETED_NONE
	Sem mensagens a serem apagadas.
MEMO_DELETED_ONE
	Mensagem %d foi apagada.
MEMO_DELETED_SEVERAL
	%d mensagens foram apagadas.
MEMO_DELETED_ALL
	Todas as suas mensagens foram apagadas.

# SET responses
MEMO_SET_SYNTAX
	SET opcao parametros
MEMO_SET_DISABLED
	Desculpe, opcao de ajuste de mensagem esta temporariamente desativada.
MEMO_SET_UNKNOWN_OPTION
	Opcao SET %s desconhecida.

# SET NOTIFY responses
MEMO_SET_NOTIFY_SYNTAX
	SET NOTIFY {ON | LOGON | NEW | OFF}
MEMO_SET_NOTIFY_ON
	%s notificara voce sobre mensagens quando voce conectar e quando enviadas voce.
MEMO_SET_NOTIFY_LOGON
	%s notificara voce sobre suas mensagens quando voce conectar ou sair de um /AWAY.
MEMO_SET_NOTIFY_NEW
	%s notificara voce sobre suas mensagens quando elas forem enviadas a voce.
MEMO_SET_NOTIFY_OFF
	%s nao notificara voce sobre qualquer aviso de mensagens.

# SET LIMIT responses
MEMO_SET_LIMIT_SYNTAX
	SET LIMIT [canal] limite
MEMO_SET_LIMIT_SERVADMIN_SYNTAX
	SET LIMIT [usuario | canal] {limit | NONE} [HARD]
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	Voce nao esta apto a alterar seu limite de mensagens.
MEMO_SET_LIMIT_FORBIDDEN
	O limite de mensagens para %s nao pode ser mudado.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	Voce nao pode ajustar seu limite de mensagens acima de %d.
MEMO_SET_LIMIT_TOO_HIGH
	Voce nao pode ajustar o limite de mensagens de %s acima de %d.
MEMO_SET_LIMIT_OVERFLOW
	Limite de mensagens muito alto; limitando para %d ao inves disso.
MEMO_SET_YOUR_LIMIT
	Seu limite de mensagens foi ajustado para %d.
MEMO_SET_YOUR_LIMIT_ZERO
	Voce nao esta mais apto a receber mensagens.
MEMO_UNSET_YOUR_LIMIT
	Seu limite de mensagens foi desativado.
MEMO_SET_LIMIT
	Limite de mensagens para %s ajustado para %d.
MEMO_SET_LIMIT_ZERO
	Limite de mensagens para %s ajustado para 0.
MEMO_UNSET_LIMIT
	Limite de mensagens para %s esta desativado.

# INFO responses
MEMO_INFO_SYNTAX
	INFO [canal]
MEMO_INFO_SERVADMIN_SYNTAX
	INFO [nick | canal]
MEMO_INFO_NO_MEMOS
	Voce nao tem mensagens.
MEMO_INFO_MEMO
	Voce tem uma mensagem.
MEMO_INFO_MEMO_UNREAD
	Voce atualmente tem uma mensagem, e esta ainda nao foi lida.
MEMO_INFO_MEMOS
	Voce atualmente tem %d mensagens.
MEMO_INFO_MEMOS_ONE_UNREAD
	Voce atualmente tem %d mensagens, das quais uma nao foi lida.
MEMO_INFO_MEMOS_SOME_UNREAD
	Voce atualmente tem %d mensagens, das quais %d nao foram lidas.
MEMO_INFO_MEMOS_ALL_UNREAD
	Voce tem %d mensagens; todas nao lidas.
MEMO_INFO_LIMIT
	Seu limite de mensagem eh %d.
MEMO_INFO_HARD_LIMIT
	Seu limite de mensagem eh %d, e nao pode ser mudado.
MEMO_INFO_LIMIT_ZERO
	Seu limite de mensagem eh 0; voce nao recebera nenhuma mensagem.
MEMO_INFO_HARD_LIMIT_ZERO
	Seu limite de mensagem eh 0; voce nao recebera nenhuma mensagem, e nao podera mudar este limite.
MEMO_INFO_NO_LIMIT
	Voce nao tem limite para as mensagens que podera possuir.
MEMO_INFO_NOTIFY_OFF
	Voce nao sera notificado por novas mensagens.
MEMO_INFO_NOTIFY_ON
	Voce sera notificado por novas mensagens no logon e quando elas chegarem.
MEMO_INFO_NOTIFY_RECEIVE
	Voce sera notificado por novas mensagens quando elas chegarem.
MEMO_INFO_NOTIFY_SIGNON
	%s eh notificado por novas mensagens no logon.
MEMO_INFO_X_NO_MEMOS
	%s nao tem mensagens.
MEMO_INFO_X_MEMO
	%s tem atualmente uma mensagem.
MEMO_INFO_X_MEMO_UNREAD
	%s tem atualmente uma mensagem, ainda nao lida.
MEMO_INFO_X_MEMOS
	%s tem atualmente %d mensagens.
MEMO_INFO_X_MEMOS_ONE_UNREAD
	%s tem atualmente %d mensagens, uma nao foi lida.
MEMO_INFO_X_MEMOS_SOME_UNREAD
	%s tem atualmente %d mensagens, %d nao lidas.
MEMO_INFO_X_MEMOS_ALL_UNREAD
	%s tem atualmente %d mensagens; todas nao lidas.
MEMO_INFO_X_LIMIT
	O limite de mensagens de %s eh %d.
MEMO_INFO_X_HARD_LIMIT
	O limite de memos de %s eh %d.
MEMO_INFO_X_NO_LIMIT
	%s nao tem limite de mensagens.
MEMO_INFO_X_NOTIFY_OFF
	%s nao eh notificado por novas mensagens.
MEMO_INFO_X_NOTIFY_ON
	%s eh notificado por novas mensagens no logon e quando elas chegam.
MEMO_INFO_X_NOTIFY_RECEIVE
	%s eh notificado por novas mensagens quando elas chegam.
MEMO_INFO_X_NOTIFY_SIGNON
	%s eh notificado por novas mensagens no logon.

###########################################################################
#
# Mensagens do OperServ
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	Services nao estao conseguindo mudar modos.  Seus servidores estao configurados corretamente?
OPER_BOUNCY_MODES_U_LINE
	Services nao estao conseguindo mudar modos.  As U:lines dos seus servidores estao configuradas corretamente?
OPER_SKELETON_MODE
	Esta funcao nao eh disponivel em modo skeleton.

# GLOBAL responses
OPER_GLOBAL_SYNTAX
	GLOBAL mensagem

# STATS responses
OPER_STATS_UNKNOWN_OPTION
	Opcao STATS %s desconhecida.
OPER_STATS_RESET_USER_COUNT
	O contador de maximo de usuarios foi reiniciado.
OPER_STATS_CURRENT_USERS
	Usuarios atuais   : %d (%d ops)
OPER_STATS_MAX_USERS
	Maximo de usuarios: %d
OPER_STATS_UPTIME_DHMS
	Services ativos a %d %s, %02d:%02d
# If >= 1 hour, hours and minutes; if < 1 hour, minutes and seconds
OPER_STATS_UPTIME_HM_MS
	Services ativos a %d %s, %d %s
OPER_STATS_BYTES_READ
	Bytes lidos   : %5d kB
OPER_STATS_BYTES_WRITTEN
	Bytes escritos: %5d kB
OPER_STATS_USER_MEM
	Usuario : %6d registros, %5d kB
OPER_STATS_SERVER_MEM
	Servidor: %6d registros, %5d kB
OPER_STATS_CHANNEL_MEM
	Canal   : %6d registros, %5d kB
OPER_STATS_NICKSERV_MEM
	NickServ: %6d registros, %5d kB
OPER_STATS_CHANSERV_MEM
	ChanServ: %6d registros, %5d kB
OPER_STATS_MEMOSERV_MEM
	MemoServ: %6d registros, %5d kB
OPER_STATS_STATSERV_MEM
	StatServ: %6d registros, %5d kB
OPER_STATS_OPERSERV_MEM
	OperServ: %6d registros, %5d kB
OPER_STATS_AKILL_COUNT
	Numero atual de AKILLs: %d
OPER_STATS_AKILL_EXPIRE_DAYS
	Tempo default para expirar AKILL: %d dias
OPER_STATS_AKILL_EXPIRE_DAY
	Tempo default para expirar AKILL: 1 dia
OPER_STATS_AKILL_EXPIRE_HOURS
	Tempo default para expirar AKILL: %d horas
OPER_STATS_AKILL_EXPIRE_HOUR
	Tempo default para expirar AKILL: 1 hora
OPER_STATS_AKILL_EXPIRE_MINS
	Tempo default para expirar AKILL: %d minutos
OPER_STATS_AKILL_EXPIRE_MIN
	Tempo default para expirar AKILL: 1 minuto
OPER_STATS_AKILL_EXPIRE_NONE
	Tempo default para expirar AKILL: nao expira
OPER_STATS_SESSIONS_MEM
	Sessoes : %6d registros, %5d kB

# MODE responses
OPER_MODE_SYNTAX
	MODE canal modos

# CLEARMODES responses
OPER_CLEARMODES_SYNTAX
	CLEARMODES canal [ALL]
OPER_CLEARMODES_DONE
	Bans e modos binarios do canal %s foram limpos.
OPER_CLEARMODES_ALL_DONE
	Todos os modos do canal %s foram limpos.

# CLEARCHAN responses
OPER_CLEARCHAN_SYNTAX
	CLEARCHAN canal
OPER_CLEARCHAN_DONE
	Todos os usuarios foram removidos do canal %s.

# KICK responses
OPER_KICK_SYNTAX
	KICK canal usuario razao

# ADMIN responses
OPER_ADMIN_SYNTAX
	ADMIN {ADD | DEL | LIST} [nick]
OPER_ADMIN_ADD_SYNTAX
	ADMIN ADD nick
OPER_ADMIN_DEL_SYNTAX
	ADMIN DEL nick
OPER_ADMIN_SKELETON
	Services esta no modo skeleton; o comando ADMIN nao esta disponivel.
OPER_ADMIN_EXISTS
	%s ja esta na lista de Administradores dos Services.
OPER_ADMIN_ADDED
	%s adicionado na lista de Administradores dos Services.
OPER_ADMIN_TOO_MANY
	Muitas entradas (%d) na lista dos Administradores dos Services; impossivel adicionar mais.
OPER_ADMIN_REMOVED
	%s foi removido da lista dos Administradores dos Services.
OPER_ADMIN_NOT_FOUND
	%s nao foi encontrado na lista dos Administradores dos Services.
OPER_ADMIN_LIST_HEADER
	Lista de Administradores dos Services:

# OPER responses
OPER_OPER_SYNTAX
	OPER {ADD | DEL | LIST} [nick]
OPER_OPER_ADD_SYNTAX
	OPER ADD nick
OPER_OPER_DEL_SYNTAX
	OPER DEL nick
OPER_OPER_SKELETON
	Services esta no modo skeleton; o comando OPER nao esta disponivel.
OPER_OPER_EXISTS
	%s ja existe na lista dos Operadores dos Services.
OPER_OPER_ADDED
	%s adicionado a lista de Operadores dos Services.
OPER_OPER_TOO_MANY
	Muitas entradas (%d) na lista dos Operadores dos Services; impossivel adicionar mais.
OPER_OPER_REMOVED
	%s removido da lista de Operadores dos Services.
OPER_OPER_NOT_FOUND
	%s nao encontrado na lista de Operadores dos Services.
OPER_OPER_LIST_HEADER
	Lista de Operadores dos Services:

# AKILL responses
OPER_AKILL_SYNTAX
	AKILL {ADD | DEL | LIST | VIEW | COUNT} [[+tempo] mascara [razao]]
OPER_AKILL_ADD_SYNTAX
	AKILL ADD [+tempo] mascara razao
OPER_AKILL_DEL_SYNTAX
	AKILL DEL mascara
OPER_TOO_MANY_AKILLS
	Lista de AKILL esta cheia!
OPER_AKILL_NO_NICK
	Lembre-se: Mascaras de AKILL nao podem conter nicks; tenha a certeza que voce nao incluiu uma parte do nick na sua mascara.
OPER_AKILL_MASK_TOO_GENERAL
	A mascara de AKILL eh muito generica.
OPER_AKILL_ADDED
	%s adicionado na lista de AKILL.
OPER_AKILL_REMOVED
	%s removido da lista de AKILL.
OPER_AKILL_NOT_FOUND
	%s nao encontrado na lista de AKILL.
OPER_AKILL_LIST_HEADER
	Lista de AKILL atual:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, reason
OPER_AKILL_VIEW_FORMAT
	%s (pelo %s em %s; %s)
	    %s
OPER_AKILL_COUNT
	Existem %d mascaras de host na lista de AKILL.

# SU responses
OPER_SU_SYNTAX
	SU password
OPER_SU_NO_PASSWORD
	O comando SU nao esta disponivel porque nenhuma senha de super-usuario foi colocada.
OPER_SU_SUCCEEDED
	Agora voce tem privilegios de super-usuario de Services.
OPER_SU_FAILED
	Incapaz de verificar a senha.

# SET responses
OPER_SET_SYNTAX
	SET opcao selecao
OPER_SET_IGNORE_ON
	Ignore code sera usado.
OPER_SET_IGNORE_OFF
	Ignore code nao ser usado.
OPER_SET_IGNORE_ERROR
	Parametro para IGNORE deve ser ON ou OFF.
OPER_SET_READONLY_ON
	Services esta agora no modo read-only.
OPER_SET_READONLY_OFF
	Services agora estao no modo leitura-escrita (read-write).
OPER_SET_READONLY_ERROR
	Parametro para READONLY deve ser ON ou OFF.
OPER_SET_DEBUG_ON
	Services esta agora no modo de depuracao (debug).
OPER_SET_DEBUG_OFF
	Services esta no modo de nao-depuracao (non-debug).
OPER_SET_DEBUG_LEVEL
	Services esta no modo de depuracao (nivel %d).
OPER_SET_DEBUG_ERROR
	Parametro para  DEBUG deve ser ON, OFF ou um numero positivo.
OPER_SET_SUPASS_FAILED
	Incapaz de colocar senha de super-usuario de Services.
OPER_SET_SUPASS_OK
	Senha de super-usuario de Services foi trocada.
OPER_SET_SUPASS_NONE
	Senha de super-usuario de Services foi desativada.
OPER_SET_UNKNOWN_OPTION
	Opcao %s desconhecida.

# JUPE responses
OPER_JUPE_SYNTAX
	JUPE nome-do-servidor [razao]

# RAW responses
OPER_RAW_SYNTAX
	RAW texto

# UPDATE responses
OPER_UPDATING
	Atualizando banco de dados.

# LISTIGNORE responses
OPER_IGNORE_LIST
	Lista de ignore do Services:
OPER_IGNORE_LIST_EMPTY
	Lista de ignore esta vazia.

# KILLCLONES responses
OPER_KILLCLONES_SYNTAX
	KILLCLONES nick
OPER_KILLCLONES_UNKNOWN_NICK
	Nao pude encontrar o usuario %s.


###########################################################################
#
# Session Limiting and Exception messages
#
########################################################################### 

# EXCEPTION responses 
OPER_EXCEPTION_SYNTAX
	EXCEPTION {ADD | DEL | MOVE | LIST | VIEW} [parametros]
OPER_EXCEPTION_ADD_SYNTAX
	EXCEPTION ADD [+expiry] mascara limite razao
OPER_EXCEPTION_DEL_SYNTAX
	EXCEPTION DEL {mascara | lista}
OPER_EXCEPTION_MOVE_SYNTAX
	EXCEPTION MOVE num posicao
OPER_EXCEPTION_DISABLED
	Limitacao de conexoes esta desativada.
OPER_EXCEPTION_ALREADY_PRESENT
	Mascara %s ja presente na lista de excecoes.
OPER_EXCEPTION_TOO_MANY
	Lista de excecoes ao limite de conexoes esta cheia!
OPER_EXCEPTION_ADDED
	Limite de conexao para %s especificado como %d.
OPER_EXCEPTION_MOVED
	Excecao para %s (#%d) movida para a posicao %d.
OPER_EXCEPTION_NO_SUCH_ENTRY
	Sem cadastro (#%d) na Lista de excecoes ao limite de conexoes.
OPER_EXCEPTION_NOT_FOUND
	%s nao foi encontrado na Lista de excecoes ao limite de conexoes.
OPER_EXCEPTION_NO_MATCH
	Nao ha entradas compativeis na Lista de excecoes ao limite de conexoes.
OPER_EXCEPTION_DELETED
	%s removida da Lista de excecoes ao limite de conexoes.
OPER_EXCEPTION_DELETED_ONE
	Apagada 1 entrada da Lista de excecoes ao limite de conexoes.
OPER_EXCEPTION_DELETED_SEVERAL
	Apagada %d entradas da Lista de excecoes ao limite de conexoes.
OPER_EXCEPTION_LIST_HEADER
	Lista atual de excecoes ao limite de conexoes:
# mask, limit
OPER_EXCEPTION_LIST_FORMAT
	%3d  %4d   %s
OPER_EXCEPTION_LIST_COLHEAD
	Num  Limite  Host
# mask, set-by, set-time, expires, limit, reason
OPER_EXCEPTION_VIEW_FORMAT
	%3d.  %s  (por %s em %s; %s)
	    Limite: %-4d  - %s
OPER_EXCEPTION_INVALID_LIMIT
	Limite de conexoes invalido;  ele deve ser um inteiro valido maior que zero e menor que %d.
OPER_EXCEPTION_INVALID_HOSTMASK
	Mascara invalida. Apenas mascaras de hosts reais (host.dominio.com) sao validas como excecoes, nao sendo verificadas se houver nick (nick!id@host) ou ident (ident@host).

# SESSION responses
OPER_SESSION_SYNTAX
	SESSION {LIST limite | VIEW host}
OPER_SESSION_LIST_SYNTAX
	SESSION LIST limite
OPER_SESSION_VIEW_SYNTAX
	SESSION VIEW host
OPER_SESSION_DISABLED
	Limitacao de conexoes esta desabilitada.
OPER_SESSION_INVALID_THRESHOLD
	Numero de conexoes invalido. Precisa ser um inteiro maior que 1.
OPER_SESSION_NOT_FOUND
	%s nao encontrado na lista de conexoes.
OPER_SESSION_LIST_HEADER
	Hosts com pelo menos %d conexoes:
OPER_SESSION_LIST_COLHEAD
	Conexoes  Host
# limit, host
OPER_SESSION_LIST_FORMAT
	%6d    %s
# host, sessions, limit
OPER_SESSION_VIEW_FORMAT
	O host %s tem atualmente %d conexoes com limite de %d.

###########################################################################
#
# StatServ messages
#
############################################################################

# General SERVERS responses
STAT_SERVERS_REMOVE_SERV_FIRST
	Servidor %s esta online. Remova-o da rede e tente novamente.
STAT_SERVERS_SERVER_EXISTS
	Servidor %s jah existe.

# SERVERS command syntax
STAT_SERVERS_SYNTAX
	SERVERS opcao parametros

# STATS responses
STAT_SERVERS_STATS_TOTAL
	Total de Servidores: %2d
STAT_SERVERS_STATS_ON_OFFLINE
	             Online: %2d (%d%%)  Offline: %2d (%d%%)
STAT_SERVERS_LASTQUIT_WAS
	        Ultimo Quit: %-30s  %s

# LIST responses
STAT_SERVERS_LIST_HEADER
	Nome do Servidor               Usuarios   Operadores
STAT_SERVERS_LIST_RESULTS
	Fim da lista -- %d/%d servidores online mostrados.

# VIEW responses
STAT_SERVERS_VIEW_HEADER_ONLINE
	%-30s  (online)
STAT_SERVERS_VIEW_HEADER_OFFLINE
	%-30s  (offline)
STAT_SERVERS_VIEW_LASTJOIN
	    Ultima entrada: %s
STAT_SERVERS_VIEW_LASTQUIT
	       Ultimo quit: %s
STAT_SERVERS_VIEW_QUITMSG
	  Mensagem de quit: %s
STAT_SERVERS_VIEW_USERS_OPERS
	          Usuarios: %3d (%2d%%)  Operadores: %3d (%2d%%)
STAT_SERVERS_VIEW_RESULTS
	Fim da lista -- %d/%d servidores mostrados.

# DELETE responses
STAT_SERVERS_DELETE_SYNTAX
	SERVERS DELETE servidor
STAT_SERVERS_DELETE_DONE
	Estatisticas para o servidor %s foram apagadas.

# COPY responses
STAT_SERVERS_COPY_SYNTAX
	SERVERS COPY servidor novonome
STAT_SERVERS_COPY_DONE
	Estatisticas para o servidor %s foram copiadas para %s

# RENAME responses
STAT_SERVERS_RENAME_SYNTAX
	SERVERS RENAME servidor novonome
STAT_SERVERS_RENAME_DONE
	Estatisticas para o servidor %s foram renomeadas para %s

# USERS command syntax
STAT_USERS_SYNTAX
	USERS opcoes parametros

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
	LOGONNEWS {ADD|DEL|LIST} [texto|numero]
NEWS_LOGON_LIST_HEADER
	Mensagens de entrada:
NEWS_LOGON_LIST_ENTRY
	%5d (%s por %s)
	    %s
NEWS_LOGON_LIST_NONE
	Nao existe nenhuma mensagem de entrada.
NEWS_LOGON_ADD_SYNTAX
	LOGONNEWS ADD texto
NEWS_LOGON_ADD_FULL
	Lista de mensagens esta cheia!
NEWS_LOGON_ADDED
	Adicionada nova mensagem de entrada (#%d).
NEWS_LOGON_DEL_SYNTAX
	LOGONNEWS DEL {numero | ALL}
NEWS_LOGON_DEL_NOT_FOUND
	Mensagem de entrada numero %d nao encontrada!
NEWS_LOGON_DELETED
	Mensagem de entrada numero %d apagada.
NEWS_LOGON_DEL_NONE
	Nao ha mensagem de entrada para apagar!
NEWS_LOGON_DELETED_ALL
	Todas as mensagens de entrada apagadas.

NEWS_OPER_SYNTAX
	OPERNEWS {ADD|DEL|LIST} [texto|numero]
NEWS_OPER_LIST_HEADER
	Oper news itens:
NEWS_OPER_LIST_ENTRY
	%5d (%s por %s)
	    %s
NEWS_OPER_LIST_NONE
	Nao ha oper news.
NEWS_OPER_ADD_SYNTAX
	OPERNEWS ADD texto
NEWS_OPER_ADD_FULL
	Lista de oper news esta cheia!
NEWS_OPER_ADDED
	Adicionada nova oper news (#%d).
NEWS_OPER_DEL_SYNTAX
	OPERNEWS DEL {numero | ALL}
NEWS_OPER_DEL_NOT_FOUND
	Oper news numero #%d nao encontrada!
NEWS_OPER_DELETED
	Oper news numero #%d apagada.
NEWS_OPER_DEL_NONE
	Nao ha oper news para apagar!
NEWS_OPER_DELETED_ALL
	Todas as oper news foram apagadas.

NEWS_HELP_LOGON
	Sintaxe: LOGONNEWS ADD texto
	         LOGONNEWS DEL {numero | ALL}
	         LOGONNEWS LIST
	
	Edita ou mostra a lista de logon news. Quando um usuario
	se conecta a rede, estas mensagens sao enviadas para ele.
	(No entanto, nao mais que tres mensagens serao enviadas
	simultaneamente para evitar flood. Se houver mais que tres
	mensagens novas, apenas essas mais novas serao mostradas.)
	
	LOGONNEWS LIST pode ser usado por qualquer IRC operator
	para listar as mensagens atuais. ADD e DEL soh podem
	ser usados pelos Administradores dos Services.

NEWS_HELP_OPER
	Sintaxe: OPERNEWS ADD texto
	         OPERNEWS DEL {numero | ALL}
	         OPERNEWS LIST

	Edita ou mostra a lista de oper news. Quando um usuario
	se torna operador (pelo comando /OPER), estas mensagens
	lhe serao enviadas. (No entanto, nao mais que tres
	mensagens serao enviadas simultaneamente para evitar
	flood. Se houver mais que tres mensagens novas, apenas
	as tres mais novas serao mostradas.)
	
	OPERNEWS LIST pode ser usado por qualquer IRC operator
	para listar as oper news. ADD e DEL soh podem ser usados
	pelos Administradores dos Services.

###########################################################################
#
# Mensagens de help do NickServ
#
###########################################################################

NICK_HELP
	%S permite que voce "registre" um nick e evita que
	outras pessoas o utilizem.  Se o nick nao for usado por %d
	dias, o registro sera cancelado.  Os seguintes comandos
	permitem o registro e a manutencao dos nicks; para
	utiliza-los, digite /msg %S comando.  Para maiores
	informacoes sobre um comando, digite /msg %S HELP comando.
	
	    REGISTER   Registra um nick
	    IDENTIFY   Identifica seu nick com sua senha
	    ACCESS     Modifica a lista de enderecos autorizados
	    LINK       Faz uma ligacao de seu nick com outro
	    SET        Ajusta opcoes, incluindo protecao de kill
	    DROP       Cancela o registro de um nick
	    RECOVER    Derruba outro usuario que esteja usando seu nick
	    RELEASE    Retoma a custodia do seu nick apos um RECOVER
	
	Outros comandos: UNLINK, UNSET, GHOST, INFO, LIST, LISTCHANS,
	                 STATUS
	
	NOTA: Este servico tem a intencao de prover um modo para
	que usuarios do IRC nao tenham sua identidade comprometida.
	Isto NAO eh voltado para facilitar "roubo" dos nicks ou
	outras atitudes ma intencionadas.  O abuso do %S
	resultara em, no minimo, perda do(s) nick(s) abusivo(s).

NICK_HELP_EXPIRE_ZERO
	%S permite voce de "registrar" um nick e impede que
	outros o utilizem. Os comandos seguintes permitem o
	registro e a manutencao dos nicks;  para usa-los, digite
	/msg %S comando. Para mais informacoes sobre um
	comando especifico, digite /msg %S HELP comando.
	
	   REGISTER  Registra um nick
	   IDENTIFY  Identifica seu nick com sua senha
	   ACCESS    Modifica a lista de enderecos autorizados
	   LINK      Faz uma ligacao de seu nick com outro
	   SET       Ajusta opcoes, incluindo protecao de kill
	   DROP      Cancela o registro de um nick
	   RECOVER   Derruba outro usuario que esteja usando seu nick
	   RELEASE   Retoma a custodia do seu nick apos um RECOVER
	
	Outros comandos: UNLINK, UNSET, GHOST, INFO, LIST, LISTCHANS,
	                 STATUS
	
	NOTA: Este servico tem a intencao de prover um modo para que
	usuarios do IRC nao tenham sua identidade comprometida.
	Isto nao eh voltado para facilitar o "roubo" dos nicks ou
	outras atitudes ma intencionadas. O abuso do %S resultara
	em, no minimo, perda do(s) nick(s) abusivos.

NICK_HELP_REGISTER
	Sintaxe: REGISTER senha [email]
	
	Registra seu nick no banco de dados do %S.  Uma vez
	que seu nick esta registrado, voce pode usar os comandos
	SET e ACCESS para configurar as opcoes do seu nick como voce
	preferir depois.  Certifique-se de lembrar sua senha durante
	o registro, voce precisara dela para fazer alteracoes no seu
	nick futuramente.  (Lembre-se que maiusculas diferem: FIDO,
	Fido, e fido sao senhas diferentes!)
	
	Voce pode incluir um endereco de E-mail ao registar seu nickname;
	voce tambem pode colocar um depois usando o comando SET EMAIL.
	
	Sugestoes ao escolher sua senha:
	
	As senhas nao devem ser de facil adivinhacao.  Por exemplo,
	usar seu nome como senha eh uma pessima ideia.  Utilizar seu
	nick como senha eh uma ideia muito pior e, de fato, o %S
	nao permitira isso.  Da mesma maneira, senhas curtas sao
	vulneraveis a testes de erro-e-acerto, entao voce deve
	escolher uma senha com pelo menos 5 caracteres.  Finalmente,
	o caracter "ESPACO" nao pode ser usado em senhas.

NICK_HELP_REGISTER_REQ_EMAIL
	Sintaxe: REGISTER senha email
	 
	Registra seu nick no banco de dados do %S.  Uma vez
	que seu nick esta registrado, voce pode usar os comandos
	SET e ACCESS para configurar as opcoes do seu nick como voce
	preferir depois.  Certifique-se de lembrar sua senha durante
	o registro, voce precisara dela para fazer alteracoes no seu
	nick futuramente.  (Lembre-se que maiusculas diferem: FIDO,
	Fido, e fido sao senhas diferentes!)
	 
	Voce pode incluir um endereco de E-mail ao registar seu nickname;
	voce tambem pode colocar um depois usando o comando SET EMAIL.
	
	Voce deve incluir um endereco de E-mail ao registar seu
	nickname. Voce pode evitar que seu E-mail seja mostrado a outros
	usuarios com o comando SET HIDE (digite /msg %S HELP SET HIDE
	para maiores informacoes).
	
	Sugestoes ao escolher sua senha:
	
	As senhas nao devem ser de facil adivinhacao.  Por exemplo,
	usar seu nome como senha eh uma pessima ideia.  Utilizar seu
	nick como senha eh uma ideia muito pior e, de fato, o %S
	nao permitira isso.  Da mesma maneira, senhas curtas sao
	vulneraveis a testes de erro-e-acerto, entao voce deve
	escolher uma senha com pelo menos 5 caracteres.  Finalmente,
	o caracter "ESPACO" nao pode ser usado em senhas.

NICK_HELP_IDENTIFY
	Sintaxe: IDENTIFY senha
	
	Diz ao %S que voce realmente eh o dono deste nick.
	Muitos comandos exigem que voce se identifique com este
	comando antes de voce usa-los.  A senha deve ser a mesma que
	voce enviou com o comando REGISTER.
	
NICK_HELP_DROP
	Sintaxe: DROP
	
	Retira seu nick do banco de dados do %S.  O nick que
	foi retirado esta livre para qualquer pessoa registrar
	novamente.
	
	Para utilizar este comando, voce primeiro deve se
	identificar com sua senha (/msg %S HELP IDENTIFY para mais
	informacoes).

NICK_HELP_ACCESS
	Sintaxe: ACCESS ADD mascara
	         ACCESS DEL mascara
	         ACCESS LIST
	
	Modifica ou mostra a lista de acesso do seu nick.  Esta eh
	a lista de enderecos a qual sera automaticamente reconhecida
	pelo %S como as permitidas a usarem seu nick.  Se voce quer
	usar um nick de um endereco diferente, voce deve mandar o
	comando IDENTIFY para fazer o %S reconhecer voce.
	
	Exemplos:
	
	    ACCESS ADD mauritz@*.americasnet.com.br
	        Permite o acesso ao usuario mauritz de qualquer
	        maquina do dominio americasnet.com.br.
	
	    ACCESS DEL mauritz@*.americasnet.com.br
	        Desfaz o comando anterior.
	
	    ACCESS LIST
	        Mostra a lista de acesso atual.

NICK_HELP_LINK
	Sintaxe: LINK nick senha
	
	Liga seu nick a outro, efetivamente, fazendo uma ligacao
	do seu nick atual com um outro nick especificado.  Quando
	voce emite este comando, a lista de acesso do seu nick
	atualmente em uso eh apagada e substituida pelo nick que
	voce esta ligando, todos os memos do seu nick atual sao
	adicionados na lista de memos do nick alvo (isso pode
	causar um excesso no limite de memos do nick, em alguns
	casos voce precisa apagar alguns memos antes de poder
	receber mais memos de uma outra pessoa).
	
	Uma vez que a ligacao foi estabilizada, seu nick sera
	transparentemente convertido para o nick alvo em todos
	os lugares nos Services, exceto para os comandos %S
	UNLINK e DROP.
	Por exemplo, voce pode usar um nick ou outro para ler
	o mesmo conjunto de memos (e mensagens enviadas para um nick
	ou outro irao para a mesma lista).  Se voce se identificar
	para um nick, estara automaticamente identificado para o
	outro.  Se um nick ou outro esta na lista de acesso de um
	canal, ambos nicks terao os mesmos privilegios de acesso.
	
	Para usar este comando, voce deve identificar o nick atual
	(usando o comando IDENTIFY), e voce deve fornecer a
	senha para o nick que voce deseja ligar.

NICK_HELP_UNLINK
	Sintaxe: UNLINK [nick senha]
	
	Remove a ligacao com outro nick.  Quando uma ligacao eh
	removida, os modos de um nick e a lista de acesso do nick
	previamente ligado sao copiados para seu nick atual e podem
	ser independetemente alterados.  Suas mensagens nao sao
	copiadas; todas as mensagens permanecerao armazenadas no
	nick ligado anteriormente.
	
	Informando nick e senha como parametros, voce pode desligar o seu
	nick do nick especificado.

NICK_HELP_SET
	Sintaxe: SET opcao parametros
	
	Ajusta varias opcoes de nick.  A opcao pode ser:
	
	    PASSWORD   Ajusta a senha do seu nick
	    LANGUAGE   Ajusta a linguagem dos Services quando
	                   mensagens sao enviadas a voce
	    URL        Associa um endereco URL com seu nick
	    EMAIL      Associa um endereco de e-mail ao seu nick
	    KILL       Ativa/Desativa a protecao de kill para o seu
	                   nick
	    SECURE     Ativa/Desativa o dispostivo de seguranca para
	                   o seu nick
	    PRIVATE    Previne seu nick de aparecer em um /msg %S LIST
	    HIDE       Esconde certas informacoes sobre seu nick
	
	Para usar este comando, voce deve primeiro se identificar
	com sua senha (/msg %S HELP IDENTIFY para maiores
	informacoes).
	
	Digite /msg %S HELP SET opcao para mais informacoes
	sobre um comando especifico.

NICK_HELP_SET_PASSWORD
	Sintaxe: SET PASSWORD nova-senha
	
	Muda a senha que eh utilizada para identificar voce como
	dono do nick.

NICK_HELP_SET_LANGUAGE
	Sintaxe: SET LANGUAGE numero
	
	Muda a linguagem que os Services usa ao enviar mensagens
	para voce (por exemplo, quando responde um comando que voce
	emite).  O numero deve ser escolhido da seguinte lista
	de linguas de apoio:
	

NICK_HELP_SET_URL
	Sintaxe: SET URL url
	
	Associa uma dada URL ao seu nick.  Esta URL sera mostrada
	sempre que alguem solicitar informacao sobre seu nick
	atraves do comando INFO.

NICK_HELP_SET_EMAIL
	Sintaxe: SET EMAIL endereco
	
	Associa um endereco de e-mail designado ao seu nick.  Este
	endereco sera sempre mostrado quando alguem solicitar
	informacao sobre seu nick atraves do comando INFO.

NICK_HELP_SET_KILL
	Sintaxe: SET KILL {ON | QUICK | IMMED | OFF}
	
	Possibilita a protecao de KILL do seu nick.  Com a protecao
	de KILL acionada, se outro usuario tentar tomar seu nick,
	sera dado 1 minuto para este mudar de nick, apos isso, sera
	forcadamente removido do IRC pelo %S.
	
	Se voce selecionar QUICK, sera dado ao usuario somente 20
	segundos para mudar de nick ao inves do usual (60 segundos).
	Se voce selecionar IMMED, o usuario sera derrubado (kill)
	imediatamente sem ser advertido ou ser dada uma chance para
	ele mudar de nick.  Por favor, nao use esta opcao a menos
	que seja necessaria.  Os Administradores da sua rede podem
	deixar essa opcao desabilitada.

NICK_HELP_SET_SECURE
	Sintaxe: SET SECURE {ON | OFF}
	
	Torna os recursos de seguranca do %S ativos (ON) ou
	desativos (OFF) sobre o seu nick. Com o SECURE acionado,
	voce deve entrar com sua senha antes de ser reconhecido
	como usuario do nick, independentemente do fato do seu
	endereco constar na lista de acesso.  Entretanto, se
	voce esta na lista de acesso, o %S nao ira dar auto-kill
	em voce de acordo com os ajustes da opcao KILL.

NICK_HELP_SET_PRIVATE
	Sintaxe: SET PRIVATE {ON | OFF}
	
	Torna a opcao de privacidade do %S sobre o seu nick
	em ativada (ON) ou desativada (OFF).  Com PRIVATE acionado,
	seu nick nao aparecera nas listagens de nicks geradas com
	o comando %S LIST.  (Entretando, alguem que sabe do seu
	nick ainda pode obter informacoes usando o comando INFO).

NICK_HELP_SET_HIDE
	Sintaxe: SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	
	Permite que voce previna que certas informacoes sejam
	mostradas quando alguem da INFO no seu nick.  Voce pode
	esconder seu endereco de e-mail (EMAIL), utima mascara vista
	ident@host (USERMASK), e sua ultima mensagem de saida
	(QUIT).  O segundo parametro especifica quando a informacao
	deve ser mostrada (OFF) ou escondida (ON).

NICK_HELP_UNSET
	Sintaxe: UNSET {URL | EMAIL}
	
	Permite voce apagar a URL ou o E-mail associados ao seu
	nickname. Use o parametro URL para apagar o URL, ou o
	parametro EMAIL para apagar o E-mail. Voce nao pode
	apagar os dois ao mesmo tempo.

NICK_HELP_UNSET_REQ_EMAIL
	Sintaxe: UNSET URL
	
	Permite voce apagar a URL associada ao seu nickname.
	O parametro URL deve ser fornecido.

NICK_HELP_RECOVER
	Sintaxe: RECOVER nick [senha]
	
	Permite que voce recupere seu nick se alguem o tiver tomado;
	isso faz o mesmo que o %S faz automaticamente se
	alguem "rouba" um nick protegido com kill.
	
	Quando voce usa este comando, o %S trara um falso
	usuario online com o mesmo nick de quem o esta usando.
	Isto causara uma desconexao pelo servidor de IRC do outro
	usuario.  O falso usuario ficara online por 1 minuto para
	assegurar que o outro usuario nao reconecte imediatamente;
	Durante deste minuto, voce pode reivindicar seu nick.
	Alternativamente, use o comando RELEASE (/msg %S HELP
	RELEASE) para retomar seu nick mais rapidamente.
	
	Para usar o comando RECOVER para um nick, seu endereco atual
	como mostrado com /WHOIS deve estar na lista de acesso do
	nick, ou voce deve fornecer a senha correta para o nick.
	
NICK_HELP_RELEASE
	Sintaxe: RELEASE nick [senha]
	
	Instrui o %S a remover qualquer espera no seu nick
	causada pelo kill automatico de protecao ou pelo uso do
	comando RECOVER.  Por padrao, essas esperas duram 1 minuto;
	este comando libera o seu nick mais cedo.
	
	Para usar o comando RELEASE para um nick, seu endereco atual
	como mostrado com /WHOIS deve estar na lista de acesso do
	nick, ou voce deve fornecer a senha correta para o nick.

NICK_HELP_GHOST
	Sintaxe: GHOST nick [senha]
	
	Elimina uma sessao "fantasma" de IRC que esteja usando seu
	nick.  A sessao "fantasma" eh aquela que nao esta realmente
	conectada, mas que o servidor de IRC acredita estar ainda
	ativa por qualquer razao.  Isso acontece normalmente se seu
	computador travar ou se sua conexao Internet ou modem cair
	por um periodo curto de tempo enquanto voce esta no IRC.
	
	Para usar o comando GHOST em um nick, seu endereco atual
	como mostrado no /WHOIS deve pertencer a lista de acesso do
	nick, ou voce deve fornecer a senha correta para o nick.

NICK_HELP_INFO
	Sintaxe: INFO nickname [ALL]
	
	Mostra a informacao sobre o nick dado, como, o dono do nick,
	ultimo endereco utilizado, tempo e opcoes.  Se voce esta   
	identificado para o nick que voce esta obtendo informacoes 
	e a opcao ALL eh especificada, sera mostrado a voce toda
	informacao possivel; havendo opcoes para esconder 
	informacoes ou nao.
	
NICK_HELP_LISTCHANS
	Sintaxe: LISTCHANS
	
	Lista os nomes o numero total de canais que voce tem
	registrado pelo seu nickname.

NICK_HELP_LIST
	Sintaxe: LIST padrao
	
	Lista todos os nicks registrados que combinam com o padrao
	fornecido no formato nick!ident@host.  Nicks com a opcao
	PRIVATE ligada nao serao mostrados.
	
	Exemplos:
	
	    LIST *!mauritz@mauritz.americasnet.com.br
	        Lista todos os nicks de mauritz@mauritz.americasnet.com.br.
	
	    LIST *Bot*!*@*
	        Lista todos os nicks registrados com Bot em seus nomes.
	        	
	    LIST *!*@*.americasnet.com.br
	        Lista todos os nicks do dominio americasnet.com.br.
	
NICK_HELP_STATUS
	Sintaxe: STATUS nick
	
	Retorna se o usuario que esta usando um determinado nick e
	eh reconhecio como dono do nick.  A resposta tem este
	formato:
	
	    nickname codigo-de-status
	
	onde nick eh o nick enviado com o comando, e
	codigo-de-status eh um dos seguintes:
	
	    0 - usuario nao esta conectado ou o nick nao esta registrado
	    1 - usuario nao reconhecido como dono do nick
	    2 - usuario reconhecido como dono soh pela lista de acesso
	    3 - usuario reconhecido como dono via identificacao por senha
	
	Ate dezesseis nicks podem ser enviados com cada comando; o
	resto sera ignorado.  Nao eh gerado mensagem de erro se nenhum
	nick for fornecido.

NICK_SERVADMIN_HELP
	
	Os comandos abaixo estao disponiveis aos Administradores dos
	Services:
	
	    GETPASS    Recupera a senha de um nick
	                   (se a encriptacao esta desativada)
	    FORBID     Previne um nick de ser usado
	
	Administradores dos Services podem tambem cancelar registro
	de qualquer nick sem a necessidade de identificacao e podem
	ver a lista de acesso de qualquer nick
	(/msg %S ACCESS LIST nick).

NICK_SERVADMIN_HELP_DROP
	Sintaxe: DROP [nick]
	
	Sem parametros, cancela o registro seu nick do banco de
	dados do %S.
	
	Com parametros, cancela o registro de um nick especificado
	do banco de dados.
	Este comando eh restrito aos Administradores dos Services.

NICK_SERVADMIN_HELP_SET
	
	Administradores dos Services podem ajustar a opcao NOEXPIRE,
	com a qual os nicks podem ser protegidos de expirar.
	E ainda, Administradores dos Services podem ajustar opcoes
	para qualquer nick sem se identificar com a senha, usando o
	SET nick opcao parametros.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxe: SET [nick] NOEXPIRE {ON | OFF}
	
	Determina se um nick fornecido podera ser expirado.
	Ajustando este para ON, evita que o nick seja expirado.
	
	Limitado aos Administradores dos Services.

NICK_SERVADMIN_HELP_UNSET
	
	Services admins podem usar o comando UNSET em qualquer
	nickname apenas incluindo o nickname antes do nome da opcao,
	como no comando SET.

NICK_SERVADMIN_HELP_UNLINK
	
	Os Administradores dos Services podem desfazer uma ligacao sem
	precisar da senha.

NICK_SERVADMIN_HELP_LISTLINKS
	Sintaxe: LISTLINKS nick [ALL]
	
	Lista os nicks ligados a um determinado nick. Se ALL eh
	fornecido, lista todos os nicks com os mesmos privilegios de
	um determinado nick; caso contrario, lista apenas os nicks
	que estao ligados ao nick especificado.
	
	Limitado aos Administradores dos Services.

NICK_SERVADMIN_HELP_ACCESS
	
	Services admins podem fornecer um parametro nickname no
	comando LIST para mostrar a lista de acesso de qualquer
	nickname.

NICK_SERVADMIN_HELP_INFO
	
	Administradores de Services podem usar o comando ALL com qualquer nick

NICK_SERVADMIN_HELP_LISTCHANS
	
	Services admins podem listar canais de qualquer nickname
	fornecendo o nickname com o comando (por exemplo,,
	/msg NickServ LISTCHANS OutroNick).

NICK_SERVADMIN_HELP_LIST
	Sintaxe: LIST padrao [FORBIDDEN] [NOEXPIRE]
	
	Lista todos os nicks registrados que combinem com o padrao
	fornecido (formato nick!user@host). Nicks com opcao PRIVATE
	serao somente exibidos para os Administradores dos Services.
	Nicks com opcao NOEXPIRE ajustada terao um ! preposto ao nick
	na lista quando for a pedido de Administrador dos Services.
	Se as opcoes FORBIDDEN ou NOEXPIRE forem fornecidas, somente os
	nicks probidos (forbidden) ou os que tem a flag NOEXPIRE serao
	exibidos, respectivamente. Se ambas as opcoes sao fornecidas,
	ambos os tipos de nicks serao exibidos.
	
	Essas opcoes sao limitadas aos Administradores dos Services.
	
	Exemplos:
	
	     LIST *!mauritz@mauritz.americasnet.com.br
	        Lista todos os nicks de mauritz@mauritz.americasnet.com.br.
	
	     LIST *Bot*!*@*
	        Lista todos os nicks registrados com Bot em seus nomes.
	
	     LIST * NOEXPIRE
	        Lista todos os nicks registrados cujos registros foram
	        ajustados para nao expirar.
	
NICK_SERVADMIN_HELP_GETPASS
	Sintaxe: GETPASS nick
	
	Mostra a senha de um nick especificado.
	Note que sempre que este comando for usado, uma mensagem
	incluindo o nick da pessoa que emitiu o comando o nick
	requisitado sera gravado e enviado para WALLOPS/GLOBOPS.
	
	Limitado aos Administradores dos Services.
	
	Este comando nao eh disponivel quando a encriptacao esta habilitada.

NICK_SERVADMIN_HELP_FORBID
	Sintaxe: FORBID nick
	
	Nao permite que um nick seja registrado ou usado por
	ninguem.  Pode ser cancelado desregistrando o nick.
	
	Limitado aos Administradores dos Services.

NICK_SERVADMIN_HELP_SUSPEND
	Sintaxe: SUSPEND [+expiracao] nickname razao
	
	Evita que um nickname, e todos aqueles nicknames com
	mesmo root nickname, seja usado ou identificado. Um
	Nickname pode ser reabilitado com o comando UNSUSPEND
	
	Ao contrario de um nickname com forbidden, um suspenso ?????
	nao perde suas informacoes e ira expirar!
	
	Limitado a Services admins.

NICK_SERVADMIN_HELP_UNSUSPEND
	Sintaxe: UNSUSPEND nickname
	
	Permite pessoas usarem e identificarem um nickname
	anteriormente suspenso.
	
	Limitado a Services admins.

###########################################################################
#
# Mensagens de help do ChanServ
#
###########################################################################

CHAN_HELP
	%S permite que voce registre e controle varios
	aspectos do canal. %S pode prevenir o "take over"
	do canal de usuarios maliciosos, limitando quem possui
	o privilegio de OP do canal. Os comandos disponiveis
	estao listados abaixo; Para usa-los, digite
	/msg %S comando. Para mais informacoes sobre
	um comando, digite /msg %S HELP comando.
	
	    REGISTER   Registra um canal
	    IDENTIFY   Identifica voce com uma senha
	    DROP       Cancela o registro de um canal
	    INFO       Mostra as opcoes e informacoes de um canal
	    SET        Ajusta as opcoes e informacoes de um canal
	    ACCESS     Mantem a lista de usuarios privilegiados
	    SOP        Mantem a lista de SuperOp
	    AOP        Mantem a lista de AutoOp
	    VOP        Mantem a lista de AutoVoice
	    AKICK      Mantem a lista de AutoKick
	
CHAN_HELP_OTHERS
	
	Outros comandos: UNSET, LIST, INVITE, UNBAN, CLEAR,
	                 LEVELS, OP, DEOP, VOICE, DEVOICE

CHAN_HELP_OTHERS_HALFOP_CHANPROT
	
	Outros comandos: UNSET, LIST, INVITE, UNBAN, CLEAR,
	                 LEVELS, OP, DEOP, VOICE, DEVOICE,
	                 HALFOP, DEHALFOP, PROTECT, DEPROTECT,
	                 HOP

CHAN_HELP_EXPIRES
	
	Note que qualquer canal nao utilizado por %d dias
	(entenda como se nenhum usuario da lista de acesso
	desse canal entrar neste periodo de tempo) tera
	automaticamente cancelado o seu registro.

CHAN_HELP_REGISTER
	Sintaxe: REGISTER canal senha descricao
	
	Registra um canal no banco de dados do %S.  Para
	utilizar este comando, voce deve primeiro ser OP do
	canal que esta tentando registrar.  A senha eh usada
	com o comando IDENTIFY e permitira que voce faca
	mudancas nas opcoes do canal futuramente.  O ultimo
	parametro que deve ser incluido, eh uma breve
	descricao do proposito do canal.
	
	Quando voce registra um canal, voce sera registrado
	como o "fundador" do canal.  O fundador do canal tem
	permissao para mudar todas as opcoes do canal; o %S
	tambem ira dar ao fundador automaticamente o privilegio
	de OP do canal quando ele/ela entra no canal.  Veja o
	comando ACCESS (/msg %S HELP ACCESS) para
	informacoes dos subconjuntos destes privilegios para
	outros usuarios do canal.
	
	IMPORTANTE:  Para registrar um canal, voce deve antes ter
	registrado seu nick.  Se ainda nao, digite /msg %s HELP
	para mais informacoes de como faze-lo.

CHAN_HELP_IDENTIFY
	Sintaxe: IDENTIFY canal senha
	
	Identifica voce no %S como fundador do canal fornecido.
	Muitos comandos exigem que voce use este comando antes
	de usa-los.  A senha devera ser a mesma usada por voce
	no comando REGISTER.

CHAN_HELP_DROP
	Sintaxe: DROP #canal
	
	Cancela o registro do canal.  So poder ser usado pelo
	fundador do canal, que primeiramente devera usar o
	comando IDENTIFY.

CHAN_HELP_SET
	Sintaxe: SET canal opcao parametros
	
	Permite ao fundador do canal ajustar as varias opcoes do
	canal e outras informacoes.  O fundador deve utilizar o
	comando IDENTIFY antes de usar o SET.
	
	Comandos disponiveis:
	
	    FOUNDER     Ajusta o fundador do canal
	    SUCCESSOR   Ajusta o sucessor do canal
	    PASSWORD    Ajusta a senha do fundador
	    DESC        Ajusta a descricao do canal
	    URL         Associa uma URL a um canal
	    EMAIL       Associa um e-mail a um canal
	    ENTRYMSG    Ajusta a mensagem que deve ser mandada
	                   aos usuarios quando eles entram no canal
	    TOPIC       Altera o topico do canal
	    KEEPTOPIC   Mantem o topico quando o canal nao esta em uso
	    TOPICLOCK   O topico pode ser mudado apenas com SET TOPIC
	    MLOCK       Liga ou desliga a trava dos modos do canal
	    PRIVATE     Esconde o canal do comando LIST
	    RESTRICTED  Acesso restrito ao canal
	    SECURE      Ativa os recursos de seguranca do %S
	    SECUREOPS   Rigoroso o controle de status de OP
	    LEAVEOPS    Nao tirar op de usuarios ao entrarem no canal
	    OPNOTICE    Envia uma notice quando os comandos OP/DEOP
	                   sao usados
	    ENFORCE     Forca status de auto-op, auto-voice
	
	Digite /msg %S HELP SET opcoes para maiores informacoes
	sobre uma opcao em particular.

CHAN_HELP_SET_FOUNDER
	Sintaxe: SET canal FOUNDER nick
	
	Muda o fundador do canal.  O novo nick deve estar
	registrado.
	
CHAN_HELP_SET_SUCCESSOR
	Sintaxe: SET canal SUCCESSOR nick
	
	Muda o sucessor de um canal. Se o nick do founder expirar
	ou estiver dropado enquanto o canal ainda estiver registrado,
	o sucessor se tornara o novo founder do canal.
	No entanto, se o sucessor possuir muitos canais registrados
	(%d), o canal sera dropado, como se nenhum sucessor tivesse
	sido ajustado. O novo nick devera estar registrado.

CHAN_HELP_SET_PASSWORD
	Sintaxe: SET canal PASSWORD senha
	
	Ajusta a senha utilizada para identificacao do
	fundador do canal.
	
CHAN_HELP_SET_DESC
	Sintaxe: SET canal DESC descricao
	
	Ajusta a descricao para o canal, que sao mostradas com
	os comandos LIST e INFO.

CHAN_HELP_SET_URL
	Sintaxe: SET canal URL url
	 
	Associa a URL dada ao canal. Esta URL sera mostrada
	sempre que alguem solicitar informacao sobre o canal
	com o comando INFO.

CHAN_HELP_SET_EMAIL
	Sintaxe: SET canal EMAIL endereco
	 
	Associa o endereco de e-mail fornecido ao canal.
	Este endereco sera mostrado sempre que alguem solicitar
	informacao sobre o canal com o comando INFO.

CHAN_HELP_SET_ENTRYMSG
	Sintaxe: SET canal ENTRYMSG mensagem
	 
	Ajusta a mensagem a qual sera enviada via /notice para
	os usuarios quando eles entrarem no canal.

CHAN_HELP_SET_TOPIC
	Sintaxe: SET canal TOPIC topico
	
	Faz o %S mudar o topico do canal pelo topico dado.
	Este comando eh muito mais util em conjunto com o
	SET TOPICLOCK.

CHAN_HELP_SET_KEEPTOPIC
	Sintaxe: SET canal KEEPTOPIC {ON | OFF}
	
	Ativa ou desativa a opcao de retencao de topico para
	um canal.  Quando a retencao de topico esta acionada,
	o topico para o canal sera relembrado pelo %S mesmo
	depois que os usuarios deixarem o canal, e sera
	restaurado na proxima vez que o canal for re-aberto.

CHAN_HELP_SET_TOPICLOCK
	Sintaxe: SET canal TOPICLOCK {ON | OFF}
	
	Ativa ou desativa a opcao de trava do topico de um canal.
	Quando a Trava do topico esta ativada, o %S nao permitira
	a mudanca do topico do canal exceto pelo comando SET TOPIC.
	

CHAN_HELP_SET_MLOCK
	Sintaxe: SET canal MLOCK modos
	
	Ajusta o parametro da trava do modo para um canal.  O %S
	permite que voce defina certos modos no canal a serem
	sempre ativos (ou desativos).  Os modos podem ser
	i, k, l, m, n, p, s e t; cada um desses
	travado como ativo, desativo ou nao travado.  O parametro
	modos e usado exatamente do mesmo modo como o comando
	/MODE;  isto eh, modos seguidos de + sao travados como
	ativos, e modos seguidos de - sao travados como desativos.
	
	Cuidado: Se voce trava uma senha, como no segundo exemplo
	abaixo, voce deveria tambem ajustar a opcao RESTRICTED para
	o canal (veja HELP SET RESTRICTED), ou qualquer usuario
	que entra no canal que esta vazio sera capaz de ver a senha!
	
	Exemplos:
	
	    SET #canal MLOCK +nt-iklps
	        Trava os modos n e t ativados, e os modos i, k, l, p,
	        e s desligados.  Modo m eh livremente deixado para se
	        ligado(on)ou desligado(off).
	
	    SET #canal MLOCK +knst-ilmp minha-senha
	        Trava os modos k, n, s, t como ligados e os modos i,
	        l, m, p como desligados.  Tambem trava a senha do
	        canal como "minha-senha".
	
	    SET #canal MLOCK +
	        Elimina a trava do modos; todos os modos do canal
	        ficam livres para ser ativados ou desativados.

CHAN_HELP_SET_PRIVATE
	Sintaxe: SET canal PRIVATE {ON | OFF}
	
	Ativa ou desativa a opcao private para um canal.  Quando
	private esta ativada, um /msg %S LIST nao ira incluir
	o canal em qualquer listagem.
	
CHAN_HELP_SET_RESTRICTED
	Sintaxe: SET canal RESTRICTED {ON | OFF}
	
	Ativa ou desativa a opcao de acesso restrito para um canal.
	Quando o acesso restrito estiver ativado, usuarios que
	normalmente nao possuem privilegios de OP no canal
	(usuarios com nivel negativo de acesso e, se secure ops
	estiver ativado, usuarios que nao pertence a lista de
	acesso) serao imediatamente kickados e banidos do canal.
	
CHAN_HELP_SET_SECURE
	Sintaxe: SET canal SECURE {ON | OFF}
	
	Ativa ou desativa os recursos de seguranca do %S para
	um canal.  Quando o SECURE estiver ativo, somente
	usuarios que possuirem seus nicks registrados no %s
	e identificados com sua senha poderao entrar no canal
	controlado pela lista de acesso.
	
CHAN_HELP_SET_SECUREOPS
	Sintaxe: SET canal SECUREOPS {ON | OFF}
	
	Ativa ou desativa a opcao de seguranca de ops para um canal.
	Quando secure-ops estiver ativada, os usuarios que nao
	estiverem na lista de acesso nao poderao ter o status de
	OP.

CHAN_HELP_SET_LEAVEOPS
	Sintaxe: SET canal LEAVEOPS {ON | OFF}
	
	Ativa ou desativa a opcao leave ops para um canal.
	Quando leave ops estiver ligado, %S deixara com op
	o usuario que entrar primeiro no canal mesmo se o
	usuario nao deveria receber op normalmente.
	A opcao SECUREOPS e o nivel de acesso de AUTODEOP
	continuarao sendo reforcados.
	Observacao: Isso pode permitir usuarios "roubarem" ops
	durante um netsplit.

CHAN_HELP_SET_OPNOTICE
	Sintaxe: SET canal OPNOTICE {ON | OFF}
	
	Ativa e desativa a opcao Op-Notice para um canal. Quando
	Op-Notice estiver ativado, o %S enviara uma notice para
	o canal sempre que os comandos OP ou DEOP forem usados em
	um usuario no canal.

CHAN_HELP_SET_ENFORCE
	Sintaxe: SET canal ENFORCE {ON | OFF}
	
	Ativa ou desativa a op$Bgc(Bo de enforce para um canal.
	Quando a op$Bgc(Bo de enforce está ligada, %S forcara o nivel
	de auto-op e auto-voice para todos os usuarios. Por Exemplo,
	se um usuario com privilegio de auto-op for deopado, %S ira
	automaticamente da-lo op novamente, e %S nao ira permitir
	que o comando DEOP seja usado nesse usuario.

CHAN_HELP_UNSET
	Sintaxe: UNSET canal {SUCCESSOR | URL | EMAIL | ENTRYMSG}
	
	Apaga do canal a opcao fornecida.

CHAN_HELP_SOP
	Sintaxe: SOP canal ADD nick
	         SOP canal DEL nick
	         SOP canal LIST [mascara | lista]
	         SOP canal COUNT
	
CHAN_HELP_SOP_NOPROT
	Mantem a lista de SuperOp (SOP) de um canal. Usuarios
	com o status de SOP recebem automaticamente op (modo
	+o) ao entrarem no canal.
CHAN_HELP_SOP_PROT
	Faz manutencao da lista de SuperOp (SOP) de um canal.
	Usuários com estatus de SOP recebem automaticamente op
	(modo +o) e protegido (modo +a) quando entram no canal.
CHAN_HELP_SOP_END
	
	Um SOP pode modificar as listas de AOP e VOP.
	Apenas o fundador do canal pode modificar a lista de SOP.
	
	O comando SOP LIST mostra a lista de SOP. Se uma mascara
	for dada, apenas as entradas que combinarem com a mascara
	serao mostradas. Se uma lista de numeros for dada, apenas tais
	entradas serao mostradas; por exemplo:
	
	   SOP #canal LIST 2-5,7-9
	      Mostra as entradas da lista de SOP numeradas de 2 a 5 e
	      de 7 a 9.
	
	O comando SOP COUNT retorna o numero de entradas que existem
	na lista de SOP.

CHAN_HELP_AOP
	Sintaxe: AOP canal ADD nick
	         AOP canal DEL nick
	         AOP canal LIST [mascara | lista]
	         AOP canal COUNT
	
	Mantem a lista de AutoOp (AOP) de um canal. Usuarios
	com o status de AOP recebem automaticamente op (modo
	+o) ao entrarem no canal.
	
	Um AOP pode modificar a lista VOP.
	
	O comando AOP LIST mostra a lista de AOP. Se uma mascara
	for dada, apenas as entradas que combinarem com a mascara
	serao mostradas. Se uma lista de numeros for dada, apenas tais
	entradas serao mostradas; por exemplo:
	
	   AOP #canal LIST 2-5,7-9
	      Mostra as entradas da lista de AOP numeradas de 2 a 5 e
	      de 7 a 9.
	
	O comando AOP COUNT retorna o numero de entradas que existem
	na lista de AOP.

CHAN_HELP_HOP
	Sintaxe: HOP canal ADD nick
	         HOP canal DEL nick
	         HOP canal LIST [mascara | lista]
	         HOP canal COUNT
	
	Faz manunten$Bgc(Bo da lista de HalfOp (HOP) de um canal.
	Usuarios com status de HOP recebem automaticamente halfop
	(modo +h) quando entram no canal.
	
	Um HOP pode modificar a lista de VOP; SOPs e AOPs podem
	modificar a lista de HOP.
	
	O comando HOP LIST mostra a lista de HOP.  Se uma mascara
	wildcard eh dada, apenas as entradas que combinam com a
	mascara sao mostradas.  Se uma lista de numeros de entradas
	eh dada, apenas tais entradas sao mostradas; por exemplo:
	
	   HOP #canal LIST 2-5,7-9
	      Mostra as entradas da lista de HOP numeradas de 2 a 5
	      e de 7 a 9
	
	O comando HOP COUNT retorna o numero de entradas que existem
	na lista de HOP.

CHAN_HELP_VOP
	Sintaxe: VOP canal ADD nick
	         VOP canal DEL nick
	         VOP canal LIST [mascara | lista]
	         VOP canal COUNT
	
	Mantem a lista de VoiceOp (VOP) de um canal. Usuarios
	com o status de VOP recebem automaticamente voice
	(modo +v) ao entrarem no canal.
	
	O comando VOP LIST mostra a lista de VOP. Se uma mascara
	for dada, apenas as entradas que combinarem com a mascara
	serao mostradas. Se uma lista de numeros for dada, apenas tais
	entradas serao mostradas; por exemplo:
	
	   VOP #canal LIST 2-5,7-9
	      Mostra as entradas da lista de VOP numeradas de 2 a 5 e
	      de 7 a 9.
	
	O comando VOP COUNT retorna o numero de entradas que existem
	na lista de VOP.

CHAN_HELP_ACCESS
	Sintaxe: ACCESS canal ADD nick nivel
	         ACCESS canal DEL {nick | entry-num | list}
	         ACCESS canal LIST [mascara | list]
	
	Faz manutencao da lista de acesso de um canal.  A lista
	de acesso especifica que usuarios tem permissao para
	0 status de OP ou tem acesso aos comandos do %S em um
	canal.  Niveis diferentes de usuarios permitem acesso a
	diferentes subniveis de privilegios; /msg %S HELP ACCESS
	LEVELS para mais informacoes especificas.  Por padrao,
	qualquer nick nao presente na lista de acesso possui
	nivel 0.
	
	O comando ACCESS ADD adiciona um nick ou mascara de um
	usuario na lista de acesso com o nivel especificado; se o
	nick ou mascara ja estiver presente na lista, seu nivel
	de acesso sera alterado para o nivel especificado.
	O nivel especificado deve ser menor do que o usuario
	que emitiu o comando.
	
	O comando ACCESS DEL remove um nick especificado da lista
	de acesso. Se uma lista de numeros eh fornecida, essas
	entradas sao apagadas. (Veja o exemplo para LIST abaixo.)
	
	O comando ACCESS LIST mostra a lista de acesso do canal. Se
	uma mascara for fornecida, somente aquelas entradas que combinarem
	com o padrao especificado na mascara serao mostradas. Se uma
	lista de numeros eh fornecida, somente essas entradas serao
	mostradas; por exemplo:
	
	ACCESS #canal LIST 2-5,7-9
	   Lista as entradas de acesso numeradas de 2 a 5 e 7 a 9.

CHAN_HELP_ACCESS_LEVELS
	Niveis de Acesso do Usuario
	
	Por padrao, os seguintes niveis de acesso sao definidos:
	
	   Founder   Acesso total as funcoes do %S; OP automatico
	                     quando entrar no canal.  Note que de
	                     somente uma pessoa pode ter o status
	                     fundador (isto nao pode ser dado usando
	                     o comando ACCESS).
	        10   Acesso ao comando AKICK; OP automatico.
	         5   OP automatico.
	         3   Voice automatico.
	         0   Sem privilegios especiais; pode se tornar OP
	                     atraves de outros ops (a menos que
	                     secure-ops esteja ativada).
	        <0   Nao pode ser OP.
	
	Esses niveis podem ser mudados, ou adiconar novos, usando o
	comando LEVELS; digite /msg %S HELP LEVELS para informacoes.
	
CHAN_HELP_AKICK
	Sintaxe: AKICK canal ADD mascara [razao]
	         AKICK canal DEL mascara
	         AKICK canal LIST [mascara]	
	         AKICK canal ENFORCE
	
	Faz a manutencao da lista de Autokick de um canal.
	Se um usuario que estiver na lista de AutoKick tentar
	entrar no canal, o %S banira este usuario do canal,
	e depois kickara o usuario.
	
	O comando AKICK ADD adiciona o usuario especificado ou
	mascara na lista de Autokick.  Se uma razao eh dada com
	o comando, esta razao sera usada quando o usuario for
	kickado; senao, a razao padrao sera "Voce foi banido deste
	canal".
	
	O comando AKICK DEL remove um nick ou mascara da lista
	de AutoKick.  Isso, entretanto, nao remove qualquer ban
	colocado pelo AutoKick; estes devem ser removidos
	manualmente.
	
	O comando AKICK LIST mostra a lista de AutoKick, ou
	opcionalmente, soh os registros de AutoKick quem se
	encaixam com o padrao de uma mascara dada.
	
	O comando AKICK ENFORCE obriga o %S a verificar
	a lista de AKICKs para remover os usuarios conectados que
	sejam compativeis com a mascara dada.

CHAN_HELP_LEVELS
	Sintaxe: LEVELS canal SET tipo nivel
	         LEVELS canal {DIS | DISABLE} tipo
	         LEVELS canal LIST
	         LEVELS canal RESET
	
	O comando LEVELS permite ajuste detalhado sobre o
	significado numerico dos niveis de acesso usados pelos
	canais.  Com esse comando, voce pode definir o nivel de
	acesso requerido pela maioria das funcoes do %S.
	(Os comandos SET FOUNDER e SET PASSWORD, assim como este
	comando, sao sempre restritos ao fundador do canal).
	
	LEVELS SET permite que o nivel de acesso para uma funcao ou
	grupo de funcoes sejam alterados.  LEVELS DISABLE (ou DIS
	para encurtar) desabilita automaticamente os dispositivos ou
	nao permite o acesso a funcoes para qualquer outra pessoa
	que nao seja o fundador do canal.  LEVELS LIST mostra os
	niveis atuais para cada funcao ou para um grupo de funcoes.
	LEVELS RESET recoloca os niveis de acordo com o padrao de um
	canal recem-criado (veja HELP ACCESS LEVELS).
	
	Para lista de recursos e funcoes cujo niveis podem ser
	ajustados, veja HELP LEVELS DESC.

CHAN_HELP_LEVELS_DESC
	A seguinte caracteristica/funcao sao entendidas.  Note que
	estes niveis para AUTODEOP e NOJOIN sao os niveis maximos,
	enquanto que todos os outros sao niveis minimos.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Sintaxe: INFO canal [ALL]
	
	Lista os dados referentes ao canal registrado dado, incluindo
	seu fundador, data do registro, ultima vez que foi usado,
	descricao, e trava dos modos (se existirem). Se voce esta 
	identificado como fundador do canal que esta solicitando
	informacoes e a opcao ALL eh especificada, informacoes 
	sobre a mensagem de entrada e sobre o sucessor do canal
	 tambem sera mostrada.

CHAN_HELP_LIST
	Sintaxe: LIST padrao
	
	Lista todos os canais registrados que combinam com o padrao
	dado.  (Canais com opcao PRIVATE ativada nao serao listados).

CHAN_HELP_OP
	Sintaxe: OP #canal nick
	
	Atribui status de Operador (modo +o) para o nick dado em
	um determinado canal.  Limitado aos usuarios de nivel 5,
	no minino, do canal especificado.

CHAN_HELP_DEOP
	Sintaxe: DEOP #canal nick
	
	Remove o status de Operador (modo +o) do nick dado para
	um determinado canal. Limitado aos usuarios de nivel 5,
	no minino, do canal especificado.

CHAN_HELP_VOICE
	Sintaxe: VOICE #canal nick
	
	Dah voice (modo +v) a um nick em um canal. Por padrão,
	limitado aqueles com nivel de acesso 3 ou mais no canal.

CHAN_HELP_DEVOICE
	Sintaxe: DEVOICE #canal nick
	
	Tira voice (modo -v) de um nick em um canal. Por padrão,
	limitado aqueles com nivel de acesso 3 ou mais no canal.

CHAN_HELP_HALFOP
	Sintaxe: HALFOP #canal nick
	
	Dah acesso de halfop (modo +h) a um nick em um canal. Por
	padrão, limitado aqueles com nivel de acesso 4 ou mais no
	canal.

CHAN_HELP_DEHALFOP
	Sintaxe: DEHALFOP #canal nick
	
	Tira acesso de halfop (modo -h) de um nick em um canal. Por
	padrão, limitado aqueles com nivel de acesso 4 ou mais no
	canal.

CHAN_HELP_PROTECT
	Sintaxe: PROTECT #canal nick
	
	Dá protecao de canal (modo +a) para um nick selecionado em um
	canal.  Por padrão, limitado aqueles com nivel de acesso igual
	ou superior a 10 no canal.

CHAN_HELP_DEPROTECT
	Sintaxe: DEPROTECT #canal nick
	
	Remove a protecao de canal (modo +a) de um nick selecionado em
	um canal.  Por padrão, limitado aqueles com nivel de acesso igual
	ou superior a 10 no canal.
	
CHAN_HELP_INVITE
	Sintaxe: INVITE #canal
	
	Manda o %S dar um invite em voce para o canal dado.
	Somente funcionara se seu nivel de acesso for pelo menos
	igual a 5.

CHAN_HELP_UNBAN
	Sintaxe: UNBAN #canal
	
	Diz ao %S para remover todos os bans permitindo que
	voce entre em um canal.  Por padrao, somente funciona
	se seu nivel de acesso no canal for pelo menos igual a 5.

CHAN_HELP_CLEAR
	Sintaxe: CLEAR canal opcao
	
	Diz ao %S para remover certas colocacoes de um canal.
	A opcap pode ser uma das seguintes:
	
	     MODES       Anula todos os modos do canal (isto eh, remove
	                     os modos i,k,l,m,n,p,s,t).
CHAN_HELP_CLEAR_EXCEPTIONS
	     EXCEPTIONS  Remove todas as excecoes de um canal.
CHAN_HELP_CLEAR_MID
	     BANS        Remove todos os bans do canal.
	     OPS         Remove o status de Operador do canal (mode +o)
	                     de todos os Operadores do canal.
CHAN_HELP_CLEAR_HALFOPS
	     HALFOPS     Remove o status de halfop (mode +h) de todos os usuarios.
CHAN_HELP_CLEAR_END
	     VOICES      Remove o status "voice" (mode +v) de qualquer
	                     pessoa que tenha esse modo.
	     USERS       Remove (kicka) todos os usuarios do canal.
	
	Por padrao, seu nivel de acesso no canal dever ser no
	minimo 10 para usar este comando.

CHAN_SERVADMIN_HELP
	
	Os seguintes comandos estao disponiveis para
	os Administradores dos Services:
	
	    GETPASS    Recupera a senha de fundador de um canal
	                   (somente se a encriptacao esta desativada)
	    FORBID     Proibe um canal de ser usado
	    SUSPEND    Proibe um canal registrado de ser usado
	    STATUS     Fornece o atual nivel de acesso de um
	                   usuario em um canal
	
	Administradores do Services podem tambem cancelar o registro sem
	a necessidade de identificacao atraves da senha, podem ver os
	acessos, AKICK, e ajuste da lista de niveis de qualquer canal.

CHAN_SERVADMIN_HELP_DROP
	Sintaxe: DROP canal
	
	Cancela o registro de um canal.  Somente Administradores dos
	Services podem cancelar canais para os quais eles nao tenham
	sido identificados.

CHAN_SERVADMIN_HELP_SET
	
	Administradores dos Services tambem pode ajustar a opcao
	NOEXPIRE, fazendo com canais sejam impedidos de ter seu
	registro expirado.  Administradores dos Services ainda podem
	ajustar opcoes para qualquer canal sem precisar da identificacao
	do canal atraves da senha.

CHAN_SERVADMIN_HELP_UNSET
	
	Como no comando SET, Services admins pode apagar configuracoes
	de qualquer canal sem estar identificado para o mesmo.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxe: SET canal NOEXPIRE {ON | OFF}
	
	Determina se o canal podera ter seu registro expirado.
	Ajustando para ON, evita que o canal seja desregistrado
	por passar do tempo de expiracao.
	
	Limitado aos Administradores dos Services.

CHAN_SERVADMIN_HELP_INFO
	
	Administradores de Services podem usar o comando ALL com qualquer canal.

CHAN_SERVADMIN_HELP_LIST
	Sintaxe: LIST padrao
	
	Lista todos os canais registrados que combinam com o
	padrao fornecido.  Canais com opcao PRIVATE ativada
	soh serao mostrados aos Administradores dos Services.

CHAN_SERVADMIN_HELP_GETPASS
	Sintaxe: GETPASS canal
	
	Retorna a senha de um canal. Note que toda vez que esse
	este comando for usado, uma mensagem incluindo o nick da
	pessoa que emitiu o comando e o canal que foi dado serao
	gravados e enviados para WALLOPS/GLOBOPS.
	
	Limitado aos Administradores dos Services.

CHAN_SERVADMIN_HELP_FORBID
	Sintaxe: FORBID canal
	
	Proibe que qualquer pessoa registre e utilize o canal
	dado.  Pode ser cancelado pelo desregistro do canal.
	
	Limitado aos Administradores dos Services.

CHAN_SERVADMIN_HELP_SUSPEND
	Sintaxe: SUSPEND [+expiracao] canal razao
	
	Evita que um canal seja usado ou identificado. Um
	Nickname pode ser reabilitado com o comando UNSUSPEND
	
	Ao contrario de um canal com forbidden, um canal suspenso
	nao perde suas informacoes e ira expirar!
	
	Limitado a Services admins.

CHAN_SERVADMIN_HELP_UNSUSPEND
	Sintaxe: UNSUSPEND canal
	
	Permite pessoas usarem e identificarem um canal
	anteriormente suspenso.
	
	Limitado a Services admins.

CHAN_SERVADMIN_HELP_STATUS
	Retorna o nivel de acesso atual de um determinado nick em um
	determinado canal. A resposta sera no formato:
	
	    STATUS canal nick nivel-de-acesso
	
	Se um erro ocorrer, a resposta sera no formato:
	
	    STATUS ERROR mensagem-de-erro

###########################################################################
#
# Mensagens de help do MemoServ
#
###########################################################################

#MEMO_HELP
#	%S eh um utilitario que permite aos usuarios de IRC
#	enviar curtas mensagens a outros usuarios, mesmo
#	que eles estejam conectados no momento ou nao; ou
#	nos canais(*).  Ambos, destinatarios e remetentes,
#	devem possuir seu nick (ou canal) registrados para
#	que possam enviar uma mensagem (memo).
#	Os comandos do %S sao:
#	
#	    SEND   Envia uma mensagem para um nick ou para um canal
#	    LIST   Lista suas mensagens
#	    READ   Le a(s) mensagem(ns)
#	    DEL    Apaga a(s) mensagem(ns)
#	    SET    Ajusta opcoes relacionadas as mensagens
#	
#	Digite  /msg %S HELP <comando> para ajuda em qualquer um dos
#	comandos acima.
#	
#	(*) Por padrao, qualquer usuario com no minimo
#	    nivel 10 pode ler as mensagens do canal.  Isto
#	    pode ser alterado com o comando %s LEVELS.

MEMO_HELP_SEND
	Sintaxe: SEND {nick | canal} mensagem
	
	Envia um memo ao nick ou ao canal determinado contendo
	a mensagem.  Quando enviada para o destinatario, este
	recebera um aviso que possui uma nova mensagem.  O nick/
	/canal de destino devera estar registrado.

MEMO_HELP_LIST
	Sintaxe: LIST [canal] [list | NEW]
	
	Lista quaisquer mensagens que voce tiver. Com NEW, lista apenas
	as novas mensagens(nao lidas). Mesangem nao lidas sao marcadas
	com "*" a esquerda do numero. Voce tambem pode especificar uma
	lista de numeros, como no exemplo abaixo:
	
	   LIST 2-5,7-9
	     Lista mensagens numeradas de 2 a 5 e 7 a 9.

MEMO_HELP_READ
	Sintaxe: READ [canal] {num | list | LAST | NEW}
	
	Mostra as mensagens especificadas. Se LAST eh fornecido, envia
	a voce a mensagem recebida mais recentemente. Se NEW eh fornecido,
	envia a voce todas as suas novas mensagens. Caso contrario, envia
	a voce uma mensagem numerada. Voce tambem pode fornecer uma lista
	de numeros, como por exemplo:
	
	   READ 2-5,7-9
	     Mostra as mensagens numeradas de 2 a 5 e 7 a 9.

MEMO_HELP_DEL
	Sintaxe: DEL [canal] {num | list | ALL}
	
	Apaga a(s) mensagem(ns) especificada(s). Voce pode fornecer
	varios numeros de mensagens ou sequencias de numeros ao inves
	de um unico numero, como no segundo exemplo abaixo.

	Se ALL eh fornecido, apaga todas suas mensagens.
	
	Exemplos:
	
	   DEL 1
	      Apaga sua primeira mensagem.
	
	   DEL 2-5,7-9
	      Apaga mensagens numeradas de 2 a 5 e de 7 a 9.

MEMO_HELP_SET
	Sintaxe: SET opcao parametros
	
	Ajusta varias opcoes de mensagens.  opcao pode ser uma dessas:
	
	    NOTIFY      Muda quando voce for notificado sobre novas
	                    mensagens (so para nicks)
	    LIMIT       Ajusta o numero maximo de mensagens que voce
	                    pode receber.
	
	Digite /msg %S HELP SET <comando>, para mais informacoes sobre
	um comando especifico.

MEMO_HELP_SET_NOTIFY
	Sintaxe: SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Mudancas que ocorrem quando voce for notificado sobre novas
	mensagens:
	
	    ON      Voce soh sera notificado sobre mensagens quando voce
	                conectar, quando voltar de um /AWAY e quando
	                sao enviadas a voce.
	    LOGON   Voce soh sera notificado sobre mensagens quando voce
	                conectar ou quando voltar de um /AWAY.
	    NEW     Voce soh sera notificado sobre mensagens quando
	                estiverem enviando para voce.
	    OFF     Voce nao recebera nenhuma notificacao sobre mensagens.
	
	ON eh essencialmente a combinacao LOGON e NEW.

MEMO_HELP_SET_LIMIT
	Sintaxe: SET LIMIT [canal] limite
	
	Ajusta o numero maximo de mensagens que voce pode ter
	(ou do canal fornecido).  Se voce ajustar para 0, ninguem
	sera capaz de enviar mensagens para voce.  Entretanto,
	voce nao pode ajustar este limite para mais que %d.

MEMO_HELP_INFO
	Sintaxe: INFO [canal]
	
	Informa o numero de mensagens que voce tem, quantas
	mensagens nao foram lidas, e o total de quantas
	mensagens voce pode receber.
	Com o parametro, mostra a mesma informacao para o canal
	fornecido.

MEMO_SERVADMIN_HELP_SET_LIMIT
	Sintaxe: SET LIMIT [usuario | canal] {limite | NONE} [HARD]
	
	Ajusta o numero maximo de mensagens que um nick ou canal podem
	ter.  Ajustando o limite para 0, previne o usuario de receber
	qualquer mensagem; colocando o limite em NONE permite que o
	usuario receba e mantenha quantas mensagens quiser.  Se voce
	nao fornecer o nick ou canal, seu proprio limite sera ajustado.
	
	Adicionando HARD previne que o usuario mude o limite.
	Nao colocar HARD tem o efeito contrario, permitindo
	que o usuario mude o limite (mesmo se um limite anterior
	foi ajustado com HARD).
	
	O uso do comando SET LIMIT eh limitado aos Administradores
	dos Services.  Outros usuarios somente ajustarao seus
	proprios limites ou de um canal onde tenham privilegios
	para isso, nao podem remover seu proprio limite, nao
	podem ajustar o limite acima de %d, e nao podem ajustar
	um limite maximo (HARD).

MEMO_SERVADMIN_HELP_INFO
	Sintaxe: INFO [nick | canal]
	
	Sem um parametro, informa o numero de mensagens que voce
	tem, quantas mensagens ainda nao foram lidas, e o total
	de quantas mensagens voce pode receber.
	
	Com o parametro do canal, mostra a mesma informacao sobre
	um canal.
	
	Com o parametro de nick, mostra a mesma informacao sobre
	um nick.  Esta derivacao do comando eh limitada aos
	Administradores dos Services.
	

###########################################################################
#
# Mensagens de help do OperServ
#
###########################################################################

OPER_HELP
	Comandos do %S :
	    GLOBAL      Envia uma mensagem a todos os usuarios
	    STATS       Mostra o status dos Services e da rede
	    OPER LIST   Lista todos os Services operators
	    ADMIN LIST  Lista todos os Services admins
	
	Comandos disponiveis para Services operators e admins apenas:
	    MODE        Modifica os modo de um canal
	    KICK        Kicka um usuario de um canal
	    CLEARMODES  Remove certos modos de um canal
	    CLEARCHAN   Remove todos os usuarios de um canal (masskick)
	    KILLCLONES  Killa todos os usuarios que possuem um certo host
	    AKILL       Manipula a lista de AKILL
	    SESSION     Mostra a lista de conexoes por host
	    EXCEPTION   Modifica a lista de excecoes do limite de conexoes
	    LOGONNEWS   Define messagens a serem mostradas aos usuarios
	                no logon
	    OPERNEWS    Define messagens a serem mostradas aos usuarios
	                no oper
	
	Comandos disponiveis para Services admins apenas:
	    OPER        Modifica a lista de Services operator
	    JUPE        "Jupiter" um servidor
	    RAW         Envia uma raw string para o servidor de IRC
	    SET         Configura varias opcoes globais dos Services
	    UPDATE      Forca o banco de dados dos Services a serem
	                atualizados no disco imediatamente
	    SHUTDOWN    Salva o banco de dados e desliga os Services
	    QUIT        Desliga os Services sem salvar o banco de dados
	    RESTART     Salva o banco de dados e reinicia os Services
	    SU          Obtem privilegios de super-usuario de Services
	
	Comandos disponiveis para super-usuarios de Services apenas:
	    ADMIN       Modifica a lista de Services admin
	
	Nota: Todos os comandos enviados ao %S sao gravados!

OPER_HELP_GLOBAL
	Sintaxe: GLOBAL mensagem
	
	Permite os IRCops mandarem mensagens a todos os usuarios da rede.
	Esta mensagem sera enviada pelo %s.

OPER_HELP_STATS
	Sintaxe: STATS [RESET | AKILL | ALL]
	
	Sem nenhuma opcao, mostra o numero atual de usuarios e
	IRCops online (excluindo Services), o numero maximo de
	usuarios online conectados simultaneamente e o tempo
	de duracao desde que a secao dos Services comecou a funcionar.
	
	Com a opcao AKILL, mostra o tamanho atual da lista de
	AKILL e o tempo default para um AKILL expirar.
	
	A opcao ALL eh disponivel somente para os Administradores
	dos Services, e mostra informacoes sobre o consumo de memoria
	dos Services.  Usando este comando, pode-se congelar os
	Services por um curto periodo de tempo em redes grandes,
	entao nao abuse deste comando!
	
	UPTIME pode ser usado como um sinonimo para STATS.

OPER_HELP_OPER
	Sintaxe: OPER ADD nick
	         OPER DEL nick
	         OPER LIST
	
	Permite os Administradores dos Services adicionar ou remover
	nicks da lista de Operadores dos Services.  O usuario que
	tem o nick na lista de Operadores dos Services e que esta
	identificado no %s eh capaz de acessar os comandos de
	Operador dos Services.
	
	Qualquer IRCop pode usar o OPER LIST.
	Todos as outras derivacoes do comando OPER sao limitados
	aos Administradores dos Services.

OPER_HELP_ADMIN
	Sintaxe: ADMIN ADD nick
	         ADMIN DEL nick
	         ADMIN LIST
	
	Permite que os super-usuarios dos Services adicionem ou
	removam nicks da lista de Administradores dos Services.
	O usuario que tem o nick na lista de Administradores dos
	Services e que ja tenham se identificado no %s sera
	capaz de ter acesso aos comandos de Administradores dos
	Services.
	
	Qualquer IRCop pode usar o comando ADMIN LIST.
	Todas as outras derivacoes do ADMIN sao limitadas ao
	Super-usuario (root) dos Services

OPER_HELP_MODE
	Sintaxe: MODE canal modos
	
	Permite que os Operadores dos Services ajustem os modos de
	qualquer canal.  Os parametros sao os mesmos que o do
	comando /MODE padrao.
	
	Limitado aos Operadores dos Services.

OPER_HELP_CLEARMODES
	Sintaxe: CLEARMODES canal [ALL]
	
	Limpa todos os modos binarios (i,k,l,m,n,p,s,t) e bans de um
	canal.  Se ALL eh fornecido, limpa tambem todos os ops e
	voices (modos +o e +v) de um canal.
	
	Limitado aos Operadores dos Services.

OPER_HELP_CLEARCHAN
	Sintaxe: CLEARCHAN canal
	
	Remove todos os usuarios de um canal (masskick)
	
	Limitado a Services operators.

OPER_HELP_KICK
	Sintaxe: KICK canal usuario razao
	
	Permite IRCops kickar qualquer usuario de um canal.
	Paramentros sao os mesmos que comando /KICK padrao.
	A mensagem do kick tem o nick do IRCop que envia o
	comando KICK, por exemplo:
	
	*** SpamMan has been kicked off from channel #my_channel by %S (Mauritz (Flood))
	
	Limitado aos Operadores dos Services.

OPER_HELP_AKILL
	Sintaxe: AKILL ADD [+tempo] mascara razao
	         AKILL DEL mascara
	         AKILL LIST [mascara] [NOEXPIRE]
	         AKILL VIEW [mascara] [NOEXPIRE]
	         AKILL COUNT
	
	Permite que Operadores dos Services manipulem a lista de
	AKILL.  Se um usuario que tenta conectar possui uma mascara
	prevista na lista de AKILL, os Services emitem um KILL para
	aquele usuario, para servidores que suporta, e instrui todos
	os servidores da rede a adicionar um ban (K-line) para a
	mascara do usuario encontrado.
	
	AKILL ADD adiciona uma mascara ident@host na lista de AKILL
	para uma dada razao (deve ser posta obrigatoriamente).
	AKILL DEL remove uma dada mascara da lista de AKILL, se esta
	estiver presente.  AKILL LIST mostra todos os AKILLs atuais;
	se uma mascara opcional for fornecida, a listagem sera
	limitada aquela mascara.  AKILL VIEW eh uma versao mais
	detalhada do AKILL LIST e mostrara quem adicionou o AKILL, a
	data que foi adicionado, e quando sera expirado, como tambem
	a mascara (ident@host) e a razao.
	
	Opcionalmente, um tempo para o akill expirar pode ser
	fornecido com o comando AKILL ADD.  O tempo precede a
	mascara ident@host, e eh especificado como um numero inteiro
	seguido por um dos d (dias), h (horas) ou m (minutos).
	Combinacoes (como de 1h30m) nao sao permitidas.  Se uma
	unidade especifica nao eh incluida, o default e em dias
	(entao +30 significa 30 dias). Para adicionar um AKILL que
	nao expira, use +0.  Se a mascara a ser adicionada comecar
	com um +, o tempo do AKILL deve ser fornecido, ate mesmo se
	este tempo for igual ao default.  O atual tempo de expiracao
	de AKILLs pode ser encontrado com o comando STATS AKILL.
	
	A razao existe apenas para uso dos IRCops, e nao sera
	mostrada aos usuarios nas mensagens de KILL.
	
	Este comando eh limitado aos Operadores dos Services.

OPER_HELP_EXCEPTION
	Syntax: EXCEPTION ADD [+tempo] mascara limite razao
	        EXCEPTION DEL {mascara | list}
	        EXCEPTION MOVE num posicao
	        EXCEPTION LIST [mascara | list]
	        EXCEPTION VIEW [mascara | list]
	
	Permite que os Administradores dos Services manipulem a lista
	de hosts que tenham limite de conexoes especificados - deixando
	certos hosts, como shell de servidores, conectar mais que o
	numero padrao de conexoes simultaneas. Uma vez um host atingindo
	um limite de conexao, todos os clientes que tentem conectar daquele
	host serao expulsos ("killados").
	
	Antes do usuario ser expulso ("killado"), ele sera notificado
	via /NOTICE do OperServ com um topico de ajuda sobre limitacao
	de conexoes.
	O conteudo desta ajuda esta num arquivo de linguagem.
	
	EXCEPTION ADD adiciona a mascara fornecida a lista de excecoes.
	Note que as mascaras nick!user@host e user@host sao
	invalidas. Soh nomes reais de hosts, como mail.dominio.com
	e *.dominio.com, sao permitidos porque a limitacao de
	conexao nao utiliza o nick ou ident para bloquear o acesso.
	
	O limite precisa ser um numero maior ou igual zero. Isto vai
	determinar quantas conexoes um host pode ter simultaneamente.
	Um valor igual a zero sera interpretado como um numero
	ilimitado de conexoes. Veja a ajuda sobre AKILL para
	detalhes sobre parametros opcionais do tempo de validade
	
	EXCEPTION DEL remove a mascara especificada da Lista de
	excecoes.
	EXCEPTION MOVE move uma excecao de numero -num- para uma
	posicao dada. As excecoes que estavam na faixa onde houve alteracao
	serao todas movidas para cima ou para baixo conforme for o
	deslocamento necessario.
	EXCEPTION LIST e EXCEPTION VIEW mostram todas as
	excecoes atuais validas; se uma mascara eh dada como parametro
	opcional, a lista eh limitada as excecoes que sao compativeis
	com a mascara dada. A diferenca eh que EXCEPTION VIEW
	eh mais detalhado, mostrando o nome da pessoa que adicionou
	a excecao, o seu limite de conexoes, o motivo, a mascara do
	host, a data e o tempo de validade.
	

	Note que um cliente que conecte vai usar a primeira excecao
	que for compativel com o seu host. Listas de excecoes muito
	grandes e mascaras de hosts muito abrangentes certamente
	irao degradar a eficacia de funcionamento ("performance")
	dos services.
	
	Limitado aos Administradores dos Services.

OPER_HELP_SESSION
	Syntax: SESSION LIST numero
	        SESSION VIEW host
	
	Perimite que os Administradores dos Services vejam a lista de
	conexoes.
	
	SESSION LIST lista mascaras de hosts com pelo menos 
	-numero- conexoes permitidas.
	O limite deve ser um numero maior que 1. Isto deve previnir
	a listagem de muitos hosts com um limite de conexoes 
	limitado a 1.
	SESSION VIEW mostra informacoes detalhadas sobre um host
	especifico, incluindo o numero de conexoes atual e o limite
	de conexoes permitidas.
	A mascara dada em -host- nao deve incluir coringas ("wildcards").
	
	Veja a ajuda sobre EXCEPTION para mais informacoes sobre
	o limite de conexoes e como especificar limites de conexoes
	para certos hosts e grupos de hosts.
	
	Limitado aos Administradores dos Services.

OPER_HELP_SU
	Sintaxe: SU senha
	
	Permite acesso a funcoes que requerem privilegios de super-usuario
	de Services. A senha eh a mesma definida com o comando SET SUPASS;
	note que a senha precisa ser definida antes de usar esse comando.
	Privilegios de super-usuario duram ate voce trocar de nick ou sair do IRC
	
	AVISO: Se voce colocar uma senha incorreta, os Services irao transmitir
	um aviso a todos os IRC operators.
	
	Limitado a super-usuarios de Services.

OPER_HELP_SET
	Sintaxe: SET opcao parametro
	
	Configura varias opcoes globais de Services. Os nomes das
	opcoes atualmente definidas sao:
	    READONLY   Define modo read-only ou read-write
	    DEBUG      Ativa ou desativa o modo debug
	    SUPASS     Define a senha para o comando SU (super-usuario)
	
	Limitado aos Services admins.

OPER_HELP_SET_READONLY
	Sintaxe: SET READONLY {ON | OFF}
	
	Ativa ou desativa o modo read-only.  No modo read-only,
	usuarios normais nao serao capazes de modificar nenhum dado
	nos Services, incluindo lista de acesso de canais e nick,
	etc.  IRCops com privilegios suficientes nos Services serao
	capazes de mudar a lista de AKILL e de proibir e cancelar o
	registro de canais ou nicks, embora quaisquer mudancas nao
	serao salvas no banco de dados a menos que o modo read-only
	seja desativado antes dos Services serem terminados ou
	reiniciados.
	
	Esta opcao eh equivalente a opcao da linha de comando
	"-readonly".

OPER_HELP_SET_DEBUG
	Sintaxe: SET DEBUG {ON | OFF | numero}
	
	Ativa ou desativa o modo de depuracao (debug).  No modo de
	depuracao, todos os dados enviados para os Services, assim
	como todas as outras mensagens de depuracao sao enviadas a
	um arquivo de log.  Se num eh fornecido, o modo de depuracao
	eh ativado, com nivel de debug fornecido.
	
	Esta opcao eh equivalente a opcao da linha de comando
	"-debug".

OPER_HELP_SET_SUPASS
	Sintaxe: SET SUPASS [senha]
	
	Define a senha para ser usada no comando SU. A senha
	precisa ser definida antes de usar o comando SU pela primeira vez.
	Se nenhuma senha for fornecida, o comando SU ficara indisponivel
	
	Esta opcao apenas pode ser usada pelo super-usuario de Services.

OPER_HELP_JUPE
	Sintaxe: JUPE servidor
	
	Diz aos Services para "jupar" um servidor -- isto eh, criar
	um falso servidor conectado aos Services que previne que o
	servidor real com aquele nome se conecte na rede.  O jupe
	pode ser removido usando um simples SQUIT.
	
	Limitado aos Administradores dos Services.

OPER_HELP_RAW
	Sintaxe: RAW texto
	
	Envia uma serie de texto diretamente ao servidor onde os
	Services estao conectados.  Este comando tem varias
	limitacoes de uso, e pode criar confusoes e problemas na
	rede se usado impropriamente. NAO USE ESTE COMANDO a menos
	que voce tenha a certeza do que esta fazendo!
	
	Limitado aos Administradores dos Services.

OPER_HELP_UPDATE
	Sintaxe: UPDATE
	
	Faz com que os Services atualizem o banco de dados logo que
	voce envia este comando.
	
	Limitado aos Administradores dos Services.

OPER_HELP_QUIT
	Sintaxe: QUIT
	
	Faz com que deligue os Services imediatamente; o banco de
	dados nao eh salvo.  Este comando nao deve ser usado a menos
	que haja um dano da copia do banco de dados na memoria e por
	isso nao eles nao devem ser salvos.  Para desligar
	normalmente, use o comando SHUTDOWN.
	
	Limitado aos Administradores dos Services.

OPER_HELP_SHUTDOWN
	Sintaxe: SHUTDOWN
	
	Salva o banco de dados dos Services e os desliga.
	
	Limitado aos Administradores dos Services.

OPER_HELP_RESTART
	Sintaxe: RESTART
	
	Salva o banco de dados dos Services e os reinicia.
	(sai e roda imediatamente o executavel).
	
	Limitado aos Administradores dos Services.

OPER_HELP_KILLCLONES
	Syntax: KILLCLONES nick
	
	Expulsa ("killa") todos os usuarios que tenham os mesmos
	hosts que o nick especificado, adicionando *@host.com como 
	AKILL temporario para prevenir que usuarios indesejados
	reconectem imediatamente. Uma mensagem em WallOps eh tambem
	enviada para indicar quem usou o comando, quais hosts foram
	afetados e quantos usuarios foram expulsos ("killados").
	Eh usado para remover varios clones da rede.
	
	Limitado aos Administradores dos Services.

###########################################################################
#
# StatServ help messages
#
############################################################################

STAT_HELP
	%S fornece informacoes estatisticas sobre a rede de IRC,
	seus servidores e seus usuarios. Para informacoes sobre um
	comando especifico, digite /msg %S HELP comando.
	
	    SERVERS     Estatisticas de servidores
	    USERS       Estatisticas de usuarios

STAT_HELP_SERVERS
	Sintaxe: SERVERS STATS
	         SERVERS LIST [mascara]
	         SERVERS VIEW [mascara] [ONLINE | OFFLINE]
	
	Mostra estatisticas relacionadas aos servidores da rede.
	
	SERVERS STATS mostra um breve sumario dos servidores
	atualmente visiveis (online) e invisiveis (offline) para
	os Services.
	SERVERS LIST mostra uma lista dos servidores online e
	estatisticas atuais sobre cada um.
	SERVERS VIEW mostra uma lista dos servidores online e
	offline com estatisticas detalhadas sobre cada um. As
	opcoes ONLINE e OFFLINE fazem, respectivamente, com que
	apenas servidores online ou offline sejam mostrados.
	
	Use a opcao mascara para limitar os servidores dos quais
	sao mostradas estatisticas.

STAT_HELP_USERS
	Sintaxe: USERS STATS
	
	Mostra estatisticas relacionadas aos usuarios da rede.

STAT_SERVROOT_HELP_SERVERS
	Sintaxe: SERVERS STATS
	         SERVERS LIST [mascara]
	         SERVERS VIEW [mascara] [ONLINE | OFFLINE]
	         SERVERS DELETE servidor
	         SERVERS COPY servidor novoname
	         SERVERS RENAME servidor novoname
	
	Mostra estatisticas relacionadas aos servidores da rede.
	
	SERVERS STATS mostra um breve sumario dos servidores
	atualmente visiveis (online) e invisiveis (offline) para
	os Services.
	SERVERS LIST mostra uma lista dos servidores online e
	estatisticas atuais sobre cada um.
	SERVERS VIEW mostra uma lista dos servidores online e
	offline com estatisticas detalhadas sobre cada um. As
	opcoes ONLINE e OFFLINE fazem, respectivamente, com que
	apenas servidores online ou offline sejam mostrados.
	
	Use a opcao mascara para limitar os servidores dos quais
	sao mostradas estatisticas.
	
	DELETE apaga as estatisticas do servidor especificado.
	COPY duplica um conjunto de estatisticas do servidor.
	RENAME renomea um conjunto de estatisticas do servidor.
	Esses tres comandos sao limitados ao super-usuario de Services.

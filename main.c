/* Services -- main source file.
 * Copyright (c) 1996-2002 Andrew Church <achurch@achurch.org>
 * Parts copyright (c) 1999-2000 Andrew Kempe and others.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see the file COPYING); if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "services.h"
#include "timeout.h"
#include "version.h"


/******** Global variables! ********/

/* Command-line options: (note that configuration variables are in config.c) */
char *services_dir = SERVICES_DIR;	/* -dir dirname */
char *log_filename = LOG_FILENAME;	/* -log filename */
int   debug        = 0;			/* -debug */
int   readonly     = 0;			/* -readonly */
int   skeleton     = 0;			/* -skeleton */
int   nofork       = 0;			/* -nofork */
int   forceload    = 0;			/* -forceload */
int   noexpire     = 0;			/* -noexpire */
int   noakill      = 0;			/* -noakill */

/* Set to 1 if we are to quit */
int quitting = 0;

/* Set to 1 if we are to quit after saving databases */
int delayed_quit = 0;

/* Contains a message as to why services is terminating */
char *quitmsg = NULL;

/* Input buffer - global, so we can dump it if something goes wrong */
char inbuf[BUFSIZE];

/* Socket for talking to server */
int servsock = -1;

/* Should we update the databases now? */
int save_data = 0;

/* At what time were we started? */
time_t start_time;


/******** Local variables! ********/

/* Set to 1 if we are waiting for input */
static int waiting = 0;

/* Set to 1 after we've set everything up */
static int started = 0;

/* If we get a signal, use this to jump out of the main loop. */
static sigjmp_buf panic_jmp;

/*************************************************************************/

/* Various signal handlers. */

/* SIGHUP = save databases and restart */
void sighup_handler(int sig_unused)
{
#ifdef CLEAN_COMPILE
    sig_unused = sig_unused;
#endif
    save_data = -2;
    signal(SIGHUP, SIG_IGN);
    log("Received SIGHUP, restarting.");
    if (!quitmsg)
	quitmsg = "Restarting on SIGHUP";
    siglongjmp(panic_jmp, 1);
}

/* SIGTERM = save databases and shut down */
void sigterm_handler(int sig_unused)
{
#ifdef CLEAN_COMPILE
    sig_unused = sig_unused;
#endif
    save_data = 1;
    delayed_quit = 1;
    signal(SIGTERM, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    log("Received SIGTERM, exiting.");
    quitmsg = "Shutting down on SIGTERM";
    siglongjmp(panic_jmp, 1);
}

/* SIGUSR2 = close and reopen log file */
void sigusr2_handler(int sig_unused)
{
#ifdef CLEAN_COMPILE
    sig_unused = sig_unused;
#endif
    log("Received SIGUSR2, cycling log file.");
    close_log();
    open_log();
    signal(SIGUSR2, sigusr2_handler);
}

/* If we get a weird signal, come here. */
void weirdsig_handler(int signum)
{
    if (started) {
	if (signum == SIGINT || signum == SIGQUIT) {
	    /* nothing -- terminate below (but no "PANIC!") */
	} else if (!waiting) {
	    log("PANIC! buffer = %s", inbuf);
	    /* Cut off if this would make IRC command >510 characters. */
	    if (strlen(inbuf) > 448) {
		inbuf[446] = '>';
		inbuf[447] = '>';
		inbuf[448] = 0;
	    }
	    wallops(NULL, "PANIC! buffer = %s\r\n", inbuf);
	} else if (waiting < 0) {
	    /* This is static on the off-chance we run low on stack */
	    static char buf[BUFSIZE];
	    switch (waiting) {
		case  -1: snprintf(buf, sizeof(buf), "in timed_update");
		          break;
		case  -2: snprintf(buf, sizeof(buf), "sending PING");
		case -11: snprintf(buf, sizeof(buf), "saving %s", NickDBName);
		          break;
		case -12: snprintf(buf, sizeof(buf), "saving %s", ChanDBName);
		          break;
		case -14: snprintf(buf, sizeof(buf), "saving %s", OperDBName);
		          break;
		case -15: snprintf(buf, sizeof(buf), "saving %s",
							AutokillDBName);
		          break;
		case -16: snprintf(buf, sizeof(buf), "saving %s", NewsDBName);
		          break;
#ifndef STREAMLINED
		case -17: snprintf(buf, sizeof(buf), "saving %s",
							ExceptionDBName);
#endif
#ifdef STATISTICS
		case -18: snprintf(buf, sizeof(buf), "saving %s", StatDBName);
#endif
		          break;
		case -21: snprintf(buf, sizeof(buf), "expiring nicknames");
		          break;
		case -22: snprintf(buf, sizeof(buf), "expiring channels");
		          break;
		case -25: snprintf(buf, sizeof(buf), "expiring autokills");
		          break;
		default : snprintf(buf, sizeof(buf), "waiting=%d", waiting);
	    }
	    wallops(NULL, "PANIC! %s (%s)", buf, strsignal(signum));
	    log("PANIC! %s (%s)", buf, strsignal(signum));
	}
    }
    if (signum == SIGUSR1 || !(quitmsg = malloc(BUFSIZE))) {
	quitmsg = "Out of memory!";
	quitting = 1;
    } else {
#if HAVE_STRSIGNAL
	snprintf(quitmsg, BUFSIZE, "Services terminating: %s", strsignal(signum));
#else
	snprintf(quitmsg, BUFSIZE, "Services terminating on signal %d", signum);
#endif
	quitting = 1;
    }
    if (started)
	siglongjmp(panic_jmp, 1);
    else {
	log("%s", quitmsg);
	if (isatty(2))
	    fprintf(stderr, "%s\n", quitmsg);
	exit(1);
    }
}

/*************************************************************************/

/* Main routine.  (What does it look like? :-) ) */

int main(int ac, char **av, char **envp)
{
    volatile time_t last_update; /* When did we last update the databases? */
    volatile time_t last_expire; /* When did we last expire nicks/channels? */
    volatile uint32 last_check;  /* When did we last check timeouts? */
    int i;
    char *progname;


    /* Find program name. */
    if ((progname = strrchr(av[0], '/')) != NULL)
	progname++;
    else
	progname = av[0];

    /* Were we run under "listnicks" or "listchans"?  Do appropriate stuff
     * if so. */
    if (strcmp(progname, "listnicks") == 0) {
	listnicks(ac, av);
	return 0;
    } else if (strcmp(progname, "listchans") == 0) {
	listchans(ac, av);
	return 0;
    }


    /* Initialization stuff. */
    if ((i = init(ac, av)) != 0)
	return i;


    /* We have a line left over from earlier, so process it first. */
    process();

    /* Set up timers. */
    last_update = time(NULL);
    last_expire = time(NULL);
    last_check  = time(NULL);

    /* The signal handler routine will drop back here with quitting != 0
     * if it gets called. */
    sigsetjmp(panic_jmp, 1);

    /* Set up special signal handlers. */
    signal(SIGHUP, sighup_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGUSR2, sigusr2_handler);

    started = 1;


    /*** Main loop. ***/

    while (!quitting) {
	time_t now = time(NULL);
	int32 now_msec = time_msec();

	if (debug >= 2)
	    log("debug: Top of main loop");
	if (!readonly && !noexpire
	 && (save_data || now-last_expire >= ExpireTimeout)
	) {
	    waiting = -3;
	    if (debug)
		log("debug: Running expire routines");
	    if (!skeleton) {
		waiting = -21;
		expire_nicks();
		waiting = -22;
		expire_chans();
	    }
	    waiting = -25;
	    expire_akills();
#ifndef STREAMLINED
	    expire_exceptions();
#endif
	    last_expire = now;
	}
	if (!readonly && (save_data || now-last_update >= UpdateTimeout)) {
	    waiting = -2;
	    if (debug)
		log("debug: Saving databases");
	    if (!skeleton) {
		waiting = -11;
		save_ns_dbase();
		waiting = -12;
		save_cs_dbase();
	    }
	    waiting = -14;
	    save_os_dbase();
	    waiting = -15;
	    save_akill();
		waiting = -30;
		save_nooper();
		waiting = -31;
		save_snooper();
		waiting = -32;
		save_aconnect();
	    waiting = -33;
		save_fs_dbase();
		waiting = -34;
		save_grname_dbase();
		waiting = -35;
		save_nakill();
	    waiting = -16;
	    save_news();
#ifndef STREAMLINED
            waiting = -17;
            save_exceptions();
#endif
#ifdef STATISTICS
	    waiting = -18;
	    save_ss_dbase();
#endif
	    if (save_data < 0)
		break;	/* out of main loop */

	    save_data = 0;
	    last_update = now;
	}
	if (delayed_quit)
	    break;
	waiting = -2;
	if (PingFrequency && now-last_send >= PingFrequency)
	    send_cmd(NULL, "PING :%s", ServerName);
	waiting = -1;
	if (now_msec - last_check >= TimeoutCheck) {
	    check_timeouts();
	    last_check = now_msec;
	}
	waiting = 1;
	i = (int)(long)sgets2(inbuf, sizeof(inbuf), servsock);
	waiting = 0;
	if (i > 0) {
	    process();
	} else if (i == 0) {
	    int errno_save = errno;
	    quitmsg = malloc(BUFSIZE);
	    if (quitmsg) {
		snprintf(quitmsg, BUFSIZE,
			"Read error from server: %s", strerror(errno_save));
	    } else {
		quitmsg = "Read error from server";
	    }
	    quitting = 1;
	}
	waiting = -4;
    }


    /* Check for restart instead of exit */
    if (save_data == -2) {
	log("Restarting");
	if (!quitmsg)
	    quitmsg = "Restarting";
	send_cmd(ServerName, "SQUIT %s :%s", ServerName, quitmsg);
	disconn(servsock);
	close_log();
	execve(SERVICES_BIN, av, envp);
	if (!readonly) {
	    int errno_save = errno;
	    open_log();
	    errno = errno_save;
	    log_perror("Restart failed");
	    close_log();
	}
	return 1;
    }

    /* Disconnect and exit */
    if (!quitmsg)
	quitmsg = "Terminating, reason unknown";
    log("%s", quitmsg);
    if (started)
	send_cmd(ServerName, "SQUIT %s :%s", ServerName, quitmsg);
    disconn(servsock);
    return 0;
}

/*************************************************************************/

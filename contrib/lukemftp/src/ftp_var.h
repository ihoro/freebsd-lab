/*	$NetBSD: ftp_var.h,v 1.62 2001/12/26 09:40:16 lukem Exp $	*/

/*-
 * Copyright (c) 1996-2001 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Luke Mewburn.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the NetBSD
 *	Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 1985, 1989, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ftp_var.h	8.4 (Berkeley) 10/9/94
 */

/*
 * Copyright (C) 1997 and 1998 WIDE Project.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * FTP global variables.
 */

#ifdef SMALL
#undef	NO_EDITCOMPLETE
#define	NO_EDITCOMPLETE
#undef	NO_PROGRESS
#define	NO_PROGRESS
#endif

#ifndef NO_EDITCOMPLETE
#include <histedit.h>
#endif /* !NO_EDITCOMPLETE */

typedef void (*sigfunc)(int);

#include "extern.h"


/*
 * Format of command table.
 */
struct cmd {
	char	*c_name;	/* name of command */
	char	*c_help;	/* help string */
	char	 c_bell;	/* give bell when command completes */
	char	 c_conn;	/* must be connected to use command */
	char	 c_proxy;	/* proxy server may execute */
#ifndef NO_EDITCOMPLETE
	char	*c_complete;	/* context sensitive completion list */
#endif /* !NO_EDITCOMPLETE */
	void	(*c_handler)(int, char **); /* function to call */
};

/*
 * Format of macro table
 */
struct macel {
	char	 mac_name[9];	/* macro name */
	char	*mac_start;	/* start of macro in macbuf */
	char	*mac_end;	/* end of macro in macbuf */
};

/*
 * Format of option table
 */
struct option {
	char	*name;
	char	*value;
};

/*
 * Indices to features[]; an array containing status of remote server
 * features; -1 not known (FEAT failed), 0 absent, 1 present.
 */
enum {
	FEAT_FEAT = 0,		/* FEAT, OPTS */
	FEAT_MDTM,		/* MDTM */
	FEAT_MLST,		/* MLSD, MLST */
	FEAT_REST_STREAM,	/* RESTart STREAM */
	FEAT_SIZE,		/* SIZE */
	FEAT_TVFS,		/* TVFS (not used) */
	FEAT_max
};


/*
 * Global defines
 */
#define	FTPBUFLEN	MAXPATHLEN + 200
#define	MAX_IN_PORT_T	0xffffU

#define	HASHBYTES	1024	/* default mark for `hash' command */
#define	DEFAULTINCR	1024	/* default increment for `rate' command */
#define	STALLTIME	5	/* # of seconds of no xfer before "stalling" */

#define	FTP_PORT	21	/* default if ! getservbyname("ftp/tcp") */
#define	HTTP_PORT	80	/* default if ! getservbyname("http/tcp") */
#ifndef	GATE_PORT
#define	GATE_PORT	21	/* default if ! getservbyname("ftpgate/tcp") */
#endif
#ifndef	GATE_SERVER
#define	GATE_SERVER	""	/* default server */
#endif

#define	DEFAULTPAGER	"more"	/* default pager if $PAGER isn't set */
#define	DEFAULTPROMPT	"ftp> "	/* default prompt  if `set prompt' is empty */
#define	DEFAULTRPROMPT	""	/* default rprompt if `set rprompt' is empty */

#define	TMPFILE		"ftpXXXXXXXXXX"


#ifndef	GLOBAL
#define	GLOBAL	extern
#endif

/*
 * Options and other state info.
 */
GLOBAL	int	trace;		/* trace packets exchanged */
GLOBAL	int	hash;		/* print # for each buffer transferred */
GLOBAL	int	mark;		/* number of bytes between hashes */
GLOBAL	int	sendport;	/* use PORT/LPRT cmd for each data connection */
GLOBAL	int	verbose;	/* print messages coming back from server */
GLOBAL	int	connected;	/* 1 = connected to server, -1 = logged in */
GLOBAL	int	fromatty;	/* input is from a terminal */
GLOBAL	int	interactive;	/* interactively prompt on m* cmds */
GLOBAL	int	confirmrest;	/* confirm rest of current m* cmd */
GLOBAL	int	debug;		/* debugging level */
GLOBAL	int	bell;		/* ring bell on cmd completion */
GLOBAL	int	doglob;		/* glob local file names */
GLOBAL	int	autologin;	/* establish user account on connection */
GLOBAL	int	proxy;		/* proxy server connection active */
GLOBAL	int	proxflag;	/* proxy connection exists */
GLOBAL	int	gatemode;	/* use gate-ftp */
GLOBAL	char   *gateserver;	/* server to use for gate-ftp */
GLOBAL	int	sunique;	/* store files on server with unique name */
GLOBAL	int	runique;	/* store local files with unique name */
GLOBAL	int	mcase;		/* map upper to lower case for mget names */
GLOBAL	int	ntflag;		/* use ntin ntout tables for name translation */
GLOBAL	int	mapflag;	/* use mapin mapout templates on file names */
GLOBAL	int	preserve;	/* preserve modification time on files */
GLOBAL	int	progress;	/* display transfer progress bar */
GLOBAL	int	code;		/* return/reply code for ftp command */
GLOBAL	int	crflag;		/* if 1, strip car. rets. on ascii gets */
GLOBAL	int	passivemode;	/* passive mode enabled */
GLOBAL	int	activefallback;	/* fall back to active mode if passive fails */
GLOBAL	char   *altarg;		/* argv[1] with no shell-like preprocessing  */
GLOBAL	char	ntin[17];	/* input translation table */
GLOBAL	char	ntout[17];	/* output translation table */
GLOBAL	char	mapin[MAXPATHLEN]; /* input map template */
GLOBAL	char	mapout[MAXPATHLEN]; /* output map template */
GLOBAL	char	typename[32];	/* name of file transfer type */
GLOBAL	int	type;		/* requested file transfer type */
GLOBAL	int	curtype;	/* current file transfer type */
GLOBAL	char	structname[32];	/* name of file transfer structure */
GLOBAL	int	stru;		/* file transfer structure */
GLOBAL	char	formname[32];	/* name of file transfer format */
GLOBAL	int	form;		/* file transfer format */
GLOBAL	char	modename[32];	/* name of file transfer mode */
GLOBAL	int	mode;		/* file transfer mode */
GLOBAL	char	bytename[32];	/* local byte size in ascii */
GLOBAL	int	bytesize;	/* local byte size in binary */
GLOBAL	int	anonftp;	/* automatic anonymous login */
GLOBAL	int	dirchange;	/* remote directory changed by cd command */
GLOBAL	int	flushcache;	/* set HTTP cache flush headers with request */
GLOBAL	int	rate_get;	/* maximum get xfer rate */
GLOBAL	int	rate_get_incr;	/* increment for get xfer rate */
GLOBAL	int	rate_put;	/* maximum put xfer rate */
GLOBAL	int	rate_put_incr;	/* increment for put xfer rate */
GLOBAL	int	retry_connect;	/* seconds between retrying connection */
GLOBAL	int	ttywidth;	/* width of tty */
GLOBAL	char   *tmpdir;		/* temporary directory */
GLOBAL	FILE   *ttyout;		/* stdout, or stderr if retrieving to stdout */
GLOBAL	int	epsv4;		/* use EPSV/EPRT on IPv4 connections */
GLOBAL	int	epsv4bad;	/* EPSV doesn't work on the current server */
GLOBAL	int	editing;	/* command line editing enabled */
GLOBAL	int	features[FEAT_max];	/* remote FEATures supported */

#ifndef NO_EDITCOMPLETE
GLOBAL	EditLine *el;		/* editline(3) status structure */
GLOBAL	History  *hist;		/* editline(3) history structure */
GLOBAL	char	 *cursor_pos;	/* cursor position we're looking for */
GLOBAL	size_t	  cursor_argc;	/* location of cursor in margv */
GLOBAL	size_t	  cursor_argo;	/* offset of cursor in margv[cursor_argc] */
#endif /* !NO_EDITCOMPLETE */

GLOBAL	off_t	bytes;		/* current # of bytes read */
GLOBAL	off_t	filesize;	/* size of file being transferred */
GLOBAL	char   *direction;	/* direction transfer is occurring */
GLOBAL	off_t	restart_point;	/* offset to restart transfer */

GLOBAL	char   *hostname;	/* name of host connected to */
GLOBAL	int	unix_server;	/* server is unix, can use binary for ascii */
GLOBAL	int	unix_proxy;	/* proxy is unix, can use binary for ascii */
GLOBAL	char	remotepwd[MAXPATHLEN];	/* remote dir */
GLOBAL	char   *username;	/* name of user logged in as. (dynamic) */

GLOBAL	sa_family_t family;	/* address family to use for connections */
GLOBAL	char	*ftpport;	/* port number to use for FTP connections */
GLOBAL	char	*httpport;	/* port number to use for HTTP connections */
GLOBAL	char	*gateport;	/* port number to use for gateftp connections */

GLOBAL	char   *outfile;	/* filename to output URLs to */
GLOBAL	int	restartautofetch; /* restart auto-fetch */

GLOBAL	sigjmp_buf toplevel;	/* non-local goto stuff for cmd scanner */

GLOBAL	char	line[FTPBUFLEN]; /* input line buffer */
GLOBAL	char	*stringbase;	/* current scan point in line buffer */
GLOBAL	char	argbuf[FTPBUFLEN]; /* argument storage buffer */
GLOBAL	char	*argbase;	/* current storage point in arg buffer */
GLOBAL	StringList *marg_sl;	/* stringlist containing margv */
GLOBAL	int	margc;		/* count of arguments on input line */
#define	margv (marg_sl->sl_str)	/* args parsed from input line */
GLOBAL	int     cpend;		/* flag: if != 0, then pending server reply */
GLOBAL	int	mflag;		/* flag: if != 0, then active multi command */

GLOBAL	int	options;	/* used during socket creation */

GLOBAL	int	sndbuf_size;	/* socket send buffer size */
GLOBAL	int	rcvbuf_size;	/* socket receive buffer size */

GLOBAL	int	macnum;		/* number of defined macros */
GLOBAL	struct macel macros[16];
GLOBAL	char	macbuf[4096];

GLOBAL	char	*localhome;		/* local home directory */
GLOBAL	char	*localname;		/* local user name */
GLOBAL	char	 netrc[MAXPATHLEN];	/* path to .netrc file */
GLOBAL	char	 reply_string[BUFSIZ];	/* first line of previous reply */
GLOBAL	void	(*reply_callback)(const char *);
					/*
					 * function to call for each line in
					 * the server's reply except for the
					 * first (`xxx-') and last (`xxx ')
					 */


GLOBAL	FILE	*cin;
GLOBAL	FILE	*cout;
GLOBAL	int	 data;

extern	struct cmd	cmdtab[];
extern	struct option	optiontab[];


#define	EMPTYSTRING(x)	((x) == NULL || (*(x) == '\0'))
#define	FREEPTR(x)	if ((x) != NULL) { free(x); (x) = NULL; }

#ifdef BSD4_4
# define HAVE_SOCKADDR_SA_LEN	1
#endif

#ifdef NO_LONG_LONG
# define LLF		"%ld"
# define LLFP(x)	"%" x "ld"
# define LLT		long
# define ULLF		"%lu"
# define ULLFP(x)	"%" x "lu"
# define ULLT		unsigned long
# define STRTOLL(x,y,z)	strtol(x,y,z)
#else
#if HAVE_PRINTF_QD
# define LLF		"%qd"
# define LLFP(x)	"%" x "qd"
# define LLT		long long
# define ULLF		"%qu"
# define ULLFP(x)	"%" x "qu"
# define ULLT		unsigned long long
# define STRTOLL(x,y,z)	strtoll(x,y,z)
#else
# define LLF		"%lld"
# define LLFP(x)	"%" x "lld"
# define LLT		long long
# define ULLF		"%llu"
# define ULLFP(x)	"%" x "llu"
# define ULLT		unsigned long long
# define STRTOLL(x,y,z)	strtoll(x,y,z)
#endif
#endif

/* ====================================================================
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2000 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Apache" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

#ifndef FILE_IO_H
#define FILE_IO_H

#include "apr_private.h"
#include "apr_general.h"
#include "apr_file_io.h"
#include "apr_errno.h"
#include "apr_lib.h"

/* System headers the file I/O library needs */
#if HAVE_FCNTL_H
#include <fcntl.h>
#endif
#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#if HAVE_ERRNO_H
#include <errno.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#endif
#if HAVE_DIRENT_H
#include <dirent.h>
#endif
#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_STDIO_H
#include <stdio.h>
#endif
#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#if HAVE_SYS_UIO_H
#include <sys/uio.h>
#endif
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef BEOS
#include <kernel/OS.h>
#endif
/* BeOS still defines fd_set in sys/socket.h so include it here.
 * I'm not just including it as most platforms won't need it...
 */
#if BEOS_BONE
#include <sys/socket.h> /* for fd_set definitions */
#endif
/* End System headers */

#define APR_FILE_BUFSIZE 4096

struct ap_file_t {
    ap_pool_t *cntxt;
    int filedes;
    char * fname;
    int oflags;
    int eof_hit;
    int pipe;
    ap_interval_time_t timeout;
    int buffered;
    enum {BLK_UNKNOWN, BLK_OFF, BLK_ON } blocking;
    int ungetchar;    /* Last char provided by an unget op. (-1 = no char)*/

    /* Stuff for buffered mode */
    char *buffer;
    int bufpos;               /* Read/Write position in buffer */
    unsigned long dataRead;   /* amount of valid data read into buffer */
    int direction;            /* buffer being used for 0 = read, 1 = write */
    unsigned long filePtr;    /* position in file of handle */
#if APR_HAS_THREADS
    struct ap_lock_t *thlock;
#endif
};

struct ap_dir_t {
    ap_pool_t *cntxt;
    char *dirname;
    DIR *dirstruct;
    struct dirent *entry;
};

ap_status_t ap_unix_file_cleanup(void *);
mode_t ap_unix_get_fileperms(ap_fileperms_t);

#endif  /* ! FILE_IO_H */


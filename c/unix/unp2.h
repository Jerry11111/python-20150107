#include    <sys/types.h>   /* basic system data types */
#include    <sys/socket.h>  /* basic socket definitions */
#if TIME_WITH_SYS_TIME
#include    <sys/time.h>    /* timeval{} for select() */
#include    <time.h>        /* timespec{} for pselect() */
#else
#if HAVE_SYS_TIME_H
#include    <sys/time.h>    /* includes <time.h> unsafely */
#else
#include    <time.h>        /* old system? */
#endif
#endif
#include    <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include    <arpa/inet.h>   /* inet(3) functions */
#include    <errno.h>
#include    <fcntl.h>       /* for nonblocking */
#include    <netdb.h>
#include    <signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>    /* for S_xxx file mode constants */
#include    <sys/uio.h>     /* for iovec{} and readv/writev */
#include    <unistd.h>
#include    <sys/wait.h>
#include    <sys/un.h>      /* for Unix domain sockets */

#ifdef  HAVE_SYS_SELECT_H
# include   <sys/select.h>  /* for convenience */
#endif
#define MAXLINE     4096    /* max text line length */
#define	SA	struct sockaddr
void	 err_quit(const char *, ...);
#define LISTENQ     1024    /* 2nd argument to listen() */

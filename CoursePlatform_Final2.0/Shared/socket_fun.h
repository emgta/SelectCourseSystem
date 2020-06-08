#ifndef socket_fun_h
#define socket_fun_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <io.h>
#include <process.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>

typedef int ssize_t;
#define LISTENQ  1024  /* second argument to listen() */

/* I/O wrappers */
int Select(fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout);

/* Sockets interface wrappers */
int Socket(int domain, int type, int protocol);
void Setsockopt(int s, int level, int optname, const void *optval, int optlen);
void Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
void Listen(int s, int backlog);
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

/* Client/server helper functions */
int open_clientfd(const char *hostname, int portno);
int open_listenfd(int portno);

/* Wrappers for client/server helper functions */
int Open_clientfd(const char *hostname, int port);
int Open_listenfd(int port);

#endif

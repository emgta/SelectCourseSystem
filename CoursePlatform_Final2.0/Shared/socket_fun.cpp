#include "socket_fun.h"

/********************************
 * Wrappers for Unix I/O routines
 ********************************/

int Select(fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout) {
    int rc;

    if ((rc = select(0, readfds, writefds, exceptfds, timeout)) < 0)
        throw std::invalid_argument("Select error!");
    return rc;
}

/****************************
 * Sockets interface wrappers
 ****************************/

int Socket(int domain, int type, int protocol) {
    int rc;

    if ((rc = socket(domain, type, protocol)) < 0)
        throw std::invalid_argument("Socket error!");
    return rc;
}

void Setsockopt(int s, int level, int optname, const void *optval, int optlen) {
    int rc;

    if ((rc = setsockopt(s, level, optname, (const char*)optval, optlen)) < 0)
        throw std::invalid_argument("Setsocket error!");
}

void Bind(int sockfd, struct sockaddr *my_addr, int addrlen) {
    int rc;

    if ((rc = bind(sockfd, my_addr, addrlen)) < 0)
        throw std::invalid_argument("Bind error!");
}

void Listen(int s, int backlog) {
    int rc;

    if ((rc = listen(s,  backlog)) < 0)
        throw std::invalid_argument("Listen error!");
}

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen) {
    int rc;

    if ((rc = accept(s, addr, addrlen)) < 0)\
        throw std::invalid_argument("Accept error!");
    return rc;
}

void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen) {
    int rc;

    if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
        throw std::invalid_argument("Connect error!");
}

/********************************
 * Client/server helper functions
 ********************************/
/* $begin open_clientfd */
int open_clientfd(const char *address, int port) {
    int clientfd;
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::invalid_argument("create socket error!");


    /* Fill in the server's IP address and port */
    memset((char *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(address);
    serveraddr.sin_port = htons(port);

    /* Establish a connection with the server */
    if (connect(clientfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr)) < 0)
        throw std::invalid_argument("create connect error!");

    return clientfd;
}
/* $end open_clientfd */

/*
 * open_listenfd - open and return a listening socket on port
 *     Returns -1 and sets errno on Unix error.
 */
/* $begin open_listenfd */
int open_listenfd(int port) {
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;

    /* Create a socket descriptor */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::invalid_argument("create socket error!");

    /* Eliminates "Address already in use" error from bind. */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
                   (const char*)&optval, sizeof(int)) < 0)
        return -1;

    /* Listenfd will be an endpoint for all requests to port
       on any IP address for this host */
    memset((char *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);
    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
        throw std::invalid_argument("bind error!");

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0)
        throw std::invalid_argument("listen error!");

    return listenfd;
}
/* $end open_listenfd */

/******************************************
 * Wrappers for the client/server helper routines
 ******************************************/
int Open_clientfd(const char *address, int port) {
    int rc;

    if ((rc = open_clientfd(address, port)) < 0)
        throw std::invalid_argument("Open_clientfd error!");
    return rc;
}

int Open_listenfd(int port) {
    int rc;

    if ((rc = open_listenfd(port)) < 0)
        throw std::invalid_argument("Open_listenfd error!");
    return rc;
}





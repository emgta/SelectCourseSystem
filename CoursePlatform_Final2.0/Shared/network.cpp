//
//  network.cpp
//  Results Management System
//

#include "network.hpp"

/*
 send the "request" packet
*/
void send_request(int fd, unsigned short int t) {
    Request_info req;
    req = t;
    Send(fd, &req, sizeof(req));
}


void recv_message(int fd, Message &mes) {
    char tmp[MAX_CONTENT_LENGTH + 2];

    Recv(fd, tmp, MAX_CONTENT_LENGTH + 2);
    memcpy(&mes.ack, tmp, 2);
    memcpy(mes.content, tmp + 2, MAX_CONTENT_LENGTH);

    if (mes.ack < 0) {
        //printf("%s", mes.content);
        throw std::invalid_argument(mes.content);
    }
}

/*
  send the "message" packet
*/
void send_message(int fd, const char *content) {
    Message mes;
    if (content == NULL)
        mes.ack = -1;
    else
        mes.ack = 0;
    strcpy(mes.content, content);

    char tmp[MAX_CONTENT_LENGTH + 2];
    memcpy(tmp, &mes.ack, 2);
    memcpy(tmp + 2, mes.content, MAX_CONTENT_LENGTH);

    Send(fd, tmp, MAX_CONTENT_LENGTH + 2);
}

void send_message(int fd, std::stringstream &os) {
    Message mes;
    strcpy(mes.content, os.str().c_str());

    char tmp[MAX_CONTENT_LENGTH + 2];
    memcpy(tmp, &mes.ack, 2);
    memcpy(tmp + 2, mes.content, MAX_CONTENT_LENGTH);

    Send(fd, tmp, MAX_CONTENT_LENGTH + 2);
}

void send_error(int fd, const char *s) {
    Message error;
    error.ack = -1;
    strcpy(error.content, s);

    char tmp[MAX_CONTENT_LENGTH + 2];
    memcpy(tmp, &error.ack, 2);
    memcpy(tmp + 2, error.content, MAX_CONTENT_LENGTH);

    Send(fd, tmp, MAX_CONTENT_LENGTH + 2);
}

int Recv(int fd, void *ptr, size_t nbytes) {
    int n;

    if ((n = recv(fd, (char *)ptr, nbytes, 0)) < 0)
        throw std::invalid_argument("Send Error!");

    // printf("Recv %d\n", n);

    return n;
}

int Send(int fd, const void *usrbuf, size_t nbytes) {
    int n;

    if ((n = send(fd, (const char *)usrbuf, nbytes, 0)) < 0)
        throw std::invalid_argument("Recv Error!");

    // printf("Send %d\n", n);

    return n;
}

bool IsSocketClosed(int clientSocket) {
    bool ret = false;
    HANDLE closeEvent = WSACreateEvent();
    WSAEventSelect(clientSocket, closeEvent, FD_CLOSE);

    DWORD dwRet = WaitForSingleObject(closeEvent, 0);

    if (dwRet == WSA_WAIT_EVENT_0)
        ret = true;
    else if (dwRet == WSA_WAIT_TIMEOUT)
        ret = false;

    WSACloseEvent(closeEvent);
    return ret;
}

//
//  network.h
//  Results Management System
//


#ifndef network_hpp
#define network_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "socket_fun.h"

constexpr unsigned int MAX_CONTENT_LENGTH = 1024;
constexpr int MIN_PASSWORD_LENGTH = 6;
constexpr int MAX_PASSWORD_LENGTH = 20;

typedef unsigned short Request_info;

struct Message {
    short int ack = 0;
    char content[MAX_CONTENT_LENGTH] = "";
};

int Recv(int fd, void *ptr, size_t nbytes);
int Send(int fd, const void *usrbuf, size_t nbytes);
void recv_message(int fd, Message &mes);
void send_request(int, unsigned short int);
void send_message(int, const char *);
void send_message(int, std::stringstream &);
void send_error(int, const char*);
bool IsSocketClosed(int clientSocket);

extern int userSock;

typedef unsigned short int clientType;
typedef unsigned short int requestType;

constexpr clientType isStudent = 1;
constexpr clientType isTeacher = 2;

constexpr unsigned short int LOGIN = 0;
constexpr unsigned short int GET_INFO = 1;
constexpr unsigned short int PRINT_ELECTIVE_COURSE = 2;
constexpr unsigned short int ATTEND_COURSE = 3;
constexpr unsigned short int CANCEL_COURSE = 4;
constexpr unsigned short int PRINT_SCORE_TABLE = 5;
constexpr unsigned short int MODIFY_SCORE = 6;
constexpr unsigned short int MODIFY_PASSWD = 7;

#endif /* network_hpp */

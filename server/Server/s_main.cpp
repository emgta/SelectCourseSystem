#include <stdio.h>
#include <iostream>
#include <ctime>
#include <signal.h>

#include "../Shared/csapp.h"
#include "../Shared/global.hpp"
#include "../Shared/network.hpp"
#include "../Library/person.hpp"
#include "../Library/system.hpp"
#include "server.hpp"

static Server *myServer;
void stop_server(int sig);

int main(int argc, const char * argv[]) {
    WSADATA wsaData;
    int iResult;
    //初始化winsocket
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("初始化出错：%d\n", iResult);
        return 1;
    }

    signal(SIGINT, stop_server);
    myServer = new Server(argc, argv);
    myServer->run();

    return 0;
}

void stop_server(int sig) {
    if (sig == SIGINT) {
        delete myServer;
        std::cout << "Server is stopping..." << std::endl;
        exit(EXIT_SUCCESS);
    }
}

#ifndef server_h
#define server_h

#include <vector>
#include <ctime>
#include <fstream>
#include <set>
#include <map>

#include "../Shared/global.hpp"
#include "../Shared/network.hpp"

constexpr unsigned short int NO_LOGIN = 0;
constexpr unsigned short int STUDENT = 1;
constexpr unsigned short int TEACHER = 2;
constexpr int MAX_CLIENT = 100;

struct Client_info {
    short int status = 0;
    Person_ptr data;
};

class Server {
public:
    Server(int, const char *[]);
    ~Server();
    void run();
private:
    int listenSock, dataSock;
    fd_set fds, rfds;
    time_t start_time;
    std::map <int, Client_info> client;
    std::set <int> sock_fd;
    std::ofstream log_file;

    /* basic function for server */
    int receive_data(int);
    void recv_request(int, Request_info*);
    void log_event(std::ostream&, Request_info, sockaddr_in, socklen_t);
    bool authenrize(int, Request_info);

    /* process the client's request */
    void do_login(int);
    void do_get_info(int);
    void do_print_elective_course(int);
    void do_attend_course(int);
    void do_cancel_course(int);
    void do_check_score(int);
    void do_modify_score(int);
    void do_modify_password(int);
};


#endif /* server_h */

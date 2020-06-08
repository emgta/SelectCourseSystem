#ifndef graphic_client_interface_hpp
#define graphic_client_interface_hpp

#include "../Client/user_interface.hpp"
#include "../Shared/global.hpp"
#include "../Shared/network.hpp"
#include <QString>

#define MAX_INFO_LENGTH 1024

extern User_interface Client;

typedef short int responType;

constexpr short int RECV_ERR = -1;
constexpr short int RECV_INFO = 0;
constexpr int ID_LEN = 10;
constexpr int COURSE_NUM_LEN = 9;
constexpr unsigned short int MAX_COURSE_SCORE = 100;


struct clientRespon {
    union Data {
        char recv_info[MAX_INFO_LENGTH];
        char err_info[MAX_INFO_LENGTH];
        Data() {}
        ~Data() {}
    } data;
    responType rp;
    clientRespon() {}
    ~clientRespon() {}
};

bool network_init(std::string ip_addr, int port);
void User_login(clientType loginType, QString id, QString passwd, clientRespon &respon);
void Get_info(Score_mode order, clientRespon &respon);
void Get_elective_course(clientRespon &respon);
void Attend_course(QString course_num, clientRespon &respon);
void Cancel_course(QString course_num, clientRespon &respon);
void Check_score(QString course_num, Score_mode order, clientRespon &respon);
void Modify_score(QString course_num, QString student_id, QString new_score, clientRespon &respon);
void Modify_passwd(clientType loginType, QString id, QString cur_passwd, QString new_passwd,clientRespon &respon);
void recv_info(clientRespon &respo);
bool isDigitString(const QString& src);


#endif /* graphic_client_interface_hpp */

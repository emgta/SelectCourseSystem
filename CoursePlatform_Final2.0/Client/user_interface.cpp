//
//  user_interface.cpp
//  Results Management System
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "user_interface.hpp"
#include "../Shared/global.hpp"
#include "../Shared/socket_fun.h"
#include "../Shared/network.hpp"

int userSock;

/******************************************
 * Wrappers for the request sending routines
 ******************************************/

void User_interface::do_display_info(Score_mode mode) {
    send_request(userSock, GET_INFO);
    Send(userSock, &mode, sizeof(mode));
}

void User_interface::do_login(clientType loginType, Shared::Person id, std::string password) {
    send_request(userSock, LOGIN);
    Send(userSock, &loginType, sizeof(loginType));
    Send(userSock, &id, sizeof(id));
    const char *passwd_sd = password.c_str();
    Send(userSock, passwd_sd, MAX_PASSWORD_LENGTH);

//    Message mes;
//	char tmp[MAX_CONTENT_LENGTH + 2];

//	Recv(userSock, &tmp, MAX_CONTENT_LENGTH + 2);
//	memcpy(&mes.ack, tmp, 2);
//	memcpy(mes.content, tmp + 2, MAX_CONTENT_LENGTH);

//    /* login successfully will return a ack >= 0 */
//    if (mes.ack < 0) {
//        throw std::invalid_argument(mes.content);
//    }
//    else {

//    }
}

void User_interface::do_attend_course(Shared::Course courseNum) {
    send_request(userSock, ATTEND_COURSE);
    Send(userSock, &courseNum, sizeof(courseNum));
}

void User_interface::do_cancel_course(Shared::Course courseNum) {
    send_request(userSock, CANCEL_COURSE);
    Send(userSock, &courseNum, sizeof(courseNum));
}

void User_interface::do_check_score(Shared::Course courseNum, Score_mode mode) {
//    unsigned short int order;
//    Course::seq courseID;

//    /* input the courseID and expected order */
//    std::cout << "Please enter the course ID" <<std::endl;
//    std::cin >> courseID;
//    std::cout << "Which order do you prefer, 0 for increasing and 1 for decreasing?" << std::endl;
//    std::cin >> order;
//    if (std::cin.fail() || order > 1) throw std::invalid_argument("Please input a integer between 0 ~ 1!");

    /* send the request */
    send_request(userSock, PRINT_SCORE_TABLE);
    Send(userSock, &courseNum, sizeof(courseNum));
    Send(userSock, &mode, sizeof(mode));
}

void User_interface::do_modify_score(Shared::Course courseNum, Shared::score newScore, Shared::Person student) {
//    Course::seq course = 0;
//    Person::seq student = 0;
//    Course::score  newScore = 0;

//    /* Read the data */
//    std::cout << "Please input the course ID, student ID, and new score:" << std::endl;
//    std::cin >> course >> student >> newScore;

    /* Send the Request info */
    send_request(userSock, MODIFY_SCORE);
    Send(userSock, &courseNum, sizeof(courseNum));
    Send(userSock, &student, sizeof(student));
    Send(userSock, &newScore, sizeof(newScore));
}

void User_interface::do_print_elective_course() {
    send_request(userSock, PRINT_ELECTIVE_COURSE);
}

void User_interface::do_modify_passwd(clientType loginType, Shared::Person id, std::string cur_passwd, std::string new_passwd) {
    send_request(userSock, MODIFY_PASSWD);
    Send(userSock, &loginType, sizeof(loginType));
    Send(userSock, &id, sizeof(id));
    const char *cur_passwd_sd = cur_passwd.c_str(),
                *new_passwd_sd = new_passwd.c_str();
    Send(userSock, cur_passwd_sd, MAX_PASSWORD_LENGTH);
    Send(userSock, new_passwd_sd, MAX_PASSWORD_LENGTH);
}

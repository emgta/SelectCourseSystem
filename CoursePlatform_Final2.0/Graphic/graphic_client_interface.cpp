#include "graphic_client_interface.hpp"
#include <QDebug>

User_interface Client;

bool network_init(std::string ip_addr, int port) {
    try {
        WSADATA wsaData;
        int iResult;
        //初始化winsocket
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("初始化出错：%d\n", iResult);
            exit(EXIT_FAILURE);
        }

        userSock = Open_clientfd(ip_addr.c_str(), port);
    } catch (std::invalid_argument err) {
        return false;
    }

    return true;
}

void User_login(clientType loginType, QString id, QString passwd, clientRespon &respon) {
    qDebug() << "User_login!";

    try {
        if(!isDigitString(id))
            throw std::invalid_argument("The username is not valid!");
        if(id.length() != ID_LEN)
            throw std::invalid_argument("The username length is not valid!");
        if(passwd.length() < MIN_PASSWORD_LENGTH || passwd.length() > MAX_PASSWORD_LENGTH)
            throw std::invalid_argument("The password length is not valid!");

        Client.do_login(loginType,
                        id.toUInt(),
                        passwd.toStdString());
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}

void Get_info(Score_mode order, clientRespon &respon) {
    qDebug() << "Get_info!";

    try {
        Client.do_display_info(order);
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}

void Get_elective_course(clientRespon &respon) {
    qDebug() << "Get_elective_course!";

    try {
        Client.do_print_elective_course();
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}

void Attend_course(QString course_num, clientRespon &respon) {
    qDebug() << "Attend_course!";

    try {
        if(!isDigitString(course_num))
            throw std::invalid_argument("The course-num is not valid!");
        if(course_num.length() != COURSE_NUM_LEN)
            throw std::invalid_argument("The course-num length is not valid!");

        Client.do_attend_course(course_num.toULong());
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}

void Cancel_course(QString course_num, clientRespon &respon) {
    qDebug() << "Cancel_course!";

    try {
        if(!isDigitString(course_num))
            throw std::invalid_argument("The course-num is not valid!");
        if(course_num.length() != COURSE_NUM_LEN)
            throw std::invalid_argument("The course-num length is not valid!");

        Client.do_cancel_course(course_num.toULong());
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}

void Check_score(QString course_num, Score_mode order, clientRespon &respon) {
    qDebug() << "Check_score!";

    try {
        if(!isDigitString(course_num))
            throw std::invalid_argument("The course-num is not valid!");
        if(course_num.length() != COURSE_NUM_LEN)
            throw std::invalid_argument("The course-num length is not valid!");

        Client.do_check_score(course_num.toULong(), order);
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}

void Modify_score(QString course_num, QString student_id, QString new_score, clientRespon &respon) {
    qDebug() << "Modify_score!";

    try {
        if(!isDigitString(course_num))
            throw std::invalid_argument("The course-num is not valid!");
        if(course_num.length() != COURSE_NUM_LEN)
            throw std::invalid_argument("The course-num length is not valid!");
        if(!isDigitString(student_id))
            throw std::invalid_argument("The student id is not valid!");
        if(student_id.length() != ID_LEN)
            throw std::invalid_argument("The student id length is not valid!");
        if(!isDigitString(new_score))
            throw std::invalid_argument("The new score is not valid!");

        Shared::score modify_score = new_score.toUShort();
        if(modify_score > MAX_COURSE_SCORE)
            throw std::invalid_argument("The new score value is not valid!");

        Client.do_modify_score(course_num.toULong(),
                               modify_score,
                               student_id.toUInt());
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}

void Modify_passwd(clientType loginType, QString id, QString cur_passwd, QString new_passwd, clientRespon &respon) {
    try {
        if(!isDigitString(id))
            throw std::invalid_argument("The username is not valid!");
        if(id.length() != ID_LEN)
            throw std::invalid_argument("The username length is not valid!");
        if(cur_passwd.length() < MIN_PASSWORD_LENGTH || cur_passwd.length() > MAX_PASSWORD_LENGTH)
            throw std::invalid_argument("The password length is not valid!");
        if(new_passwd.length() < MIN_PASSWORD_LENGTH || new_passwd.length() > MAX_PASSWORD_LENGTH)
            throw std::invalid_argument("The password length is not valid!");

        Client.do_modify_passwd(loginType,
                                id.toUInt(),
                                cur_passwd.toStdString(),
                                new_passwd.toStdString());
        recv_info(respon);
    } catch (std::invalid_argument err) {
        process_error(err, respon.data.err_info);
        respon.rp = RECV_ERR;
    }
}


void recv_info(clientRespon &respon) {
    Message mes;

    recv_message(userSock, mes);
    strcpy(respon.data.recv_info, mes.content);

    respon.rp = RECV_INFO;
}

bool isDigitString(const QString& src) {
    const char *s = src.toUtf8().data();
    while(*s && *s>='0' && *s<='9')s++;
    return !bool(*s);
}




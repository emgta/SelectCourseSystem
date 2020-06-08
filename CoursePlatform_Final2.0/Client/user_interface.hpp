//
//  user_interface.hpp
//  Results Management System
//
//

#ifndef user_interface_hpp
#define user_interface_hpp

#include <stdio.h>
#include <string>
#include "../Shared/global.hpp"
#include "../Shared/network.hpp"

class User_interface {
public:
    User_interface() = default;
    ~User_interface() = default;

private:
    clientType userType = 0;

public:
    /* to send the user's request */
    void do_display_info(Score_mode mode = INCREASE_BY_SCORE);
    void do_attend_course(Shared::Course coursenum);
    void do_cancel_course(Shared::Course courseNum);
    void do_check_score(Shared::Course courseNum, Score_mode mode = INCREASE_BY_SCORE);
    void do_modify_score(Shared::Course courseNum, Shared::score newScore, Shared::Person student);
    void do_login(clientType loginType, Shared::Person id, std::string password);
    void do_print_elective_course();
    void do_modify_passwd(clientType loginType, Shared::Person id, std::string cur_passwd, std::string new_passwd);
};

#endif /* user_interface_hpp */

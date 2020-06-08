#ifndef INFO_TO_STR_H
#define INFO_TO_STR_H

#include<QString>
#include "graphic_client_interface.hpp"

constexpr short int STU_CHECK = 1;
constexpr short int STU_SELECT= 2;
constexpr short int TEA_CHECK = 3;
constexpr short int TEA_SELECT = 2;
constexpr short int STU_PERCHECK = 5;
constexpr short int TEA_PERCHECK = 6;


int change_info_to_str(clientRespon &respon,QString *q[],int input);

#endif // INFO_TO_STR_H

#include "stu_check.h"
#include "ui_stu_check.h"
#include "graphic_client_interface.hpp"
#include <QDebug>


std::string stuCheck[100][8]= {""};
for(int i=0,j=0,n=0; respon.data.recv_info[i]!='\0'; i++) {
    while(n<6) {
        while((respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t')||(respon.data.recv_info[i]=='\n')) {
            i++;
        }
        while(respon.data.recv_info[i]!='\n') {
            i++;
        }
        n++;
    }
    i++;
    for(int k=0; respon.data.recv_info[i]!='\n'; k++) {

        while((respon.data.recv_info[i]!=' ')&&(respon.data.recv_info[i]!='\t')) {
            stuCheck[j][k].push_back(respon.data.recv_info[i]);
            i++;
        }
        for(; (respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t'); i++);
    }
    j++;
}

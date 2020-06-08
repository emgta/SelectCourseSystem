#include<QString>
#include "graphic_client_interface.hpp"
#include "change_func.h"


int change_func(clientRespon &respon,QString *q) {
    int i=0,j=0,n=0;
    std::string stuCheck[100][8]= {};                       //创建string二维数组
    for(; respon.data.recv_info[i]!='\0'; i++) {            //判断字符数组是否结束
        while(n<6) {                                        //跳过前n行数据
            while((respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t')||(respon.data.recv_info[i]=='\n')) {
                i++;
            }                                               //跳过开头的空格、制表符、换行符
            while(respon.data.recv_info[i]!='\n') {
                i++;
            }
            n++;                                            //跳过每一行数据
        }
        i++;
        for(int k=0; respon.data.recv_info[i]!='\n'; k++) { //开始将数据放入

            while((respon.data.recv_info[i]!=' ')&&(respon.data.recv_info[i]!='\t')&&(respon.data.recv_info[i]!='\n')) {
                stuCheck[j][k].push_back(respon.data.recv_info[i]);             //将字符压入string
                i++;
            }
            for(; (respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t'); i++);      //跳过空格、制表符
        }
        j++;
    }
    int m=0;
    for(int i=0; i<100; i++)
        for(int j=0; j<8; j++) {
            q[m]=QString::fromStdString(stuCheck[i][j]);             //把数据传入QString数组中
            m++;
        }
    return j;                                           //返回行数
}

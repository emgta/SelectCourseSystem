#include "graphic_client_interface.hpp"
#include "info_to_str.h"


int change_info_to_str(clientRespon &respon,QString *q[],int input) {
    int i=0,j=0,n=0;
    std::string stuCheck[10][8]= {};                       //创建string二维数组
    if(input==1) {
        for(i=0; respon.data.recv_info[i]!='\0'; i++) {            //判断字符数组是否结束
            while(n<4) {                                        //跳过前n行数据
                while((respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t')||(respon.data.recv_info[i]=='\n')) {
                    i++;
                }                                               //跳过开头的空格、制表符、换行符
                while(respon.data.recv_info[i]!='\n') {
                    i++;
                }
                n++;                                            //跳过每一行数据
            }
            if(j==0)//钟健更改
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

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //把数据传入QString数组中

        return j;                                           //返回行数
    } else if(input==2) {
        for(i=0; respon.data.recv_info[i]!='\0'; i++) {            //判断字符数组是否结束

            for(int k=0; respon.data.recv_info[i]!='\n'; k++) { //开始将数据放入

                while((respon.data.recv_info[i]!=' ')&&(respon.data.recv_info[i]!='\t')&&(respon.data.recv_info[i]!='\n')) {
                    stuCheck[j][k].push_back(respon.data.recv_info[i]);             //将字符压入string
                    i++;
                }
                for(; (respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t'); i++);      //跳过空格、制表符
            }
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //把数据传入QString数组中

        return j;
    } else if(input==3) {
        for(i=0; respon.data.recv_info[i]!='\0'; i++) {            //判断字符数组是否结束
            while(n<3) {                                        //跳过前n行数据
                while((respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t')||(respon.data.recv_info[i]=='\n')) {
                    i++;
                }                                               //跳过开头的空格、制表符、换行符
                while(respon.data.recv_info[i]!='\n') {
                    i++;
                }
                n++;                                            //跳过每一行数据
            }
            if(j==0)//钟健更改
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

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //把数据传入QString数组中

        return j;                                           //返回行数
    } else if(input==5) {
        while(j<4) {                                        //跳过前n行数据
            while(respon.data.recv_info[i]!='\n') {
                stuCheck[j][0].push_back(respon.data.recv_info[i]);             //将字符压入string
                i++;
            }
            i++;
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //把数据传入QString数组中

        return j;
    }

    else if(input==6) {
        while(j<3) {                                        //跳过前n行数据
            while(respon.data.recv_info[i]!='\n') {
                stuCheck[j][0].push_back(respon.data.recv_info[i]);             //将字符压入string
                i++;
            }
            i++;
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //把数据传入QString数组中

        return j;
    }

    else
        return 0;
}


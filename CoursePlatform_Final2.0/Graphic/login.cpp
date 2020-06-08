#include "login.h"
#include "ui_login.h"
#include "graphic_client_interface.hpp"
#include <QString>
#include <QDebug>

Login::Login(QWidget *parent) : QDialog(parent)
    ,ui(new Ui::Login) {
    ui->setupUi(this);

    connect(ui->change_to_register_button,
            &QPushButton::clicked,
            this,&Login::change_to_register);

    connect(&subwin,&RegisterDialog::changewinSignal
            ,this,&Login::dealRegister);

    connect(ui->LoginButton,
            &QPushButton::clicked,
            this,&Login::dealLogin);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("登录界面"));

}


void Login::change_to_register() {
    subwin.show();
    this->hide();

    //点击其他的切换界面清除原来所有的输入信息
    ui->username->clear();
    ui->password->clear();
}

void Login::dealRegister() {
    subwin.hide();
    this->show();

    //点击其他的切换界面清除原来所有的输入信息
    ui->username->clear();
    ui->password->clear();
}

void Login::dealLogin() { //处理登录的响应函数
    //获取行编辑器的用户名和密码
    QString username = ui->username->text();
    QString password = ui->password->text();

    clientRespon respon;

    if(ui->Login_type->currentIndex()==0) {
        User_login(isStudent, username, password, respon);
        if(respon.rp == RECV_ERR) { //登录不成功
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名和密码不正确"));
        } else {
            stu_win.show();
            this->hide();
            QMessageBox::information(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("登录成功"));
        }
    } else {
        User_login(isTeacher, username, password, respon);
        if(respon.rp == RECV_ERR) { //登录不成功
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或者密码不正确"));
        } else {
            teacher_win.show();
            this->hide();
            QMessageBox::information(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("登录成功"));
        }
    }
}


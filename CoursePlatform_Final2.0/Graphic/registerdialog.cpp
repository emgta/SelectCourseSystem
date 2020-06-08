#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "graphic_client_interface.hpp"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog) {
    ui->setupUi(this);

    connect(ui->change_login_button,
            &QPushButton::clicked,
            this,&RegisterDialog::send_login_Slot);

    //处理注册按钮的事件
    connect(ui->registerButton,
            &QPushButton::clicked,
            this,&RegisterDialog::deal_register);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("更改密码界面"));



}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::send_login_Slot() {
    emit changewinSignal();

    //点击其他的切换界面清除原来所有的输入信息
    ui->usernameEdit->clear();
    ui->ordinarypasswordEdit->clear();
    ui->currentpasswordEdit->clear();

}

void RegisterDialog::deal_register() {
    //获取行编辑器的用户名、名字和密码
    QString username = ui->usernameEdit->text();
    QString cur_password = ui->ordinarypasswordEdit->text();
    QString new_password = ui->currentpasswordEdit->text();

    clientRespon respon;

    if(ui->typeBox->currentIndex()==0) {
        Modify_passwd(isStudent, username, cur_password,new_password,respon);
        if(respon.rp == RECV_ERR) { //改密不成功
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或密码不正确"));
        } else {
            QMessageBox::information(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("改密成功"));
        }
    } else {
        Modify_passwd(isTeacher, username,cur_password,new_password,respon);
        if(respon.rp == RECV_ERR) { //改密不成功
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或者密码不正确"));
        } else {
            QMessageBox::information(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("改密成功"));
        }
    }


}

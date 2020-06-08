#include "ipaddlogin.h"
#include "ui_ipaddlogin.h"
#include "graphic_client_interface.hpp"

IpaddLogin::IpaddLogin(QWidget *parent) : QWidget(parent),ui(new Ui::IpaddLogin) {
    ui->setupUi(this);

    connect(ui->connectButton,&QPushButton::clicked,
            this,&IpaddLogin::deal_connect_login);//处理连接

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("连接到服务器界面"));


}

void IpaddLogin::deal_connect_login() {
    QString ipadd = ui->ipaddress->text();
    QString port = ui->portnum->text();

    if(!network_init(ipadd.toStdString(), port.toInt())) {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("连接无服务器失败！"));
        return;
    }

    this->hide();
    loginwin.show();
}

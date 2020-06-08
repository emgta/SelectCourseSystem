#ifndef IPADDLOGIN_H
#define IPADDLOGIN_H

#include <QWidget>
#include<QPushButton>
#include <QString>
#include <QDebug>
#include "login.h"

namespace Ui {
class IpaddLogin;
}

class IpaddLogin : public QWidget {
    Q_OBJECT
public:
    explicit IpaddLogin(QWidget *parent = nullptr);

    void deal_connect_login();


private:
    Ui::IpaddLogin *ui;
    Login loginwin;

signals:

public slots:
};

#endif // IPADDLOGIN_H

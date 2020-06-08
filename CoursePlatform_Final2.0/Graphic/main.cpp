#include "registerdialog.h"
#include "login.h"
#include "ipaddlogin.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    IpaddLogin w;
    w.show();
    return a.exec();
}

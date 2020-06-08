#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include "registerdialog.h"
#include "studentmain.h"
#include "teachermain.h"

namespace Ui {
class Login;
}

class Login : public QDialog {
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);

    void change_to_register();
    void dealRegister();
    void dealLogin();

private:
    Ui::Login *ui;
    RegisterDialog subwin;
    StudentMain stu_win;
    TeacherMain teacher_win;

signals:

public slots:
};

#endif // LOGIN_H

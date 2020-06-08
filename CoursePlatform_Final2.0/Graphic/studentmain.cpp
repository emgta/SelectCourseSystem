#include "studentmain.h"
#include "ui_studentmain.h"

StudentMain::StudentMain(QWidget *parent) : QMainWindow(parent),ui(new Ui::StudentMain) {
    ui->setupUi(this);

    //切换到学生的各功能区界面
    connect(ui->stu_check_button,
            &QPushButton::clicked,
            this,&StudentMain::change_to_stu_check);//切换到查看界面

    connect(ui->stu_cancel_button,
            &QPushButton::clicked,
            this,&StudentMain::change_to_stu_cancel);//切换到取消界面

    connect(ui->stu_select_button,
            &QPushButton::clicked,
            this,&StudentMain::change_to_stu_select);//切换到选课界面

    connect(ui->stu_percheck_button,
            &QPushButton::clicked,
            this,&StudentMain::change_to_stu_percheck);//切换到查询个人信息界面


    //处理从子窗口的请求返回主界面信号
    connect(&stu_check_win,&Stu_Check::change_check_win_Signal
            ,this,&StudentMain::deal_Check);
    connect(&stu_cancel_win,&Stu_Cancel::change_to_cancel_Signal
            ,this,&StudentMain::deal_Cancel);
    connect(&stu_select_win,&Stu_Select::change_select_win_Signal
            ,this,&StudentMain::deal_Select);
    connect(&stu_percheck_win,&Stu_Percheck::change_to_percheck_Signal
            ,this,&StudentMain::deal_Percheck);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("学生主界面"));





}

void StudentMain::change_to_stu_check() {
    this->hide();
    stu_check_win.show();

}

void StudentMain::change_to_stu_cancel() {
    this->hide();
    stu_cancel_win.show();

}

void StudentMain::change_to_stu_select() {
    this->hide();
    stu_select_win.show();

}

void StudentMain::change_to_stu_percheck() {
    this->hide();
    stu_percheck_win.show();
}

void StudentMain::deal_Check() {
    this->show();
    stu_check_win.hide();
}

void StudentMain::deal_Cancel() {
    this->show();
    stu_cancel_win.hide();
}

void StudentMain::deal_Select() {
    this->show();
    stu_select_win.hide();
}

void StudentMain::deal_Percheck() {
    this->show();
    stu_percheck_win.hide();
}

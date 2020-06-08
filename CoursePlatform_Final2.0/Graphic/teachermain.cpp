#include "teachermain.h"
#include "ui_teachermain.h"

TeacherMain::TeacherMain(QWidget *parent) : QMainWindow(parent)
    ,ui(new Ui::TeacherMain) {
    ui->setupUi(this);

    //切换到教师各功能区界面
    connect(ui->tea_check_button,
            &QPushButton::clicked,
            this,&TeacherMain::change_to_tea_check);//切换到查看界面

    connect(ui->tea_change_button,
            &QPushButton::clicked,
            this,&TeacherMain::change_to_tea_change);//切换到更改成绩界面
    connect(ui->tea_percheck_button,
            &QPushButton::clicked,
            this,&TeacherMain::change_to_tea_percheck);//切换到查看个人信息界面

    //处理子窗口的切换回主界面请求
    connect(&tea_check_win,&Tea_Check::change_checkwin_Signal,
            this,&TeacherMain::deal_Check);
    connect(&tea_change_win,&Tea_Change::change_changewin_Signal,
            this,&TeacherMain::deal_Change);
    connect(&tea_percheck_win,&Tea_Percheck::change_to_percheck_Signal,
            this,&TeacherMain::deal_Percheck);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("教师主界面"));


}

void TeacherMain::change_to_tea_check() {
    this->close();
    tea_check_win.show();

}

void TeacherMain::change_to_tea_change() {
    this->hide();
    tea_change_win.show();

}

void TeacherMain::change_to_tea_percheck() {
    this->hide();
    tea_percheck_win.show();
}

void TeacherMain::deal_Check() {
    this->show();
    tea_check_win.close();
}

void TeacherMain::deal_Change() {
    this->show();
    tea_change_win.hide();
}

void TeacherMain::deal_Percheck() {
    this->show();
    tea_percheck_win.hide();
}

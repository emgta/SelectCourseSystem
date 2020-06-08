#include "stu_check.h"
#include "ui_stu_check.h"
#include "graphic_client_interface.hpp"
#include <QDebug>
#include <QString>
#include "info_to_str.h"


Stu_Check::Stu_Check(QWidget *parent) : QWidget(parent),ui(new Ui::Stu_Check) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格

    //给主窗口发送返回信号
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Stu_Check::send_check_Slot);

    //连接查询按钮和事件
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Stu_Check::check_information);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("学生查看选课信息界面"));

}

void Stu_Check::send_check_Slot() {
    emit change_check_win_Signal();

    //点返回清除表格内容
    ui->tableWidget->clearContents();
}

void Stu_Check::check_information() {
    //设置行数
    //ui->tableWidget->setRowCount(20);
    //设置列数
    //ui->tableWidget->setColumnCount();

    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //声明Qstring数组
    QString **q =new QString *[10];//假定最多一百行
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//申请空间

    int input = STU_CHECK;
    int rows = change_info_to_str(respon,q,input);
    ui->tableWidget->setRowCount(rows-1);

    for(int i = 0; i < rows-1; i++) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][4]));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][2]));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][5]));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(q[i][6]));
    }

    //释放空间
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;




}

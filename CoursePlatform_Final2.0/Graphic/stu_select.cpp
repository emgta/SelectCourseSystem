#include "stu_select.h"
#include "ui_stu_select.h"
#include "graphic_client_interface.hpp"
#include <QDebug>
#include "info_to_str.h"


Stu_Select::Stu_Select(QWidget *parent) : QWidget(parent),ui(new Ui::Stu_Select) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格

    //给主窗口发送返回信号
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Stu_Select::send_select_Slot);

    //查询可选课程
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Stu_Select::search_section);
    //选课
    connect(ui->selectButton_2,
            &QPushButton::clicked,
            this,&Stu_Select::select_section);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("学生选课界面"));

}

void Stu_Select::send_select_Slot() {
    emit change_select_win_Signal();

    //点返回清除表格和输入框内容
    ui->tableWidget->clearContents();
    ui->sectionnumEdit->clear();
}

void Stu_Select::search_section() {
    //设置行数
    ui->tableWidget->setRowCount(20);
    //设置列数
    //ui->tableWidget->setColumnCount();

    clientRespon respon;
    Get_elective_course(respon);

    //声明Qstring数组
    QString **q =new QString *[10];//假定最多一百行
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//申请空间

    int input = STU_SELECT;
    int rows = change_info_to_str(respon,q,input);
    ui->tableWidget->setRowCount(rows-1);

    for(int i = 0; i < rows-1; i++) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][2]));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][4]));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][5]));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(q[i][6]));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(q[i][3]));
    }

    //释放空间
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;

}

void Stu_Select::select_section() {
    //获取想要选择的课程号
    QString sectionnum = ui->sectionnumEdit->text();

    clientRespon respon;
    Attend_course(sectionnum, respon);

    if(respon.rp == RECV_ERR) { //设置弹出框
        QMessageBox::warning(this,QString::fromLocal8Bit("课程号错误"),respon.data.recv_info);
    } else {
        QMessageBox::information(this,QString::fromLocal8Bit("选课成功"),respon.data.recv_info);
    }
}

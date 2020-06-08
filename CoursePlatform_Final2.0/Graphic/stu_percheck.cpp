#include "stu_percheck.h"
#include "ui_stu_percheck.h"
#include "info_to_str.h"

Stu_Percheck::Stu_Percheck(QWidget *parent) : QWidget(parent),ui(new Ui::Stu_Percheck) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格

    //返回到主界面
    connect(ui->returnButton,&QPushButton::clicked,
            this,&Stu_Percheck::send_percheck_Slot);

    //点击查询后生成个人信息
    connect(ui->searchButton,&QPushButton::clicked,
            this,&Stu_Percheck::check_personalinfo);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("学生查看个人信息界面"));

}

void Stu_Percheck::send_percheck_Slot() {
    emit change_to_percheck_Signal();

    //点返回清除表格内容
    ui->tableWidget->clearContents();
}

void Stu_Percheck::check_personalinfo() {
    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //声明Qstring数组
    QString **q =new QString *[10];//假定最多一百行
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//申请空间

    int input = STU_PERCHECK;
    int rows = change_info_to_str(respon,q,input);

    ui->tableWidget->setRowCount(rows);

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::fromLocal8Bit("姓名")));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem(QString::fromLocal8Bit("学号")));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem(QString::fromLocal8Bit("班级号")));
    ui->tableWidget->setItem(3,0,new QTableWidgetItem(QString::fromLocal8Bit("学院")));

    for(int i = 0; i < rows; i++) {
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][0]));
    }

    //释放空间
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;

}

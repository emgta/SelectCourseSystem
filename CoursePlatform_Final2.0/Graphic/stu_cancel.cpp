#include "stu_cancel.h"
#include "ui_stu_cancal.h"
#include "graphic_client_interface.hpp"
#include <QDebug>
#include "info_to_str.h"

Stu_Cancel::Stu_Cancel(QWidget *parent) : QWidget(parent),ui(new Ui::Stu_Cancel) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格

    //给主窗口发送返回信号
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Stu_Cancel::send_cancel_Slot);

    //查询所有的已选课程
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Stu_Cancel::search_section);

    //输入想取消的课程号并退出
    connect(ui->cancelButton,
            &QPushButton::clicked,
            this,&Stu_Cancel::cancel_section);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("学生取消选课界面"));


}

void Stu_Cancel::send_cancel_Slot() {
    emit change_to_cancel_Signal();

    ui->tableWidget->clearContents();
    ui->sectionnumEdit->clear();
}

void Stu_Cancel::search_section() {
    //设置行数
    ui->tableWidget->setRowCount(20);

    clientRespon respon;

    //TODO: 补充排序模式
    Get_info(INCREASE_BY_SCORE, respon);
    qDebug() << respon.data.recv_info;

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
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][2]));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][4]));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][6]));
    }

    //释放空间
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;

}

void Stu_Cancel::cancel_section() {
    //获取想要取消的课程号
    QString sectionnum = ui->sectionnumEdit->text();

    clientRespon respon;
    Cancel_course(sectionnum, respon);

    if(respon.rp == RECV_ERR) { //设置弹出框
        QMessageBox::warning(this,QString::fromLocal8Bit("课程号错误"),respon.data.recv_info);
    } else {
        QMessageBox::information(this,QString::fromLocal8Bit("成功"),respon.data.recv_info);
    }
}








#include "tea_check.h"
#include "ui_tea_check.h"
#include "graphic_client_interface.hpp"
#include "info_to_str.h"

Tea_Check::Tea_Check(QWidget *parent) : QWidget(parent),ui(new Ui::Tea_Check) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格
    ui->sectiontableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格

    //发送返回主窗口信号
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Tea_Check::send_check_Slot);

    //查看该教师名下所有同学的成绩
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Tea_Check::search_all_info);
    //筛选成绩
    connect(ui->dressButton,
            &QPushButton::clicked,
            this,&Tea_Check::search_dress_info);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("教师查看学生成绩界面"));



}

void Tea_Check::send_check_Slot() {
    emit change_checkwin_Signal();

    //点击返回清除页面所有输入信息
    ui->tableWidget->clearContents();
    ui->sectionnumEdit->clear();
    ui->sectiontableWidget->clear();
}

void Tea_Check::search_all_info() {
    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //声明Qstring数组
    QString **q =new QString *[10];//假定最多一百行
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//申请空间

    int input = TEA_CHECK;
    int rows = change_info_to_str(respon,q,input);
    ui->sectiontableWidget->setRowCount(rows-1);


    //qDebug()<<q[0][0];


    for(int i = 0; i < rows-1; i++) {
        ui->sectiontableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->sectiontableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
    }

    //释放空间
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;
}

void Tea_Check::search_dress_info() {
    //获取想要查看的课程号
    QString sectionnum = ui->sectionnumEdit->text();

    clientRespon respon;
    Check_score(sectionnum, INCREASE_BY_SCORE, respon);

    if(respon.rp == RECV_ERR) { //出错设置弹出框
        QMessageBox::warning(this,QString::fromLocal8Bit("课程号错误"),respon.data.recv_info);
    } else { //查询成功
        QMessageBox::information(this,QString::fromLocal8Bit("查询成功!"),QString::fromLocal8Bit("课程号正确!"));

        //声明Qstring数组
        QString **q =new QString *[10];//假定最多一百行
        for(int i = 0; i<10; i++)
            q[i] = new QString[8];//申请空间

        int input = TEA_SELECT;
        int rows = change_info_to_str(respon,q,input);
        ui->tableWidget->setRowCount(rows);


        for(int i = 0; i < rows; i++) {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(q[i][3]));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][0]));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][2]));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][4]));
        }

        //释放空间
        for(int i = 0; i < 10; i++)
            delete []q[i];
        delete []q;
    }
}





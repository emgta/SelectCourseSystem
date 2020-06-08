#include "tea_change.h"
#include "ui_tea_change.h"
#include "graphic_client_interface.hpp"
#include "info_to_str.h"

Tea_Change::Tea_Change(QWidget *parent) : QWidget(parent),ui(new Ui::Tea_Change) {
    ui->setupUi(this);

    ui->sectiontableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格
    ui->scoretableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止用户修改表格

    //发送返回主窗口信号
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Tea_Change::send_change_Slot);

    //查询所教的几个课程的信息
    connect(ui->searchsectionButton,
            &QPushButton::clicked,
            this,&Tea_Change::search_section);
    //查询指定课程下所有学生成绩
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Tea_Change::search_score);
    //改变学生成绩
    connect(ui->confimButton,
            &QPushButton::clicked,
            this,&Tea_Change::change_stu_score);

    //设置左上角图标
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //设置左上角名字
    this->setWindowTitle(QString::fromLocal8Bit("教师更改学生成绩界面"));

}

void Tea_Change::send_change_Slot() {
    emit change_changewin_Signal();

    //点击返回清除页面上所有输入信息
    ui->sectiontableWidget->clearContents();
    ui->scoretableWidget->clearContents();
    ui->sectionnumEdit->clear();
    ui->stunumEdit->clear();
    ui->stuscorceEdit->clear();
}

void Tea_Change::search_section() {
    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //声明Qstring数组
    QString **q =new QString *[10];//假定最多一百行
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//申请空间

    int input = TEA_CHECK;
    int rows = change_info_to_str(respon,q,input);
    ui->sectiontableWidget->setRowCount(rows-1);

    for(int i = 0; i < rows-1; i++) {
        ui->sectiontableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->sectiontableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
        ui->sectiontableWidget->setItem(i,2,new QTableWidgetItem(q[i][2]));
        ui->sectiontableWidget->setItem(i,3,new QTableWidgetItem(q[i][3]));
        ui->sectiontableWidget->setItem(i,4,new QTableWidgetItem(q[i][4]));
        ui->sectiontableWidget->setItem(i,5,new QTableWidgetItem(q[i][5]));
    }

    //释放空间
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;
}

void Tea_Change::search_score() {
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
        ui->scoretableWidget->setRowCount(rows);


        for(int i = 0; i < rows; i++) {
            ui->scoretableWidget->setItem(i,0,new QTableWidgetItem(q[i][1]));
            ui->scoretableWidget->setItem(i,1,new QTableWidgetItem(q[i][0]));
            ui->scoretableWidget->setItem(i,2,new QTableWidgetItem(q[i][4]));
        }

        //释放空间
        for(int i = 0; i < 10; i++)
            delete []q[i];
        delete []q;
    }
}

void Tea_Change::change_stu_score() {
    //获取想要更改的课程号,学生学号成绩
    QString sectionnum = ui->sectionnumEdit->text();
    QString stu_no = ui->stunumEdit->text();
    QString stu_score = ui->stuscorceEdit->text();

    clientRespon respon;
    Modify_score(sectionnum, stu_no, stu_score, respon);

    if(respon.rp == RECV_ERR) { //设置出错弹出框
        QMessageBox::warning(this,QString::fromLocal8Bit("输入错误!"),respon.data.recv_info);
    } else { //成功
        QMessageBox::information(this,QString::fromLocal8Bit("修改成功!"),QString::fromLocal8Bit("更改成绩成功!"));
    }
}

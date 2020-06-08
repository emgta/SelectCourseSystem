#ifndef STUDENTMAIN_H
#define STUDENTMAIN_H

#include <QMainWindow>
#include "stu_cancel.h"
#include "stu_check.h"
#include "stu_select.h"
#include "stu_percheck.h"

namespace Ui {
class StudentMain;
}

class StudentMain : public QMainWindow {
    Q_OBJECT
public:
    explicit StudentMain(QWidget *parent = nullptr);

    void change_to_stu_cancel();
    void change_to_stu_check();
    void change_to_stu_select();
    void change_to_stu_percheck();

    void deal_Cancel();
    void deal_Check();
    void deal_Select();
    void deal_Percheck();


private:
    Ui::StudentMain *ui;
    Stu_Cancel stu_cancel_win;
    Stu_Check stu_check_win;
    Stu_Select stu_select_win;
    Stu_Percheck stu_percheck_win;


signals:

public slots:
};

#endif // STUDENTMAIN_H

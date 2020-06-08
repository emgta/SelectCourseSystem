#ifndef TEACHERMAIN_H
#define TEACHERMAIN_H

#include <QMainWindow>
#include "tea_change.h"
#include "tea_check.h"
#include "tea_percheck.h"


namespace Ui {
class TeacherMain;
}

class TeacherMain : public QMainWindow {
    Q_OBJECT
public:
    explicit TeacherMain(QWidget *parent = nullptr);

    void change_to_tea_check();
    void change_to_tea_change();
    void change_to_tea_percheck();
    void deal_Change();
    void deal_Check();
    void deal_Percheck();

private:
    Ui::TeacherMain *ui;
    Tea_Check tea_check_win;
    Tea_Change tea_change_win;
    Tea_Percheck tea_percheck_win;


signals:

public slots:
};

#endif // TEACHERMAIN_H

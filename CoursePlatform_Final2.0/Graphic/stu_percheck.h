#ifndef STU_PERCHECK_H
#define STU_PERCHECK_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Stu_Percheck;
}

class Stu_Percheck : public QWidget {
    Q_OBJECT
public:
    explicit Stu_Percheck(QWidget *parent = nullptr);

    void send_percheck_Slot();
    void check_personalinfo();


signals:
    void change_to_percheck_Signal();

private:
    Ui::Stu_Percheck *ui;


signals:

public slots:
};

#endif // STU_PERCHECK_H

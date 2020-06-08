#ifndef STU_CHECK_H
#define STU_CHECK_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class Stu_Check;
}

class Stu_Check : public QWidget {
    Q_OBJECT
public:
    explicit Stu_Check(QWidget *parent = nullptr);

    void send_check_Slot();
    void check_information();

signals:
    void change_check_win_Signal();

private:
    Ui::Stu_Check *ui;
signals:

public slots:
};

#endif // STU_CHECK_H

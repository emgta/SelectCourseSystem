#ifndef STU_SELECT_H
#define STU_SELECT_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Stu_Select;
}

class Stu_Select : public QWidget {
    Q_OBJECT
public:
    explicit Stu_Select(QWidget *parent = nullptr);

    void send_select_Slot();
    void search_section();
    void select_section();

signals:
    void change_select_win_Signal();

private:
    Ui::Stu_Select *ui;
signals:

public slots:
};

#endif // STU_SELECT_H

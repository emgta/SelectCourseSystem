#ifndef STU_CANCEL_H
#define STU_CANCEL_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Stu_Cancel;
}

class Stu_Cancel : public QWidget {
    Q_OBJECT
public:
    explicit Stu_Cancel(QWidget *parent = nullptr);

    void send_cancel_Slot();
    void search_section();
    void cancel_section();

signals:
    void change_to_cancel_Signal();

private:
    Ui::Stu_Cancel *ui;

signals:

public slots:
};

#endif // STU_CANCEL_H

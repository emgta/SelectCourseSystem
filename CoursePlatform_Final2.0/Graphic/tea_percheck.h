#ifndef TEA_PERCHECK_H
#define TEA_PERCHECK_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Tea_Percheck;
}

class Tea_Percheck : public QWidget {
    Q_OBJECT
public:
    explicit Tea_Percheck(QWidget *parent = nullptr);

    void send_percheck_Slot();
    void check_personalinfo();

signals:
    void change_to_percheck_Signal();

private:
    Ui::Tea_Percheck *ui;

signals:

public slots:
};

#endif // TEA_PERCHECK_H

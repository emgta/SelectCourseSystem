#ifndef TEA_CHECK_H
#define TEA_CHECK_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Tea_Check;
}

class Tea_Check : public QWidget {
    Q_OBJECT
public:
    explicit Tea_Check(QWidget *parent = nullptr);

    void send_check_Slot();
    void search_all_info();
    void search_dress_info();

signals:
    void change_checkwin_Signal();

private:
    Ui::Tea_Check *ui;

signals:

public slots:
};

#endif // TEA_CHECK_H

#ifndef TEA_CHANGE_H
#define TEA_CHANGE_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Tea_Change;
}

class Tea_Change : public QWidget {
    Q_OBJECT
public:
    explicit Tea_Change(QWidget *parent = nullptr);

    void send_change_Slot();
    void search_section();
    void search_score();
    void change_stu_score();

signals:
    void change_changewin_Signal();

private:
    Ui::Tea_Change *ui;

signals:

public slots:
};

#endif // TEA_CHANGE_H

#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include<QPushButton>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "graphic_client_interface.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class RegisterDialog;
}
QT_END_NAMESPACE

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

    void send_login_Slot();
    void deal_register();

signals:
    void changewinSignal();

private:
    Ui::RegisterDialog *ui;

};
#endif // REGISTERDIALOG_H

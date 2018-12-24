#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    QString Login, Haslo;
    ~LoginDialog();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H

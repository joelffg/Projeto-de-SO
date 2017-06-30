#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    DialogLogin(MainWindow *mwp, QWidget *parent = 0);
    ~DialogLogin();

    MainWindow* mw;

private slots:
    map<int, string> getTurmasDocente(string username, string password);
    void on_pushButton_clicked();

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H

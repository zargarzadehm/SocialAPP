#ifndef SIGNINANDSIGNUP_H
#define SIGNINANDSIGNUP_H
#include "signin.h"
#include "signup.h"

#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QAction>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>

namespace Ui {
class signinandsignup;
}

class signinandsignup : public QMainWindow
{
    Q_OBJECT

public:
    explicit signinandsignup(QMainWindow*p, QWidget *parent = 0);
    ~signinandsignup();

private slots:
    void on_Signin_clicked();

    void on_Signup_clicked();

    void on_Close_clicked();

private:
    Ui::signinandsignup *ui;
    QLabel *status;
    Signin *signin;
    Signup *signup;
};

#endif // SIGNINANDSIGNUP_H

#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QAction>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>

namespace Ui {
class Signin;
}

class Signin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = 0);
    ~Signin();

private:
    Ui::Signin *ui;
};

#endif // SIGNIN_H

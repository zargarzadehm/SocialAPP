#include "signinandsignup.h"
#include "ui_signinandsignup.h"
#include "mainwindow.h"

signinandsignup::signinandsignup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signinandsignup)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
    QLabel *status = new QLabel();
    status ->setText("Select Sign In  or Sign Up");
    ui->statusbar->addWidget(status);

}

signinandsignup::~signinandsignup()
{
    delete ui;
}

void signinandsignup::on_Signin_clicked()
{
    Signin *s = new Signin;
    //this-> hide();
    //signin -> show();
    ui->statusbar->close();
    setCentralWidget(s);
}

void signinandsignup::on_Signup_clicked()
{
    Signup* s = new Signup;
    //this-> hide();
   // signup -> show();
    ui->statusbar->close();
    setCentralWidget(s);
}

void signinandsignup::on_Close_clicked()
{
    //this->close();
    MainWindow *s =new MainWindow;
    ui->statusbar->close();
    setCentralWidget(s);
}

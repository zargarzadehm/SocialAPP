#include "signinandsignup.h"
#include "ui_signinandsignup.h"
#include "mainwindow.h"

signinandsignup::signinandsignup(QMainWindow *p, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signinandsignup)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
    status = new QLabel();
    status ->setText("Select Sign In  or Sign Up");
    ui->statusbar->addWidget(status);
    connect(ui->Close , SIGNAL(clicked(bool)) , p , SLOT(close()));

}

signinandsignup::~signinandsignup()
{
    delete ui;
//    this->close();
}

void signinandsignup::on_Signin_clicked()
{
    signin = new Signin;
    //this-> hide();
    //signin -> show();
    ui->statusbar->close();
    setCentralWidget(signin);
}

void signinandsignup::on_Signup_clicked()
{
    signup = new Signup;
    QTimer* timer = new QTimer();
    connect(timer , SIGNAL(timeout()) , signup , SLOT(run()));
    timer->start(500);

    ui->statusbar->close();

    setCentralWidget(signup);
//    checkConnection *th1 =new checkConnection(signup);
//    th1->start();
}


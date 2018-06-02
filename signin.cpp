#include "signin.h"
#include "ui_signin.h"

Signin::Signin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);

    setWindowTitle("Sign In");
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));

    QLabel *status = new QLabel();
    status ->setText("Enter your username and password");
    ui->statusbar->addWidget(status);
}

Signin::~Signin()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QString token;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Messenger KING & KOALA");
    movie = new QMovie("/home/moein/QTProjects/SocialAPP/coollogo_com-23433320.gif");
    processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    processLabel->setGeometry(130,5,500,250);
    movie->start();

    status = new QLabel();
    status ->setText("Welcome to our messenger");

    ui->statusbar->addWidget(status);

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

MainWindow::~MainWindow()
{
    ui->statusbar->close();
    delete ui;
    delete processLabel;
    delete status;
    delete movie;
    delete s;
}

void MainWindow::on_STARTAPP_clicked()
{
        s = new signinandsignup(this);
        setCentralWidget(s);
        processLabel->clear();
        ui->statusbar->close();
}


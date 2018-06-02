#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Messenger KING & KOALA");
    QMovie *movie = new QMovie("/home/moein/QTProjects/SocialAPP/coollogo_com-23433320.gif");
    processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    processLabel->setGeometry(130,5,500,250);
    movie->start();

    QLabel *status = new QLabel();
    status ->setText("Welcome to our messenger");
    ui-> statusBar->addWidget(status);

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_STARTAPP_clicked()
{
   // s = new signinandsignup (this);
    //this-> hide();
    signinandsignup* s = new signinandsignup;
    setCentralWidget(s);
    processLabel->clear();
    ui->statusBar->close();

}


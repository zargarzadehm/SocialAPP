#include "interface.h"
#include "ui_interface.h"
#include "confirmlogout.h"
#include "mainwindow.h"
#include "send_user.h"
#include "send_group.h"
#include "send_channel.h"

extern int flag1;
extern QString token;
interface::interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface)
{
    setWindowTitle("Messenger KING & KOALA");
    this->setStyleSheet("background-color: rgb(211, 215, 207);");
    ui->setupUi(this);
    QTabWidget* tab = new QTabWidget;
    ui->horizentsl->addWidget(tab);
    send_user* Send_user = new send_user;
    send_group* Send_group = new send_group;
    send_channel* Send_channel = new send_channel;
    tab->addTab(Send_user,"Users");
    tab->addTab(Send_group,"Groups");
    tab->addTab(Send_channel,"Channels");

    QTimer* timer = new QTimer();
    connect(timer , SIGNAL(timeout()) , this , SLOT(run()));
    timer->start(500);

    status = new QLabel();

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

interface::~interface()
{
    delete ui;
    delete reply;
    delete status;
}
void interface::run()
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    reply = nam.get(req);
    QEventLoop loop;

    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
    loop.exec();

    if(reply->bytesAvailable())
    {
        status->setText("You are connected to the internet :)");
        ui->statusbar->addWidget(status);
    }
    else
       {
        status->setText("You are not connected to the internet :)");
        ui->statusbar->addWidget(status);

    }
}
void interface::on_actionCreate_Group_triggered()
{
    creategroup* x = new creategroup;
    x->show();
}

void interface::on_actionCreate_Channel_triggered()
{
    createchannel* x = new createchannel;
    x->show();
}

void interface::on_actionLog_out_triggered()
{
    confirmlogout x;
    x.exec();

    if(flag1==1)
    {
        flag1 = 0;
        MainWindow *main = new MainWindow;
        this->hide();
        setCentralWidget(main);
    }
}



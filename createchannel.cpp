#include "createchannel.h"
#include "ui_createchannel.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "interface.h"

extern QString token;
createchannel::createchannel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::createchannel)
{
    setWindowTitle("Messenger KING & KOALA");
    this->setStyleSheet("background-color: rgb(211, 215, 207);");
    ui->setupUi(this);
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(manage(QNetworkReply*)));
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

createchannel::~createchannel()
{
    delete ui;
}

// api : http://api.softserver.org:1104/createchannel?token=7a3c48f7c7939b7269d01443a431825f&channel_name=mine&channel_title=mine;

void createchannel::manage(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument x = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject y= x.object();
    QMessageBox* z = new QMessageBox;
    qDebug()<<y["code"];
    if(y["code"]=="200"){
        z->setText("channel created successfully !");
        z->show();
        this->close();
    }
    else if (y["code"]=="204"){
        z->setText("channel name or title already exist\nplease try again");
        z->show();
    }
    else if (y["code"]=="401"){
        z->setText("a basical error!");
        z->show();
    }

}

void createchannel::on_cancel_clicked()
{
    this->close();
}

void createchannel::on_create_channel_clicked()
{
    QMessageBox* z = new QMessageBox;
    if (ui->lineEdit_2->text()==NULL){
        z->setText("please enter the channel title and try again");
        z->show();
    }
    else if (ui->lineEdit->text()==NULL){
        z->setText("please enter the channel name and try again");
    }
    else{
    QString api = "http://api.softserver.org:1104/createchannel?token=" + token + "&channel_name=" + ui->lineEdit->text() + "&channel_title=" + ui->lineEdit_2->text();
    request.setUrl(QUrl(api));
    manager->get(request);
    }
}

#include "send_channel.h"
#include "ui_send_channel.h"

extern QString token;

send_channel::send_channel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send_channel)
{
    tedad1 = 0;
    tedad2 = 0;
    tedad_chat = 0;

    ui->setupUi(this);

    manager1 = new QNetworkAccessManager;
    manager2 = new QNetworkAccessManager;
    manager3 = new QNetworkAccessManager;
    manager4 = new QNetworkAccessManager;
    manager5 = new QNetworkAccessManager;

    admin = false;

    ui->text->setStyleSheet("background-color: rgb(186, 189, 182);");

    connect(manager1,SIGNAL(finished(QNetworkReply*)),this,SLOT(managechannels(QNetworkReply*)));
    connect(manager2,SIGNAL(finished(QNetworkReply*)),this,SLOT(getchats(QNetworkReply*)));
    connect(manager4,SIGNAL(finished(QNetworkReply*)),this,SLOT(resault(QNetworkReply*)));
    connect(ui->list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(threadchats(QListWidgetItem*)));
    connect(manager5,SIGNAL(finished(QNetworkReply*)),this,SLOT(check_admin_channel(QNetworkReply*)));

    ui->lineEdit->hide();
    ui->send->hide();

    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(sendapichannel()));
    timer->start(500);

}

send_channel::~send_channel()
{
    delete ui;
    delete manager1;
    delete manager2;
    delete manager3;
    delete manager4;
    delete manager5;
    delete item1;
}

void send_channel::on_search_clicked()
{
    QString api = "http://api.softserver.org:1104/joinchannel?token=" + token + "&channel_name=" +ui->lineEdit_2->text();
    request4.setUrl(QUrl(api));
    manager4->get(request4);
    ui->lineEdit_2->clear();
}

void send_channel::on_send_clicked()
{
    if(ui->lineEdit->text() == NULL){
        QMessageBox* box = new QMessageBox;
        box->setText("please enter the message body");
        box->addButton(QMessageBox::Ok);
        box->show();
    }
    else{
    QString api = "http://api.softserver.org:1104/sendmessagechannel?token=" + token + "&dst=" + channelname + "&body =" + ui->lineEdit->text();
    ui->lineEdit->clear();
    request3.setUrl(QUrl(api));
    manager3->get(request3);
    }
}

void send_channel::sendapichannel(){
    QString api = "http://api.softserver.org:1104/getchannellist?token="+token;
    request1.setUrl(QUrl(api));
    manager1->get(request1);
}

void send_channel::threadchats(QListWidgetItem *item){
    QTimer* timer1 = new QTimer;
    connect(timer1,SIGNAL(timeout()),this,SLOT(send_api_chat()));
    item1 = item;
    send_api_admin();
    ui->lineEdit->hide();
    ui->send->hide();

            ui->text->clear();

            tedad2 =0;

            timer1->start(500);
}

void send_channel::send_api_chat(){
    channelname = item1->text();
    QString api ="http://api.softserver.org:1104/getchannelchats?token=" + token + "&dst=" + channelname;
    request2.setUrl(QUrl(api));
    manager2->get(request2);
}

void send_channel::send_api_admin(){
    channelname = item1->text();
    QString api ="http://api.softserver.org:1104/sendmessagechannel?token=" + token + "&dst=" + channelname + "&body=";
    request5.setUrl(QUrl(api));
    manager5->get(request5);
}

void send_channel::check_admin_channel(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();
    if(map["code"].toString() == "200") admin = true;
}

void send_channel::managechannels(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();

    QString message = map["message"].toString();
    QStringList stringlist = message.split('-');

    int tedad = stringlist[1].toInt();
    QListWidgetItem* item;
    item = new QListWidgetItem[tedad];

    for(int i = tedad1 ; i < tedad ; i++){
        QString string = "block " + QString::number(i);
        QVariantMap block = map[string].toMap();
        QString name = block["channel_name"].toString();
        item[i].setText(name);
        ui->list->addItem(&item[i]);
    }

    tedad1 = tedad;
}


void send_channel::getchats(QNetworkReply *rep){
    if(admin){
    ui->lineEdit->show();
    ui->send->show();
    }
    admin = false;
    QString data = rep->readAll();

    ui->text->setAlignment(Qt::AlignLeft);

    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();

    QString message = map["message"].toString();

    QStringList list = message.split('-');
    int tedad = list[1].toInt();

    tedad_chat = tedad;

    for(int i = tedad2 ; i < tedad ; i++){

        QString string = "block " + QString::number(i);
        QVariantMap block = map[string].toMap();

        ui->text->append(block["body"].toString());

        }
    tedad2=tedad;
}

void send_channel::resault(QNetworkReply *rep){

    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();

    if(map["message"].toString() == "404"){
        auto box = new QMessageBox;
        box->setText("channel not found");
        box->show();
    }
}

#include "send_group.h"
#include "ui_send_group.h"
#include <QTimer>

extern QString token;

QString groupname;
QString User_src;

send_group::send_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send_group)
{
     tedad1 = 0;
     tedad2 = 0;
     tedad_chat = 0;
    ui->setupUi(this);
    ui->lineEdit->hide();
    ui->send->hide();

    manager1 = new QNetworkAccessManager;
    manager2 = new QNetworkAccessManager;
    manager3 = new QNetworkAccessManager;
    manager4 = new QNetworkAccessManager;
    connect(manager1,SIGNAL(finished(QNetworkReply*)),this,SLOT(managegroups(QNetworkReply*)));
    connect(manager2,SIGNAL(finished(QNetworkReply*)),this,SLOT(getchats(QNetworkReply*)));
    connect(ui->list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(threadchat(QListWidgetItem*)));
    connect(manager4,SIGNAL(finished(QNetworkReply*)),this,SLOT(resault(QNetworkReply*)));

    ui->text->setStyleSheet("background-color: rgb(186, 189, 182);");
    ui->text_2->setStyleSheet("background-color: rgb(186, 189, 182);");

    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(sendapigroup()));
    timer->start(500);
}

send_group::~send_group()
{
    delete ui;
    delete manager1;
    delete manager2;
    delete manager3;
    delete item1;
}

void send_group::sendapigroup()
{
    QString api = "http://api.softserver.org:1104/getgrouplist?token="+token;
    request1.setUrl(QUrl(api));
    manager1->get(request1);
}
void send_group::threadchat(QListWidgetItem *item)
{
    QTimer* timer1 = new QTimer;
    connect(timer1,SIGNAL(timeout()),this,SLOT(send_api_chat()));
    item1 = item;

//    if(tedad_chat != 0){

//    }
            ui->text->clear();
            ui->text_2->clear();
            tedad2 =0;
    timer1->start(500);

}
void send_group::send_api_chat(){
    groupname = item1->text();
    QString api ="http://api.softserver.org:1104/getgroupchats?token=" + token + "&dst=" + groupname;
    request2.setUrl(QUrl(api));
    manager2->get(request2);
}

void send_group::managegroups(QNetworkReply *rep){
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
        QString name = block["group_name"].toString();
        item[i].setText(name);
        ui->list->addItem(&item[i]);
    }

    tedad1 = tedad;

}

void send_group::getchats(QNetworkReply *rep){
    ui->lineEdit->show();
    ui->send->show();

    QString data = rep->readAll();

    ui->text->setAlignment(Qt::AlignLeft);
    ui->text_2->setAlignment(Qt::AlignRight);

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

        if(User_src != block["src"].toString()){
            ui->text->append(block["src"].toString()+" : "+block["body"].toString());
            ui->text_2->append("\n");
        }
        else{
            ui->text_2->append(block["body"].toString());
            ui->text->append("\n");
            }
        }
    tedad2=tedad;
}

void send_group::on_send_clicked()
{
    if(ui->lineEdit->text() == NULL){
        QMessageBox* box = new QMessageBox;
        box->setText("please enter the message body");
        box->addButton(QMessageBox::Ok);
        box->show();
    }
    else{
    QString api = "http://api.softserver.org:1104/sendmessagegroup?token=" + token + "&dst=" + groupname + "&body=" + ui->lineEdit->text();
    ui->lineEdit->clear();
    request3.setUrl(QUrl(api));
    manager3->get(request3);
    }
}

void send_group::on_search_clicked()
{
    QString api = "http://api.softserver.org:1104/joingroup?token=" + token + "&group_name=" +ui->lineEdit_2->text();
    request4.setUrl(QUrl(api));
    manager4->get(request4);
}

void send_group::resault(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();

    if(map["message"].toString() == "404"){
        auto box = new QMessageBox;
        box->setText("group not found");
        box->show();
    }
}

#include "send_user.h"
#include "ui_send_user.h"
#include "signin.h"

extern QString token;
//QString karbar;
//QString karbar;
    QString* usernames;
send_user::send_user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send_user)
{
    setWindowTitle("Messenger KING & KOALA");
    tedad1 = 0;
    tedad2 = 0;
    tedad_chat = 0;
    tedad_chat_ha = 0;
    tedad_user_ha = 0;
    ui->setupUi(this);

    ui->lineEdit->hide();
    ui->send->hide();
    ui->text->setStyleSheet("background-color: rgb(186, 189, 182);");
    ui->text_2->setStyleSheet("background-color: rgb(186, 189, 182);");

    /**********************************/
//    QFile file("info/information.txt");
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    QString data = file.readAll();
//    QStringList list = data.split(',');
//    karbar = list[1];
//    file.close();
    /*********************************/

    manager1 = new QNetworkAccessManager;
    manager2 = new QNetworkAccessManager;
    manager3 = new QNetworkAccessManager;
    manager4 = new QNetworkAccessManager;
    manager5 = new QNetworkAccessManager;

    connect(manager1,SIGNAL(finished(QNetworkReply*)),this,SLOT(manageusers(QNetworkReply*)));
    connect(manager2,SIGNAL(finished(QNetworkReply*)),this,SLOT(getchats(QNetworkReply*)));
    connect(ui->list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(threadchat(QListWidgetItem*)));
    connect(manager4,SIGNAL(finished(QNetworkReply*)),this,SLOT(resault(QNetworkReply*)));
    connect(manager5,SIGNAL(finished(QNetworkReply*)),this,SLOT(chat_offline(QNetworkReply*)));

    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(sendapiuser()));
    timer->start(500);

//    QTimer* timer_offline = new QTimer();
//    connect(timer_offline,SIGNAL(timeout()),this,SLOT(api_offline()));
//    timer_offline->start(500);

//    sendapiuser();
}

send_user::~send_user()
{
    delete ui;
    delete manager1;
    delete manager2;
    delete manager3;
    delete manager4;
    delete manager5;
    delete item1;
}

void send_user::sendapiuser()
{
    QString api = "http://api.softserver.org:1104/getuserlist?token="+token;
    request1.setUrl(QUrl(api));
    manager1->get(request1);
}
void send_user::threadchat(QListWidgetItem *item)
{
    QTimer* timer1 = new QTimer;
    connect(timer1,SIGNAL(timeout()),this,SLOT(send_api_chat()));
    item1 = item;

            ui->text->clear();
            ui->text_2->clear();
            tedad2 =0;
    timer1->start(500);

}

void send_user::api_offline(){
    for(int i = 0 ; i < tedad_user_ha ; i++){
        qDebug()<<i;
        QString api = "http://api.softserver.org:1104/getuserchats?token=" + token + "&dst=" + usernames[i];
        request5.setUrl(QUrl(api));
        manager5->get(request5);
    }
}

int j = 0;

void send_user::chat_offline(QNetworkReply *rep){

    QFile file("users/" + usernames[j] + ".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream in(&file);

    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();

    QString message = map["message"].toString();
    QStringList stringlist = message.split('-');

    int tedad = stringlist[1].toInt();

    for(int i = 0 ; i < tedad ; i++){

        QString string = "block " + QString::number(i);
        QVariantMap block = map[string].toMap();

        /************************/

        in<<block["body"].toString()<<","<<block["src"].toString()<<","<<block["dst"].toString()<<endl;

        /************************/
    }
file.close();
j++;
}

//int j = 0;
//for(int i = 0 ; i < tedad_user_ha ; i++){
//user = item1->text();
//QString api ="http://api.softserver.org:1104/getuserchats?token=" + token + "&dst=" + usernames[i];
//request2.setUrl(QUrl(api));
//manager2->get(request2);
//j++;
//}

void send_user::send_api_chat()
{

    user = item1->text();
    QString api ="http://api.softserver.org:1104/getuserchats?token=" + token + "&dst=" + user;
    request2.setUrl(QUrl(api));
    manager2->get(request2);

}

void send_user::manageusers(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();
    QFile file("usernames.txt");

    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream input(&file);

    QString message = map["message"].toString();
    QStringList stringlist = message.split('-');

    int tedad = stringlist[1].toInt();
    tedad_user_ha = tedad;
    QListWidgetItem* item;
    item = new QListWidgetItem[tedad];

    for(int i = tedad1 ; i < tedad ; i++){

        QString string = "block " + QString::number(i);
        QVariantMap block = map[string].toMap();

        item[i].setText(block["src"].toString());

        input<<block["src"].toString()<<endl;


        ui->list->addItem(&item[i]);
    }
    file.close();
    tedad1 = tedad;
}

void send_user::getchats(QNetworkReply *rep){

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

    ////////////////////
    QFile file("users/" + user + ".txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream in(&file);
    //////////////////////////////



    for(int i = tedad2 ; i < tedad ; i++){
        QString username = user;

        QString string = "block " + QString::number(i);
        QVariantMap block = map[string].toMap();

        in<<block["body"].toString()<<","<<block["src"].toString()<<","<<block["dst"].toString()<<endl;

        if(block["body"].toString() != NULL){
            if(username == block["src"].toString()){
                ui->text->append(block["body"].toString());
                ui->text_2->append("\n");
            }
            else{
                ui->text_2->append(block["body"].toString());
                ui->text->append("\n");
                }
        }
    }
file.close();
    tedad2=tedad;

}

void send_user::on_send_clicked()
{
    if(ui->lineEdit->text() == NULL){
        QMessageBox* box = new QMessageBox;
        box->setText("please enter the message body");
        box->addButton(QMessageBox::Ok);
        box->show();
    }
    else{
    QString api = "http://api.softserver.org:1104/sendmessageuser?token=" + token + "&dst=" + user + "&body=" + ui->lineEdit->text();
    ui->lineEdit->clear();
    request3.setUrl(QUrl(api));
    manager3->get(request3);
    }
}

void send_user::on_search_clicked()
{
    QString api = "http://api.softserver.org:1104/sendmessageuser?token=" + token + "&dst=" + ui->lineEdit_2->text() + "&body=";
    request4.setUrl(QUrl(api));
    manager4->get(request4);
}

void send_user::resault(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();

    if(map["message"].toString() == "404"){
        auto box = new QMessageBox;
        box->setText("user not found");
        box->show();
    }
}

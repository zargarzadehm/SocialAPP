#include "creategroup.h"
#include "ui_creategroup.h"
#include "interface.h"

extern QString token;
creategroup::creategroup(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::creategroup)
{
    setWindowTitle("Messenger KING & KOALA");
    this->setStyleSheet("background-color: rgb(211, 215, 207);");
    ui->setupUi(this);
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(manage(QNetworkReply*)));
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

creategroup::~creategroup()
{
    delete ui;
}

// api = http://api.softserver.org:1104/creategroup?token=7a3c48f7c7939b7269d01443a431825f&group_name=ap&group_title=Advance-programming;

void creategroup::manage(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument x = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject y = x.object();
    if(y["code"]=="200"){
        QMessageBox* z = new QMessageBox;
        z->setText("group created successfully !");
        z->show();
        this->close();
    }
    else if(y["code"]=="204"){
        QMessageBox* z = new QMessageBox;
        z->setText("group name or title already exist\nplease try again");
        z->show();
    }
    else if (y["code"]=="401"){
        QMessageBox* z = new QMessageBox;
        z->setText("a basical error!");
        z->show();
    }

}

void creategroup::on_create_group_clicked()
{
    QMessageBox* z = new QMessageBox;
    if(ui->lineEdit->text()==NULL){
        z->setText("please enter the group name and try again");
        z->show();
    }
    else if(ui->lineEdit_2->text()==NULL){
        z->setText("please enter the group title and try again");
        z->show();
    }
    else{
    QString api = "http://api.softserver.org:1104/creategroup?token=" + token + "&group_name=" + ui->lineEdit->text() + "&group_title=" + ui->lineEdit_2->text();
    request.setUrl(QUrl(api));
    manager->get(request);
    }
}


void creategroup::on_cancel_clicked()
{
    this->close();
}

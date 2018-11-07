#include "logout.h"
#include "ui_logout.h"
extern QString token;

logout::logout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logout)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(manage(QNetworkReply*)));
}

logout::~logout()
{
    delete ui;
}

// http://api.softserver.org:1104/logout?username=amirmnoohi&password=1104

void logout::on_pushButton_clicked()
{
    QMessageBox* z = new QMessageBox;
    if(ui->lineEdit->text()==NULL) {
    z->setText("please enter the username first!");
    z->show();
    }
    else if(ui->lineEdit_2->text()==NULL){
    z->setText("please enter your password");
    z->show();
    }
    else if (ui->lineEdit->text()==NULL || ui->lineEdit_2->text()==NULL){
    z->setText("ridi aamoo!");
    z->show();
    }
    else{
    QString api = "http://api.softserver.org:1104/logout?username=" + ui->lineEdit->text() + "&password=" + ui->lineEdit_2->text();
    request.setUrl(QUrl(api));
    manager->get(request);
    }
}

void logout::manage(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument x = QJsonDocument::fromJson(data.toUtf8());
    QMessageBox* z = new QMessageBox;
    QJsonObject y = x.object();
    if(y["code"]=="200") z->setText("logout successfully done!\ngood bye!");
    else if (y["code"]=="401") z->setText("invalid username or password\nplease try again");
    z->show();
    this->close();
}

#include "signin.h"
#include "ui_signin.h"
#include "interface.h"

#include "signinandsignup.h"
#include "send_group.h"

extern QString User_src;
QString token;

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

    ui->usernameLineEdit->setPlaceholderText("Your Username");
    ui->passwordLineEdit->setPlaceholderText("Your Password");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));
}

Signin::~Signin()
{
    delete ui;
}

void Signin::on_SignIn_clicked()
{
    QMessageBox message;
    QString user;

    if(ui->usernameLineEdit->text() == NULL)
    {
        message.setWindowTitle(tr("Sign IN"));
        message.setText(tr("! Please enter your Username !"));
        message.addButton(QMessageBox::Ok);

        message.setStyleSheet("QMessageBox{"
                              "border : 1px solid rgb(255, 0, 0);\n"
                              "border-radius : 10px}"
                              "QMessageBox QLabel{color :rgb(255, 0, 0)}");
        message.button(QMessageBox::Ok)->setStyleSheet("border : none;\n"
                                                      "color : rgb(255, 0, 0);\n"
                                                      "border: 1px solid rgb(255, 0, 0);\n"
                                                      "padding : 10px;\n"
                                                      "border-radius : 10px");
        message.exec();
    }
    else if(ui->passwordLineEdit->text() == NULL)
    {
        message.setWindowTitle(tr("Sign IN"));
        message.setText(tr("! Please enter your Password !"));
        message.addButton(QMessageBox::Ok);

        message.setStyleSheet("QMessageBox{"
                              "border : 1px solid rgb(255, 0, 0);\n"
                              "border-radius : 10px}"
                              "QMessageBox QLabel{color :rgb(255, 0, 0)}");
        message.button(QMessageBox::Ok)->setStyleSheet("border : none;\n"
                                                      "color : rgb(255, 0, 0);\n"
                                                      "border: 1px solid rgb(255, 0, 0);\n"
                                                      "padding : 10px;\n"
                                                      "border-radius : 10px");
        message.exec();
    }
    else
    {
        user = "http://api.softserver.org:1104/login?username="+ui->usernameLineEdit->text()+"&password="+ui->passwordLineEdit->text();
        qDebug()<<user;
        request.setUrl(QUrl(user));
        manager->get(request);
    }
}
void Signin::mfin(QNetworkReply *rep)
{
    QString data = (QString)rep->readAll();
    QJsonDocument jsd =QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsb =jsd.object();
    qDebug()<< data ;
    QMessageBox message;
    if(jsb["code"].toString()=="200")
    {
        message.setWindowTitle(tr("Sign IN"));
        message.setText(jsb["message"].toString());
        message.addButton(QMessageBox::Ok);

        message.setStyleSheet("QMessageBox{"
                              "border : 1px solid rgb(255, 0, 0);\n"
                              "border-radius : 10px}"
                              "QMessageBox QLabel{color :rgb(255, 0, 0)}");
        message.button(QMessageBox::Ok)->setStyleSheet("border : none;\n"
                                                      "color : rgb(255, 0, 0);\n"
                                                      "border: 1px solid rgb(255, 0, 0);\n"
                                                      "padding : 10px;\n"
                                                      "border-radius : 10px");
        message.exec();

        token = jsb["token"].toString();
//        signinandsignup *s = new signinandsignup;
//        setCentralWidget(s);
        ui->statusbar->close();
        interface *Interface = new interface;
        setCentralWidget(Interface);
        // QFile

        QFile file("info/information.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream textstream(&file);
            textstream<<token<<","<<ui->usernameLineEdit->text()<<","<<ui->passwordLineEdit->text();
            file.close();
        }
        User_src = ui->usernameLineEdit->text();

    }
    else if(jsb["code"].toString()=="404")
    {
        message.setWindowTitle(tr("Sign IN"));
        message.setText(jsb["message"].toString());
        message.addButton(QMessageBox::Ok);

        message.setStyleSheet("QMessageBox{"
                              "border : 1px solid rgb(255, 0, 0);\n"
                              "border-radius : 10px}"
                              "QMessageBox QLabel{color :rgb(255, 0, 0)}");
        message.button(QMessageBox::Ok)->setStyleSheet("border : none;\n"
                                                      "color : rgb(255, 0, 0);\n"
                                                      "border: 1px solid rgb(255, 0, 0);\n"
                                                      "padding : 10px;\n"
                                                      "border-radius : 10px");
        message.exec();
    }
    else if(jsb["code"].toString()=="401")
    {
        message.setWindowTitle(tr("Sign UP"));
        message.setText(jsb["message"].toString());
        message.addButton(QMessageBox::Ok);

        message.setStyleSheet("QMessageBox{"
                              "border : 1px solid rgb(255, 0, 0);\n"
                              "border-radius : 10px}"
                              "QMessageBox QLabel{color :rgb(255, 0, 0)}");
        message.button(QMessageBox::Ok)->setStyleSheet("border : none;\n"
                                                      "color : rgb(255, 0, 0);\n"
                                                      "border: 1px solid rgb(255, 0, 0);\n"
                                                      "padding : 10px;\n"
                                                      "border-radius : 10px");
        message.exec();
    }
}

void Signin::on_cancel_2_clicked()
{

    signinandsignup *s = new signinandsignup(this);
    setCentralWidget(s);
    ui->statusbar->close();
}

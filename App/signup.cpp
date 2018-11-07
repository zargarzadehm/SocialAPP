#include "signup.h"
#include "ui_signup.h"
#include "signinandsignup.h"
#include "confirmemail.h"
#include "interface.h"
#include <QTime>
#include <QTimer>

QString code_confirm,message1;
extern QString token;
Signup::Signup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    setWindowTitle("Sign Up");

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
    status = new QLabel();
    status ->setText("Enter a username and password ");
    ui->statusbar->addWidget(status);

    ui->usernameLineEdit->setPlaceholderText("Your Username");
    ui->passWordLineEdit->setPlaceholderText("Your Password");
    ui->passWordLineEdit->setEchoMode(QLineEdit::Password);
    ui->firstNameLineEdit->setPlaceholderText("Your Firstname");
    ui->lastNameLineEdit->setPlaceholderText("Your Lastname");
    ui->emailLineEdit->setPlaceholderText("Your Email");

    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));
    manager1 = new QNetworkAccessManager();
    connect(manager1,SIGNAL(finished(QNetworkReply*)),this,SLOT(signinmanage(QNetworkReply*)));

       client_ = NULL;
}

void Signup::run()
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

Signup::~Signup()
{
    client_->deleteLater();
    delete status;
    delete ui;
}

void Signup::on_cancel_clicked()
{
    //this->hide();
    signinandsignup *s = new signinandsignup(this);
    setCentralWidget(s);
    ui->statusbar->close();
}

void Signup::on_SignUp_clicked()
{
    QMessageBox message;
    QString user;

    if(ui->usernameLineEdit->text() == NULL)
    {
        message.setWindowTitle(tr("Sign UP"));
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
    else if(ui->passWordLineEdit->text() == NULL)
    {
        message.setWindowTitle(tr("Sign UP"));
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
    else if(ui->emailLineEdit->text() == NULL)
    {
        message.setWindowTitle(tr("Sign UP"));
        message.setText(tr("! Please enter your Email !"));
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
        user = "http://api.softserver.org:1104/signup?username="+ui->usernameLineEdit->text()+"&password="+ui->passWordLineEdit->text()+"&firstname="+ui->firstNameLineEdit->text()+"&lastname="+ui->lastNameLineEdit->text();
        qDebug()<<user;
        request.setUrl(QUrl(user));
        manager->get(request);
    }
}

void Signup::mfin(QNetworkReply *rep)
{
    QString data = (QString)rep->readAll();
    QJsonDocument jsd =QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsb =jsd.object();
    qDebug()<< data ;
    QMessageBox message;
    if(jsb["code"].toString()=="200")
    {
        message1 = jsb["message"].toString();
        //email

        Email email = createEmail();

        // Create the SMTPClient
        client_ = new SMTPClient("smtp.gmail.com",465);
        // Connection used to receive the results
        connect(client_, SIGNAL(status(Status::e, QString)),this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

        // Try to send the email
        client_->sendEmail(email);

        /////////////////
        ConfirmEmail em;
        em.exec();
        this->hide();

        QString api = "http://api.softserver.org:1104/login?username="+ui->usernameLineEdit->text()+"&password="+ui->passWordLineEdit->text();
        //qDebug()<<user;
        request1.setUrl(QUrl(api));
        manager1->get(request1);

        ///////////////////////////////qfile;
//        QFile file("info/information.txt");
//        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
//            QTextStream textstream(&file);
//            textstream<<token<<","<<ui->usernameLineEdit->text()<<","<<ui->passWordLineEdit->text();
//            file.close();
//        }

        ///////////////////////////////qfile;

        interface *Interface = new interface(this);
        ui->statusbar->close();
        this->close();
        Interface->show();
        //setCentralWidget(Interface);


    }
    else if(jsb["code"].toString()=="204")
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


Email Signup::createEmail()
{
    // Create the credentials EmailAddress
    EmailAddress credentials("moein.zargarzadeh@gmail.com","AdGjL46775282zargar");

    // Create the from EmailAddress
    EmailAddress from("moein.zargarzadeh@gmail.com");

    // Create the to EmailAddress
    EmailAddress to(ui->emailLineEdit->text());

    // Create the random code confirm & email
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int randomValue = randInt(0,9999);

    code_confirm = QString::number((randomValue));
    qDebug()<<code_confirm;
    Email email(credentials,
                from,
                to,
                "Confirm Rigester in messenger",
               QString::number(randomValue));

    return email;
}

void Signup::onStatus(Status::e status, QString errorMessage)
{
    // Show a message based on the Status
    switch (status)
    {
    case Status::Success:
        QMessageBox::information(NULL, tr("SMTPClient"), tr("Message successfully sent!"));
        break;
    case Status::Failed:
    {
        QMessageBox::warning(NULL, tr("SMTPClient"), tr("Could not send the message!"));
        qCritical() << errorMessage;
    }
        break;
    default:
        break;
    }

    // Delete the client pointer
    client_->deleteLater();
}

int Signup::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

void Signup::signinmanage(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jso = jsd.object();
    QVariantMap map = jso.toVariantMap();

    token = map["token"].toString();

    QFile file("info/information.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream textstream(&file);
        textstream<<token<<","<<ui->usernameLineEdit->text()<<","<<ui->passWordLineEdit->text();
        file.close();
    }
}

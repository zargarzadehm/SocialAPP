#include "signup.h"
#include "ui_signup.h"
#include "signinandsignup.h"
#include "confirmemail.h"

QString code_confirm,message1;

Signup::Signup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);

    setWindowTitle("Sign Up");

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
    QLabel *status = new QLabel();
    status ->setText("Enter a username and password ");
    ui->statusbar->addWidget(status);

    ui->usernameLineEdit->setPlaceholderText("Your Username");
    ui->passWordLineEdit->setPlaceholderText("Your Password");
    ui->passWordLineEdit->setEchoMode(QLineEdit::Password);
    ui->firstNameLineEdit->setPlaceholderText("Your Firstname");
    ui->lastNameLineEdit->setPlaceholderText("Your Lastname");
    ui->usernameLineEdit->setStyleSheet(tr("border : none;\nborder : 1px outset rgb(0, 255, 0);\nbackground-color: rgb(0, 75, 0);\noutline : none;\ncolor:rgb(0, 255, 0);\n"));
    ui->emailLineEdit->setPlaceholderText("Your Email");

    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));

    //QT Tread

    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if(reply->bytesAvailable())
    {
        //QMessageBox::information(this, "Info", "You are connected to the internet :)");
        status->setText("You are connected to the internet :)");
        ui->statusbar->addWidget(status);
    }
    else
    //QMessageBox::critical(this, "Info", "You are not connected to the internet :(");
       status->setText("You are not connected to the internet :)");
       ui->statusbar->addWidget(status);

       client_ = NULL;

       // Connect all signals and slots
       //connect(ui->SignUp, SIGNAL(clicked(bool)), this, SLOT(sendEmail()));
}

Signup::~Signup()
{
    client_->deleteLater();
    delete ui;
}

void Signup::on_cancel_clicked()
{
    //this->hide();
    signinandsignup *s = new signinandsignup;
    ui->statusbar->close();
    setCentralWidget(s);
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

        signinandsignup *s = new signinandsignup;
        ui->statusbar->close();
        setCentralWidget(s);

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

/*void Signup::sendEmail()
{
    // Create the email object
    Email email = createEmail();

    // Create the SMTPClient
    client_ = new SMTPClient("smtp.mail.yahoo.com",465);

    // Connection used to receive the results
    connect(client_, SIGNAL(status(Status::e, QString)),
            this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

    // Try to send the email
    client_->sendEmail(email);
}*/

Email Signup::createEmail()
{
    // Create the credentials EmailAddress
    EmailAddress credentials("moein.zargarzadeh@gmail.com","1377Moienzm");

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

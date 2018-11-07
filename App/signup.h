#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QtNetwork>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDesktopWidget>
#include <QtCore/qglobal.h>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include "email.h"
#include "smtpclient.h"
#include "emailaddress.h"

namespace Ui {
class Signup;
}

class Signup : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = 0);
    int randInt(int low, int high);
    static void set_status(int condition);
    ~Signup();
public slots:
    void run();
private slots:
    void on_cancel_clicked();
    void on_SignUp_clicked();
    void mfin(QNetworkReply*);
    void onStatus(Status::e status, QString errorMessage);
    void signinmanage(QNetworkReply*);

private:
    Ui::Signup *ui;
    QNetworkAccessManager * manager;
    QNetworkAccessManager * manager1;
    QNetworkReply *reply;
    QLabel *status;
    QNetworkRequest request;
    QNetworkRequest request1;
    Email createEmail();
    SMTPClient *client_;
};

#endif // SIGNUP_H

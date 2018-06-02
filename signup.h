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
    ~Signup();

private slots:
    void on_cancel_clicked();
    void on_SignUp_clicked();

    void mfin(QNetworkReply*);
    void onStatus(Status::e status, QString errorMessage);

private:
    Ui::Signup *ui;
    QNetworkAccessManager * manager;
    QNetworkRequest request;
    Email createEmail();
    SMTPClient *client_;
};

#endif // SIGNUP_H

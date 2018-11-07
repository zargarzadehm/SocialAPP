#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QtNetwork>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Signin;
}

class Signin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = 0);
    ~Signin();

private slots:
    void on_SignIn_clicked();
     void mfin(QNetworkReply*);

     void on_cancel_2_clicked();

private:
    Ui::Signin *ui;
    QNetworkAccessManager * manager;
    QNetworkRequest request;
};

#endif // SIGNIN_H

#ifndef SEND_USER_H
#define SEND_USER_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidget>
#include <QListWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPushButton>
#include <QString>
#include <QTextBrowser>
#include <QTime>
#include <QWidget>
#include <QMessageBox>
#include <QVariantMap>
#include <QTextStream>

namespace Ui {
class send_user;
}

class send_user : public QWidget
{
    Q_OBJECT

public:
    explicit send_user(QWidget *parent = 0);
    ~send_user();
private slots:

    void manageusers(QNetworkReply*);
    void getchats(QNetworkReply*);
    void sendapiuser();
    void send_api_chat();
    void threadchat(QListWidgetItem*);
    void on_send_clicked();
    void api_offline();
    void chat_offline(QNetworkReply*);

    /////////
    void resault(QNetworkReply*);
    /////////

    void on_search_clicked();

private:

    Ui::send_user *ui;

    QNetworkAccessManager* manager1;
    QNetworkAccessManager* manager2;
    QNetworkAccessManager* manager3;
    QNetworkAccessManager* manager4;
    QNetworkAccessManager* manager5;

    QNetworkRequest request1;
    QNetworkRequest request2;
    QNetworkRequest request3;
    QNetworkRequest request4;
    QNetworkRequest request5;

    QListWidgetItem* item1;

    int tedad1 ;
    int tedad2 ;
    int tedad_chat ;
    QString user;
    int tedad_chat_ha;
    int tedad_user_ha;


};

#endif // SEND_USER_H

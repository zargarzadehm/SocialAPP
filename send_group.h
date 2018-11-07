#ifndef SEND_GROUP_H
#define SEND_GROUP_H
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
#include <QFile>

namespace Ui {
class send_group;
}

class send_group : public QWidget
{
    Q_OBJECT

public:
    explicit send_group(QWidget *parent = 0);
    ~send_group();
private slots:

    void managegroups(QNetworkReply*);
    void getchats(QNetworkReply*);
    void sendapigroup();
    void send_api_chat();
    void threadchat(QListWidgetItem*);
    void on_send_clicked();
    void on_search_clicked();
    void resault(QNetworkReply*);

private:
    QNetworkAccessManager* manager1;
    QNetworkAccessManager* manager2;
    QNetworkAccessManager* manager3;
    QNetworkAccessManager* manager4;

    QNetworkRequest request1;
    QNetworkRequest request2;
    QNetworkRequest request3;
    QNetworkRequest request4;


    Ui::send_group *ui;

    QListWidgetItem* item1;

    int tedad1 ;
    int tedad2 ;
    int tedad_chat ;
};

#endif // SEND_GROUP_H

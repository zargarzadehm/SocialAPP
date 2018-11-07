#ifndef SEND_CHANNEL_H
#define SEND_CHANNEL_H
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
#include <QTimer>
#include <QWidget>
#include <QMessageBox>
#include <QVariantMap>
#include <QFile>

namespace Ui {
class send_channel;
}

class send_channel : public QWidget
{
    Q_OBJECT

public:
    explicit send_channel(QWidget *parent = 0);
    ~send_channel();
private slots:

    void managechannels(QNetworkReply*);
    void getchats(QNetworkReply*);
    void resault(QNetworkReply*);
    void threadchats(QListWidgetItem*);
    void sendapichannel();
    void send_api_chat();
    void on_search_clicked();
    void on_send_clicked();
    void send_api_admin();
    void check_admin_channel(QNetworkReply*);

private:

    Ui::send_channel *ui;

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
    int tedad_channel;

    bool admin;

    QString channelname;


};

#endif // SEND_CHANNEL_H

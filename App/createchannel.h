#ifndef CREATECHANNEL_H
#define CREATECHANNEL_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

namespace Ui {
class createchannel;
}

class createchannel : public QMainWindow
{
    Q_OBJECT

public:
    explicit createchannel(QWidget *parent = 0);
    ~createchannel();

private slots:
    void manage(QNetworkReply*);

    void on_cancel_clicked();

    void on_create_channel_clicked();

private:
    Ui::createchannel *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest request;
};

#endif // CREATECHANNEL_H

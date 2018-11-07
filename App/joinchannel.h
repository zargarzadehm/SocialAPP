#ifndef JOINCHANNEL_H
#define JOINCHANNEL_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QMessageBox>
#include "interface.h"

namespace Ui {
class joinchannel;
}

class joinchannel : public QMainWindow
{
    Q_OBJECT

public:
    explicit joinchannel(QWidget *parent = 0);
    ~joinchannel();

private slots:
    void on_pushButton_clicked();
    void manage(QNetworkReply*);

    void on_join_channel_clicked();

    void on_cancel_clicked();

private:
    Ui::joinchannel *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest request;
};

#endif // JOINCHANNEL_H

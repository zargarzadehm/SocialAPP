#ifndef LOGOUT_H
#define LOGOUT_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QMessageBox>

namespace Ui {
class logout;
}

class logout : public QWidget
{
    Q_OBJECT

public:
    explicit logout(QWidget *parent = 0);
    ~logout();

private slots:
    void on_pushButton_clicked();
    void manage(QNetworkReply*);

private:
    Ui::logout *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest request;
};

#endif // LOGOUT_H

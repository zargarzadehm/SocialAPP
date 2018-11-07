#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QWidget>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>

namespace Ui {
class creategroup;
}

class creategroup : public QMainWindow
{
    Q_OBJECT

public:
    explicit creategroup(QMainWindow *parent = 0);
    ~creategroup();

private slots:
    void manage(QNetworkReply*);

    void on_create_group_clicked();

    void on_cancel_clicked();

private:
    Ui::creategroup *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest request;
};

#endif // CREATEGROUP_H

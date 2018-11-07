#ifndef JOINGROUP_H
#define JOINGROUP_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QMessageBox>
#include <QMainWindow>
#include <QDesktopWidget>

namespace Ui {
class joingroup;
}

class joingroup : public QMainWindow
{
    Q_OBJECT

public:
    explicit joingroup(QWidget *parent = 0);
    ~joingroup();

private slots:
    void on_pushButton_clicked();
    void manage(QNetworkReply*);

    void on_join_group_clicked();

    void on_cancel_clicked();

private:
    Ui::joingroup *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest request;
};

#endif // JOINGROUP_H

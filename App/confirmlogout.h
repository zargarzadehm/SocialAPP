#ifndef CONFIRMLOGOUT_H
#define CONFIRMLOGOUT_H
#include <QFile>
#include <QDialog>
#include <QDesktopWidget>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork>

namespace Ui {
class confirmlogout;
}

class confirmlogout : public QDialog
{
    Q_OBJECT

public:
    explicit confirmlogout(QWidget *parent = 0);
    ~confirmlogout();

private slots:
    void manage(QNetworkReply *);

    void on_YES_clicked();

    void on_NO_clicked();

private:
    Ui::confirmlogout *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest request;
};

#endif // CONFIRMLOGOUT_H

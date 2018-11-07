#ifndef CONFIRMEMAIL_H
#define CONFIRMEMAIL_H

#include <QDialog>
#include <QDesktopWidget>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
namespace Ui {
class ConfirmEmail;
}

class ConfirmEmail : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmEmail(QWidget *parent = 0);
    ~ConfirmEmail();

private slots:

    void on_confirm_clicked();

private:
    Ui::ConfirmEmail *ui;
};

#endif // CONFIRMEMAIL_H

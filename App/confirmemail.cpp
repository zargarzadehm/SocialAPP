#include "confirmemail.h"
#include "ui_confirmemail.h"
#include "signinandsignup.h"

extern QString code_confirm;
extern QString message1;
ConfirmEmail::ConfirmEmail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmEmail)
{
    ui->setupUi(this);
    setWindowTitle("Code Varification");
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

ConfirmEmail::~ConfirmEmail()
{
    delete ui;
}


void ConfirmEmail::on_confirm_clicked()
{
       QMessageBox message;
    if (ui->codeverification->text()==code_confirm)
    {
        message.setWindowTitle(tr("Confirm Email"));
        message.setText(message1);

        message.addButton(QMessageBox::Ok);

        message.setStyleSheet("QMessageBox{"
                              "border : 1px solid rgb(255, 0, 0);\n"
                              "border-radius : 10px}"
                              "QMessageBox QLabel{color :rgb(255, 0, 0)}");
        message.button(QMessageBox::Ok)->setStyleSheet("border : none;\n"
                                                      "color : rgb(255, 0, 0);\n"
                                                      "border: 1px solid rgb(255, 0, 0);\n"
                                                      "padding : 10px;\n"
                                                      "border-radius : 10px");
        message.exec();

        this->close();

    }
    else
    {
        message.setWindowTitle(tr("Confirm Code"));
        message.setText("Code confirm is invalid");

        message.addButton(QMessageBox::Ok);

        message.setStyleSheet("QMessageBox{"
                              "border : 1px solid rgb(255, 0, 0);\n"
                              "border-radius : 10px}"
                              "QMessageBox QLabel{color :rgb(255, 0, 0)}");
        message.button(QMessageBox::Ok)->setStyleSheet("border : none;\n"
                                                      "color : rgb(255, 0, 0);\n"
                                                      "border: 1px solid rgb(255, 0, 0);\n"
                                                      "padding : 10px;\n"
                                                      "border-radius : 10px");
        message.exec();
    }
}

#include "getuserchats.h"
#include "ui_getuserchats.h"

getuserchats::getuserchats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getuserchats)
{
    ui->setupUi(this);
}

getuserchats::~getuserchats()
{
    delete ui;
}

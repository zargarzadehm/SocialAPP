#include "getusers.h"
#include "ui_getusers.h"

getusers::getusers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getusers)
{
    ui->setupUi(this);
}

getusers::~getusers()
{
    delete ui;
}

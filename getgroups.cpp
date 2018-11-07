#include "getgroups.h"
#include "ui_getgroups.h"

getgroups::getgroups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getgroups)
{
    ui->setupUi(this);
}

getgroups::~getgroups()
{
    delete ui;
}

#include "getgroupchats.h"
#include "ui_getgroupchats.h"

getgroupchats::getgroupchats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getgroupchats)
{
    ui->setupUi(this);
}

getgroupchats::~getgroupchats()
{
    delete ui;
}

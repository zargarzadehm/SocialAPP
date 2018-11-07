#include "getchannels.h"
#include "ui_getchannels.h"

getchannels::getchannels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getchannels)
{
    ui->setupUi(this);
}

getchannels::~getchannels()
{
    delete ui;
}

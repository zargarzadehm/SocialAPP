#include "getchannelchats.h"
#include "ui_getchannelchats.h"

getchannelchats::getchannelchats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getchannelchats)
{
    ui->setupUi(this);
}

getchannelchats::~getchannelchats()
{
    delete ui;
}

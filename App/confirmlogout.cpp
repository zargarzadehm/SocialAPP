#include "confirmlogout.h"
#include "ui_confirmlogout.h"

int flag1;
confirmlogout::confirmlogout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmlogout)
{
    ui->setupUi(this);
    setWindowTitle("confirm logout");
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(manage(QNetworkReply*)));
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

confirmlogout::~confirmlogout()
{
    delete ui;
    delete manager;
}

void confirmlogout::manage(QNetworkReply *rep){
    QString data = rep->readAll();
    QJsonDocument x = QJsonDocument::fromJson(data.toUtf8());
    QMessageBox* z = new QMessageBox;
    QJsonObject y = x.object();
    if(y["code"]=="200"){
        z->setText("logout successfully done!\ngood bye!");
    }
    else if (y["code"]=="401") z->setText("invalid username or password\nplease try again");
    z->show();
    this->close();
}

void confirmlogout::on_YES_clicked()
{
    QFile file("info/information.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString string = file.readAll();
    QStringList stringlist = string.split(',');

    QString username = stringlist[1];
    QString password = stringlist[2];
    qDebug()<<username<<endl<<password;

    QString api = "http://api.softserver.org:1104/logout?username=" + username + "&password=" + password;
    file.close();
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.close();
    request.setUrl(QUrl(api));
    manager->get(request);
    flag1 =1;

}


void confirmlogout::on_NO_clicked()
{
    this->close();
}

#ifndef INTERFACE_H
#define INTERFACE_H
#include "creategroup.h"
#include "createchannel.h"
#include "joinchannel.h"
#include "joingroup.h"
#include "logout.h"
#include <QMainWindow>
#include <QTabWidget>
#include <QTime>
#include <QTimer>

namespace Ui {
class interface;
}

class interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface(QWidget *parent = 0);
    ~interface();
public slots:
        void run();
private slots:
    void on_actionCreate_Group_triggered();

    void on_actionCreate_Channel_triggered();

    void on_actionLog_out_triggered();

private:
    Ui::interface *ui;
    QNetworkReply *reply;
    QLabel *status;

};

#endif // INTERFACE_H

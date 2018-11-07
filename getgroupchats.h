#ifndef GETGROUPCHATS_H
#define GETGROUPCHATS_H

#include <QWidget>

namespace Ui {
class getgroupchats;
}

class getgroupchats : public QWidget
{
    Q_OBJECT

public:
    explicit getgroupchats(QWidget *parent = 0);
    ~getgroupchats();

private:
    Ui::getgroupchats *ui;
};

#endif // GETGROUPCHATS_H

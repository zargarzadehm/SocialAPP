#ifndef GETGROUPS_H
#define GETGROUPS_H

#include <QWidget>

namespace Ui {
class getgroups;
}

class getgroups : public QWidget
{
    Q_OBJECT

public:
    explicit getgroups(QWidget *parent = 0);
    ~getgroups();

private:
    Ui::getgroups *ui;
};

#endif // GETGROUPS_H

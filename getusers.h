#ifndef GETUSERS_H
#define GETUSERS_H

#include <QWidget>

namespace Ui {
class getusers;
}

class getusers : public QWidget
{
    Q_OBJECT

public:
    explicit getusers(QWidget *parent = 0);
    ~getusers();

private:
    Ui::getusers *ui;
};

#endif // GETUSERS_H

#ifndef GETCHANNELS_H
#define GETCHANNELS_H

#include <QWidget>

namespace Ui {
class getchannels;
}

class getchannels : public QWidget
{
    Q_OBJECT

public:
    explicit getchannels(QWidget *parent = 0);
    ~getchannels();

private:
    Ui::getchannels *ui;
};

#endif // GETCHANNELS_H

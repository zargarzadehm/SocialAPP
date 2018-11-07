#ifndef GETCHANNELCHATS_H
#define GETCHANNELCHATS_H

#include <QWidget>

namespace Ui {
class getchannelchats;
}

class getchannelchats : public QWidget
{
    Q_OBJECT

public:
    explicit getchannelchats(QWidget *parent = 0);
    ~getchannelchats();

private:
    Ui::getchannelchats *ui;
};

#endif // GETCHANNELCHATS_H

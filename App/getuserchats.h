#ifndef GETUSERCHATS_H
#define GETUSERCHATS_H

#include <QWidget>

namespace Ui {
class getuserchats;
}

class getuserchats : public QWidget
{
    Q_OBJECT

public:
    explicit getuserchats(QWidget *parent = 0);
    ~getuserchats();

private:
    Ui::getuserchats *ui;
};

#endif // GETUSERCHATS_H

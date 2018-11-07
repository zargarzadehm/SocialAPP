#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QAction>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "signinandsignup.h"
#include "interface.h"
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_STARTAPP_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *processLabel;
    QLabel *status;
    QMovie *movie;
    signinandsignup* s;
};

#endif // MAINWINDOW_H

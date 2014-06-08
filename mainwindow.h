#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "twitchmanager.h"
#include "monitor.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    twitchManager *t_manager = new twitchManager;
    Monitor streamMonitor;

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};
//Within this class we need to reimplement the ability to move the window around when a user clicks on the Form Widget
#endif // MAINWINDOW_H

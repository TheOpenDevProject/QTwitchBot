#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "twitchmanager.h"
#include "monitor.h"
#include "twitchcommandlist.h"
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
    TwitchCommandList *t_commandList = new TwitchCommandList;
    ~MainWindow(){
        //dtor
        delete t_manager;
       delete t_commandList;
        delete ui;
    }

private slots:
    void on_pushButton_clicked();

    void on_actionLoad_Commands_triggered();

private:
    Ui::MainWindow *ui;

};
//Within this class we need to reimplement the ability to move the window around when a user clicks on the Form Widget
#endif // MAINWINDOW_H

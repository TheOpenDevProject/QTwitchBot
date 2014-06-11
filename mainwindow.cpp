#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebSettings>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->streamView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    streamMonitor.show();
    streamMonitor.setTwitchManager(t_manager);
}

void MainWindow::on_pushButton_clicked()
{
    t_manager->connectToChannel("irc.twitch.tv",6667,ui->twitch_user->text(),"Twitch Bot",ui->twitch_user->text(),ui->twitch_user->text(),ui->twitch_token->text());
    //Enable our UI buttons
    ui->addModeratorBttn->setEnabled(true);
    ui->removeModeratorBttn->setEnabled(true);
     ui->AnnounceBttn->setEnabled(true);
       ui->banUserBttn->setEnabled(true);
        ui->unbanUserBttn->setEnabled(true);
        ui->EnableSlowBttn->setEnabled(true);
        ui->DisableSlowBttn->setEnabled(true);
        //Set stream webkit view to streamers name
        ui->streamView->setUrl("http://twitch.tv/" + ui->twitch_user->text());
}

void MainWindow::on_actionLoad_Commands_triggered()
{
    QString script_file = QFileDialog::getOpenFileName(this,tr("Load Twitch Bot Script"),"/scripts",tr("Script Files (*.tbs)"));
    t_manager->setCommandList(t_commandList->loadFromFile(script_file));
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebSettings>
#include <QFileDialog>
#include <QInputDialog>
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
        ui->clearStreamBttn->setEnabled(true);
        //Set stream webkit view to streamers name
        ui->streamView->setUrl("http://twitch.tv/" + ui->twitch_user->text());
}

void MainWindow::on_actionLoad_Commands_triggered()
{
    QString script_file = QFileDialog::getOpenFileName(this,tr("Load Twitch Bot Script"),"/scripts",tr("Script Files (*.tbs)"));
    t_manager->setCommandList(t_commandList->loadFromFile(script_file));
    commandKeys.setStringList(t_manager->getCommandKeysAsStringList());
    ui->m_CommandView->setModel(&commandKeys);
}

void MainWindow::on_addModeratorBttn_clicked()
{
    bool ok;
   QString modName = QInputDialog::getText(this,tr("Add Moderator"),tr("Enter Twitch Username"),QLineEdit::Normal,NULL,&ok);
   if(ok && !modName.isEmpty()){
       t_manager->sendMessage("/mod " + modName);
   }
}

void MainWindow::on_clearStreamBttn_clicked()
{
    t_manager->sendMessage("/clear");
}

void MainWindow::on_removeModeratorBttn_clicked()
{
    bool ok;
   QString modName = QInputDialog::getText(this,tr("Remove Moderator"),tr("Enter Twitch Username"),QLineEdit::Normal,NULL,&ok);
   if(ok && !modName.isEmpty()){
       t_manager->sendMessage("/unmod " + modName);
   }
}

void MainWindow::on_banUserBttn_clicked()
{
    bool ok;
   QString banName = QInputDialog::getText(this,tr("Ban User"),tr("Enter Twitch Username"),QLineEdit::Normal,NULL,&ok);
   if(ok && !banName.isEmpty()){
       t_manager->sendMessage("/ban " + banName);
   }
}

void MainWindow::on_unbanUserBttn_clicked()
{
    bool ok;
   QString banName = QInputDialog::getText(this,tr("Un-Ban User"),tr("Enter Twitch Username"),QLineEdit::Normal,NULL,&ok);
   if(ok && !banName.isEmpty()){
       t_manager->sendMessage("/unban " + banName);
   }
}

void MainWindow::on_AnnounceBttn_clicked()
{
    bool ok;
   QString message = QInputDialog::getText(this,tr("Make Announcement"),tr("Enter  Announcement To Send"),QLineEdit::Normal,NULL,&ok);
   if(ok && !message.isEmpty()){
       t_manager->sendMessage(message);
   }
}

void MainWindow::on_EnableSlowBttn_clicked()
{
    bool ok;
   int delayTime = QInputDialog::getInt(this,tr("Set Slow Mode"),tr("Delay Time"),0,1,214743647,1,&ok);
   if(ok){
       t_manager->sendMessage("/slow " + QString::number(delayTime));
   }
}

void MainWindow::on_DisableSlowBttn_clicked()
{
       t_manager->sendMessage("/slowoff");
}

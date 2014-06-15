#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebSettings>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->streamView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    streamMonitor.show();
    streamMonitor.setTwitchManager(t_manager);
    ///////////////////////////////////////////////////////
    //                      Theme Manger V.10                           //
    //////////////////////////////////////////////////////
  auto cartoonDark = std::bind(&MainWindow::enableCartoonDarkTheme,this);
  auto defaultTheme = std::bind(&MainWindow::enableDefaultTheme,this);
    themeManager.emplace_back(defaultTheme);
    themeManager.emplace_back(cartoonDark);
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
        ui->streamView->setUrl("http://twitch.tv/" + ui->twitch_user->text() + "/popout");
        ui->chatFeed->setUrl("http://twitch.tv/" + ui->twitch_user->text() + "/chat?popout=");
        updateCmdTimer->start(3);
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
//Install a keyboard hander
void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_F1){
        streamMonitor.hide();
    }
    if(e->key() == Qt::Key_F2){
        streamMonitor.show();
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

void MainWindow::on_actionDisable_Javascript_triggered()
{
     ui->streamView->settings()->setAttribute(QWebSettings::JavascriptEnabled,false);
}

void MainWindow::on_actionEnable_Javascript_triggered()
{
    ui->streamView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
}

void MainWindow::updateCmdRate(){
    ui->progressBar->setValue(t_manager->getCommandRate());
}

void MainWindow::on_actionLoad_Music_From_Folder_triggered()
{
    musicFiles.clear();
    QMessageBox err_out;
    musicFiles = QFileDialog::getOpenFileNames(this,tr("Load Music"),tr("/"),tr("All Files(*.*)"));
    if(musicFiles.empty()){
        err_out.setText("You MUST select at least ONE file for playback");
        err_out.exec();
    }else{
      t_manager->setMusicPlayer(&streamPlayer);
    streamPlayer.setPlaylistFromFile(musicFiles);
    m_musicFiles.setStringList(musicFiles);
    ui->music_List_view->setModel(&m_musicFiles);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    streamPlayer.play();
}

void MainWindow::on_v_Slider_valueChanged(int value)
{
    streamPlayer.setVolume(value);
    ui->volumeLbl->setText("Current Volume: " + QString::number(value));
}

void MainWindow::on_pushButton_5_clicked()
{
    streamPlayer.nextSong();
}

void MainWindow::on_pushButton_3_clicked()
{
    streamPlayer.pause();
}

void MainWindow::on_pushButton_4_clicked()
{
    streamPlayer.stop();
}

void MainWindow::on_pushButton_7_clicked()
{
    //This will make the effect of a restart
    streamPlayer.stop();
    streamPlayer.play();
}

void MainWindow::on_m_playeyTab_tabCloseRequested(int index)
{

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    themeManager.at(index)();
}

void MainWindow::enableCartoonDarkTheme(){
    this->setStyleSheet("#MainWindow{border-image:url(:/themes/res/cartoonDark/cartoon-dark-bng.jpg);} #m_CommandView{background-color: rgb(62, 62, 62);color: rgb(255, 255, 255);}#tab_3{background-color: rgb(62, 62, 62);color: rgb(255, 255, 255);}");

}

void MainWindow::enableDefaultTheme()
{
    this->setStyleSheet("");
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     //Makes our MainWindow the controller
            ui->streamView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    streamMonitor.show();
    streamMonitor.setTwitchManager(t_manager);
    ///////////////////////////////////////////////////////
    // Theme Manger V.10              //
    //////////////////////////////////////////////////////
  auto cartoonDark = std::bind(&MainWindow::enableCartoonDarkTheme,this);
  auto defaultTheme = std::bind(&MainWindow::enableDefaultTheme,this);
  auto TeKeLiLi = std::bind(&MainWindow::enableTekeLiLiTheme,this);
  auto carbonToxic = std::bind(&MainWindow::enableToxicCarbonTheme,this);
    themeManager.emplace_back(defaultTheme);
    themeManager.emplace_back(cartoonDark);
    themeManager.emplace_back(TeKeLiLi);
    themeManager.emplace_back(carbonToxic);
    connect(&riot_api,SIGNAL(requestComplete(QByteArray)),this,SLOT(riotAPI_BasicProfileUpdated(QByteArray)));
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

    ui->streamView->load(QUrl("http://twitch.tv/" + ui->twitch_user->text() + "/popout"));
   ui->chatFeed->setUrl(QUrl("http://twitch.tv/" + ui->twitch_user->text() + "/chat?popout="));

}

void MainWindow::on_actionLoad_Commands_triggered()
{
    QString script_file = QFileDialog::getOpenFileName(this,tr("Load Twitch Bot Script"),"/scripts",tr("Script Files (*.tbs)"));
    if(script_file.isEmpty()){
        qDebug() << "External Error: No File Selected";
    }else{
    t_manager->setCommandList(t_commandList->loadFromFile(script_file));
    commandKeys.setStringList(t_manager->getCommandKeysAsStringList());
    ui->m_CommandView->setModel(&commandKeys);
    tbsScriptURL = script_file;
    scriptEditor->loadFromFile(script_file);
     }
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


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    themeManager.at(index)();
}

void MainWindow::enableCartoonDarkTheme(){
    this->setStyleSheet("#MainWindow{border-image:url(:/themes/res/cartoonDark/cartoon-dark-bng.jpg);} QLabel{color:#FA4B4B;} QPushButton{background-color:#FA4B4B; color:#fff;}");
    ui->addModeratorBttn->setFlat(true);
    ui->removeModeratorBttn->setFlat(true);
     ui->AnnounceBttn->setFlat(true);
       ui->banUserBttn->setFlat(true);
        ui->unbanUserBttn->setFlat(true);
        ui->EnableSlowBttn->setFlat(true);
        ui->DisableSlowBttn->setFlat(true);
        ui->clearStreamBttn->setFlat(true);


        ui->addModeratorBttn->setAutoFillBackground(true);
        ui->removeModeratorBttn->setAutoFillBackground(true);
         ui->AnnounceBttn->setAutoFillBackground(true);
           ui->banUserBttn->setAutoFillBackground(true);
            ui->unbanUserBttn->setAutoFillBackground(true);
            ui->EnableSlowBttn->setAutoFillBackground(true);
            ui->DisableSlowBttn->setAutoFillBackground(true);
            ui->clearStreamBttn->setAutoFillBackground(true);

}

void MainWindow::enableDefaultTheme()
{
    this->setStyleSheet("");
}

void MainWindow::enableTekeLiLiTheme()
{
    this->setStyleSheet("#MainWindow{border-image:url(:/themes/res/TeKeLiLi/background.jpg);} #settingsSetup_lbl{color:#fff;} #twitchUser_lbl{color:#fff;} #toathToken_lbl{color:#fff;} progressBar{color#fff;} QPushButton{background-color:#A4F069; color:#000;}");
    streamMonitor.setStyleSheet("#Monitor{border-image:url(:/themes/res/TeKeLiLi/background.jpg); background-color:none;}");
    ui->addModeratorBttn->setFlat(true);
    ui->removeModeratorBttn->setFlat(true);
     ui->AnnounceBttn->setFlat(true);
       ui->banUserBttn->setFlat(true);
        ui->unbanUserBttn->setFlat(true);
        ui->EnableSlowBttn->setFlat(true);
        ui->DisableSlowBttn->setFlat(true);
        ui->clearStreamBttn->setFlat(true);


        ui->addModeratorBttn->setAutoFillBackground(true);
        ui->removeModeratorBttn->setAutoFillBackground(true);
         ui->AnnounceBttn->setAutoFillBackground(true);
           ui->banUserBttn->setAutoFillBackground(true);
            ui->unbanUserBttn->setAutoFillBackground(true);
            ui->EnableSlowBttn->setAutoFillBackground(true);
            ui->DisableSlowBttn->setAutoFillBackground(true);
            ui->clearStreamBttn->setAutoFillBackground(true);

}

void MainWindow::enableToxicCarbonTheme()
{
 QMessageBox dedication;
 dedication.setText("This theme is dedicated to Riot ToxicHawk");
 dedication.exec();
 dedication.setText("Patient tester and Inspiration for the project - Thankyou buddy :)");
 dedication.exec();
  this->setStyleSheet("#MainWindow{border-image:url(:/themes/res/Premium-Carbon/background.png);} #settingsSetup_lbl{color:#fff;} #twitchUser_lbl{color:#fff;} #toathToken_lbl{color:#fff;} progressBar{color#fff;} QPushButton{background-color:#A4F069; color:#000;}");
 ui->addModeratorBttn->setFlat(true);
 ui->removeModeratorBttn->setFlat(true);
  ui->AnnounceBttn->setFlat(true);
    ui->banUserBttn->setFlat(true);
     ui->unbanUserBttn->setFlat(true);
     ui->EnableSlowBttn->setFlat(true);
     ui->DisableSlowBttn->setFlat(true);
     ui->clearStreamBttn->setFlat(true);


     ui->addModeratorBttn->setAutoFillBackground(true);
     ui->removeModeratorBttn->setAutoFillBackground(true);
      ui->AnnounceBttn->setAutoFillBackground(true);
        ui->banUserBttn->setAutoFillBackground(true);
         ui->unbanUserBttn->setAutoFillBackground(true);
         ui->EnableSlowBttn->setAutoFillBackground(true);
         ui->DisableSlowBttn->setAutoFillBackground(true);
         ui->clearStreamBttn->setAutoFillBackground(true);

}

void MainWindow::on_actionNew_Note_triggered()
{
    //Patched for C++11 smart pointers
    displayWindows.push_back(std::shared_ptr<popupDisplayWindow>(new popupDisplayWindow));
    displayWindows.back()->show();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent *event){
   qApp->quit();
}

void MainWindow::on_pushButton_8_clicked()
{
    bool ok;

    if(!displayWindows.empty()){
        QString winTitle = QInputDialog::getText(this,tr("Set Window Title"),tr("Enter A Window Title"),QLineEdit::Normal,NULL,&ok);
   if(ok){
        for(int i;i < displayWindows.size();i++){
        displayWindows.at(i)->setWindowTitle(winTitle);
        }
    }
    }else{
        QMessageBox errorbox;
        errorbox.setText("There are currently 0 note windows active, No need to set a title on nothing :)");
        errorbox.exec();
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    if(!displayWindows.empty()){
        QColor bngcolour = QColorDialog::getColor(Qt::white,this,tr("Select A Colour"),0);
   for (int i;i < displayWindows.size(); i++){
   displayWindows.at(i)->setBackgroundColour(bngcolour);
   }
    }else{
        //No note windows in vector
        QMessageBox errorbox;
        errorbox.setText("There are currently 0 note windows active, No need to set a title on nothing :)");
        errorbox.exec();
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(!displayWindows.empty()){
        QColor brushcolour = QColorDialog::getColor(Qt::white,this,tr("Select A Colour"),0);
        for (int i;i < displayWindows.size(); i++){
        displayWindows.at(i)->setBrushColour(brushcolour);
        }
    }else{
        //No note windows in vector
        QMessageBox errorbox;
        errorbox.setText("There are currently 0 note windows active, No need to set a title on nothing :)");
        errorbox.exec();
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    bool xOk = false;
    bool yOk = false;
    if(!displayWindows.empty()){
        float brushSizeX = QInputDialog::getDouble(this,tr("Enter Width"),tr("Enter A Width"),0,0,2147483647,2,&xOk,0);
         float brushSizeY = QInputDialog::getDouble(this,tr("Enter Height"),tr("Enter A Height"),0,0,2147483647,2,&yOk,0);
        if(xOk && yOk){
          for(int i;i < displayWindows.size(); i++){
              displayWindows.at(i)->setBrushSize(brushSizeX,brushSizeY);
          }
        }
    }else{
        QMessageBox errorbox;
        errorbox.setText("There are currently 0 note windows active, No need to set a title on nothing :)");
        errorbox.exec();
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    if(!displayWindows.empty()){

        displayWindows.at(0)->p_addText("FUN TimeS");
    }
}

void MainWindow::on_actionScript_Editor_triggered()
{
 //   scriptEditor->show();

}

void MainWindow::on_actionReload_Current_TBS_triggered()
{
    t_manager->setCommandList(t_commandList->loadFromFile(tbsScriptURL));
    commandKeys.setStringList(t_manager->getCommandKeysAsStringList());
    ui->m_CommandView->setModel(&commandKeys);
}

void MainWindow::on_pushButton_15_clicked()
{
riot_api.requestBasicProfile(ui->summoner_ID_Entry->text().toUtf8());

}

void MainWindow::riotAPI_BasicProfileUpdated(QByteArray data){
    ui->apiDebugView->append(data + "\n");

}

void MainWindow::on_setApiButton_clicked()
{
    QMessageBox warning;
    warning.setText("Warning: KEEP YOUR API KEY PRIVATE AT ALL TIMES TO PREVENT OTHERS USING UP ALL YOUR ALLOWANCE FROM RIOT GAMES");
    warning.exec();
    if(ui->apiKeyEdit->text().isEmpty() || ui->apiKeyEdit->text().size() < 36 || ui->apiKeyEdit->text().size() > 36){
        warning.setText("API Key Is Invalid - Must be 36 characters long");
        warning.exec();
        ui->apiDebugView->append("RiotAPI - API Key Is Invalid - Must be 36 characters long\n");
    }else{
          riot_api.setAPIKey(ui->apiKeyEdit->text());
    }

}

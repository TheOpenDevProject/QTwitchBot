#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSettings>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QColorDialog>
#include "twitchmanager.h"
#include "monitor.h"
#include "twitchcommandlist.h"
#include <QTimer>
#include "musicplayer.h"
#include "scriptedit.h"
#include <functional>
#include <vector>
#include "popupdisplaywindow.h"
#include <memory>
#include <apimanager.h>
namespace Ui {
class MainWindow;
}
//All usages of pointers are now updated to use C++11 smart pointers
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    twitchManager *t_manager = new twitchManager;
    Monitor streamMonitor;
    TwitchCommandList *t_commandList = new TwitchCommandList;
    MusicPlayer streamPlayer;
    scriptEdit *scriptEditor = new scriptEdit;
    RiotAPI *riot_api = new RiotAPI;
     ~MainWindow(){
        //dtor
        qDebug() << "Dtor called";
        //Update made and now using C++11 smart pointers
       // std::for_each(displayWindows.begin(),displayWindows.end(),std::default_delete<popupDisplayWindow>());
        delete ui;
        delete t_manager;
        delete t_commandList;
        delete scriptEditor;
        delete riot_api;
    }

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);
    void on_actionLoad_Commands_triggered();
    void on_addModeratorBttn_clicked();
    void on_clearStreamBttn_clicked();
    void on_removeModeratorBttn_clicked();
    void on_banUserBttn_clicked();
    void on_unbanUserBttn_clicked();
    void on_AnnounceBttn_clicked();
    void on_EnableSlowBttn_clicked();
    void on_DisableSlowBttn_clicked();
    void on_actionDisable_Javascript_triggered();
    void on_actionEnable_Javascript_triggered();

    void on_actionLoad_Music_From_Folder_triggered();
    void on_pushButton_2_clicked();
   void on_v_Slider_valueChanged(int value);
   void on_pushButton_5_clicked();
   void on_pushButton_3_clicked();
   void on_pushButton_4_clicked();
   void on_pushButton_7_clicked();
   void on_comboBox_currentIndexChanged(int index);
   void on_actionNew_Note_triggered();
   void on_actionExit_triggered();
   void on_pushButton_8_clicked();
   void on_pushButton_10_clicked();
   void on_pushButton_9_clicked();
   void on_pushButton_11_clicked();
   void on_pushButton_13_clicked();
   void on_actionScript_Editor_triggered();
   void on_actionReload_Current_TBS_triggered();

   void on_pushButton_15_clicked();
void riotAPI_BasicProfileUpdated(QByteArray data);
void on_setApiButton_clicked();

private:
       QStringList musicFiles;
       QStringListModel m_musicFiles;
    Ui::MainWindow *ui;
    QStringListModel commandKeys;
    std::vector<std::function<void()>> themeManager;
    //The scope of the pointer is this class
    std::vector<std::shared_ptr<popupDisplayWindow>> displayWindows; //All Popup display windows should be added into here
    void enableCartoonDarkTheme();
    void enableDefaultTheme();
    void enableTekeLiLiTheme();
    void enableToxicCarbonTheme();
    QString tbsScriptURL;
protected:
    void keyPressEvent(QKeyEvent *e);


};
//Within this class we need to reimplement the ability to move the window around when a user clicks on the Form Widget
#endif // MAINWINDOW_H

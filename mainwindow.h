#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "twitchmanager.h"
#include "monitor.h"
#include "twitchcommandlist.h"
#include <QTimer>
#include "musicplayer.h"
#include <functional>
#include <vector>
#include "popupdisplaywindow.h"
#include <memory>
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
    QTimer *updateCmdTimer = new QTimer(this);
    MusicPlayer streamPlayer;
     ~MainWindow(){
        //dtor
        qDebug() << "Dtor called";
                std::for_each(displayWindows.begin(),displayWindows.end(),std::default_delete<popupDisplayWindow>());
        delete ui;
        delete t_manager;
       delete t_commandList;


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
   void updateCmdRate();
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

private:
       QStringList musicFiles;
       QStringListModel m_musicFiles;
    Ui::MainWindow *ui;
    QStringListModel commandKeys;
    std::vector<std::function<void()>> themeManager;
    std::vector<popupDisplayWindow*> displayWindows; //All Popup display windows should be added into here
    void enableCartoonDarkTheme();
    void enableDefaultTheme();
    void enableTekeLiLiTheme();
protected:
    void keyPressEvent(QKeyEvent *e);

};
//Within this class we need to reimplement the ability to move the window around when a user clicks on the Form Widget
#endif // MAINWINDOW_H

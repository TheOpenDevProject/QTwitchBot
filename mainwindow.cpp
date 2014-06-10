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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    t_manager->connectToChannel("irc.twitch.tv",6667,ui->twitch_user->text(),"Twitch Bot",ui->twitch_user->text(),ui->twitch_user->text(),ui->twitch_token->text());
}

void MainWindow::on_actionLoad_Commands_triggered()
{
    QString script_file = QFileDialog::getOpenFileName(this,tr("Load Twitch Bot Script"),"/scripts",tr("Script Files (*.tbs)"));

}

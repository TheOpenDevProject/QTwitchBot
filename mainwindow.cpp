#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebSettings>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->streamView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

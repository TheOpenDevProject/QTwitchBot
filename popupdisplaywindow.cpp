#include "popupdisplaywindow.h"
#include "ui_popupdisplaywindow.h"

popupDisplayWindow::popupDisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::popupDisplayWindow)
{
    ui->setupUi(this);
}


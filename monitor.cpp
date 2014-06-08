#include "monitor.h"
#include "ui_monitor.h"
#include <QMouseEvent>
#include "mainwindow.h"
Monitor::Monitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Monitor::~Monitor()
{
    delete ui;
}

void Monitor::mouseMoveEvent(QMouseEvent *e){
    if(e->MouseButtonPress){
        this->move(e->globalPos());
    }

}

void Monitor::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Escape){
        this->hide();
    }

    if(e->key() == Qt::Key_F10){
        this->setGeometry(this->x(),this->y(),this->width() + 4,this->height() + 4);
    }

    if(e->key() == Qt::Key_F11){
        this->setGeometry(this->x(),this->y(),this->width() - 4,this->height() - 4);
    }
}

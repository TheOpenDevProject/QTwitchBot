#include "monitor.h"
#include "ui_monitor.h"
#include <QMouseEvent>
#include "mainwindow.h"
Monitor::Monitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);
    connect(feedTimer,SIGNAL(timeout()),this,SLOT(updateFeed()));
    feedTimer->start(100);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->m_DataView->setModel(&feed_model);
    //We can enable the developer option by pressing F7
    ui->developer_sendRaw->setVisible(false);
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
    if(e->key() == Qt::Key_F7){
        ui->developer_sendRaw->setVisible(true);
    }
    if(e->key() == Qt::Key_Enter){
        QByteArray rawCommand;
        rawCommand.append(ui->developer_sendRaw->text());
        twitch_manager->sendRaw(rawCommand);
    }
}

void Monitor::updateFeed(){
    feed_model.setStringList(twitch_manager->getMessageHistory());
}

void Monitor::setTwitchManager(twitchManager *t_manage){
    twitch_manager = t_manage;
}

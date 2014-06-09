#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QMouseEvent>
#include <QStringListModel>
#include <QTimer>
#include "twitchmanager.h"
namespace Ui {
class Monitor;
}

class Monitor : public QWidget
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = 0);
  QTimer *feedTimer = new QTimer(this);
   void setTwitchManager(twitchManager *t_manage);
    ~Monitor();
private slots:
   void updateFeed();
private:
    Ui::Monitor *ui;
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    QStringListModel feed_model;
    twitchManager *twitch_manager;
};

#endif // MONITOR_H

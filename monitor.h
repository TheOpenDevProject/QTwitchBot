#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QMouseEvent>
namespace Ui {
class Monitor;
}

class Monitor : public QWidget
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

private:
    Ui::Monitor *ui;
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
};

#endif // MONITOR_H

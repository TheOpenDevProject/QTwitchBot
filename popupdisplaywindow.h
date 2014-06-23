#ifndef POPUPDISPLAYWINDOW_H
#define POPUPDISPLAYWINDOW_H
#include <QWidget>
#include <QDebug>
#include <QGraphicsScene>
#include <memory>
#include <QColor>
#include <QBrush>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
namespace Ui {
class popupDisplayWindow;
}
class QPaintSceneC : public QGraphicsScene{
    Q_OBJECT
public:

    QPaintSceneC(){
        paintBrush.setColor(Qt::black);
        paintBrush.setStyle(Qt::SolidPattern);
        paintBrush_outer.setColor(Qt::black);
    }
    QBrush paintBrush;
    QPen paintBrush_outer;
    float bsX = 30;
    float bsY= 30;
    float setBrushSize(float w,float h);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

protected:
};

class popupDisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit popupDisplayWindow(QWidget *parent = 0);
    ~popupDisplayWindow()
    {
        qDebug() << "NoteWindow Destroyed";
        delete qgs;
        delete ui;
    }
    //Actual scene
    //Waiting for QGraphicsView to support the use of smart pointers
  QPaintSceneC *qgs = new QPaintSceneC;
   void setBrushSize(float w,float h);
   void setBackgroundColour(QColor s_colour);
   void setBrushColour(QColor b_colour);
private:
    Ui::popupDisplayWindow *ui;
    QBrush paintBrush;
   QPen paintBrush_outer;
};

#endif // POPUPDISPLAYWINDOW_H

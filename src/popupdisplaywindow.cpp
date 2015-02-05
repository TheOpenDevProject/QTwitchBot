#include "popupdisplaywindow.h"
#include "ui_popupdisplaywindow.h"

popupDisplayWindow::popupDisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::popupDisplayWindow)
{
    ui->setupUi(this);
    qgs->setSceneRect(ui->displayView->geometry().left(),ui->displayView->geometry().top(),ui->displayView->geometry().width(),ui->displayView->geometry().height());
    ui->displayView->setScene(qgs);
    ///////////////////////////////////////
    //Our Brushes have some defaults
    //////////////////////////////////////


}

void popupDisplayWindow::setBrushSize(float w, float h)
{
    qgs->setBrushSize(w,h);
}

void popupDisplayWindow::setBackgroundColour(QColor s_colour)
{
    QBrush x;
    x.setColor(s_colour);
    qgs->setBackgroundBrush(x.color());

}

void popupDisplayWindow::setBrushColour(QColor b_colour)
{
    qgs->paintBrush.setColor(b_colour);
    qgs->paintBrush_outer.setColor(b_colour);
}





float QPaintSceneC::setBrushSize(float w, float h)
{
    bsX = w;
    bsY = h;
    return 0;
}

void popupDisplayWindow::p_addText(QString txtToDraw)
{
    QFont calibri("Calibri",14,QFont::Bold);
    qgs->addText(txtToDraw,calibri);
    
}

void popupDisplayWindow::setActiveBrushType(int abt)
{
    qgs->setActiveBrushType(abt);
}

void QPaintSceneC::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->MouseButtonPress){
        if(getActiveBrushType() == SQUARE_BRUSH){
            this->addRect(event->scenePos().x() - (bsX / 2),event->scenePos().y() - (bsY / 2),bsX,bsY,paintBrush_outer,paintBrush);
            qDebug() << "Mouse Event Handler Active:" <<event->scenePos().x() << "," << event->scenePos().y();
        }else if(getActiveBrushType() == ELIPSE_BRUSH){
            this->addEllipse(event->scenePos().x() - (bsX / 2),event->scenePos().y() - (bsY / 2),bsX,bsY,paintBrush_outer,paintBrush);
            qDebug() << "Mouse Event Handler Active:" <<event->scenePos().x() << "," << event->scenePos().y();
        }else if(getActiveBrushType() == LINE_BRUSH){
            //    this->addLine(event->scenePos().x() - (bsX / 2),event->scenePos().y() - (bsY / 2),bsX,bsY,paintBrush_outer,paintBrush);
            qDebug() << "Mouse Event Handler Active:" <<event->scenePos().x() << "," << event->scenePos().y();
        }
    }
}
void QPaintSceneC::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->MouseButtonPress){
        this->addRect(event->scenePos().x() - (bsX / 2),event->scenePos().y() - (bsY / 2),bsX,bsY,paintBrush_outer,paintBrush);

        qDebug() << "Mouse Event Handler Active:" <<event->scenePos().x() << "," << event->scenePos().y();
    }
}

int QPaintSceneC::getActiveBrushType()
{
    return activeBrushType;
}
void QPaintSceneC::setActiveBrushType(int abt){
    activeBrushType = abt;
}

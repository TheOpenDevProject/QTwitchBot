#ifndef POPUPDISPLAYWINDOW_H
#define POPUPDISPLAYWINDOW_H
#include <QWidget>
#include <QDebug>
namespace Ui {
class popupDisplayWindow;
}

class popupDisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit popupDisplayWindow(QWidget *parent = 0);
    ~popupDisplayWindow()
    {
        qDebug() << "NoteWindow Destroyed";
        delete ui;
    }

private:
    Ui::popupDisplayWindow *ui;
};

#endif // POPUPDISPLAYWINDOW_H

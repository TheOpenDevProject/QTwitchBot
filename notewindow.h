#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QWidget>
#include <QTextEdit>
class NoteWindow : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWindow(QWidget *parent = 0);
    QTextEdit note_edit;
signals:

public slots:

};

#endif // NOTEWINDOW_H

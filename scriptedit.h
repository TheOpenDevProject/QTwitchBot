#ifndef SCRIPTEDIT_H
#define SCRIPTEDIT_H

#include <QWidget>
#include <QFile>
#include <twitchmanager.h>
#include <twitchcommandlist.h>
#include <QStringListModel>
namespace Ui {
class scriptEdit;
}

class scriptEdit : public QWidget
{
    Q_OBJECT

public:
    explicit scriptEdit(QWidget *parent = 0);
    void loadFromFile(QString path_toFile);

    ~scriptEdit();

private slots:
    void on_pushButton_clicked();


private:
    Ui::scriptEdit *ui;
    QFile scriptFile;
};

#endif // SCRIPTEDIT_H

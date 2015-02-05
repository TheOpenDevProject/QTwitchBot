#ifndef LEAGUEMATCHHISTORYBOX_H
#define LEAGUEMATCHHISTORYBOX_H
#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QString>
#include <QWidget>
#include <QListWidgetItem>
class LeagueMatchHistoryBox : public QListWidgetItem
{
    Q_OBJECT
public:
    LeagueMatchHistoryBox();
private:
    bool winStatus;
    QString championPlayed;
    QString item1,item2,item3,item4,item5,item6;
    //UI Elements
    QFrame container;
    QGridLayout internalLayout;

};

#endif // LEAGUEMATCHHISTORYBOX_H

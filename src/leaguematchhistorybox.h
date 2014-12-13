#ifndef LEAGUEMATCHHISTORYBOX_H
#define LEAGUEMATCHHISTORYBOX_H
#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QString>
class LeagueMatchHistoryBox
{
public:
    LeagueMatchHistoryBox();
private:
    bool winStatus;
    QString championPlayed;


};

#endif // LEAGUEMATCHHISTORYBOX_H

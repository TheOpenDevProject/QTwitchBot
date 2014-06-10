#ifndef TWITCHCOMMANDLIST_H
#define TWITCHCOMMANDLIST_H
#include <QFile>
#include <QStringList>
#include <QMap>
class TwitchCommandList
{
public:
    TwitchCommandList();
    QMap<QString,QString> loadFromFile(QString file_name);
private:
    QMap<QString,QString> commandTree; //Our Key is a string and our return is a string
};

#endif // TWITCHCOMMANDLIST_H

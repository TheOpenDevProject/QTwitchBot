#ifndef TWITCHUSER_H
#define TWITCHUSER_H
#include <QString>
struct TwitchUser
{
public:
    void setUsername(QString username);
    void setAccessLevel(int cmdLevel);
    int getAccessLevel();
    QString getTwitchUsername();
    TwitchUser(QString username, int cmdLevel);
    TwitchUser();
protected:
    QString twitchUsername;
    int accessLevel;
};

#endif // TWITCHUSER_H

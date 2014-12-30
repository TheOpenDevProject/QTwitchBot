#include "twitchuser.h"

TwitchUser::TwitchUser(QString username,int cmdLevel){
    twitchUsername = username;
    accessLevel = cmdLevel;
}
TwitchUser::TwitchUser(){

}

void TwitchUser::setUsername(QString username)
{
    twitchUsername = username;
}

void TwitchUser::setAccessLevel(int cmdLevel)
{
    accessLevel = cmdLevel;
}

int TwitchUser::getAccessLevel()
{
    return accessLevel;
}

QString TwitchUser::getTwitchUsername(){
return twitchUsername;
}

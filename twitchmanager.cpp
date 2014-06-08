#include "twitchmanager.h"

twitchManager::twitchManager(QObject *parent) :
    QObject(parent)
{
    messageHistory << "Test";
}

void twitchManager::connectToChannel(QString server, int port, QString t_Nick, QString t_realName, QString t_channel, QString t_username, QString t_oAuthToken){

}

QStringList twitchManager::getMessageHistory(){
    return messageHistory;
}

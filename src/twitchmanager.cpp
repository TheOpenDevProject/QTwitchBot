#include "twitchmanager.h"
#include <QMapIterator>
#include <QTime>

twitchManager::twitchManager()
{
connect(updateCommandRate,SIGNAL(timeout()),this,SLOT(updateCommandRate_Slot()));
}

void twitchManager::connectToChannel(QString server, int port, QString t_Nick, QString t_realName, QString t_channel, QString t_username, QString t_oAuthToken){
    messageHistory << "This is dedicated to Dale Perlov - Thanks for being strong for us - Zac Morris";
    messageHistory << "Attempting to connect to tmi.twitch.tv...";
    local_net_settings.push_back(server);
    local_net_settings.push_back(QString::number(port)); //This must be converted back to an integer for use
    local_net_settings.push_back(t_realName);
    local_net_settings.push_back(t_channel);
    local_net_settings.push_back(t_username);
    local_net_settings.push_back(t_oAuthToken);
    local_net_settings.push_back(t_Nick);
    messageHistory << "Store settings (OK)";
    twitch_socket = new QTcpSocket(this);
    connect(twitch_socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(twitch_socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(twitch_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    twitch_socket->connectToHost(server,port);
    if(!twitch_socket->waitForConnected()){
        messageHistory << "Unable to connect to tmi.twitch.tv";
   }else{
        messageHistory << "Connected!";
    //    updateCommandRate->start(3000);

        }
   }

QStringList twitchManager::getMessageHistory(){
    return messageHistory;
}

void twitchManager::sendMessage(QString rawMessage)
{
    QByteArray message_to_send;
    message_to_send.append("PRIVMSG #");
    message_to_send.append(local_net_settings.at(3));
    message_to_send.append(" :");
    message_to_send.append(rawMessage);
    message_to_send.append("\r\n");
   twitch_socket->write(message_to_send);
   twitch_socket->flush();
   messageHistory << "Message to stream(" + rawMessage + ")";
}

void twitchManager::sendRaw(QByteArray rawMessage)
{
    rawMessage.append("\r\n");
    twitch_socket->write(rawMessage);
    twitch_socket->flush();
    messageHistory << "Raw Command Sent to tmi.twitch.tv: " + rawMessage;
}

void twitchManager::getModeratorList()
{
sendMessage("/mods");
}

void twitchManager::connected(){
//This is all done acording to the RFC published by the ieef
    QByteArray oAuthToken;
    oAuthToken.append("PASS ");
    oAuthToken.append(local_net_settings.at(5)); //Setting number 5 is the token
    oAuthToken.append("\r\n");
    twitch_socket->write(oAuthToken); //Send to twitch and beg the gate keeper to let us past this stage!
    twitch_socket->flush();
    /////////////////////////////////////////////////////////////////////
    QByteArray nickArray;
    nickArray.append("NICK ");
    nickArray.append(local_net_settings.at(3));
    nickArray.append("\r\n");
    twitch_socket->write(nickArray);
    twitch_socket->flush();
    ////////////////////////////////////////////////////////////////////
    QByteArray nsIdentity; // Send matching nick to nickserv
    nsIdentity.append("USER ");
    nsIdentity.append(local_net_settings.at(4)); //Setting 4 is nickname
    nsIdentity.append(" 8 *: ");
    nsIdentity.append(local_net_settings.at(2)); //Setting 2 is real name
    nsIdentity.append("\r\n");
    twitch_socket->write(nsIdentity);
    twitch_socket->flush();
    //////////////////////////////////////////////////////////////////////
    //Finally join the stream!                                                                      //
    ////////////////////////////////////////////////////////////////////
    QByteArray channelJoin;
    channelJoin.append("JOIN #");
    channelJoin.append(local_net_settings.at(3));
    channelJoin.append("\r\n");
    twitch_socket->write(channelJoin);
    twitch_socket->flush();
}

void twitchManager::disconnected(){

}

void twitchManager::readyRead(){
    QByteArray array;


    while( !(array = twitch_socket->readLine()).isNull()){
   commandHandler(array);
    messageHistory << array;
    }
    qDebug() << messageHistory;
}

void twitchManager::getTime()
{
    QTime sysTime;
   sendMessage(sysTime.currentTime().toString());
}
void twitchManager::randomNumber(){
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
   sendMessage(QString::number(qrand() % (1000 - 1) - (0) + 0));
}

void twitchManager::setCommandList(QMap<QString, QString> commandMap){
    commandMap_kp = commandMap;
    qDebug() << commandMap_kp;
}


void twitchManager::commandHandler(QString streamInput){
  //  commandExpression.setPattern("(?<=");
    if(streamInput == "PING :tmi.twitch.tv\r\n"){
    twitch_socket->write("PONG tmi.twitch.tv\r\n");
            twitch_socket->flush();
            qDebug() << "Pong Sent";
    }

   commandExpression.setPattern("(?<=PRIVMSG\\s#"+ local_net_settings.at(3) +"\\s:).*");
   commandMatchFound = commandExpression.match(streamInput);
   bool hasMatch = commandMatchFound.hasMatch();
   if(hasMatch){
      commandRateMS++;
   QString commandFound = commandMatchFound.captured();
   commandFound.chop(1);
   QMapIterator<QString,QString> map_ittr(commandMap_kp);
    while(map_ittr.hasNext()){
        map_ittr.next();
        if(map_ittr.key().at(0) == '[' && map_ittr.key().at(1) == 'M' && map_ittr.key().at(2) == ']'){

                   QString keyNoFlag =  map_ittr.key();
                   keyNoFlag.remove(0,2);

                if(keyNoFlag == commandFound){
                for(int i = 0; i < tmiServices->getModerators().size(); i++){
                    if(streamInput.split("!",QString::SkipEmptyParts).first() == tmiServices->getModerators().at(i)){
                        qDebug() << "Moderator Command Sent from Moderator";
                        }
                    }
                }
        }
        if(map_ittr.key() == commandFound){
            //This could be moved into a function pointer array if the list of functions get big
            //We need to deal with the end new line characters if they are present
            if(map_ittr.value() == "[GetTime]\r\n" || map_ittr.value() == "[GetTime]"){
                getTime();
            }else if(map_ittr.value() == "[randomNumber]\r\n" || map_ittr.value() == "[randomNumber]"){
            randomNumber();
            }else if(map_ittr.value() == "[nextSong]\r\n" || map_ittr.value() == "[nextSong]"){
                m_player->nextSong();
            }else if(map_ittr.value() == "[prevSong]\r\n" || map_ittr.value() == "[prevSong]"){
            m_player->prevSong();
            }else if(map_ittr.value() == "[whatNext]\r\n" || map_ittr.value() == "[whatNext]"){
                sendMessage(QUrl(m_player->getNextSong()).toString(0x0));
            }else if(map_ittr.value() == "[Riot::getSummonerLevel]\r\n" ||  map_ittr.value() == "[Riot::getSummonerLevel]"){
                //#14
                 sendMessage(r_api->getSummonerName() + " is currently level: " +r_api->getSummonerLevel());
            }else if(map_ittr.value() == "[Riot::getRankedSummary]\r\n" ||  map_ittr.value() == "[Riot::getRankedSummary]"){
                //#15
                sendMessage(r_api->getSummonerName() + " Is currently " + ranked_api->getTier() + " " + ranked_api->getDivision() + " " + ranked_api->getLeaguePoints() + "LP");
            }else{
            sendMessage(map_ittr.value());
            qDebug() << map_ittr.value();
           }

          }
        }
    }
}



QStringList twitchManager::getCommandKeysAsStringList()
{
    if(!commandMap_kp.isEmpty()){
        QStringList keyList;
       QMapIterator<QString,QString>map_ittr(commandMap_kp);
       while(map_ittr.hasNext()){
           map_ittr.next();
            keyList << map_ittr.key();
       }
       return keyList;
    }else{
    qDebug() << "No Keys Found!";
    }

}

void twitchManager::setMusicPlayer(MusicPlayer *p_m_player)
{
    m_player = p_m_player;
}

int twitchManager::getCommandRate()
{
    return commandRateMS;
}
//We refresh our command rate at an interval of 3 secconds
void twitchManager::updateCommandRate_Slot() {
    commandRateMS = 0;
}
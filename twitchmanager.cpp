#include "twitchmanager.h"
#include <QMapIterator>
#include <QTime>
twitchManager::twitchManager()
{

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

void twitchManager::setCommandList(QMap<QString, QString> commandMap){
    commandMap_kp = commandMap;
    qDebug() << commandMap_kp;
}

void twitchManager::commandHandler(QString streamInput){
   commandExpression.setPattern("(?<=PRIVMSG\\s#"+ local_net_settings.at(3) +"\\s:).*");
   commandMatchFound = commandExpression.match(streamInput);
   bool hasMatch = commandMatchFound.hasMatch();
   if(hasMatch){
   QString commandFound = commandMatchFound.captured();
   commandFound.chop(1);
   QMapIterator<QString,QString> map_ittr(commandMap_kp);
    while(map_ittr.hasNext()){
        map_ittr.next();
        if(map_ittr.key() == commandFound){
            //This could be moved into a function pointer array if the list of functions get big
            if(map_ittr.value() == "[GetTime]"){
                getTime();
            }else{
            sendMessage(map_ittr.value());
            qDebug() << map_ittr.value();
           }
          }
        }
    }
}

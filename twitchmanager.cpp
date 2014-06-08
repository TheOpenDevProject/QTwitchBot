#include "twitchmanager.h"

twitchManager::twitchManager(QObject *parent) :
    QObject(parent)
{

}

void twitchManager::connectToChannel(QString server, int port, QString t_Nick, QString t_realName, QString t_channel, QString t_username, QString t_oAuthToken){
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

    }


    }

QStringList twitchManager::getMessageHistory(){
    return messageHistory;
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
    QByteArray nsIdentity; // Send matching nick to nickserv
    nsIdentity.append("USER ");
    nsIdentity.append(local_net_settings.at(4)); //Setting 4 is nickname
    nsIdentity.append(" 8 *: ");
    nsIdentity.append(local_net_settings.at(2)); //Setting 2 is real name
    nsIdentity.append("\r\n");
    twitch_socket->write(nsIdentity);
    twitch_socket->flush();
    /////////////////////////////////////////////////////////////////////
    //Finally join the stream!
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
    while( !(array=twitch_socket->readLine()).isNull()){
        qDebug() << array;
    messageHistory << array;
    }
}


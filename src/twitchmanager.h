#ifndef TWITCHMANAGER_H
#define TWITCHMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTimer>
#include <QStringList>
#include <QMap>
#include <QTimer>
#include "musicplayer.h"
#include "apimanager.h"
#include "twitchjsonapiamanger.h"
class twitchManager : public QObject
{
    Q_OBJECT
public:
    explicit twitchManager();
    void connectToChannel(QString server,int port,QString t_Nick,QString t_realName,QString t_channel,QString t_username,QString t_oAuthToken);
    QStringList getMessageHistory();
    void setCommandList(QMap<QString,QString> commandMap);
    void sendMessage(QString rawMessage);
    void sendRaw(QByteArray rawMessage);
    void getModeratorList();
    void commandHandler(QString streamInput);
    QStringList getCommandKeysAsStringList();
    QTimer *updateCommandRate = new QTimer(this);
    void setMusicPlayer(MusicPlayer *p_m_player);
    int getCommandRate();

    RiotAPI *r_api;
    RiotAPI_RankedStats *ranked_api;
    TwitchJSONAPIAManger *tmiServices;
signals:



public slots:
    void connected();
    void disconnected();
    void readyRead();
    void updateCommandRate_Slot();
private:
    int commandRateMS = 0;

    QStringList local_net_settings;
    QTcpSocket *twitch_socket;
    QStringList messageHistory;
    QMap<QString,QString>commandMap_kp;
    QRegularExpression commandExpression;
    QRegularExpressionMatch commandMatchFound;
    //Here is where we can create special functions and make internal calls
    void getTime();
    void randomNumber();
    QString getCallingUser(QString rawIRCData);
    MusicPlayer *m_player;
    QMap<QString,int> accessLevel;

    bool isModerator(QString rawIRCData);
};

#endif // TWITCHMANAGER_H

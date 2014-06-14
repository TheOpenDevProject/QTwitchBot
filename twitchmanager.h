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
class twitchManager : public QObject
{
    Q_OBJECT
public:
    explicit twitchManager();
    void connectToChannel(QString server,int port,QString t_Nick,QString t_realName,QString t_channel,QString t_username,QString t_oAuthToken);
    QStringList getMessageHistory();
    void setCommandList(QMap<QString,QString> commandMap);
    void sendMessage(QString rawMessage);
    void commandHandler(QString streamInput);
    QStringList getCommandKeysAsStringList();
    QTimer *updateCommandRate = new QTimer(this);
    int getCommandRate();
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


};

#endif // TWITCHMANAGER_H

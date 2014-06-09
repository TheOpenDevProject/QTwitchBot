#ifndef TWITCHMANAGER_H
#define TWITCHMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTimer>
#include <QStringList>
class twitchManager : public QObject
{
    Q_OBJECT
public:
    explicit twitchManager();
    void connectToChannel(QString server,int port,QString t_Nick,QString t_realName,QString t_channel,QString t_username,QString t_oAuthToken);
    QStringList getMessageHistory();
signals:



public slots:
    void connected();
    void disconnected();
       void readyRead();
private:
     QStringList local_net_settings;
    QTcpSocket *twitch_socket;
    QStringList messageHistory;
};

#endif // TWITCHMANAGER_H

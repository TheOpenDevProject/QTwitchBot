#include "twitchcommandlist.h"
#include <QDebug>
TwitchCommandList::TwitchCommandList()
{
}

QMap<QString, QString> TwitchCommandList::loadFromFile(QString file_name,QFile c_File)
{
   //Reset the commandTree from any other times the user loaded the file in this session
    commandTree.clear();
    /////////////////////
    c_File.setFileName(file_name);
    if(!c_File.open(QIODevice::ReadOnly)){
        qDebug() << "File did not load"; //This way we can push an error into the messageHistory
    }else{
   //It worked
    while(!c_File.atEnd()){
        //This is quite a simple algorithm,
        // All we are doing is reading in the file line by line and spliting it by csv and adding it to our map
   QString keyPair = c_File.readLine();
   QStringList keyPairList = keyPair.split(",");
        commandTree.insert(keyPairList.at(0),keyPairList.at(1));
        }
    }
    qDebug() << commandTree; //#Remove before release
    return commandTree;
}

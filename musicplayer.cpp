#include "musicplayer.h"
#include <QTime>
MusicPlayer::MusicPlayer()
{

}
//N-P
void MusicPlayer::nextSong()
{
 m_mediaPlaylist->next();
}
void MusicPlayer::prevSong(){
    m_mediaPlaylist->previous();
}
//PPP
void MusicPlayer::play(){
    m_mediaPlayer->play();
}

void MusicPlayer::pause(){
    m_mediaPlayer->pause();
}
void MusicPlayer::stop(){
    m_mediaPlayer->stop();
}
//LoadFromFile
void MusicPlayer::setPlaylistFromFile(QStringList songList){
    m_mediaPlaylist->clear();
    for(int i = 0; i < songList.size(); i++){
    m_mediaPlaylist->addMedia(QUrl(songList.at(i)));
    }
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
}

//SetVolume
void MusicPlayer::setVolume(int vol){
    m_mediaPlayer->setVolume(vol);
}

//QTime MusicPlayer::getCurrentSongTime()
//{
  // return QTime:: m_mediaPlayer->position();
//}

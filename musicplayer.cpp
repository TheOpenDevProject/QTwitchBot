#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{

}

void MusicPlayer::nextSong()
{
 m_mediaPlaylist->next();
}

void MusicPlayer::setPlaylistFromFile(QStringList songList){
    m_mediaPlaylist->clear();
    for(int i = 0; i < songList.size(); i++){
    m_mediaPlaylist->addMedia(QUrl(songList.at(i)));
    }
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
}

void MusicPlayer::play(){
    m_mediaPlayer->play();
}

void MusicPlayer::pause(){
    m_mediaPlayer->pause();
}
void MusicPlayer::setVolume(int vol){
    m_mediaPlayer->setVolume(vol);
}

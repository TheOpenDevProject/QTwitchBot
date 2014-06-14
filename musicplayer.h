#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QMediaPlayer>
#include <QMediaPlaylist>
class MusicPlayer
{
public:
    MusicPlayer();
    void nextSong();
    void prevSong();
    void pause();
    void play();
    void setPlaylistFromFile(QStringList songList);
    void setVolume(int vol);
private:
    QMediaPlayer *m_mediaPlayer = new QMediaPlayer;
    QMediaPlaylist *m_mediaPlaylist = new QMediaPlaylist(m_mediaPlayer);
};

#endif // MUSICPLAYER_H

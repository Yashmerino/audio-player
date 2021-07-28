#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class Audioplayer
{
public:
    Audioplayer();

    ~Audioplayer();

private:
    QMediaPlayer* player; // Creating a QMediaPlayer and QMediaPlaylist to work with audio
    QMediaPlaylist* playlist;

};

#endif // AUDIOPLAYER_H

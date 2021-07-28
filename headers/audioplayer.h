#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>

class Audioplayer
{
public:
    Audioplayer();

    ~Audioplayer();

public:
    QMediaPlayer* player; // Creating a QMediaPlayer and QMediaPlaylist to work with audio
    QMediaPlaylist* playlist;

    QString file_path;

    QFileInfo* file_info;
};

#endif // AUDIOPLAYER_H

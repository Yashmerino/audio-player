#include "headers/audioplayer.h"

Audioplayer::Audioplayer() // Constructor of the class Audioplayer
{
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();
}

Audioplayer::~Audioplayer() // Destructor of the class Audioplayer
{
   delete player;
   delete playlist;
   delete file_info;
}

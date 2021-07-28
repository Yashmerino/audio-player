#include "headers/audioplayer.h"

Audioplayer::Audioplayer() // Constructor of the class Audioplayer
{
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();

    timer.setInterval(100); // Timeout interval is equal to 100 ms (0.1 s)
    timer.start();
}

Audioplayer::~Audioplayer() // Destructor of the class Audioplayer
{
   delete player;
   delete playlist;
   delete file_info;
}

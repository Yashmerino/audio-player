#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectbutton_clicked() // If select file button is clicked
{
    QString filter = "All File (*.mp3, *.ogg, *.wav)"; // Filter to show only audio files

    audioplayer.file_path = QFileDialog::getOpenFileName(this, "Select a file", "C://", filter); // Get file path

    audioplayer.file_info = new QFileInfo(audioplayer.file_path); // Initializing QFileInfo

    if(audioplayer.file_path.isEmpty() || (audioplayer.file_info->suffix() != "mp3" && // If no file was selected or it's not an audio file
                                           audioplayer.file_info->suffix() != "wav" &&
                                           audioplayer.file_info->suffix() != "ogg"))
    {
        QMessageBox::warning(this, "Error", "Something went wrong!");
    }
    else
    {
        QMessageBox::information(this, "Succes", audioplayer.file_info->fileName() + " has been selected!");
        audioplayer.playlist->addMedia(QUrl(audioplayer.file_path)); //Adding file to playlist

        audioplayer.player->setPlaylist(audioplayer.playlist);
        audioplayer.player->setVolume(50);

        connect(audioplayer.player, &QMediaPlayer::durationChanged, this, [&](qint64 duration) // If caught signal that duration changed
        {                                                                                      // change text label content in ui
            set_durationText();
            qDebug() << duration;
        });
    }
}


void MainWindow::on_playbutton_clicked() // If play button is clicked
{
    connect(audioplayer.timer, SIGNAL(timeout()), this, SLOT(set_timelineSliderValue())); // Execute set_timelineSliderValue() every 100 ms

    audioplayer.player->setVolume(ui->volume->sliderPosition()); // Change the volume if initial position of volume slider changed

    audioplayer.player->play();
}

void MainWindow::on_pauseButton_clicked() // If pause button is clicked
{
    disconnect(audioplayer.timer, SIGNAL(timeout()), this, SLOT(set_timelineSliderValue())); // Stop exectuing set_timelineSliderValue() every 100 ms

    audioplayer.player->pause();
}


void MainWindow::on_volume_valueChanged(int value) // Change volume in dependence of volume slider's position
{
    audioplayer.player->setVolume(value);
}

void MainWindow::set_timelineSliderValue() // Move slider's position in dependance of audio's position
{
    set_currentPositionText(0);

    ui->timeline->setValue(audioplayer.player->position() * 100 / audioplayer.player->duration());
}


void MainWindow::on_timeline_valueChanged(int value) // Change audio's position if slider's position changed
{
    set_currentPositionText(value);

    audioplayer.player->setPosition(audioplayer.player->duration() * value / 100);
}

void MainWindow::set_durationText() // Set label text duration of audio
{
    qint64 duration = audioplayer.player->duration();
    QTime time(0,(duration % (1000 * 60 * 60)) / (1000 * 60),(duration % (1000 * 60)) / 1000);
    ui->duration->setText(time.toString("mm:ss"));
}

void MainWindow::set_currentPositionText(int value) // Set label text current position of audio
{
    qint64 duration;

    if(value == 0)
    {
        duration = audioplayer.player->position();
    }
    else
    {
        duration = audioplayer.player->duration() * value / 100;
    }
    QTime time(0,(duration % (1000 * 60 * 60)) / (1000 * 60),(duration % (1000 * 60)) / 1000);
    ui->currentPosition->setText(time.toString("mm:ss"));
}

void MainWindow::on_loop_clicked(bool checked) // If loop box checked then loop the audio
{
    if(checked)
    {
        audioplayer.playlist->setPlaybackMode(QMediaPlaylist::Loop);
    }
    else
    {
        audioplayer.playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    }
}


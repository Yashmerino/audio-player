#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

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

    }
}


void MainWindow::on_playbutton_clicked() // If play button is clicked
{
    audioplayer.player->play();
}

void MainWindow::on_pauseButton_clicked() // If pause button is clicked
{
    audioplayer.player->pause();
}


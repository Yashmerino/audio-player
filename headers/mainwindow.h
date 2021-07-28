#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers/audioplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectbutton_clicked();

    void on_playbutton_clicked();

    void on_pauseButton_clicked();

private:
    Ui::MainWindow *ui;
    Audioplayer audioplayer;
};
#endif // MAINWINDOW_H

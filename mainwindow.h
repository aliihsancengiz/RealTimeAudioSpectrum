#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioFormat>
#include <QAudioDecoder>
#include "spectrum.h"
#include "audiodata.h"
#include "FFTObj.h"
#include <cmath>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        Spectrum mSpectrum;
        QTimer *updateTimer;
        QFileDialog *fileLoad;
        AudioData* audio_data;
        float buffer[1024]={0};
        float frameBuffer[1024]={0};
        QMediaPlayer* mPlayer;

private slots:
    void TimerExpires();
    void Load_files();
    void StartSpectrumAnalyzer();

};
#endif // MAINWINDOW_H

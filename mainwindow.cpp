#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mSpectrum.add_freq_bar(ui->freq1);
    this->mSpectrum.add_freq_bar(ui->freq2);
    this->mSpectrum.add_freq_bar(ui->freq3);
    this->mSpectrum.add_freq_bar(ui->freq4);
    this->mSpectrum.add_freq_bar(ui->freq5);
    this->mSpectrum.add_freq_bar(ui->freq6);
    this->mSpectrum.add_freq_bar(ui->freq7);
    this->mSpectrum.add_freq_bar(ui->freq8);
    this->mSpectrum.add_freq_bar(ui->freq9);
    this->mSpectrum.add_freq_bar(ui->freq10);

    this->ui->freq1->setValue(0);
    this->ui->freq2->setValue(0);
    this->ui->freq3->setValue(0);
    this->ui->freq4->setValue(0);
    this->ui->freq5->setValue(0);
    this->ui->freq6->setValue(0);
    this->ui->freq7->setValue(0);
    this->ui->freq8->setValue(0);
    this->ui->freq9->setValue(0);
    this->ui->freq10->setValue(0);

    updateTimer=new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(TimerExpires()));

    fileLoad=new QFileDialog(this);
    connect(ui->LoadFile,SIGNAL(clicked()),this,SLOT(Load_files()));

    connect(ui->StartSpectrum,SIGNAL(clicked()),this,SLOT(StartSpectrumAnalyzer()));

    mPlayer= new QMediaPlayer;
}

MainWindow::~MainWindow()
{
    delete updateTimer;
    delete ui;
}

void MainWindow::TimerExpires()
{
    QVector<float> ex;
    uint32_t s;
    // Get a frame
    audio_data->getFrame(frameBuffer,&s);
    if(s == 1024)
    {
        // Do fft
        fft_object.do_fft(buffer,frameBuffer);

        // take absolute value of fft to get ride of complex number
        for(int i=0;i<512;i++)
        {
            buffer[i]=sqrt(buffer[i]*buffer[i]+buffer[i+512]*buffer[i+512]);
        }

        // Normalize frequency into bar
        for (int i=0;i<10;i++ )
        {
            float sum=0;
            for (int j=0;j<51 ;j++ )
            {
                    sum+=buffer[i*51+j];
            }
            ex.append(sum);
        }

        // Take Maximum
        float m=*std::max_element(ex.constBegin(),ex.constEnd());

        // Set Max Power 100
        for (int i=0;i<10 ;i++ )
        {
            ex[i]=(ex[i]/m)*100;
        }

        // Update Bars
        mSpectrum.update(ex);
    }
    else
    {
        // if there is no Frame to process,stop the processing
        updateTimer->stop();
    }

}

void MainWindow::Load_files()
{
    QString filename(QFileDialog::getOpenFileName(this, "","C:/",""));
    audio_data=new AudioData(filename.toStdString().c_str());
    this->ui->FileUrl->setText(filename);
    mPlayer->setMedia(QUrl::fromLocalFile(filename.toStdString().c_str()));
    mPlayer->setVolume(70);
}

void MainWindow::StartSpectrumAnalyzer()
{
    qDebug("Started");
    // The reason for chosing 23 is that every 23ms we take 1024 samples
    // So total number of samples is (1000/23)*1024 which is approximately 44.1kHz

    // From testing result 19ms is timer Interrupt will be better for Real Time
    updateTimer->start(19);
    mPlayer->play();

}


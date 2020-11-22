#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QMainWindow>
#include <QVector>
#include <QProgressBar>

class Spectrum : public QMainWindow
{
        Q_OBJECT
    public:
        explicit Spectrum(QWidget *parent = nullptr);
        void add_freq_bar(QProgressBar* bar);
        void update(QVector<float> values);
    private:
        QVector<QProgressBar*>  mFrequencies;

    signals:

};

#endif // SPECTRUM_H

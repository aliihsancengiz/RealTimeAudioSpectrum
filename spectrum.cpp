#include "spectrum.h"
#include <QDebug>
#include <QString>
#include <iostream>

Spectrum::Spectrum(QWidget *parent) : QMainWindow(parent)
{

}

void Spectrum::add_freq_bar(QProgressBar *bar)
{
    bar->setMaximum(100);
    bar->setMinimum(0);
    this->mFrequencies.append(bar);
}

void Spectrum::update(QVector<float> values)
{
//    QString a=QString::number(values.size());
//    const char * str=a.toStdString().c_str();
//    qDebug(str);

    for (int i=0;i<this->mFrequencies.size();i++ )
    {
        this->mFrequencies[i]->setValue(static_cast<int>(values[i]));
    }

}

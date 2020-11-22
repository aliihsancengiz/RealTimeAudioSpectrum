#ifndef AUDIODATA_H
#define AUDIODATA_H

#include <cstdint>
#include <iostream>
#include "WavReader/AudioFile.h"


class AudioData
{
    private:
        uint32_t SampleRate,numberofChannels,NumberOfSamples;
        float* pData;
        uint32_t frameSize=1024;
        uint32_t leftToProcess;
        uint32_t numberOfFrame=0;
    public:
        AudioData();
        AudioData(const char * filename);
        void setFrameSize(uint32_t fs);
        void getFrame(float *ptr,uint32_t* size);
        uint32_t getLeftToProcess(){return leftToProcess;}
};

#endif // AUDIODATA_H

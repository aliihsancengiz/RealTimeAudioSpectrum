#include "audiodata.h"

AudioData::AudioData():SampleRate(0),numberofChannels(0),NumberOfSamples(0)
{

}

AudioData::AudioData(const char * filename)
{
    AudioFile<float> wavFile;
    wavFile.load(filename);
    pData=new float[wavFile.getNumSamplesPerChannel()];
    for(int i=0;i<wavFile.getNumSamplesPerChannel();i++)
    {
        pData[i]=wavFile.samples[0][i];
    }
    numberofChannels=wavFile.getNumChannels();
    SampleRate=wavFile.getSampleRate();
    NumberOfSamples=wavFile.getNumSamplesPerChannel();
    leftToProcess=NumberOfSamples;
}


void AudioData::setFrameSize(uint32_t fs)
{
    this->frameSize=fs;
}

void AudioData::getFrame(float *ptr,uint32_t* size)
{
    if(leftToProcess>0)
    {
        if(this->leftToProcess > this->frameSize )
        {
         *size=this->frameSize;
         for(uint32_t i=0;i<frameSize;i++)
         {
          ptr[i]=pData[numberOfFrame*frameSize+i];
         }
         numberOfFrame++;
         leftToProcess-=frameSize;
        }
        else
        {
            *size=this->leftToProcess;
            for(uint32_t i=0;i<*size;i++)
            {
                ptr[i]=pData[numberOfFrame*frameSize+i];
            }
             numberOfFrame++;
             leftToProcess-=*size;
        }
    }
    else
    {
        *size=0;
    }
}

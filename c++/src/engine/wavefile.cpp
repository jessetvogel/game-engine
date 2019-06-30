#include "wavefile.hpp"
#include <fstream>

float float_from_8bit(char x) {
    return -1.0f + 2.0f / UINT8_MAX * ((uint8_t) x);
}

float float_from_16bit(char x, char y) {
    uint16_t z = ((uint8_t) x) + (((uint8_t) y) << 8) - INT16_MIN;
    return -1.0f + 2.0f / UINT16_MAX * z;
}

WaveFile::WaveFile(std::string path) {
    // Open file for binary reading
    std::ifstream file(path);
    if(file.fail())
        return;
    
    // Read header
    file.read(ChunkID, sizeof(ChunkID));
    file.read((char*) &ChunkSize, sizeof(ChunkSize));
    file.read(Format, sizeof(Format));
    file.read(Subchunk1ID, sizeof(Subchunk1ID));
    file.read((char*) &Subchunk1Size, sizeof(Subchunk1Size));
    file.read((char*) &AudioFormat, sizeof(AudioFormat));
    file.read((char*) &NumChannels, sizeof(NumChannels));
    file.read((char*) &SampleRate, sizeof(SampleRate));
    file.read((char*) &ByteRate, sizeof(ByteRate));
    file.read((char*) &BlockAlign, sizeof(BlockAlign));
    file.read((char*) &BitsPerSample, sizeof(BitsPerSample));
    file.read(Subchunk2ID, sizeof(Subchunk2ID));
    file.read((char*) &Subchunk2Size, sizeof(Subchunk2Size));
    
    // Before using these values, check if they are valid
    if(!valid())
        return;
    
    // Allocate space and read data
    Data = new char[Subchunk2Size];
    file.read(Data, Subchunk2Size);
    
    // Compute the amount of samples
    size_t bytesPerSample = NumChannels * BitsPerSample / 8;
    NumSamples = (bytesPerSample > 0 ? Subchunk2Size / bytesPerSample : 0);
}

WaveFile::~WaveFile() {
    // Free the space used for the data
    if(Data != nullptr)
        delete[] Data;
}

bool WaveFile::valid() {
    if(strncmp(ChunkID, "RIFF", 4) != 0)
        return false;
    
    if(strncmp(Format, "WAVE", 4) != 0)
        return false;
    
    if(strncmp(Subchunk1ID, "fmt ", 4) != 0)
        return false;
    
    if(strncmp(Subchunk2ID, "data", 4) != 0)
        return false;
    
    if(BitsPerSample != 8 && BitsPerSample != 16)
        return false;
    
    return true;
}

float* WaveFile::getChannelData(uint32_t channel) {
    // Allocate an array of floats
    float* data = new float[NumSamples];
    
    // Read data from given channel
    if(BitsPerSample == 8) {
        char* ptr = Data + channel;
        for(size_t i = 0;i < NumSamples; ++i) {
            data[i] = float_from_8bit(*ptr);
            ptr += NumChannels;
        }
    }
    
    if(BitsPerSample == 16) {
        char* ptr = Data + channel * 2;
        for(size_t i = 0;i < NumSamples; ++i) {
            data[i] = float_from_16bit(*ptr, *(ptr + 1));
            ptr += NumChannels * 2;
        }
    }
    
    return data;
}

double WaveFile::getDuration() {
    return (double) NumSamples / SampleRate;
}

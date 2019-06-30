// Reference: http://soundfile.sapp.org/doc/WaveFormat/

#include <cstdint>
#include <string>

typedef float sample_t;

class WaveFile {

public:
    
    char ChunkID[4] = { 0 };
    uint32_t ChunkSize;
    char Format[4];
    char Subchunk1ID[4];
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
    char Subchunk2ID[4];
    uint32_t Subchunk2Size;
    char* Data = nullptr;
    uint32_t NumSamples;
    
    WaveFile(std::string);
    ~WaveFile();
    
    bool valid();
    double getDuration();
    float* getChannelData(uint32_t);
    
};

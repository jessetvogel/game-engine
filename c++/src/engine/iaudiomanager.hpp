#ifndef iaudiomanager_hpp
#define iaudiomanager_hpp

#include "types.hpp"

namespace Game {
    
    struct AudioData {
        size_t length;
        float* left;
        float* right;
    };
    
    struct Audio {
        const AudioData* const data;
        
        bool playing = false;
        size_t position = 0;
        float volume = 1.0f;
        float pan = 0.0f;
        float rate = 1.0f;
        
    public:
        
        Audio(const AudioData*);
        
        void seekTo(double);
        void setRate(float);
        void setPan(float);
        void setVolume(float);
        void play();
        void pause();
        bool isPlaying();
        double getLength();
        
    };
    
    class IAudioManager {
        
        AudioData* loadAudioData(std::string);
        
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, AudioData*> audioData;
        
    protected:
        
        std::vector<Audio*> audios;
        
    public:
        
        bool defineAudio(std::string, std::string);
        void cleanUpAudio();
        
        Audio* getAudio(std::string);
        void releaseAudio(Audio*);
        
        virtual bool startAudioStream() = 0;
        virtual bool stopAudioStream() = 0;
        
    };
    
}

#endif

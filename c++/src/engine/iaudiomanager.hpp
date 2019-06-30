#ifndef iaudiomanager_hpp
#define iaudiomanager_hpp

#include "types.hpp"
#include "iresourcemanager.hpp"

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
    
        struct AudioRecord {
            std::string name;
            RefCount refCount;
            Audio* audio;
        };
        
        AudioData* loadAudioData(std::string);
        
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, AudioData*> audioData;
        
    protected:
        
        std::vector<Audio*> audios;
        
    public:
        
        void manageAudio();
        bool defineAudio(std::string, std::string);
        
        Audio* getAudio(std::string);
        void releaseAudio(Audio*);
        
        virtual bool startAudioStream() = 0;
        virtual bool stopAudioStream() = 0;
        
    };
    
}

#endif

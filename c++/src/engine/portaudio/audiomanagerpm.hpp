#ifndef audiomanagerpm_hpp
#define audiomanagerpm_hpp

#include "iaudiomanager.hpp"
#include <portaudio/portaudio.h>

namespace Game {

    class AudioManagerPM : public virtual IAudioManager {
        
        static int audioCallback(const void*, void*, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*);
        
        PaStream* stream;
        bool streaming = false;
        bool stereo;
        
    public:
        
        bool startAudioStream();
        bool stopAudioStream();
        
    };
    
}

#endif

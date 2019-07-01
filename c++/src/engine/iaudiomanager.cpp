#include "iaudiomanager.hpp"
#include "wavefile.hpp"

using namespace std;
using namespace Game;

// ---- Audio ----
Audio::Audio(const AudioData* data) : data(data) {}

void Audio::seekTo(double t) {
    if(t < 0)
        position = 0;
    else
        position = std::min(data->length, (size_t) (t * 44100.0));
}

void Audio::setRate(float r) {
    rate = r;
}

void Audio::setPan(float p) {
    pan = p;
}

void Audio::setVolume(float v) {
    volume = v;
}

void Audio::play() {
    playing = true;
}

void Audio::pause() {
    playing = false;
}

bool Audio::isPlaying() {
    return playing;
}

double Audio::getLength() {
    return (double) data->length / 44100.0;
}

// ---- IAudioManager ----
bool IAudioManager::defineAudio(string name, string path) {
    // Check if 'name' is already defined
    auto it = definitions.find(name);
    if(it != definitions.end())
        return false;
    
    definitions[name] = path;
    return true;
}

Audio* IAudioManager::getAudio(string name) {
    AudioData* data;
    
    // Check if audio data is already loaded
    auto it = audioData.find(name);
    if(it != audioData.end())
        data = it->second;
    else {
        // Create new AudioData from definition
        auto it = definitions.find(name);
        if(it == definitions.end())
            return nullptr;
        
        data = loadAudioData(it->second);
        if(data == nullptr)
            return nullptr;
        
        audioData[name] = data;
    }
    
    Audio* audio = new Audio(data);
    audios.push_back(audio);
    return audio;
}

void IAudioManager::releaseAudio(Audio* audio) {
    // Remove Audio from the list
    auto it = std::find(audios.begin(), audios.end(), audio);
    if(it != audios.end())
        audios.erase(it);
    
    delete audio;
}

AudioData* IAudioManager::loadAudioData(string path) {
    WaveFile wav(path);
    if(!wav.valid())
        return nullptr;
    
    AudioData* data = new AudioData();
    data->length = wav.NumSamples;
    data->left = wav.getChannelData(0);
    data->right = (wav.NumChannels > 1) ? wav.getChannelData(1) : nullptr;
    return data;
}

void IAudioManager::cleanUpAudio() { // TODO: this may be optimized ?
    // Release all AudioData that is not currently in use
    for(auto it = audioData.begin();it != audioData.end();) {
        bool flag = false;
        for(auto audio : audios) {
            if(audio->data == it->second) {
                flag = true;
                break;
            }
        }
        
        if(!flag) {
            delete it->second;
            it = audioData.erase(it);
        }
        else {
            ++it;
        }
    }
}

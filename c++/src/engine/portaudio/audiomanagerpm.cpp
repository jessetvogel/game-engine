#include "audiomanagerpm.hpp"
#include <iostream>

using namespace std;
using namespace Game;

bool AudioManagerPM::startAudioStream() {
    // Set output device and parameters
    PaDeviceIndex outputDevice = Pa_GetDefaultOutputDevice();
    PaStreamParameters outputParams;
    auto outputParamsAddr = &outputParams;
    
    const PaDeviceInfo* outputInfo = Pa_GetDeviceInfo(outputDevice);
    if(outputInfo == nullptr) {
        cout << "no output info" << endl;
        return false;
    }
    
    stereo = (outputInfo->maxOutputChannels >= 2);
    outputParams.device = outputDevice;
    outputParams.channelCount = stereo ? 2 : 1; // If stereo is available, use it
    outputParams.sampleFormat = stereo ? paFloat32 | paNonInterleaved : paFloat32; // If stereo, use nonInterleaved format
    outputParams.suggestedLatency = outputInfo->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = nullptr;
    
    // Try to open audio stream
    PaError error = Pa_OpenStream(&stream,
                                  nullptr,
                                  outputParamsAddr,
                                  44100.0,
                                  256,
                                  paClipOff,
                                  audioCallback,
                                  (void*) this);
    
    if(error != paNoError) {
        cout << "failed to open stream" << endl;
        return false;
    }
    
    // Try to start audio stream
    streaming = true;
    error = Pa_StartStream(stream);
    if(error != paNoError) {
        cout << "failed to start stream" << endl;
        return false;
    }
 
    return true;
}

bool AudioManagerPM::stopAudioStream() {
    streaming = false;
    return true;
}

int AudioManagerPM::audioCallback(const void* inputBuffer,
                                  void* outputBuffer,
                                  unsigned long frames,
                                  const PaStreamCallbackTimeInfo*,
                                  PaStreamCallbackFlags,
                                  void* userData) {
    // Find AudioManagerPM instance
    AudioManagerPM* am = (AudioManagerPM*) userData;

    if(!am->stereo) {
        float* out = (float*) outputBuffer;
        memset(out, 0, sizeof(float) * frames);
        for(auto audio : am->audios) {
            if(!audio->playing)
                continue;
            
            for(int i = 0;i < frames; ++i) {
                if(audio->position >= audio->data->length) {
                    audio->playing = false;
                    break;
                }
                
                out[i] += audio->data->left[audio->position++] * audio->volume;
            }
        }
    }
    else {
        float* left =  ((float**) outputBuffer)[0];
        float* right = ((float**) outputBuffer)[1];
        memset(left, 0, sizeof(float) * frames);
        memset(right, 0, sizeof(float) * frames);
        for(auto audio : am->audios) {
            if(!audio->playing)
                continue;
            
            for(int i = 0;i < frames; ++i) {
                if(audio->position >= audio->data->length) {
                    audio->playing = false;
                    break;
                }
                
                // TODO: implement panning
                left[i] += audio->data->left[audio->position] * audio->volume;
                if(audio->data->right != nullptr)
                    right[i] += audio->data->right[audio->position] * audio->volume;
                ++ audio->position;
            }
        }
    }
    
    // Continue while it should
    return am->streaming ? paContinue : paComplete;
}

#include "mycontroller.hpp"
#include <portaudio/portaudio.h>

using namespace std;
using namespace Game;
using namespace Example;

extern void error(string);

Controller* start(void* view) {
    // Initialize portaudio
    Pa_Initialize();
    
    // Create controller object
    Controller* c = new MyController(view);
    
    // Start audio stream by default
    if(!c->startAudioStream())
        error("Failed to start audio stream!");
        
    return c;
}

void stop(Controller* c) {
    // Delete controller
    delete c;
    
    // Terminate portaudio
    Pa_Terminate();
}

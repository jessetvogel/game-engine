#ifndef mycontroller_hpp
#define mycontroller_hpp

#include "controller.hpp"
#include "texturemanagergl.hpp"
#include "audiomanagerpm.hpp"

namespace Example {
    
    class MyController : public Game::Controller, public Game::TextureManagerGL, public Game::AudioManagerPM {
    
    };
    
}

#endif

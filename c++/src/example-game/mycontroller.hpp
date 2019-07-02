#ifndef mycontroller_hpp
#define mycontroller_hpp

#include "controller.hpp"
#include "texturemanagergl.hpp"
#include "framebuffermanagergl.hpp"
#include "audiomanagerpm.hpp"
#include "windowmanagerglmac.hpp"

namespace Example {
    
    class MyController : public Game::Controller,
                         public Game::TextureManagerGL,
                         public Game::AudioManagerPM,
                         public Game::FrameBufferManagerGL,
                         public Game::WindowManagerGLMac {
        
        
    public:
           
        MyController(void* view) : Game::FrameBufferManagerGL(this, this),
                                   Game::WindowManagerGLMac(view) {}
                             
    
    };
    
}

#endif

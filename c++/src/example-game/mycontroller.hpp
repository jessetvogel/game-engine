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
                         public Game::WindowManagerGLMac
    {
        
        void init();
        
        void onSceneStart();
        
    public:
           
        MyController(void* view) : Game::Controller(),
                                   Game::WindowManagerGLMac(view),
                                   Game::FrameBufferManagerGL(this) { init(); }
    
    };
    
}

#endif

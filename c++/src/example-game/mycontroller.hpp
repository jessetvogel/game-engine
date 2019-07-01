#ifndef mycontroller_hpp
#define mycontroller_hpp

#include "controller.hpp"
#include "texturemanagergl.hpp"
#include "audiomanagerpm.hpp"
#include "fontmanagerft.hpp"

namespace Example {
    
    class MyController : public Game::Controller,
                         public Game::TextureManagerGL,
                         public Game::AudioManagerPM,
                         public Game::FontManagerFT {

    public:
                 
         MyController() : Game::IFontManager(this),
                          Game::FontManagerFT(this) {}
    
    };
    
}

#endif

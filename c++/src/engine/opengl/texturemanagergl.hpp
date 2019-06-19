#ifndef texturemanagergl_hpp
#define texturemanagergl_hpp

#include "itexturemanager.hpp"

namespace Game {

    class TextureManagerGL : virtual public ITextureManager {
    
        ResId loadResource(std::string);
        void freeResource(ResId);
        
    };
    
}

#endif

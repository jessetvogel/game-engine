#ifndef texturemanagergl_hpp
#define texturemanagergl_hpp

#include "itexturemanager.hpp"
#include "opengl.hpp"

namespace Game {

    class TextureManagerGL : virtual public ITextureManager {
    
        TextureId loadTexture(std::string);
        void freeTexture(TextureId);
        
    };
    
}

#endif

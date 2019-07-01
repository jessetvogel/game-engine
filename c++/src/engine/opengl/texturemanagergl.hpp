#ifndef texturemanagergl_hpp
#define texturemanagergl_hpp

#include "itexturemanager.hpp"
#include "opengl.hpp"

namespace Game {

    class TextureManagerGL : virtual public ITextureManager {
    
        TextureId createTexture(unsigned char*, int, int, int);
        void freeTexture(TextureId);        
        
    };
    
}

#endif

#ifndef texturemanagergl_hpp
#define texturemanagergl_hpp

#include "iresourcemanager.hpp"

namespace Game {

    class TextureManagerGL : public IResourceManager {
    
        ResId loadResource(std::string);
        void freeResource(ResId);
        
    public:
        
        ResId getTexture(std::string name) { return get(name); }
        void releaseTexture(ResId id) { return release(id); }
        
    };
    
}

#endif

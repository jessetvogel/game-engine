#ifndef itexturemanager_hpp
#define itexturemanager_hpp

#include "iresourcemanager.hpp"

namespace Game {
    
    class ITextureManager : public IResourceManager {
        
        virtual ResId loadResource(std::string) = 0;
        virtual void freeResource(ResId) = 0;
        
    public:
        
        ResId getTexture(std::string name) { return get(name); }
        void releaseTexture(ResId id) { return release(id); }
        
    };
    
}


#endif

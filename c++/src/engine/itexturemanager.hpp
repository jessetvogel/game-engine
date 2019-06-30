#ifndef itexturemanager_hpp
#define itexturemanager_hpp

#include "iresourcemanager.hpp"

namespace Game {
    
    class ITextureManager {
        
        struct TextureData {
            TextureId id;
            int refCount;
        };
        
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, TextureData> textureData;
        
        virtual TextureId loadTexture(std::string) = 0;
        virtual void freeTexture(ResId) = 0;
        
    public:
        
        void manageTextures();
        bool defineTexture(std::string, std::string);
        
        TextureId getTexture(std::string);
        void releaseTexture(TextureId);
        
    };
    
}


#endif

#ifndef itexturemanager_hpp
#define itexturemanager_hpp

#include "types.hpp"

namespace Game {
    
    class ITextureManager {
        
        struct TextureData {
            TextureId id;
            int refCount;
        };
        
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, TextureData> textureData;
        
        TextureId loadTexture(std::string);
        
        virtual TextureId createTexture(unsigned char*, int, int, int) = 0;
        virtual void freeTexture(TextureId) = 0;
        
    public:
        
        bool defineTexture(std::string, std::string);
        void cleanUpTextures();
        
        TextureId getTexture(std::string);
        TextureId getTexture(unsigned char*, int, int, int);
        void releaseTexture(TextureId);

        
    };
    
}


#endif

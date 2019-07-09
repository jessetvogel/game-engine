#ifndef itexturemanager_hpp
#define itexturemanager_hpp

#include "types.hpp"

namespace Game {
    
    class ITextureManager {
        
        struct TextureData {
            Texture texture;
            int refCount;
        };
        
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, TextureData> textureData;
        
        Texture loadTexture(std::string);
        
        virtual Texture createTexture(unsigned char*, int, int, int) = 0;
        virtual void freeTexture(Texture) = 0;
        
    public:
        
        bool defineTexture(std::string, std::string);
        void cleanUpTextures();
        
        Texture getTexture(std::string);
        Texture getTexture(unsigned char*, int, int, int);
        void releaseTexture(Texture);

        
    };
    
}


#endif

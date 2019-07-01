#ifndef spritemanager_hpp
#define spritemanager_hpp

#include "types.hpp"
#include "itexturemanager.hpp"

namespace Game {
        
    class SpriteManager {
        
        ITextureManager* const textureManager;
        
        std::unordered_map<std::string, SpriteData> definitions;
        
    public:
        
        SpriteManager(ITextureManager* m) : textureManager(m) {}
        
        bool defineSprite(std::string, SpriteData);
        
        Sprite* getSprite(std::string);
        void releaseSprite(Sprite*);
        
    };
    
}

#endif

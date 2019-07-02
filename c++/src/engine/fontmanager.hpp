#ifndef fontmanager_hpp
#define fontmanager_hpp

#include "itexturemanager.hpp"

namespace Game {
    
    class FontManager {
    
        struct FontData {
            Font* font;
            int refCount;
        };
        
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, FontData> fontData;
        
        Font* loadFont(std::string, int);
        
    protected:
        
        ITextureManager* const textureManager;
        
    public:
        
        FontManager(ITextureManager* m) : textureManager(m) {}
        
        bool defineFont(std::string, std::string);
        void cleanUpFonts();
        
        Font* getFont(std::string);
        void releaseFont(Font*);
        
    };
    
}

#endif

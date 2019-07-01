#ifndef ifontmanager_hpp
#define ifontmanager_hpp

#include "itexturemanager.hpp"

namespace Game {
    
    class IFontManager {
    
        struct FontData {
            Font* font;
            int refCount;
        };
        
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, FontData> fontData;
        
        virtual Font* loadFont(std::string, int) = 0;
        
    protected:
        
        ITextureManager* const textureManager;
        
    public:
        
        IFontManager(ITextureManager* m) : textureManager(m) {}
        
        bool defineFont(std::string, std::string);
        void cleanUpFonts();
        
        Font* getFont(std::string);
        void releaseFont(Font*);
        
    };
    
}

#endif

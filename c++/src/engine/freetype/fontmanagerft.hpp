#ifndef fontmanagerft_hpp
#define fontmanagerft_hpp

#include "ifontmanager.hpp"

namespace Game {
    
    class FontManagerFT : virtual public IFontManager {
    
        Font* loadFont(std::string, int);
        
    public:
        
        FontManagerFT(ITextureManager* m) : IFontManager(m) {}
        
    };
    
}

#endif

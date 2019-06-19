#ifndef ishader_hpp
#define ishader_hpp

#include "types.hpp"

namespace Game {
    
    class Controller;
    
    class IShader {
        
    public:
        
        virtual ~IShader() {}
        
        void render(RenderData&);
        
    };
    
}

#endif

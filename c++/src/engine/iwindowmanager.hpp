#ifndef iwindowmanager_hpp
#define iwindowmanager_hpp

#include "types.hpp"

namespace Game {
    
    class IWindowManager {
    
    public:
        
        virtual Vec2 getWindowSize() = 0;
        
    };
    
}

#endif

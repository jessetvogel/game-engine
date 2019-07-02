#ifndef windowmanagerglmac_hpp
#define windowmanagerglmac_hpp

#include "iwindowmanager.hpp"

namespace Game {
    
    class WindowManagerGLMac : virtual public IWindowManager {
    
        void* view;
        
    public:
        
        WindowManagerGLMac(void* view) : view(view) {}
        
        Vec2 getWindowSize();
        
    };
    
}

#endif

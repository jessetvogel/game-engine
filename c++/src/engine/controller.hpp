#ifndef controller_hpp
#define controller_hpp

#include "objectmanager.hpp"
#include "texturemanagergl.hpp"

namespace Game {

    class Controller : public ObjectManager, public TextureManagerGL {
        
    public:
        
        // Methods to be called by main thread
        void update(double);
        void render();
        
    };
    
}

#endif

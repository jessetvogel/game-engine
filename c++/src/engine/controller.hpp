#ifndef controller_hpp
#define controller_hpp

#include "objectmanager.hpp"
#include "inputmanager.hpp"
#include "shadermanager.hpp"
#include "itexturemanager.hpp"

namespace Game {

    class Controller : public ObjectManager, public InputManager, public ShaderManager, virtual public ITextureManager {
        
    public:
        
        void update(double);
        void render();
        
    };
    
}

#endif

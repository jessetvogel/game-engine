#ifndef controller_hpp
#define controller_hpp

#include "objectmanager.hpp"
#include "inputmanager.hpp"
#include "shadermanager.hpp"
#include "itexturemanager.hpp"
#include "iaudiomanager.hpp"
#include "ifontmanager.hpp"

namespace Game {

    class Controller : public ObjectManager, public InputManager, public ShaderManager, virtual public ITextureManager, virtual public IAudioManager { //, virtual public IFontManager {
        
    public:
        
        Controller() : ObjectManager(this) {}
        
        void update(double);
        void render();
        
    };
    
}

#endif

#ifndef controller_hpp
#define controller_hpp

#include "iwindowmanager.hpp"
#include "objectmanager.hpp"
#include "inputmanager.hpp"
#include "shadermanager.hpp"
#include "spritemanager.hpp"
#include "itexturemanager.hpp"
#include "iframebuffermanager.hpp"
#include "iaudiomanager.hpp"
#include "fontmanager.hpp"

namespace Game {

    class Controller : public ObjectManager,
                       public InputManager,
                       public ShaderManager,
                       public SpriteManager,
                       public FontManager,
                       virtual public IWindowManager,
                       virtual public ITextureManager,
                       virtual public IFrameBufferManager,
                       virtual public IAudioManager {
        
    public:
        
        Controller() : ObjectManager(this),
                       SpriteManager(this),
                       FontManager(this) {}
                           
        virtual ~Controller() {}
        
        void update(double);
        void render();
        
    };
    
}

#endif

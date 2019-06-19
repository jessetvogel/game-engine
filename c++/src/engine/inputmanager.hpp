#ifndef inputmanager_hpp
#define inputmanager_hpp

#include "types.hpp"
#include <mutex>

namespace Game {
        
    class InputManager {
        
        std::vector<KeyEvent> keyEvents, queueKeyEvents;
        std::vector<MouseEvent> mouseEvents, queueMouseEvents;
        std::mutex mutex;
        
    protected:
        
        void manageInput();
        
    public:

        void addKeyEvent(KeyEvent);
        void addMouseEvent(MouseEvent);
        
        const std::vector<KeyEvent>& getKeyEvents() { return keyEvents; }
        const std::vector<MouseEvent>& getMouseEvents() { return mouseEvents; }
        
    };
    
}

#endif

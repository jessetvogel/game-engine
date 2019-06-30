#ifndef inputmanager_hpp
#define inputmanager_hpp

#include "types.hpp"
#include <mutex>
#include <iostream>

namespace Game {
        
    class InputManager {
        
        std::vector<KeyEvent> keyEvents, queueKeyEvents;
        std::vector<MouseEvent> mouseEvents, queueMouseEvents;
        std::mutex mutex;
        
        bool keyDown[128] = { false };
        bool mouseDown[3] = { false };
        Vec2 mousePosition = { 0, 0 };
        
    protected:
        
        void manageInput();
        
    public:

        void addKeyEvent(KeyEvent);
        void addMouseEvent(MouseEvent);
        
        std::vector<KeyEvent>& getKeyEvents() { return keyEvents; }
        std::vector<MouseEvent>& getMouseEvents() { return mouseEvents; }

        bool isKeyDown(KeyCode key) { return keyDown[key]; }
        bool isMouseDown(MouseButton button) { return mouseDown[button]; }
        Vec2 getMousePosition() { return mousePosition; }
        
    };
    
}

#endif

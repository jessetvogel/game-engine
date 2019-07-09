#ifndef camera_hpp
#define camera_hpp

#include "types.hpp"
#include "iobject.hpp"

namespace Example {
    
    class Camera : public Game::IObject {
    
        Game::Vec2 position;
        float zoom;
        
        Game::Mat4 VPMatrix;
        
    public:
        
        Camera(Game::ObjectData&);
        
        void update(double);
        void render();
        
        void setPosition(Game::Vec2);
        void setZoom(float);
        
        Game::Mat4& getVPMatrix() { return VPMatrix; }
        
    };
    
}

#endif

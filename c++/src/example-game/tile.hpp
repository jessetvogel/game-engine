#ifndef tile_hpp
#define tile_hpp

#include "iobject.hpp"
#include "iaudiomanager.hpp"

namespace Example {

    class Tile : public Game::IObject {
        
        Game::Sprite* sprite;        
        Game::Vec2 position, scale;
        
    public:
        
        Tile(Game::ObjectData&);
        ~Tile();
        
        void update(double);
        void render();
        
    };

}

#endif

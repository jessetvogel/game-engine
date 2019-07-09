#ifndef tile_hpp
#define tile_hpp

#include "iobject.hpp"
#include "iaudiomanager.hpp"

namespace Example {

    class Tile : public Game::IObject {
        
        Game::Sprite* sprite;
//        Game::Audio* gun;
//        Game::Font* font;
        
        Game::Vec2 position, size;
        
    public:
        
        Tile(Game::ObjectData&);
        ~Tile();
        
        void update(double);
        void render();
        
    };

}

#endif

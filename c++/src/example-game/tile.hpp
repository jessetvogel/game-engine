#ifndef tile_hpp
#define tile_hpp

#include "iobject.hpp"
#include "iaudiomanager.hpp"

namespace Example {

    class Tile : public Game::IObject {
        
        Game::Sprite* sprite;
//        Game::Audio* gun;
//        Game::Font* font;
        
        float x, y, width, height;
        
    public:
        
        Tile(Game::ObjectData&);
        ~Tile();
        
        void update(double);
        void render();
        
    };

}

#endif

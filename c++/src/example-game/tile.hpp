#ifndef tile_hpp
#define tile_hpp

#include "iobject.hpp"
#include "iaudiomanager.hpp"

namespace Example {

    class Tile : public Game::IObject {
        
        Game::Audio* gun;
        
    public:
        
        Tile(Game::ObjectData&);
      
        void update(double);
        void render();
        
    };

}

#endif

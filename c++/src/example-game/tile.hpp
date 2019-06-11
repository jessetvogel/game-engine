#ifndef tile_hpp
#define tile_hpp

#include "object.hpp"

namespace Example {

    class Tile : public Game::Object {
        
    public:
        
        Tile(Game::ObjectData&);
      
        void update(double);
        void render();
        
    };

}

#endif

#ifndef factory_hpp
#define factory_hpp

#include "objectfactory.hpp"

namespace Example {

    class Factory : public Game::ObjectFactory {
    
    public:
        
        Game::Object* create(Game::ObjectData&);
        
    };
    
};

#endif

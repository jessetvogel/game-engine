#ifndef factory_hpp
#define factory_hpp

#include "iobjectfactory.hpp"

namespace Example {

    class Factory : public Game::IObjectFactory {
    
    public:
        
        Game::Object* create(Game::ObjectData&);
        
    };
    
};

#endif

#ifndef objectfactory_hpp
#define objectfactory_hpp

#include "types.hpp"
#include "object.hpp"

namespace Game {
    
    class ObjectFactory {
        
    public:
        
        virtual Object* create(map<string, string>&) = 0;
        
    };
    
}

#endif

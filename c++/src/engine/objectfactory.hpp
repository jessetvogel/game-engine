#ifndef objectfactory_hpp
#define objectfactory_hpp

#include "types.hpp"
#include "object.hpp"

namespace Game {
    
    class ObjectFactory {
        
    public:
        
        virtual Object* create(ObjectData&) = 0;
        
    };
    
}

#define FACTORY_DEFINE_TYPE(CLASS,NAME) if(data.type==NAME) return new CLASS(data);

#endif

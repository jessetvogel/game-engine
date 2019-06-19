#ifndef iobjectfactory_hpp
#define iobjectfactory_hpp

#include "types.hpp"
#include "iobject.hpp"

namespace Game {
    
    class IObjectFactory {
        
    public:
        
        virtual IObject* create(ObjectData&) = 0;
        
    };
    
}

#define FACTORY_DEFINE_TYPE(CLASS,NAME) if(data.type==NAME) return new CLASS(data);

#endif

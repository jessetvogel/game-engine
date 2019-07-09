#ifndef iobject_hpp
#define iobject_hpp

#include "types.hpp"

namespace Game {
    
    class Controller;
    
    class IObject {

        const std::string id;
        const std::string type;
        
    protected:
        
        Controller* const c;
        
    public:
        
        IObject(ObjectData& data) : c(data.c), type(data.type), id(data.id) {}
        virtual ~IObject() {}
        
        const std::string getId() { return id; }
        const std::string getType() { return type; }
        
        virtual void update(double) = 0;
        virtual void render() {}
        
    };
    
}

#endif

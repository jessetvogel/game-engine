#ifndef object_hpp
#define object_hpp

#include "types.hpp"

namespace Game {
    
    class Controller;
    
    class Object {

        const std::string id;
        const std::string type;
        
    protected:
        
        Controller* const c;
        
    public:
        
        Object(ObjectData&);
        virtual ~Object() {};
        
        const std::string getId() { return id; }
        const std::string getType() { return type; }
        
        virtual void update(double) = 0;
        virtual void render() = 0;
        
    };
    
}

#endif

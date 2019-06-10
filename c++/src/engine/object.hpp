#ifndef object_hpp
#define object_hpp

#include "types.hpp"

using namespace std;

namespace Game {
    
    class Controller;
    
    class Object {

        const string id;
        const string type;
        
    protected:
        
        Controller* const c;
        
    public:
        
        Object(Controller*, map<string, string>&);
        virtual ~Object() {};
        
        const string getId() { return id; }
        const string getType() { return type; }
        
        virtual void update(double) = 0;
        virtual void render() = 0;
        
    };
    
}

#endif

#ifndef types_h
#define types_h

#include <string>
#include <vector>
#include <map>

namespace Game {

    class Controller;
    
    typedef struct {
        Controller* c;
        std::string type;
        std::string id;
        std::map<std::string, std::string>& params;
        
    } ObjectData;
    
}

#endif

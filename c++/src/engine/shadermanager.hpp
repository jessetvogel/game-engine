#ifndef shadermanager_hpp
#define shadermanager_hpp

#include "types.hpp"
#include "ishader.hpp"

namespace Game {
    
    class ShaderManager {
        
        std::unordered_map<std::string, IShader*> shaders;
        
    public:
        
        ~ShaderManager();
        
        bool addShader(std::string, IShader*);
        IShader* getShader(std::string);
        
    };
    
}

#endif

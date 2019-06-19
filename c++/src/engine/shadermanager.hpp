#ifndef shadermanager_hpp
#define shadermanager_hpp

#include "types.hpp"
#include "ishader.hpp"

namespace Game {
    
    class ShaderManager {
        
        std::vector<IShader*> shaders;
        size_t n = 0;
        
    public:
        
        ~ShaderManager();
        
        ResId addShader(IShader*);
        IShader* getShader(ResId);
        
    };
    
}

#endif

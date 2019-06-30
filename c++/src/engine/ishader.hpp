#ifndef ishader_hpp
#define ishader_hpp

#include "types.hpp"

namespace Game {
    
    class Controller;
    
    class IShader {
    
    protected:
        
        size_t vertexDataLength;
        
    public:
        
        virtual ~IShader() {}
        
        virtual void render() = 0;
      
        virtual void setVertexDataLength(size_t) = 0;
        
        virtual void setUniform(std::string, float) = 0;
        virtual void setUniform(std::string, Vec2) = 0;
        virtual void setUniform(std::string, Vec3) = 0;
        virtual void setUniform(std::string, Vec4) = 0;
        
        virtual void setAttribute(std::string, float*, size_t, size_t) = 0;
        
        virtual void setTexture(std::string, TextureId) = 0;
        
    };
}

#endif

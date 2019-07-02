#ifndef shadergl_hpp
#define shadergl_hpp

#include "ishader.hpp"
#include "opengl.hpp"

namespace Game {

    class ShaderGL : public IShader {
    
        static GLuint compileShader(const char*, GLenum);
        static GLuint createProgram(const char*, const char*);
        
        struct Uniform {
            std::string name;
            GLint location;
            GLint texId;
        };
        
        struct Attribute {
            std::string name;
            GLint location;
            int size;
            GLuint VBO;
        };
        
        std::vector<Uniform> uniforms;
        std::vector<Attribute> attributes;
        
        Uniform* getUniform(std::string);
        Attribute* getAttribute(std::string);
        
        void findUniformsAndAttributes();
        
        GLuint program;
        GLuint VAO;
                
    public:
        
        ShaderGL(ShaderData);
        ~ShaderGL();
    
        void render();
        
        void setVertexDataLength(size_t);
        
        void setUniform(std::string, float);
        void setUniform(std::string, Vec2);
        void setUniform(std::string, Vec3);
        void setUniform(std::string, Vec4);
        void setUniform(std::string, Mat4&);
        void setUniform(std::string, int);
        
        void setAttribute(std::string, float*, size_t n = 0, size_t offset = 0);
        
        void setTexture(std::string, TextureId);
        
    };
    
}

#endif

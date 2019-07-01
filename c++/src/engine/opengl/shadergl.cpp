#include "shadergl.hpp"
#include <fstream>

using namespace std;
using namespace Game;

extern void error(string);

ShaderGL::ShaderGL(ShaderData data) {
    // Open source files
    std::ifstream vertexFile(data.vertexShader, std::ios::binary | std::ios::ate);
    if(vertexFile.fail()) {
        error("Failed to open vertex shader file: " + data.vertexShader);
        return;
    }
    
    std::ifstream fragmentFile(data.fragmentShader, std::ios::binary | std::ios::ate);
    if(fragmentFile.fail()) {
        error("Failed to open fragment shader file: " + data.fragmentShader);
        return;
    }
    
    // Read files into data buffers
    size_t size = vertexFile.tellg();
    vertexFile.seekg(0, std::ios::beg);
    char vertexData[size + 1];
    if(!vertexFile.read(vertexData, size)) {
        error("Failed to read vertex shader file: " + data.vertexShader);
        return;
    }
    vertexData[size] = '\0';
    
    size = fragmentFile.tellg();
    fragmentFile.seekg(0, std::ios::beg);
    char fragmentData[size + 1];
    if(!fragmentFile.read(fragmentData, size)) {
        error("Failed to read fragment shader file: " + data.fragmentShader);
        return;
    }
    fragmentData[size] = '\0';
    
    // Create a program from data data buffers
    program = createProgram(vertexData, fragmentData);
    
    // Find uniforms and attributes
    findUniformsAndAttributes();
    
    // Initialize with some data (length 3)
    setVertexDataLength(3);
}

ShaderGL::~ShaderGL() {
    // Delete program
    glDeleteProgram(program);
    
    // Delete VAO & VBO's
    glDeleteVertexArrays(1, &VAO);
    for(auto& a : attributes)
        glDeleteBuffers(1, &(a.VBO));
}

GLuint ShaderGL::compileShader(const char* src, GLenum type) {
    // Create and compile shader
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    // Check the result of the compilation
    GLint test;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
    if(!test) {
        char log[512];
        GLsizei length;
        glGetShaderInfoLog(shader, sizeof(log), &length, log);
        error("Shader compilation failed with this message: " + string(log, length));
    }
    
    return shader;
}

GLuint ShaderGL::createProgram(const char* srcVertex, const char* srcFragment) {
    // Compile the vertex and fragment shaders
    GLuint vertexShader = compileShader(srcVertex, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(srcFragment, GL_FRAGMENT_SHADER);
    
    // Attach the above shaders to a program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    // Flag the shaders for deletion
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // Link and use the program
    glLinkProgram(program);
    glUseProgram(program);
    
    return program;
}

void ShaderGL::findUniformsAndAttributes() {
    // Retrieve uniform information
    GLint count, maxLength, currentTexId = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
    for(GLint i = 0;i < count; ++i) {
        GLsizei length;
        GLint size;
        GLenum type;
        GLchar name[maxLength];
        glGetActiveUniform(program, i, maxLength, &length, &size, &type, name);
        string uniformName(name, length);
        GLint location = glGetUniformLocation(program, name);
        
        // Add uniform to list
        uniforms.push_back({
            uniformName,
            location,
            (type == GL_SAMPLER_2D) ? currentTexId++ : 0
        });
    }
    
    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Retrieve attribute information
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    for(GLint i = 0;i < count; ++i) {
        GLsizei length;
        GLint size;
        GLenum type;
        GLchar name[maxLength];
        glGetActiveAttrib(program, i, maxLength, &length, &size, &type, name);
        string attributeName(name, length);
        GLint location = glGetAttribLocation(program, name);
        
        if(type == GL_FLOAT_VEC2)
            size *= 2;
        else if(type == GL_FLOAT_VEC3)
            size *= 3;
        else if(type == GL_FLOAT_VEC4)
            size *= 4; // TODO : ???
        
        // Create VBO per attribute
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * size, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Add attribute to list
        attributes.push_back({
            attributeName,
            location,
            size,
            VBO
        });
    }
    
    glBindVertexArray(0);
}

void ShaderGL::render() {
    // Use program
    glUseProgram(program);
    
    // Draw arrays
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertexDataLength);
    glBindVertexArray(0);
}

void ShaderGL::setVertexDataLength(size_t length) {
    // Update VBO's
    vertexDataLength = length;
    glBindVertexArray(VAO);
    for(auto& a : attributes) {
        glBindBuffer(GL_ARRAY_BUFFER, a.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * a.size * vertexDataLength, nullptr, GL_DYNAMIC_DRAW); // TODO: GL_DYNAMIC_DRAW ???
        glEnableVertexAttribArray(a.location);
        glVertexAttribPointer(a.location, a.size, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * a.size, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }
    glBindVertexArray(0);
}

ShaderGL::Uniform* ShaderGL::getUniform(string name) {
    for(auto& uniform : uniforms) {
        if(uniform.name == name)
            return &uniform;
    }
    return nullptr;
}

ShaderGL::Attribute* ShaderGL::getAttribute(string name) {
    for(auto& attribute : attributes) {
        if(attribute.name == name)
            return &attribute;
    }
    return nullptr;
}

void ShaderGL::setUniform(string name, float value) {
    glUseProgram(program);
    Uniform* u = getUniform(name);
    if(u != nullptr)
        glUniform1f(u->location, value);
}

void ShaderGL::setUniform(string name, Vec2 value) {
    glUseProgram(program);
    Uniform* u = getUniform(name);
    if(u != nullptr)
        glUniform2f(u->location, value.x, value.y);
}

void ShaderGL::setUniform(string name, Vec3 value) {
    glUseProgram(program);
    Uniform* u = getUniform(name);
    if(u != nullptr)
        glUniform3f(u->location, value.x, value.y, value.z);
}

void ShaderGL::setUniform(string name, Vec4 value) {
    glUseProgram(program);
    Uniform* u = getUniform(name);
    if(u != nullptr)
        glUniform4f(u->location, value.x, value.y, value.z, value.w);
}

void ShaderGL::setUniform(string name, Mat4& value) {
    glUseProgram(program);
    Uniform* u = getUniform(name);
    if(u != nullptr)
        glUniformMatrix4fv(u->location, 1, GL_FALSE, &value[0][0]);
}

void ShaderGL::setAttribute(string name, float* values, size_t n, size_t offset) {
    Attribute* a = getAttribute(name);
    if(a != nullptr) {
        if(n == 0)
            n = vertexDataLength;
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, a->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(GLfloat) * a->size * n, values);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void ShaderGL::setTexture(string name, TextureId textureId) {
    glUseProgram(program);
    Uniform* u = getUniform(name);
    if(u != nullptr) {
        glUniform1i(u->location, u->texId);
        glActiveTexture(GL_TEXTURE0 + u->texId);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
}

#include "shadergl.hpp"
#include <iostream>

using namespace std;
using namespace Game;

ShaderGL::ShaderGL(ShaderData& data) {
    // Create a program from data data buffers
    program = createProgram(data.vertexShader.c_str(), data.fragmentShader.c_str());
    
    // Find uniforms and attributes
    findUniformsAndAttributes();
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
        cout << "Shader compilation failed with this message: ";
        char log[512];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        cout << log << endl;
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
    GLint count, maxLength;
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
            name,
            location
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
    
    // Initialize with some data (length 1)
    setVertexDataLength(1);
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

void ShaderGL::setAttribute(string name, float* values, size_t n, size_t offset) {
    Attribute* a = getAttribute(name);
    if(a != nullptr) {
        if(n == 0)
            n = vertexDataLength;
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, a->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(GLfloat) * n, values);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

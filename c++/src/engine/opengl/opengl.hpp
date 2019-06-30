#ifndef opengl_hpp
#define opengl_hpp

#include <OpenGL/gl.h>

#ifdef __APPLE__
// Don't know why, but does not work without this (for mac)
#undef glGenVertexArrays
#define glGenVertexArrays glGenVertexArraysAPPLE
#undef glBindVertexArray
#define glBindVertexArray glBindVertexArrayAPPLE
#undef glDeleteVertexArrays
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif

// Debug
#define DEBUG_OPENGL {GLenum error;while((error=glGetError())!=GL_NO_ERROR)std::cout<<"[OPENGL ERROR "<<std::to_string(error)<<" AT " __FILE__ ":"<<__LINE__<<"]"<<std::endl;}

#endif

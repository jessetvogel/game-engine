#include "texturemanagergl.hpp"
#include "opengl.hpp"

using namespace std;
using namespace Game;

Texture TextureManagerGL::createTexture(unsigned char* pixels, int width, int height, int channels) {
    // Determine texture format
    GLenum format;
    if(channels == 1) format = GL_RED;
    else if(channels == 2) format = GL_RG;
    else if(channels == 3) format = GL_RGB;
    else if(channels == 4) format = GL_RGBA;
    else return { -1, Vec2(0.0f, 0.0f) };
    
    // Create texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    return { (TextureId) texture, Vec2(width, height) };
}

void TextureManagerGL::freeTexture(Texture texture) {
    // Delete texture
    GLuint id = texture.id;
    glDeleteTextures(1, &id);
}

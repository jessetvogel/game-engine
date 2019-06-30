#include "texturemanagergl.hpp"
#include <OpenGL/gl.h>
#include "lodepng.hpp"
#include <iostream>

using namespace std;
using namespace Game;

TextureId TextureManagerGL::loadTexture(string path) {
    // Create texture
    GLuint textureId;
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Load image
    unsigned int width, height;
    vector<unsigned char> pixels;
    unsigned error = lodepng::decode(pixels, width, height, path);
    if(error) {
        cout << "Failed to load png '" + path + "' (error " + to_string(error) + "): " + lodepng_error_text(error) << endl;
        
        // Use checkers board as default TODO: remove this at some point
        pixels.clear();
        pixels.push_back(127); pixels.push_back(127); pixels.push_back(127); pixels.push_back(255);
        pixels.push_back(255); pixels.push_back(255); pixels.push_back(255); pixels.push_back(255);
        pixels.push_back(255); pixels.push_back(255); pixels.push_back(255); pixels.push_back(255);
        pixels.push_back(127); pixels.push_back(127); pixels.push_back(127); pixels.push_back(255);
        width = height = 2;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
    return textureId;
}

void TextureManagerGL::freeTexture(TextureId id) {
    // Delete texture
    GLuint textureId = id;
    glDeleteTextures(1, &textureId);
}

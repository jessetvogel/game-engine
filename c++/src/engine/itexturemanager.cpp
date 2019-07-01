#include "itexturemanager.hpp"
#include "lodepng.hpp"

using namespace std;
using namespace Game;

extern void error(string);

bool ITextureManager::defineTexture(string name, string path) {
    // Check if 'name' is already defined
    auto it = definitions.find(name);
    if(it != definitions.end())
        return false;
    
    definitions[name] = path;
    return true;
}

void ITextureManager::cleanUpTextures() {
    // Free all textures that are not currently in use
    for(auto it = textureData.begin();it != textureData.end();) {
        if(it->second.refCount <= 0) {
            freeTexture(it->second.id);
            it = textureData.erase(it);
        }
        else {
            ++ it;
        }
    }
}

TextureId ITextureManager::getTexture(string name) {
    // Check if texture is already loaded
    auto it = textureData.find(name);
    if(it != textureData.end()) {
        ++ it->second.refCount;
        return it->second.id;
    }
    else {
        // If not, load new texture from definition
        auto it = definitions.find(name);
        if(it == definitions.end())
            return -1;
    
        TextureId id = loadTexture(it->second);
        textureData[name] = { id, 1 };
        return id;
    }
}

TextureId ITextureManager::getTexture(unsigned char* pixels, int width, int height, int channels) {
    TextureId id = createTexture(pixels, width, height, channels);
    if(id < 0)
        return -1;
    
    return id;
}

void ITextureManager::releaseTexture(TextureId id) {
    // Decrement reference count
    for(auto& entry : textureData) {
        if(entry.second.id == id) {
            -- entry.second.refCount;
            return;
        }
    }
    
    // If not in map, free immediately
    freeTexture(id);
}

TextureId ITextureManager::loadTexture(string path) {
    // Load image
    unsigned int width, height;
    vector<unsigned char> pixels;
    unsigned err = lodepng::decode(pixels, width, height, path);
    if(err) {
        error("Failed to load png '" + path + "' (error " + to_string(err) + "): " + lodepng_error_text(err));
        
        // Use checkers board as default TODO: remove this at some point
        pixels.clear();
        pixels.push_back(127); pixels.push_back(127); pixels.push_back(127); pixels.push_back(255);
        pixels.push_back(255); pixels.push_back(255); pixels.push_back(255); pixels.push_back(255);
        pixels.push_back(255); pixels.push_back(255); pixels.push_back(255); pixels.push_back(255);
        pixels.push_back(127); pixels.push_back(127); pixels.push_back(127); pixels.push_back(255);
        width = height = 2;
    }
    
    return createTexture(&pixels[0], width, height, 4);
}

#include "itexturemanager.hpp"

using namespace std;
using namespace Game;

bool ITextureManager::defineTexture(string name, string path) {
    // Check if 'name' is already defined
    auto it = definitions.find(name);
    if(it != definitions.end())
        return false;
    
    definitions[name] = path;
    return true;
}

void ITextureManager::manageTextures() {
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

void ITextureManager::releaseTexture(TextureId id) {
    for(auto& entry : textureData) {
        if(entry.second.id == id) {
            -- entry.second.refCount;
            break;
        }
    }
}

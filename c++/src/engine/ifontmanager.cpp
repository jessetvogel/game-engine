#include "ifontmanager.hpp"

using namespace std;
using namespace Game;

bool IFontManager::defineFont(string name, string path) {
    // Check if 'name' is already defined
    auto it = definitions.find(name);
    if(it != definitions.end())
        return false;
    
    definitions[name] = path;
    return true;
}

void IFontManager::cleanUpFonts() {
    // Free all fonts that are not currently in use
    for(auto it = fontData.begin();it != fontData.end();) {
        if(it->second.refCount <= 0) {
            textureManager->releaseTexture(it->second.font->texture);
            delete it->second.font;
            it = fontData.erase(it);
        }
        else {
            ++ it;
        }
    }
}

Font* IFontManager::getFont(string name) {
    // Check if Font is already loaded
    auto it = fontData.find(name);
    if(it != fontData.end()) {
        ++ it->second.refCount;
        return it->second.font;
    }
    else {
        // Create Font from definition
        auto it = definitions.find(name);
        if(it == definitions.end())
            return nullptr;
        
        Font* font = loadFont(it->second, 64);
        if(font == nullptr)
            return nullptr;
        
        fontData[name] = { font, 1 };
        return font;
    }
}

void IFontManager::releaseFont(Font* font) {
    // Decrement reference count
    for(auto& entry : fontData) {
        if(entry.second.font == font) {
            -- entry.second.refCount;
            break;
        }
    }
}

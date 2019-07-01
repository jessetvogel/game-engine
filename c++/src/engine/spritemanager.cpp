#include "spritemanager.hpp"

using namespace std;
using namespace Game;

bool SpriteManager::defineSprite(std::string name, SpriteData data) {
    // Check if 'name' is already defined
    auto it = definitions.find(name);
    if(it != definitions.end())
        return false;
    
    definitions[name] = data;
    return true;
}

Sprite* SpriteManager::getSprite(std::string name) {
    // Lookup definition
    auto it = definitions.find(name);
    if(it == definitions.end())
        return nullptr;
    
    // Lookup texture
    TextureId texture = textureManager->getTexture(it->second.texture);
    if(texture < 0)
        return nullptr;
    
    // Create Sprite from data
    Sprite* sprite = new Sprite();
    sprite->texture = texture;
    sprite->x = it->second.x;
    sprite->y = it->second.y;
    sprite->frames = it->second.frames;
    return sprite;
}

void SpriteManager::releaseSprite(Sprite* sprite) {
    // Release texture & delete sprite
    textureManager->releaseTexture(sprite->texture);
    delete sprite;
}

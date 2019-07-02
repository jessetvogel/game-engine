#include "iframebuffermanager.hpp"

using namespace std;
using namespace Game;

bool IFrameBufferManager::createFrameBuffer(string name) {
    // Check if 'name' is already defined
    auto it = frameBuffers.find(name);
    if(it != frameBuffers.end())
        return false;
    
    // Try to create a new frame buffer
    FrameBuffer fb = createFrameBuffer();
    if(fb.FBO < 0)
        return false;
    
    frameBuffers[name] = fb;
    return true;
}

bool IFrameBufferManager::freeFrameBuffer(string name) {
    // Lookup frame buffer
    auto it = frameBuffers.find(name);
    if(it == frameBuffers.end())
        return false;
    
    // Free frame buffer and erase from map
    freeFrameBuffer(it->second);
    frameBuffers.erase(it);
    return true;
}

bool IFrameBufferManager::useFrameBuffer(string name) {
    // Lookup frame buffer
    auto it = frameBuffers.find(name);
    if(it == frameBuffers.end())
        return false;

    useFrameBuffer(it->second);
    return true;
}

TextureId IFrameBufferManager::getFrameBufferTexture(std::string name) {
    // Lookup frame buffer
    auto it = frameBuffers.find(name);
    if(it == frameBuffers.end())
        return -1;
    
    return it->second.texture;
}

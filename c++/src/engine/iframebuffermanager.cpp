#include "iframebuffermanager.hpp"

using namespace std;
using namespace Game;

bool IFrameBufferManager::createFrameBuffer(string name, int width, int height, int channels) {
    // Check if 'name' is already defined
    auto it = frameBuffers.find(name);
    if(it != frameBuffers.end())
        return false;
    
    // Try to create a new frame buffer
    FrameBuffer fb = createFrameBuffer(width, height, channels);
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

Texture IFrameBufferManager::getFrameBufferTexture(std::string name) {
    // Lookup frame buffer
    auto it = frameBuffers.find(name);
    if(it == frameBuffers.end())
        return { -1, Vec2(0.0f, 0.0f) };
    
    return it->second.texture;
}

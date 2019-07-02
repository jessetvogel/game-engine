#include "framebuffermanagergl.hpp"
#include "opengl.hpp"

using namespace std;
using namespace Game;

extern void error(string);

IFrameBufferManager::FrameBuffer FrameBufferManagerGL::createFrameBuffer() {
    // Create Frame Buffer Object
    GLuint FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    
    // Attach texture to frame buffer TODO: this should also be deleted!
    Vec2 windowSize = windowManager->getWindowSize();
    GLuint texture = textureManager->getTexture(nullptr, windowSize.x, windowSize.y, 3);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    
    // Check for completeness
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    return {
        (int) FBO,
        (TextureId) texture
    };
}

void FrameBufferManagerGL::useFrameBuffer(FrameBuffer& fb) {
    // Bind frame buffer
    GLuint FBO = fb.FBO;
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void FrameBufferManagerGL::useDefaultFrameBuffer() {
    // Default frame buffer is set by 0
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferManagerGL::freeFrameBuffer(FrameBuffer& fb) {
    // Delete frame buffer & texture
    GLuint FBO = fb.FBO;
    textureManager->releaseTexture(fb.texture);
    glDeleteFramebuffers(1, &FBO);
}

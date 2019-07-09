#include "framebuffermanagergl.hpp"
#include "opengl.hpp"

using namespace std;
using namespace Game;

extern void error(string);

IFrameBufferManager::FrameBuffer FrameBufferManagerGL::createFrameBuffer(int width, int height, int channels) {
    // Create Frame Buffer Object
    GLuint FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    
    // Attach texture to frame buffer TODO: this should also be deleted!
    GLuint textureId = textureManager->getTexture(nullptr, width, height, channels).id;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
    
    // Check for completeness
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    return {
        (int) FBO,
        { (TextureId) textureId, Vec2(width, height) }
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

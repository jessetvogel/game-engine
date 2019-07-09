#ifndef framebuffermanagergl_hpp
#define framebuffermanagergl_hpp

#include "iframebuffermanager.hpp"
#include "iwindowmanager.hpp"
#include "texturemanagergl.hpp"

namespace Game {
    
    class FrameBufferManagerGL : virtual public IFrameBufferManager {
    
        TextureManagerGL* const textureManager;
        
        FrameBuffer createFrameBuffer(int, int, int);
        void useFrameBuffer(FrameBuffer&);
        void freeFrameBuffer(FrameBuffer&);
        
    public:
        
        FrameBufferManagerGL(TextureManagerGL* t) : textureManager(t) {}
        
        void useDefaultFrameBuffer();
        
    };
    
}

#endif

#ifndef framebuffermanagergl_hpp
#define framebuffermanagergl_hpp

#include "iframebuffermanager.hpp"
#include "iwindowmanager.hpp"
#include "texturemanagergl.hpp"

namespace Game {
    
    class FrameBufferManagerGL : virtual public IFrameBufferManager {
    
        IWindowManager* const windowManager;
        TextureManagerGL* const textureManager;
        
        FrameBuffer createFrameBuffer();
        void useFrameBuffer(FrameBuffer&);
        void freeFrameBuffer(FrameBuffer&);
        
    public:
        
        FrameBufferManagerGL(IWindowManager* w, TextureManagerGL* t) : windowManager(w), textureManager(t) {}
        
        void useDefaultFrameBuffer();
        
    };
    
}

#endif

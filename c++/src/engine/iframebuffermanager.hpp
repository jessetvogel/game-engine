#ifndef iframebuffermanager_hpp
#define iframebuffermanager_hpp

#include "types.hpp"

namespace Game {
    
    class IFrameBufferManager {

    protected:
        
        struct FrameBuffer {
            int FBO;
            Texture texture;
        };

    private:
        
        std::unordered_map<std::string, FrameBuffer> frameBuffers;
        
        virtual FrameBuffer createFrameBuffer(int, int, int) = 0;
        virtual void useFrameBuffer(FrameBuffer&) = 0;
        virtual void freeFrameBuffer(FrameBuffer&) = 0;
        
    public:
        
        bool createFrameBuffer(std::string, int, int, int);
        bool useFrameBuffer(std::string);
        virtual void useDefaultFrameBuffer() = 0;
        bool freeFrameBuffer(std::string);
        
        Texture getFrameBufferTexture(std::string);
        
    };
    
}

#endif

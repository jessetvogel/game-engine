#ifndef iresourcemanager_hpp
#define iresourcemanager_hpp

#include "types.hpp"

namespace Game {
        
    class IResourceManager {
    
        std::unordered_map<std::string, std::pair<ResId, RefCount>> resourceIds;
        
        virtual ResId loadResource(std::string) = 0;
        virtual void freeResource(ResId) = 0;

    protected:
        
        ResId get(std::string);
        void release(ResId);
        
    };
    
}

#endif

#include "iresourcemanager.hpp"

using namespace Game;

ResId IResourceManager::get(std::string name) {
    // Chek if resource is already loaded
    auto it = resourceIds.find(name);
    if(it != resourceIds.end()) {
        it->second.second ++; // Increment reference counter
        return it->second.first; // Return resource id
    }
    
    // Load new resource and store it in map
    ResId id = loadResource(name);
    resourceIds[name] = { id, 1 };
    return id;
}

void IResourceManager::release(ResId id) {
    // Decrement reference counter, and free resource if there are no more references to it
    for(auto it = resourceIds.begin();it != resourceIds.end(); ++it) {
        if(it->second.first == id) {
            if((--(it->second.second)) <= 0) {
                freeResource(id);
                resourceIds.erase(it);
            }
            break;
        }
    }
}

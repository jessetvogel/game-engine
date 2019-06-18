#ifndef objectmanager_hpp
#define objectmanager_hpp

#include "types.hpp"
#include "iobjectfactory.hpp"
#include "object.hpp"

namespace Game {
    
    class ObjectManager {
        
        IObjectFactory* objectFactory = nullptr;
        
        std::unordered_map<std::string, Object*> objectsById;
        std::vector<Object*> objectsToAdd, objectsToDestroy;

        std::string sceneToLoad;
        bool loadScene(std::string);
        void clearObjects();
        
    protected:
        
        std::unordered_map<std::string, std::vector<Object*>> objects;
        void manageObjects();
        
    public:
        
        void setObjectFactory(IObjectFactory*);
        bool goToScene(std::string);
        bool create(ObjectData&);
        bool destroy(Object*);
        Object* getObjectById(std::string);
        std::vector<Object*> getObjectsByType(std::string);
        
    };
    
}

#endif

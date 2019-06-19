#ifndef objectmanager_hpp
#define objectmanager_hpp

#include "types.hpp"
#include "iobjectfactory.hpp"

namespace Game {
    
    class ObjectManager {
        
        IObjectFactory* objectFactory = nullptr;
        
        std::unordered_map<std::string, IObject*> objectsById;
        std::vector<IObject*> objectsToAdd, objectsToDestroy;

        std::string sceneToLoad;
        bool loadScene(std::string);
        void clearObjects();
        
    protected:
        
        std::unordered_map<std::string, std::vector<IObject*>> objects;
        void manageObjects();
        
    public:
        
        void setObjectFactory(IObjectFactory*);
        bool goToScene(std::string);
        bool create(ObjectData&);
        bool destroy(IObject*);
        IObject* getObjectById(std::string);
        std::vector<IObject*> getObjectsByType(std::string);
        
    };
    
}

#endif

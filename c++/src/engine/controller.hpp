#ifndef controller_hpp
#define controller_hpp

#include "objectfactory.hpp"
#include "object.hpp"

#include "types.hpp"

namespace Game {

    class Controller {
        
        ObjectFactory* objectFactory = nullptr;
        
        std::map<std::string, std::vector<Object*>> objects;
        std::map<std::string, Object*> objectsById;
        std::vector<Object*> objectsToAdd, objectsToDestroy;

        std::string sceneToLoad;
        
        void clearObjects();
        void manageObjects();
        
    public:
        
        // Methods to be called by main thread
        void setObjectFactory(ObjectFactory*);
        void update(double);
        void render();
        
        // Methods to be called by Objects. Any instructions will be
        // stored in a queue, and executed before the next update iteration.
        bool goToScene(std::string);
        bool create(ObjectData&);
        bool destroy(Object*);
        Object* getObjectById(std::string);
        std::vector<Object*> getObjectsByType(std::string);
      
        void error(std::string);
        
    };
    
}

#endif

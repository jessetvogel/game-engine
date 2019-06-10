#ifndef controller_hpp
#define controller_hpp

#include "objectfactory.hpp"
#include "object.hpp"

#include "types.hpp"

using namespace std;

namespace Game {

    class Controller {
        
        ObjectFactory* objectFactory = nullptr;
        
        map<string, vector<Object*>> objects;
        map<string, Object*> objectsById;
        vector<Object*> objectsToAdd, objectsToDestroy;

        string sceneToLoad;
        
        void clearObjects();
        void manageObjects();
        
        void error(string);
        
    public:
        
        // Methods to be called by main thread
        void setObjectFactory(ObjectFactory*);
        void update(double);
        void render();
        
        // Methods to be called by Objects. Any instructions will be
        // stored in a queue, and executed before the next update iteration.
        bool goToScene(string);
        bool create(map<string, string>&);
        bool destroy(Object*);
        Object* getObjectById(string);
        vector<Object*> getObjectsByType(string);
        
    };
    
}

#endif

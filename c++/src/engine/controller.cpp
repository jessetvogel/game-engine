#include "controller.hpp"
#include "scene.hpp"

using namespace std;
using namespace Game;

void Controller::clearObjects() {
    // Delete all objects & clear all lists
    for(auto& entry : objects)
        for(auto obj : entry.second)
            delete obj;
    objects.clear();
    objectsById.clear();
    objectsToAdd.clear();
    objectsToDestroy.clear();
}

void Controller::manageObjects() {
    // If there is a scene to load, clear objects and load that scene
    if(sceneToLoad != "") {
        clearObjects();
        if(!Scene::load(this, sceneToLoad))
            error("failed to load scene");
        sceneToLoad = "";
    }
    
    // Add newly created objects
    for(auto obj : objectsToAdd) {
        string type = obj->getType();
        string id = obj->getId();
        objects[type].push_back(obj);
        if(id != "")
            objectsById[id] = obj;
    }
    objectsToAdd.clear();
    
    // Remove and delete destroyed objects
    for(auto obj : objectsToDestroy) {
        string type = obj->getType();
        string id = obj->getId();
        objectsById.erase(id);
        auto pos = objects.find(type);
        if(pos != objects.end()) {
            auto& list = pos->second;
            auto it = ::find(list.begin(), list.end(), obj);
            if(it != list.end())
                list.erase(it);
        }
        delete obj;
    }
    objectsToDestroy.clear();
}

void Controller::setObjectFactory(ObjectFactory* factory) {
    objectFactory = factory;
}

void Controller::update(double dt) {
    // Manage objects
    manageObjects();
    
    // Update all objects
    for(auto& entry : objects) {
        for(auto obj : entry.second)
            obj->update(dt);
    }
}

void Controller::render() {
    // Render all objects
    for(auto& entry : objects)
        for(auto obj : entry.second)
            obj->render();
}

bool Controller::goToScene(string scene) {
    sceneToLoad = scene;
    return true;
}

bool Controller::create(ObjectData& data) {
    // Requires an object factory
    if(objectFactory == nullptr) {
        error("object factory is not set");
        return false;
    }
    
    // Try to produce an object
    Object* obj = objectFactory->create(data);
    if(obj == nullptr) {
        error("failed to create object of type " + data.type);
        return false;
    }
    
    // Add to queue
    objectsToAdd.push_back(obj);
    return true;
}

bool Controller::destroy(Object* obj) {
    // Must be non-null
    if(obj == nullptr) {
        error("tried to destroy nullptr");
        return false;
    }
    
    // Add to queue (neglect duplicates)
    if(::find(objectsToDestroy.begin(), objectsToDestroy.end(), obj) == objectsToDestroy.end())
        objectsToDestroy.push_back(obj);
    return true;
}

Object* Controller::getObjectById(string id) {
    auto it = objectsById.find(id);
    if(it == objectsById.end())
        return nullptr;
    return it->second;
}

vector<Object*> Controller::getObjectsByType(string type) {
    auto it = objects.find(type);
    if(it == objects.end())
        return {};
    return it->second;
}





// ------------------------------------------------
#include <iostream>

void Controller::error(string message) {
    cout << "[ERROR] " << message << endl;
}

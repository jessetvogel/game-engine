#include "objectmanager.hpp"
#include "controller.hpp"
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>

using namespace std;
using namespace Game;
using namespace rapidjson;

extern void error(string);

bool ObjectManager::defineObject(string name, IObject* (*f)(ObjectData&)) {
    // Check if 'name' is already defined
    auto it = definitions.find(name);
    if(it != definitions.end())
        return false;
    
    definitions[name] = f;
    return true;
}

void ObjectManager::clearObjects() {
    // Delete all objects & clear all lists
    for(auto& entry : objects)
        for(auto obj : entry.second)
            delete obj;
    objects.clear();
    objectsById.clear();
    objectsToAdd.clear();
    objectsToDestroy.clear();
}

void ObjectManager::manageObjects() {
    // If there is a scene to load, clear objects and load that scene
    if(sceneToLoad != "") {
        if(currentScene != "")
            controller->onSceneEnd();
        
        clearObjects();
        if(!loadScene(sceneToLoad))
            error("failed to load scene");

        currentScene = sceneToLoad;
        sceneToLoad = "";
        
        controller->onSceneStart();
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

bool ObjectManager::goToScene(string scene) {
    sceneToLoad = scene;
    return true;
}

bool ObjectManager::createObject(ObjectData& data) {
    // Create Object from definition
    auto it = definitions.find(data.type);
    if(it == definitions.end())
        return false;
    
    IObject* obj = (it->second)(data);
    if(obj == nullptr) {
        error("failed to create object of type " + data.type);
        return false;
    }
    
    // Add to queue
    objectsToAdd.push_back(obj);
    return true;
}

bool ObjectManager::destroyObject(IObject* obj) {
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

IObject* ObjectManager::getObjectById(string id) {
    auto it = objectsById.find(id);
    if(it == objectsById.end())
        return nullptr;
    return it->second;
}

vector<IObject*> ObjectManager::getObjectsByType(string type) {
    auto it = objects.find(type);
    if(it == objects.end())
        return {};
    return it->second;
}

bool ObjectManager::loadScene(string path) {
    // Try to open file for reading
    ifstream file(path);
    if(file.fail())
        return false;
    
    // Try to extract its content
    stringstream ss;
    string line;
    while(getline(file, line))
        ss << line;
    
    // Try to parse as JSON
    Document doc;
    if(doc.Parse(ss.str().c_str()).HasParseError())
        return false;
    
    // Make sure its content is an array
    if(!doc.IsArray())
        return false;
    
    // Create object for each item in the array
    for(auto& v : doc.GetArray()) {
        if(!v.IsObject()) {
            error("non-object in array in json file " + path);
            continue;
        }
        
        // Determine object data
        ObjectData data;
        data.c = controller;
        for(auto& m : v.GetObject()) {
            if(!m.value.IsString()) {
                error("non-string value in object in json file " + path);
                continue;
            }
            
            string key = m.name.GetString(),
                 value = m.value.GetString();
            if(key == "type")
                data.type = value;
            else if(key == "id")
                data.id = value;
            else
                data.parameters[m.name.GetString()] = value;
        }
        
        createObject(data);
    }
    
    return true;
}

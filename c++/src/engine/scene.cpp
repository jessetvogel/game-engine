#include "scene.hpp"
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>

using namespace std;
using namespace Game;
using namespace rapidjson;

bool Scene::load(Controller* c, string path) {
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
            c->error("non-object in array in json file " + path);
            continue;
        }
        
        // Determine object data
        std::string type;
        std::string id;
        map<string, string> params;
        for(auto& m : v.GetObject()) {
            if(!m.value.IsString()) {
                c->error("non-string value in object in json file " + path);
                continue;
            }
            
            std::string key = m.name.GetString(), value = m.value.GetString();
            if(key == "type")
                type = value;
            else if(key == "id")
                id = value;
            else
                params[m.name.GetString()] = value;
        }
        
        // Create new object from data
        ObjectData data = {
            c,
            type,
            id,
            params
        };
        c->create(data);
    }
    
    return true;
}

#include "shadermanager.hpp"

using namespace std;
using namespace Game;

ShaderManager::~ShaderManager() {
    // Delete all shaders
    for(auto& entry : shaders)
        delete entry.second;
}

bool ShaderManager::addShader(string name, IShader* shader) {
    // Check if 'name' is already defined
    auto it = shaders.find(name);
    if(it != shaders.end())
        return false;
    
    // Add shader to the list and return its index in the list
    shaders[name] = shader;
    return true;
}

IShader* ShaderManager::getShader(string name) {
    // Lookup shader
    auto it = shaders.find(name);
    if(it == shaders.end())
        return nullptr;
    
    return it->second;
}

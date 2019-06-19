#include "shadermanager.hpp"

using namespace Game;

ShaderManager::~ShaderManager() {
    // Delete all shaders
    for(auto shader : shaders)
        delete shader;
}

ResId ShaderManager::addShader(IShader* shader) {
    // Add shader to the list and return its index in the list
    shaders.push_back(shader);
    return (ResId) (n ++);
}

IShader* ShaderManager::getShader(ResId id) {
    // Check validity of shader id, if so, return the shader
    if(id < 0 || id > n)
        return nullptr;

    return shaders.at(id);
}

#include "mycontroller.hpp"

#include "shadergl.hpp"
#include "tile.hpp"
#include "camera.hpp"

#include <iostream>

using namespace std;
using namespace Game;
using namespace Example;

void MyController::init() {
    // Definitions
    #include "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/definitions.def"
    
    // Add shaders
    addShader("ShaderGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.fsh"
    }));
    addShader("FontGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.fsh"
    }));
    addShader("SpriteGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/sprite.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/sprite.fsh"
    }));
    
    // Set shader settings
    float vertices[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    
    IShader* shader = getShader("SpriteGL");
    shader->setVertexDataLength(6);
    shader->setAttribute("aVertex", vertices, 6, 0);
    shader->setAttribute("aTexCoord", vertices, 6, 0);
    
    // Load this scene by start
    goToScene("/Users/jessetvogel/Desktop/scene.json");
}



void MyController::onSceneStart() {
    // Don't forget the camera!
    ObjectData data = { this, "camera", "camera", {} };
    createObject(data);
}
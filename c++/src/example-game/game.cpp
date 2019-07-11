#include "mycontroller.hpp"
#include "shadergl.hpp"
#include <portaudio/portaudio.h>
#include "tile.hpp"
#include "camera.hpp"

using namespace std;
using namespace Game;
using namespace Example;

extern void error(string);

Controller* start(void* view) {
    // Initialize portaudio
    Pa_Initialize();
    
    // Create controller object
    Controller* c = new MyController(view);
    
    // Definitions
    #include "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/definitions.def"
    
    // Add shaders
    c->addShader("ShaderGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.fsh"
    }));
    c->addShader("FontGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.fsh"
    }));
    c->addShader("SpriteGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/sprite.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/sprite.fsh"
    }));
    
    // Start audio stream by default
    if(!c->startAudioStream())
        error("Failed to start audio stream!");
    
    // Load this scene by start
    c->goToScene("/Users/jessetvogel/Desktop/scene.json");
    
    return c;
}

void stop(Controller* c) {
    // Delete controller
    delete c;
    
    // Terminate portaudio
    Pa_Terminate();
}

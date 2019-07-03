#include "mycontroller.hpp"
#include "shadergl.hpp"
#include <portaudio/portaudio.h>
#include "tile.hpp"

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
    c->defineObject("tile", [](ObjectData& data) -> IObject* { return new Example::Tile(data); });
    
    c->defineTexture("helloWorld", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/textures/helloworld.png");
    c->defineTexture("ground", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/textures/ground.png");
    c->defineTexture("sign", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/textures/sign.png");
    
    c->defineSprite("ground", { "ground", 0.0f, 0.0f, 1.0f, 1.0f });
    c->defineSprite("sign", { "sign", 0.0f, 0.0f, 1.0f, 1.0f });
    
    c->defineAudio("gun", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/audio/gun.wav");
    c->defineFont("myriadpro", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/fonts/Myriad Pro Regular.ttf");
    
    // Add shaders
    c->addShader("ShaderGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.fsh"
    }));
    c->addShader("FontGL", new ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.fsh"
    }));
    
    // Start audio stream by default
    if(!c->startAudioStream())
        error("Failed to start audio stream!");
    
    // Load this scene by start
    c->goToScene("/Users/jessetvogel/Desktop/test.json");
    
    return c;
}

void stop(Controller* c) {
    // Delete controller
    delete c;
    
    // Terminate portaudio
    Pa_Terminate();
}

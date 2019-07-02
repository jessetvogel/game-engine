#import "AppDelegate.h"
#import "openglview-mac.hpp"
#include "mycontroller.hpp"
#include "shadergl.hpp"
#include <iostream>
#include <portaudio/portaudio.h>

#include "tile.hpp"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*) aNotification {
    Pa_Initialize();

    // Find view
    OpenGLView* view = [[[NSApp windows] objectAtIndex: 0] contentView];

    // Insert code here to initialize your application
    Example::MyController* controller = new Example::MyController((__bridge void*) view);
    
    // Definitions
    controller->defineObject("tile", [](Game::ObjectData& data) -> Game::IObject* { return new Example::Tile(data); });
    
    controller->defineTexture("helloWorld", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/textures/helloworld.png");
    controller->defineAudio("gun", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/audio/gun.wav");
    controller->defineSprite("sprite_1", { "helloWorld", 0.0f, 0.0f, 1.0f, 1.0f });
    controller->defineFont("myriadpro", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/fonts/Myriad Pro Regular.ttf");
    
    controller->addShader("ShaderGL", new Game::ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.fsh"
    }));
    controller->addShader("FontGL", new Game::ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/font.fsh"
    }));

    
    if(!controller->startAudioStream())
        std::cout << "Failed to start audio stream!" << std::endl;
    
    controller->goToScene("/Users/jessetvogel/Desktop/test.json");
    
    [view setController: controller];
    
    [view setNeedsDisplay: YES];
    [view startTimer];
}

- (void)applicationWillTerminate:(NSNotification*) aNotification {
    // Insert code here to tear down your application
    Pa_Terminate();
}

@end

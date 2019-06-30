#import "AppDelegate.h"
#import "openglview-mac.hpp"
#include "mycontroller.hpp"
#include "factory.hpp"
#include "shadergl.hpp"
#include <iostream>
#include <portaudio/portaudio.h>

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*) aNotification {
    Pa_Initialize();
    
    // Insert code here to initialize your application
    Example::MyController* controller = new Example::MyController();
    
    // Definitions
    controller->defineTexture("helloWorld", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/textures/helloworld.png");
    controller->defineAudio("gun", "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/audio/gun.wav");
    
    controller->addShader(new Game::ShaderGL({
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.vsh",
        "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/shader.fsh"
    }));
    
    if(!controller->startAudioStream())
        std::cout << "Failed to start audio stream!" << std::endl;
    
    Example::Factory* factory = new Example::Factory();
    controller->setObjectFactory(factory);
    
    controller->goToScene("/Users/jessetvogel/Desktop/test.json");
    
    OpenGLView* view = [[[NSApp windows] objectAtIndex: 0] contentView];
    [view setController: controller];
    
    [view setNeedsDisplay: YES];
    [view startTimer];
}

- (void)applicationWillTerminate:(NSNotification*) aNotification {
    // Insert code here to tear down your application
    Pa_Terminate();
}

@end

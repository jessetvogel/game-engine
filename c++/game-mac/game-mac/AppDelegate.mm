#import "AppDelegate.h"
#import "openglview.hpp"
#include "controller.hpp"
#include "factory.hpp"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*) aNotification {
    // Insert code here to initialize your application
    Game::Controller* controller = new Game::Controller();
    
    Example::Factory* factory = new Example::Factory();
    controller->setObjectFactory(factory);
    
    controller->goToScene("/Users/jessetvogel/Desktop/test.json");
    
    OpenGLView* view = [[[NSApp windows] objectAtIndex: 0] contentView];
    [view setController: controller];
    
    [view setNeedsDisplay: YES];
}

- (void)applicationWillTerminate:(NSNotification*) aNotification {
    // Insert code here to tear down your application
    
}

@end

#import "AppDelegate.h"
#include "controller.hpp"
#include "factory.hpp"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*) aNotification {
    // Insert code here to initialize your application
    Game::Controller controller;
    
    Example::Factory factory;
    controller.setObjectFactory(&factory);
    
    controller.goToScene("/Users/jessetvogel/Desktop/test.json");
    
    controller.update(1);
}

- (void)applicationWillTerminate:(NSNotification*) aNotification {
    // Insert code here to tear down your application
    
}

@end

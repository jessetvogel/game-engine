#import "openglview-mac.hpp"

extern Game::Controller* start(void*);
extern void stop(Game::Controller*);

Game::Controller* controller;

// App Delegate
@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@interface AppDelegate()

@property (weak) IBOutlet NSWindow* window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*) aNotification {
    // Find OpenGLView
    OpenGLView* view = [[[NSApp windows] objectAtIndex: 0] contentView];

    // Create game controller & pass it to the view
    controller = start((__bridge void*) view);
    [view setController: controller];
    [view setNeedsDisplay: YES];
    [view startTimer];
}

- (void)applicationWillTerminate:(NSNotification*) aNotification {
    // Stop the game
    stop(controller);
}

@end

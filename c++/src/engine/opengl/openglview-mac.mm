#import "openglview-mac.hpp"
#include "controller.hpp"

@implementation OpenGLView

- (id) initWithFrame:(NSRect) rect {
    self = [super initWithFrame: rect];
    [[self window] makeFirstResponder: self];
    
    controller = nullptr;
    return self;
}

- (void) prepareOpenGL {
    [[self openGLContext] makeCurrentContext];
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; // set to vbl sync
}

- (void) drawRect:(NSRect) bounds {
    [[self openGLContext] makeCurrentContext];
    glViewport(0, 0, bounds.size.width, bounds.size.height);
    
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(controller != nullptr) {
        controller->update(1);
        controller->render();
    }
    
    glFlush();
}

- (void) viewWillMoveToWindow:(NSWindow*) window {
    // Setup a new tracking area when the view is added to the window.
    NSTrackingArea* trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds] options: (NSTrackingMouseMoved | NSTrackingEnabledDuringMouseDrag | NSTrackingActiveInKeyWindow) owner:self userInfo:nil];
    [self addTrackingArea:trackingArea];
}

- (BOOL) acceptsFirstResponder {
    return YES;
}

- (void) mouseDown:(NSEvent*) event {
    
}

- (void) mouseUp:(NSEvent*) event {
    
}

- (void) rightMouseDown:(NSEvent*) event {
    
}

- (void) rightMouseUp:(NSEvent*) event {
    
}

- (void) mouseMoved:(NSEvent*) event {
    
}

- (void) mouseDragged:(NSEvent*) event {

}

- (void) scrollWheel:(NSEvent*) event {

}

- (void) keyDown:(NSEvent*) event {

}

- (void) keyUp:(NSEvent*) event {

}

- (void) setController:(Game::Controller*) c {
    controller = c;
}

@end

#import "openglview-mac.hpp"
#include "controller.hpp"

using namespace Game;

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
    
    // Some OpenGL settings
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

- (void) drawRect:(NSRect) bounds {
    [[self openGLContext] makeCurrentContext];
    glViewport(0, 0, bounds.size.width, bounds.size.height);
    
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(controller != nullptr) {
        controller->update(0.017);
        controller->render();
    }
    
    glFlush();
    
    DEBUG_OPENGL
}

- (void) startTimer {
    timer = [NSTimer scheduledTimerWithTimeInterval:0.017 target:self selector:@selector(onTimer:) userInfo:nil repeats:YES];
}

- (void) stopTimer {
    [timer invalidate];
}

- (void) onTimer:(NSTimer*) timer {
    [self setNeedsDisplay:YES];
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
    controller->addMouseEvent({
        Down,
        (MouseButton) [event buttonNumber],
        { (float) [event absoluteX], (float) [event absoluteY] }
    });
}

- (void) mouseUp:(NSEvent*) event {
    controller->addMouseEvent({
        Up,
        (MouseButton) [event buttonNumber],
        { (float) [event absoluteX], (float) [event absoluteY] }
    });
}

- (void) rightMouseDown:(NSEvent*) event {
    controller->addMouseEvent({
        Down,
        (MouseButton) [event buttonNumber],
        { (float) [event absoluteX], (float) [event absoluteY] }
    });
}

- (void) rightMouseUp:(NSEvent*) event {
    controller->addMouseEvent({
        Up,
        (MouseButton) [event buttonNumber],
        { (float) [event absoluteX], (float) [event absoluteY] }
    });
}

- (void) mouseMoved:(NSEvent*) event {
    
}

- (void) mouseDragged:(NSEvent*) event {

}

- (void) scrollWheel:(NSEvent*) event {

}

- (void) keyDown:(NSEvent*) event {
    controller->addKeyEvent({
        Down,
        (KeyCode) [event keyCode]
    });
}

- (void) keyUp:(NSEvent*) event {
    controller->addKeyEvent({
        Up,
        (KeyCode) [event keyCode]
    });
}

- (void) setController:(Controller*) c {
    controller = c;
}

@end

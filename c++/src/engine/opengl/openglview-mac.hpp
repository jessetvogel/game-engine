#ifndef openglview_mac_h
#define openglview_mac_h

#import <Cocoa/Cocoa.h>
#include "opengl.hpp"

namespace Game {
    class Controller;
}

@interface OpenGLView : NSOpenGLView {
    Game::Controller* controller;
    NSPoint mouse;

}

- (id) initWithFrame:(NSRect) rect;
- (void) prepareOpenGL;
- (void) drawRect:(NSRect) bounds;
- (void) viewWillMoveToWindow:(NSWindow*) window;
- (BOOL) acceptsFirstResponder;

- (void) mouseDown:(NSEvent*) event;
- (void) mouseUp:(NSEvent*) event;
- (void) rightMouseDown:(NSEvent*) event;
- (void) rightMouseUp:(NSEvent*) event;
- (void) mouseMoved:(NSEvent*) event;
- (void) mouseDragged:(NSEvent*) event;
- (void) scrollWheel:(NSEvent*) event;

- (void) keyDown:(NSEvent*) event;
- (void) keyUp:(NSEvent*) event;
- (void) setController:(Game::Controller*) controller;

@end


#endif

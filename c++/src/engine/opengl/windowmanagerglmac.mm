#include "windowmanagerglmac.hpp"
#include "openglview-mac.hpp"

using namespace std;
using namespace Game;

Vec2 WindowManagerGLMac::getWindowSize() {
    OpenGLView* v = (__bridge OpenGLView*) view;
    NSRect rect = [v bounds];
    return Vec2(rect.size.width, rect.size.height);
}

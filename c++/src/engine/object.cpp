#include "object.hpp"

using namespace Game;

Object::Object(Controller* c, dict& params) : c(c), id(params["id"]), type(params["type"]) {
    
}

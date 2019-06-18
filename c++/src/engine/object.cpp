#include "object.hpp"

using namespace std;
using namespace Game;

Object::Object(ObjectData& data) : c(data.c),
                                   type(data.type),
                                   id(data.id) {
    
}

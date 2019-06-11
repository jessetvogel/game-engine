#include "factory.hpp"
#include "tile.hpp"

using namespace std;
using namespace Game;
using namespace Example;

Object* Factory::create(ObjectData& data) {
    
    FACTORY_DEFINE_TYPE(Tile, "tile")

    return nullptr;
}

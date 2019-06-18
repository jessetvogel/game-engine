#include "tile.hpp"
#include <iostream>

using namespace std;
using namespace Game;
using namespace Example;

Tile::Tile(ObjectData& data) : Object(data) {
    for(auto& v : data.params)
        cout << v.first << ": " << v.second << endl;
}

void Tile::update(double dt) {
    cout << "test?" << endl;
}

void Tile::render() {
    
}

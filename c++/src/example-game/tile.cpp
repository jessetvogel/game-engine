#include "tile.hpp"
#include "controller.hpp"
#include <iostream>
#include "mycontroller.hpp"

using namespace std;
using namespace Game;
using namespace Example;

Tile::Tile(ObjectData& data) : IObject(data) {
//    for(auto& v : data.params)
//        cout << v.first << ": " << v.second << endl;
    
    // Set gun sound
    gun = c->getAudio("gun");
    
    // Set shader settings
    IShader* shader = c->getShader(0);
    shader->setVertexDataLength(6);
    
    float vertices[] = {
        -0.5f, -0.5f,
        0.0f, 1.0f,
        0.5f, -0.5f,
        0.0, 1.0f,
        0.5f, -0.5f,
        1.0f, 1.0f
    };
    
    float texCoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    
    shader->setAttribute("aVertex", vertices, 6, 0);
    shader->setAttribute("aTexCoord", texCoords, 6, 0);
}

void Tile::update(double dt) {
    auto& events = c->getKeyEvents();
    for(auto& event : events) {
        if(event.action == Down) {
            cout << "PRESSED KEY!" << endl;
            gun->seekTo(0);
            gun->play();
        }
    }
}

void Tile::render() {
    IShader* shader = c->getShader(0);
    shader->setTexture("uTexture", c->getTexture("helloWorld"));
    shader->render();
}

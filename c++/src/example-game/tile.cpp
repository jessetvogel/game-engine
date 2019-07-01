#include "tile.hpp"
#include "controller.hpp"
#include <iostream>
#include "mycontroller.hpp"

using namespace std;
using namespace Game;
using namespace Example;

Tile::Tile(ObjectData& data) : IObject(data) {
    // Set gun sound
    gun = c->getAudio("gun");
    sprite = c->getSprite("sprite_1");
    font = c->getFont("myriadpro");
    
    x = stof(data.params["x"]);
    y = stof(data.params["y"]);
    
    // Set shader settings
    IShader* shader = c->getShader(0);
    shader->setVertexDataLength(6);
    
    float vertices[] = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f
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

Tile::~Tile() {
    c->releaseAudio(gun);
    c->releaseSprite(sprite);
    c->releaseFont(font);
}

void Tile::update(double dt) {
    auto& events = c->getKeyEvents();
    for(auto& event : events) {
        if(event.action == Down && event.key == Space) {
            gun->seekTo(0);
            gun->play();
        }
    }
    
    if(c->isKeyDown(ArrowUp))
        y += 16.0f;

    if(c->isKeyDown(ArrowDown))
        y -= 16.0f;

    if(c->isKeyDown(ArrowLeft))
        x -= 16.0f;
    
    if(c->isKeyDown(ArrowRight))
        x += 16.0f;
}

#include <glm/ext.hpp>

void Tile::render() {
    Mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, Vec3(x, y, 0.0f));
    m = glm::scale(m, Vec3(512.0f, 512.0f, 1.0f));
    Mat4 uMVP = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f) * m;
    
    IShader* shader = c->getShader(0);
    shader->setTexture("uTexture", font->texture);
    shader->setUniform("uMVP", uMVP);
    shader->render();
}

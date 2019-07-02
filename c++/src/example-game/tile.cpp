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
    
    IShader* shader = c->getShader("ShaderGL");
    shader->setVertexDataLength(6);
    shader->setAttribute("aVertex", vertices, 6, 0);
    shader->setAttribute("aTexCoord", texCoords, 6, 0);
    shader = c->getShader("FontGL");
    shader->setVertexDataLength(6);
    shader->setAttribute("aVertex", texCoords, 6, 0);
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
        y += 2.0f;

    if(c->isKeyDown(ArrowDown))
        y -= 2.0f;

    if(c->isKeyDown(ArrowLeft))
        x -= 2.0f;
    
    if(c->isKeyDown(ArrowRight))
        x += 2.0f;
}

#include <glm/ext.hpp>

void Tile::render() {
    Mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, Vec3(x, y, 0.0f));
    m = glm::scale(m, Vec3(48.0f, 48.0f, 1.0f));
    
    Vec2 windowSize = c->getWindowSize();
    
    Mat4 uMVP = glm::ortho(0.0f, windowSize.x, 0.0f, windowSize.y) * m;
    
    IShader* shader = c->getShader("ShaderGL");
    shader->setTexture("uTexture", sprite->texture);
    shader->setUniform("uMVP", uMVP);
    
    shader->render();
    
    shader->setTexture("uTexture", sprite->texture);
    shader->render();
    
    shader = c->getShader("FontGL");
    shader->setTexture("uTexture", font->texture);
    shader->setUniform("uMVP", uMVP);
    shader->setUniform("uColor", Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    
    string text = "Hello world!";

    Vec2 position = Vec2(0.0f, 0.0f);
    for(char c : text) {
        shader->setUniform("uChar", (int) c);
        shader->setUniform("uOffset", position + Vec2(font->characters[c].bearing.x, font->characters[c].bearing.y));
        shader->render();
        
        position.x += font->characters[c].advance;
    }
}

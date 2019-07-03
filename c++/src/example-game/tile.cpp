#include "tile.hpp"
#include "controller.hpp"
#include <iostream>
#include "mycontroller.hpp"

using namespace std;
using namespace Game;
using namespace Example;

Tile::Tile(ObjectData& data) : IObject(data) {
    // Set gun sound
//    gun = c->getAudio("gun");
    sprite = c->getSprite(data.params["sprite"]);
//    font = c->getFont("myriadpro");
    
    x = stof(data.params["x"]);
    y = stof(data.params["y"]);
    width = stof(data.params["w"]);
    height = stof(data.params["h"]);
    
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
}

Tile::~Tile() {
//    c->releaseAudio(gun);
    c->releaseSprite(sprite);
//    c->releaseFont(font);
}

void Tile::update(double dt) {
    auto& events = c->getKeyEvents();
    for(auto& event : events) {
        if(event.action == Down && event.key == Space) {
            
            unordered_map<string, string> params;
            ObjectData data = { c, "tile", "", params };
            params["x"] = to_string(x - 1.0f);
            params["y"] = to_string(y);
            params["w"] = to_string(width);
            params["h"] = to_string(height);
            params["sprite"] = "sign";
            c->createObject(data);
            
            c->destroyObject(this);
            
        }
    }
    
//            gun->seekTo(0);
//            gun->play();
//        }
//    }
    
//    if(c->isKeyDown(ArrowUp))
//        y += 48.0f * dt;
//
//    if(c->isKeyDown(ArrowDown))
//        y -= 48.0f * dt;
//
//    if(c->isKeyDown(ArrowLeft))
//        x -= 48.0f * dt;
//    
//    if(c->isKeyDown(ArrowRight))
//        x += 48.0f * dt;
}

#include <glm/ext.hpp>

void Tile::render() {
    Mat4 m = glm::mat4(1.0f);
    m = glm::scale(m, Vec3(32.0f * width, 32.0f * height, 1.0f));
    m = glm::translate(m, Vec3(x, y, 0.0f));
    
    Vec2 windowSize = c->getWindowSize();
    int w = round(windowSize.x / 2), h = round(windowSize.y / 2);
    Mat4 uMVP = glm::ortho(-(float) w, windowSize.x - w, -(float) h, windowSize.y - h) * m;
    
    IShader* shader = c->getShader("ShaderGL");
    shader->setTexture("uTexture", sprite->texture);
    shader->setUniform("uMVP", uMVP);
    shader->render();
    
//    shader->setTexture("uTexture", sprite->texture);
//    shader->render();
//    
//    shader = c->getShader("FontGL");
//    shader->setTexture("uTexture", font->texture);
//    shader->setUniform("uMVP", uMVP);
//    shader->setUniform("uColor", Vec4(0.0f, 0.0f, 0.0f, 1.0f));
//    
//    // How to render text:
//    string text = "Hello world!";
//    Vec2 position = Vec2(0.0f, 0.0f);
//    for(char c : text) {
//        shader->setUniform("uChar", (int) c);
//        shader->setUniform("uOffset", position + Vec2(font->characters[c].bearing.x, font->characters[c].bearing.y));
//        shader->render();
//        
//        position.x += font->characters[c].advance;
//    }
}

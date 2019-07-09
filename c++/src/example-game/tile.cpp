#include "tile.hpp"
#include "controller.hpp"
#include "camera.hpp"
#include <iostream>
#include "mycontroller.hpp"

using namespace std;
using namespace Game;
using namespace Example;

Tile::Tile(ObjectData& data) : IObject(data) {
    // Set gun sound
//    gun = data.get("gun", (Audio*) nullptr);
//    font = data.get("myriadpro", (Font*) nullptr);
    sprite = data.get("sprite", (Sprite*) nullptr);
    position = data.get("position", Vec2(0.0f, 0.0f));
    size = data.get("size", Vec2(1.0f, 1.0f));
    
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
    
    IShader* shader = c->getShader("SpriteGL");
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
            params["position"] = to_string(position.x - 1.0f) + "," + to_string(position.y);
            params["size"] = to_string(size.x) + "," + to_string(size.y);
            params["sprite"] = "sign";
            c->createObject(data);
            
            c->destroyObject(this);
            
            cout << params["position"] << endl;
            
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
    m = glm::translate(m, Vec3(position.x, position.y, 0.0f));
    m = glm::scale(m, Vec3(size.x, size.y, 1.0f));
    
    Camera* camera = (Camera*) c->getObjectById("camera");
    Mat4 uMVP = camera->getVPMatrix() * m;
    
    IShader* shader = c->getShader("SpriteGL");
    shader->setTexture("uTexture", sprite->texture.id);
    shader->setUniform("uFrame", Vec4(sprite->frame.x / sprite->texture.size.x, sprite->frame.y / sprite->texture.size.y, sprite->frame.z / sprite->texture.size.x, sprite->frame.w / sprite->texture.size.y));
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

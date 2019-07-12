#include "tile.hpp"
#include "controller.hpp"
#include "camera.hpp"
#include <iostream>
#include "mycontroller.hpp"

using namespace std;
using namespace Game;
using namespace Example;

Tile::Tile(ObjectData& data) : IObject(data) {
    sprite = data.get("sprite", (Sprite*) nullptr);
    position = data.get("position", Vec2(0.0f, 0.0f));
    scale = data.get("scale", Vec2(1.0f, 1.0f));
}

Tile::~Tile() {
    c->releaseSprite(sprite);
}

void Tile::update(double dt) {
    auto& events = c->getKeyEvents();
    for(auto& event : events) {
        if(event.action == Down && event.key == Space) {
            
            unordered_map<string, string> params;
            ObjectData data = { c, "tile", "", params };
            params["position"] = to_string(position.x - 1.0f) + "," + to_string(position.y);
            params["scale"] = to_string(scale.x) + "," + to_string(scale.y);
            params["sprite"] = "sign";
            c->createObject(data);
            
            c->destroyObject(this);
            
            cout << params["position"] << endl;
            
        }
    }
}

#include <glm/ext.hpp>

void Tile::render() {
    Mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, Vec3(position.x, position.y, 0.0f));
    m = glm::scale(m, Vec3(sprite->frame.z / 16.0f * scale.x, sprite->frame.w / 16.0f * scale.y, 1.0f));
    
    Camera* camera = (Camera*) c->getObjectById("camera");
    Mat4 uMVP = camera->getVPMatrix() * m;
    
    IShader* shader = c->getShader("SpriteGL");
    shader->setTexture("uTexture", sprite->texture.id);
    shader->setUniform("uFrame", Vec4(sprite->frame.x / sprite->texture.size.x, sprite->frame.y / sprite->texture.size.y, sprite->frame.z / sprite->texture.size.x, sprite->frame.w / sprite->texture.size.y));
    shader->setUniform("uCenter", Vec2(sprite->center.x / sprite->frame.z, 1.0f - sprite->center.y / sprite->frame.w));
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

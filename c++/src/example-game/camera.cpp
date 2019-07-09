#include "camera.hpp"
#include "controller.hpp"
#include <glm/ext.hpp>

using namespace std;
using namespace Game;
using namespace Example;

Camera::Camera(ObjectData& data) : IObject(data) {
    setPosition(Vec2(0.0f, 0.0f));
}

void Camera::update(double dt) {
    setZoom(32);
    
    if(c->isKeyDown(ArrowRight))
        position.x += 0.5f;
    if(c->isKeyDown(ArrowLeft))
        position.x -= 0.5f;
    if(c->isKeyDown(ArrowUp))
        position.y += 0.5f;
    if(c->isKeyDown(ArrowDown))
        position.y -= 0.5f;
}

void Camera::render() {
    // Update VPMatrix
    Vec2 viewSize = c->getWindowSize();
    float w = round(viewSize.x * 0.5f) / zoom, h = round(viewSize.y * 0.5f) / zoom;
    viewSize /= zoom;
    VPMatrix = glm::ortho(position.x - w, position.x - w + viewSize.x, position.y - h, position.y - h + viewSize.y);
}

void Camera::setPosition(Vec2 p) {
    position = p;
}

void Camera::setZoom(float z) {
    zoom = z;
}

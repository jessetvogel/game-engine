#include "inputmanager.hpp"

using namespace std;
using namespace Game;

void InputManager::manageInput() {
    // Move queue to current lists
    mutex.lock();
    keyEvents = queueKeyEvents;
    mouseEvents = queueMouseEvents;
    queueKeyEvents.clear();
    queueMouseEvents.clear();
    mutex.unlock();
}

void InputManager::addKeyEvent(KeyEvent event) {
    // Update key state, and add event to the queue
    mutex.lock();
    if(event.action == Down)
        keyDown[event.key] = true;
    else if(event.action == Up)
        keyDown[event.key] = false;
    queueKeyEvents.push_back(event);
    mutex.unlock();
}

void InputManager::addMouseEvent(MouseEvent event) {
    // Update mouse state, and add event to the queue
    mutex.lock();
    mousePosition = event.position;
    if(event.action == Down)
        mouseDown[event.button] = true;
    else if(event.action == Up)
        mouseDown[event.button] = false;
    queueMouseEvents.push_back(event);
    mutex.unlock();
}

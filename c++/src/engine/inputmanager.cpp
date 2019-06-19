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
    // Add event to the queue
    mutex.lock();
    queueKeyEvents.push_back(event);
    mutex.unlock();
}

void InputManager::addMouseEvent(MouseEvent event) {
    // Add event to the queue
    mutex.lock();
    queueMouseEvents.push_back(event);
    mutex.unlock();
}

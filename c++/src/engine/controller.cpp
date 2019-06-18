#include "controller.hpp"

using namespace std;
using namespace Game;

void Controller::update(double dt) {
    // Manage objects
    manageObjects();
    
    // Update all objects
    for(auto& entry : objects) {
        for(auto obj : entry.second)
            obj->update(dt);
    }
}

void Controller::render() {
    // Render all objects
    for(auto& entry : objects)
        for(auto obj : entry.second)
            obj->render();
}






// ------------------------------------------------
#include <iostream>

void error(string message) {
    cout << "[ERROR] " << message << endl;
}

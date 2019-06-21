#ifndef types_h
#define types_h

#include <string>
#include <vector>
#include <unordered_map>

namespace Game {

    class Controller;
    
    // Vector types
    typedef struct {
        float x, y;
    } Vec2;
    
    typedef struct {
        float x, y, z;
    } Vec3;
    
    typedef struct {
        float x, y, z, w;
    } Vec4;
    
    // Data types
    typedef struct {
        Controller* c;
        std::string type;
        std::string id;
        std::unordered_map<std::string, std::string>& params;
        
    } ObjectData;
    
    typedef struct {
        std::string vertexShader;
        std::string fragmentShader;
    } ShaderData;
    
    typedef struct {
        
    } RenderData;
    
    // Input types
    enum KeyCode {
        
    };
    
    enum MouseButton {
        Left = 0,
        Middle = 1,
        Right = 2
    };
    
    enum Action {
        Down, Up
    };
    
    typedef struct {
        Action action;
        KeyCode key;
    } KeyEvent;
    
    typedef struct {
        Action action;
        MouseButton button;
        Vec2 position;
        
    } MouseEvent;
    
    // Other
    typedef int ResId;
    typedef int RefCount;
    
}

#endif

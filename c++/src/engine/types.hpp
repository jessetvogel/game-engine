#ifndef types_h
#define types_h

#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Game {

    class Controller;
    
    // Vector types
    typedef glm::vec2 Vec2;
    typedef glm::vec3 Vec3;
    typedef glm::vec4 Vec4;
    typedef glm::mat4 Mat4;
    
    // Data types
    typedef struct {
        Controller* c;
        std::string type;
        std::string id;
        std::unordered_map<std::string, std::string>& parameters;
        
        template <typename T>
        T get(std::string, T);
    } ObjectData;
    
    typedef struct {
        std::string vertexShader;
        std::string fragmentShader;
    } ShaderData;
    
    typedef struct {
        std::string texture;
        Vec4 frame;
        Vec2 center;
        int frames;
    } SpriteData;
    
    // Input types
    enum KeyCode {
        Space = 49, ArrowUp = 126, ArrowLeft = 123, ArrowRight = 124, ArrowDown = 125
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
    typedef int TextureId;
    typedef int RefCount;
    
    // [...] types
    typedef struct {
        TextureId id;
        Vec2 size;
    } Texture;
    
    typedef struct {
        Texture texture;
        Vec4 frame;
        Vec2 center;
        int frames;
    } Sprite;
    
    typedef struct {
        struct Character {
            Vec2 size;     // Size of glyph
            Vec2 bearing;  // Offset from baseline to left/top of glyph
            float advance; // Offset to advance to next glyph
        };
        
        Texture texture;
        int width, height;
        Character characters[128];
    } Font;

    
    
    
    
}

#endif

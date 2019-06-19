#ifndef types_h
#define types_h

#include <string>
#include <vector>
#include <unordered_map>

namespace Game {

    class Controller;
    
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
    
    typedef struct {
        
    } KeyEvent;
    
    typedef struct {
        
    } MouseEvent;
    
    typedef int ResId;
    typedef int RefCount;
    
}

#endif

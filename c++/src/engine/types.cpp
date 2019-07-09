#include "types.hpp"
#include "controller.hpp"
#include <regex>

using namespace std;
using namespace Game;

#define REGEX_FLOAT "-?\\d*.?\\d+"
regex regexFloat("^(" REGEX_FLOAT ")$");
regex regexVec2("^(" REGEX_FLOAT "),(" REGEX_FLOAT ")$");

// ---- ObjectData ----
template <>
float ObjectData::get(string key, float _default) {
    auto it = parameters.find(key);
    if(it == parameters.end())
        return _default;
    
    if(!regex_match(it->second, regexFloat))
        return _default;
    
    return stof(it->second);
}

template <>
Vec2 ObjectData::get(string key, Vec2 _default) {
    auto it = parameters.find(key);
    if(it == parameters.end())
        return _default;
    
    cmatch cm;
    if(!regex_search(it->second.c_str(), cm, regexVec2))
        return _default;
    
    return Vec2(stof(cm[1]), stof(cm[2]));
}

template <>
Sprite* ObjectData::get(string key, Sprite* _default) {
    auto it = parameters.find(key);
    if(it == parameters.end())
        return _default;
    
    Sprite* sprite = c->getSprite(it->second);
    if(sprite == nullptr)
        return _default;
    
    return sprite;
}

template <>
Font* ObjectData::get(string key, Font* _default) {
    auto it = parameters.find(key);
    if(it == parameters.end())
        return _default;
    
    Font* font = c->getFont(it->second);
    if(font == nullptr)
        return _default;
    
    return font;
}

template <>
Audio* ObjectData::get(string key, Audio* _default) {
    auto it = parameters.find(key);
    if(it == parameters.end())
        return _default;
    
    Audio* audio = c->getAudio(it->second);
    if(audio == nullptr)
        return _default;
    
    return audio;
}

#include "fontmanager.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;
using namespace Game;

extern void error(string);

bool FontManager::defineFont(string name, string path) {
    // Check if 'name' is already defined
    auto it = definitions.find(name);
    if(it != definitions.end())
        return false;
    
    definitions[name] = path;
    return true;
}

void FontManager::cleanUpFonts() {
    // Free all fonts that are not currently in use
    for(auto it = fontData.begin();it != fontData.end();) {
        if(it->second.refCount <= 0) {
            textureManager->releaseTexture(it->second.font->texture);
            delete it->second.font;
            it = fontData.erase(it);
        }
        else {
            ++ it;
        }
    }
}

Font* FontManager::getFont(string name) {
    // Check if Font is already loaded
    auto it = fontData.find(name);
    if(it != fontData.end()) {
        ++ it->second.refCount;
        return it->second.font;
    }
    else {
        // Create Font from definition
        auto it = definitions.find(name);
        if(it == definitions.end())
            return nullptr;
        
        Font* font = loadFont(it->second, 24);
        if(font == nullptr)
            return nullptr;
        
        fontData[name] = { font, 1 };
        return font;
    }
}

void FontManager::releaseFont(Font* font) {
    // Decrement reference count
    for(auto& entry : fontData) {
        if(entry.second.font == font) {
            -- entry.second.refCount;
            break;
        }
    }
}

unsigned int next_power_of_two(unsigned int v) {
    -- v;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    ++ v;
    return v;
}

Font* FontManager::loadFont(string path, int size) {
    // Load font using FreeType
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        error("Failed to initialize FreeType");
        return nullptr;
    }
    
    FT_Face face;
    if(FT_New_Face(ft, path.c_str(), 0, &face)) {
        error("Failed to load font " + path);
        return nullptr;
    }
    
    FT_Set_Pixel_Sizes(face, 0, size);
    
    // Determine maximum width/height of glyphs
    unsigned int maxWidth = 0, maxHeight = 0;
    for(FT_ULong c = 0; c < 128; ++c) {
        // Load character glyph
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            error("Failed to load character " + to_string((int) c) + " in font " + path);
            continue;
        }
        
        maxWidth = max(maxWidth, face->glyph->bitmap.width);
        maxHeight = max(maxHeight, face->glyph->bitmap.rows);
    }
    
    // Create Font object
    Font* font = new Font();
    
    // Create pixel data from font
    int w = next_power_of_two(maxWidth),
    h = next_power_of_two(maxHeight);
    unsigned char pixels[w * h * 256];
    memset(pixels, 0, sizeof(unsigned char) * w * h * 256);
    
    for(FT_ULong c = 0; c < 128; ++c) {
        // Load character glyph
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            error("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
        
        // Copy glyph onto texture
        auto bitmap = face->glyph->bitmap;
        for(int y = 0;y < bitmap.rows; ++y) {
            for(int x = 0;x < bitmap.width; ++x)
                pixels[w * 16 * (c / 16 * h + y) + (c % 16) * w + x] = bitmap.buffer[bitmap.width * y + x];
        }
        
        // Set Font character information
        font->characters[c].size = Vec2((float) face->glyph->bitmap.width / w, (float) face->glyph->bitmap.rows / h);
        font->characters[c].bearing = Vec2((float) face->glyph->bitmap_left / w, (float) face->glyph->bitmap_top / h);
        font->characters[c].advance = (float) (face->glyph->advance.x >> 6) / w;
    }
    
    // Clear FreeType objects
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    
    // Create texture from pixel data
    Texture texture = textureManager->getTexture(pixels, w * 16, h * 16, 1);
    if(texture.id < 0)
        return nullptr;
    font->texture = texture;
    
    return font;
}

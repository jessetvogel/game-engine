#include "fontmanagerft.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

using namespace std;
using namespace Game;

extern void error(string);

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

Font* FontManagerFT::loadFont(string path, int size) {
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
        font->characters[c].size = Vec2((float) face->glyph->bitmap.width / (w * 16), (float) face->glyph->bitmap.rows / (h * 16));
        font->characters[c].bearing = Vec2((float) face->glyph->bitmap_left / (w * 16), (float) face->glyph->bitmap_top / (h * 16));
        font->characters[c].advance = (float) face->glyph->advance.x / (w * 16);
    }

    // Clear FreeType objects
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
        
    // Create texture from pixel data
    TextureId texture = textureManager->getTexture(pixels, w * 16, h * 16, 1);
    if(texture < 0)
        return nullptr;
    font->texture = texture;
    
    return font;
}

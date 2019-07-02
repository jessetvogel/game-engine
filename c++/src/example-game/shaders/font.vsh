uniform vec2 uOffset;
attribute vec2 aVertex;
varying vec2 vTexCoord;
uniform mat4 uMVP;

void main() {
    vTexCoord = aVertex;
    vTexCoord.y = 1.0 - vTexCoord.y;
    
    gl_Position = uMVP * vec4(aVertex + uOffset, 0.0, 1.0);
}

attribute vec2 aVertex;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;

uniform mat4 uMVP;

void main() {
    vTexCoord = aTexCoord;
    
    gl_Position = uMVP * vec4(aVertex, 0.0, 1.0);
}

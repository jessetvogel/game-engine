attribute vec2 aVertex;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;
uniform vec2 uCenter;
uniform mat4 uMVP;

void main() {
    vTexCoord = aTexCoord;
    vTexCoord.y = 1.0 - vTexCoord.y;
    gl_Position = uMVP * vec4(aVertex - uCenter, 0.0, 1.0);
}

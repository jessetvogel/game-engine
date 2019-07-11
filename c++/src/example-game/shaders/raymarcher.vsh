attribute vec2 aVertex;
uniform vec2 uView;
varying vec2 vUV;

void main() {
    vUV = aVertex * uView * 0.5;
    gl_Position = vec4(aVertex, 0.0, 1.0);
}

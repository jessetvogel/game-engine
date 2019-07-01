uniform sampler2D uTexture;
varying vec2 vTexCoord;

void main() {
    vec4 c = texture2D(uTexture, vTexCoord);
    gl_FragColor = c;
}

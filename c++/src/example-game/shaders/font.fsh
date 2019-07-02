uniform sampler2D uTexture;
varying vec2 vTexCoord;
uniform int uChar;
uniform vec4 uColor;

void main() {
    float x = mod(float(uChar), 16.0);
    float y = floor(float(uChar) / 16.0);
    vec2 offset = vec2(x, y) * 0.0625;
    
    gl_FragColor = uColor;
    gl_FragColor.a = texture2D(uTexture, offset + vTexCoord * 0.0625).r;
}

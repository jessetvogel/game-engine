uniform sampler2D uTexture;
varying vec2 vTexCoord;
uniform vec4 uFrame;

void main() {
    gl_FragColor = texture2D(uTexture, uFrame.xy + uFrame.zw * vTexCoord);
}

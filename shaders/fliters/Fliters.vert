attribute vec4 a_position;
attribute vec2 a_texCoord0;

void main() {
    gl_Position = a_position;
    gl_TexCoord[0]  = vec4(a_texCoord0, 1.0, 1.0);
}

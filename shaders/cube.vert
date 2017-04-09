attribute vec4 a_position;
attribute vec2 a_tex0;

uniform mat4 u_projMatrix;
uniform mat4 u_modelViewMatrix;

void main() {
    gl_Position = u_projMatrix*u_modelViewMatrix*a_position;
    gl_TexCoord[0]  = vec4(a_tex0, 1.0, 1.0);
}

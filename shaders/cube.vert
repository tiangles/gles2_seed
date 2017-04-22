attribute vec4 a_position;
attribute vec2 a_texCoord0;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

uniform mat4 u_modelViewMatrix;
uniform mat4 u_modelViewProjMatrix;

void main() {
    gl_Position = u_projMatrix*u_modelViewMatrix*a_position;
    gl_TexCoord[0]  = vec4(a_texCoord0, 1.0, 1.0);
}

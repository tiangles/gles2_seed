// textures
uniform sampler2D u_texture0;
const vec4 bkColor = vec4(0.5, 0.5, 0.5, 1.0);
const vec3 W = vec3(0.2125, 0.7154, 0.0721);
const vec2 TexSize = vec2(638, 960);

void main() {
    vec2 tex = gl_TexCoord[0].st;

    vec2 upLeftUV = vec2(tex.x-1.0/TexSize.x, tex.y-1.0/TexSize.y);
    vec4 curColor = texture2D(u_texture0, tex);
    vec4 upLeftColor = texture2D(u_texture0, upLeftUV);
    vec4 delColor = curColor - upLeftColor;
    float luminance = dot(delColor.rgb, W);
    gl_FragColor = vec4(vec3(luminance), 0.0) + bkColor;
}

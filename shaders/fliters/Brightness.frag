// textures
uniform sampler2D u_texture0;
const float brightness = 0.3;

void main() {
    vec2 tex = gl_TexCoord[0].st;

    vec4 textureColor = texture2D(u_texture0, tex);

    gl_FragColor = vec4((textureColor.rgb + vec3(brightness)), textureColor.w);
}

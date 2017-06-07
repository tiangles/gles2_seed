uniform sampler2D u_texture0;

void main() {
    vec2 tex = gl_TexCoord[0].st;

    vec4 textureColor = texture2D(u_texture0, tex);

    gl_FragColor = vec4((1.0 - textureColor.rgb), textureColor.w);
}

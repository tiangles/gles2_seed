uniform sampler2D u_texture0;

void main() {
    vec2 tex = gl_TexCoord[0].st;
    gl_FragColor = texture2D(u_texture0, tex);
}

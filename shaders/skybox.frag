uniform sampler2D u_texture0;

void main()
{
    gl_FragColor = texture2D(u_texture0, gl_TexCoord[0].st);
}

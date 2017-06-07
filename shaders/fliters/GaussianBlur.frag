uniform sampler2D u_texture0;

const int GAUSSIAN_SAMPLES = 9;

void main()
{
    vec2 tex = gl_TexCoord[0].st;
    vec3 sum = vec3(0.0);
    vec4 fragColor=texture2D(u_texture0, tex);
    
    int multiplier = 0;
    vec2 blurStep;
    vec2 singleStepOffset = vec2(1.0/638.0, 1.0/960.0);

    vec2 blurCoordinates[GAUSSIAN_SAMPLES];
    for (int i = 0; i < GAUSSIAN_SAMPLES; i++)
    {
        multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));
        // Blur in x (horizontal)
        blurStep = float(multiplier) * singleStepOffset;
        blurCoordinates[i] = tex + blurStep;
    }

    sum += texture2D(u_texture0, blurCoordinates[0]).rgb * 0.05;
    sum += texture2D(u_texture0, blurCoordinates[1]).rgb * 0.09;
    sum += texture2D(u_texture0, blurCoordinates[2]).rgb * 0.12;
    sum += texture2D(u_texture0, blurCoordinates[3]).rgb * 0.15;
    sum += texture2D(u_texture0, blurCoordinates[4]).rgb * 0.18;
    sum += texture2D(u_texture0, blurCoordinates[5]).rgb * 0.15;
    sum += texture2D(u_texture0, blurCoordinates[6]).rgb * 0.12;
    sum += texture2D(u_texture0, blurCoordinates[7]).rgb * 0.09;
    sum += texture2D(u_texture0, blurCoordinates[8]).rgb * 0.05;

    gl_FragColor = vec4(sum,fragColor.a);
}

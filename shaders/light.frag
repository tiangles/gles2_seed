uniform vec3 u_lightPos;

uniform vec4 u_ambient;

uniform vec4 u_diffuse;

varying vec4 v_fragPos;
varying vec3 v_normal;

uniform sampler2D u_texture0;

vec4 ambientColor(){
    return u_ambient;
}

vec4 diffuseColor(){
    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPos - v_fragPos.xyz);
    float diff = max(dot(normal, lightDir), 0.0);
    return u_diffuse*diff;
}

void main()
{
    vec4 ambient = ambientColor();
    vec4 diffuse = diffuseColor();
    vec4 texColor = texture2D(u_texture0, gl_TexCoord[0].st);
    gl_FragColor = texColor*(ambient + diffuse);
}

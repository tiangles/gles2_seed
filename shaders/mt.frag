// textures

uniform sampler2D u_textureFg;
uniform sampler2D u_textureBg;

// the texCoords passed in from the vertex shader.
uniform vec2 u_resolution;

vec2 texCoord(){
  return vec2(gl_FragCoord.x, u_resolution.y-gl_FragCoord.y)/u_resolution;
}

void main() {
    vec2 coord = texCoord();
    vec4 bg=texture2D(u_textureBg, coord);
    vec4 fg=texture2D(u_textureFg, coord);
    gl_FragColor = bg*fg;
}

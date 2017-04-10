#pragma once

const char* VERTEX_SHADER_SOURCE =
        "attribute vec4 a_position; \n"
        "attribute vec2 a_tex0; \n"
        "varying vec2 v_texCoord0; \n"
        "void main() \n"
        "{ \n"
        "    gl_Position = a_position; \n"
        "    v_texCoord0  = a_tex0;\n"
        "} \n"
        ;


const char* FRAGMENT_SHADER_SOURCE =
        "#ifndef GL_ES\n"
            "#define mediump \n"
            "#define lowp \n"
            "#define highp \n"
        "#endif\n"
        "uniform sampler2D u_texSampler_0; \n"
        "varying mediump vec2 v_texCoord0; \n"
        "void main() \n"
        "{ \n"
        "  gl_FragColor = texture2D(u_texSampler_0, v_texCoord0); \n"
        "} \n"
        ;


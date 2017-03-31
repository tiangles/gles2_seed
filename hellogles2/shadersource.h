#pragma once

const char* VERTEX_SHADER_SOURCE =
        "uniform  mat4 u_mvMatrix; \n"
        "uniform  mat4 u_pMatrix; \n"
        "uniform  vec4 u_texMatrix0; \n"
        "uniform  vec4 u_texMatrix1; \n"
        "attribute vec4 a_position; \n"
        "attribute vec3 a_normal; \n"
        "attribute vec2 a_tex0; \n"
        "attribute vec2 a_tex1; \n"
        "attribute vec4 a_color; \n"
        "varying vec2 v_texCoord0; \n"
        "varying vec2 v_texCoord1; \n"
        "varying vec4 v_color; \n"
        "void main() \n"
        "{ \n"
        "    gl_Position = a_position; \n"
        "    gl_TexCoord[0]  = gl_MultiTexCoord0;\n"
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
        "  gl_FragColor = texture2D(u_texSampler_0, gl_TexCoord[0].st); \n"
        "} \n"
        ;


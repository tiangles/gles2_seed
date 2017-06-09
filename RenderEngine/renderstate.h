#pragma once
#include <QtOpenGL>

namespace GLES2 {
class Renderer;

class RenderState:private QOpenGLFunctions {
public:
    // Reset the render states.
    void invalidate();

    bool blending(GLboolean enable);
    bool blendingFunc(GLenum sfactor, GLenum dfactor);

    bool clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
    bool colorMask(GLboolean r, GLboolean g, GLboolean b, GLboolean a);

    bool cullFace(GLenum face);
    bool culling(GLboolean enable);

    bool depthTest(GLboolean enable);
    bool depthMask(GLboolean enable);

    bool frontFace(GLenum face);
    bool stencilMask(GLuint mask);

    bool stencilFunc(GLenum func, GLint ref, GLuint mask);
    bool stencilOp(GLenum sfail, GLenum spassdfail, GLenum spassdpass);

    bool stencilTest(GLboolean enable);

    bool shaderProgram(GLuint program);
    void shaderProgramUnset(GLuint program);

    bool texture(GLenum target, GLuint handle);
    GLuint getTextureUnit(GLuint _unit);
    bool textureUnit(GLuint unit);
    void textureUnset(GLenum target, GLuint handle);

    bool vertexBuffer(GLuint handle);
    bool indexBuffer(GLuint handle);
    bool framebuffer(GLuint handle);

    bool viewport(GLint x, GLint y, GLsizei width, GLsizei height);

    void vertexBufferUnset(GLuint handle);
    void indexBufferUnset(GLuint handle);

private:
    RenderState();
    ~RenderState();

    RenderState(const RenderState&) = delete;
    RenderState(RenderState&&) = delete;
    RenderState& operator=(const RenderState&) = delete;
    RenderState& operator=(RenderState&&) = delete;

    friend class Renderer;

private:

    int m_validGeneration = 0;
    uint32_t m_nextTextureUnit = 0;

    struct {
        GLboolean enabled;
        bool set;
    } m_blending, m_culling, m_depthMask, m_depthTest, m_stencilTest;

    struct {
        GLenum sfactor, dfactor;
        bool set;
    } m_blendingFunc;

    struct {
        GLuint mask;
        bool set;
    } m_stencilMask;

    struct {
        GLenum func;
        GLint ref;
        GLuint mask;
        bool set;
    } m_stencilFunc;

    struct {
        GLenum sfail, spassdfail, spassdpass;
        bool set;
    } m_stencilOp;

    struct {
        GLboolean r, g, b, a;
        bool set;
    } m_colorMask;

    struct {
        GLenum face;
        bool set;
    } m_frontFace, m_cullFace;

    struct {
        GLuint handle;
        bool set;
    } m_vertexBuffer, m_indexBuffer;

    struct {
        GLuint program;
        bool set;
    } m_program;

    struct {
        GLclampf r, g, b, a;
        bool set;
    } m_clearColor;

    struct {
        GLenum target;
        GLuint handle;
        bool set;
    } m_texture;

    struct {
        GLuint unit;
        bool set;
    } m_textureUnit;

    struct FrameBufferState {
        GLuint handle;
        bool set;
    } m_framebuffer;

    struct ViewportState {
        GLint x;
        GLint y;
        GLsizei width;
        GLsizei height;
        bool set;
    } m_viewport;
};

}

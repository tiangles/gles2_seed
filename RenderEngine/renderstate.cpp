#include "renderstate.h"

using namespace GLES2;

#define LOGE(x, ...)

RenderState::RenderState()
{
    initializeOpenGLFunctions();

    m_blending = { 0, false };
    m_culling = { 0, false };
    m_depthMask = { 0, false };
    m_depthTest = { 0, false };
    m_stencilTest = { 0, false };
    m_blendingFunc = { 0, 0, false };
    m_stencilMask = { 0, false };
    m_stencilFunc = { 0, 0, 0, false };
    m_stencilOp = { 0, 0, 0, false };
    m_colorMask = { 0, 0, 0, 0, false };
    m_frontFace = { 0, false };
    m_cullFace = { 0, false };
    m_vertexBuffer = { 0, false };
    m_indexBuffer = { 0, false };
    m_program = { 0, false };
    m_clearColor = { 0., 0., 0., 0., false };
    m_texture = { 0, 0, false };
    m_textureUnit = { 0, false };
    m_framebuffer = { 0, false };
    m_viewport = { 0, 0, 0, 0, false };
}

RenderState::~RenderState() {
}

void RenderState::invalidate() {

    m_blending.set = false;
    m_blendingFunc.set = false;
    m_clearColor.set = false;
    m_colorMask.set = false;
    m_cullFace.set = false;
    m_culling.set = false;
    m_depthTest.set = false;
    m_depthMask.set = false;
    m_frontFace.set = false;
    m_stencilTest.set = false;
    m_stencilMask.set = false;
    m_program.set = false;
    m_indexBuffer.set = false;
    m_vertexBuffer.set = false;
    m_texture.set = false;
    m_textureUnit.set = false;
    m_viewport.set = false;
    m_framebuffer.set = false;

    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    glDepthRange(0.0, 1.0);

}

inline void setGlFlag(GLenum flag, GLboolean enable) {
    if (enable) {
        glEnable(flag);
    } else {
        glDisable(flag);
    }
}

bool RenderState::blending(GLboolean enable) {
    if (!m_blending.set || m_blending.enabled != enable) {
        m_blending = { enable, true };
        setGlFlag(GL_BLEND, enable);
        return false;
    }
    return true;
}

bool RenderState::blendingFunc(GLenum sfactor, GLenum dfactor) {
    if (!m_blendingFunc.set || m_blendingFunc.sfactor != sfactor || m_blendingFunc.dfactor != dfactor) {
        m_blendingFunc = { sfactor, dfactor, true };
        glBlendFunc(sfactor, dfactor);
        return false;
    }
    return true;
}

bool RenderState::clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
    if (!m_clearColor.set || m_clearColor.r != r || m_clearColor.g != g || m_clearColor.b != b || m_clearColor.a != a) {
        m_clearColor = { r, g, b, a, true };
        glClearColor(r, g, b, a);
        return false;
    }
    return true;
}

bool RenderState::colorMask(GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
    if (!m_colorMask.set || m_colorMask.r != r || m_colorMask.g != g || m_colorMask.b != b || m_colorMask.a != a) {
        m_colorMask = { r, g, b, a, true };
        glColorMask(r, g, b, a);
        return false;
    }
    return true;
}

bool RenderState::cullFace(GLenum face) {
    if (!m_cullFace.set || m_cullFace.face != face) {
        m_cullFace = { face, true };
        glCullFace(face);
        return false;
    }
    return true;
}

bool RenderState::culling(GLboolean enable) {
    if (!m_culling.set || m_culling.enabled != enable) {
        m_culling = { enable, true };
        setGlFlag(GL_CULL_FACE, enable);
        return false;
    }
    return true;
}

bool RenderState::depthTest(GLboolean enable) {
    if (!m_depthTest.set || m_depthTest.enabled != enable) {
        m_depthTest = { enable, true };
        setGlFlag(GL_DEPTH_TEST, enable);
        return false;
    }
    return true;
}

bool RenderState::depthMask(GLboolean enable) {
    if (!m_depthMask.set || m_depthMask.enabled != enable) {
        m_depthMask = { enable, true };
        glDepthMask(enable);
        return false;
    }
    return true;
}

bool RenderState::frontFace(GLenum face) {
    if (!m_frontFace.set || m_frontFace.face != face) {
        m_frontFace = { face, true };
        glFrontFace(face);
        return false;
    }
    return true;
}

bool RenderState::stencilMask(GLuint mask) {
    if (!m_stencilMask.set || m_stencilMask.mask != mask) {
        m_stencilMask = { mask, true };
        glStencilMask(mask);
        return false;
    }
    return true;
}

bool RenderState::stencilFunc(GLenum func, GLint ref, GLuint mask) {
    if (!m_stencilFunc.set || m_stencilFunc.func != func || m_stencilFunc.ref != ref || m_stencilFunc.mask != mask) {
        m_stencilFunc = { func, ref, mask, true };
        glStencilFunc(func, ref, mask);
        return false;
    }
    return true;
}

bool RenderState::stencilOp(GLenum sfail, GLenum spassdfail, GLenum spassdpass) {
    if (!m_stencilOp.set || m_stencilOp.sfail != sfail || m_stencilOp.spassdfail != spassdfail || m_stencilOp.spassdpass != spassdpass) {
        m_stencilOp = { sfail, spassdfail, spassdpass, true };
        glStencilOp(sfail, spassdfail, spassdpass);
        return false;
    }
    return true;
}

bool RenderState::stencilTest(GLboolean enable) {
    if (!m_stencilTest.set || m_stencilTest.enabled != enable) {
        m_stencilTest = { enable, true };
        setGlFlag(GL_STENCIL_TEST, enable);
        return false;
    }
    return true;
}

bool RenderState::shaderProgram(GLuint program) {
    if (!m_program.set || m_program.program != program) {
        m_program = { program, true };
        glUseProgram(program);
        return false;
    }
    return true;
}

bool RenderState::texture(GLenum target, GLuint handle) {
    if (!m_texture.set || m_texture.target != target || m_texture.handle != handle) {
        m_texture = { target, handle, true };
        glBindTexture(target, handle);
        return false;
    }
    return true;
}

GLuint RenderState::getTextureUnit(GLuint unit)
{
    return GL_TEXTURE0 + unit;
}

bool RenderState::textureUnit(GLuint unit) {
    if (!m_textureUnit.set || m_textureUnit.unit != unit) {
        m_textureUnit = { unit, true };
        // Our cached texture handle is irrelevant on the new unit, so unset it.
        m_texture.set = false;
        glActiveTexture(getTextureUnit(unit));
        return false;
    }
    return true;
}

bool RenderState::vertexBuffer(GLuint handle) {
    if (!m_vertexBuffer.set || m_vertexBuffer.handle != handle) {
        m_vertexBuffer = { handle, true };
        glBindBuffer(GL_ARRAY_BUFFER, handle);
        return false;
    }
    return true;
}

bool RenderState::indexBuffer(GLuint handle) {
    if (!m_indexBuffer.set || m_indexBuffer.handle != handle) {
        m_indexBuffer = { handle, true };
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
        return false;
    }
    return true;
}

void RenderState::vertexBufferUnset(GLuint handle) {
    if (m_vertexBuffer.handle == handle) {
        m_vertexBuffer.set = false;
    }
}

void RenderState::indexBufferUnset(GLuint handle) {
    if (m_indexBuffer.handle == handle) {
        m_indexBuffer.set = false;
    }
}

void RenderState::shaderProgramUnset(GLuint program) {
    if (m_program.program == program) {
        m_program.set = false;
    }
}

void RenderState::textureUnset(GLenum /*target*/, GLuint handle) {
    if (m_texture.handle == handle) {
        m_texture.set = false;
    }
}

bool RenderState::framebuffer(GLuint handle) {
    if (!m_framebuffer.set || m_framebuffer.handle != handle) {
        m_framebuffer = { handle, true };
        glBindFramebuffer(GL_FRAMEBUFFER, handle);
        return false;
    }
    return true;
}

bool RenderState::viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    if (!m_viewport.set || m_viewport.x != x || m_viewport.y != y
      || m_viewport.width != width || m_viewport.height != height) {
        m_viewport = { x, y, width, height, true };
        glViewport(x, y, width, height);
        return false;
    }
    return true;
}


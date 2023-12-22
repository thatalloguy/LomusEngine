#include "DebugEBO.h"

void DebugEBO::copyDataIntoEBO(GLsizei size, const void* data, GLenum usage)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void* DebugEBO::mapBuffer(GLenum access)
{
    return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, access);
}

void DebugEBO::unMapBuffer()
{
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}


void DebugEBO::bind()
{
    assert(id != 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void DebugEBO::unbind()
{
    assert(id != 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DebugEBO::destroy()
{
    if (id != 0) {
        glDeleteBuffers(1, &id);
        id = 0;
    }
}
DebugEBO::DebugEBO()
{
}

DebugEBO::~DebugEBO()
{
    destroy();
}

bool DebugEBO::create()
{
    destroy();

    glGenBuffers(1, &id);
    assert(id != 0);

    return true;
}

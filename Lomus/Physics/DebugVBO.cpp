#include "DebugVBO.h"

DebugVBO::DebugVBO()
{
}

DebugVBO::~DebugVBO()
{
	destroy();
}

bool DebugVBO::create()
{
	destroy();

	glGenBuffers(1, &id);
	assert(id != 0);

	return true;
}

void DebugVBO::copyDataIntoVBO(GLsizei size, const void* data, GLenum usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void* DebugVBO::mapBuffer(GLenum access)
{
	return glMapBuffer(GL_ARRAY_BUFFER, access);
}

void DebugVBO::unMapBuffer()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}


void DebugVBO::bind()
{
	assert(id != 0);

	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void DebugVBO::unbind()
{
	assert(id != 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DebugVBO::destroy()
{
	if (id != 0) {
		glDeleteBuffers(1, &id);
		id = 0;
	}
}

void DebugVBO::clear() {

    bind();

    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

    unbind();

}

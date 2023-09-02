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
	glBufferData(targetData, size, data, usage);
}

void* DebugVBO::mapBuffer(GLenum access)
{
	return glMapBuffer(targetData, access);
}

void DebugVBO::unMapBuffer()
{
	glUnmapBuffer(targetData);
}


void DebugVBO::bind()
{
	assert(id != 0);

	glBindBuffer(targetData, id);
}

void DebugVBO::unbind()
{
	assert(id != 0);

	glBindBuffer(targetData, 0);
}

void DebugVBO::destroy()
{
	if (id != 0) {
		glDeleteFramebuffers(1, &id);
		id = 0;
	}
}

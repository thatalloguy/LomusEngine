#include "DebugVAO.h"

DebugVAO::DebugVAO() : id(0) {
}

DebugVAO::~DebugVAO()
{
	Delete();
}

bool DebugVAO::create()
{
	Delete();

	glGenVertexArrays(1, &id);
	assert(id != 0);

	return true;
}

void DebugVAO::bind()
{
	glBindVertexArray(id);
}

void DebugVAO::unbind()
{
	glBindVertexArray(0);
}

void DebugVAO::Delete()
{
	if (id != 0) {
		glDeleteVertexArrays(1, &id);
		id = 0;
	}
	
}

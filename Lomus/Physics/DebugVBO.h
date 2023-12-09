#pragma once
#include <glad/glad.h>
#include <cassert>
#include <iostream>

class DebugVBO {

public:
	DebugVBO();
	~DebugVBO();

	bool create();

	void copyDataIntoVBO(GLsizei size, const void* data, GLenum usage);
	void* mapBuffer(GLenum access);

	void unMapBuffer();

	void bind();
	void unbind();

    void clear();

	void destroy();
private:
	GLuint id;
	GLenum targetData;
};
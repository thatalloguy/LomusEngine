#pragma once


#include <cassert>
#include <iostream>
#include <glad/glad.h>

class DebugVAO {
public:
	DebugVAO();
	~DebugVAO();

	bool create();
	void bind();
	void unbind();
	void Delete();
private:
	GLuint id;
};
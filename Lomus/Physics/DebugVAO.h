#pragma once
#include <glad/glad.h>
#include <cassert>
#include <iostream>

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
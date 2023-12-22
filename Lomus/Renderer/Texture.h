#pragma once

#include <glad/glad.h>
#include "../../Libs/Include/stb/std_image.h"

#include "../Shader/ShaderClass.h"


class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};


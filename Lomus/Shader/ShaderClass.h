#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

	void setIntUniform(const char* name, int value);
	
	void setVec3Uniform(const char* name, float x, float y, float z);
	void setVec4Uniform(const char* name, float x, float y, float z, float w);
	void setFloatUniform(const char* name, float f);

	GLuint getUniformLocation(const char* name);

	// Activates the Shader Program
	void Activate();
	void Deactivate();
	// Deletes the Shader Program
	void Delete();

    void Recompile();

private:
    const char* vertexFile; // for recompiling;
    const char* fragmentFile;



	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif
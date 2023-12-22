
#pragma once

#include <glad/glad.h>
#include <cassert>
#include <iostream>

class DebugEBO {

public:
    DebugEBO();
    ~DebugEBO();

    bool create();

    void copyDataIntoEBO(GLsizei size, const void* data, GLenum usage);
    void* mapBuffer(GLenum access);

    void unMapBuffer();

    void bind();
    void unbind();

    void destroy();
private:
    GLuint id;
    GLenum targetData;
};


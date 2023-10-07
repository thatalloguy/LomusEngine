#pragma once
#include <glad/glad.h>
#include <iostream>

namespace Lomus{

    class FrameBuffer {
    public:
        FrameBuffer(int resolutionWidth, int resolutionHeight);
        void Delete();

        unsigned int fbo;
        unsigned int fboTexture;
    };

}


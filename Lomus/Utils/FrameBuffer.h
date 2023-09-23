#pragma once
#include <glad/glad.h>
#include <iostream>

namespace Lomus{
    class FrameBuffer {
    public:
        void Init();
        void Delete();
    private:
        unsigned int fbo;
    };

}


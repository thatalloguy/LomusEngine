#pragma once
#include <glad/glad.h>


namespace Lomus{
    class FrameBuffer {
    public:
        void Init();
    private:
        unsigned int fbo;
    };

}



#include "FrameBuffer.h"

using namespace Lomus;

void Lomus::FrameBuffer::Init() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        // LETS GOOOOO

        std::cout << "Sucsessfully generated a framebuffer\n";
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void FrameBuffer::Delete() {
    glDeleteFramebuffers(1, &fbo);
}

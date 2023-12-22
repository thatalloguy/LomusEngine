
#include "FrameBuffer.h"

using namespace Lomus;


void FrameBuffer::Delete() {
    glDeleteFramebuffers(1, &fbo);
}
FrameBuffer::FrameBuffer(int resolutionWidth, int resolutionHeight) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &fboTexture);
    glBindTexture(GL_TEXTURE_2D, fboTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolutionWidth, resolutionHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);


    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    // Unbind the framebuffer after checking its status.


    if (status == GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "WE DID IT BOYS\n";
    } else {
        std::cout << "WAH WAH WAH ;-;\n";
        std::cerr << "Framebuffer Error: " << status << "\n";
    }
}
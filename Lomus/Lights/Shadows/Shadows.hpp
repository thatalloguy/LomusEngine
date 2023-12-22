#pragma once
#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace Lomus::Lighting::ShadowUtils{


    class ShadowMapFBO {
    public:
        ShadowMapFBO();
        ~ShadowMapFBO();

        bool Init(unsigned  int Width, unsigned int Height) {
            m_width = Width;
            m_height = Height;

            spdlog::info("Creating ShadowMap frameBuffer");
            glGenFramebuffers(1, &m_fbo);

            //Texture stuff <- very good comment i know :), i dont like comments code should speak mostly for itself !
            glGenTextures(1, &m_shadowMap);
            glBindTexture(GL_TEXTURE_2D, m_shadowMap);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_TEXTURE_2D, m_shadowMap, 0);

            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);

            GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

            if (Status != GL_FRAMEBUFFER_COMPLETE) {
                spdlog::error("Could not make the shadowMap framebuffer {}", Status);
                return false;
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            return true;
        }

        void bindForWritting() {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
            glViewport(0, 0, m_width, m_height);
        }

        void bindForReading(GLenum TextureUnit) {
            glActiveTexture(TextureUnit);
            glBindTexture(GL_TEXTURE_2D, m_shadowMap);
        }

    private:
        int m_width = 0;
        int m_height = 0;
        GLuint m_fbo;
        GLuint m_shadowMap;
    };

}

namespace  Lomus::Lighting::ShadowMap {

}
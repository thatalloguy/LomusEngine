#include "../stb/include/std_image.h"
#include <glm/gtx/euler_angles.hpp>
#include "Billboard.h"
#include "spdlog/spdlog.h"

void LomusModelTypes::Billboard::load(std::string& imagePath) {
    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrComponents, 0);



    if (data) {


        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glGenTextures(1, &rawTexture);
        glBindTexture(GL_TEXTURE_2D, rawTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        spdlog::info("Sucsessfully loaded image for billboard | " + imagePath + " | " + std::to_string(width) + " | " + std::to_string(height));
    } else {
        spdlog::error("Couldnt load image: " + imagePath);

        stbi_image_free(data);
    }
}

LomusModelTypes::Billboard::~Billboard() {
    glDeleteTextures(1, &rawTexture);
}

void LomusModelTypes::Billboard::Render(Lomus::Camera &camera, Shader &billboardShader) {
    billboardShader.Activate();

    glm::mat4 model;
    glm::mat4 trans = glm::mat4(1.0f);
    glm::translate(trans, position);
    glm::mat4 sca = glm::mat4(1.0f);
    sca = glm::scale(sca, scale);
    glm::mat4 rot;
    if (!lockYRot) {
        rot = glm::inverse(glm::lookAt(position, camera.Position, glm::vec3(0, 1, 0)));
    } else {
        rot = glm::inverse(glm::lookAt(position, glm::vec3(camera.Position.x, position.y, camera.Position.z), glm::vec3(0, 1, 0)));

    }

    model = trans  * rot * sca;


    billboardShader.setMat4Uniform("model", model);
    billboardShader.setMat4Uniform("camMatrix", camera.cameraMatrix);

    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, rawTexture);
    billboardShader.setIntUniform("billBoardTexture", 10);


    // opengl stuff :(
    if (quadVAO == 0)
    {
        float quadVertices[] = {
                // positions                      // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);


}

void LomusModelTypes::Billboard::swapImage(std::string &imagePath) {
    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glGenTextures(1, &rawTexture);
        glBindTexture(GL_TEXTURE_2D, rawTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        spdlog::info("Sucsessfully loaded image for billboard | " + imagePath + " | " + std::to_string(width) + " | " + std::to_string(height));
    } else {
        spdlog::error("Couldnt load image: " + imagePath);

        stbi_image_free(data);
    }
}


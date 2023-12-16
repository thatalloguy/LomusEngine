#pragma once

#include <glad/glad.h>

#include "Camera.h"
#include <glm/glm.hpp>


namespace LomusModelTypes {

    // Billboards are not instanced :(


    class Billboard {

    public:
        void load(std::string& imagePath);
        ~Billboard();

        void Render(Lomus::Camera& camera, Shader& billboardShader);

        void swapImage(std::string& imagePath);
        bool amEmpty = true; // has to be set by other class for some reasone :(

        glm::vec3 scale{4, 4, 4};
        glm::vec3 position{0, 0, 0};


    private:
        unsigned int rawTexture;
        unsigned int quadVAO = 0;
        unsigned int quadVBO;



    };

}

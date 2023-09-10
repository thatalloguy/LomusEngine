#pragma once

#include "../../Libs/Include/tinygltf/tiny_gltf.h"
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <map>

#include "../Shader/ShaderClass.h"
#include "../Renderer/Camera.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace Lomus {

    class Model {
    public:

        void Load(const char* path);
        void Render(Shader& shader, Camera& camera, glm::mat4 matrix,
                    glm::vec3 translation,
                    glm::quat rotation,
                    glm::vec3 scale);
        void cleanUp();

    private:

        std::pair<GLuint, std::map<int, GLuint>> bindModel();
        void bindModelNodes(std::map<int, GLuint>& vbos, tinygltf::Model &model, tinygltf::Node &node);
        void bindMesh(std::map<int, GLuint>& vbos, tinygltf::Model &model, tinygltf::Mesh &mesh);

        void drawModelNodes(const std::pair<GLuint, std::map<int, GLuint>>& vaoAndEbos, tinygltf::Node &node);
        void drawModel(const std::pair<GLuint, std::map<int, GLuint>>& vaoAndEbos);
        void drawMesh(const std::map<int, GLuint>& vbos, tinygltf::Mesh &mesh);

        tinygltf::Model mModel;
        std::pair<GLuint, std::map<int, GLuint>> vaoAndEbos;

    };


}

#include "Tmodel.h"

void Lomus::Model::Load(const char* path) {
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool result = loader.LoadASCIIFromFile(&mModel, &err, &warn, path);

    if (!warn.empty()) {
        std::cout << "Warning while loading Model: " << warn << "\n";
    }

    if (!err.empty()) {
        std::cout << "Error while loading Model: " << err << "\n";
    }

    if (!result) {
        std::cout << "Failed to load GlTF model: " << path << "\n";
    } else{
        std::cout << "Successfully loaded GLTF model " << path << "\n";
    }

    Lomus::Model::vaoAndEbos = bindModel();
}

std::pair<GLuint, std::map<int, GLuint>> Lomus::Model::bindModel() {
    std::map<int, GLuint> vbos;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const tinygltf::Scene &scene = mModel.scenes[mModel.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++i) {
        //assert((scene.nodes[i] >= 0) && (scene.nodes[i] < mModel.nodes.size()));
        bindModelNodes(vbos, mModel, mModel.nodes[scene.nodes[i]]);
    }
    glBindVertexArray(0);
    // cleanup vbos but do not delete index buffers yet
    for (auto it = vbos.cbegin(); it != vbos.cend();) {
        tinygltf::BufferView bufferView = mModel.bufferViews[it->first];
        if (bufferView.target != GL_ELEMENT_ARRAY_BUFFER) {
            glDeleteBuffers(1, &vbos[it->first]);
            vbos.erase(it++);
        }
        else {
            ++it;
        }
    }
    std::cout << "bound model\n";
    return {vao, vbos};

}

void Lomus::Model::bindModelNodes(std::map<int, GLuint> &vbos, tinygltf::Model &model, tinygltf::Node &node) {
    if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
        bindMesh(vbos, model, model.meshes[node.mesh]);
    }

    for (size_t i = 0; i < node.children.size(); i++) {
        assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
        bindModelNodes(vbos, model, model.nodes[node.children[i]]);
    }
}

void Lomus::Model::bindMesh(std::map<int, GLuint> &vbos, tinygltf::Model &model, tinygltf::Mesh &mesh) {
    for (size_t i = 0; i < model.bufferViews.size(); ++i) {
        const tinygltf::BufferView &bufferView = model.bufferViews[i];
        if (bufferView.target == 0) {  // TODO impl drawarrays
            std::cout << "WARN: bufferView.target is zero" << std::endl;
            continue;  // Unsupported bufferView.

        }

        const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
        std::cout << "bufferview.target " << bufferView.target << std::endl;

        GLuint vbo;
        glGenBuffers(1, &vbo);
        vbos[i] = vbo;
        glBindBuffer(bufferView.target, vbo);

        std::cout << "buffer.data.size = " << buffer.data.size()
                  << ", bufferview.byteOffset = " << bufferView.byteOffset
                  << std::endl;

        glBufferData(bufferView.target, bufferView.byteLength,
                     &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
    }

    for (size_t i = 0; i < mesh.primitives.size(); ++i) {
        tinygltf::Primitive primitive = mesh.primitives[i];
        tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

        for (auto &attrib : primitive.attributes) {
            tinygltf::Accessor accessor = model.accessors[attrib.second];
            int byteStride =
                    accessor.ByteStride(model.bufferViews[accessor.bufferView]);
            glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                size = accessor.type;
            }

            int vaa = -1;
            if (attrib.first.compare("POSITION") == 0) vaa = 0;
            if (attrib.first.compare("NORMAL") == 0) vaa = 1;
            if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
            if (vaa > -1) {
                glEnableVertexAttribArray(vaa);
                glVertexAttribPointer(vaa, size, accessor.componentType,
                                      accessor.normalized ? GL_TRUE : GL_FALSE,
                                      byteStride, BUFFER_OFFSET(accessor.byteOffset));
            } else
                std::cout << "vaa missing: " << attrib.first << std::endl;
        }

        if (model.textures.size() > 0) {
            // fixme: Use material's baseColor
            tinygltf::Texture &tex = model.textures[0];

            if (tex.source > -1) {

                GLuint texid;
                glGenTextures(1, &texid);

                tinygltf::Image &image = model.images[tex.source];

                glBindTexture(GL_TEXTURE_2D, texid);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                GLenum format = GL_RGBA;

                if (image.component == 1) {
                    format = GL_RED;
                } else if (image.component == 2) {
                    format = GL_RG;
                } else if (image.component == 3) {
                    format = GL_RGB;
                } else if (image.component == 4) {
                    format = GL_RGB;
                }
                else {
                    // ???
                    std::cerr << "ERROR: Unsupported Image type: " << image.component << "\n";
                }

                GLenum type = GL_UNSIGNED_BYTE;
                if (image.bits == 8) {
                    // ok
                } else if (image.bits == 16) {
                    type = GL_UNSIGNED_SHORT;
                } else {
                    // ???
                }

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
                             format, type, &image.image.at(0));
            }
        }
    }
}

void Lomus::Model::drawModelNodes(const std::pair<GLuint, std::map<int, GLuint>> &vaoAndEbos, tinygltf::Node &node) {

    if ((node.mesh >= 0) && (node.mesh < mModel.meshes.size())) {
        drawMesh(vaoAndEbos.second, mModel.meshes[node.mesh]);
    }
    for (size_t i = 0; i < node.children.size(); i++) {
        drawModelNodes(vaoAndEbos, mModel.nodes[node.children[i]]);
    }
}

void Lomus::Model::drawModel(const std::pair<GLuint, std::map<int, GLuint>> &vaoAndEbos) {
    glBindVertexArray(vaoAndEbos.first);

    const tinygltf::Scene &scene = mModel.scenes[mModel.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++i) {
        drawModelNodes(vaoAndEbos, mModel.nodes[scene.nodes[i]]);
    }

    glBindVertexArray(0);
}

void Lomus::Model::drawMesh(const std::map<int, GLuint> &vbos, tinygltf::Mesh &mesh) {
    for (size_t i = 0; i < mesh.primitives.size(); ++i) {
        tinygltf::Primitive primitive = mesh.primitives[i];
        tinygltf::Accessor indexAccessor = mModel.accessors[primitive.indices];

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos.at(indexAccessor.bufferView));

        glDrawElements(primitive.mode, indexAccessor.count,
                       indexAccessor.componentType,
                       BUFFER_OFFSET(indexAccessor.byteOffset));
    }
}





void Lomus::Model::Render(Shader &shader, Camera &camera,glm::mat4 matrix,
                          glm::vec3 translation,
                          glm::quat rotation,
                          glm::vec3 scale) {

    shader.Activate();
    shader.setIntUniform("diffuse0", mModel.textures[0].sampler);

    glBindVertexArray(vaoAndEbos.first);

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Transform the matrices to their correct form
    translation.y = -translation.y;
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    // Push the matrices to the vertex shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    glBindVertexArray(0);

    drawModel(vaoAndEbos);
}

void Lomus::Model::cleanUp() {
    glDeleteVertexArrays(1, &vaoAndEbos.first);
}





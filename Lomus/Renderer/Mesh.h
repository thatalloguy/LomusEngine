#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shader/ShaderClass.h"
#include "Camera.h"


#include <string>
#include <vector>
using namespace std;


#define MAX_BONE_INFLUENCE 4

struct Vertex {

    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};
namespace Lomus {
    struct Material {
        float metalAmplifier = 1.0f;
        float roughnessAmplifier = 1.0f;
        float aoAmplifier = 1.0f;
        float emissiveAmplifier = 1.0f;

        bool useMetalRoughnessMap = false;
        bool useAOMap = false;
        bool useNormalMap = false;
        bool useEmissivityMap = false;
    };

}


struct mTexture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<mTexture>      textures;
    unsigned int VAO;

    void Delete() {
        vertices.clear();
        indices.clear();
        textures.clear();
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }


    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<mTexture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }

    // render the mesh
    void Draw(Shader &shader, Lomus::Camera& camera,
              glm::mat4 matrix,
              glm::vec3 translation,
              glm::quat rotation,
              glm::vec3 scale,
              Lomus::Material& material,
              bool castShadow)
    {
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = textures[i].type;
            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.ID, (name + "0").c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        shader.setIntUniform("useMR", material.useMetalRoughnessMap);
        shader.setIntUniform("useAOMap", material.useAOMap);
        shader.setIntUniform("useNormalMap", material.useNormalMap);
        shader.setIntUniform("useEMap", material.useEmissivityMap);

        shader.setFloatUniform("metalAmplifier", material.metalAmplifier);
        shader.setFloatUniform("roughnessAmplifier", material.roughnessAmplifier);
        shader.setFloatUniform("aoAmplifier", material.aoAmplifier);
        shader.setFloatUniform("emissiveAmplifier", material.emissiveAmplifier);

        glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        camera.Matrix(shader, "camMatrix");

        // Initialize matrices

        GLint modelLoc = glGetUniformLocation(shader.ID, "model");


        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        // Transform the matrices to their correct form
        translation.y = translation.y;
        trans = glm::translate(trans, translation);
        rot = glm::mat4_cast(rotation);
        sca = glm::scale(sca, scale);

        matrix = trans * -rot * sca;

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(matrix)));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));
        glUniformMatrix3fv(shader.getUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);



        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

private:
    // render data
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.



        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        glBindVertexArray(0);
    }
};
#endif
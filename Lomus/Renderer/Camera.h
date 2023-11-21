#pragma once

//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../Shader/ShaderClass.h"
namespace Lomus {
    class Camera
    {
    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Right = glm::vec3(-1.0f, 0.0f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);

        float Yaw = -90;
        float Pitch = 0.0f;
        float Speed = 1.0f;



        int width;
        int height;

        bool firstClick = true;

        float sensitivity = 100.0f;

        Camera(int width, int height, glm::vec3 position);
        void updateMatrix(float FOVdeg, float nearPlane, float farPlane, float nWidth, float nHeight);
        void Matrix(Shader& shader, const char* uniform);
        void Inputs(GLFWwindow* window, float lockX, float lockY, float deltaTime);
        void Lookat(glm::vec3 position, float FOV, float nearPlane, float farPlane);

        glm::mat4 view;
        glm::mat4 projection;

    private:
        void updateVectors();
        double lastMouseX = 0;
        double lastMouseY = 0;
    };
}



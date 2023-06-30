#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vector_relational.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
//Engine
#include "Lomus/Renderer/Texture.h"
#include "Lomus/Shader/ShaderClass.h"
#include "Lomus/Renderer/Camera.h"
#include "Lomus/Renderer/Mesh.h"
#include "Lomus/Renderer/Model.h"
#include "Lomus/Utils/ToolBox.h"
//Other
#include "Libs/Include/stb/std_image.h"

const unsigned int width = 800;
const unsigned int height = 800;


int main() {
	glfwInit();
	

	//Window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Lomus", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create glfw Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//render
	gladLoadGL();
	glViewport(0, 0, width, height);
	
	

	Shader shaderProgram("Lomus/Shader/shaders/default.vert", "Lomus/Shader/shaders/default.frag");
	
	
	
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 20.0f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform2f(glGetUniformLocation(shaderProgram.ID, "fog"), 0.1f, 100.0f);
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	Model model("Resources/Model/Map/scene.gltf");


	//fps counter
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;


	while (!glfwWindowShouldClose(window)) {
		
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0) {
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string newTitle = "Lomus  | FPS: " + FPS;
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = crntTime;
			counter = 0;

			
		}

		//Renderstuff
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Error checking
		if (glGetError() != 0) {
			std::cout << glGetError() << std::endl;
		}
		
		
		camera.Inputs(window); 
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);


		glfwSwapBuffers(window);
		glfwPollEvents();
		

	}
	
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
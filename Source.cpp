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
#include "Lomus/Renderer/Skybox.h"
#include "Lomus/Utils/ToolBox.h"

#include "Lomus/Lights/shadowMap.h"
//Other
#include "Libs/Include/stb/std_image.h"

const unsigned int width = 800;
const unsigned int height = 800;

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}



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
	
	

	//SKYBOOXXX

	Skybox skybox;

	skybox.Init();


	Shader shaderProgram("Lomus/Shader/shaders/default.vert", "Lomus/Shader/shaders/default.frag");
	
	
	
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1, 1, 1);//glm::vec3(2.0f, 2.79f, -2.9f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	//glUniform2f(glGetUniformLocation(shaderProgram.ID, "fog"), 0.1f, 100.0f);
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(MessageCallback, 0);

	Model model("Resources/Model/airPlane/scene.gltf");

	////////////shadowMap my_shadowMap = shadowMap();

	////////////my_shadowMap.setLight(lightPos);

	//ShadowMappss


	shadowMap shadows = shadowMap();
	shadows.setLight(lightPos);



	//fps counter
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	bool isfirstFrame = true;

	while (!glfwWindowShouldClose(window)) {
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "Error: " << err << " \n";
			return -1;
		}


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
		//glEnable(GL_DEPTH_TEST);

		std::cout << camera.Position.x  << " | " << camera.Position.y << " | " << camera.Position.z << "\n";
		shadows.prepareRender();

		// Draw scene for shadow map
		model.Draw(shadows.shadowMapShader, camera);

		shadows.unprepareRender(width, height);

		shaderProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(shadows.lightProjection));
			
		// Bind the Shadow Map
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, shadows.my_shadowMap);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "shadowMap"),  2);
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);
		skybox.Render(camera, width, height);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	///////////my_shadowMap.Delete();
	shadows.Delete();
	skybox.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
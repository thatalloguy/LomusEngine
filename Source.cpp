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

#include "Lomus//Lights/LightManager.h"
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
	Shader shadowCubeMapProgram("Lomus/Shader/shaders/shadowCubeMap.vert", "Lomus/Shader/shaders/shadowCubeMap.frag", "Lomus/Shader/shaders/shadowCubeMap.geom");
	//Light myLight;
	glm::vec3 lightPos = glm::vec3(0, 5, 0);
	glm::vec4 lightColor = glm::vec4(1.0f, 0, 0, 1);
	float lightInten = 100.0f;
	/////myLight.Init(lightPos, glm::vec3(0, 0, 0), glm::vec4(0.7f, 1, 1, 1), 70.0f,  shaderProgram);
	///bool castShadow = true;
	//myLight.InitShadow(2048, 2048);

	shaderProgram.Activate();
	//glUniform2f(glGetUniformLocation(shaderProgram.ID, "fog"), 0.1f, 100.0f);
	//glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	//glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	//glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightInten"), lightInten);
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "castShadow"), 0.0f);
	glUniform1i(glGetUniformLocation(shaderProgram.ID, "lightType"), 1);

	LightManager lightManager;
	lightManager.Init();

	//lightManager.createNewLight(lightPos, lightColor, lightInten, "light1");
	//lightManager.createNewLight(glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1), 10, "light2");
	lightManager.createNewLight(glm::vec3(0, 4, 0), glm::vec4(0.1f, 0.1f, 0.1f, 1), 5, "light42");
	lightManager.createNewLight(glm::vec3(0, 4, 10), glm::vec4(0.1f, 0.1f, 0.4f, 1), 1, "light2");

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);

	glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(MessageCallback, 0);

	Model ground("Resources/Model/ground/scene.gltf");
	//Model trees("Resources/Model/trees/scene.gltf");

	////////////shadowMap my_shadowMap = shadowMap();

	////////////my_shadowMap.setLight(lightPos);

	//////cubeShadowMap pointShadow(2048, 2048, 100.0f, lightPos, shadowCubeMapProgram);

	float farPlane = 100.0f;
	unsigned int shadowMapWidth = 1;
	unsigned int shadowMapHeight = 1;
	
	cubeShadowMap cubeShadow;
	cubeShadow.Init(shadowMapWidth, shadowMapHeight, farPlane, lightPos, shadowCubeMapProgram);


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
			//return -1;
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

		//lightPos.x += 0.01f;

		
		



		cubeShadow.RenderPhaseBegin(shadowMapWidth, shadowMapHeight);

		// Draw scene for shadow map
		ground.Draw(shadowCubeMapProgram, camera);  //ground.Draw(myLight.myShadow.shadowMapShader, camera);
		//trees.Draw(shadowCubeMapProgram, camera);   //trees.Draw(myLight.myShadow.shadowMapShader, camera);
		
		cubeShadow.RenderPhaseEnd(width, height);

		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		lightManager.updateShader(shaderProgram);
		
		cubeShadow.UpdateShader(shaderProgram, farPlane, lightPos);
		
		ground.Draw(shaderProgram, camera);
		//trees.Draw(shaderProgram, camera);
		skybox.Render(camera, width, height);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	///////////my_shadowMap.Delete();
	
	//myLight.Delete(castShadow);
	skybox.Delete();
	lightManager.Delete();
	shaderProgram.Delete();
	shadowCubeMapProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	////////////pointShadow.Delete();
	shadowCubeMapProgram.Delete();
	return 0;
}
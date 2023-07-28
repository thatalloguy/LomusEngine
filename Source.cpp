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

#include "Lomus//Lights/Light.h"
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
	glm::vec3 lightPos = glm::vec3(0, 3, 0);
	glm::vec4 lightColor = glm::vec4(0.7f, 1, 1, 1);
	float lightInten = 70.0f;
	/////myLight.Init(lightPos, glm::vec3(0, 0, 0), glm::vec4(0.7f, 1, 1, 1), 70.0f,  shaderProgram);
	///bool castShadow = true;
	//myLight.InitShadow(2048, 2048);

	shaderProgram.Activate();
	//glUniform2f(glGetUniformLocation(shaderProgram.ID, "fog"), 0.1f, 100.0f);
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightInten"), lightInten);


	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);

	glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(MessageCallback, 0);

	Model ground("Resources/Model/ground/scene.gltf");
	Model trees("Resources/Model/trees/scene.gltf");

	////////////shadowMap my_shadowMap = shadowMap();

	////////////my_shadowMap.setLight(lightPos);

	//////cubeShadowMap pointShadow(2048, 2048, 100.0f, lightPos, shadowCubeMapProgram);

	unsigned int pointShadowMapFBO;
	glGenFramebuffers(1, &pointShadowMapFBO);
	float farPlane = 100.0f;
	unsigned int shadowMapWidth = 2048;
	unsigned int shadowMapHeight = 2048;


	// Texture for Cubemap Shadow Map FBO
	unsigned int depthCubemap;
	glGenTextures(1, &depthCubemap);

	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (unsigned int i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, pointShadowMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// Matrices needed for the light's perspective on all faces of the cubemap
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float) shadowMapWidth / shadowMapHeight, 0.1f, farPlane);
	glm::mat4 shadowTransforms[] =
	{
	shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
	shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
	shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
	shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)),
	shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)),
	shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0))
	};
	// Export all matrices to shader
	shadowCubeMapProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[0]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[0]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[1]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[1]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[2]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[2]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[3]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[3]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[4]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[4]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[5]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[5]));
	glUniform3f(glGetUniformLocation(shadowCubeMapProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shadowCubeMapProgram.ID, "farPlane"), farPlane);






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

		//lightPos.x += 0.01f;

		


		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, farPlane);
		glm::mat4 shadowTransforms[] =
		{
		shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
		shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
		shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
		shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)),
		shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)),
		shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0))
		};
		// Export all matrices to shader
		shadowCubeMapProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[0]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[0]));
		glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[1]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[1]));
		glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[2]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[2]));
		glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[3]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[3]));
		glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[4]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[4]));
		glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[5]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[5]));
		glUniform3f(glGetUniformLocation(shadowCubeMapProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(shadowCubeMapProgram.ID, "farPlane"), farPlane);



		



		///myLight.PrepareRender(castShadow);
		////////////////pointShadow.RenderPhaseBegin();
		glBindFramebuffer(GL_FRAMEBUFFER, pointShadowMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, shadowMapWidth, shadowMapHeight);
		// Draw scene for shadow map
		ground.Draw(shadowCubeMapProgram, camera);  //ground.Draw(myLight.myShadow.shadowMapShader, camera);
		trees.Draw(shadowCubeMapProgram, camera);   //trees.Draw(myLight.myShadow.shadowMapShader, camera);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// Switch back to the default viewport
		glViewport(0, 0, width, height);
		////////////////pointShadow.RenderPhaseEnd(shaderProgram, 100.0f);
		//myLight.UnprepareRender(castShadow, width, height, shaderProgram);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		shaderProgram.Activate();
		
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "farPlane"), farPlane);

		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "shadowCubeMap"), 2);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		ground.Draw(shaderProgram, camera);
		trees.Draw(shaderProgram, camera);
		skybox.Render(camera, width, height);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	///////////my_shadowMap.Delete();
	
	//myLight.Delete(castShadow);
	skybox.Delete();
	shaderProgram.Delete();
	glDeleteFramebuffers(1, &pointShadowMapFBO);
	shadowCubeMapProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	////////////pointShadow.Delete();
	shadowCubeMapProgram.Delete();
	return 0;
}
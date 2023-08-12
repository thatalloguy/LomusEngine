#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "../Shader/ShaderClass.h"

class shadowMap
{
public:

	void init(unsigned int width = 2048, unsigned int height = 2048);

	void setLight(glm::vec3 lightPos, glm::vec3 lightDirection);

	void prepareRender();
	void unprepareRender(float screenWidth, float screenHeight);
	void Delete();

	void renderShadowBuffer(int width, int height);

	glm::mat4 lightProjection;
	unsigned int my_shadowMap;
	Shader shadowMapShader = Shader("../../../Lomus/Shader/shaders/shadowMap.vert", "../../../Lomus/Shader/shaders/shadowMap.frag");
private:
	unsigned int shadowMapFBO;
	unsigned int shadowMapWidth;
	unsigned int shadowMapHeight;


	void initShader();

	glm::mat4 orthgonalProjection;
	glm::mat4 lightView;


	

};

class cubeShadowMap {

public:
	void Init(int shadowMapWidth, int shadowMapHeight, float farPlane, glm::vec3 lightPos, Shader cubeMapShadowShader);
	void RenderPhaseBegin(int shadowMapWidth, int shadowMapHeight);
	void RenderPhaseEnd(float windowWidth, float windowHeight);
	void UpdateShader(Shader DefaultShader, float farPlane, glm::vec3 lightPos);
	void Delete();
	void updateShadowMap(float farPlane, glm::vec3 lightPos, Shader shadowCubeMapProgram, int shadowMapWidth, int shadowMapHeight);


private:
	unsigned int pointShadowMapFBO;
	unsigned int depthCubemap;
};


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
#include "LightManager.h"

class ShadowMap
{
public:

	ShadowMap(unsigned int width = 2048, unsigned int height = 2048);

	void updateProjection(glm::vec3& lightPos);

	void prepareRender();
	void unprepareRender(float screenWidth, float screenHeight);
	void Delete();

    //void updateShader(Shader& shader);

	void renderShadowBuffer(int width, int height);

	glm::mat4 lightProjection;

    unsigned int my_shadowMap;
	Shader shadowMapShader{"../../Lomus/Shader/shaders/shadowMap.vert", "../../Lomus/Shader/shaders/shadowMap.frag"};
private:
	unsigned int shadowMapFBO;
	unsigned int shadowMapWidth;
	unsigned int shadowMapHeight;


	void uploadProjectionToShader();

	glm::mat4 orthgonalProjection;
	glm::mat4 lightView;


	

};

class cubeShadowMap {

public:
	void Init(int shadowMapWidth, int shadowMapHeight, float farPlane,  Light& shadowCaster, Shader& cubeMapShadowShader);
	void RenderPhaseBegin(int shadowMapWidth, int shadowMapHeight);
	void RenderPhaseEnd(float windowWidth, float windowHeight);
	void UpdateShader(Shader& DefaultShader, float farPlane, Light& shadowCaster);
	void Delete();
	void updateShadowMap(float farPlane, Light& shadowCaster, Shader& shadowCubeMapProgram, int shadowMapWidth, int shadowMapHeight);

    int renderShadow;

private:
    glm::vec3 reUseVec{0, 0, 0};
	unsigned int pointShadowMapFBO;
	unsigned int depthCubemap;
};


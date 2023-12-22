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

	void init(unsigned int width = 2048, unsigned int height = 2048);

    void prepareRender(Camera& camera, Light& light, float resoWidth, float resoHeight);
    void unprepareRender(int width, int height);

    void updateShader(Shader& shader, Light& light);

    void Delete();

    unsigned int depthMap;

    float near_plane = -200, far_plane = 20;
    float area = 200;

	Shader shadowMapShader{"../../Lomus/Shader/shaders/shadowMap.vert", "../../Lomus/Shader/shaders/shadowMap.frag"};
private:
    unsigned int depthMapFBO;
    vector<glm::vec4> corners;
	unsigned int shadowMapWidth;
	unsigned int shadowMapHeight;
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;



	

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


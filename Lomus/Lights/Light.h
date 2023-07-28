#pragma once
#include "shadowMap.h"
#include "../Shader/ShaderClass.h"
#include "../Renderer/Camera.h"



class Light
{
public:

	glm::vec4 lightColor;
	glm::vec3 lightPos;
	glm::mat4 lightModel;
	glm::vec3 lightDirection;
	float lightInten = 1.0f;

	void Init(glm::vec3 LightPos, glm::vec3 LightDirection, glm::vec4 LightColor, float lightInten, Shader shaderProgram);
	void PrepareRender(bool castShadow);
	void UnprepareRender(bool castShadow, float windowWidth, float windowHeight, Shader defaultShader);

	void Delete(bool castedShadow);
	void InitShadow(float resolutionWidth, float resolutionHeight);

	

	//Some nice Utils methods
	void setPosition(float x, float y, float z);
	void increasePosition(float x, float y, float z);
	glm::vec3 getPosition();

	void setDirection(float x, float y, float z);
	glm::vec3 getDirection();

	void setColor(float r, float g, float b, float a);
	glm::vec4 getColor();


	shadowMap myShadow;
};


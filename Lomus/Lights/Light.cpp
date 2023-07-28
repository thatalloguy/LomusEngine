#include "Light.h"

//Life time functions
void Light::Init(glm::vec3 LightPos, glm::vec3 LightDirection, glm::vec4 LightColor, float lightInten, Shader shaderProgram) {
	Light::lightPos = LightPos;
	Light::lightDirection = LightDirection;
	Light::lightColor = LightColor;

	Light::lightModel = glm::translate(Light::lightModel, lightPos);
	Light::lightInten = lightInten;

	//Boot them light stuff into le shader

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightInten"), lightInten);
}

void Light::PrepareRender(bool castShadow)
{
	if (castShadow) {
		myShadow.prepareRender();
	}
}

void Light::UnprepareRender(bool castShadow, float windowWidth, float windowHeight, Shader defaultShader)
{
	
	if (castShadow) {
		myShadow.setLight(lightPos, lightDirection);

		myShadow.unprepareRender(windowWidth, windowHeight);

		defaultShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(myShadow.lightProjection));
		glUniform3f(glGetUniformLocation(defaultShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		// Bind the Shadow Map
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, myShadow.my_shadowMap);
		glUniform1i(glGetUniformLocation(defaultShader.ID, "shadowMap"), 2);
		
	}
	else {
		defaultShader.Activate();
		glUniform3f(glGetUniformLocation(defaultShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	}
	
	
	glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void Light::Delete(bool castedShadow)
{
	if (castedShadow) {
		myShadow.Delete();
	}
}

void Light::InitShadow(float resolutionWidth, float resolutionHeight)
{
	myShadow.init(resolutionWidth, resolutionHeight);
}




////////////////-------Utils functions--------////////////////////



void Light::setPosition(float x, float y, float z)
{
	lightPos.x = x;
	lightPos.y = y;
	lightPos.z = z;
}

glm::vec3 Light::getPosition()
{
	return Light::lightPos;
}


glm::vec3 Light::getDirection()
{
	return Light::lightDirection;
}

void Light::setDirection(float x, float y, float z)
{
	lightDirection.x = x;
	lightDirection.y = y;
	lightDirection.z = z;
}


void Light::setColor(float r, float g, float b, float a) {
	lightColor.r = r;
	lightColor.g = g;
	lightColor.b = b;
	lightColor.a = a;
}

glm::vec4 Light::getColor() {
	return Light::lightColor;
}

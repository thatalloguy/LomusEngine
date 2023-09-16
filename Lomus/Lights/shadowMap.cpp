#include "shadowMap.h"


void shadowMap::init(unsigned int width, unsigned int height)
{
	shadowMapHeight = height;
	shadowMapWidth = width;

	glGenFramebuffers(1, &shadowMapFBO);

	glGenTextures(1, &my_shadowMap);
	glBindTexture(GL_TEXTURE_2D, my_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


	

	// Prevents darkness outside the frustrum
	float clampColor[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, my_shadowMap, 0);
	unsigned int fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << fboStatus << std::endl;

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	

}

void shadowMap::setLight(glm::vec3& lightPos, glm::vec3& lightDirection)
{
	float near_plane = 1.0f, far_plane = 1000.5f;
	orthgonalProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	glm::mat4 matrix = glm::mat4(1.0f);

	lightView = glm::lookAt(lightPos, lightDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	lightProjection = orthgonalProjection * lightView;
	initShader();
}

void shadowMap::prepareRender()
{
	//glCullFace(GL_BACK);
	
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	shadowMapShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapShader.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
}

void shadowMap::unprepareRender(float screenWidth, float screenHeight)
{
	//After scene done rendering
	//glCullFace(GL_FRONT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void shadowMap::Delete()
{
	glDeleteFramebuffers(1, &shadowMapFBO);
	shadowMapShader.Delete();
}

void shadowMap::renderShadowBuffer(int width, int height)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, shadowMapFBO);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void shadowMap::initShader()
{
	shadowMapShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapShader.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
}

void shadowMap::updateShader(Shader& shader) {

}




///CUBE MAP SHADOWS 
//-----------------

void cubeShadowMap::Init( int shadowMapWidth, int shadowMapHeight, float farPlane, glm::vec3& lightPos, Shader& cubeMapShadowShader) {

	glGenFramebuffers(1, &pointShadowMapFBO);
	
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

	updateShadowMap(farPlane, lightPos, cubeMapShadowShader, shadowMapWidth, shadowMapHeight);
}

void cubeShadowMap::RenderPhaseBegin(int shadowMapWidth, int shadowMapHeight)
{
	glBindFramebuffer(GL_FRAMEBUFFER, pointShadowMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
}

void cubeShadowMap::RenderPhaseEnd(float windowWidth, float windowHeight)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, windowWidth, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cubeShadowMap::UpdateShader(Shader& DefaultShader, float farPlane, glm::vec3& lightPos)
{

	DefaultShader.Activate();

	glUniform1f(glGetUniformLocation(DefaultShader.ID, "farPlane"), farPlane);

	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	glUniform1i(glGetUniformLocation(DefaultShader.ID, "shadowCubeMap"), 2);
    glUniform1i(glGetUniformLocation(DefaultShader.ID, "castShadow"), renderShadow);
	glUniform3f(glGetUniformLocation(DefaultShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
}

void cubeShadowMap::updateShadowMap(float farPlane, glm::vec3& lightPos, Shader& shadowCubeMapProgram, int shadowMapWidth, int shadowMapHeight)
{
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)shadowMapWidth / shadowMapHeight, 0.1f, farPlane);
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

}

void cubeShadowMap::Delete()
{
	glDeleteFramebuffers(1, &pointShadowMapFBO);
}

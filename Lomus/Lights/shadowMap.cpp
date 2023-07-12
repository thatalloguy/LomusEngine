#include "shadowMap.h"


shadowMap::shadowMap(unsigned int width, unsigned int height)
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

void shadowMap::setLight(glm::vec3 lightPos)
{
	float near_plane = 1.0f, far_plane = 7.5f;
	orthgonalProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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

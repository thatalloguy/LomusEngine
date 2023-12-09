
#include "shadowMap.h"



///CUBE MAP SHADOWS 
//-----------------

void cubeShadowMap::Init( int shadowMapWidth, int shadowMapHeight, float farPlane,  Light& shadowCaster, Shader& cubeMapShadowShader) {

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

	updateShadowMap(farPlane, shadowCaster, cubeMapShadowShader, shadowMapWidth, shadowMapHeight);
}

void cubeShadowMap::RenderPhaseBegin(int shadowMapWidth, int shadowMapHeight)
{
	glBindFramebuffer(GL_FRAMEBUFFER, pointShadowMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
}

void cubeShadowMap::RenderPhaseEnd(float windowWidth, float windowHeight)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void cubeShadowMap::UpdateShader(Shader& DefaultShader, float farPlane,  Light& shadowCaster)
{

	DefaultShader.Activate();

	glUniform1f(glGetUniformLocation(DefaultShader.ID, "farPlane"), farPlane);

	glActiveTexture(GL_TEXTURE0 + 4);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	glUniform1i(glGetUniformLocation(DefaultShader.ID, "shadowCubeMap"), 4);
    glUniform1i(glGetUniformLocation(DefaultShader.ID, "castShadow"), renderShadow);
	glUniform3f(glGetUniformLocation(DefaultShader.ID, "lightPos"), shadowCaster.lightPosition_x, shadowCaster.lightPosition_y, shadowCaster.lightPosition_z);
}

void cubeShadowMap::updateShadowMap(float farPlane,  Light& shadowCaster, Shader& shadowCubeMapProgram, int shadowMapWidth, int shadowMapHeight)
{
    reUseVec.x = shadowCaster.lightPosition_x;
    reUseVec.y = shadowCaster.lightPosition_y;
    reUseVec.z = shadowCaster.lightPosition_z;
    shadowCubeMapProgram.Activate();
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)shadowMapWidth / shadowMapHeight, 0.1f, farPlane);
	glm::mat4 shadowTransforms[] =
	{
	shadowProj * glm::lookAt(reUseVec, reUseVec + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
	shadowProj * glm::lookAt(reUseVec, reUseVec + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)),
	shadowProj * glm::lookAt(reUseVec, reUseVec + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
	shadowProj * glm::lookAt(reUseVec, reUseVec + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)),
	shadowProj * glm::lookAt(reUseVec, reUseVec + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)),
	shadowProj * glm::lookAt(reUseVec, reUseVec + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0))
	};
	// Export all matrices to shader
	shadowCubeMapProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[0]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[0]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[1]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[1]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[2]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[2]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[3]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[3]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[4]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[4]));
	glUniformMatrix4fv(glGetUniformLocation(shadowCubeMapProgram.ID, "shadowMatrices[5]"), 1, GL_FALSE, glm::value_ptr(shadowTransforms[5]));
	glUniform3f(glGetUniformLocation(shadowCubeMapProgram.ID, "lightPos"), shadowCaster.lightPosition_x, shadowCaster.lightPosition_y, shadowCaster.lightPosition_z);
	glUniform1f(glGetUniformLocation(shadowCubeMapProgram.ID, "farPlane"), farPlane);

}

void cubeShadowMap::Delete()
{
	glDeleteFramebuffers(1, &pointShadowMapFBO);
}

std::vector<glm::vec4> getFrustumCornersWorldSpace(const glm::mat4& proj, const glm::mat4& view)
{
    const auto inv = glm::inverse(view * proj);

    std::vector<glm::vec4> frustumCorners;
    for (unsigned int x = 0; x < 2; ++x)
    {
        for (unsigned int y = 0; y < 2; ++y)
        {
            for (unsigned int z = 0; z < 2; ++z)
            {
                const glm::vec4 pt =
                        inv * glm::vec4(
                                2.0f * x - 1.0f,
                                2.0f * y - 1.0f,
                                2.0f * z - 1.0f,
                                1.0f);
                frustumCorners.push_back(pt / pt.w);
            }
        }
    }

    return frustumCorners;
}

/// NORMAL SHADOWS

void ShadowMap::init(unsigned int width, unsigned int height) {
    shadowMapWidth = width;
    shadowMapHeight = height;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void ShadowMap::unprepareRender(int width, int height) {
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // reset viewport
    glViewport(0, 0, width, height);
}

void ShadowMap::prepareRender(Camera& camera, Light& light, float resoWidth, float resoHeight) {
    glViewport(0, 0, resoWidth, resoHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    camera.updateMatrix(45.0f, 0.1f, 500.0f, resoWidth, resoHeight);
    corners = getFrustumCornersWorldSpace(camera.view, camera.projection);
    glm::vec3 center = glm::vec3(0, 0, 0);
    for (const auto& v : corners)
    {
        center += glm::vec3(v);
    }
    center /= corners.size();

    const auto lightView = glm::lookAt(
            center + glm::normalize(glm::vec3(light.lightAngle[0],light.lightAngle[1],light.lightAngle[2])),
            center,
            glm::vec3(0.0f, 1.0f, 0.0f)
    );
    lightProjection = glm::ortho(-area, area, -area, area, near_plane, far_plane);
    lightSpaceMatrix = lightProjection * lightView;



    // render scene from light's point of view
    shadowMapShader.Activate();
    shadowMapShader.setMat4Uniform("lightProjection", lightSpaceMatrix);
    glCullFace(GL_FRONT);
}

void ShadowMap::updateShader(Shader &shader, Light& light) {
    shader.Activate();
    shader.setVec3Uniform("lightPos", light.lightPosition_x, light.lightPosition_y, light.lightPosition_z);
    shader.setMat4Uniform("lightProjection", lightSpaceMatrix);

    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    shader.setIntUniform("shadowMap", 4);
}

void ShadowMap::Delete() {
    glDeleteTextures(1, &depthMap);
    glDeleteFramebuffers(1, &depthMapFBO);
    shadowMapShader.Delete();
}
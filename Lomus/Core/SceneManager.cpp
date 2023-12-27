#include "SceneManager.h"
#include <spdlog/spdlog.h>

SceneManager::SceneManager() {

}

SceneManager::~SceneManager()
{
	Delete();
}

void SceneManager::createNewScene(std::string name)
{
	auto newScene = std::make_shared<Scene>(Scene{});
	newScene->name = name;
	newScene->world = common.createPhysicsWorld();
	scenes.emplace(name, newScene);

}

void SceneManager::addGameObject(GameObject& gameObject)
{
    gameObject.id = idCounter;
    auto newGameObject = std::make_shared<GameObject>(gameObject);
	currentScene->gameObjects.emplace(idCounter, newGameObject);
    newGameObject->id = idCounter;
    idCounter++;
}


void SceneManager::removeGameObject(std::shared_ptr<GameObject> gameObject) {
    spdlog::info("Removing gameObject " + gameObject->name + " | ID: " + std::to_string(gameObject->id).c_str());
    auto poorGameObject = currentScene->gameObjects.at(gameObject->id);
    currentScene->gameObjects.erase(poorGameObject->id);
}



void SceneManager::setCurrentScene(std::string name)
{

	currentScene = scenes.at(name);
	isItFirstScene = false;
}

void SceneManager::deleteScene(std::string name)
{
	scenes.erase(name);
}

std::shared_ptr<Scene> SceneManager::getCurrentScene()
{
	return SceneManager::currentScene;
}

std::shared_ptr<GameObject> SceneManager::getGameobject(int id)
{
    auto go = currentScene->gameObjects.at(id);
    return go;
}

void SceneManager::renderCurrentScene(Shader& shader, Lomus::Camera& camera)
{
    // Load IBL maps
    shader.Activate();
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    shader.setIntUniform("irradianceMap", 7);

    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    shader.setIntUniform("prefilterMap", 8);

    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    shader.setIntUniform("brdfLUT", 9);


    if (!shader.isBroken) {
        for (auto& gameObject : currentScene->gameObjects) {
            gameObject.second->castsShadow = false;
            gameObject.second->Draw(shader, camera);

            if (!gameObject.second->mBillboard.amEmpty) {
                gameObject.second->mBillboard.position = -gameObject.second->position;
                gameObject.second->mBillboard.scale = gameObject.second->scale;
                gameObject.second->mBillboard.Render(camera, billboardShader);
            }

        }
    }


    renderHDRMap(camera);

}


void SceneManager::Delete()
{
    if (!hasDeleted) {
        hasDeleted = true;
        auto it = scenes.begin();

        while (it != scenes.end()) {
            for (auto& gameObject : it->second->gameObjects) {
                it->second->world->destroyRigidBody(gameObject.second->mRigidBody);
                gameObject.second->Delete();
                gameObject.second->DeletePhysicsData(common);

                //delete gameObject.second;
            }

            common.destroyPhysicsWorld(it->second->world);
            //delete it->second;
            it++;
        }


        brdfShader.Delete();
        irradianceShader.Delete();
        prefilterShader.Delete();
        cubeMapShader.Delete();
        toCubeMapShader.Delete();
    }

}



void SceneManager::createRigidBody(int GameObjectId, BodyType type)
{
    auto currentGameObject = SceneManager::getGameobject(GameObjectId);
	currentGameObject->Pvec3.x =  currentGameObject->position.x;
	currentGameObject->Pvec3.y = -currentGameObject->position.y;
	currentGameObject->Pvec3.z =  currentGameObject->position.z;
    currentGameObject->Pquat.x =  currentGameObject->rotation.x;
	currentGameObject->Pquat.y =  currentGameObject->rotation.y;
	currentGameObject->Pquat.z =  currentGameObject->rotation.z;
	currentGameObject->Pquat.w =  currentGameObject->rotation.w;

    currentGameObject->Pquat.inverse();
	currentGameObject->transform = Transform(currentGameObject->Pvec3, currentGameObject->Pquat);
	currentGameObject->mRigidBody = currentScene->world->createRigidBody(currentGameObject->transform);
	currentGameObject->mRigidBody->setType(type);
	currentGameObject->isPhysical = true;

}

void SceneManager::addCollisionBoxShape(int GameObjectId, Vector3 halfExtents, Transform& Offset)
{
    auto currentGameObject = SceneManager::getGameobject(GameObjectId);

    BoxShape* shape = common.createBoxShape(halfExtents);
	currentGameObject->colliderInfo.collider = currentGameObject->mRigidBody->addCollider(shape, Offset);

    currentGameObject->colliderInfo.type = Lomus::ColliderShapeType::Box;
    currentGameObject->colliderInfo.boxShape = shape;
    currentGameObject->colliderInfo.hasShape = true;
}
void SceneManager::addCollisionSphereShape(int GameObjectId, float radius, Transform& Offset) {
    auto currentGameObject = SceneManager::getGameobject(GameObjectId);

    SphereShape* shape = common.createSphereShape(radius);
    currentGameObject->colliderInfo.collider = currentGameObject->mRigidBody->addCollider(shape, Offset);

    currentGameObject->colliderInfo.type = Lomus::ColliderShapeType::Sphere;
    currentGameObject->colliderInfo.sphereShape = shape;
    currentGameObject->colliderInfo.hasShape = true;
}

void SceneManager::addCollisionCapsuleShape(int GameObjectId, float radius, float height, Transform& Offset) {
    auto currentGameObject = SceneManager::getGameobject(GameObjectId);
    CapsuleShape* shape = common.createCapsuleShape(radius, height);
    currentGameObject->colliderInfo.collider = currentGameObject->mRigidBody->addCollider(shape, Offset);

    currentGameObject->colliderInfo.type = Lomus::ColliderShapeType::Capsule;
    currentGameObject->colliderInfo.capsuleShape = shape;
    currentGameObject->colliderInfo.hasShape = true;
}

void SceneManager::UpdatePhysicsWorld(float timeStamp) {
    refreshRigdBodiesTransforms();
    currentScene->world->update(timeStamp);
    for (auto &gameObject: currentScene->gameObjects) {

        if (gameObject.second->isPhysical) {

            gameObject.second->position.x = gameObject.second->mRigidBody->getTransform().getPosition().x;
            gameObject.second->position.y = -gameObject.second->mRigidBody->getTransform().getPosition().y;
            gameObject.second->position.z = gameObject.second->mRigidBody->getTransform().getPosition().z;

            tempQuat.x = gameObject.second->mRigidBody->getTransform().getOrientation().x;
            tempQuat.y = gameObject.second->mRigidBody->getTransform().getOrientation().y;
            tempQuat.z = gameObject.second->mRigidBody->getTransform().getOrientation().z;
            tempQuat.w = gameObject.second->mRigidBody->getTransform().getOrientation().w;

            tempQuat.inverse();

            gameObject.second->rotation.x = tempQuat.x;
            gameObject.second->rotation.y = tempQuat.y;
            gameObject.second->rotation.z = tempQuat.z;
            gameObject.second->rotation.w = tempQuat.w;

        }
    }
}
void SceneManager::refreshRigdBodiesTransforms() {

    for (auto &gameObject : currentScene->gameObjects) {
        if (gameObject.second->isPhysical) {
            gameObject.second->transform.setPosition(reactphysics3d::Vector3(gameObject.second->position.x,-gameObject.second->position.y,gameObject.second->position.z));

            gameObject.second->Pquat.x =  gameObject.second->rotation.x;
            gameObject.second->Pquat.y =  gameObject.second->rotation.y;
            gameObject.second->Pquat.z =  gameObject.second->rotation.z;
            gameObject.second->Pquat.w =  gameObject.second->rotation.w;

            gameObject.second->Pquat.inverse();
            gameObject.second->transform.setOrientation(gameObject.second->Pquat);
            gameObject.second->mRigidBody->setTransform(gameObject.second->transform);
        }
    }
}


void SceneManager::renderShadowMapScene(Shader &shader, Lomus::Camera &camera) {
    if (!shader.isBroken) {
        for (auto& gameObject : currentScene->gameObjects) {
            if (gameObject.second->castsShadow) {
                gameObject.second->castsShadow = true;
                gameObject.second->Draw(shader, camera);
            }
        }
    }
}

void SceneManager::initHDRmap(const char *path) {

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf(path, &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if (data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        spdlog::info("Lads we did it, we loaded an Hdr image \n");
    }
    else
    {
        spdlog::error("Failed to load HDR image.\n");
    }



    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);


    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        // note that we store each face with 16 bit floating point values
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
                     512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
            {
                    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
                    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
                    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
            };

// convert HDR equirectangular environment map to cubemap equivalent
    toCubeMapShader.Activate();
    toCubeMapShader.setIntUniform("equirectangularMap", 0);
    toCubeMapShader.setMat4Uniform("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        toCubeMapShader.setMat4Uniform("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube(); // renders a 1x1 cube
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);


    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    irradianceShader.Activate();
    irradianceShader.setIntUniform("environmentMap", 0);
    irradianceShader.setMat4Uniform("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        irradianceShader.setMat4Uniform("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------

    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minification filter to mip_linear
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    // ----------------------------------------------------------------------------------------------------
    prefilterShader.Activate();
    prefilterShader.setIntUniform("environmentMap", 0);
    prefilterShader.setMat4Uniform("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);

    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        unsigned int mipHeight = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        prefilterShader.setFloatUniform("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            prefilterShader.setMat4Uniform("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: generate a 2D LUT from the BRDF equations used.
    // ----------------------------------------------------

    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
    brdfShader.Activate();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void SceneManager::renderHDRMap(Lomus::Camera& camera) {
    cubeMapShader.Activate();
    cubeMapShader.setMat4Uniform("view", camera.view);
    cubeMapShader.setMat4Uniform("projection", camera.projection);
    glDepthFunc(GL_LEQUAL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    cubeMapShader.setIntUniform("skybox", 0);
    renderCube();
    glDepthFunc(GL_LESS);

}

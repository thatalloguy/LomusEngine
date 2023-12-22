#pragma once
#include <string>
#include "../Shader/ShaderClass.h"
#include <glm/glm.hpp>
#include <glm/vector_relational.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "../../Libs/Include/stb/std_image.h"

class Skybox
{
public:
	void Init();
	void Render(Lomus::Camera camera, float width, float height, float gamma);
	void Delete();
	
	void setSkyboxImageLocation(std::string path);
	

private:
	void loadTextures();



	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	unsigned int cubemapTexture;

	std::string path = "../../Lomus/Shader/shaders/Resources/Skyboxes/default/";
	std::string facesCubeMap[6] = {
		path + "right.png",
		path + "left.png",
		path + "top.png",
		path + "bottom.png",
		path + "front.png",
		path + "back.png"
	};

	//Shaderss

	Shader skyboxShader = Shader("../../Lomus/Shader/shaders/skybox.vert", "../../Lomus/Shader/shaders/skybox.frag");

};


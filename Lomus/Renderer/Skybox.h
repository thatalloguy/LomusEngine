#pragma once
#include <string>

class Skybox
{
public:
	void Init();
	void Render();
	void Delete();
	
	void setSkyboxImageLocation(std::string path);
	

private:
	void loadTextures();



	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	unsigned int cubemapTexture;

	std::string path = "../Shader/Resources/Skyboxes/default/";
	std::string facesCubeMap[6] = {
		path + "right.png",
		path + "left.png",
		path + "top.png",
		path + "bottom.png",
		path + "front.png",
		path + "back.png"
	};
};


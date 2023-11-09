#pragma once
#include "../Core/SceneManager.h"
#include "../Shader/ShaderClass.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

using namespace std;
using namespace  Lomus;

namespace Lomus {

    struct Light {
        float lightPosition_x;
        float lightPosition_y;
        float lightPosition_z;
        float lightColor_r;
        float lightColor_g;
        float lightColor_b;
        float lightColor_a;
        float lightInten;
        float lightAngle[3];
        int lightType;
        std::string name;
        bool castShadow;
    };

}
class LightManager
{
public:
	void Init();
    void InitScene(std::shared_ptr<Scene> scene);
	void Delete();
	void createNewLight(std::shared_ptr<Scene> scene, Light& light);


    std::shared_ptr<Light> getLight(std::shared_ptr<Scene> scene, std::string name);

	void updateShader(Shader& shader, std::shared_ptr<Scene> scene);

	void deleteLight(std::shared_ptr<Scene> scene, string& id);


    int placeId = 0;
    unordered_map<string, unordered_map<string, std::shared_ptr<Light>>> lightIdMap;
private:

	bool castShadow = false;
	Light currentShadowCaster;


	unsigned int lightBuffer;
};

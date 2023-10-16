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
    void InitScene(Scene& scene);
	void Delete();
	void createNewLight(Scene& scene, Light& light);


    Light& getLight(Scene& scene, std::string name);

	void updateShader(Shader& shader, Scene& scene);

	void deleteLight(Scene& scene, string& id);


    int placeId = 0;
    unordered_map<string, unordered_map<string, Light&>> lightIdMap;
private:

	bool castShadow = false;
	Light currentShadowCaster;


	unsigned int lightBuffer;
};

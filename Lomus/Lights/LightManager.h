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
        float lightPosition[3];
        float lightColor_r;
        float lightColor_g;
        float lightColor_b;
        float lightColor_a;
        float lightInten;
        float lightAngle[3];
        int lightType;
        std::string name;
    };

}
class LightManager
{
public:
	void Init();
    void InitScene(Scene& scene);
	void Delete();
	void createNewLight(Scene& scene, Light& light);

	glm::vec3 getLightPosition(Scene& scene, string& id);
	glm::vec4 getLightColor(Scene& scene, string& id);
	float     getLightInten(Scene& scene, string& id);
	
	void setLightPosition(Scene& scene, string id, glm::vec3& newPosition);
	void setLightColor(Scene& scene, string& id,    glm::vec4&    newColor);
	void setLightInten(Scene& scene, string& id,    float        newInten);

	void updateShader(Shader& shader, Scene& scene);

	void deleteLight(Scene& scene, string& id);

    Light lights[100];
    int placeId = 0;
private:
    unordered_map<string, unordered_map<string,int>> lightIdMap;
	bool castShadow = false;
	Light currentShadowCaster;


	unsigned int lightBuffer;
};

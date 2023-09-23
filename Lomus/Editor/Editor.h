#include "../../Thirdparty/imgui/imgui.h"
#include "../Core/SceneManager.h"
#include "../Lights/LightManager.h"
#include "../Core/Console.h"
#include "../Shader/ShaderClass.h"
#include <GLFW/glfw3.h>

namespace Lomus {


    enum EditorMode{debug,editor,release};

    class Editor {


    public:
        void Init(SceneManager& sceneManager);

        void Delete(SceneManager& sceneManager);

        void Render(SceneManager& sceneManager,LightManager& lightManager, GLFWwindow* window,Shader& shader,  Camera& camera, int windowWidth, int windowHeight, EditorMode mode);

        Console mConsole;

        int visible = 1;
    private:

        void renderDebugModeData(SceneManager& sceneManager,LightManager& lightManager,Shader& shader,  GLFWwindow* window,  Camera& camera, int windowWidth, int windowHeight);

        void initStlyle();
        bool togglePressed = false;


        // Debug editor stuff;
        float shadowSamples[1] = {8.0f};
        float baises[1] = {100.0f};
        float offset[1] = {20.7f};
        float a[1] = {0.0003f};
        float b[1]= {0.00002f};
        float ambient[1] = {0.20f};
        float sAmbient[1] = {1.0f};
        bool autoUpdate[1] ={false};
    };

}

#include "../../Thirdparty/imgui/imgui.h"
#include "../Core/SceneManager.h"
#include "../Lights/LightManager.h"
#include "../Core/Console.h"
#include <GLFW/glfw3.h>

namespace Lomus {


    enum EditorMode{debug,editor,release};

    class Editor {


    public:
        void Init(SceneManager& sceneManager);

        void Delete(SceneManager& sceneManager);

        void Render(SceneManager& sceneManager,LightManager& lightManager, GLFWwindow* window,  Camera& camera, int windowWidth, int windowHeight, EditorMode mode);

        Console mConsole;

    private:

        void renderDebugModeData(SceneManager& sceneManager,LightManager& lightManager,  GLFWwindow* window,  Camera& camera, int windowWidth, int windowHeight);

        void initStlyle();


    };

}

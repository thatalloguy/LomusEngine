#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../Thirdparty/imgui/imgui.h"
#include "../../Thirdparty/imgui/ImGuizmo.h"
#include "../../Thirdparty/imgui/IconsFontAwesome6.h"


#include "../Core/SceneManager.h"
#include "../Lights/LightManager.h"
#include "../Core/Console.h"
#include "../Shader/ShaderClass.h"
#include "ShaderEditor.h"

#include <GLFW/glfw3.h>
#include <glm/gtx/matrix_decompose.hpp>
#include "../Input/Keyboard.h"

namespace Lomus {


    enum EditorMode{debug,editor,shader};

    class Editor {


    public:

        enum EditorStyle{Clean,Unreal,Ocean,Space};
        Editor(GLFWwindow *window, EditorStyle style);

        void Delete(SceneManager& sceneManager);
        void prepareFrameBuffer();
        void unprepareFrameBuffer();
        void Delete();
        void Render(SceneManager& sceneManager, LightManager& lightManager, Camera& camera, EditorMode mode);
        void setShader(int i, Shader& shader);


        bool allowCameraInput();

        Console mConsole;
        int windowWidth[1] ={1280};
        int windowHeight[1] = {720};
        int visible = 1;
        unsigned int shadowTexture;

        float shadowArea[1] = {200};
        float shadowNearPlane[1] = {-200};
        float shadowFarPlane[1] = {20};
    private:

        void renderDebugModeData(SceneManager& sceneManager,LightManager& lightManager,Shader& shader, Shader& outlineShader,  GLFWwindow* window,  Camera& camera, int windowWidth, int windowHeight);
        void renderTheFullEditor(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);

        void renderSelectionPanel(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);
        void renderOtherPanel(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);

        void renderPropertiesPanel(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);
        void renderGameObjectProperties(GameObject& currentGameObject);
        void renderActiveScene(SceneManager& sceneManager);

        void createFBO(int width, int height);

        void resizeFrameBuffer(int newWidth, int newHeight);
        void manipulateGameObjectViaGizmo(GameObject& gameObject, Camera& camera);

        void handleInputs(Camera& camera);

        void handleShaderEditor();

        bool togglePressed = false;


        GLFWwindow* rawWindow;

        float oldWindowWidth = 0;
        float oldWindowHeight = 0;

        ImTextureID imTexID;
        unsigned int FBO;
        unsigned int texture_id;
        unsigned int RBO;

        unordered_map<int, Shader&> shaderList;

        // Debug editor stuff;
        float shadowSamples[1] = {8.0f};
        float baises[1] = {100.0f};
        float offset[1] = {20.7f};
        float a[1] = {0.0003f};
        float b[1]= {0.00002f};
        float ambient[1] = {0.20f};
        float sAmbient[1] = {1.0f};
        bool autoUpdate[1] ={false};
        int celLevel[1] = {5};
        bool useNM[1] = {false};
        float outlineThick[1] = {0.08};
        float outlineColor[4] = {1, 1, 1, 1};

        ImGuizmo::OPERATION currentGizmoState = ImGuizmo::OPERATION::TRANSLATE;

        enum EditorState{gameObject,Scene,Light,Script}; // What Type of object is the engine displaying / editing



        EditorState currentState;
        int currentId = -1;

        void initStlyle(EditorStyle style);

        ShaderEditor shaderEditor{};


    };

}

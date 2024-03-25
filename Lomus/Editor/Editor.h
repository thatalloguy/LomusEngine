#pragma  once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../Thirdparty/imgui/imgui.h"
#include "../../Thirdparty/imgui/ImGuizmo.h"
#include "../../Thirdparty/imgui/IconsFontAwesome6.h"
#include "../../Thirdparty/imgui/ImGuiFileBrowser.h"

#include "../../Thirdparty/ImGuiColorTextEdit/TextEditor.h"

#include "../Core/SceneManager.h"
#include "../Core/ProjectManager.h"
#include "../Core/Console.h"
#include "../Core/GameObject.h"
#include "Launcher.h"

#include "../Lights/LightManager.h"
#include "CodeEditor.h"
#include "../Shader/ShaderClass.h"

#include "../Input/Keyboard.h"
#include "../Utils/ToolBox.h"

#include <GLFW/glfw3.h>
#include <glm/gtx/matrix_decompose.hpp>
#include <spdlog/spdlog.h>




namespace Lomus {


    enum EditorMode{debug,editor,shader,launcher};

    struct ToggleButton{

        bool isActive = false;
        const char* hoverText = "A toggle button";
        ImVec4 activeColor = ImVec4(1, 1, 1, 1);
        ImVec4 passiveColor = ImVec4(1, 1, 1, 1);

        bool click= false;

        void Render(const char* defaultText, const char* activeText) {
            ImGuiStyle& style = ImGui::GetStyle();
            click= false;
            if (isActive) {

                style.Colors[ImGuiCol_Text] = activeColor;

                if (ImGui::Button(activeText, ImVec2(21, 20))) {
                    click = true;
                    isActive = false;
                }
                style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);

            } else{

                style.Colors[ImGuiCol_Text] = passiveColor;

                if (ImGui::Button(defaultText, ImVec2(21, 20))) {
                    click = true;
                    isActive = true;
                }

                style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
            }

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip(hoverText);
            }
        }


    };


    struct UIWindow{
        float x, y, width, height;
    };


    class Editor {


    public:

        enum EditorStyle{Clean,Unreal,Ocean,Space};
        Editor(GLFWwindow *window, EditorStyle style, SceneManager& sceneManager);

        void Delete(SceneManager& sceneManager);
        void prepareFrameBuffer();
        void unprepareFrameBuffer();
        void Delete();
        void Render(SceneManager& sceneManager, LightManager& lightManager, Camera& camera, EditorMode mode);
        void setShader(int i, Shader& shader);
        bool isWindowMinized();

        void renderDebugLightObjects(Camera& camera, Shader& billboardShader);

        bool allowCameraInput();

        bool doDebugRenderer() const {
          return debugRenderButton.isActive;
        };
        bool isGameRunning();

        Console mConsole;
        ProjectManager projectManager;
        int windowWidth[1] ={1280};
        int windowHeight[1] = {720};
        int visible = 1;
        unsigned int shadowTexture;

        float shadowArea[1] = {100};
        float shadowNearPlane[1] = {-50};
        float shadowFarPlane[1] = {25};

        LomusModelTypes::Billboard cameraBillboard;

        EditorMode getDesiredMode();


    private:

        struct EditorMouse {
            bool isDraggingTile = false;
            AssetData* selectedTile= nullptr;
        };
        EditorMouse editorMouse;

        struct movableObject {
            glm::vec3& position;
            glm::quat& rotation;
            glm::vec3& scale;
        };

        bool isFirstFrame = true;

        std::string lightImagePath = "../../Lomus/Resources/lightbulb.png";
        std::string cameraImagePath = "../../Lomus/Resources/camera.png";

        void renderDebugModeData(SceneManager& sceneManager,LightManager& lightManager,Shader& shader, Shader& outlineShader,  GLFWwindow* window,  Camera& camera, int windowWidth, int windowHeight);
        void renderTheFullEditor(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);
        void renderTitlebar(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);


        void renderSelectionPanel(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);
        void renderOtherPanel(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);
        void renderPropertiesPanel(Camera& camera, SceneManager& sceneManager, LightManager& lightManager);

        //Game Object
        void renderGameObjectProperties(std::shared_ptr<GameObject> currentGameObject, Camera& camera, SceneManager& sceneManager);
        void renderActiveScene(SceneManager& sceneManager);
        void renderModelComponent(Model& model);
        void renderRigidBodyComponent(reactphysics3d::RigidBody* rigidyBody, bool isPhysical, SceneManager& sceneManager, std::shared_ptr<GameObject> currentGameObject);
        void renderBoxColliderComponent(std::shared_ptr<GameObject> currentGameObject);
        void renderSphereColliderComponent(std::shared_ptr<GameObject> currentGameObject);
        void renderCapsuleColliderComponent(std::shared_ptr<GameObject> currentGameObject);

        void renderBillboardModelComponent(std::shared_ptr<GameObject> currentGameObject);

        void renderProjectCreationMenu();
        Lomus::ProjectData newProjectData;
        Lomus::Launcher mLauncher{projectManager};

        void createNewGameObject(SceneManager& sceneManager);

        void prepareGameRuntime(SceneManager& sceneManager);
        void reloadEditScene(SceneManager& sceneManager);

        static void dropCallback(GLFWwindow* window, int count, const char** paths);


        void renderAssetsTab();
        void refreshAssetsFolder();
        void renderAssetTile(AssetData& assetData);
        std::string currentViewDir = "/Assets/";

        std::vector<AssetData> fileAssets;

        void renderLightProperties(SceneManager& sm, LightManager& lm);
        void createNewLight(SceneManager& sm, LightManager& lm);

        void createFBO(int width, int height);

        void handleWindowResize();
        void resizeFrameBuffer(int newWidth, int newHeight);
        void manipulateObjectViaGizmo(movableObject& object, Camera& camera);

        void handleInputs(Camera& camera);


        bool togglePressed = false;
        bool selectingComponents = false;

        GLFWwindow* rawWindow;

        float oldWindowWidth = 0;
        float oldWindowHeight = 0;

        ImTextureID imTexID;
        unsigned int FBO;
        unsigned int texture_id;
        unsigned int RBO;

        unordered_map<int, Shader&> shaderList;

        // Debug editor stuff;
        float shadowSamples[1] = {1};
        float baises[1] = {0.05f};
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
        enum EditState {editing, playing, texteditor, launcher};
        bool isCreatingNewProject = false;

        std::shared_ptr<Lomus::Light> currentSelectedLight = nullptr;

        EditorState currentState;
        EditState currentSceneState = EditState::editing;
        int currentId = -1;

        void initStlyle(EditorStyle style);

        //CodeEditor shaderEditor{};
        TextEditor textEditor;
        TextEditor::ErrorMarkers errorMarkers;
        imgui_addons::ImGuiFileBrowser file_dialog;

        int errorline = 0;

        ToggleButton debugRenderButton;
        ToggleButton playButton;
        ToggleButton pauseButton;

        bool selectingCollider = false;
        std::vector<Lomus::backUpObject> sceneCache;

        //Game runtime stuff
        backUpObject createBackupOfGameObject(std::shared_ptr<GameObject> gameObject);
        void rollBackGameObject(std::shared_ptr<GameObject> gameObject, backUpObject rollBackData);

        std::unordered_map<std::shared_ptr<Lomus::Light>, LomusModelTypes::Billboard*> lightBillboards;

    protected:
        bool hasWindowResized = false;
        int lightCount = 0;

    };




}
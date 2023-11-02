#define IMGUI_DEFINE_MATH_OPERATORS
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

//Imgui
#include "Thirdparty/imgui/imgui_impl_glfw.h"
#include "Thirdparty/imgui/imgui_impl_opengl3.h"

#include <reactphysics3d/reactphysics3d.h>
#include "Libs/Include/stb/std_image.h"
#include <glm/gtc/random.hpp>

//Engine
#include "Lomus/Renderer/Texture.h"
#include "Lomus/Renderer/Camera.h"
#include "Lomus/Renderer/Skybox.h"

#include "Lomus/Lights/LightManager.h"
#include "Lomus/Lights/shadowMap.h"

#include "Lomus/Core/GameObject.h"
#include "Lomus/Core/SceneManager.h"
#include "Lomus/Core/Console.h"
#include "Lomus/Shader/ShaderClass.h"

#include "Lomus/Physics/DebugRenderer.h"
#include "Lomus/Physics/DebugVAO.h"

#include "Lomus/Editor/Editor.h"


using namespace Lomus;
int width;
int height;
unsigned int samples = 8;

float rectangleVertices[] =
        {
                //  Coords   // texCoords
                1.0f, -1.0f,  1.0f, 0.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                -1.0f,  1.0f,  0.0f, 1.0f,

                1.0f,  1.0f,  1.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                -1.0f,  1.0f,  0.0f, 1.0f
        };


static bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "Opengl error: (" << error << "); function: " << function << "; line: " << line << "; file: " << file << "\n";
        return false;

    }
    return true;

}

void mySillyFunction(std::vector<std::string> args, Camera& camera, SceneManager& sceneManager, Console &console) {
    std::string message = "[OUTPUT] Hello World!: " + args[0] + "\n";
    console.addConsoleLog(message.c_str());
}



int main() {
    //EDITOR VERSION


    //Window init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4);
    //const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int window_width = 1280;// mode->width;
    int window_height = 720;// mode->height;

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Lomus", NULL, NULL);


    //Now calculate the window viewport size thats 6 / 10 of the monitor size; - width
    width = window_width;// * 0.7;
    height = window_height;// * 0.55;

    if (window == NULL) {
        std::cout << "Failed to create glfw Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Render settings
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_MULTISAMPLE);



    // IMGUI

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontDefault();

    ImFontConfig config;
    config.MergeMode = true;
    config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    io.Fonts->AddFontFromFileTTF("../../Lomus/Resources/Font/forkawesome-webfont.ttf", 13.0f, &config, icon_ranges);
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");



    //Camera and init of shaders

    Shader shaderProgram("../../Lomus/Shader/shaders/default.vert", "../../Lomus/Shader/shaders/default.frag");
    Shader framebufferProgram("../../Lomus/Shader/shaders/framebuffer.vert", "../../Lomus/Shader/shaders/framebuffer.frag");
    framebufferProgram.Activate();
    glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);
    glUniform1f(glGetUniformLocation(framebufferProgram.ID, "gamma"), 2.2f);



    Camera camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 2.0f));

    //Scene

    SceneManager sceneManager;
    sceneManager.createNewScene("mainScene");
    sceneManager.setCurrentScene("mainScene");

    GameObject trees(glm::vec3(0, -5.0f, 0), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -1.0f, 1.0f), "Cube :)");
    trees.createModel("../../Resources/Model/testCube/testCube.gltf");

    GameObject ground(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(5.0f, -1.0f, 5.0f), "Sponza");

    ground.createModel("../../Resources/Model/testCube/testCube.gltf");


    sceneManager.addGameObject(trees);
    sceneManager.addGameObject(ground);



    Light sun = Light{
            0, 50, 0,
            1,1, 1, 1,
            1,
            {-0.2f, -1.0f, -0.3f},
            1,
            "Sun",
            true
    };

    LightManager lightManager;
    lightManager.InitScene(sceneManager.getCurrentScene());
    lightManager.createNewLight(sceneManager.getCurrentScene(), sun);
    float gamma = 1.5f;





    Skybox skybox;
    skybox.Init();


    //Shadow

    ShadowMap shadowMap;
    shadowMap.init();
    shadowMap.far_plane = 26.0f;
    shadowMap.near_plane = -52.0f;
    shadowMap.area = 102;
    //fps counter
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;


    sceneManager.doPhysics = false;
    //Physics
    sceneManager.createRigidBody(1, BodyType::DYNAMIC); // MONKEY

    Transform transform;
    sceneManager.addCollisionCapsuleShape(1, 1, 5, transform);



    Lomus::DebugRenderer lDebugRenderer(sceneManager.getCurrentScene()->world);



    bool showErrors = false;


    //Icon time
    int imgWidth, imgHeight;
    int channels;
    unsigned char* iconPixels = stbi_load("../../Lomus/Resources/LogoV2.jpg", &imgWidth, &imgHeight, &channels, 4);

    GLFWimage images[1];
    images[0].width = imgWidth;
    images[0].height = imgHeight;
    images[0].pixels = iconPixels;

    glfwSetWindowIcon(window, 1, images);



    /// EDITORRR
    Lomus::Editor editor(window, Lomus::Editor::Clean);
    editor.setShader(1, shaderProgram);

    std::string temp = "light1";

    Shader outline("../../Lomus/Shader/shaders/outline.vert", "../../Lomus/Shader/shaders/outline.frag");
    //load some shader stuff
    shaderProgram.Activate();
    shaderProgram.setFloatUniform("sBiases", 0.05f);
    shaderProgram.setFloatUniform("sampleSize", 1.0f);

    shaderProgram.setFloatUniform("lAmbient", 0.20f);

    glm::mat4 gridModel;
    editor.shadowTexture = shadowMap.depthMap;



    while (!glfwWindowShouldClose(window)) {

        // Error checking
        GLenum err;
        if ((err = glGetError()) != GL_NO_ERROR && showErrors)
        {

            std::cerr << "Opengl Error: " << err << " \n";
            //return -1; -- disabled so it wont crash everytime i get error :(
        }

        //Updating fps and Title
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0) {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string newTitle = "Lomus  | FPS: " + FPS;
            glfwSetWindowTitle(window, newTitle.c_str());
            prevTime = crntTime;
            counter = 0;


        }
        if (sceneManager.doPhysics) {
            sceneManager.UpdatePhysicsWorld(timeDiff);
        }

        // First update shadow projection
        shadowMap.area       = editor.shadowArea[0];
        shadowMap.near_plane = editor.shadowNearPlane[0];
        shadowMap.far_plane  = editor.shadowFarPlane[0];

        shadowMap.prepareRender(camera, sun, editor.windowWidth[0] * 0.745f, editor.windowHeight[0] * 0.745f);
        sceneManager.renderCurrentScene(shadowMap.shadowMapShader, camera);
        shadowMap.unprepareRender(editor.windowWidth[0], editor.windowHeight[0]);



        editor.prepareFrameBuffer();
        if (editor.allowCameraInput()) {
            camera.Inputs(window, (editor.windowWidth[0] * 0.75f) / 2, (editor.windowHeight[0] * 0.65f) / 2, timeDiff);
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        }

        lightManager.updateShader(shaderProgram, sceneManager.getCurrentScene());
        shadowMap.updateShader(shaderProgram, sun);

        shaderProgram.Activate();
        shaderProgram.setFloatUniform("sBaises", 0.05f);
        shaderProgram.setFloatUniform("sampleSize", 1.0f);

        shaderProgram.setFloatUniform("lAmbient", 0.20f);
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "castShadow"), 0.2);
        glUniform1i(glGetUniformLocation(shaderProgram.ID, "lightType"), 1);
        shaderProgram.setFloatUniform("gamma", gamma);

        sceneManager.renderCurrentScene(shaderProgram, camera);

        ///lDebugRenderer.Render(sceneManager.getCurrentScene().world, camera, sceneManager.doPhysics)
        skybox.Render(camera, width, height, gamma);



        editor.unprepareFrameBuffer();

        // Init imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();





        editor.Render(sceneManager, lightManager, camera, EditorMode::editor);



        //Imgui render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //swap :)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Clean Up Phase

    //modelTest.cleanUp();
    skybox.Delete();
    lightManager.Delete();
    shaderProgram.Delete();
    shadowMap.Delete();
    sceneManager.Delete();
    lDebugRenderer.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}




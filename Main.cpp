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

    //Load demo scene

    GameObject helmet(glm::vec3(0, -5.0f, 0), glm::quat(1.0f, 0.0, 0.0, 0.0), glm::vec3(3.0f, -3.0f, 3.0f), "Helmet :)");
    helmet.createModel("../../Resources/Model/Helmet/DamagedHelmet.gltf");
    helmet.model.mMaterial.roughnessAmplifier = 0.0f;
    GameObject ground(glm::vec3(0.0f, 5.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(10.0f, -1.0f, 10.0f), "Ground");
    ground.createModel("../../Resources/Model/testCube/testCube.gltf");

    GameObject emptyObject(glm::vec3(5.0f, 5.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), "Billboard");


    std::string billboardPath ="../../Lomus/Resources/lightbulb.png";
    emptyObject.createBillboardModel(billboardPath);


    sceneManager.addGameObject(helmet);
    sceneManager.addGameObject(ground);
    sceneManager.addGameObject(emptyObject);



    Light sun = Light{
            0, 10, 0,
            1,1, 1, 1,
            54,
            {-0.18f, -3.8f, -0.2f},
            1,
            "Sun",
            true
    };


    Light testLight = Light{
            0, 5, 0,
            1, 0, 1, 1,
            5,
            {0, 0, 0},
            2,
            "TestLight",
            false
    };

    LightManager lightManager;
    lightManager.InitScene(sceneManager.getCurrentScene());
    lightManager.createNewLight(sceneManager.getCurrentScene(), sun);
    //lightManager.createNewLight(sceneManager.getCurrentScene(), testLight); // use later
    float gamma = 1.5f;





    //Skybox skybox;
    //skybox.Init();


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


    sceneManager.doPhysics = true;
    //Physics
    sceneManager.createRigidBody(ground.id, BodyType::STATIC); // Ground
    sceneManager.createRigidBody(helmet.id, BodyType::DYNAMIC);

    Transform transform;
    Vector3 tvec3(ground.scale.x, (ground.scale.y * ground.scale.y),ground.scale.z);
    sceneManager.addCollisionBoxShape(ground.id, tvec3, transform);

    Transform transform1;
    sceneManager.addCollisionBoxShape(helmet.id, Vector3(2, 2, 2), transform1);



    Lomus::DRay lDebugRenderer(sceneManager.getCurrentScene()->world);



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
    Lomus::Editor editor(window, Lomus::Editor::Clean, sceneManager);
    editor.setShader(1, shaderProgram);

    std::string temp = "light1";

    //load some shader stuff
    shaderProgram.Activate();
    shaderProgram.setFloatUniform("sBiases", 0.05f);
    shaderProgram.setFloatUniform("sampleSize", 1.0f);

    shaderProgram.setFloatUniform("lAmbient", 0.20f);

    glm::mat4 gridModel;

    sceneManager.initHDRmap("../../Lomus/Shader/shaders/Resources/Skyboxes/hdr/default3.hdr");



    //Shadows bad

    unsigned int shadowMapFBO;
    glGenFramebuffers(1, &shadowMapFBO);

    unsigned int shadowMapWidth = 2048, shadowMapHeight = 2048;
    unsigned int shadowMapTexture;

    glGenTextures(1, &shadowMapTexture);
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float clampColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float near_plane = 0.1f;
    float far_plane = 500.0f;
    float area = 35.0f;

    glm::mat4 lightProjection;
    glm::mat4 lightView;

    glm::mat4 lightMatrix;
    editor.shadowTexture = shadowMapTexture;

    Shader mShadowShader("../../Lomus/Shader/shaders/shadowMap.vert", "../../Lomus/Shader/shaders/shadowMap.frag");

    ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;

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

        // First update shadow projection
        shadowMap.area       = editor.shadowArea[0];
        shadowMap.near_plane = editor.shadowNearPlane[0];
        shadowMap.far_plane  = editor.shadowFarPlane[0];

        lightProjection = glm::ortho(-area, area, -area, area, near_plane, far_plane);
        lightView = glm::lookAt(camera.Position, glm::vec3(0,0,0), glm::vec3(0, 1, 0));

        lightMatrix = lightProjection * lightView;




        shadowMap.prepareRender(camera, sun, editor.windowWidth[0], editor.windowHeight[0]);
        //sceneManager.renderCurrentScene(shadowMap.shadowMapShader, camera);
        shadowMap.unprepareRender(editor.windowWidth[0], editor.windowHeight[0]);

        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, shadowMapWidth, shadowMapHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        mShadowShader.Activate();
        mShadowShader.setMat4Uniform("lightProjection", lightMatrix);
        sceneManager.renderCurrentScene(mShadowShader, camera);


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, editor.windowWidth[0], editor.windowHeight[0]);


        editor.prepareFrameBuffer();
        if (editor.allowCameraInput()) {
            camera.Inputs(window, (editor.windowWidth[0] * 0.75f) / 2, (editor.windowHeight[0] * 0.65f) / 2, timeDiff);
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        }



        lightManager.updateShader(shaderProgram, sceneManager.getCurrentScene());
        shadowMap.updateShader(shaderProgram, sun);


        sceneManager.renderCurrentScene(shaderProgram, camera);
        if (editor.doDebugRenderer()) {
            sceneManager.refreshRigdBodiesTransforms();
            lDebugRenderer.Render(sceneManager.getCurrentScene()->world, camera, !editor.isGameRunning());
        }

        if (editor.isGameRunning()) {
            sceneManager.UpdatePhysicsWorld(timeDiff);

            // Running scripts goes here
        }




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

    //skybox.Delete();

    lightManager.Delete();

    shaderProgram.Delete();

    shadowMap.Delete();

    lDebugRenderer.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    sceneManager.Delete();
    return 0;
}

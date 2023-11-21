#define IMGUI_DEFINE_MATH_OPERATORS
#define NOMINMAX

#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>


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
#include "Lomus/Lights/Shadows/Shadows.hpp"


using namespace Lomus;
int width;
int height;
unsigned int samples = 8;

unsigned int lightFBO;
unsigned int lightDepthMaps;
constexpr unsigned int depthMapResolution = 4096;

float cameraFarPlane = 500.0f;
float cameraNearPlane = 0.1f;

std::vector<float> shadowCascadeLevels{ cameraFarPlane / 50.0f, cameraFarPlane / 25.0f, cameraFarPlane / 10.0f, cameraFarPlane / 2.0f };
int debugLayer = 0;

std::vector<glm::mat4> lightMatricesCache;
const glm::vec3 lightDir = glm::normalize(glm::vec3(20.0f, 50, 20.0f));

std::vector<glm::vec4> getTFrustumCornersWorldSpace(const glm::mat4& projview)
{
    const auto inv = glm::inverse(projview);

    std::vector<glm::vec4> frustumCorners;
    for (unsigned int x = 0; x < 2; ++x)
    {
        for (unsigned int y = 0; y < 2; ++y)
        {
            for (unsigned int z = 0; z < 2; ++z)
            {
                const glm::vec4 pt = inv * glm::vec4(2.0f * x - 1.0f, 2.0f * y - 1.0f, 2.0f * z - 1.0f, 1.0f);
                frustumCorners.push_back(pt / pt.w);
            }
        }
    }

    return frustumCorners;
}


std::vector<glm::vec4> getLightFrustumCornersWorldSpace(const glm::mat4& proj, const glm::mat4& view)
{
    return getTFrustumCornersWorldSpace(proj * view);
}

glm::mat4 getLightSpaceMatrix(Lomus::Camera& camera, const float nearPlane, const float farPlane,float width,float height)
{
    const auto proj = glm::perspective(
            45.0f, (float)width / (float)height, nearPlane,
            farPlane);
    const auto corners = getLightFrustumCornersWorldSpace(proj, camera.view);

    glm::vec3 center = glm::vec3(0, 0, 0);
    for (const auto& v : corners)
    {
        center += glm::vec3(v);
    }
    center /= corners.size();

    const auto lightView = glm::lookAt(center + lightDir, center, glm::vec3(0.0f, 1.0f, 0.0f));

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::lowest();
    for (const auto& v : corners)
    {
        const auto trf = lightView * v;
        minX = std::min(minX, trf.x);
        maxX = std::max(maxX, trf.x);
        minY = std::min(minY, trf.y);
        maxY = std::max(maxY, trf.y);
        minZ = std::min(minZ, trf.z);
        maxZ = std::max(maxZ, trf.z);
    }

    // Tune this parameter according to the scene
    constexpr float zMult = 10.0f;
    if (minZ < 0)
    {
        minZ *= zMult;
    }
    else
    {
        minZ /= zMult;
    }
    if (maxZ < 0)
    {
        maxZ /= zMult;
    }
    else
    {
        maxZ *= zMult;
    }

    const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
    return lightProjection * lightView;
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderDebugQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}


std::vector<glm::mat4> getLightSpaceMatrices(Lomus::Camera& camera, float width, float height)
{
    std::vector<glm::mat4> ret;
    for (size_t i = 0; i < shadowCascadeLevels.size() + 1; ++i)
    {
        if (i == 0)
        {
            ret.push_back(getLightSpaceMatrix(camera, cameraNearPlane, shadowCascadeLevels[i], width, height));
        }
        else if (i < shadowCascadeLevels.size())
        {
            ret.push_back(getLightSpaceMatrix(camera, shadowCascadeLevels[i - 1], shadowCascadeLevels[i], width, height));
        }
        else
        {
            ret.push_back(getLightSpaceMatrix(camera, shadowCascadeLevels[i - 1], cameraFarPlane, width, height));
        }
    }
    return ret;
}


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

    spdlog::info("Hello World!");

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

    GameObject trees(glm::vec3(0, -5.0f, 0), glm::quat(1.0f, 0.0, 0.0, 0.0), glm::vec3(3.0f, -3.0f, 3.0f), "Cube :)");
    trees.createModel("../../Resources/Model/testCube/testCube.gltf");

    GameObject ground(glm::vec3(0.0f, 5.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(30.0f, -1.0f, 30.0f), "Ground");

    ground.createModel("../../Resources/Model/testCube/testCube.gltf");


    sceneManager.addGameObject(trees);
    sceneManager.addGameObject(ground);



    Light sun = Light{
            0, 0, 0,
            1,1, 1, 1,
            54,
            {0.0f, 0.0f, 0.0f},
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

    //load some shader stuff
    shaderProgram.Activate();
    shaderProgram.setFloatUniform("sBiases", 0.05f);
    shaderProgram.setFloatUniform("sampleSize", 1.0f);

    shaderProgram.setFloatUniform("lAmbient", 0.20f);

    glm::mat4 gridModel;
    editor.shadowTexture = shadowMap.depthMap;

    sceneManager.initHDRmap("../../Lomus/Shader/shaders/Resources/Skyboxes/hdr/default3.hdr");


    // Cascaded Shadow Mapping
    Shader simpleDepthShader("../../Lomus/Shader/shaders/cascadedShadows.vert","../../Lomus/Shader/shaders/cascadedShadows.frag","../../Lomus/Shader/shaders/cascadedShadows.geom");
        

    glGenFramebuffers(1, &lightFBO);

    glGenTextures(1, &lightDepthMaps);
    glBindTexture(GL_TEXTURE_2D_ARRAY, lightDepthMaps);
    glTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, depthMapResolution, depthMapResolution, int(shadowCascadeLevels.size()) + 1,
            0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    constexpr float bordercolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, bordercolor);

    glBindFramebuffer(GL_FRAMEBUFFER, lightFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, lightDepthMaps, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
        throw 0;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure UBO
    // --------------------
    unsigned int matricesUBO;
    glGenBuffers(1, &matricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4) * 16, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, matricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    bool showQuad = true;

    Shader debugDepthQuad("../../Lomus/Shader/shaders/framebuffer.vert","../../Lomus/Shader/shaders/debugShadow.frag");



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

        //shadowMap.prepareRender(camera, sun, editor.windowWidth[0], editor.windowHeight[0]);
        //sceneManager.renderShadowMapScene(shadowMap.shadowMapShader, camera);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 0. UBO setup
        const auto lightMatrices = getLightSpaceMatrices(camera, editor.windowWidth[0],editor.windowHeight[0]);
        glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
        for (size_t i = 0; i < lightMatrices.size(); ++i)
        {
            glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(glm::mat4x4), sizeof(glm::mat4x4), &lightMatrices[i]);
        }
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
        // render scene from light's point of view
        simpleDepthShader.Activate();

        glBindFramebuffer(GL_FRAMEBUFFER, lightFBO);
        glViewport(0, 0, depthMapResolution, depthMapResolution);
        glClear(GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_FRONT);  // peter panning


        sceneManager.renderCurrentScene(simpleDepthShader, camera);


        glCullFace(GL_BACK);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, editor.windowWidth[0], editor.windowHeight[0]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





        editor.prepareFrameBuffer();
        if (editor.allowCameraInput()) {
            camera.Inputs(window, (editor.windowWidth[0] * 0.75f) / 2, (editor.windowHeight[0] * 0.65f) / 2, timeDiff);
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        }



        lightManager.updateShader(shaderProgram, sceneManager.getCurrentScene());
        shaderProgram.Activate();

        sceneManager.renderCurrentScene(shaderProgram, camera);
        //lDebugRenderer.Render(sceneManager.getCurrentScene().world, camera, sceneManager.doPhysics)
        //skybox.Render(camera, width, height, gamma);

        debugDepthQuad.Activate();
        debugDepthQuad.setIntUniform("layer", debugLayer);
        debugDepthQuad.setIntUniform("depthMap", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, lightDepthMaps);
        if (showQuad)
        {
            renderDebugQuad();
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
    shadowMap.Delete();
    //skybox.Delete();
    lightManager.Delete();
    shaderProgram.Delete();
    shadowMap.Delete();
    sceneManager.Delete();
    lDebugRenderer.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}




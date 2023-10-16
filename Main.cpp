
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include <reactphysics3d/reactphysics3d.h>
#include "Libs/Include/stb/std_image.h"

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

//Imgui
#include "Thirdparty/imgui/imgui.h"
#include "Thirdparty/imgui/imgui_impl_glfw.h"
#include "Thirdparty/imgui/imgui_impl_opengl3.h"

using namespace Lomus;
int width;
int height;



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
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");



    //Camera and init of shaders

    Shader shaderProgram("../../Lomus/Shader/shaders/default.vert", "../../Lomus/Shader/shaders/default.frag");


    shaderProgram.Activate();
    glUniform1f(glGetUniformLocation(shaderProgram.ID, "castShadow"), 0.2);
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "lightType"), 1);

    Camera camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 2.0f));

    //Scene

    SceneManager sceneManager;
    sceneManager.createNewScene("mainScene");
    sceneManager.setCurrentScene("mainScene");

    GameObject trees(glm::vec3(0, -20.0f, 0), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(9.0f, -4.0f, 7.0f), "Astronaut");
    trees.createModel("../../Resources/Model/Astronaut/astronaut.obj");
    GameObject ground(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(100.1f, -1.1f, 100.1f), "Sponza");

    ground.createModel("../../Resources/Model/tree_ground/scene.gltf");


    sceneManager.addGameObject(trees, 1);
    sceneManager.addGameObject(ground, 2);



    Light sun = Light{
            0, 50, 0,
            1,1, 1, 1,
            1,
            {1, 360, 1},
            1,
            "Sun"
    };

    LightManager lightManager;
    lightManager.InitScene(sceneManager.getCurrentScene());
    lightManager.createNewLight(sceneManager.getCurrentScene(), sun);
    float gamma = 1.5f;
    shaderProgram.setFloatUniform("gamma", gamma);



    Skybox skybox;
    skybox.Init();


    //Shadow - 11th time

    Shader shadowShader("../../Lomus/Shader/shaders/shadowMap.vert", "../../Lomus/Shader/shaders/shadowMap.frag");
    glm::vec3 tempVec = glm::vec3(sun.lightPosition_x, sun.lightPosition_y, sun.lightPosition_z);

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 1000.0f;

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



    Lomus::DebugRenderer lDebugRenderer(sceneManager.getCurrentScene().world);



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
    Lomus::Editor editor;
    editor.Init(sceneManager);


    std::string temp = "light1";

    Shader outline("../../Lomus/Shader/shaders/outline.vert", "../../Lomus/Shader/shaders/outline.frag");
    //load some shader stuff
    shaderProgram.Activate();
    shaderProgram.setFloatUniform("sSamples", 8.0f);
    shaderProgram.setFloatUniform("sBiases", 100.0f);
    shaderProgram.setFloatUniform("sOffset", 20.7f);
    shaderProgram.setFloatUniform("shadowAmbient", 1.0f);

    shaderProgram.setFloatUniform("lAmbient", 0.20f);



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
        tempVec.x = sun.lightPosition_x;
        tempVec.y = sun.lightPosition_y;
        tempVec.z = sun.lightPosition_z;




        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(tempVec, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        // render scene from light's point of view
        shadowShader.Activate();
        shadowShader.setMat4Uniform("lightProjection", lightSpaceMatrix);

        sceneManager.renderCurrentScene(shadowShader, camera);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, width, height);



        // Normal Render Loop

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (!editor.visible) {
            camera.Inputs(window);
        }

        camera.updateMatrix(45.0f, 0.1f, 1000.0f);
        lightManager.updateShader(shaderProgram, sceneManager.getCurrentScene());
        // Send the light matrix to the shader
        shaderProgram.Activate();
        shaderProgram.setVec3Uniform("lightPos", tempVec.x,tempVec.y,tempVec.z);
        shaderProgram.setMat4Uniform("lightProjection", lightSpaceMatrix);

        glActiveTexture(GL_TEXTURE0 + 4);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        shaderProgram.setIntUniform("shadowMap", 4);

        sceneManager.renderCurrentScene(shaderProgram, camera);

        ///lDebugRenderer.Render(sceneManager.getCurrentScene().world, camera, sceneManager.doPhysics);


        skybox.Render(camera, width, height, gamma);

        // Init imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();




        editor.Render(sceneManager, lightManager, window, shaderProgram, outline, camera, window_width, window_height, EditorMode::debug);
/////        std::cout << "astronaut:" << trees.position.x << " | " << trees.position.y << " | " << trees.position.z << "\n";
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
    sceneManager.Delete();
    lDebugRenderer.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
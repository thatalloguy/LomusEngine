// Other libraries 

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
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

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



    // IMGUI

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");



    //Camera and init of shaders

    Shader shaderProgram("../../Lomus/Shader/shaders/default.vert", "../../Lomus/Shader/shaders/default.frag");
    Shader shadowCubeMapProgram("../../Lomus/Shader/shaders/shadowCubeMap.vert", "../../Lomus/Shader/shaders/shadowCubeMap.frag", "../../Lomus/Shader/shaders/shadowCubeMap.geom");


    shaderProgram.Activate();
    glUniform1f(glGetUniformLocation(shaderProgram.ID, "castShadow"), 0.2);
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "lightType"), 1);

    Camera camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 2.0f));

    //Scene

    SceneManager sceneManager;
    sceneManager.createNewScene("mainScene");
    sceneManager.setCurrentScene("mainScene");

    GameObject trees(glm::vec3(0, 10.0f, 0), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -1.0f, 1.0f), "Astronaut");
    trees.createModel("../../Resources/Model/Astronaut/astronaut.obj");
    GameObject ground(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -1.0f, 1.0f), "ground");

    ground.createModel("../../Resources/Model/ground/ground.gltf");


    sceneManager.addGameObject(ground, 2);
    sceneManager.addGameObject(trees, 1);

    glm::vec3 lightPos = glm::vec3(0, 50, 0);

    LightManager lightManager;
    lightManager.Init();
    lightManager.createNewLight(sceneManager.getCurrentScene(), lightPos, glm::vec4(0.1f, 0.1f, 0.1f, 1), 10, "light1");
    float gamma = 1.5f;
    shaderProgram.setFloatUniform("gamma", gamma);



    Skybox skybox;
    skybox.Init();


    // Shadow map
    float farPlane = 10000.0f;
    unsigned int shadowMapWidth = 1024;
    unsigned int shadowMapHeight = 1024;

    cubeShadowMap cubeShadow{};
    cubeShadow.Init(1024, 1024, farPlane, lightPos, shadowCubeMapProgram);
    cubeShadow.renderShadow = 1; // true

    //fps counter
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;


/*
    Console console;
    console.init();
    console.addCommand("test", mySillyFunction);
*/



    sceneManager.doPhysics = false;
    //Physics
    sceneManager.createRigidBody(1, BodyType::DYNAMIC); // MONKEY

    Transform transform;
    sceneManager.addCollisionCapsuleShape(1, 1, 5, transform);



    Lomus::DebugRenderer lDebugRenderer(sceneManager.getCurrentScene().world);



    bool showErrors = false;


    // Ooga booga Icon time
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


    //load some shader stuff
    shaderProgram.Activate();
    shaderProgram.setFloatUniform("sSamples", 8.0f);
    shaderProgram.setFloatUniform("sBiases", 100.0f);
    shaderProgram.setFloatUniform("sOffset", 20.7f);
    shaderProgram.setFloatUniform("shadowAmbient", 1.0f);
    shaderProgram.setIntUniform("shadeLevels", 5);
    shaderProgram.setIntUniform("useNormalMap", 0);
    //shaderProgram.setFloatUniform("lA", 0.0003f);
    //shaderProgram.setFloatUniform("lB", 0.00002f);
    shaderProgram.setFloatUniform("lAmbient", 0.20f);


    // Outline stuff


    Shader outlineShader("../../Lomus/Shader/shaders/outline.vert","../../Lomus/Shader/shaders/outline.frag");
    editor.setShader(1, outlineShader);


    outlineShader.Activate();
    outlineShader.setVec4Uniform("color", 1, 1, 1, 1);
    outlineShader.setFloatUniform("thickness", 0.08f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


    while (!glfwWindowShouldClose(window)) {

        lightPos = lightManager.getLightPosition(sceneManager.getCurrentScene(), temp);
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
        //lightPos.y += 1;
        // lightManager.setLightPosition(sceneManager.getCurrentScene(), reString, lightPos);

        cubeShadow.updateShadowMap(10000, lightPos, shadowCubeMapProgram, 1024, 1024);
        cubeShadow.RenderPhaseBegin(shadowMapWidth, shadowMapHeight);

        // Draw scene for shadow map
        sceneManager.renderCurrentScene(shadowCubeMapProgram, camera);

        cubeShadow.RenderPhaseEnd(width, height);
        glClearColor(0.2, 0.7, 0.8, 1);


        // Normal Render Loop
        if (!editor.visible) {
            camera.Inputs(window);
        }

        camera.updateMatrix(45.0f, 0.1f, 1000.0f);
        lightManager.updateShader(shaderProgram, sceneManager.getCurrentScene());

        cubeShadow.UpdateShader(shaderProgram, farPlane, lightPos);


        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        shaderProgram.Activate();
        sceneManager.renderCurrentScene(shaderProgram, camera);
        shaderProgram.Deactivate();



        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);


        outlineShader.Activate();
        sceneManager.renderCurrentScene(outlineShader, camera);
        outlineShader.Deactivate();

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        ///lDebugRenderer.Render(sceneManager.getCurrentScene().world, camera, sceneManager.doPhysics);


        //skybox.Render(camera, width, height, gamma);

        // Init imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();




        editor.Render(sceneManager, lightManager, window, shaderProgram, outlineShader, camera, window_width, window_height, EditorMode::debug);

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
    shadowCubeMapProgram.Delete();
    sceneManager.Delete();
    lDebugRenderer.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    shadowCubeMapProgram.Delete();
    return 0;
}

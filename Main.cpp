// Other libraries 
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vector_relational.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include <reactphysics3d/reactphysics3d.h>
#include "Libs/Include/stb/std_image.h"

//Engine
#include "Lomus/Renderer/Texture.h"
#include "Lomus/Renderer/Camera.h"
#include "Lomus/Renderer/Mesh.h"
#include "Lomus/Renderer/Model.h"
#include "Lomus/Renderer/Skybox.h"

#include "Lomus/Lights/LightManager.h"
#include "Lomus/Lights/shadowMap.h"

#include "Lomus/Core/GameObject.h"
#include "Lomus/Core/SceneManager.h"
#include "Lomus/Core/Console.h"
#include "Lomus/Shader/ShaderClass.h"

//Imgui
#include "Thirdparty/imgui/imgui.h"
#include "Thirdparty/imgui/imgui_impl_glfw.h"
#include "Thirdparty/imgui/imgui_impl_opengl3.h" 

const unsigned int width = 1280;
const unsigned int height = 720;

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
	

	//Window init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Lomus", NULL, NULL);
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

	Shader shaderProgram("../../../Lomus/Shader/shaders/default.vert", "../../../Lomus/Shader/shaders/default.frag");
	Shader shadowCubeMapProgram("../../../Lomus/Shader/shaders/shadowCubeMap.vert", "../../../Lomus/Shader/shaders/shadowCubeMap.frag", "../../../Lomus/Shader/shaders/shadowCubeMap.geom");


	shaderProgram.Activate();
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "castShadow"), 0.5f);
	glUniform1i(glGetUniformLocation(shaderProgram.ID, "lightType"), 1);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Scene

	SceneManager sceneManager;
	sceneManager.createNewScene("mainScene");
	sceneManager.setCurrentScene("mainScene");

	GameObject trees(glm::vec3(5.0f, 10.0f, 5.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -1.0f, 1.0f), "kenku");
	trees.createModel("../../../Resources/Model/monkey/scene.gltf");
	GameObject ground(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -1.0f, 1.0f), "bob");
	ground.createModel("../../../Resources/Model/ground/scene.gltf" );
	sceneManager.addGameObject(ground, 0);
	sceneManager.addGameObject(trees, 1);


	LightManager lightManager;
	lightManager.Init();
	lightManager.createNewLight(sceneManager.getCurrentScene(), glm::vec3(0, 50, 0), glm::vec4(0.1f, 0.1f, 0.1f, 1), 50, "light1");
	

	Skybox skybox;
	skybox.Init();


	// Shadow map
	float farPlane = 100.0f;
	unsigned int shadowMapWidth = 2048;
	unsigned int shadowMapHeight = 2048;
	
	cubeShadowMap cubeShadow;
	glm::vec3 lightPos = glm::vec3(0, 5, 0);
	cubeShadow.Init(shadowMapWidth, shadowMapHeight, farPlane, lightPos, shadowCubeMapProgram);


	//fps counter
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	bool isfirstFrame = true;

	Console console;
	console.init();
	console.addCommand("test", mySillyFunction);

	sceneManager.doPhysics = false;
	//Physics
	sceneManager.createRigidBody(1, BodyType::DYNAMIC);
	Transform transform;
	sceneManager.addCollisionBoxShape(1, Vector3(1, 1, 1), transform);

	while (!glfwWindowShouldClose(window)) {

		// Error checking
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
		{
			
			std::cout << "Error: " << err << " \n";
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
		

		cubeShadow.RenderPhaseBegin(shadowMapWidth, shadowMapHeight);

		// Draw scene for shadow map
		sceneManager.renderCurrentScene(shadowCubeMapProgram, camera);
		
		cubeShadow.RenderPhaseEnd(width, height);


		// Normal Render Loop
		if (console.mode == console.MODE_TOGGLE) {
			camera.Inputs(window);
		}

		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		lightManager.updateShader(shaderProgram, sceneManager.getCurrentScene());
		
		cubeShadow.UpdateShader(shaderProgram, farPlane, lightPos);
		
		sceneManager.renderCurrentScene(shaderProgram, camera);
		skybox.Render(camera, width, height);
		
		// Init imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		console.renderConsole(window, 400, 500, camera, sceneManager);


		//Imgui render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//swap :)
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	
	// Clean Up Phase
	skybox.Delete();
	lightManager.Delete();
	shaderProgram.Delete();
	shadowCubeMapProgram.Delete();
	sceneManager.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	shadowCubeMapProgram.Delete();
	return 0;
}
#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <glfw/glfw3.h>

#include "../../Thirdparty/imgui/imgui_stdlib.h"
#include "../../Thirdparty/imgui/imgui.h"
#include "../../Thirdparty/imgui/imstb_textedit.h"

#include "SceneManager.h"
#include "../Renderer/Camera.h"

namespace Lomus {
    enum ConsoleMode {separate, intergrated};

    class Console {
    public:
        int MODE_TOGGLE = 0;
        int MODE_WINDOW = 1;
        bool hideConsole = false;
        // Core
        void addCommand(std::string name, std::function<void(std::vector<std::string> &args,Camera& camera, SceneManager &sceneManager, Console& console)> mFunction);
        void deleteCommand(std::string name);
        bool executeCommand(std::string name, std::vector<std::string> &args, Camera& camera, SceneManager& sceneManager);

        // Visual Console
        void init(); //This is for loading the engine's own commands
        void addConsoleLog(const char* data);
        void renderConsole(GLFWwindow *window, int width, int height, Camera& camera, SceneManager& sceneManager, ConsoleMode _mode);
        void clearConsole();
        void cleanUp();

        int mode = Console::MODE_WINDOW;
        ImGuiTextBuffer buf;
        std::unordered_map<std::string, std::function<void(std::vector<std::string> &args, Camera& camera, SceneManager& sceneManager, Console& console)>> commands;

    private:

        std::string commandBuffer;
        std::string prevCommand;

        bool togglePressed;

        bool toggleCurrentlyPressed;

        void initStyle();
    };
};

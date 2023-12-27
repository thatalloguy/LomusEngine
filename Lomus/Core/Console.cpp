#include "Console.h"
#include <sstream>

using namespace Lomus;

void tokennize(std::string const& str, const char delim,
    std::vector<std::string>& out) // For spliting string
{

    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}


// Default Commands:

void helpCommand(std::vector<std::string> &args, Camera& camera, SceneManager& sceneManager, Console& console) {
    console.addConsoleLog("Current registered Commands are:\n");
    for (const auto& command : console.commands) {
        std::string out = "--" + command.first + "\n";
        console.addConsoleLog(out.c_str());
    }
}

void applyForceCommand(std::vector<std::string>& args, Camera& camera, SceneManager& sceneManager, Console& console) {
    if (args.size() == 4) {
        try {
            Vector3 force(stof(args[1]), stof(args[2]), stof(args[3]));
            sceneManager.getGameobject(stoi(args[0]))->mRigidBody->applyWorldForceAtCenterOfMass(force);
            std::string out = "Applied force to Entity: " + to_string(force.x) + " | " + to_string(force.y) + " | " + to_string(force.z) + " \n";
            console.addConsoleLog(out.c_str());
        } catch (std::exception& e) {
            std::string out = e.what();
            out = "[C++ ERROR] " + out + "\n";
            console.addConsoleLog(out.c_str());
            console.addConsoleLog("ERROR: applyForce args are incorrect!\n");
        }

    } else {
        console.addConsoleLog("ERROR: applyForce args are incorrect!\n");
    }

}

void togglePhysicsCommand(std::vector<std::string>& args, Camera& camera, SceneManager& sceneManager, Console& console) {
    if (sceneManager.doPhysics) {
        sceneManager.doPhysics = false;
        console.addConsoleLog("Toggled Physics to FALSE\n");
    } else if (!sceneManager.doPhysics) {
        sceneManager.doPhysics = true;
        console.addConsoleLog("Toggled Physics to TRUE\n");
    }
    
}

void listCommand(std::vector<std::string>& args, Camera& camera, SceneManager& sceneManager, Console& console) {
    console.addConsoleLog("Current Game Objects in the scene:\n");
    auto scene = sceneManager.getCurrentScene();
    for (auto gameObject : scene->gameObjects) {
        std::string ids = +" | ID: " + to_string(gameObject.first);
        std::string out = "--" + gameObject.second->name + ids + "\n";
        console.addConsoleLog(out.c_str());
    }
}



void Console::addCommand(std::string name, std::function<void(std::vector<std::string> &args, Camera& camera, SceneManager& sceneManager, Console &console)> mFunction)
{
    commands.emplace(name, mFunction);
}

void Console::deleteCommand(std::string name)
{
    commands.erase(name);
}

bool Console::executeCommand(std::string name, std::vector<std::string> &args, Camera& camera, SceneManager& sceneManager)
{
    if (commands.find(name) != commands.end()) {
        commands.at(name)(args, camera, sceneManager, *this); // run the function
        return true;
    }
    else {
        name = "[ERROR] Could not find command: " + name + "\n";
        addConsoleLog(name.c_str());
        return false;
    }
}


void Console::init()
{
    // Now We load the default commands
    addCommand("help", helpCommand);
    addCommand("list", listCommand);
    //addCommand("togglePhysics", togglePhysicsCommand);
    addCommand("applyForce", applyForceCommand);

    //init the imgui style
    initStyle();
}

void Console::addConsoleLog(const char* data)
{
    Console::buf.append("[Info]  ");
    Console::buf.append(data);
    Console::buf.append("\n");
    spdlog::info(data);
}

void Console::addConsoleWarning(const char *data) {
    Console::buf.append("[Warning]  ");
    Console::buf.append(data);
    Console::buf.append("\n");
    spdlog::info(data);
}

void Console::addConsoleError(const char *data) {
    Console::buf.append("[Error]  ");
    Console::buf.append(data);
    Console::buf.append("\n");
    spdlog::info(data);
}


int Console::previewCommands(ImGuiInputTextCallbackData *data) {


    return 0;
}




void Console::renderConsole(GLFWwindow* window, int width, int height, Camera& camera, SceneManager& sceneManager, ConsoleMode _mode)
{
    if (_mode == ConsoleMode::intergrated) {
        mode = Console::MODE_WINDOW;
    }
    if (mode == Console::MODE_WINDOW) {
        if (_mode == ConsoleMode::separate) {
            ImGui::SetNextWindowSize(ImVec2(width, height));
            ImGui::Begin("Console");
        }


        if (ImGui::Button("Clear")) {
            Console::clearConsole();
        } ImGui::SameLine();  if (ImGui::Button("To Bottom")) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::BeginChild("Logs",ImVec2(ImGui::GetWindowContentRegionWidth(), height * 0.6), true);

        ImGui::TextUnformatted(Console::buf.begin());


        ImGui::EndChild();

        ImGui::PushID(340);
        const char* d = "";

        ImGui::SetCursorPosY(height - 25);
        ImGui::SetNextItemWidth(width * 0.9);

        ImGui::InputText(d, &commandBuffer,  ImGuiInputTextFlags_CallbackEdit, previewCommands);

        ImGui::PopID();
        ImGui::SameLine();
        if (ImGui::Button("Done") || glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            if (!commandBuffer.empty()) {
                prevCommand = commandBuffer;
                std::vector<std::string> out;
                tokennize(commandBuffer, ' ', out);
                commandBuffer = out[0];
                out.erase(out.begin());
                executeCommand(commandBuffer, out, camera, sceneManager);
                commandBuffer = "";

            }
            
        }
        if (_mode == ConsoleMode::separate) {
            ImGui::End();
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && togglePressed) {
            
            Console::mode = Console::MODE_TOGGLE;
            togglePressed = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            togglePressed = true;
        }

        //Play back old command
        if (glfwGetKey(window, GLFW_KEY_UP)) {
            commandBuffer = prevCommand;
        } else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
            commandBuffer = "";
        }

    }
    else if (mode == Console::MODE_TOGGLE) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && togglePressed) {
            
            Console::mode = Console::MODE_WINDOW;
            togglePressed = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            togglePressed = true;
        }
    }
}

void Console::clearConsole()
{
    Console::buf.clear();
}

void Console::cleanUp()
{
    
}

// HUGE CREDITS TO: https://github.com/janekb04
void Console::initStyle()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding                     = ImVec2(8.00f, 8.00f);
    style.FramePadding                      = ImVec2(5.00f, 2.00f);
    style.CellPadding                       = ImVec2(6.00f, 6.00f);
    style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
    style.IndentSpacing                     = 25;
    style.ScrollbarSize                     = 15;
    style.GrabMinSize                       = 10;
    style.WindowBorderSize                  = 1;
    style.ChildBorderSize                   = 1;
    style.PopupBorderSize                   = 1;
    style.FrameBorderSize                   = 1;
    style.TabBorderSize                     = 1;
    style.WindowRounding                    = 7;
    style.ChildRounding                     = 4;
    style.FrameRounding                     = 3;
    style.PopupRounding                     = 4;
    style.ScrollbarRounding                 = 9;
    style.GrabRounding                      = 3;
    style.LogSliderDeadzone                 = 4;
    style.TabRounding                       = 4;
}

#include "Console.h"
#include <sstream> 

void tokenize(std::string const& str, const char delim,
    std::vector<std::string>& out) // For spliting string 
{

    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}


// Default Commands:

void helpCommand(std::vector<std::string> args, Camera& camera, SceneManager& sceneManager, Console& console) {
    console.addConsoleLog("Current registered Commands are:\n");
    for (const auto& command : console.commands) {
        std::string out = "--" + command.first + "\n";
        console.addConsoleLog(out.c_str());
    }
}




void Console::addCommand(std::string name, std::function<void(std::vector<std::string> args, Camera& camera, SceneManager& sceneManager, Console &console)> mFunction)
{
    commands.emplace(name, mFunction);
}

void Console::deleteCommand(std::string name)
{
    commands.erase(name);
}

bool Console::executeCommand(std::string name, std::vector<std::string> args, Camera& camera, SceneManager& sceneManager)
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
}

void Console::addConsoleLog(const char* data)
{
    Console::buf.append(data);
}


void Console::renderConsole(GLFWwindow* window, int width, int height, Camera& camera, SceneManager& sceneManager)
{
    if (mode == Console::MODE_WINDOW) {
        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::Begin("Console");

        if (ImGui::Button("Clear")) {
            Console::clearConsole();
        } ImGui::SameLine();  if (ImGui::Button("To Bottom")) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::TextUnformatted(Console::buf.begin());
        ImGui::PushID(340);
        const char* d = "";
        ImGui::SetCursorPosY(height - 30);
        ImGui::InputText(d, &commandBuffer);
        ImGui::PopID();
        ImGui::SameLine();
        if (ImGui::Button("Done") || glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            if (!commandBuffer.empty()) {
                commandBuffer;
                std::vector<std::string> out;
                tokenize(commandBuffer, ' ', out);
                commandBuffer = out[0];
                out.erase(out.begin());
                executeCommand(commandBuffer, out, camera, sceneManager);
                commandBuffer = "";

            }
            
        }
        
        ImGui::End();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && togglePressed) {
            
            Console::mode = Console::MODE_TOGGLE;
            togglePressed = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            togglePressed = true;
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

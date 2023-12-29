
#include "ProjectManager.h"

void Lomus::ProjectManager::createNewProject(Lomus::ProjectData &projectData) {

    mConsole.addConsoleLog(std::string("[ProjectManager] Creating new Project: " + projectData.name).c_str());


    if (projectData.path == "DEFAULT") {
        setProjectPath(std::string("../../Projects/") + projectData.name);
    } else {
        setProjectPath(projectData.path + projectData.name);
    }


    if (createNewFolder(projectPath)) {
        spdlog::info("[ProjectManager] created folder: " + projectPath);
    } else {
        spdlog::error("[ProjectManager] Could not create folder" + projectPath);
    }
}

void Lomus::ProjectManager::setProjectPath(std::string path) {
    projectPath = path;
}

ProjectManager::ProjectManager(Console &console) : mConsole(console) {
    mConsole.addConsoleLog("[ProjectManager] Initialing ProjectManager!");

    LoadSettings();
}

bool ProjectManager::createNewFolder(std::string newFolderPath) {
    return std::filesystem::create_directories(newFolderPath);
}

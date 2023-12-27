
#include "ProjectManager.h"

void Lomus::ProjectManager::createNewProject(Lomus::ProjectData &projectData) {

    mConsole.addConsoleLog(std::string("[ProjectManager] Creating new Project: " + projectData.name).c_str());

}

void Lomus::ProjectManager::setDefaultProjectPath(std::string &path) {

}

ProjectManager::ProjectManager(Console &console) : mConsole(console) {
    mConsole.addConsoleLog("Initialing ProjectManager!");

    LoadSettings();
}

#pragma once
#include <string>
#include <spdlog/spdlog.h>
#include <filesystem>

#include "Console.h"

namespace Lomus {

    struct ProjectData{
        std::string name = "New Lomus Project";
        std::string path = "DEFAULT";
    };

    class ProjectManager {

    public:
        ProjectManager(Console& console);
        ~ProjectManager() {};

        void createNewProject(ProjectData& projectData);

        void setProjectPath(std::string path);
        std::string& getProjectPath() { return projectPath; };

        bool isAnyProjectOpen() { return projectPath != "../../Projects"; };


    private:
        std::string projectPath = "../../Projects/";
        Lomus::Console& mConsole;



        bool createNewFolder(std::string newFolderPath);

        void LoadSettings() {};
    };


}
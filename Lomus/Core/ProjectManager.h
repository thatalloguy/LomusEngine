#pragma once
#include <string>
#include <spdlog/spdlog.h>

#include "Console.h"

namespace Lomus {

    struct ProjectData{
        std::string name;
        std::string path = "DEFAULT";
    };

    class ProjectManager {

    public:
        ProjectManager(Console& console);
        ~ProjectManager() {};

        void createNewProject(ProjectData& projectData);

        void setDefaultProjectPath(std::string& path);
        std::string& getDefaultProjectPath() { return defaultProjectPath; };


    private:
        std::string defaultProjectPath = "../../Projects/";
        Lomus::Console& mConsole;

        void LoadSettings() {};
    };


}
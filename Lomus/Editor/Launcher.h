#pragma once
#include <glad/glad.h>
#include <yaml-cpp/yaml.h>
#include "../Core/ProjectManager.h"
#include "../../Thirdparty/imgui/IconsFontAwesome6.h"
#include "../../Thirdparty/imgui/ImGuiFileBrowser.h"

namespace Lomus {

    class Launcher {

    public:
        Launcher(ProjectManager& projectManager);
        ~Launcher();

        void render(float windowWidth, float windowHeight);

        bool hasProjectOpen() { return hasProjectedOpened; };
    private:

        enum LauncherTabs{Projects,Plugins,Settings,About};

        //Master tabs
        void renderSelectionTab();
        void renderInfoTab();
        void renderTitlebarTab();

        // Child tabs
        void renderSettingsTab();
        void renderProjectManagerTab();
        void renderPluginsTab();

        void renderProjectTiles();

        void loadIconImage();
        void loadSettings();

        void saveManagedProjects();
        void loadManagedProjects(YAML::Node& node);

        float currentWindowWidth, currentWindowHeight = 0.0f;

        LauncherTabs currentOpenTab = LauncherTabs::Projects;
        unsigned int rawTexture;
        const char* imagePath = "../../Lomus/Resources/LogoV2.jpg";
        const char* configPath = "../../Lomus/Resources/Data/config.yml";

        std::string version = "unknown";
        ProjectData newProjectData;
        ProjectData openedProject;
        bool hasProjectedOpened = false;

        int item_current_2 = 0;
        int currentSelectedProject = 0;
        bool openProjectAfterCreation = true;

        std::vector<ProjectData> managedProjects;

        YAML::Emitter config;

        imgui_addons::ImGuiFileBrowser file_dialog;

        ProjectManager& mProjectManager;
    };

}

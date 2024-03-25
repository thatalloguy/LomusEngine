//
// Created by allos on 12/28/2023.
//

#include "Launcher.h"
#include "../../Thirdparty/imgui/imgui_internal.h"

Launcher::Launcher(ProjectManager &projectManager) : mProjectManager(projectManager) {
    // Other init stuff
    loadIconImage();
    loadSettings();

}

Launcher::~Launcher() {
    // Delete stuff
}

void Launcher::render(float windowWidth, float windowHeight) {
    // Render tabs
    ImGuiIO& io = ImGui::GetIO();

    io.FontGlobalScale = 0.5f;

    currentWindowWidth = windowWidth;
    currentWindowHeight = windowHeight;


    renderTitlebarTab();
    renderSelectionTab();
    renderInfoTab();

}

void Launcher::renderSelectionTab() {
    ImGui::SetNextWindowPos(ImVec2(0, currentWindowHeight * 0.075f));
    ImGui::SetNextWindowSize(ImVec2(currentWindowWidth * 0.25f, currentWindowHeight * 0.925f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Selection Tab", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::PopStyleVar(1);
    // Icon go here

    ImGui::SetWindowFontScale(1.2f);
    ImGui::SetCursorPosY(0);
    if (ImGui::Selectable(ICON_FA_FOLDER       "   Projects", (currentOpenTab == LauncherTabs::Projects))) {
        currentOpenTab = LauncherTabs::Projects;
    }
    if (ImGui::Selectable(ICON_FA_PUZZLE_PIECE "   Plugins", (currentOpenTab == LauncherTabs::Plugins))) {
        currentOpenTab = LauncherTabs::Plugins;
    }
    if (ImGui::Selectable(ICON_FA_GEAR         "   Settings", (currentOpenTab == LauncherTabs::Settings))) {
        currentOpenTab = LauncherTabs::Settings;
    }
    ImGui::End();
}

void Launcher::renderTitlebarTab() {

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(currentWindowWidth, currentWindowHeight * 0.075));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.180980454683304f, 0.180980454683304f, 0.180980454683304f, 1.0f)); // Background color


    ImGui::Begin("Titlebar", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);

    ImGui::SetCursorPos(ImVec2(0, 2));
    ImGui::Image(reinterpret_cast<ImTextureID>(rawTexture), ImVec2(static_cast<float>(currentWindowWidth * 0.04f), static_cast<float>(currentWindowHeight * 0.07f)), ImVec2(0, 1), ImVec2(1, 0));


    ImGui::End();

}



void Launcher::loadIconImage() {


    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glGenTextures(1, &rawTexture);
        glBindTexture(GL_TEXTURE_2D, rawTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        spdlog::info("[Launcher] Sucsessfully loaded Launcher Icon  ");
    } else {
        spdlog::error("[Launcher] Couldnt load image: %i", imagePath);

        stbi_image_free(data);
    }
}

void Launcher::renderInfoTab() {

    ImGui::SetNextWindowPos(ImVec2(currentWindowWidth * 0.25f, currentWindowHeight * 0.075f));
    ImGui::SetNextWindowSize(ImVec2(currentWindowWidth * 0.75f, currentWindowHeight * 0.925f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.120980454683304f, 0.120980454683304f, 0.120980454683304f, 1.0f)); // Background color
    ImGui::Begin("Info Tab", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);


    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);

    switch (currentOpenTab) {
        case LauncherTabs::Projects:
            renderProjectManagerTab();
            break;
        case LauncherTabs::Plugins:
            renderPluginsTab();
            break;
        case LauncherTabs::Settings:
            renderSettingsTab();
            break;
    }


    ImGui::End();

}

void Launcher::renderSettingsTab() {
    ImGui::Text("No Settings Available :(");
}

void Launcher::renderProjectManagerTab() {


    renderProjectTiles();

    ImGui::SetCursorScreenPos(ImVec2(currentWindowWidth * 0.94f, currentWindowHeight * 0.94f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.4, 1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 1.5f);

    if (ImGui::Button(" New ")) {
        ImGui::OpenPopup("Create new Project");
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);



    ImGui::SetNextWindowSize(ImVec2(currentWindowWidth * 0.6f, currentWindowHeight * 0.5f));
    if (ImGui::BeginPopupModal("Create new Project")) {
        ImGui::Separator();
        ImGui::Text("Name: "); ImGui::SameLine();
        ImGui::PushID("PN");
        ImGui::InputText(" ", &newProjectData.name);
        ImGui::PopID();

        ImGui::Text("Path: "); ImGui::SameLine();

        ImGui::PushID("Pc");
        ImGui::Combo(" ", &item_current_2, "Default\0 Custom\0");
        ImGui::PopID();

        if (item_current_2 == 1) {
            ImGui::PushID("NP");
            ImGui::InputText(" ", &newProjectData.path);
            ImGui::PopID();
            ImGui::SameLine();

            if (ImGui::Button("Open")) {
                ImGui::CloseCurrentPopup();
                ImGui::OpenPopup(3);
            }
        } else {
            newProjectData.path = "DEFAULT";
        }
        ImGui::Text("Version: "); ImGui::SameLine(); ImGui::BeginDisabled(); ImGui::Selectable(version.c_str()); ImGui::EndDisabled();

        ImGui::Text(" ");
        ImGui::Spacing();

        ImGui::Checkbox(" Open Project after creation", &openProjectAfterCreation);

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 40);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.5f);
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.4, 1, 1));

        if (ImGui::Button("Done")) {
            newProjectData.version = version;
            managedProjects.push_back(newProjectData);
            saveManagedProjects();
            openedProject = managedProjects.back();


            mProjectManager.createNewProject(openedProject);

            if (openProjectAfterCreation) {
                hasProjectedOpened = true;
                mProjectManager.openProject(openedProject);
            }

            ImGui::CloseCurrentPopup();
        }

        ImGui::PopStyleVar(1);
        ImGui::PopStyleColor(1);
        ImGui::EndPopup();
    }

    if(file_dialog.showFileDialog(3, imgui_addons::ImGuiFileBrowser::DialogMode::SELECT, ImVec2(currentWindowWidth / 2, currentWindowHeight / 2)))
    {
        if (!file_dialog.selected_path.empty()) {
            newProjectData.path = file_dialog.selected_path;
            ImGui::OpenPopup("Create new Project");
        }


    }
}

void Launcher::renderProjectTiles() {
    int count = 0;

    if (ImGui::BeginTable("Projects", 4)) {


        for (auto& project : managedProjects) {

            count++;

            ImGui::TableNextColumn();

            ImVec2 rectMin = ImGui::GetCursorScreenPos();
            rectMin.y += 15;




            ImVec2 rectMax = ImVec2(rectMin.x + ImGui::GetColumnWidth(), rectMin.y + 225);

            ImVec4 color = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);

            ImGui::GetWindowDrawList()->AddRectFilled(rectMin, rectMax, IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255), 10.0f);

            // Draw Project icon
            ImGui::SetCursorScreenPos(ImVec2(rectMin.x, rectMin.y));
            ImGui::Image(reinterpret_cast<ImTextureID>(rawTexture), ImVec2(175, 150), ImVec2(0, 1), ImVec2(1, 0));
            if (ImGui::IsItemHovered()) {
                ImGui::SetWindowFontScale(0.5f);
                ImGui::SetTooltip("%s", std::string(project.name + " - Version: " + project.version +"\n \n(Double click to open)").c_str());
                ImGui::SetWindowFontScale(1.0f);
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                spdlog::info("[Launcher] Opening Project: " + project.name);
                openedProject = project;
                hasProjectedOpened = true;
                openedProject.path = "../../Projects/" + project.name;
                mProjectManager.openProject(openedProject);
            }
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
                currentSelectedProject = count;
                ImGui::OpenPopup(1);
            }
            ImGui::SetNextWindowSize(ImVec2(150, 35));
            if (ImGui::BeginPopupEx(1, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
                    if (ImGui::Selectable("Delete Project")) {
                        managedProjects.erase(managedProjects.begin() + currentSelectedProject - 1);
                    }
                ImGui::EndPopup();
            }

            ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(rectMin.x, rectMin.y + 150), ImVec2(rectMax.x, rectMin.y + 150), IM_COL32(0.4f * 255, 0.322f * 255, 0.89f * 255, 255), 10.0f);

            ImGui::SetCursorScreenPos(ImVec2(rectMin.x + 5, rectMin.y + 155));
            ImGui::SetWindowFontScale(1.0f);
            ImGui::Text(project.name.c_str());


            ImGui::SetCursorScreenPos(ImVec2(rectMin.x + 5, rectMin.y + 200));
            ImGui::SetWindowFontScale(0.6f);
            ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.3, 0.3, 0.3, 1);
            ImGui::Text(project.version .c_str()); ImGui::SameLine(); ImGui::Text("*");
            ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Engine Version");
            }
            ImGui::SetWindowFontScale(1.0f);

        }

        ImGui::EndTable();
    }

}


void Launcher::renderPluginsTab() {
    ImGui::SetCursorPosX(currentWindowWidth  / 1.5f);
    ImGui::Button(ICON_FA_BOOK " Import");

    ImGui::TextColored(ImVec4(1, 0.2, 0.2, 1), "No Plugins loaded");
}

void Launcher::loadSettings() {
    spdlog::info("[Launcher] loading config file");
    YAML::Node root = YAML::LoadFile(configPath);

    if (root["version"]) {
        version = root["version"].as<std::string>();
    } else {
        spdlog::error("[Launcher] Could not find engine version :(");
    }

    loadManagedProjects(root);


    spdlog::info("[Launcher] sucsess with config file");
}

void Launcher::saveManagedProjects() {
    config << YAML::BeginMap;
    config << YAML::Key << "ManagedProjects" << YAML::Value << YAML::BeginSeq;

    for (auto& project : managedProjects) {
        config << YAML::BeginMap;
        config << YAML::Key << "Name" << YAML::Value << project.name;
        config << YAML::Key << "Path" << YAML::Value << project.path;
        config << YAML::Key << "Version" << YAML::Value << project.version;
        config << YAML::EndMap;
    }

    config << YAML::EndSeq;

    config << YAML::Key << "version" << YAML::Value << version;
    config << YAML::Key << "fpsCap" << YAML::Value <<  60.0f;
    std::ofstream os(configPath);

    if (os.is_open()) {
        os.clear();
        os << config.c_str();

        spdlog::info("[Launcher] Sucsessfully saved config");

        os.close();
    } else {
        spdlog::error("[Launcher] Could not write to config file!");

    }

}

void Launcher::loadManagedProjects(YAML::Node &node) {
    managedProjects.clear();
    if (node["ManagedProjects"]) {
        spdlog::info("[Launcher] Loading Managed projects");
        const auto& managedProjectsFromConfig = node["ManagedProjects"];

        for (const auto& project : managedProjectsFromConfig) {
            managedProjects.push_back(ProjectData{project["Name"].as<std::string>(), project["Path"].as<std::string>(), project["Version"].as<std::string>()});
            spdlog::info("[Launcher] loaded project info for --> " + project["Name"].as<std::string>());
        }
    }
}

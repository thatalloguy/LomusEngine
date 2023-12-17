#include "Editor.h"


void Lomus::Editor::initStlyle(EditorStyle editorStyle) {
// Visual Studio style by MomoDeve from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    auto& imGuiIO{ ImGui::GetIO() };
    imGuiIO.IniFilename = NULL;
    imGuiIO.LogFilename = NULL;
    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 7.5f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5921568870544434f, 0.5921568870544434f, 0.5921568870544434f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1400980454683304f, 0.1400980454683304f, 0.1400196138620377f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.104f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1350980454683304f, 0.1350980454683304f, 0.1390196138620377f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);

}

Lomus::Editor::Editor(GLFWwindow *window, EditorStyle style, SceneManager& sceneManager) {
    mConsole.init();
    initStlyle(style);
    Editor::rawWindow = window;

    glfwGetWindowSize(window, Editor::windowWidth, Editor::windowHeight);
    std::cout << "Creating editor at size:" << Editor::windowWidth[0] << "X" << Editor::windowHeight[0] << "\n";

    createFBO(512, 512);

    Lomus::Keyboard::getInstance().setCaptureWindow(rawWindow);
    auto& guizmoStyle = ImGuizmo::GetStyle();

    

    guizmoStyle.HatchedAxisLineThickness = 0;

    // Prepare the color text editor
    auto lang = TextEditor::LanguageDefinition::GLSL();
    textEditor.SetLanguageDefinition(lang);
    std::ifstream in("../../Lomus/Shader/shaders/default.frag", std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        textEditor.SetText(contents);
    } else {
        std::cout << "Couldn't load: ../../Lomus/Shader/shaders/default.frag\n";
        textEditor.SetText("Couldnt load shader file :/\n");
    }


    playButton.hoverText = "Play or Stop the game";
    pauseButton.hoverText = "(Un)pause the Game";

    playButton.activeColor = ImVec4(1, 0.44, 0.44, 1);
    playButton.passiveColor = ImVec4(0.44, 1, 0.44, 1);

    pauseButton.activeColor = ImVec4(0.44, 0.44, 1, 1);

    cameraBillboard.load(cameraImagePath);
    cameraBillboard.lockYRot = true;

}

void Lomus::Editor::Render(SceneManager& sceneManager, LightManager& lightManager, Camera& camera, EditorMode mode) {
    switch (mode) {
        case EditorMode::debug:
            //renderDebugModeData(sceneManager, lightManager, shader, outlineShader, window, camera, windowWidth, windowHeight);
            std::cerr << "Debug mode is deprecated\n";
        case EditorMode::editor:
            renderTheFullEditor(camera, sceneManager, lightManager);
            break;
        case EditorMode::shader:

            shaderEditor.Render();
            break;
    }
}

void Lomus::Editor::Delete(SceneManager &sceneManager) {

}

void Lomus::Editor::renderDebugModeData(SceneManager &sceneManager,LightManager& lightManager,Shader& shader, Shader& outlineShader, GLFWwindow* window, Camera& camera,  int windowWidth, int windowHeight) {

}

void Editor::setShader(int name, Shader &shader) {
    shaderList.emplace(name, shader);
}

void Editor::renderTheFullEditor(Camera& camera, SceneManager& sceneManager, LightManager& lightManager) {
    oldWindowHeight = windowHeight[0];
    oldWindowWidth = windowWidth[0];
    hasWindowResized = false;


    glfwGetWindowSize(Editor::rawWindow, Editor::windowWidth, Editor::windowHeight);

    if (oldWindowWidth != windowWidth[0] || oldWindowHeight != windowHeight[0]) {

        if (isWindowMinized()) {
            windowWidth[0] = 1;
            windowHeight[0] = 1;
        }

        resizeFrameBuffer(Editor::windowWidth[0], Editor::windowHeight[0]);
    }
    oldWindowHeight = windowHeight[0];
    oldWindowWidth = windowWidth[0];

        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.75f,oldWindowHeight * 0.65f));
        ImGui::Begin(ICON_FA_TABLE_CELLS_LARGE " Windows", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::BeginTabBar("Bigboi's");


        imTexID = (void*)(intptr_t)texture_id;

        if (ImGui::BeginTabItem(ICON_FA_LAPTOP " Scene")) {
            ImGui::Image(imTexID, ImVec2(static_cast<float>(oldWindowWidth * 0.745f), static_cast<float>(oldWindowHeight * 0.65f)),ImVec2(0, 1), ImVec2(1, 0));
            currentSceneState = EditState::editing;

            ImGui::SetCursorPos(ImVec2(12, 52));
            debugRenderButton.hoverText = "Toggle Physics Debug Renderer";
            debugRenderButton.Render(ICON_FA_EYE_SLASH, ICON_FA_EYE);

            ImGui::EndTabItem();
        }
    ImGui::SetCursorPos(ImVec2((oldWindowWidth * 0.75) / 2 - 50, 25));
        if (ImGui::BeginTabItem(ICON_FA_GAMEPAD " Game")) {
            playButton.Render(ICON_FA_PLAY, ICON_FA_STOP);
            if (playButton.isActive) {
                ImGui::SameLine();
                pauseButton.Render(ICON_FA_PAUSE,ICON_FA_FORWARD_STEP);

            }

            ImGui::Image(imTexID, ImVec2(static_cast<float>(oldWindowWidth * 0.745f), static_cast<float>(oldWindowHeight * 0.65f)),ImVec2(0, 1), ImVec2(1, 0));
            currentSceneState = EditState::playing;
            if (playButton.click && playButton.isActive) {
                prepareGameRuntime(sceneManager);
            } else if (playButton.click && !playButton.isActive) {
                reloadEditScene(sceneManager);
            }


            ImGui::EndTabItem();
        }



        ImGui::EndTabBar();
        if (currentId != -1 && currentState == EditorState::gameObject && currentSceneState == EditState::editing) {
            auto currentGameObject = sceneManager.getGameobject(currentId);
            Editor::movableObject moveObject = {
                    currentGameObject->position,
                    currentGameObject->rotation,
                    currentGameObject->scale,
            };

            manipulateObjectViaGizmo(moveObject, camera);
        }

        if (currentState == EditorState::Scene) {

            glm::vec3 ts = {1, 1, 1};
            glm::quat tq = {0, 0, 0, 1};
            glm::vec3 tp = -cameraBillboard.position;
            Editor::movableObject moveObject = {
                    tp,
                    tq,
                    ts
            };

            manipulateObjectViaGizmo(moveObject, camera);

            cameraBillboard.position.x = -moveObject.position.x;
            cameraBillboard.position.y = -moveObject.position.y;
            cameraBillboard.position.z = -moveObject.position.z;
        }


        if (currentSelectedLight != nullptr && currentState == EditorState::Light && currentSelectedLight->lightType != 1 && currentSceneState == EditState::editing) {

            glm::vec3 tp = glm::vec3(currentSelectedLight->lightPosition_x,currentSelectedLight->lightPosition_y,currentSelectedLight->lightPosition_z);
            glm::quat tq = glm::quat(0, 0, 0, 1);
            glm::vec3 ts = glm::vec3(1, 1, 1);

            Editor::movableObject moveObject = {
                    tp,
                    tq,
                    ts
            };

            manipulateObjectViaGizmo(moveObject, camera);

            currentSelectedLight->lightPosition_x = tp.x;
            currentSelectedLight->lightPosition_y = tp.y;
            currentSelectedLight->lightPosition_z = tp.z;

            auto billboard = lightBillboards.at(currentSelectedLight);
            if (billboard != nullptr) {
                billboard->position.x = -currentSelectedLight->lightPosition_x;
                billboard->position.y = -currentSelectedLight->lightPosition_y;
                billboard->position.z = -currentSelectedLight->lightPosition_z;
            }
        }


        ImGui::End();


        renderSelectionPanel(camera, sceneManager, lightManager);

        renderOtherPanel(camera, sceneManager, lightManager);

        renderPropertiesPanel(camera, sceneManager, lightManager);

        handleInputs(camera);


}


void Editor::createNewGameObject(SceneManager &sceneManager) {
    mConsole.addConsoleLog("Creating a new Game Object");
    GameObject newObject(glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 1), glm::vec3(1, -1, 1), "GameObject");
    sceneManager.addGameObject(newObject);
}




void Editor::renderSelectionPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {

    ImGui::SetNextWindowPos(ImVec2(oldWindowWidth * 0.75f, 0));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.25f, oldWindowHeight * 0.5f));
    ImGui::Begin(ICON_FA_ARROW_POINTER " Selection Panel", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::BeginTabBar("Selection");

    if (ImGui::BeginTabItem(ICON_FA_CUBES " Game Objects")) {
        int i = 0;
        std::string search = "";
        ImGui::Spacing();
        ImGui::PushID("search");
        ImGui::SetNextItemWidth(oldWindowWidth * 0.20f);
        ImGui::InputTextWithHint(" ", "Search for Objects", &search);
        ImGui::PopID();

        ImGui::SameLine();
        ImGui::SetWindowFontScale(1.25f);
        if (ImGui::Button(ICON_FA_PLUS)) {
            createNewGameObject(sceneManager);
        }

        ImGui::SetWindowFontScale(1.0f);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Create a new Game Object");
        }

        ImGui::Spacing();
        ImGui::Separator();
        currentState = EditorState::gameObject;

        for (auto& pair : sceneManager.currentScene->gameObjects) {
            std::shared_ptr<GameObject> gameObject = pair.second;

            ImGui::PushID(i);
            std::string newName = ICON_FA_CUBE + std::string(" " + gameObject->name);

            if (gameObject->name.find(search) != string::npos) {

                auto& style = ImGui::GetStyle();
                if (gameObject->id == currentId) { // is object selected
                    style.Colors[ImGuiCol_Text] = ImVec4(0.5, 0.5, 1, 1);
                }



                ImGui::BulletText(newName.c_str());
                if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                    if (gameObject->id == currentId) {
                        currentId = -1;
                    } else {
                        currentId = pair.first;
                    }
                }


                style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
                ImGui::Separator();


            }

            i++;
            ImGui::PopID();
        }
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(ICON_FA_OBJECT_UNGROUP" Scenes")) {
        ImGui::Text("Scenes here");
        currentState = EditorState::Scene;
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(ICON_FA_LIGHTBULB " Lights")) {
        currentState = EditorState::Light;
        int i = 0;

        std::string search = "";
        ImGui::Spacing();
        ImGui::PushID("search");
        ImGui::SetNextItemWidth(oldWindowWidth * 0.20f);
        ImGui::InputTextWithHint(" ", "Search for Lights", &search);
        ImGui::PopID();

        ImGui::SameLine();
        ImGui::SetWindowFontScale(1.25f);
        if (ImGui::Button(ICON_FA_PLUS)) {
            createNewLight(sceneManager, lightManager);
        }
        ImGui::SetWindowFontScale(1.0f);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Create a new light Source");
        }

        ImGui::Spacing();
        ImGui::Separator();

        for (auto& pair : lightManager.lightIdMap.at(sceneManager.currentScene->name)) {


            ImGui::PushID(i);
            std::string newName = ICON_FA_LIGHTBULB + std::string(" " + pair.second->name);

            auto &style = ImGui::GetStyle();

            if (pair.second->name.find(search) != string::npos) {
                if (currentSelectedLight == pair.second) { // is object selected
                    style.Colors[ImGuiCol_Text] = ImVec4(0.5, 0.5, 1, 1);
                }


                ImGui::BulletText(newName.c_str());
                style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);


                if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                    if (currentSelectedLight == pair.second) { // is object selected
                        currentSelectedLight = nullptr;
                    } else {
                        currentSelectedLight = pair.second;
                    }
                }

                ImGui::Separator();
            }
            i++;
            ImGui::PopID();
        }
        ImGui::EndTabItem();
    }



    ImGui::EndTabBar();


    ImGui::End();
}

void Editor::renderOtherPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {
    ImGui::SetNextWindowPos(ImVec2(0, oldWindowHeight * 0.65f));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.75f, oldWindowHeight * 0.35f));
    ImGui::Begin(ICON_FA_GEARS " Utils", NULL,  ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::BeginTabBar("Other");

    if (ImGui::BeginTabItem(ICON_FA_TERMINAL " Console", false, ImGuiWindowFlags_NoScrollbar)) {
        mConsole.renderConsole(Editor::rawWindow, oldWindowWidth * 0.75f, oldWindowHeight * 0.35f, camera, sceneManager, Lomus::ConsoleMode::intergrated);
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(ICON_FA_FOLDER " Files")) {
        ImGui::Text("Files here");
        ImGui::EndTabItem();
    }


    if (ImGui::BeginTabItem(ICON_FA_CODE" Shader Editor")) {
        if (ImGui::Button("Reload Shader")) {
            shaderList.at(1).reCompile();
            if ( shaderList.at(1).getErrorLine() != -1) {
                errorMarkers.insert(std::make_pair<int, std::string>(shaderList.at(1).getErrorLine(), shaderList.at(1).getErrorMessage().c_str()));
                textEditor.SetErrorMarkers(errorMarkers);
                errorline =shaderList.at(1).getErrorLine();
            } else if (shaderList.at(1).getErrorLine() == -1) {
                errorMarkers.erase(errorline);
                textEditor.SetErrorMarkers(errorMarkers);
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Save")) {
            std::ofstream out("../../Lomus/Shader/shaders/default.frag");
            out << textEditor.GetText().c_str();
            out.close();
        }

        textEditor.Render("--Shader editor--");
        currentSceneState = EditState::texteditor;
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();

    ImGui::End();
}

void Editor::renderPropertiesPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {
    ImGui::SetNextWindowPos(ImVec2(oldWindowWidth * 0.75f, oldWindowHeight * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.25f, oldWindowHeight * 0.5f));
    ImGui::Begin(ICON_FA_INFO " Information & Properties", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);



    switch (currentState){
        case gameObject:

            if (currentId != -1) {
                renderGameObjectProperties(sceneManager.getGameobject(currentId), camera,sceneManager);
            }

            break;
        case Scene:
            renderActiveScene(sceneManager);
            break;
        case Light:
            renderLightProperties(sceneManager, lightManager);
            //mConsole.addConsoleLog("Not Ready!\n");
            break;
        case Script:
            mConsole.addConsoleLog("Not Ready!\n");
            break;

    }
    ImGui::End();

}

void Editor::renderGameObjectProperties(std::shared_ptr<GameObject> currentGameObject, Camera& camera, SceneManager& sceneManager) {
    bool isdel = false;
    ImGuiStyle& style = ImGui::GetStyle();


    ImGui::Text("Name: ");
    ImGui::PushID("name");
    ImGui::SameLine();
    ImGui::InputText("", &currentGameObject->name);
    ImGui::PopID();


    ImGui::Text("ID: "); ImGui::SameLine(); ImGui::Text(  "%s", std::to_string(currentGameObject->id).c_str());



    ImGui::Spacing();

    if (ImGui::Button("Delete GameObject")) {
        if (currentSceneState != playing) {
            sceneManager.removeGameObject(currentGameObject);
            currentId = -1;
            currentGameObject = nullptr;
            return;
        } else {
            mConsole.addConsoleError("Cannot delete a gameObject in game runtime!");
        }

    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(windowWidth[0] * 0.175);
    if (ImGui::TreeNodeEx((ICON_FA_GEAR" TransFormation"), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {
        ImGui::Spacing();
///     pos
        float tempX[1] = {currentGameObject->position.x};
        float tempY[1] = {currentGameObject->position.y};
        float tempZ[1] = {currentGameObject->position.z};
        // Rot
        glm::vec3 convertedVec = eulerAngles(currentGameObject->rotation);
        float tempRX[1] = {convertedVec.x};
        float tempRY[1] = {convertedVec.y};
        float tempRZ[1] = {convertedVec.z};
        // Scale

        float tempSX[1] = {currentGameObject->scale.x};
        float tempSY[1] = {currentGameObject->scale.y};
        float tempSZ[1] = {currentGameObject->scale.z};


        ImGui::Text("Position: ");
        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(1, 0.2, 0.2, 1);
        ImGui::Text("X");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("x");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempX, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();
        style.Colors[ImGuiCol_Text] = ImVec4(0.2, 1, 0.2, 1);
        ImGui::Text("Y");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("Y");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempY, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(0.3, 0.3, 1, 1);
        ImGui::Text("Z");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("z");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempZ, 0.5f);
        ImGui::PopID();


        ImGui::Text(" ");
        // Display Rotation
        ImGui::BulletText("Rotation: ");
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Rotation can only be changed via gizmo's ");
        }
        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(1, 0.2, 0.2, 1);
        ImGui::Text("X");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("xr");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempRX, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();
        style.Colors[ImGuiCol_Text] = ImVec4(0.2, 1, 0.2, 1);
        ImGui::Text("Y");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("Yr");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempRY, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(0.3, 0.3, 1, 1);
        ImGui::Text("Z");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("zr");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempRZ, 0.5f);
        ImGui::PopID();


        ImGui::Text(" ");

        ImGui::Text("Scale: ");
        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(1, 0.2, 0.2, 1);
        ImGui::Text("X");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("sx");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempSX, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();
        style.Colors[ImGuiCol_Text] = ImVec4(0.2, 1, 0.2, 1);
        ImGui::Text("Y");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("sY");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempSY, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(0.3, 0.3, 1, 1);
        ImGui::Text("Z");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("sz");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempSZ, 0.5f);
        ImGui::PopID();




        currentGameObject->position.x = tempX[0];
        currentGameObject->position.y = tempY[0];
        currentGameObject->position.z = tempZ[0];
        glm::quat tq = glm::quat(convertedVec);
        currentGameObject->rotation.x = tq.x;
        currentGameObject->rotation.y = tq.y;
        currentGameObject->rotation.z = tq.z;
        currentGameObject->rotation.w = tq.w;

        currentGameObject->scale.x = tempSX[0];
        currentGameObject->scale.y = tempSY[0];
        currentGameObject->scale.z = tempSZ[0];

        ImGui::TreePop();
    }
    ImGui::Text(" ");
    if (!currentGameObject->model.isEmpty()) {
        if (ImGui::TreeNodeEx((ICON_FA_CUBES" Model"), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {
            renderModelComponent(currentGameObject->model);
            ImGui::TreePop();
        }

    }
    ImGui::Text(" ");


    if (currentGameObject->isPhysical) {
        renderRigidBodyComponent(currentGameObject->mRigidBody, currentGameObject->isPhysical, sceneManager, currentGameObject);
    }
    renderBillboardModelComponent(currentGameObject);

    ImGui::Separator();

    ImGui::Text(" ");



    if (ImGui::Button("Add Component", ImVec2(windowWidth[0] / 4, 0.0f))) {
        selectingComponents = true;
        ImGui::OpenPopup("Select a component:");
    }


    if (ImGui::BeginPopup("Select a component:")) {

        if (ImGui::BeginMenu(ICON_FA_CUBE " Render")) {

            if (ImGui::MenuItem("Model")) {
                selectingComponents = false;
                currentGameObject->model.isDeleted = false;
            }

            if (ImGui::MenuItem("Billboard")) {
                selectingComponents = false;
                currentGameObject->mBillboard.amEmpty = false;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu(ICON_FA_PUZZLE_PIECE " Physics")) {

            if (ImGui::MenuItem(ICON_FA_WAND_MAGIC" RigidBody")) {
                sceneManager.createRigidBody(currentGameObject->id, BodyType::STATIC);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu( ICON_FA_TERMINAL" Scripting")) {

            ImGui::Text("Nothing here");

            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }

}

void Editor::renderModelComponent(Model& model) {
    if (model.rawPath != "EMPTY") {

        ImGui::Text("Name: "); ImGui::SameLine();
        ImGui::BeginDisabled();

        vector<string> filename;
        vector<string> fileextension;
        Lomus::Toolbox::splitStringToComponents(model.rawPath, '/', filename);
        Lomus::Toolbox::splitStringToComponents(filename.back(), '.', filename);
        filename.pop_back();
        Lomus::Toolbox::splitStringToComponents(model.rawPath, '.', fileextension);
        ImGui::Button(filename.back().c_str());
        ImGui::EndDisabled();

        ImGui::Text("File extension: "); ImGui::SameLine();
        ImGui::BeginDisabled();
        string extension = "." + fileextension.back();
        ImGui::Button(extension.c_str());
        ImGui::EndDisabled();

        ImGui::Text(" ");
        if (ImGui::Button("Change")) {
            ImGui::OpenPopup("Open File");
        }
        ImGui::Text(" ");
    } else {

        if (ImGui::Button("Load Model")) {
            ImGui::OpenPopup("Open File");
        }
    }


    if(file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(windowWidth[0] / 2, windowHeight[0] / 2)))
    {
        if (!file_dialog.selected_path.empty()) {
            model.Delete();
            if (!model.load(file_dialog.selected_path)) {
                mConsole.addConsoleLog("[ERROR] could not load model file!\n");
                ImGui::OpenPopup("Error");

                if (ImGui::BeginPopupModal("Error")) {
                    ImGui::Text("[ERROR] could not load model file!");
                    ImGui::EndPopup();
                }
            }
        }

    }

    if (ImGui::Button("Remove")) {
        model.rawPath = "EMPTY";
        model.Delete();
    }

    if (ImGui::TreeNodeEx((ICON_FA_GEAR" Material"), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {
        bool boolN[1] = {model.mMaterial.useNormalMap};
        bool boolMR[1] = {model.mMaterial.useMetalRoughnessMap};
        bool boolAO[1] = {model.mMaterial.useAOMap};
        bool boolE[1] = {model.mMaterial.useEmissivityMap};

        float Mamplifier[1] = {model.mMaterial.metalAmplifier};
        float Ramplifier[1] = {model.mMaterial.roughnessAmplifier};
        float AOamplifier[1] = {model.mMaterial.aoAmplifier};
        float Eamplifier[1] = {model.mMaterial.emissiveAmplifier};

        ImGui::BeginDisabled();

        ImGui::Text("has NormalMap: "); ImGui::SameLine(); ImGui::PushID("mN");
        ImGui::Checkbox(" ", boolN);
        ImGui::PopID();

        ImGui::Text("has Metal-RoughnessMap: "); ImGui::SameLine(); ImGui::PushID("mM");
        ImGui::Checkbox(" ", boolMR);
        ImGui::PopID();

        ImGui::Text("has AOMap: "); ImGui::SameLine(); ImGui::PushID("mA");
        ImGui::Checkbox(" ", boolAO);
        ImGui::PopID();

        ImGui::Text("has EmissiveMap: "); ImGui::SameLine(); ImGui::PushID("mE");
        ImGui::Checkbox(" ", boolE);
        ImGui::PopID();

        ImGui::EndDisabled();


        ImGui::Text("Metal amplifier: "); ImGui::SameLine(); ImGui::PushID("ma");
        ImGui::DragFloat(" ", Mamplifier, 0.05, 0.001);
        ImGui::PopID();


        ImGui::Text("Roughness amplifier: "); ImGui::SameLine(); ImGui::PushID("ra");
        ImGui::DragFloat(" ", Ramplifier, 0.05, 0.001);
        ImGui::PopID();


        ImGui::Text("AO amplifier: "); ImGui::SameLine(); ImGui::PushID("aoa");
        ImGui::DragFloat(" ", AOamplifier, 0.05, 0.001);
        ImGui::PopID();


        ImGui::Text("Emissivity amplifier: "); ImGui::SameLine(); ImGui::PushID("ea");
        ImGui::DragFloat(" ", Eamplifier, 0.05, 0.001);
        ImGui::PopID();

        model.mMaterial.metalAmplifier = Mamplifier[0];
        model.mMaterial.roughnessAmplifier = Ramplifier[0];
        model.mMaterial.aoAmplifier = AOamplifier[0];
        model.mMaterial.emissiveAmplifier = Eamplifier[0];

        ImGui::TreePop();

    }

}

void Editor::renderRigidBodyComponent(reactphysics3d::RigidBody *rigidyBody, bool isPhysical, SceneManager& sceneManager, std::shared_ptr<GameObject> currentGameObject) {
        if (ImGui::TreeNodeEx(ICON_FA_WAND_MAGIC " RigidBody", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {

            ImGui::Text(ICON_FA_INFO " Type:");
            ImGui::SameLine();
            int item_current_2 = static_cast<int>(rigidyBody->getType());
            ImGui::PushID("rbT");
            ImGui::Combo(" ", &item_current_2, "Static\0Kinematic\0Dynamic\0");
            ImGui::PopID();
            switch (item_current_2) {
                case 0:
                    rigidyBody->setType(BodyType::STATIC);
                    break;
                case 2:
                    rigidyBody->setType(BodyType::DYNAMIC);
                    break;
                case 1:
                    rigidyBody->setType(BodyType::KINEMATIC);
                    break;
            }
            float mass[1] = {rigidyBody->getMass()};
            ImGui::Text(ICON_FA_SCALE_BALANCED " Mass"); ImGui::SameLine();
            ImGui::PushID("rbM");
            ImGui::DragFloat(" ", mass, 0.1f);
            ImGui::PopID();
            rigidyBody->setMass(mass[0]);

            ImGui::Text(" ");

            if (!currentGameObject->colliderInfo.hasShape) {
                if (ImGui::Button("Add Collider", ImVec2(windowWidth[0] / 4, 0.0f))) {
                    selectingCollider = true;
                    ImGui::OpenPopup("Select a Collider: ");
                }
            }
            else {
                ImGui::Spacing();

                ImGui::Spacing();
                if (ImGui::TreeNodeEx("Collider", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {



                    switch (currentGameObject->colliderInfo.type) {
                        case Lomus::ColliderShapeType::Box:
                            renderBoxColliderComponent(currentGameObject);
                            break;
                        case Lomus::ColliderShapeType::Sphere:
                            renderSphereColliderComponent(currentGameObject);
                            break;
                        case Lomus::ColliderShapeType::Capsule:
                            renderCapsuleColliderComponent(currentGameObject);
                            break;
                    }

                    ImGui::Text(" ");
                    ImGui::SetNextItemWidth(windowWidth[0] / 10);
                    if (ImGui::Button("Remove Collider")) {
                        currentGameObject->mRigidBody->removeCollider(currentGameObject->colliderInfo.collider);
                        currentGameObject->colliderInfo.hasShape = false;
                    }

                    ImGui::TreePop();
                }
            }
            if (ImGui::BeginPopup("Select a Collider: ")) {

                if (ImGui::BeginMenu(ICON_FA_OBJECT_UNGROUP " Shapes")) {

                if (ImGui::MenuItem(ICON_FA_CUBE " Box")) {
                      sceneManager.addCollisionBoxShape(currentGameObject->id, Vector3(1,1,1), currentGameObject->colliderInfo.offsetTransform);
                }
                if (ImGui::MenuItem(ICON_FA_CIRCLE " Sphere")) {
                    sceneManager.addCollisionSphereShape(currentGameObject->id, 1.0f, currentGameObject->colliderInfo.offsetTransform);
                }
                if (ImGui::MenuItem( "O Capsule")) {
                    sceneManager.addCollisionCapsuleShape(currentGameObject->id, 1.0f, 2.0f, currentGameObject->colliderInfo.offsetTransform);
                }

                ImGui::EndMenu();
                }

                ImGui::EndPopup();
            }

            ImGui::TreePop();
        }





}



void Editor::renderBoxColliderComponent(std::shared_ptr<GameObject> currentGameObject) {
    BoxShape* boxShape = currentGameObject->colliderInfo.boxShape;

    ImGui::Text(ICON_FA_INFO " Shape Type: Box");

    float halfExtentX[1] = {boxShape->getHalfExtents().x};
    float halfExtentY[1] = {boxShape->getHalfExtents().y};
    float halfExtentZ[1] = {boxShape->getHalfExtents().z};
    ImGui::SeparatorTextEx(0, "Half Extents: ", NULL, 0);
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("The size of the Box Collider");
    }


    ImGui::Text("X: "); ImGui::SameLine();
    ImGui::PushID("heX");
    ImGui::DragFloat(" ", halfExtentX, 0.1, 0.01);
    ImGui::PopID();

    ImGui::Text("Y: "); ImGui::SameLine();
    ImGui::PushID("heY");
    ImGui::DragFloat(" ", halfExtentY, 0.1, 0.01);
    ImGui::PopID();

    ImGui::Text("Z: "); ImGui::SameLine();
    ImGui::PushID("heZ");
    ImGui::DragFloat(" ", halfExtentZ, 0.1, 0.01);
    ImGui::PopID();

    boxShape->setHalfExtents(Vector3(halfExtentX[0],halfExtentY[0],halfExtentZ[0]));
}

void Editor::renderSphereColliderComponent(std::shared_ptr<GameObject> currentGameObject) {
    SphereShape* sphereShape = currentGameObject->colliderInfo.sphereShape;

    ImGui::Text(ICON_FA_INFO " Shape Type: Sphere");

    float radius[1] = {sphereShape->getRadius()};
    ImGui::SeparatorText("Radius: ");


    ImGui::Text("Size: "); ImGui::SameLine();
    ImGui::PushID("raX");
    ImGui::DragFloat(" ", radius, 0.1, 0.01);
    ImGui::PopID();

    sphereShape->setRadius(radius[0]);
}

void Editor::renderCapsuleColliderComponent(std::shared_ptr<GameObject> currentGameObject) {
    CapsuleShape* capsuleShape = currentGameObject->colliderInfo.capsuleShape;

    ImGui::Text(ICON_FA_INFO " Shape Type: Capsule");

    float radius[1] = {capsuleShape->getRadius()};
    float height[1] = {capsuleShape->getHeight()};
    ImGui::SeparatorText("Size: ");


    ImGui::Text("Radius: "); ImGui::SameLine();
    ImGui::PushID("raX");
    ImGui::DragFloat(" ", radius, 0.1, 0.01);
    ImGui::PopID();

    ImGui::Text("Height: "); ImGui::SameLine();
    ImGui::PushID("raY");
    ImGui::DragFloat(" ", height, 0.1, 0.01);
    ImGui::PopID();

    capsuleShape->setRadius(radius[0]);
    capsuleShape->setHeight(height[0]);
}

void Editor::renderBillboardModelComponent(std::shared_ptr<GameObject> currentGameObject) {
    std::string filedialog = "OPEN IMAGE";
    if (!currentGameObject->mBillboard.amEmpty) {
        if (ImGui::TreeNodeEx(ICON_FA_OBJECT_GROUP " Billboard", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {
            ImGui::Text(ICON_FA_INFO " Type: "); ImGui::SameLine(); ImGui::Text("Billboard");
            ImGui::Text(" ");
            if (ImGui::TreeNodeEx(ICON_FA_IMAGE " Texture")) {
                ImGui::BeginChild("Logs",ImVec2(oldWindowWidth * 0.21f, oldWindowHeight * 0.21f), true);

                ImGui::Image((void*)(intptr_t)currentGameObject->mBillboard.rawTexture, ImVec2(static_cast<float>(oldWindowWidth * 0.2), static_cast<float>(oldWindowHeight * 0.2)),ImVec2(0, -1), ImVec2( 1, 0));
                ImGui::EndChild();

                if (ImGui::Button("Change Image")) {
                    ImGui::OpenPopup(3);
                }
                ImGui::TreePop();
            }


            ImGui::TreePop();

            ImGui::Text(" ");
            ImGui::Text(ICON_FA_LOCK " Lock Y rotation: "); ImGui::SameLine();
            ImGui::PushID("lyr");
            ImGui::Checkbox(" ", &currentGameObject->mBillboard.lockYRot);
            ImGui::PopID();
            ImGui::Spacing();
            ImGui::Spacing();
            if (ImGui::Button(ICON_FA_TRASH" Delete")) {
                currentGameObject->mBillboard.amEmpty = true;
            }
        }
    }



    if(file_dialog.showFileDialog(3, imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(windowWidth[0] / 2, windowHeight[0] / 2)))
    {
        if (!file_dialog.selected_path.empty()) {
            currentGameObject->mBillboard.swapImage(file_dialog.selected_path);
        }

    }

}

void Editor::manipulateObjectViaGizmo(movableObject& object, Camera& camera) {
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);


    // Transform the matrices to their correct form
    trans = glm::translate(trans, -object.position);
    rot = glm::mat4_cast(object.rotation);
    sca = glm::scale(sca, object.scale);

    glm::mat4 editMatrix = glm::mat4(1.0f) * trans * rot * sca;
    ImGuizmo::Enable(true);

    glm::mat4 cameraView;// = glm::mat4(0.0f);
    glm::mat4 emptyMatrix = glm::mat4(1.0f);

    emptyMatrix = glm::translate(glm::vec3(0, 0, 0));

    ImGuizmo::SetRect(0, 0, oldWindowWidth * 0.75f, windowHeight[0] * 0.65f);
    ImGuizmo::SetDrawlist();
    //ImGuizmo::DrawGrid(glm::value_ptr(camera.view), glm::value_ptr(camera.projection), glm::value_ptr(emptyMatrix), 200.0f);
    ImGuizmo::Manipulate(glm::value_ptr(camera.view),  glm::value_ptr(camera.projection), Editor::currentGizmoState, ImGuizmo::WORLD, glm::value_ptr(editMatrix), nullptr,  nullptr);

    glm::quat newRot;
    glm::vec3 newPos;
    glm::vec3 newScale;
    glm::vec3 skew;
    glm::vec4 Perspective;


    glm::decompose(editMatrix, newScale, newRot, newPos, skew, Perspective);

    object.position.x = -newPos.x;
    object.position.y = -newPos.y ;
    object.position.z = -newPos.z ;

    object.scale = newScale;
    newRot.w = -newRot.w;
    object.rotation = glm::conjugate(newRot);

}

void Editor::renderActiveScene(SceneManager &sceneManager) {
    ImGui::BeginTabBar("SceneOverview");

    if (ImGui::BeginTabItem("General")) {
        ImGui::PushID("Scenename");
        ImGui::Text("Scene Name: "); ImGui::SameLine();
        ImGui::InputText("", &sceneManager.currentScene->name);
        ImGui::PopID();
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Shadows")) {
        ImGui::Spacing();
        ImGui::Text("Shadow Depth Texture:");
        ImTextureID imTexID = (void*)(intptr_t)shadowTexture;

        // Display the texture using ImGui::Image
        ImGui::Image(imTexID, ImVec2(static_cast<float>(windowWidth[0] * 0.1f), static_cast<float>(windowHeight[0] * 0.1f)));

        ImGui::Separator();
        ImGui::Text("Shadow Area: ");
        ImGui::SameLine();

        ImGui::PushID("ShadowArea");
        ImGui::DragFloat(" ", shadowArea, 1.0);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("Shadow Near plane: ");
        ImGui::SameLine();

        ImGui::PushID("Shadow Nearplane");
        ImGui::DragFloat(" ", shadowNearPlane, 1.0);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("Shadow Far plane: ");
        ImGui::SameLine();

        ImGui::PushID("Shadow Farplane");
        ImGui::DragFloat(" ", shadowFarPlane, 1.0);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("Baises:");
        ImGui::SameLine();
        ImGui::PushID("SHADOWBIAS");
        ImGui::DragFloat(" ", baises, 0.0001);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("PCF Samples:");
        ImGui::SameLine();
        ImGui::PushID("SHADOWPCF");
        ImGui::DragFloat(" ", shadowSamples, 0.01f);
        ImGui::PopID();

        shaderList.at(1).Activate();
        shaderList.at(1).setFloatUniform("sBaises", baises[0]);
        shaderList.at(1).setFloatUniform("sampleSize", shadowSamples[0]);



        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
}





void Editor::renderLightProperties(SceneManager& sm, LightManager& lm) {

    if (currentSelectedLight != nullptr) {
        ImGui::Text(" ");
        ImGui::Text("Name: ");
        ImGui::SameLine();
        ImGui::PushID("lightN");
        ImGui::InputText(" ", &currentSelectedLight->name);
        ImGui::PopID();
        ImGui::Text("Type: "); ImGui::SameLine();
        int item_current_2 = currentSelectedLight->lightType - 1;
        ImGui::PushID("lightT");
        ImGui::Combo(" ", &item_current_2, "Direct Light\0Point Light\0");
        ImGui::PopID();
        item_current_2 += 1;
        currentSelectedLight->lightType = item_current_2;

        ImGui::Spacing();
        if (ImGui::Button("Delete Light")) {
            lm.deleteLight(sm.currentScene, currentSelectedLight->name);
            currentSelectedLight = nullptr;
            return;
        }
        ImGui::Spacing();

        ImGui::Text(" ");
        if (ImGui::TreeNodeEx((ICON_FA_GEAR" TransFormation"), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {


            if (currentSelectedLight->lightType == 1) {
                ImGui::Text("Angle: ");
                ImGui::SameLine();
                ImGui::PushID("lightA");
                ImGui::DragFloat3(" ", currentSelectedLight->lightAngle, 0.1f);
                ImGui::PopID();


            }

            if (currentSelectedLight->lightType == 2) {
                float lightPos[3] = {currentSelectedLight->lightPosition_x,currentSelectedLight->lightPosition_y,currentSelectedLight->lightPosition_z};
                ImGui::Text("Position: ");
                ImGui::SameLine();
                ImGui::PushID("LightP");
                ImGui::DragFloat3(" ", lightPos, 0.5f);
                currentSelectedLight->lightPosition_x = lightPos[0];
                currentSelectedLight->lightPosition_y = lightPos[1];
                currentSelectedLight->lightPosition_z = lightPos[2];
                ImGui::PopID();
            }

            ImGui::TreePop();
        }

        ImGui::Text(" ");
        if (ImGui::TreeNodeEx((ICON_FA_LIGHTBULB " Light Component"), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {

            ImGui::Text(" ");
            ImGui::Text("Brightness: ");
            ImGui::PushID("lightI");
            float tli[1] = { currentSelectedLight->lightInten};
            ImGui::DragFloat(" ", tli);
            ImGui::PopID();
            currentSelectedLight->lightInten= tli[0];
            float lcolor[4] = {currentSelectedLight->lightColor_r,currentSelectedLight->lightColor_g,currentSelectedLight->lightColor_b,currentSelectedLight->lightColor_a};
            ImGui::Text("Color: ");
            ImGui::PushID("lightCp");
            ImGui::ColorPicker4("", lcolor);
            ImGui::PopID();
            ImGui::PushID("lightC");
            ImGui::DragFloat4(" ", lcolor);
            ImGui::PopID();

            currentSelectedLight->lightColor_r = lcolor[0];
            currentSelectedLight->lightColor_g = lcolor[1];
            currentSelectedLight->lightColor_b = lcolor[2];
            currentSelectedLight->lightColor_a = lcolor[3];

            ImGui::TreePop();
        }

    }

}



void Editor::createFBO(int width, int height) {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

}

void Editor::prepareFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    // Specify the color of the background
    glClearColor(0,0, 0, 1);
    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Enable depth testing since it's disabled when drawing the framebuffer rectangle
    glEnable(GL_DEPTH_TEST);
}

void Editor::unprepareFrameBuffer() {
    // Bind the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0,0, 0, 1);
}

void Editor::Delete() {
    glDeleteRenderbuffers(1, &RBO);
    glDeleteTextures(1, &texture_id);
    glDeleteFramebuffers(1, & FBO);

    for (auto pair : lightBillboards) {
        delete pair.second;
    }

}

void Editor::resizeFrameBuffer(int newWidth, int newHeight) {
    hasWindowResized = true;
    if (newWidth > 0 && newHeight > 0) {
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, newWidth, newHeight, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, newWidth, newHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    }
}

void Editor::handleInputs(Camera &camera) {
    Lomus::Keyboard& keyboard = Lomus::Keyboard::getInstance();
    if (allowCameraInput()) {
        camera.Speed += ImGui::GetIO().MouseWheel;
    }

    if (keyboard.isKeyPressed(Lomus::Keyboard::R)) {
        currentGizmoState = ImGuizmo::OPERATION::ROTATE;
    }


    if (keyboard.isKeyPressed(Lomus::Keyboard::T)) {
        currentGizmoState = ImGuizmo::OPERATION::TRANSLATE;
    }

    if (keyboard.isKeyPressed(Lomus::Keyboard::Y)) {
        currentGizmoState = ImGuizmo::OPERATION::SCALE;
    }
}

bool Editor::allowCameraInput() {
    float mouseX = ImGui::GetMousePos().x;
    float mouseY = ImGui::GetMousePos().y;
    float sceneViewWidth = windowWidth[0] * 0.75f;
    float sceneViewHeight = windowHeight[0] * 0.65f;

    return (windowWidth[0] > 0 && windowHeight[0] > 0 && mouseX >= 0 && mouseX <= sceneViewWidth && mouseY >= 0 && mouseY <= sceneViewHeight && ImGui::IsMouseDown(ImGuiMouseButton_Right)); // Checks if mouse is inside the scene preview frame
}

bool Editor::isWindowMinized() {
    return !(windowWidth[0] > 0 && windowHeight[0] > 0);
}

bool Editor::isGameRunning() {
    return (playButton.isActive && !pauseButton.isActive);
}

void Editor::prepareGameRuntime(SceneManager& sceneManager) {
    sceneCache.clear();
    mConsole.addConsoleLog("Starting Game Runtime");
    for (auto pair : sceneManager.currentScene->gameObjects) {
        sceneCache.push_back(createBackupOfGameObject(pair.second));
    }
}

void Editor::reloadEditScene(SceneManager& sceneManager) {
    for (backUpObject rollBackData : sceneCache) {
        rollBackGameObject(sceneManager.getGameobject(rollBackData.id), rollBackData);
    }
}

backUpObject Editor::createBackupOfGameObject(std::shared_ptr<GameObject> gameObject) {
    backUpObject newObject;
    newObject.id = gameObject->id;
    newObject.position = gameObject->position;
    newObject.rotation = gameObject->rotation;
    newObject.scale = gameObject->scale;
    return newObject;
}

void Editor::rollBackGameObject(std::shared_ptr<GameObject> gameObject, backUpObject rollBackData) {
    if (gameObject != nullptr) {
        if (gameObject->mRigidBody != nullptr) {
            gameObject->mRigidBody->resetForce();
            gameObject->mRigidBody->resetTorque();
            gameObject->mRigidBody->setAngularVelocity(Vector3(0, 0, 0));
            gameObject->mRigidBody->setLinearVelocity(Vector3(0, 0, 0));

            gameObject->position = rollBackData.position;
            gameObject->rotation = rollBackData.rotation;
            gameObject->scale = rollBackData.scale;
        }


    } else{
        mConsole.addConsoleError("Could not change this gameObject since its a nullptr :(");
    }

}

void Editor::createNewLight(SceneManager &sm, LightManager &lm) {
    mConsole.addConsoleLog("Created new Light Object");
    Lomus::Light newLight = Lomus::Light{
            0, 0, 0,
            1,1, 1, 1,
            5,
            {0, 0, 0},
            2,
            std::string("New Light" + std::to_string(lightCount)),
            false
    };
    lm.createNewLight(sm.currentScene, newLight);
    lightCount++;
    auto* bill = new LomusModelTypes::Billboard();
    bill->load(lightImagePath);
    bill->scale.x = 1;
    bill->scale.y = 2;
    lightBillboards.emplace(lm.lightIdMap.at(sm.currentScene->name).at(std::string("New Light" + std::to_string(lightCount - 1))), bill);
    spdlog::info("GOT HERE");
}

void Editor::renderDebugLightObjects(Camera &camera, Shader& billboardShader) {
    for (auto pair : lightBillboards) {
        pair.second->Render(camera, billboardShader);
    }
    cameraBillboard.Render(camera, billboardShader);
}

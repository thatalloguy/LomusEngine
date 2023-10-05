#include "Editor.h"


void Lomus::Editor::initStlyle() {
    // LomusStyle style from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowPadding = ImVec2(8.199999809265137f, 14.39999961853027f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.6000000238418579f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding = 4.300000190734863f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 0.0f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.900000095367432f;
    style.ScrollbarSize = 11.60000038146973f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize = 9.899999618530273f;
    style.GrabRounding = 2.599999904632568f;
    style.TabRounding = 1.700000047683716f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Left;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1115879490971565f, 0.1115868836641312f, 0.1115880012512207f, 0.9399999976158142f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2000000029802322f, 0.2078431397676468f, 0.2196078449487686f, 0.5400000214576721f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4000000059604645f, 0.4000000059604645f, 0.4000000059604645f, 0.4000000059604645f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1764705926179886f, 0.1764705926179886f, 0.1764705926179886f, 0.6700000166893005f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9372549057006836f, 0.9372549057006836f, 0.9372549057006836f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.2231759428977966f, 0.629969596862793f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8588235378265381f, 0.8588235378265381f, 0.8588235378265381f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.4000000059604645f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4588235318660736f, 0.4666666686534882f, 0.47843137383461f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.4196078479290009f, 0.4196078479290009f, 0.4196078479290009f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.6980392336845398f, 0.3100000023841858f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.6980392336845398f, 0.800000011920929f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.47843137383461f, 0.4980392158031464f, 0.5176470875740051f, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.7176470756530762f, 0.7176470756530762f, 0.7176470756530762f, 0.7799999713897705f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.9098039269447327f, 0.9098039269447327f, 0.9098039269447327f, 0.25f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.8078431487083435f, 0.8078431487083435f, 0.8078431487083435f, 0.6700000166893005f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4588235318660736f, 0.4588235318660736f, 0.4588235318660736f, 0.949999988079071f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.1405809670686722f, 0.1484937220811844f, 0.1545064449310303f, 0.8619999885559082f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.3716774880886078f, 0.4335407316684723f, 0.5064377784729004f, 0.800000011920929f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.3763193488121033f, 0.3806866109371185f, 0.3862661123275757f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.729411780834198f, 0.6000000238418579f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.8666666746139526f, 0.8666666746139526f, 0.8666666746139526f, 0.3499999940395355f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);

}

void Lomus::Editor::Init(SceneManager &sceneManager) {
    initStlyle();
    mConsole.init();
}

void Lomus::Editor::Render(SceneManager &sceneManager,LightManager& lightManager, GLFWwindow* window,Shader& shader, Shader& outlineShader, Camera& camera,  int windowWidth, int windowHeight, EditorMode mode) {
    switch (mode) {
        case EditorMode::debug:
            renderDebugModeData(sceneManager, lightManager, shader, outlineShader, window, camera, windowWidth, windowHeight);

    }
}

void Lomus::Editor::Delete(SceneManager &sceneManager) {
}

void Lomus::Editor::renderDebugModeData(SceneManager &sceneManager,LightManager& lightManager,Shader& shader, Shader& outlineShader, GLFWwindow* window, Camera& camera,  int windowWidth, int windowHeight) {

    if (visible) {
        ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.3, windowHeight * 0.7));
        ImGui::Begin("Editor | Mode: debug");

        ImGui::BeginTabBar("General");

        if (ImGui::BeginTabItem("Lights")) {
            for (int i=0; i < lightManager.placeId; i++) {
                std::string temp = "Light: " + std::to_string(i);

                if (ImGui::TreeNode(temp.c_str())) {

                    ImGui::Text("Position:");
                    ImGui::PushID(temp.c_str());
                    ImGui::DragFloat3("", lightManager.lights[i].lightPosition, 0.5f, 5.0f);
                    ImGui::PopID();

                    ImGui::Spacing();

                    float v[4] = {lightManager.lights[i].lightColor_r,lightManager.lights[i].lightColor_g,lightManager.lights[i].lightColor_b,lightManager.lights[i].lightColor_a};
                    temp = "col" + std::to_string(i);

                    ImGui::Text("Color:");
                    ImGui::PushID(temp.c_str());
                    ImGui::DragFloat4("", v, 0.1f, 0.0f, 1.0f);
                    ImGui::PopID();
                    lightManager.lights[i].lightColor_r = v[0];
                    lightManager.lights[i].lightColor_g = v[1];
                    lightManager.lights[i].lightColor_b = v[2];
                    lightManager.lights[i].lightColor_a = v[3];

                    ImGui::Spacing();

                    temp = "inten" + std::to_string(i);
                    ImGui::Text("Inten");
                    float s[1] = {lightManager.lights[i].lightInten};
                    ImGui::PushID(temp.c_str());
                    ImGui::DragFloat("", s, 0.1f, 0.0f);
                    ImGui::PopID();
                    lightManager.lights[i].lightInten = *s;
                    ImGui::TreePop();
                }
            }
            ImGui::EndTabItem();
        }



        if (ImGui::BeginTabItem("Entities")) {


            Scene& curScene = sceneManager.getCurrentScene();
            string temp = "";
            for (auto& gameObject : curScene.gameObjects) {
                if (ImGui::TreeNode(gameObject.second.name.c_str())) {

                    ImGui::Spacing();
                    ImGui::Text("Position: ");
                    temp = gameObject.second.name + "Pos";
                    ImGui::PushID(temp.c_str());
                    float v[3] = {gameObject.second.position.x, gameObject.second.position.y, gameObject.second.position.z};
                    ImGui::DragFloat3("", v, 0.5f, -20);
                    ImGui::PopID();
                    gameObject.second.position.x = v[0];
                    gameObject.second.position.y = v[1];
                    gameObject.second.position.z = v[2];

                    ImGui::TreePop();
                }
            }


            ImGui::EndTabItem();
        }



        if (ImGui::BeginTabItem("Render")) {

                shader.Activate();
                shader.setFloatUniform("sSamples", shadowSamples[0]);
                shader.setFloatUniform("sBiases", baises[0]);
                shader.setFloatUniform("sOffset", offset[0]);
                shader.setFloatUniform("lAmbient", ambient[0]);
                shader.setFloatUniform("shadowAmbient", sAmbient[0]);
                shader.setIntUniform("shadeLevels", celLevel[0]);
                shader.setIntUniform("useNormalMap", useNM[0]);


                outlineShader.Activate();
                outlineShader.setFloatUniform("thickness", outlineThick[0]);
                outlineShader.setVec4Uniform("color", outlineColor[0], outlineColor[1], outlineColor[2], outlineColor[3]);

            ImGui::Spacing();


            ImGui::Spacing();
            ImGui::Separator();

            ImGui::Text("Shadows: ");
            ImGui::Spacing();
            ImGui::Text("Samples:");
            ImGui::PushID("samp");
            ImGui::DragFloat("",Editor::shadowSamples, 0.1f, 1.0f, 10.0f);
            ImGui::PopID();

            ImGui::Text("Baise:");
            ImGui::PushID("bas");
            ImGui::DragFloat("", Editor::baises, 1.0f, 1.0f, 100.0f);
            ImGui::PopID();

            ImGui::Text("Offset:");
            ImGui::PushID("ofs");
            ImGui::DragFloat("", Editor::offset, 0.5f, 1.0f, 100.0f);
            ImGui::PopID();

            ImGui::Text("Shadow Ambient:");
            ImGui::PushID("sA");
            ImGui::DragFloat("", Editor::sAmbient, 0.01f, 0.01f, 3.0f);
            ImGui::PopID();


            ImGui::Separator();
            ImGui::Spacing();
            ImGui::Text("Ambient");
            ImGui::PushID("am");
            ImGui::DragFloat("", Editor::ambient, 0.01f, 0.01f, 1.0f);
            ImGui::PopID();

            ImGui::Separator();
            ImGui::Spacing();
            ImGui::Text("Toon shader");
            ImGui::Spacing();
            ImGui::Text("Cel Levels");
            ImGui::PushID("cl");
            ImGui::DragInt("", Editor::celLevel, 1, 1, 20);
            ImGui::PopID();
            ImGui::Text("Use Normal Maps");
            ImGui::PushID("uNM");
            ImGui::Checkbox("", Editor::useNM);
            ImGui::PopID();

            ImGui::Spacing();
            ImGui::Text("Outline Width:");
            ImGui::PushID("oT");
            ImGui::DragFloat("", Editor::outlineThick, 0.01f, 0.01f, 1);
            ImGui::PopID();
            ImGui::Text("Outline Color");
            ImGui::PushID("oC");
            ImGui::DragFloat4("", Editor::outlineColor, 0.01f, 0, 1);
            ImGui::PopID();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Console")) {
            mConsole.renderConsole(window, 400, 500, camera, sceneManager, Lomus::ConsoleMode::intergrated);
            ImGui::EndTabItem();
        }



        ImGui::EndTabBar();

        ImGui::End();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && togglePressed) {

            visible = 0;
            togglePressed = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            togglePressed = true;
        }
    } else if (!visible) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && togglePressed) {

            visible = 1;
            togglePressed = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            togglePressed = true;
        }
    }

}

void Editor::setShader(int name, Shader &shader) {
    shaderList.emplace(name, shader);
}

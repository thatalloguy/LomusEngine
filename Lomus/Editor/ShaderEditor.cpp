#include <iostream>
#include "ShaderEditor.h"

Lomus::ShaderEditor::ShaderEditor(): mNodeSystem(VisNodeSys::NodeSystem::getInstance()) {

    printf("GOT HERE\n");
    mNodeSystem.Initialize();
    NodeArea = mNodeSystem.CreateNodeArea();
    NodeArea->SetIsFillingWindow(true);

    testNode = new VisNodeSys::Node();

    testNode->SetName("Test Node 1");
    testNode->AddSocket(new VisNodeSys::NodeSocket(testNode, "EXEC", "in", false));
    testNode->AddSocket(new VisNodeSys::NodeSocket(testNode, "EXEC", "out", true));
    testNode->SetPosition(ImVec2(1280 / 2.0f - testNode->GetSize().x / 2.0, 250));

    testNode2 = new VisNodeSys::Node();

    testNode2->SetName("Test Node 2");
    testNode2->AddSocket(new VisNodeSys::NodeSocket(testNode2, "EXEC", "in", false));
    testNode2->AddSocket(new VisNodeSys::NodeSocket(testNode2, "EXEC", "out", true));
    testNode2->SetPosition(ImVec2(1280 / 2.0f - testNode->GetSize().x / 2.0, 550));


    NodeArea->AddNode(testNode);
    NodeArea->AddNode(testNode2);



    testFloatNode = new LomusNodes::FloatNode();
    testFloatNode->SetPosition(ImVec2(10.0f, 40.0f));

    testFloatNode2 = new LomusNodes::FloatNode();
    testFloatNode2->SetPosition(ImVec2(10.0f, 100.0f));

    testMulNode = new LomusNodes::MulNode();
    testMulNode->SetPosition(ImVec2(400, 400));

    NodeArea->AddNode(testFloatNode);
    NodeArea->AddNode(testFloatNode2);
    NodeArea->AddNode(testMulNode);

}

void Lomus::ShaderEditor::Render() {
    DrawNodeAreaWindow();
}

void Lomus::ShaderEditor::CleanUp() {

}

void Lomus::ShaderEditor::DrawNodeAreaWindow() {


    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(ImVec2(1280, 720));
    static bool ShowDemoWindow = true;
    if (ImGui::Begin("Test Node Editor", &ShowDemoWindow, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
        NodeArea->Update();

    }


    ImGui::End();

    ImGui::Begin("Hello!");

    if (ImGui::Button("Run")) {
        std::cout << testMulNode->GetData() << "\n";
    }

    ImGui::End();

}

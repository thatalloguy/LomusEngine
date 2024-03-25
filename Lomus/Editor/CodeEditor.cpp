#include <iostream>
#include "CodeEditor.h"
/*
Lomus::CodeEditor::CodeEditor(): mNodeSystem(VisNodeSys::NodeSystem::getInstance()) {

    mNodeSystem.Initialize();
    NodeArea = mNodeSystem.CreateNodeArea();
    NodeArea->SetIsFillingWindow(true);
    theBeginNode = new LomusNodes::onStartNode();
    NodeArea->AddNode(theBeginNode);


}

void Lomus::CodeEditor::Render() {
    DrawNodeAreaWindow();
}

void Lomus::CodeEditor::CleanUp() {
    delete NodeArea;
}

void Lomus::CodeEditor::DrawNodeAreaWindow() {


    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(ImVec2(1280, 720));
    static bool ShowDemoWindow = true;
    if (ImGui::Begin("Test Node Editor", &ShowDemoWindow, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
        ImGui::SetWindowFontScale(4.0f);
        NodeArea->Update();
        ImGui::SetWindowFontScale(1.0f);

        if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && Lomus::Keyboard::getInstance().isKeyPressed(Lomus::Keyboard::LSHIFT)) {
            showCreationMenu = true;

        }

        if (Lomus::Keyboard::getInstance().isKeyPressed(Lomus::Keyboard::ESCAPE)) {
            showCreationMenu = false;
        }

        if (showCreationMenu) {
            ImGui::SetNextWindowSize(ImVec2(NodeArea->GetSize().x / 9.0f, 250));
            ImGui::SetNextWindowPos(ImGui::GetMousePos(), ImGuiCond_Appearing);
            ImGui::Begin("Create New Node", NULL, ImGuiWindowFlags_NoCollapse);
            showCreationMenu = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);

            static char searchQuery[256] = "";
            static std::vector<MenuItem> filteredItems;

            ImGui::InputTextWithHint(" ", "Search", searchQuery, IM_ARRAYSIZE(searchQuery));

            if (ImGui::Button("Clear")) {
                searchQuery[0] = '\0';
            }

            FilterMenuItems(searchQuery, filteredItems);

            if (ImGui::BeginMenu("Math")) {
                ImGui::SetItemDefaultFocus();
                for (const auto& item : filteredItems) {
                    if (item.Menu == "Math") {
                        if (ImGui::MenuItem(std::string(std::string(item.label) + " Node").c_str())) {
                            CreateNewNode(const_cast<MenuItem &>(item));
                        }
                    }

                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("TransForms")) {
                for (const auto& item : filteredItems) {
                    if (item.Menu == "TransForms") {
                        if (ImGui::MenuItem(std::string(std::string(item.label) + " Node").c_str())) {
                            CreateNewNode(const_cast<MenuItem &>(item));
                        }
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Actions")) {
                for (const auto& item : filteredItems) {
                    if (item.Menu == "Actions") {
                        if (ImGui::MenuItem(std::string(std::string(item.label) + " Node").c_str())) {
                            CreateNewNode(const_cast<MenuItem &>(item));
                        }
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Logic")) {
                for (const auto& item : filteredItems) {
                    if (item.Menu == "Logic") {
                        if (ImGui::MenuItem(std::string(std::string(item.label) + " Node").c_str())) {
                            CreateNewNode(const_cast<MenuItem &>(item));
                        }
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::End();
        }

    }


    ImGui::End();

    ImGui::Begin("Hello!");

    if (ImGui::Button("Run")) {
        curOut = "Output: ";//  + std::to_string(testMulNode->GetData());
    }
    ImGui::Text(curOut.c_str());

    ImGui::End();

}

void Lomus::CodeEditor::CreateNewNode(CodeEditor::MenuItem& menuItem) {
    // Dunno another fix :shrug:
    LomusNodes::FloatNode* newFNode;
    LomusNodes::MulNode* newMNode;
    LomusNodes::PrintNode* newPNode;

    switch (menuItem.id) {
        case LomusNodeTypes::Add:
            spdlog::info("creating an Add Node");
            newMNode = new LomusNodes::MulNode();
            newMNode->SetPosition(ImGui::GetMousePos());
            NodeArea->AddNode(newMNode);
            break;


        case LomusNodeTypes::Float:
            spdlog::info("creating an Float Node");
            newFNode = new LomusNodes::FloatNode();
            newFNode->SetPosition(ImGui::GetMousePos());
            NodeArea->AddNode(newFNode);
            break;

        case LomusNodeTypes::Print:
            spdlog::info("creating an Print Node");
            newPNode = new LomusNodes::PrintNode();
            newPNode->SetPosition(ImGui::GetMousePos());
            NodeArea->AddNode(newPNode);
            break;
    }
}
*/
std::vector<std::string> splitStdString(const std::string& s, char seperator)
{
    std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}

int getNodeIdViaPinId(int pinId, std::vector<Lomus::CodeEditor::Node>& allnodes) {
    for (auto nodes : allnodes) {
        for (auto in : nodes.inputPins) {
            if (in.id == pinId) {
                return nodes.id;
            }
        }
        for (auto in : nodes.outputPins) {
            if (in.id == pinId) {
                return nodes.id;
            }
        }
    }
}

int getPinPosArrayViaId(int pinId, std::vector<Lomus::CodeEditor::pins>& pins) { // pos as in position in array
    int i = 0;
    for (auto pin : pins) {
        if (pin.id == pinId) {
            return i;
        }
        i++;
    }
    return -1;
}



int getNodeArrayPosViaId(int nodeId, std::vector<Lomus::CodeEditor::Node>& allnodes) { // pos as in position in array
    int i = 0;
    for (auto nodes : allnodes) {
        if (nodes.id == nodeId) {
            return i;
        }
        i++;
    }
    return -1;
}

Lomus::CodeEditor::Link* getLinkViaPinId(int pinId,  std::vector<Lomus::CodeEditor::Link> allLinks) {
    for (auto link : allLinks) {
        if (link.start_pin == pinId || link.end_pin == pinId) {
            return &link;
        }
    }
    return nullptr;
}


void noLogic(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Lomus::CodeEditor::Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks) {

}

void toStringNode(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Lomus::CodeEditor::Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks) {
    int AinputNodeId = getNodeIdViaPinId(getLinkViaPinId(inputPin[0].id, allLinks)->start_pin, allNodes);
    auto inputNode = allNodes[getNodeArrayPosViaId(AinputNodeId, allNodes)];
    inputNode.logic(&inputNode, inputNode.inputPins, inputNode.outputPins, allNodes, allLinks);

    node->outputPins[0].data.s_output = std::to_string(inputNode.outputPins[getPinPosArrayViaId(getLinkViaPinId(inputPin[0].id, allLinks)->start_pin, inputNode.outputPins)].data.f_output);
}

void addNodeOutput(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Lomus::CodeEditor::Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks) {
    int AinputNodeId = getNodeIdViaPinId(getLinkViaPinId(inputPin[0].id, allLinks)->start_pin, allNodes);
    auto AinputNode = allNodes[getNodeArrayPosViaId(AinputNodeId, allNodes)];

    int BinputNodeId = getNodeIdViaPinId(getLinkViaPinId(inputPin[1].id, allLinks)->start_pin, allNodes);
    auto BinputNode = allNodes[getNodeArrayPosViaId(BinputNodeId, allNodes)];

    // Always update the connected data
    AinputNode.logic(&AinputNode, AinputNode.inputPins, AinputNode.outputPins, allNodes, allLinks);
    BinputNode.logic(&BinputNode, BinputNode.inputPins, BinputNode.outputPins, allNodes, allLinks);

    node->outputPins[0].data.f_output = AinputNode.outputPins[getPinPosArrayViaId(getLinkViaPinId(inputPin[0].id, allLinks)->start_pin, AinputNode.outputPins)].data.f_output + BinputNode.outputPins[getPinPosArrayViaId(getLinkViaPinId(inputPin[1].id, allLinks)->start_pin, BinputNode.outputPins)].data.f_output;
}

void printNodeLogic(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Lomus::CodeEditor::Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks) {
    int inputNodeId = getNodeIdViaPinId(getLinkViaPinId(inputPin[1].id, allLinks)->start_pin, allNodes);

    auto inputNode = allNodes[getNodeArrayPosViaId(inputNodeId, allNodes)];

    // First make it do its logic
    inputNode.logic(&inputNode, inputNode.inputPins, inputNode.outputPins, allNodes, allLinks);
    spdlog::info("[PrintNode]:" + inputNode.outputPins[getPinPosArrayViaId(getLinkViaPinId(inputPin[1].id, allLinks)->start_pin, inputNode.outputPins)].data.s_output);
}

void onStartNodeLogic(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Lomus::CodeEditor::Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks) {

    auto link = getLinkViaPinId(outputPin[0].id, allLinks);
    if (link != nullptr) {
        int linkid = link->end_pin;
        int outNodeId = getNodeIdViaPinId(linkid, allNodes);


        auto outNode = allNodes[getNodeArrayPosViaId(outNodeId, allNodes)];
        outNode.logic(&outNode, outNode.inputPins, outNode.outputPins, allNodes, allLinks);

    } else {
        spdlog::error("Nothing connected to start!");
    }

}

void getTransFormNodeOutput(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Lomus::CodeEditor::Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks) {
    int gameObjectInputNodeId = getNodeIdViaPinId(getLinkViaPinId(inputPin[0].id, allLinks)->start_pin, allNodes);
    auto AinputNode = allNodes[getNodeArrayPosViaId(gameObjectInputNodeId, allNodes)];

    node->outputPins[0].data.f_output = std::any_cast<Lomus::CodeEditor::Gameobject>(AinputNode.outputPins[0].data.customClass).x;
    node->outputPins[1].data.f_output = std::any_cast<Lomus::CodeEditor::Gameobject>(AinputNode.outputPins[0].data.customClass).y;
}

void setTransFormNodeOutput(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Lomus::CodeEditor::Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks) {
    int gameObjectInputNodeId = getNodeIdViaPinId(getLinkViaPinId(inputPin[0].id, allLinks)->start_pin, allNodes);
    auto AinputNode = allNodes[getNodeArrayPosViaId(gameObjectInputNodeId, allNodes)];

    //node->outputPins[0].data.f_output; //std::any_cast<Lomus::CodeEditor::Gameobject>(AinputNode.outputPins[0].data.customClass).x;
    //node->outputPins[1].data.f_output; //std::any_cast<Lomus::CodeEditor::Gameobject>(AinputNode.outputPins[0].data.customClass).y;
}



void Lomus::CodeEditor::createAddNode() {
    Node addNode;
    addNode.id = getNextNode();
    addNode.name = "Add ";
    addNode.description = "Adds input a and b together";
    addNode.catagory = NodeCatagory::Math;
    addNode.logic = addNodeOutput;
    addNode.inputPins.push_back(pins{getNextPin(), "A", "float", pinTypes::Input, addNode.id});
    addNode.inputPins.push_back(pins{getNextPin(), "B", "float",pinTypes::Input, addNode.id});
    addNode.outputPins.push_back(pins{getNextPin(), "out", "float",pinTypes::Output, addNode.id});

    addNode.outputPins[0].data.type = Float;

    mNodes.push_back(addNode);
}

void customVarNodeRender(Lomus::CodeEditor::Node* node) {
    ImGui::PushID(node->id);
    ImGui::SetNextItemWidth(ImGui::CalcTextSize(std::to_string(node->outputPins[0].data.f_output).c_str()).x);
    ImGui::InputFloat(" ", &node->outputPins[0].data.f_output);
    ImGui::PopID();
}

void customStringNodeRender(Lomus::CodeEditor::Node* node) {
    ImGui::PushID(node->id);
    ImGui::SetNextItemWidth(ImGui::CalcTextSize(std::to_string(node->outputPins[0].data.f_output).c_str()).x);
    char buffer[256];  // Buffer to hold the entered text
    strncpy_s(buffer, node->outputPins[0].data.s_output.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0;
    ImGui::InputText(" ", buffer, sizeof(buffer));
    node->outputPins[0].data.s_output = buffer;
    ImGui::PopID();
}

void Lomus::CodeEditor::createVarNode() {
    Node varNode;
    varNode.id = getNextNode();
    varNode.name = "Float ";
    varNode.description = "A Float variable";
    varNode.catagory = NodeCatagory::Variables;
    varNode.logic = noLogic;
    varNode.customRenderFunction = customVarNodeRender;
    varNode.useCustomRenderFunc = true;
    varNode.outputPins.push_back(pins{getNextPin(), "out", "float",pinTypes::Output, varNode.id});


    varNode.outputPins[0].data.type = outPutDataType::Float;
    varNode.outputPins[0].data.f_output = 4.0f;

    mNodes.push_back(varNode);


}

void Lomus::CodeEditor::createGetGONode() {
    Node getNode;
    getNode.id = getNextNode();
    getNode.name = "Get Game Object ";
    getNode.description = "Returns wanted Game Object";
    getNode.catagory = NodeCatagory::Logic;
    getNode.logic = noLogic;
    getNode.outputPins.push_back(pins{getNextPin(), " " ICON_FA_CUBE, "gameObject",pinTypes::Output, getNode.id});

    getNode.outputPins[0].data.type = Custom;
    getNode.outputPins[0].data.customClass = testobject;

    mNodes.push_back(getNode);
}

void Lomus::CodeEditor::createToStringNode() {
    Node varNode;
    varNode.id = getNextNode();
    varNode.name = "To String ";
    varNode.description = "Converts a float to a string";
    varNode.catagory = NodeCatagory::Utils;
    varNode.logic = toStringNode;
    varNode.outputPins.push_back(pins{getNextPin(), "string", "string",pinTypes::Output, varNode.id});
    varNode.inputPins.push_back(pins{getNextPin(), "float", "float",pinTypes::Input, varNode.id});


    varNode.outputPins[0].data.type = outPutDataType::String;
    varNode.outputPins[0].data.s_output = "Empty";

    mNodes.push_back(varNode);
}

void Lomus::CodeEditor::createGetTransFormNode() {
    Node getNode;
    getNode.id = getNextNode();
    getNode.name = "Get TransForm ";
    getNode.description = "Returns transForm of a Game Object";
    getNode.catagory = NodeCatagory::Math;
    getNode.logic = getTransFormNodeOutput;
    getNode.outputPins.push_back(pins{getNextPin(), "x", "float",pinTypes::Output, getNode.id});
    getNode.outputPins.push_back(pins{getNextPin(), "y", "float",pinTypes::Output, getNode.id});
    getNode.inputPins.push_back(pins{getNextPin(), ICON_FA_CUBE, "gameObject",pinTypes::Input, getNode.id});
    getNode.outputPins[0].data.type = Float;
    getNode.outputPins[1].data.type = Float;
    getNode.outputPins[1].data.f_output = 0.0f;
    getNode.outputPins[1].data.f_output = 0.0f;

    mNodes.push_back(getNode);
}

void Lomus::CodeEditor::createSetTransFormNode() {
    Node getNode;
    getNode.id = getNextNode();
    getNode.name = "Set TransForm ";
    getNode.description = "changes transForm of a Game Object to the x and y value";
    getNode.catagory = NodeCatagory::Math;
    getNode.logic = setTransFormNodeOutput;
    getNode.inputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event", pinTypes::Input, getNode.id});
    getNode.inputPins.push_back(pins{getNextPin(), ICON_FA_CUBE, "gameObject",pinTypes::Input, getNode.id});
    getNode.inputPins.push_back(pins{getNextPin(), "x", "float",pinTypes::Input, getNode.id});
    getNode.inputPins.push_back(pins{getNextPin(), "y", "float",pinTypes::Input, getNode.id});
    getNode.outputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event",pinTypes::Output, getNode.id});

    mNodes.push_back(getNode);
}

void Lomus::CodeEditor::createPrintNode() {

    Node printNode;

    printNode.id = getNextNode();
    printNode.name = "Print String";
    printNode.description = "Prints String to console";
    printNode.catagory = NodeCatagory::Logic;
    printNode.logic = printNodeLogic;
    printNode.inputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event", pinTypes::Input, printNode.id});
    printNode.inputPins.push_back(pins{getNextPin(), "string", "string",pinTypes::Input, printNode.id});
    printNode.outputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event",pinTypes::Output, printNode.id});


    printNode.outputPins[0].data.type = outPutDataType::Event;
    mNodes.push_back(printNode);
}


void Lomus::CodeEditor::createIfNode() {
    Node ifNode;
    ifNode.id = getNextNode();
    ifNode.name = "If statement";
    ifNode.description = "Calls next connected node if condition is met";
    ifNode.catagory = NodeCatagory::Conditions;
    ifNode.logic = noLogic;
    ifNode.outputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event",pinTypes::Output, ifNode.id});
    ifNode.inputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event",pinTypes::Input, ifNode.id});
    ifNode.inputPins.push_back(pins{getNextPin(), "cond", "condition",pinTypes::Input, ifNode.id});

    ifNode.outputPins[0].data.type = outPutDataType::Event;

    mNodes.push_back(ifNode);
}


void Lomus::CodeEditor::createStringNode() {
    Node stringNode;
    stringNode.id = getNextNode();
    stringNode.name = "String ";
    stringNode.description = "A String";
    stringNode.catagory = NodeCatagory::Variables;
    stringNode.logic = noLogic;
    stringNode.customRenderFunction = customStringNodeRender;
    stringNode.useCustomRenderFunc = true;
    stringNode.outputPins.push_back(pins{getNextPin(), "out", "string",pinTypes::Output, stringNode.id});


    stringNode.outputPins[0].data.type = outPutDataType::String;
    stringNode.outputPins[0].data.s_output = "A String";

    mNodes.push_back(stringNode);
}


Lomus::CodeEditor::Node &Lomus::CodeEditor::generateNodeViaCode(std::string input) {
    Node outNode;

    std::vector<std::string> code = splitStdString(input, ' ');
    std::cout << "Type = " << code[0] << "\n";

    std::unordered_map<std::string, NodeCatagory> NodeConvertlist = {
            {"float", NodeCatagory::Math},
            {"int",   NodeCatagory::Math},
            {"vec3",  NodeCatagory::Math},

            {"void",  NodeCatagory::Logic},
            {"bool",  NodeCatagory::Conditions},
    };


    return outNode;
}



Lomus::CodeEditor::CodeEditor() {

    testobject.x = 10.0f;
    testobject.y = 12.0f;
    testobject.width = 100.0f;
    testobject.height = 100.0f;




    onStartNode.id = getNextNode();
    onStartNode.name = ICON_FA_PLAY " On Start";
    onStartNode.description = "This Event gets called once";
    onStartNode.catagory = NodeCatagory::Special;
    onStartNode.logic = onStartNodeLogic;
    onStartNode.outputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event",pinTypes::Output, onStartNode.id});


    onUpdateNode.id = getNextNode();
    onUpdateNode.name =  ICON_FA_FORWARD_FAST " On Update";
    onUpdateNode.description ="This Event gets called every tick";
    onUpdateNode.catagory = NodeCatagory::Special;
    onUpdateNode.logic = onStartNodeLogic;
    onUpdateNode.outputPins.push_back(pins{getNextPin(), ICON_FA_ARROW_RIGHT, "event",pinTypes::Output, onUpdateNode.id});
    std::string testCode = "void testFunction(Event event, String str, Float fl);";
    generateNodeViaCode(testCode);
    ///mNodes.push_back(generateNodeViaCode(testCode));


    mNodes.push_back(onStartNode);
    mNodes.push_back(onUpdateNode);
}

void Lomus::CodeEditor::Render() {


    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(800, 720));
    ImGui::Begin("Code Nodes", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

    ImNodes::BeginNodeEditor();

    for (auto& node : mNodes) {
        renderNode(node);
    }

    for (auto& link : mLinks) {
        ImNodes::Link(link.id, link.start_pin, link.end_pin);
    }



    ImNodes::MiniMap(.1f, ImNodesMiniMapLocation_BottomLeft);

    if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
        ImGui::OpenPopup("New Node");
    }

    if (ImGui::BeginPopup("New Node")) {
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Text("Create A new Node");

        if (ImGui::BeginMenu("Math")) {
            if (ImGui::MenuItem("Add Node  ")) {
                createAddNode();
            }

            if (ImGui::MenuItem("Set TransForm Node  ")) {
                createSetTransFormNode();
            }
            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Action")) {

            if (ImGui::MenuItem("Get TransForm Node  ")) {
                createGetTransFormNode();
            }
            if (ImGui::MenuItem("Get GameObject Node  ")) {
                createGetGONode();
            }
            if (ImGui::MenuItem("Print String Node  ")) {
                createPrintNode();
            }
            if (ImGui::MenuItem("To String Node  ")) {
                createToStringNode();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Conditions")) {
            if (ImGui::MenuItem("If Statement Node  ")) {
                createIfNode();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Types")) {
            if (ImGui::MenuItem("String Node  ")) {
                createStringNode();
            }

            if (ImGui::MenuItem("Float Node  ")) {
                createVarNode();
            }

            ImGui::EndMenu();
        }


        ImGui::EndPopup();
    }

    ImNodes::EndNodeEditor();
    Link link;
    if (ImNodes::IsLinkCreated(&link.start_pin, &link.end_pin)) {
        if (getPin(link.start_pin).valueType == getPin(link.end_pin).valueType) {

            link.id = linkIdCounter++;
            mLinks.push_back(link);
        } else {
            spdlog::error("Unvalid");
        }
    }

    if (Keyboard::getInstance().isKeyPressed(Lomus::Keyboard::DELETE)) {
        int i = 0;
        for (auto link : mLinks) {
            if (ImNodes::IsLinkSelected(link.id)) {
                mLinks.erase(mLinks.begin() + i);
            }
            i++;
        }
    }

    int link_id;
    if (ImNodes::IsLinkDestroyed(&link_id))
    {
        auto it = std::remove_if(mLinks.begin(), mLinks.end(),
                                 [link_id](const Link& link) { return link.id == link_id; });

        mLinks.erase(it, mLinks.end());
    }


    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(800,0));
    ImGui::SetNextWindowSize(ImVec2(1270 - 800, 720));
    ImGui::Begin("Console");

    if (ImGui::Button("Start")) {
        onStartNode.logic(&onStartNode, onStartNode.inputPins, onStartNode.outputPins, mNodes, mLinks);
    }

    ImGui::SameLine(); ImGui::Checkbox(" Update", &runProgram);

    if (runProgram) {
        onUpdateNode.logic(&onUpdateNode, onUpdateNode.inputPins, onUpdateNode.outputPins, mNodes, mLinks);
    }

    // render game Object
    ImGui::Text("Game Object Position: "); ImGui::SameLine(); ImGui::Text("X - "); ImGui::SameLine(); ImGui::Text(std::to_string(testobject.x).c_str()); ImGui::SameLine(); ImGui::Text(" | Y - "); ImGui::SameLine(); ImGui::Text(std::to_string(testobject.y).c_str());

    ImGui::SetCursorPosX(1000);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() * 3.0f);
    ImGui::GetWindowDrawList()->AddRectFilled(
            ImGui::GetCursorPos() + ImVec2(testobject.x , testobject.y),
            ImGui::GetCursorPos() + ImVec2(testobject.x + testobject.width , testobject.y + testobject.height ),
            IM_COL32(255, 255, 255, 255)
    );

    ImGui::End();
}

void Lomus::CodeEditor::CleanUp() {

}

void Lomus::CodeEditor::renderNode(Lomus::CodeEditor::Node &node) {
    ImNodes::PushColorStyle(ImNodesCol_TitleBar, node.catagory);
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, node.catagory);
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, node.catagory);
    ImNodes::BeginNode(node.id);
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(node.name.c_str());
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(node.description.c_str());
    }

    ImNodes::EndNodeTitleBar();

    // Render input pins
    for (const auto& inputPin : node.inputPins) {
        ImNodes::BeginInputAttribute(inputPin.id);
        ImGui::Text(inputPin.name);
        ////ImGui::SameLine(); ImGui::Text(std::to_string(inputPin.id).c_str());
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("%s", inputPin.valueType.c_str());
        }
        ImNodes::EndInputAttribute();
    }
    if (node.useCustomRenderFunc) {
        node.customRenderFunction(&node);
    }


    // Render output pins
    ImGui::Indent(80);
    for (const auto& outputPin : node.outputPins) {

        ImNodes::BeginOutputAttribute(outputPin.id);
        ImGui::Text(outputPin.name);
        ////ImGui::SameLine(); ImGui::Text(std::to_string(outputPin.id).c_str());
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("%s", outputPin.valueType.c_str());
        }
        ImNodes::EndOutputAttribute();
    }
    ImGui::Indent(0);


    ImNodes::EndNode();
    ImNodes::PopColorStyle();
}

Lomus::CodeEditor::Node &Lomus::CodeEditor::getNode(int id) {
    for (auto node : mNodes) {
        if (node.id == id) {
            return node;
        }
    }
}

Lomus::CodeEditor::pins Lomus::CodeEditor::getPin(int id) {
    for (auto nodes : mNodes) {
        for (auto in : nodes.inputPins) {
            if (in.id == id) {
                return in;
            }
        }
        for (auto in : nodes.outputPins) {
            if (in.id == id) {
                return in;
            }
        }
    }
}

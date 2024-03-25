#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../Thirdparty/imgui/imgui.h"
#include "../../Thirdparty/imgui/imnodes.h"
#include "../../Thirdparty/imgui/IconsFontAwesome6.h"
#include "../Input/Keyboard.h"
#include <spdlog/spdlog.h>
#include <any>


namespace Lomus {


    class CodeEditor {



    public:

        struct Gameobject {
            float x, y;
            float width, height;
        };

        CodeEditor();
        void Render();
        void CleanUp();

        enum outPutDataType {
            Float = 0,
            String = 1,
            Event = 2,
            Custom = 3,
            Boolean = 4
        };

        struct outPutData {
            float f_output;
            std::string s_output = "EMPTY";
            bool isEvent = false;
            outPutDataType type;
            std::any customClass;
        };

        enum NodeCatagory{
            Math = IM_COL32(200,20,20,255),
            Variables = IM_COL32(100,10,255,255),
            Special = IM_COL32(200,10,255,255),
            Logic = IM_COL32(10, 230, 150, 255),
            Utils = IM_COL32(10, 150, 250, 255),
            Conditions = IM_COL32(255, 196, 0, 255)
        };

        enum pinTypes {
            Input = 0,
            Output = 1
        };

        struct Link {
            int id;
            int start_pin, end_pin;
        };


        struct pins {
            int id = -1;
            const char* name;
            std::string valueType;
            int type;
            int parentId;
            outPutData data;
        };

        struct Node {
            int id = -1;
            std::string name;
            std::string description;
            NodeCatagory catagory;


            std::function<void(Lomus::CodeEditor::Node* node, std::vector<Lomus::CodeEditor::pins>& inputPin, std::vector<Lomus::CodeEditor::pins>& outputPin, std::vector<Node> allNodes, std::vector<Lomus::CodeEditor::Link> allLinks)> logic;
            std::function<void(Lomus::CodeEditor::Node* node)> customRenderFunction;
            bool useCustomRenderFunc = false;
            std::vector<pins> inputPins;
            std::vector<pins> outputPins;
        };

        int nodeIdCounter = -1;
        int pinIdCounter = 0;
        int linkIdCounter = 0;

        int getNextNode() {nodeIdCounter++; return nodeIdCounter;};
        int getNextPin()  {pinIdCounter++; return pinIdCounter;};

        CodeEditor::Node& getNode(int id);
        CodeEditor::pins getPin(int id);

        Gameobject testobject;


        std::vector<Node> mNodes;
        std::vector<Link> mLinks;


    private:


        void renderNode(Node& node);

        void createAddNode();
        void createVarNode();
        void createGetGONode();
        void createGetTransFormNode();
        void createSetTransFormNode();
        void createToStringNode();
        void createPrintNode();
        void createStringNode();
        void createIfNode();

        Node& generateNodeViaCode(std::string input);

        bool runProgram = false;


        Node onStartNode;
        Node onUpdateNode;
    };


}

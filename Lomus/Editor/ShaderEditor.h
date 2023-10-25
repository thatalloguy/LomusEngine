#pragma once
#include "../../Thirdparty/visualNodeSystem/VisualNodeSystem.h"
#include "Nodes.h"

namespace Lomus {



    class ShaderEditor {

    public:
        ShaderEditor();
        void Render();
        void CleanUp();

    private:
        VisNodeSys::NodeSystem& mNodeSystem;
        VisNodeSys::NodeArea* NodeArea = nullptr;

        void DrawNodeAreaWindow();

        // Test
        VisNodeSys::Node* testNode = nullptr;
        VisNodeSys::Node* testNode2 = nullptr;
        LomusNodes::FloatNode* testFloatNode;
        LomusNodes::FloatNode* testFloatNode2;
        LomusNodes::MulNode* testMulNode;
    };


}

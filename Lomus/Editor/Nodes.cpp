#include <iostream>
#include "Nodes.h"

using namespace VisNodeSys;
using namespace LomusNodes;

bool FloatNode::isRegistered = []()
{
    NODE_FACTORY.RegisterNodeType("FloatNode",
                                  []() -> Node* {
                                      return new FloatNode();
                                  },

                                  [](const Node& CurrentNode) -> Node* {
                                      const FloatNode& NodeToCopy = static_cast<const FloatNode&>(CurrentNode);
                                      return new FloatNode(NodeToCopy);
                                  }
    );

    return true;
}();

FloatNode::FloatNode() : Node()
{
    Type = "FloatNode";

    SetStyle(DEFAULT);

    SetSize(ImVec2(250, 120));
    SetName("FloatNode");

    TitleBackgroundColor = ImColor(128, 117, 208);
    TitleBackgroundColorHovered = ImColor(135, 145, 255);

    AddSocket(new NodeSocket(this, "FLOAT", "out", true));
}

FloatNode::FloatNode(const FloatNode& Src) : Node(Src)
{
    Data = Src.Data;

    SetStyle(DEFAULT);

}

void FloatNode::SetStyle(NODE_STYLE NewValue)
{

    // Do nothing. We don't want to change style
}

void FloatNode::Draw()
{
    Node::Draw();

    float Zoom = ParentArea->GetZoomFactor();
    ImVec2 NodePosition = ImGui::GetCursorScreenPos();
    ImVec2 NodeSize = GetSize();

    ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 50.0f) * Zoom);
    float v[1] = {Data};

    ImGui::PushID(this->GetID().c_str());
    ImGui::SetNextItemWidth(this->GetSize().x * 0.6);
    ImGui::InputFloat(" ", v, 0.1f);
    ImGui::PopID();
    Data = v[0];

    ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 90.0f) * Zoom);

}

void FloatNode::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, NODE_SOCKET_EVENT EventType)
{
    Node::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

float FloatNode::GetData()
{
    return Data;
}

bool FloatNode::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{

    if (!Node::CanConnect(OwnSocket, CandidateSocket, nullptr))
        return false;

    return true;
}


// Multiply Node --

bool MulNode::isRegistered = []()
{
    NODE_FACTORY.RegisterNodeType("FloatNode",
                                  []() -> Node* {
                                      return new FloatNode();
                                  },

                                  [](const Node& CurrentNode) -> Node* {
                                      const MulNode& NodeToCopy = static_cast<const MulNode&>(CurrentNode);
                                      return new MulNode(NodeToCopy);
                                  }
    );

    return true;
}();

MulNode::MulNode() : Node()
{
    Type = "MulNode";

    SetStyle(DEFAULT);

    SetSize(ImVec2(250, 120));
    SetName("Multiply ");

    TitleBackgroundColor = ImColor(204, 0, 0);
    TitleBackgroundColorHovered = ImColor(204, 10, 10);

    AddSocket(new NodeSocket(this, "FLOAT", "out", true));
    AddSocket(new NodeSocket(this, "INFLOAT", "A", false));
    AddSocket(new NodeSocket(this, "INFLOAT", "B", false));
}

MulNode::MulNode(const MulNode& Src) : Node(Src)
{
    Data = Src.Data;

    SetStyle(DEFAULT);

}

void MulNode::SetStyle(NODE_STYLE NewValue)
{

    // Do nothing. We don't want to change style
}

void MulNode::Draw()
{
    Node::Draw();

    float Zoom = ParentArea->GetZoomFactor();
    ImVec2 NodePosition = ImGui::GetCursorScreenPos();
    ImVec2 NodeSize = GetSize();

    ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 50.0f) * Zoom);

    ImGui::Text(" + ");

    ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 90.0f) * Zoom);

}

void MulNode::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, NODE_SOCKET_EVENT EventType)
{
    if (EventType == CONNECTED) {
        if (OwnSocket->GetName() == "A") {
            a = reinterpret_cast<FloatNode*>(ConnectedSocket->GetParent());
        } else {
            b = reinterpret_cast<FloatNode*>(ConnectedSocket->GetParent());
        }

    } else if (EventType == DISCONNECTED) {
        if (OwnSocket->GetName() == "A") {
            a = nullptr;
        } else {
            b = nullptr;
        }
    }

    Node::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

float MulNode::GetData()
{
    if (a != nullptr && b != nullptr) {
        return a->GetData() + b->GetData();
    } else {
        return 0.0f;
    }
}

bool MulNode::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{
    if (OwnSocket->GetType() == "INFLOAT" && CandidateSocket->GetType() == "FLOAT") {
        return true;
    }
    return false;


}


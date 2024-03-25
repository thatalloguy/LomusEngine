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

    AddSocket(new NodeSocket(this, "FLOAT", "f", true));
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


    ImGui::PushID(this->GetID().c_str());
    ImGui::SetNextItemWidth(this->GetSize().x * 0.6 * Zoom);
    ImGui::InputFloat(" ", &Data, 0.1f);
    ImGui::PopID();

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
    NODE_FACTORY.RegisterNodeType("MulNode",
                                  []() -> Node* {
                                      return new MulNode();
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
    //bCouldBeDestroyed = false;
    SetStyle(DEFAULT);

    SetSize(ImVec2(250, 120));
    SetName("Add ");

    TitleBackgroundColor = ImColor(204, 0, 0);
    TitleBackgroundColorHovered = ImColor(204, 10, 10);

    AddSocket(new NodeSocket(this, "FLOAT", "f", true));
    AddSocket(new NodeSocket(this, "INFLOAT", "f", false));
    AddSocket(new NodeSocket(this, "INFLOAT", "f", false));
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

    ImGui::SetCursorScreenPos(NodePosition + NodeSize / 2 * Zoom);

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




// On Start node --

bool onStartNode::isRegistered = []()
{
    NODE_FACTORY.RegisterNodeType("OnStartNode",
                                  []() -> Node* {
                                      return new onStartNode();
                                  },

                                  [](const Node& CurrentNode) -> Node* {
                                      const onStartNode& NodeToCopy = static_cast<const onStartNode&>(CurrentNode);
                                      return new FloatNode; // disable Copying
                                  }
    );

    return true;
}();

onStartNode::onStartNode() : Node()
{
    Type = "OnStart";
    //bCouldBeDestroyed = false;
    SetStyle(DEFAULT);

    SetSize(ImVec2(150, 75));
    SetName("On Start ");

    TitleBackgroundColor = ImColor(104, 204, 255);
    TitleBackgroundColorHovered = ImColor(154, 204, 255);

    AddSocket(new NodeSocket(this, "EVENT", "=>", true));
}

onStartNode::onStartNode(const onStartNode& Src) : Node(Src)
{
    Data = Src.Data;
    SetStyle(DEFAULT);
}

void onStartNode::SetStyle(NODE_STYLE NewValue)
{

    // Do nothing. We don't want to change style
}

void onStartNode::Draw()
{
    Node::Draw();

    float Zoom = ParentArea->GetZoomFactor();
    ImVec2 NodePosition = ImGui::GetCursorScreenPos();
    ImVec2 NodeSize = GetSize();


}

void onStartNode::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, NODE_SOCKET_EVENT EventType)
{
    if (EventType == CONNECTED) {


    } else if (EventType == DISCONNECTED) {

    }

    Node::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

bool onStartNode::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{
    if (OwnSocket->GetType() == "EVENT" && CandidateSocket->GetType() == "INEVENT") {
        return true;
    }
    return false;


}



// Print To text Node


bool PrintNode::isRegistered = []()
{
    NODE_FACTORY.RegisterNodeType("PrintNode",
                                  []() -> Node* {
                                      return new PrintNode();
                                  },

                                  [](const Node& CurrentNode) -> Node* {
                                      const PrintNode& NodeToCopy = static_cast<const PrintNode&>(CurrentNode);
                                      return new PrintNode(NodeToCopy);
                                  }
    );

    return true;
}();

PrintNode::PrintNode() : Node()
{
    Type = "PrintNode";

    SetStyle(DEFAULT);

    SetSize(ImVec2(250, 120));
    SetName("PrintNode");

    TitleBackgroundColor = ImColor(100, 208, 108);
    TitleBackgroundColorHovered = ImColor(110, 208, 108);

    AddSocket(new NodeSocket(this, "EVENT", "=>", false));
    AddSocket(new NodeSocket(this, "EVENT", "=>", true));
    AddSocket(new NodeSocket(this, "PRINT", "Output", false));
}

PrintNode::PrintNode(const PrintNode& Src) : Node(Src)
{
    SetStyle(DEFAULT);
}

void PrintNode::SetStyle(NODE_STYLE NewValue)
{
}

void PrintNode::Draw()
{
    Node::Draw();

    float Zoom = ParentArea->GetZoomFactor();
    ImVec2 NodePosition = ImGui::GetCursorScreenPos();
    ImVec2 NodeSize = GetSize();

}

void PrintNode::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, NODE_SOCKET_EVENT EventType)
{
    Node::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}


bool PrintNode::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{

    if (CandidateSocket->GetType() == "FLOAT" || CandidateSocket->GetType() == "String" || CandidateSocket->GetType() == "INT")
        return true;

    if (OwnSocket->GetType() == "EVENT" && CandidateSocket->GetType() == "EVENT")
        return true;

    return false;
}

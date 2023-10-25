#include "../../Thirdparty/visualNodeSystem/VisualNodeSystem.h"

using namespace VisNodeSys;

namespace LomusNodes {


    class FloatNode : public VisNodeSys::Node {
        friend class NodeFactory;
        static bool isRegistered;

        float Data = 0.0f;

        bool CanConnect(VisNodeSys::NodeSocket* OwnSocket, VisNodeSys::NodeSocket* CandidateSocket, char** MsgToUser);
        void SocketEvent(VisNodeSys::NodeSocket* OwnSocket, VisNodeSys::NodeSocket* ConnectedSocket, VisNodeSys::NODE_SOCKET_EVENT EventType);

        // Make it private
        void SetStyle(VisNodeSys::NODE_STYLE NewValue);
    public:
        FloatNode();
        FloatNode(const FloatNode& Src);

        void Draw();
        float GetData();
    };

    class MulNode : public VisNodeSys::Node {
        friend class NodeFactory;
        static bool isRegistered;

        float Data = 0.0f;

        FloatNode* a = nullptr;
        FloatNode* b = nullptr;

        bool CanConnect(VisNodeSys::NodeSocket* OwnSocket, VisNodeSys::NodeSocket* CandidateSocket, char** MsgToUser);
        void SocketEvent(VisNodeSys::NodeSocket* OwnSocket, VisNodeSys::NodeSocket* ConnectedSocket, VisNodeSys::NODE_SOCKET_EVENT EventType);

        // Make it private
        void SetStyle(VisNodeSys::NODE_STYLE NewValue);
    public:
        MulNode();
        MulNode(const MulNode& Src);

        void Draw();
        float GetData();
    };


}
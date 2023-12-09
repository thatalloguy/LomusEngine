#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace Lomus {

    class Atomus {

    public:

        enum PassType {
            depth = GL_DEPTH_COMPONENT,
            RGBA16f = GL_RGBA16F,
            RGBA = GL_RGBA
        };

        void createNewRenderPass(const char* name, PassType renderType );

    private:

    };


}
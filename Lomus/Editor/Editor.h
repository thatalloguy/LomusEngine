#include "../../Thirdparty/imgui/imgui.h"
#include "../Core/SceneManager.h"


namespace Lomus {

    class Editor {


    public:
        void Init(SceneManager& sceneManager);

        void Delete(SceneManager& sceneManager);

        void Render(SceneManager& sceneManager, int windowWidth, int windowHeight);

    private:

        void renderObjectListTab(SceneManager& sceneManager, int windowWidth, int windowHeight);
        void initStlyle();


    };

}

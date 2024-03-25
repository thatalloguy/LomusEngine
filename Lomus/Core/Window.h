#include <string>
#include <GLFW/glfw3.h>


struct WindowCreationInfo {
    std::string title            = "a Lomus project";
    int width                    = 1920;
    int height                   = 1080;
    bool autoSizeWindowToMonitor = false;
    bool fullscreen              = false;
    bool resizable               = true;
};

class Window {

public:
    Window(WindowCreationInfo& creationInfo);

    bool shouldWindowClose();

    void update();

    void cleanUp();

    float getTime();

    bool isFullscreen();
    void setFullScreen();

    bool isWindowFocused();


private:
    unsigned int width;
    unsigned int height;
    std::string windowTitle;

    GLFWwindow* rawWindow;

};


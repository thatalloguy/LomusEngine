//
// Created by allos on 3/25/2024.
//

#include "Window.h"

Window::Window(WindowCreationInfo &creationInfo) {

    if (!creationInfo.autoSizeWindowToMonitor) {
        width = creationInfo.width;
        height = creationInfo.height;
    } else {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        width  = mode->width;
        height = mode->height;
    }



}

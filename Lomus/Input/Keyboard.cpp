
#include "Keyboard.h"

Lomus::Keyboard &Lomus::Keyboard::getInstance() {
    static Lomus::Keyboard instance;
    return instance;
}

bool Lomus::Keyboard::isKeyPressed(Lomus::Keyboard::Key key) {
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

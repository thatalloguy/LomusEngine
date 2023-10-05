
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace Lomus {


    class Keyboard {

        enum Key{
            Q = GLFW_KEY_Q,
            W = GLFW_KEY_W,
            E = GLFW_KEY_E,
            R = GLFW_KEY_R,
            T = GLFW_KEY_T,
            Y = GLFW_KEY_Y,
            U = GLFW_KEY_U,
            I = GLFW_KEY_I,
            O = GLFW_KEY_O,
            A = GLFW_KEY_A,
            S = GLFW_KEY_S,
            D = GLFW_KEY_D,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            Z = GLFW_KEY_Z,
            X = GLFW_KEY_X,
            C = GLFW_KEY_C,
            V = GLFW_KEY_V,
            B = GLFW_KEY_B,
            N = GLFW_KEY_N,
            M = GLFW_KEY_M,

            COMMA = GLFW_KEY_COMMA,
            LSHIFT = GLFW_KEY_LEFT_SHIFT,
            LCONTROL = GLFW_KEY_LEFT_CONTROL,
            RSHIFT = GLFW_KEY_RIGHT_SHIFT,
            RCONTROL = GLFW_KEY_RIGHT_CONTROL,

            SPACE = GLFW_KEY_SPACE,
            ESCAPE = GLFW_KEY_ESCAPE,

            ONE = GLFW_KEY_1,
            TWO = GLFW_KEY_2,
            THREE = GLFW_KEY_3,
            FOUR = GLFW_KEY_4,
            FIVE = GLFW_KEY_5,
            SIX = GLFW_KEY_6,
            SEVEN = GLFW_KEY_7,
            EIGHT = GLFW_KEY_8,
            NINE = GLFW_KEY_9,
            ZERO = GLFW_KEY_0,

            BACKSPACE = GLFW_KEY_BACKSPACE,
            ENTER = GLFW_KEY_ENTER,
            TAB = GLFW_KEY_TAB,

            F1 = GLFW_KEY_F1,
            F2 = GLFW_KEY_F2,
            F3 = GLFW_KEY_F3,
            F4 = GLFW_KEY_F4,
            F5 = GLFW_KEY_F5,
            F6 = GLFW_KEY_F6,
            F7 = GLFW_KEY_F7,
            F8 = GLFW_KEY_F8,
            F9 = GLFW_KEY_F9,
            F10 = GLFW_KEY_F10,
            F11 = GLFW_KEY_F11,
            F12 = GLFW_KEY_F12
        };


    protected:
        Keyboard() = default;

    public:
        static Keyboard& getInstance();


        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;
        Keyboard& operator=(Keyboard&&) = delete;


        bool isKeyPressed(GLFWwindow* window, Key key);


    private:

    };

}

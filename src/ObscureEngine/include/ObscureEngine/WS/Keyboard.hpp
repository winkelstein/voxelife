#pragma once
#include "Core.h"
#include "Window.h"

namespace ObscureEngine
{
    namespace WS
    {
        class Keyboard
        {
        public:
            enum class VirtualKey
            {
                Backspace = GLFW_KEY_BACKSPACE,
                Tab = GLFW_KEY_TAB,
                Enter = GLFW_KEY_ENTER,
                LeftShift = GLFW_KEY_LEFT_SHIFT,
                RightShift = GLFW_KEY_RIGHT_SHIFT,
                LeftCtrl = GLFW_KEY_LEFT_CONTROL,
                RightCtrl = GLFW_KEY_RIGHT_CONTROL,
                LeftAlt = GLFW_KEY_LEFT_ALT,
                RightAlt = GLFW_KEY_RIGHT_ALT,
                Pause = GLFW_KEY_PAUSE,
                CapsLock = GLFW_KEY_CAPS_LOCK,
                ESC = GLFW_KEY_ESCAPE,
                Space = GLFW_KEY_SPACE,
                PageUp = GLFW_KEY_PAGE_UP,
                PageDown = GLFW_KEY_PAGE_DOWN,
                End = GLFW_KEY_END,
                Home = GLFW_KEY_HOME,
                Left = GLFW_KEY_LEFT,
                Up = GLFW_KEY_UP,
                Right = GLFW_KEY_RIGHT,
                Down = GLFW_KEY_DOWN,
                PrintScreen = GLFW_KEY_PRINT_SCREEN,
                Insert = GLFW_KEY_INSERT,
                Delete = GLFW_KEY_DELETE,
                N0 = GLFW_KEY_0,
                N1 = GLFW_KEY_1,
                N2 = GLFW_KEY_2,
                N3 = GLFW_KEY_3,
                N4 = GLFW_KEY_4,
                N5 = GLFW_KEY_5,
                N6 = GLFW_KEY_6,
                N7 = GLFW_KEY_7,
                N8 = GLFW_KEY_8,
                N9 = GLFW_KEY_9,
                A = GLFW_KEY_A,
                B = GLFW_KEY_B,
                C = GLFW_KEY_C,
                D = GLFW_KEY_D,
                E = GLFW_KEY_E,
                F = GLFW_KEY_F,
                G = GLFW_KEY_G,
                H = GLFW_KEY_H,
                I = GLFW_KEY_I,
                J = GLFW_KEY_J,
                K = GLFW_KEY_K,
                L = GLFW_KEY_L,
                M = GLFW_KEY_M,
                N = GLFW_KEY_N,
                O = GLFW_KEY_O,
                P = GLFW_KEY_P,
                Q = GLFW_KEY_Q,
                R = GLFW_KEY_R,
                S = GLFW_KEY_S,
                T = GLFW_KEY_T,
                U = GLFW_KEY_U,
                V = GLFW_KEY_V,
                W = GLFW_KEY_W,
                X = GLFW_KEY_X,
                Y = GLFW_KEY_Y,
                Z = GLFW_KEY_Z,
                LeftSuper = GLFW_KEY_LEFT_SUPER,
                RightSuper = GLFW_KEY_RIGHT_SUPER,
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
                F12 = GLFW_KEY_F12,
                F13 = GLFW_KEY_F13,
                F14 = GLFW_KEY_F14,
                F15 = GLFW_KEY_F15,
                F16 = GLFW_KEY_F16,
                F17 = GLFW_KEY_F17,
                F18 = GLFW_KEY_F18,
                F19 = GLFW_KEY_F19,
                F20 = GLFW_KEY_F20,
                F21 = GLFW_KEY_F21,
                F22 = GLFW_KEY_F22,
                F23 = GLFW_KEY_F23,
                F24 = GLFW_KEY_F24,
                NumLock = GLFW_KEY_NUM_LOCK,
            };

        public:
            inline static bool is_button_pressed(const Window &win, const VirtualKey key);
            inline static bool is_button_released(const Window &win, const VirtualKey key);
        };
    }
}

bool ObscureEngine::WS::Keyboard::is_button_pressed(const Window &win, const VirtualKey key)
{
    int state = glfwGetKey(win.__get_native_handler(), (int)key);
    return state == GLFW_PRESS;
}

bool ObscureEngine::WS::Keyboard::is_button_released(const Window &win, const VirtualKey key)
{
    int state = glfwGetKey(win.__get_native_handler(), (int)key);
    return state == GLFW_RELEASE;
}
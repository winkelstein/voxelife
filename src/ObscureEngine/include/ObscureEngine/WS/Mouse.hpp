#pragma once
#include "Core.h"
#include "Window.h"

namespace ObscureEngine
{
    namespace WS
    {
        class Mouse
        {
        public:
            enum class MouseButton
            {
                Left = GLFW_MOUSE_BUTTON_LEFT,
                Right = GLFW_MOUSE_BUTTON_RIGHT,
                Middle = GLFW_MOUSE_BUTTON_MIDDLE,
            };

        public:
            inline static bool isButtonPressed(const Window &win, const MouseButton button);
            inline static bool isButtonReleased(const Window &win, const MouseButton button);
            inline static Position position(const Window &win);

            inline static void position(const Window &win, const Position pos);

            inline static void visibility(const Window &win, bool state);
        };
    }
}

bool ObscureEngine::WS::Mouse::isButtonPressed(const Window &win, const MouseButton button)
{
    int state = glfwGetMouseButton(win.__get_native_handler(), (int)button);
    return state == GLFW_PRESS;
}

bool ObscureEngine::WS::Mouse::isButtonReleased(const Window &win, const MouseButton button)
{
    int state = glfwGetMouseButton(win.__get_native_handler(), (int)button);
    return state == GLFW_RELEASE;
}

ObscureEngine::WS::Position ObscureEngine::WS::Mouse::position(const Window &win)
{
    double xpos, ypos;
    glfwGetCursorPos(win.__get_native_handler(), &xpos, &ypos);
    Size win_size = win.size();
    if (xpos < 0 || xpos > win_size.width || ypos < 0 || ypos > win_size.height)
        return Position(0, 0);
    return Position(xpos, ypos);
}

void ObscureEngine::WS::Mouse::position(const Window &win, const Position pos)
{
    glfwSetCursorPos(win.__get_native_handler(), pos.x, pos.y);
}

void ObscureEngine::WS::Mouse::visibility(const Window &win, bool state)
{
    if (state)
        glfwSetInputMode(win.__get_native_handler(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(win.__get_native_handler(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
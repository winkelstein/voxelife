#pragma once
#include "Core.h"
#include "Window.h"

namespace Engine
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

bool Engine::WS::Mouse::isButtonPressed(const Window &win, const MouseButton button)
{
    int state = glfwGetMouseButton(win.__get_native_handler(), (int)button);
    return state == GLFW_PRESS;
}

bool Engine::WS::Mouse::isButtonReleased(const Window &win, const MouseButton button)
{
    int state = glfwGetMouseButton(win.__get_native_handler(), (int)button);
    return state == GLFW_RELEASE;
}

Engine::WS::Position Engine::WS::Mouse::position(const Window &win)
{
    double xpos, ypos;
    glfwGetCursorPos(win.__get_native_handler(), &xpos, &ypos);
    Size win_size = win.size();
    if (xpos < 0 || xpos > win_size.width || ypos < 0 || ypos > win_size.height)
        return Position(0, 0);
    return Position(xpos, ypos);
}

void Engine::WS::Mouse::position(const Window &win, const Position pos)
{
    Size win_size = win.size();
    if (pos.x > 0 && pos.y > 0 && pos.x < win_size.width && pos.y < win_size.width)
        glfwSetCursorPos(win.__get_native_handler(), pos.x, pos.x);
}

void Engine::WS::Mouse::visibility(const Window &win, bool state)
{
    if (state)
        glfwSetInputMode(win.__get_native_handler(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(win.__get_native_handler(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
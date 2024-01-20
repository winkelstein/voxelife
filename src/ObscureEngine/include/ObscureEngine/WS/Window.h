#pragma once
#include <string>
#include <queue>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Event.hpp"

namespace ObscureEngine
{
    namespace WS
    {
        class Window
        {
        private:
            GLFWwindow *window;
            bool isWorking;

            std::queue<Event> events;

        public:
            Window(std::string window_name, int width, int height);
            ~Window();

        public:
            void swap_buffers();
            void poll_event(Event &ev);

        public:
            inline bool isOpen() { return !glfwWindowShouldClose(this->window); }

        public:
            inline GLFWwindow *__get_native_handler() const { return this->window; }
            inline Size size() const;
            inline Position position() const;
            inline void position(const Position position);
            inline void close();
        };
    }
}

ObscureEngine::WS::Size ObscureEngine::WS::Window::size() const
{
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    return Size(width, height);
}

ObscureEngine::WS::Position ObscureEngine::WS::Window::position() const
{
    int x, y;
    glfwGetWindowPos(this->window, &x, &y);
    return Position(x, y);
}

void ObscureEngine::WS::Window::position(const Position position)
{
    glfwSetWindowPos(this->window, position.x, position.y);
}

void ObscureEngine::WS::Window::close()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}
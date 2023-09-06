#pragma once
#include <string>
#include <queue>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Event.hpp"

namespace Engine
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
            void swapBuffers();
            void pollEvent(Event &ev);

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

Engine::WS::Size Engine::WS::Window::size() const
{
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    return Size(width, height);
}

Engine::WS::Position Engine::WS::Window::position() const
{
    int x, y;
    glfwGetWindowPos(this->window, &x, &y);
    return Position(x, y);
}

void Engine::WS::Window::position(const Position position)
{
    glfwSetWindowPos(this->window, position.x, position.y);
}

void Engine::WS::Window::close()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}
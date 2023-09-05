#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{
    namespace WS
    {
        class Window
        {
        private:
            GLFWwindow *window;

        public:
            Window(std::string window_name, int width, int height);
            ~Window();

        public:
            void swapBuffers();
            void pollEvent();

        public:
            bool isOpen();
        };
    }
}
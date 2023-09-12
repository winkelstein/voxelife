#include "../include/ObscureEngine/WS/Window.h"
#include <stdexcept>

Engine::WS::Window::Window(std::string window_name, int width, int height)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    this->window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    if (this->window == nullptr)
        throw std::runtime_error("Failed to create GLFW window");
    glfwMakeContextCurrent(this->window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Engine::WS::Window::~Window()
{
    glfwTerminate();
}

void Engine::WS::Window::swapBuffers()
{
    glfwSwapBuffers(this->window);
}

void Engine::WS::Window::pollEvent(Event &ev)
{
    glfwPollEvents();
}
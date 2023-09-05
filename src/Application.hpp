#pragma once
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/WS/Window.h"
#include "Engine/GLTK/Shader.h"
#include "Engine/Logger.h"
#include "Engine/Screen.h"
#include "Engine/FPSCounter.h"

using Engine::FPSCounter;
using Engine::Logger;
using Engine::Screen;
using Engine::gltk::Shader;
using Engine::WS::Size;
using Engine::WS::Window;

class Application
{
private:
    std::unique_ptr<Window> window;
    std::unique_ptr<Screen> screen;
    std::shared_ptr<Shader> shader;
    Logger logger;

public:
    Application();
    ~Application();

    void run();

private:
    static void _debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char *message, const void *classptr);
    void draw();
    void window_init(std::string name, int width, int height);
    void assets_init();
};

void Application::_debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char *message, const void *classptr)
{
    Logger *logger = (Engine::Logger *)classptr;

    Logger::severity sev;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        sev = Logger::severity::high;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        sev = Logger::severity::medium;
        break;
    case GL_DEBUG_SEVERITY_LOW:
        sev = Logger::severity::low;
        break;
    default:
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        sev = Logger::severity::notification;
        break;
    }
    *logger << Logger::message("OpenGL", message, sev);
}

Application::Application()
{
    try
    {
        this->window_init("Biolife", 800, 600);
    }
    catch (std::exception &e)
    {
        this->logger << Logger::message("Window System (WS)", e.what());
    }

    this->logger << Logger::message("Window System (WS)", "Window has been successfully created");

    try
    {
        this->assets_init();
    }
    catch (std::exception &e)
    {
        this->logger << Logger::message("Assets", e.what());
    }
    this->logger << Logger::message("Assets", "assets has been successfully initialized");

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(Application::_debugfunc, &this->logger);
}

void Application::window_init(std::string name, int width, int height)
{
    this->window = std::unique_ptr<Window>(new Window(name, width, height));
    this->screen = std::unique_ptr<Screen>(new Screen(Size(width, height)));
}

void Application::assets_init()
{
}

Application::~Application()
{
}

void Application::run()
{
    FPSCounter counter;
    while (this->window->isOpen())
    {
        counter.start();
        this->window->pollEvent();

        draw();

        this->window->swapBuffers();
        glClearColor(135.0 / 255.0f, 206.0 / 255.0f, 235.0 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        this->logger.flush();
        counter.stop();
    }
}

void Application::draw()
{
}
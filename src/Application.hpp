#pragma once
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/GLTK/Shader.h"
#include "Engine/FPSCounter.h"

#include "Engine/EngineApp.h"

using Engine::FPSCounter;
using Engine::gltk::Shader;

class Application : Engine::EngineApp
{
public:
    Application();
    ~Application();

    void run() override;

private:
    void draw();
    void assets_init();
};

Application::Application() : Engine::EngineApp("Biolife", 800, 600, 0, 0)
{
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
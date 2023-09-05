#pragma once
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ObscureEngine/GLTK/Shader.h>
#include <ObscureEngine/FPSCounter.h>

#include <ObscureEngine/EngineApp.h>
#include <ObscureEngine/Importer/ShaderImporter.h>
#include <ObscureEngine/Logger.h>

using Engine::FPSCounter;
using Engine::Logger;
using Engine::gltk::Shader;

class Application : public Engine::EngineApp
{
public:
    Application();
    ~Application();

    void run() override;

private:
    void draw() override;
    void assets_init();
};

Application::Application() : Engine::EngineApp("Biolife", 800, 600, 0, 0)
{
    try
    {
        this->assets_init();
    }
    catch (std::exception &e)
    {
        this->logger << Logger::message("Assets", e.what());
    }
    this->logger << Logger::message("Assets", "Assets has been successfully loaded");
}

void Application::assets_init()
{
    using namespace Engine::Importer;
    ShaderImporter shader_importer;
    shader_importer.add(ShaderImporter::ShaderType::vertex, "../shaders/default/vertex.glsl");
    shader_importer.add(ShaderImporter::ShaderType::fragment, "../shaders/default/fragment.glsl");

    auto shader = shader_importer.import();
    this->logger << Logger::message("Assets", "Default shader has been imported successfully");
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
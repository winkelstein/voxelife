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
#include <ObscureEngine/WS/Keyboard.hpp>
#include <ObscureEngine/WS/Mouse.hpp>
#include <ObscureEngine/Assets.h>

#include <ObscureEngine/Voxel.h>
#include <ObscureEngine/Physics/Core.h>

#ifdef _RELEASE
#define SHADER_PATH std::string("shaders/")
#else
#define SHADER_PATH std::string("../shaders/")
#endif // _DEBUG

using Engine::Assets;
using Engine::FPSCounter;
using Engine::Logger;
using Engine::gltk::Shader;

class Application : public Engine::EngineApp
{
private:
    Assets assets;

public:
    Application();
    ~Application();

    void run() override;

private:
    void draw() override;
    void handle_event() override;
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
    auto shader_data = shader_importer.import(SHADER_PATH + "/default/");
    std::string shader_name = shader_data.first;

    this->assets.store(shader_name, shader_data.second);
    this->logger << Logger::message("Assets", shader_name + " shader has been imported successfully");
}

Application::~Application()
{
}

void Application::run()
{
    Engine::WS::Event ev;
    FPSCounter counter;

    std::shared_ptr<Shader> default_shader = this->assets.get<std::shared_ptr<Shader>>("default");
    Engine::Voxel grass(glm::vec4(0.24, 0.46, 0.23, 1.0));
    Engine::Voxel tree(glm::vec4(101.0 / 255.0, 67 / 255.0, 33 / 255.0, 1.0));
    Engine::Voxel leaves(glm::vec4(0.0, 1.0, 0.0, 1.0));
    grass.position(glm::vec3(0.0f, -3.0f, 0));
    tree.position(glm::vec3(0.0f, -1.45, 0));
    leaves.position(glm::vec3(0.0f, -0.5, 0));

    grass.size(glm::vec3(15.0f, 0.1f, 15.0f));
    tree.size(glm::vec3(0.5, 3.0, 0.5));
    leaves.size(glm::vec3(2.0, 0.25, 0.1));

    // grass.rotate(glm::vec3(1.0, 0.0, 0.0), glm::vec3(30.0, 0.0, 0.0));

    while (this->window->isOpen())
    {
        counter.start();
        this->window->pollEvent(ev);

        this->handle_event();
        this->player->process(counter.ticks());
        this->screen->onUpdateCamera(this->player->camera());

        this->screen->push(&grass, *default_shader);
        this->screen->push(&tree, *default_shader);
        this->screen->push(&leaves, *default_shader);

        draw();

        if (Engine::WS::Keyboard::isButtonPressed(*this->window, Engine::WS::Keyboard::VirtualKey::ESC))
            this->window->close();

        this->window->swapBuffers();
        glClearColor(135.0 / 255.0f, 206.0 / 255.0f, 235.0 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->logger.flush();

        counter.stop();
    }
}

void Application::draw()
{
    this->screen->render();
}

void Application::handle_event()
{
    this->player->onMouseInput(*this->window);
    Engine::WS::Mouse::position(*this->window, Engine::WS::Position(this->window->size().width / 2.0, this->window->size().height / 2.0));
    this->player->onKeyboardInput(*this->window);
}
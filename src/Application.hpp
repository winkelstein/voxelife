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

#include <ObscureEngine/Importer/ModelImporter.h>

const std::string SHADER_PATH = "shaders/";

using ObscureEngine::Assets;
using ObscureEngine::FPSCounter;
using ObscureEngine::Logger;
using ObscureEngine::gltk::Shader;

class Application : public ObscureEngine::EngineApp
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

Application::Application() : ObscureEngine::EngineApp("Voxelife", 800, 600, 0, 0)
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
    using namespace ObscureEngine::Importer;
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
    using ObscureEngine::Importer::ModelImporter;
    using ObscureEngine::WS::Event;
    using ObscureEngine::WS::Keyboard;

    Event ev;
    FPSCounter counter;

    std::shared_ptr<Shader> default_shader = this->assets.get<std::shared_ptr<Shader>>("default");
    ObscureEngine::Voxel grass0(glm::vec4(sin(0), 0.46, 0.23, 1.0));

    ModelImporter modelImporter;

    auto t = modelImporter.import("models/deer");

    auto model = t.second;

    default_shader->bind();
    while (this->window->isOpen())
    {
        counter.start();
        this->window->poll_event(ev);

        this->handle_event();
        this->player->process(counter.ticks());
        this->screen->on_update_camera(this->player->camera());

        this->screen->push(&grass0, *default_shader);
        this->screen->push(model.get(), *default_shader);

        draw();

        if (Keyboard::is_button_pressed(*this->window, Keyboard::VirtualKey::ESC))
            this->window->close();

        this->window->swap_buffers();
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
    using ObscureEngine::WS::Mouse;
    using ObscureEngine::WS::Position;

    this->player->on_mouse_input(*this->window);
    Mouse::position(*this->window, Position(this->window->size().width / 2.0, this->window->size().height / 2.0));
    this->player->on_keyboard_input(*this->window);
}
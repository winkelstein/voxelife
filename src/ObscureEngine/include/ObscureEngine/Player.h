#pragma once
#include "Camera.h"
#include "WS/Window.h"
#include "WS/Mouse.hpp"
#include "WS/Keyboard.hpp"

namespace Engine
{
    class Player
    {
    private:
        Camera m_camera;

        float speed;
        glm::vec3 velocity;

        float sensitive;

    private:
        void move(glm::vec3 velocity);

    public:
        Player() : speed(5.0), sensitive(0.1), velocity(glm::vec3(0.0)) {}

    public:
        virtual void onMouseInput(const WS::Window &win);
        virtual void onKeyboardInput(const WS::Window &win);

        virtual void process(double ticks);

    public:
        inline const Engine::Camera &camera() const { return this->m_camera; }
    };
}
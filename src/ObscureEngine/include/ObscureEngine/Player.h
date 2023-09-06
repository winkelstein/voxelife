#pragma once
#include "Camera.h"
#include "WS/Window.h"
#include "WS/Mouse.hpp"
#include "WS/Keyboard.hpp"

#define TICK_COEFF 120

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
        Player();

    public:
        void onMouseInput(const WS::Window &win);
        void onKeyboardInput(const WS::Window &win);

        void process(double ticks);

    public:
        inline const Engine::Camera &camera() const { return this->m_camera; }
    };
}
#pragma once
#include "Camera.h"
#include "WS/Window.h"
#include "WS/Mouse.hpp"
#include "WS/Keyboard.hpp"

namespace ObscureEngine
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
        Player() : speed(5.0), velocity(glm::vec3(0.0)), sensitive(0.1) {}

    public:
        virtual void on_mouse_input(const WS::Window &win);
        virtual void on_keyboard_input(const WS::Window &win);

        virtual void process(double ticks);

    public:
        inline const Camera &camera() const { return this->m_camera; }
    };
}
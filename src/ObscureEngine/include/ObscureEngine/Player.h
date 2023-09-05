#pragma once
#include "Camera.h"

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
        // TODO: implement void onMouseInput();
        // TODO: implement void onKeyboardInput();

        void process(double ticks);

    public:
        inline const Engine::Camera &camera() const { return this->m_camera; }
    };
}
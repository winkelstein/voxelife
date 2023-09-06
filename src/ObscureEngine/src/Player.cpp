#include "../include/ObscureEngine/Player.h"
#include "../include/ObscureEngine/Physics/Core.h"

void Engine::Player::move(glm::vec3 velocity)
{
    glm::vec3 position = this->m_camera.position();
    glm::vec3 front = this->m_camera.front();

    // front.y = 0.0;

    position += glm::normalize(front) * velocity.x;
    position += glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0))) * velocity.z;
    position += glm::normalize(glm::cross(front, glm::cross(front, glm::vec3(0.0, 1.0, 0.0)))) * (-velocity.y);

    this->m_camera.position(position);
}

void Engine::Player::onMouseInput(const Engine::WS::Window &win)
{
    using Engine::WS::Mouse;

    static float pitch, yaw;

    float xoff = ((int64_t)Mouse::position(win).x - (int64_t)(win.size().width / 2.0));
    float yoff = ((int64_t)(win.size().height / 2.0) - (int64_t)Mouse::position(win).y);

    yaw += xoff * this->sensitive;
    pitch += yoff * this->sensitive;

    if (pitch > 85.0)
        pitch = 85.0;
    else if (pitch < -85.0)
        pitch = -85.0;

    this->m_camera.rotate(glm::radians(yaw), glm::radians(pitch));
}

void Engine::Player::onKeyboardInput(const Engine::WS::Window &win)
{
    using Engine::WS::Keyboard;

    this->velocity.x = ((1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::W) + (-1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::S))));
    this->velocity.z = ((1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::D) + (-1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::A))));
}

void Engine::Player::process(double ticks)
{
    float speed = this->speed * ticks / Physics::constants::TICK_COEFF;

    this->move(speed * this->velocity);
}
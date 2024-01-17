#include "../include/ObscureEngine/Player.h"
#include "../include/ObscureEngine/Physics/Core.h"

void ObscureEngine::Player::move(glm::vec3 velocity)
{
    glm::vec3 position = this->m_camera.position();
    glm::vec3 front = this->m_camera.front();

    // front.y = 0.0;

    position += glm::normalize(front) * velocity.x;
    position += glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0))) * velocity.z;
    // position += glm::normalize(glm::cross(front, glm::cross(front, glm::vec3(0.0, 1.0, 0.0)))) * (-velocity.y);
    position += glm::vec3(0.0, 1.0, 0.0) * velocity.y;

    this->m_camera.position(position);
}

void ObscureEngine::Player::onMouseInput(const ObscureEngine::WS::Window &win)
{
    using ObscureEngine::WS::Mouse;

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

void ObscureEngine::Player::onKeyboardInput(const ObscureEngine::WS::Window &win)
{
    using ObscureEngine::WS::Keyboard;

    this->velocity.x = ((1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::W) + (-1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::S))));
    this->velocity.z = ((1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::D) + (-1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::A))));
    this->velocity.y = ((1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::Space)) + (-1.0 * Keyboard::isButtonPressed(win, Keyboard::VirtualKey::LeftCtrl)));

    if (Keyboard::isButtonPressed(win, Keyboard::VirtualKey::LeftShift))
        this->velocity *= 2;
}

void ObscureEngine::Player::process(double ticks)
{
    float speed = this->speed * ticks / Physics::constants::TICK_COEFF;

    this->move(speed * this->velocity);
}
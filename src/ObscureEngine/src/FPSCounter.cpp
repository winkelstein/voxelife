#include "../include/ObscureEngine/FPSCounter.h"

Engine::FPSCounter::FPSCounter() : m_ticks(0.1) {}

void Engine::FPSCounter::start()
{
    this->time = std::chrono::high_resolution_clock::now();
}

void Engine::FPSCounter::stop()
{
    auto end = std::chrono::high_resolution_clock::now();

    this->m_ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(end - this->time).count();
}
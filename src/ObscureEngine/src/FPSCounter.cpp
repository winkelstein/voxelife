#include "../include/ObscureEngine/FPSCounter.h"

ObscureEngine::FPSCounter::FPSCounter() : m_ticks(0.1) {}

void ObscureEngine::FPSCounter::start()
{
    this->time = std::chrono::high_resolution_clock::now();
}

void ObscureEngine::FPSCounter::stop()
{
    auto end = std::chrono::high_resolution_clock::now();

    this->m_ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(end - this->time).count();
}
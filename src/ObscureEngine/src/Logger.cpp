#include "../include/ObscureEngine/Logger.h"
#include <iostream>
#include <iomanip>
#include <fstream>

#define END "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

void ObscureEngine::Logger::flush()
{
    while (!this->qMessages.empty())
    {
        this->out(this->qMessages.front());
        this->qMessages.pop();
    }
}

void ObscureEngine::Logger::out(const message &msg)
{
    std::tm now = this->currentTime();

    std::lock_guard<std::recursive_mutex> lock(this->mtx);
    static std::ofstream outputfile("debug.log");

#ifdef _WIN32
    if (msg.sev == severity::high)
        MessageBoxA(nullptr, msg.body.c_str(), msg.header.c_str(), MB_ICONERROR);
#endif

    switch (msg.sev)
    {
    case severity::high:
        std::cout << RED;
        break;
    case severity::medium:
    case severity::low:
        std::cout << YELLOW;
        break;
    case severity::notification:
        std::cout << GREEN;
        break;
    }

    std::cout << "[" << std::setw(2) << std::setfill('0') << now.tm_hour << ":" << std::setw(2) << std::setfill('0') << now.tm_min << ":" << std::setw(2) << std::setfill('0') << now.tm_sec << " " << msg.header << "]: ";
    std::cout << END;
    std::cout << msg.body << std::endl;
    outputfile << "[" << std::setw(2) << std::setfill('0') << now.tm_hour << ":" << std::setw(2) << std::setfill('0') << now.tm_min << ":" << std::setw(2) << std::setfill('0') << now.tm_sec << " " << msg.header << "]: " << msg.body << std::endl;
}
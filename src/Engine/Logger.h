#pragma once
#pragma warning(disable : 4996)

#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <ctime>

#define END "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

namespace Engine
{
    class Logger
    {
    public:
        enum class severity
        {
            high = 3,
            medium = 2,
            low = 1,
            notification = 0
        };

        struct message
        {
            std::string header;
            std::string body;
            severity sev;

            message(std::string header, std::string body, severity sev = severity::notification)
            {
                this->header = header;
                this->body = body;
                this->sev = sev;
            }
        };

    protected:
        std::queue<message> qMessages;
        std::recursive_mutex mtx;

        std::atomic<bool> isWorking;

        inline std::tm currentTime()
        {
            std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm *now = std::localtime(&time);
            return *now;
        }

    public:
        friend Logger &operator<<(Logger &logger, const message &msg)
        {
            std::lock_guard<std::recursive_mutex> lock(logger.mtx);
            logger.qMessages.push(msg);

            return logger;
        }

    public:
        void flush();

    protected:
        void out(const message &msg);
    };
}

void Engine::Logger::flush()
{
    while (!this->qMessages.empty())
    {
        this->out(this->qMessages.front());
        this->qMessages.pop();
    }
}

void Engine::Logger::out(const message &msg)
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

    std::cout << "[" << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << " " << msg.header << "]: ";
    std::cout << END;
    std::cout << msg.body << std::endl;
    outputfile << "[" << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << "] " << msg.header << ": " << msg.body << std::endl;
}
#pragma once
#include <memory>
#include <string>
#include "WS/Window.h"
#include "WS/Core.h"
#include "Screen.h"
#include "Logger.h"

namespace Engine
{
    class EngineApp
    {
    protected:
        std::unique_ptr<WS::Window> window;
        std::unique_ptr<Screen> screen;
        Logger logger;

    public:
        EngineApp(std::string window_name, int width, int height, int x, int y);
        ~EngineApp();

        virtual void run();

    protected:
        static void _debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char *message, const void *classptr);
        void window_init(std::string name, int width, int height);
        virtual void assets_init() {}
        virtual void draw() {}
    };
}
#include "../include/ObscureEngine/EngineApp.h"
#include "../include/ObscureEngine/FPSCounter.h"

Engine::EngineApp::EngineApp(std::string window_name, int width, int height, int x, int y)
{
    try
    {
        this->window_init(window_name, width, height);
    }
    catch (const std::exception &e)
    {
        this->logger << Logger::message("Window System (WS)", e.what());
    }
    this->logger << Logger::message("Window System (WS)", "Window has been successfully created");

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(EngineApp::_debugfunc, &this->logger);

    this->player = std::unique_ptr<Player>(new Player());
}

Engine::EngineApp::~EngineApp()
{
    this->logger << Logger::message("Obscure Engine", "Closing session");
    this->logger.flush();
}

void Engine::EngineApp::window_init(std::string name, int width, int height)
{
    this->window = std::unique_ptr<WS::Window>(new WS::Window(name, width, height));
    this->screen = std::unique_ptr<Screen>(new Screen(WS::Size(width, height)));
}

void Engine::EngineApp::_debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char *message, const void *classptr)
{
    Logger *logger = (Engine::Logger *)classptr;

    Logger::severity sev;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        sev = Logger::severity::high;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        sev = Logger::severity::medium;
        break;
    case GL_DEBUG_SEVERITY_LOW:
        sev = Logger::severity::low;
        break;
    default:
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        sev = Logger::severity::notification;
        break;
    }
    *logger << Logger::message("OpenGL", message, sev);
}

/*void Engine::EngineApp::run()
{

    FPSCounter counter;
    while (this->window->isOpen())
    {
        counter.start();
        this->window->pollEvent();

        draw();

        this->window->swapBuffers();
        glClearColor(135.0 / 255.0f, 206.0 / 255.0f, 235.0 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        this->logger.flush();
        counter.stop();
    }
}*/
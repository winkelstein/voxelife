#include "../include/ObscureEngine/Importer/ShaderImporter.h"

Engine::Importer::ShaderImporter::ShaderImporter()
{
    for (uint8_t i = 0; i < 6; i++)
    {
        this->shaders[i] = 0;
    }
}

std::string Engine::Importer::ShaderImporter::getSourceFromFile(std::filesystem::path path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("unable to open shader file");

    std::string src, buffer;
    while (std::getline(file, buffer))
        src += buffer + '\n';

    return src;
}
GLuint Engine::Importer::ShaderImporter::compileShader(std::string src, ShaderType type)
{
    GLuint shader = glCreateShader((GLenum)type);
    const char *str = src.c_str();
    glShaderSource(shader, 1, &str, nullptr);

    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::string infoLog;
        infoLog.resize(512);
        glGetShaderInfoLog(shader, 512, nullptr, &infoLog[0]);
        throw std::runtime_error(infoLog.c_str());
    }
    else
        return shader;
}

void Engine::Importer::ShaderImporter::add(ShaderType type, std::filesystem::path path)
{
    uint8_t i = 0;
    while (this->shaders[i] != 0)
        i++;

    if (i > 6)
        throw std::runtime_error("too much shaders");
    else
        this->shaders[i] = ShaderImporter::compileShader(ShaderImporter::getSourceFromFile(path), type);
}
std::shared_ptr<Engine::gltk::Shader> Engine::Importer::ShaderImporter::import()
{

    GLuint handler = glCreateProgram();
    for (uint8_t i = 0; i < this->shaders[i] != 0; i++)
        glAttachShader(handler, this->shaders[i]);

    glLinkProgram(handler);

    int status;
    glGetProgramiv(handler, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::string infoLog;
        infoLog.resize(512);
        glGetProgramInfoLog(handler, 512, nullptr, &infoLog[0]);
        throw std::runtime_error(infoLog.c_str());
    }

    for (uint8_t i = 0; i < this->shaders[i] > 0; i++)
    {
        glDeleteShader(this->shaders[i]);
        this->shaders[i] = 0;
    }
    return std::shared_ptr<gltk::Shader>(new gltk::Shader(handler));
}
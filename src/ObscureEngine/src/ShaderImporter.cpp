#include "../include/ObscureEngine/Importer/ShaderImporter.h"
#include <nlohmann/json.hpp>

std::string ObscureEngine::Importer::ShaderImporter::getSourceFromFile(std::filesystem::path path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("unable to open shader file");

    std::string src, buffer;
    while (std::getline(file, buffer))
        src += buffer + '\n';

    return src;
}
GLuint ObscureEngine::Importer::ShaderImporter::compileShader(std::string src, ShaderType type)
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

GLuint ObscureEngine::Importer::ShaderImporter::add(ShaderType type, std::filesystem::path path)
{
    return ShaderImporter::compileShader(ShaderImporter::getSourceFromFile(path), type);
}

GLuint ObscureEngine::Importer::ShaderImporter::linkShaderProgram(std::vector<GLuint> shaders)
{
    GLuint handler = glCreateProgram();
    for (uint8_t i = 0; i < shaders.size(); i++)
        glAttachShader(handler, shaders[i]);

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

    return handler;
}

ObscureEngine::Importer::ShaderImporter::ShaderImporterType ObscureEngine::Importer::ShaderImporter::import(std::filesystem::path path_to_config)
{
    using json = nlohmann::json;
    std::ifstream f(path_to_config / "config.json");

    if (!f.is_open())
        throw std::runtime_error("config.json file is not found");

    json data = json::parse(f);

    std::string name = data["name"].get<std::string>();

    /*
    geometry
    tess_control
    tess_evaluation
    compute
    */

    std::vector<std::pair<ShaderType, std::filesystem::path>> shaders_data;
    if (data.contains("vertex"))
    {
        std::filesystem::path vertex = data["vertex"].get<std::string>();
        shaders_data.push_back(std::make_pair(ShaderType::vertex, path_to_config / vertex));
    }

    if (data.contains("fragment"))
    {
        std::filesystem::path fragment = data["fragment"].get<std::string>();
        shaders_data.push_back(std::make_pair(ShaderType::fragment, path_to_config / fragment));
    }

    if (data.contains("geometry"))
    {
        std::filesystem::path geometry = data["geometry"].get<std::string>();
        shaders_data.push_back(std::make_pair(ShaderType::geometry, path_to_config / geometry));
    }

    if (data.contains("tess_control"))
    {
        std::filesystem::path tess_control = data["tess_control"].get<std::string>();
        shaders_data.push_back(std::make_pair(ShaderType::tess_control, path_to_config / tess_control));
    }

    if (data.contains("tess_evaluation"))
    {
        std::filesystem::path tess_evaluation = data["tess_evaluation"].get<std::string>();
        shaders_data.push_back(std::make_pair(ShaderType::tess_evaluation, path_to_config / tess_evaluation));
    }

    if (data.contains("compute"))
    {
        std::filesystem::path compute = data["compute"].get<std::string>();
        shaders_data.push_back(std::make_pair(ShaderType::compute, path_to_config / compute));
    }

    if (shaders_data.size() < 1)
        throw std::runtime_error("no shaders is provided");

    std::vector<GLuint> shaders;

    for (auto &shader_data : shaders_data)
        shaders.push_back(ShaderImporter::add(shader_data.first, shader_data.second));

    std::shared_ptr<gltk::Shader> program = std::shared_ptr<gltk::Shader>(new gltk::Shader(ShaderImporter::linkShaderProgram(shaders)));

    return std::make_pair(name, program);
}
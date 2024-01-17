#include "../include/ObscureEngine/GLTK/Shader.h"
#include <cstring>

void ObscureEngine::gltk::Shader::getUniforms()
{
    int numUniforms = 0;
    glGetProgramInterfaceiv(this->handler, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

    this->uniforms.resize(numUniforms);

    GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

    for (int i = 0; i < numUniforms; i++)
    {
        GLint results[4];
        glGetProgramResourceiv(this->handler, GL_UNIFORM, i, 4, properties, 4, nullptr, results);

        if (results[3] != -1)
            continue;

        GLint nameBufSize = results[0];
        std::string name;
        name.resize(nameBufSize);

        glGetProgramResourceName(this->handler, GL_UNIFORM, i, nameBufSize, nullptr, &name[0]);

        this->uniforms[i].name = name.substr(0, name.size() - 1);
        this->uniforms[i].type = results[1];
        this->uniforms[i].location = results[2];
    }
}

ObscureEngine::gltk::Shader::Uniform ObscureEngine::gltk::Shader::findUniform(std::string name)
{
    for (size_t i = 0; i < this->uniforms.size(); i++)
        if (name == this->uniforms[i].name)
            return this->uniforms[i];

    throw std::runtime_error("specified uniform was not found");
}

ObscureEngine::gltk::Shader::Shader(GLuint handler)
{
    this->handler = handler;
    this->getUniforms();
}

ObscureEngine::gltk::Shader::~Shader()
{
    glDeleteProgram(this->handler);
}

void ObscureEngine::gltk::Shader::bind()
{
    if (!this->_checkIsBinded())
    {
        this->_bind();
        glUseProgram(this->handler);
    }
}

void ObscureEngine::gltk::Shader::unbind()
{
    if (this->_checkIsBinded())
    {
        this->_unbind();
        glUseProgram(0);
    }
}
#pragma once
#include <unordered_map>
#include <stdexcept>

#include "GLTK/Shader.h"

namespace ObscureEngine
{
    class Assets
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<gltk::Shader>> shaders;

    public:
        template <class _Ty>
        void store(std::string name, _Ty object);

        template <class _Ty>
        const _Ty get(std::string name);
    };
}

template <>
inline void ObscureEngine::Assets::store(std::string name, std::shared_ptr<ObscureEngine::gltk::Shader> object)
{
    this->shaders[name] = object;
}

template <>
inline const std::shared_ptr<ObscureEngine::gltk::Shader> ObscureEngine::Assets::get(std::string name)
{
    if (this->shaders.find(name) != this->shaders.end())
        return this->shaders[name];
    else
        throw std::runtime_error("Shader not found");
}
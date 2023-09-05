#pragma once
#include <glm/glm.hpp>

#include "GLTK/Shader.h"
#include "Renderer.h"

namespace Engine
{
    class drawable
    {
    public:
        virtual void draw(gltk::Shader &shader) const = 0;
    };
}
#pragma once
#include "GLTK/Shader.h"

namespace ObscureEngine
{
    class Renderer
    {
    public:
        static void render()
        {
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    };
}
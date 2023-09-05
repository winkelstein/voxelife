#pragma once
#include <cstdint>

namespace Engine
{
    namespace WS
    {
        struct Size
        {
            int width, height;
            Size(int width, int height)
            {
                this->width = width;
                this->height = height;
            }
        };

        struct Position
        {
            uint64_t x, y;
            Position(uint64_t x, uint64_t)
            {
                this->x = x;
                this->y = y;
            }
        };
    }
}
#pragma once
#include <cstdint>

namespace ObscureEngine
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
            uint64_t x, y, z;
            Position(uint64_t x, uint64_t y, uint64_t z = 0)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }
        };
    }
}
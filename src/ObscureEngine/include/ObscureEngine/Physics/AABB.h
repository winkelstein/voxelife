#pragma once
#include <vector>
#include <stdexcept>
#include <glm/glm.hpp>

namespace Engine
{
    namespace Physics
    {
        class AABB
        {
        protected:
            glm::vec3 min;
            glm::vec3 max;

        public:
            friend bool calculate(const AABB &a, const AABB &b)
            {
                return (
                    a.min.x <= b.max.x &&
                    a.max.x >= b.min.x &&
                    a.min.y <= b.max.y &&
                    a.max.y >= b.min.y &&
                    a.min.z <= b.max.z &&
                    a.max.z >= b.min.z);
            }
        };
    }
}
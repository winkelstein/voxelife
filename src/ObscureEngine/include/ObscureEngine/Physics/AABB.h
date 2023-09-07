#pragma once
#include <vector>
#include <stdexcept>
#include <glm/glm.hpp>

#include "../Voxel.h"

namespace Engine
{
    namespace Physics
    {
        class AABB
        {
        public:
            /*static bool calculate(const Voxel &obj1, const Voxel &obj2)
            {
                glm::vec3 a_min = obj1.position() - (obj1.size() / 2.0f);
                glm::vec3 a_max = obj1.position() + (obj1.size() / 2.0f);

                glm::vec3 b_min = obj2.position() - (obj2.size() / 2.0f);
                glm::vec3 b_max = obj2.position() + (obj2.size() / 2.0f);

                return (
                    a_min.x <= b_max.x &&
                    a_max.x >= b_min.x &&
                    a_min.y <= b_max.y &&
                    a_max.y >= b_min.y &&
                    a_min.z <= b_max.z &&
                    a_max.z >= b_min.z);
            }*/

            static glm::vec3 calculate(const Voxel &obj1, const Voxel &obj2)
            {
                glm::vec3 a_min = obj1.position() - (obj1.size() / 2.0f);
                glm::vec3 a_max = obj1.position() + (obj1.size() / 2.0f);

                glm::vec3 b_min = obj2.position() - (obj2.size() / 2.0f);
                glm::vec3 b_max = obj2.position() + (obj2.size() / 2.0f);

                // Переменные для хранения векторов смещения по каждой оси
                glm::vec3 displacement = glm::vec3(0.0f, 0.0f, 0.0f);

                // Проверка пересечения по каждой оси
                if (a_max.x >= b_min.x && a_min.x <= b_max.x)
                {
                    // Произошло пересечение по оси X, вычисляем смещение
                    float overlapX = std::min(a_max.x, b_max.x) - std::max(a_min.x, b_min.x);
                    displacement.x = (obj1.position().x < obj2.position().x) ? overlapX : -overlapX;
                }

                if (a_max.y >= b_min.y && a_min.y <= b_max.y)
                {
                    // Произошло пересечение по оси Y, вычисляем смещение
                    float overlapY = std::min(a_max.y, b_max.y) - std::max(a_min.y, b_min.y);
                    displacement.y = (obj1.position().y < obj2.position().y) ? overlapY : -overlapY;
                }

                if (a_max.z >= b_min.z && a_min.z <= b_max.z)
                {
                    // Произошло пересечение по оси Z, вычисляем смещение
                    float overlapZ = std::min(a_max.z, b_max.z) - std::max(a_min.z, b_min.z);
                    displacement.z = (obj1.position().z < obj2.position().z) ? overlapZ : -overlapZ;
                }

                return displacement;
            }
        };
    }
}
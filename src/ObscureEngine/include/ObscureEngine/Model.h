#pragma once
#include <vector>
#include <memory>
#include "drawable.h"
#include "Voxel.h"
#include "GLTK/Shader.h"

namespace ObscureEngine
{
    class Model : public drawable
    {
    private:
        std::vector<std::shared_ptr<Voxel>> voxels;
        std::vector<glm::vec3> voxel_positions;
        std::vector<glm::vec3> voxel_sizes;
        std::vector<glm::vec3> voxel_rotates;

        glm::vec3 m_position;
        glm::vec3 m_size;
        glm::vec3 m_rotate;
        glm::vec3 m_rotate_around_point;

    public:
        Model(std::vector<std::shared_ptr<Voxel>> voxels);

    public:
        void draw(gltk::Shader &shader) const override;

    public:
        void position(glm::vec3 position);
        void size(glm::vec3 size);
        // void rotate(glm::vec3 point, glm::vec3 angles);

    public:
        inline glm::vec3 position() const { return this->m_position; }
        inline glm::vec3 size() const { return this->m_size; }
        inline glm::vec3 rotate() const { return this->m_rotate; }
    };
}
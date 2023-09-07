#pragma once
#include <filesystem>
#include <glm/glm.hpp>
#include "drawable.h"

namespace Engine
{
    class Voxel : public drawable
    {
    private:
        static GLuint VAO;

    protected:
        glm::vec4 color;
        glm::mat4 model;

        glm::vec3 m_size;
        glm::vec3 m_position;
        glm::vec3 m_rotate;
        glm::vec3 m_rotate_around_point;

    public:
        Voxel(glm::vec4 color);
        ~Voxel();

    public:
        void draw(gltk::Shader &shader) const override;

    private:
        void update_matrix();

    public:
        void position(glm::vec3 position);
        void size(glm::vec3 size);
        void rotate(glm::vec3 point, glm::vec3 angles);

    public:
        inline glm::vec3 position() const { return this->m_position; }
        inline glm::vec3 size() const { return this->m_size; }
        inline glm::vec3 rotate() const { return this->m_rotate; }
    };
}

GLuint Engine::Voxel::VAO = 0;
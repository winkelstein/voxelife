#pragma once
#include <filesystem>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "drawable.h"

namespace Engine
{
    class Voxel : public drawable
    {
    private:
        static GLuint VAO;

    protected:
        glm::mat4 model;
        glm::vec4 m_color;

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
        void color(glm::vec4 col);

    public:
        inline glm::vec3 position() const { return this->m_position; }
        inline glm::vec3 size() const { return this->m_size; }
        inline glm::vec3 rotate() const { return this->m_rotate; }
        inline glm::vec3 color() const { return this->m_color; }

    public:
        static inline std::vector<float> __get_model_vertices();
        inline glm::mat4 __get_model_matrix() const { return this->model; }
        inline glm::vec3 __get_model_vertex(size_t index) const;
    };
}

GLuint Engine::Voxel::VAO = 0;

inline std::vector<float> Engine::Voxel::__get_model_vertices()
{
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.5f, // 0
        0.5f, -0.5f, 0.5f,  // 1
        0.5f, 0.5f, 0.5f,   // 2
        -0.5f, -0.5f, 0.5f, // 3
        0.5f, 0.5f, 0.5f,   // 4
        -0.5f, 0.5f, 0.5f,  // 5

        -0.5f, -0.5f, -0.5f, // 6
        0.5f, -0.5f, -0.5f,  // 7
        0.5f, 0.5f, -0.5f,   // 8
        -0.5f, -0.5f, -0.5f, // 9
        0.5f, 0.5f, -0.5f,   // 10
        -0.5f, 0.5f, -0.5f,  // 11

        -0.5f, -0.5f, -0.5f, // 12
        -0.5f, 0.5f, -0.5f,  // 13
        -0.5f, -0.5f, 0.5f,  // 14
        -0.5f, 0.5f, -0.5f,  // 15
        -0.5f, 0.5f, 0.5f,   // 16
        -0.5f, -0.5f, 0.5f,  // 17

        0.5f, -0.5f, -0.5f, // 18
        0.5f, 0.5f, -0.5f,  // 19
        0.5f, -0.5f, 0.5f,  // 20
        0.5f, 0.5f, -0.5f,  // 21
        0.5f, 0.5f, 0.5f,   // 22
        0.5f, -0.5f, 0.5f,  // 23

        -0.5f, 0.5f, -0.5f, // 24
        0.5f, 0.5f, -0.5f,  // 25
        0.5f, 0.5f, 0.5f,   // 26
        -0.5f, 0.5f, -0.5f, // 27
        0.5f, 0.5f, 0.5f,   // 28
        -0.5f, 0.5f, 0.5f,  // 29

        -0.5f, -0.5f, -0.5f, // 30
        0.5f, -0.5f, -0.5f,  // 31
        0.5f, -0.5f, 0.5f,   // 32
        -0.5f, -0.5f, -0.5f, // 33
        0.5f, -0.5f, 0.5f,   // 34
        -0.5f, -0.5f, 0.5f   // 35
    };

    return vertices;
}

inline glm::vec3 Engine::Voxel::__get_model_vertex(size_t index) const
{
    std::vector<float> vertices = Voxel::__get_model_vertices();

    if (index * 3 + 2 < vertices.size())
    {
        float x = vertices[index * 3];
        float y = vertices[index * 3 + 1];
        float z = vertices[index * 3 + 2];

        return glm::vec3(this->model * glm::vec4(x, y, z, 1.0));
    }
    else
        return glm::vec3(0.0f, 0.0f, 0.0f);
}
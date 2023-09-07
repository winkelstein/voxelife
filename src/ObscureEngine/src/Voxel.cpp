#include "../include/ObscureEngine/Voxel.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../include/ObscureEngine/Physics/Core.h"

Engine::Voxel::Voxel(glm::vec4 color) : color(color), m_position(glm::vec3(0.0)), m_size(glm::vec3(1.0)), m_rotate(glm::vec3(0.0)), m_rotate_around_point(glm::vec3(0.0))
{
    this->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f));
    if (this->VAO != 0)
        return;

    GLfloat vertices[] = {
        // Передняя грань
        -0.5f, -0.5f, 0.5f, // 0
        0.5f, -0.5f, 0.5f,  // 1
        0.5f, 0.5f, 0.5f,   // 2
        -0.5f, -0.5f, 0.5f, // 3
        0.5f, 0.5f, 0.5f,   // 4
        -0.5f, 0.5f, 0.5f,  // 5

        // Задняя грань
        -0.5f, -0.5f, -0.5f, // 6
        0.5f, -0.5f, -0.5f,  // 7
        0.5f, 0.5f, -0.5f,   // 8
        -0.5f, -0.5f, -0.5f, // 9
        0.5f, 0.5f, -0.5f,   // 10
        -0.5f, 0.5f, -0.5f,  // 11

        // Левая грань
        -0.5f, -0.5f, -0.5f, // 12
        -0.5f, 0.5f, -0.5f,  // 13
        -0.5f, -0.5f, 0.5f,  // 14
        -0.5f, 0.5f, -0.5f,  // 15
        -0.5f, 0.5f, 0.5f,   // 16
        -0.5f, -0.5f, 0.5f,  // 17

        // Правая грань
        0.5f, -0.5f, -0.5f, // 18
        0.5f, 0.5f, -0.5f,  // 19
        0.5f, -0.5f, 0.5f,  // 20
        0.5f, 0.5f, -0.5f,  // 21
        0.5f, 0.5f, 0.5f,   // 22
        0.5f, -0.5f, 0.5f,  // 23

        // Верхняя грань
        -0.5f, 0.5f, -0.5f, // 24
        0.5f, 0.5f, -0.5f,  // 25
        0.5f, 0.5f, 0.5f,   // 26
        -0.5f, 0.5f, -0.5f, // 27
        0.5f, 0.5f, 0.5f,   // 28
        -0.5f, 0.5f, 0.5f,  // 29

        // Нижняя грань
        -0.5f, -0.5f, -0.5f, // 30
        0.5f, -0.5f, -0.5f,  // 31
        0.5f, -0.5f, 0.5f,   // 32
        -0.5f, -0.5f, -0.5f, // 33
        0.5f, -0.5f, 0.5f,   // 34
        -0.5f, -0.5f, 0.5f   // 35
    };

    glGenVertexArrays(1, &this->VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(this->VAO, 0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

Engine::Voxel::~Voxel()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void Engine::Voxel::draw(gltk::Shader &shader) const
{
    shader.bind();
    shader.uniform<glm::mat4>("model", this->model);
    shader.uniform<glm::vec4>("color", this->color);
    Renderer::render(this->VAO);
}

void Engine::Voxel::position(glm::vec3 position)
{
    this->m_position = position;
    this->update_matrix();
}

void Engine::Voxel::size(glm::vec3 size)
{
    this->m_size = size;
    this->update_matrix();
}

void Engine::Voxel::rotate(glm::vec3 point, glm::vec3 angles)
{
    this->m_rotate = angles;
    this->m_rotate_around_point = point;

    this->update_matrix();
}

/*void Engine::Voxel::update_matrix()
{
    using Engine::Physics::constants::pi;

    glm::mat4 _model = glm::mat4(1.0f);
    _model = glm::translate(_model, this->m_position);

    _model = glm::rotate(_model, glm::radians(this->m_rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    _model = glm::rotate(_model, glm::radians(this->m_rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    _model = glm::rotate(_model, glm::radians(this->m_rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));

    _model = glm::scale(_model, this->m_size);

    this->model = _model;
}*/

void Engine::Voxel::update_matrix()
{
    using Engine::Physics::constants::pi;

    glm::mat4 _model = glm::mat4(1.0f);

    glm::vec3 offset = this->m_rotate_around_point;

    _model = glm::translate(_model, this->m_position);
    _model = glm::translate(_model, offset);
    _model = glm::rotate(_model, glm::radians(this->m_rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    _model = glm::rotate(_model, glm::radians(this->m_rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    _model = glm::rotate(_model, glm::radians(this->m_rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
    _model = glm::translate(_model, -offset);

    _model = glm::scale(_model, this->m_size);

    this->model = _model;
}

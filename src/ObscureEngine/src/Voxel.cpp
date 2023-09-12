#include "../include/ObscureEngine/Voxel.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../include/ObscureEngine/Physics/Core.h"

Engine::Voxel::Voxel(glm::vec4 color) : m_color(color), m_position(glm::vec3(0.0)), m_size(glm::vec3(1.0)), m_rotate(glm::vec3(0.0)), m_rotate_around_point(glm::vec3(0.0))
{
    this->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f));
    if (this->VAO != 0)
        return;

    std::vector<float> vertices = Voxel::__get_model_vertices();

    glGenVertexArrays(1, &this->VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

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
    shader.uniform<glm::vec4>("color", this->m_color);
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

void Engine::Voxel::color(glm::vec4 col)
{
    this->m_color = col;
}

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

#include "../include/ObscureEngine/Model.h"

ObscureEngine::Model::Model(std::vector<std::shared_ptr<Voxel>> voxels)
{
    this->voxels = voxels;

    for (size_t i = 0; i < this->voxels.size(); i++)
    {
        this->voxel_positions.push_back(this->voxels[i]->position());
        this->voxel_sizes.push_back(this->voxels[i]->size());
        this->voxel_rotates.push_back(this->voxels[i]->rotate());
    }
}

void ObscureEngine::Model::draw(ObscureEngine::gltk::Shader &shader) const
{
    shader.bind();
    for (auto &t : this->voxels)
        t->draw(shader);
}

void ObscureEngine::Model::position(glm::vec3 position)
{
    for (size_t i = 0; i < this->voxels.size(); i++)
        this->voxels[i]->position(this->voxel_positions[i] + position);

    this->m_position = position;
}

void ObscureEngine::Model::size(glm::vec3 size)
{
    for (size_t i = 0; i < this->voxels.size(); i++)
    {
        this->voxels[i]->size(size);
        this->voxels[i]->position(this->voxel_positions[i] * size);
    }

    this->m_size = size;
}

/*void ObscureEngine::Model::rotate(glm::vec3 point, glm::vec3 angles)
{
    for (size_t i = 0; i < this->voxels.size(); i++)
    {
        this->voxels[i]->rotate(point, angles);
    }

    this->m_rotate = angles;
    this->m_rotate_around_point = point;
}*/
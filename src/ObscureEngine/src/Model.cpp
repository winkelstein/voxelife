#include "../include/ObscureEngine/Model.h"

ObscureEngine::Model::Model(std::vector<std::shared_ptr<Voxel>> voxels)
{
    this->voxels = voxels;
}

void ObscureEngine::Model::draw(ObscureEngine::gltk::Shader &shader) const
{
    shader.bind();
    for (auto &t : this->voxels)
        t->draw(shader);
}

// void ObscureEngine::Model::position(glm::vec3 position) {}
// void ObscureEngine::Model::size(glm::vec3 size) {}
// void ObscureEngine::Model::rotate(glm::vec3 point, glm::vec3 angles) {}
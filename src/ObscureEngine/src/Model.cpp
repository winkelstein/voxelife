#include "../include/ObscureEngine/Model.h"

Engine::Model::Model(std::vector<std::shared_ptr<Voxel>> voxels)
{
    this->voxels = voxels;
}

void Engine::Model::draw(Engine::gltk::Shader &shader) const
{
    shader.bind();
    for (auto &t : this->voxels)
        t->draw(shader);
}
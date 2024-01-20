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
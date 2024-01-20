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

    public:
        Model(std::vector<std::shared_ptr<Voxel>> voxels);

    public:
        void draw(gltk::Shader &shader) const override;
    };
}
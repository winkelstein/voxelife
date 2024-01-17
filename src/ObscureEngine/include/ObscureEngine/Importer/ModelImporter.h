#pragma once
#include "Importer.h"
#include "../Model.h"

namespace Engine
{
    namespace Importer
    {
        class ModelImporter : public Importer<Model>
        {
            using ModelImporterType = std::pair<std::string, std::shared_ptr<Model>>;

            struct VoxColor
            {
                uint8_t red;
                uint8_t green;
                uint8_t blue;
                uint8_t alpha;
            };

            struct VoxVoxel
            {
                uint8_t x;
                uint8_t y;
                uint8_t z;
                uint8_t colorIndex;
            };

            struct VoxMainChunk
            {
                uint32_t sizeX;
                uint32_t sizeY;
                uint32_t sizeZ;
                VoxVoxel *voxels;
            };

            struct VoxXYZIChunk
            {
                uint32_t voxelCount;
                VoxVoxel *voxels;
            };

            struct VoxRGBAChunk
            {
                VoxColor *colors;
            };

            struct VoxFormat
            {

                struct VoxHeader
                {
                    char signature[4];
                    uint32_t version;
                } header;

                VoxMainChunk mainChunk;
                VoxXYZIChunk xyziChunk;
                VoxRGBAChunk rgbaChunk;
            };

            struct Config
            {
                std::string name;
                std::filesystem::path model;
            };

            VoxFormat *read_from_file(std::filesystem::path path_to_config);
            std::shared_ptr<Model> parse_model(VoxFormat format);
            Config parse_config(std::ifstream &config_file);

        public:
            ModelImporterType import(std::filesystem::path path_to_config);
        };
    }
}
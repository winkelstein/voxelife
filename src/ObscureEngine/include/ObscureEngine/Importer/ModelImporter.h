#pragma once
#include "Importer.h"
#include "../Model.h"

namespace ObscureEngine
{
    namespace Importer
    {
        class ModelImporter : public Importer<Model>
        {
            using ModelImporterType = std::pair<std::string, std::shared_ptr<Model>>;

        private:
            struct Config
            {
                std::string name;
                std::filesystem::path model;
            };

        private:
            struct SizeChunk
            {
                int32_t x, y, z;
            };

            struct VoxelFormat
            {
                unsigned char distance;
                unsigned char color;
                unsigned char shade;
                unsigned char index;
            };

            struct VoxPos
            {
                int x, y, z, colorIndex;
            };

            struct VoxSize
            {
                int sizeX, sizeY, sizeZ;
            };

        private:
            std::shared_ptr<Model> read_from_file(std::filesystem::path path_to_config);
            std::shared_ptr<Model> parse_model(std::vector<VoxPos> positions, std::vector<VoxSize> sizes, std::vector<uint32_t> palette);
            std::vector<uint32_t> load_palette(FILE *file, int total_size);
            Config parse_config(std::filesystem::path path_to_config);

        public:
            ModelImporterType import(std::filesystem::path path_to_config);
        };
    }
}
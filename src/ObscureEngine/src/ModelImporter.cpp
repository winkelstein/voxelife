#include "../include/ObscureEngine/Importer/ModelImporter.h"
#include <nlohmann/json.hpp>
#include <fstream>

Engine::Importer::ModelImporter::ModelImporterType Engine::Importer::ModelImporter::import(std::filesystem::path path_to_config)
{
    std::ifstream config_file(path_to_config / "config.json");

    if (!config_file.is_open())
        throw std::runtime_error("config.json file is not found");

    Config config = this->parse_config(config_file);
    VoxFormat format = this->read_from_file(config.model);
    std::shared_ptr<Model> model = this->parse_model(format);

    return std::make_pair(config.name, model);
}

Engine::Importer::ModelImporter::Config Engine::Importer::ModelImporter::parse_config(std::ifstream &config_file)
{
    using json = nlohmann::json;
    json data = json::parse(config_file);

    Config config;
    config.name = data["name"].get<std::string>();
    config.model = data["model"].get<std::string>();

    return config;
}

Engine::Importer::ModelImporter::VoxFormat *Engine::Importer::ModelImporter::read_from_file(std::filesystem::path path_to_config)
{
    FILE *file = fopen(path_to_config.c_str(), "r");
    if (file == NULL)
        throw std::runtime_error("unable to open file");

    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = new char[filesize];

    size_t read = fread(buffer, sizeof(char), filesize, file);
    fclose(file);

    if (read == 0)
        throw std::runtime_error("unable to read file");

    VoxFormat *format = (VoxFormat *)calloc(1, sizeof(VoxFormat));
    memcpy(&(format->header), buffer, sizeof(VoxFormat.VoxHeader));
    buffer += sizeof(VoxFormat.VoxHeader);

    VoxMainChunk *mainChunkHeader = (VoxChunk *)buffer;
    memcpy(&(format->mainChunk), buffer, sizeof(VoxMainChunk));
    buffer += sizeof(VoxMainChunk);

    format->mainChunk.voxels = (VoxVoxel *)calloc(mainChunkHeader->sizeX);

    return format;
}
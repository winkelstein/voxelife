#include "../include/ObscureEngine/Importer/ModelImporter.h"
#include <nlohmann/json.hpp>
#include <fstream>

ObscureEngine::Importer::ModelImporter::ModelImporterType ObscureEngine::Importer::ModelImporter::import(std::filesystem::path path_to_config)
{
    Config config = this->parse_config(path_to_config);
    std::shared_ptr<Model> model = this->read_from_file(config.model);

    return std::make_pair(config.name, model);
}

ObscureEngine::Importer::ModelImporter::Config ObscureEngine::Importer::ModelImporter::parse_config(std::filesystem::path path_to_config)
{
    using json = nlohmann::json;

    std::ifstream config_file(path_to_config / "config.json");

    if (!config_file.is_open())
        throw std::runtime_error("config.json file is not found");

    json data = json::parse(config_file);

    Config config;
    config.name = data["name"].get<std::string>();
    config.model = path_to_config / data["model"].get<std::string>();

    return config;
}

std::vector<uint32_t> ObscureEngine::Importer::ModelImporter::load_palette(FILE *file, int totalSize)
{
    std::vector<uint32_t> palette;

    long pos = ftell(file);
    for (int i = 0; i < totalSize;)
    {
        char chunkID[4];
        int chunkContentBytes;
        fread(chunkID, 4, 1, file);
        fread(&chunkContentBytes, 4, 1, file);
        fseek(file, 4, SEEK_CUR);
        i += chunkContentBytes;
        if (strncmp(chunkID, "RGBA", 4) == 0)
        {
            for (int i = 0; i < chunkContentBytes / 4; i += 1)
            {
                unsigned int color;
                fread(&color, 4, 1, file);

                if (color == 0xFFFFFFFF)
                {
                    unsigned char r = 0, g = 0, b = 100, a = 100;
                    color = (a << 24) | (b << 16) | (g << 8) | r;
                }
                if (color == 0xFFFF00FF)
                {
                    unsigned char r = 0, g = 0, b = 0, a = 250;
                    color = (a << 24) | (b << 16) | (g << 8) | r;
                }

                if (palette.size() == 255)
                    palette.insert(palette.begin(), color);
                else
                    palette.push_back(color);
            }
            break;
        }
        else
        {
            fseek(file, chunkContentBytes, SEEK_CUR);
        }
    }
    if (palette.size() != 256)
    {
        unsigned int colors[256] = {
            0x00000000, 0xffffffff, 0xffccffff, 0xff99ffff, 0xff66ffff, 0xff33ffff, 0xff00ffff, 0xffffccff, 0xffccccff, 0xff99ccff, 0xff66ccff, 0xff33ccff, 0xff00ccff, 0xffff99ff, 0xffcc99ff, 0xff9999ff,
            0xff6699ff, 0xff3399ff, 0xff0099ff, 0xffff66ff, 0xffcc66ff, 0xff9966ff, 0xff6666ff, 0xff3366ff, 0xff0066ff, 0xffff33ff, 0xffcc33ff, 0xff9933ff, 0xff6633ff, 0xff3333ff, 0xff0033ff, 0xffff00ff,
            0xffcc00ff, 0xff9900ff, 0xff6600ff, 0xff3300ff, 0xff0000ff, 0xffffffcc, 0xffccffcc, 0xff99ffcc, 0xff66ffcc, 0xff33ffcc, 0xff00ffcc, 0xffffcccc, 0xffcccccc, 0xff99cccc, 0xff66cccc, 0xff33cccc,
            0xff00cccc, 0xffff99cc, 0xffcc99cc, 0xff9999cc, 0xff6699cc, 0xff3399cc, 0xff0099cc, 0xffff66cc, 0xffcc66cc, 0xff9966cc, 0xff6666cc, 0xff3366cc, 0xff0066cc, 0xffff33cc, 0xffcc33cc, 0xff9933cc,
            0xff6633cc, 0xff3333cc, 0xff0033cc, 0xffff00cc, 0xffcc00cc, 0xff9900cc, 0xff6600cc, 0xff3300cc, 0xff0000cc, 0xffffff99, 0xffccff99, 0xff99ff99, 0xff66ff99, 0xff33ff99, 0xff00ff99, 0xffffcc99,
            0xffcccc99, 0xff99cc99, 0xff66cc99, 0xff33cc99, 0xff00cc99, 0xffff9999, 0xffcc9999, 0xff999999, 0xff669999, 0xff339999, 0xff009999, 0xffff6699, 0xffcc6699, 0xff996699, 0xff666699, 0xff336699,
            0xff006699, 0xffff3399, 0xffcc3399, 0xff993399, 0xff663399, 0xff333399, 0xff003399, 0xffff0099, 0xffcc0099, 0xff990099, 0xff660099, 0xff330099, 0xff000099, 0xffffff66, 0xffccff66, 0xff99ff66,
            0xff66ff66, 0xff33ff66, 0xff00ff66, 0xffffcc66, 0xffcccc66, 0xff99cc66, 0xff66cc66, 0xff33cc66, 0xff00cc66, 0xffff9966, 0xffcc9966, 0xff999966, 0xff669966, 0xff339966, 0xff009966, 0xffff6666,
            0xffcc6666, 0xff996666, 0xff666666, 0xff336666, 0xff006666, 0xffff3366, 0xffcc3366, 0xff993366, 0xff663366, 0xff333366, 0xff003366, 0xffff0066, 0xffcc0066, 0xff990066, 0xff660066, 0xff330066,
            0xff000066, 0xffffff33, 0xffccff33, 0xff99ff33, 0xff66ff33, 0xff33ff33, 0xff00ff33, 0xffffcc33, 0xffcccc33, 0xff99cc33, 0xff66cc33, 0xff33cc33, 0xff00cc33, 0xffff9933, 0xffcc9933, 0xff999933,
            0xff669933, 0xff339933, 0xff009933, 0xffff6633, 0xffcc6633, 0xff996633, 0xff666633, 0xff336633, 0xff006633, 0xffff3333, 0xffcc3333, 0xff993333, 0xff663333, 0xff333333, 0xff003333, 0xffff0033,
            0xffcc0033, 0xff990033, 0xff660033, 0xff330033, 0xff000033, 0xffffff00, 0xffccff00, 0xff99ff00, 0xff66ff00, 0xff33ff00, 0xff00ff00, 0xffffcc00, 0xffcccc00, 0xff99cc00, 0xff66cc00, 0xff33cc00,
            0xff00cc00, 0xffff9900, 0xffcc9900, 0xff999900, 0xff669900, 0xff339900, 0xff009900, 0xffff6600, 0xffcc6600, 0xff996600, 0xff666600, 0xff336600, 0xff006600, 0xffff3300, 0xffcc3300, 0xff993300,
            0xff663300, 0xff333300, 0xff003300, 0xffff0000, 0xffcc0000, 0xff990000, 0xff660000, 0xff330000, 0xff0000ee, 0xff0000dd, 0xff0000bb, 0xff0000aa, 0xff000088, 0xff000077, 0xff000055, 0xff000044,
            0xff000022, 0xff000011, 0xff00ee00, 0xff00dd00, 0xff00bb00, 0xff00aa00, 0xff008800, 0xff007700, 0xff005500, 0xff004400, 0xff002200, 0xff001100, 0xffee0000, 0xffdd0000, 0xffbb0000, 0xffaa0000,
            0xff880000, 0xff770000, 0xff550000, 0xff440000, 0xff220000, 0xff110000, 0xffeeeeee, 0xffdddddd, 0xffbbbbbb, 0xffaaaaaa, 0xff888888, 0xff777777, 0xff555555, 0xff444444, 0xff222222, 0xff111111};
        palette.clear();
        for (int i = 0; i < 256; i++)
        {
            palette.push_back(colors[i]);
        }
    }
    fseek(file, pos, SEEK_SET);

    return palette;
}

// TODO: done
std::shared_ptr<ObscureEngine::Model> ObscureEngine::Importer::ModelImporter::parse_model(std::vector<VoxPos> positions, std::vector<VoxSize> sizes, std::vector<uint32_t> palette)
{
    std::vector<std::shared_ptr<Voxel>> voxels;

    for (uint32_t i = 0; i < positions.size(); i++)
    {
        uint32_t color = palette[positions[i].colorIndex];

        float r, g, b, a = 1.0;

        r = ((color >> 16) & 0xFF) / 255.0;
        g = ((color >> 8) & 0xFF) / 255.0;
        b = ((color) & 0xFF) / 255.0;

        voxels.push_back(std::shared_ptr<Voxel>(new Voxel(glm::vec4(r, g, b, 1.0))));
        voxels[i]->position(glm::vec3(positions[i].x, positions[i].y, positions[i].z));
        // voxels[i]->size(glm::vec3(sizes[i].sizeX, sizes[i].sizeY, sizes[i].sizeZ));
    }

    std::shared_ptr<Model>
        model(new Model(voxels));

    return model;
}

std::shared_ptr<ObscureEngine::Model> ObscureEngine::Importer::ModelImporter::read_from_file(std::filesystem::path path_to_config)
{
    FILE *file = fopen(path_to_config.c_str(), "rb");
    if (file == NULL)
        throw std::runtime_error("unable to open \"" + path_to_config.string() + "\" file");

    fseek(file, 16, SEEK_CUR);
    int totalSize;
    fread(&totalSize, 4, 1, file);
    std::vector<uint32_t> palette = this->load_palette(file, totalSize);

    std::vector<VoxPos> positions;
    std::vector<VoxSize> sizes;

    bool isPos = false;

    for (int i = 0; i < totalSize;)
    {
        char chunkID[4];
        int chunkContentBytes;
        int chunkChildrenBytes;
        fread(chunkID, 4, 1, file);
        fread(&chunkContentBytes, 4, 1, file);
        fread(&chunkChildrenBytes, 4, 1, file);
        i += chunkContentBytes;

        if (strncmp(chunkID, "SIZE", 4) == 0)
        {
            int sizeX, sizeY, sizeZ;

            fread(&sizeX, 4, 1, file);
            fread(&sizeY, 4, 1, file);
            fread(&sizeZ, 4, 1, file);

            sizes.push_back({sizeX, sizeY, sizeZ});
            isPos = false;
        }
        else if (strncmp(chunkID, "XYZI", 4) == 0)
        {
            int numVoxels;
            fread(&numVoxels, 4, 1, file);
            for (int j = 0; j < numVoxels; j++)
            {
                if (isPos)
                    sizes.push_back({1, 1, 1});
                unsigned char x, y, z, colorIndex;
                fread(&x, 1, 1, file);
                fread(&y, 1, 1, file);
                fread(&z, 1, 1, file);
                fread(&colorIndex, 1, 1, file);

                positions.push_back({x, y, z, colorIndex});
                isPos = true;
            }
        }
        else
        {
            fseek(file, chunkContentBytes, SEEK_CUR);
        }
    }

    std::shared_ptr<ObscureEngine::Model> model = this->parse_model(positions, sizes, palette);
    return model;
}
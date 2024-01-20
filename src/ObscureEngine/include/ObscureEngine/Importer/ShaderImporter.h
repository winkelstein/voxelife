#pragma once
#include "Importer.h"
#include "../GLTK/Shader.h"

namespace ObscureEngine
{
    namespace Importer
    {
        class ShaderImporter : public Importer<gltk::Shader>
        {
            using ShaderImporterType = std::pair<std::string, std::shared_ptr<gltk::Shader>>;

        public:
            enum class ShaderType
            {
                vertex = GL_VERTEX_SHADER,
                fragment = GL_FRAGMENT_SHADER,
                geometry = GL_GEOMETRY_SHADER,
                tess_control = GL_TESS_CONTROL_SHADER,
                tess_evaluation = GL_TESS_EVALUATION_SHADER,
                compute = GL_COMPUTE_SHADER
            };

        private:
            static std::string get_source_from_file(std::filesystem::path path);
            static GLuint compile_shader(std::string src, ShaderType type);

            static GLuint link_shader_program(std::vector<GLuint> shaders);
            static GLuint add(ShaderType type, std::filesystem::path path);

        public:
            ShaderImporterType import(std::filesystem::path path_to_config) override;
        };
    }
}
#pragma once
#include "Importer.h"
#include "../GLTK/Shader.h"

namespace Engine
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
            static std::string getSourceFromFile(std::filesystem::path path);
            static GLuint compileShader(std::string src, ShaderType type);

            static GLuint linkShaderProgram(std::vector<GLuint> shaders);
            static GLuint add(ShaderType type, std::filesystem::path path);

        public:
            ShaderImporterType import(std::filesystem::path path_to_config) override;
        };
    }
}
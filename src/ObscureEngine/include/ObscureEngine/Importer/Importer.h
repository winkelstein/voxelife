#pragma once
#include <memory>
#include <filesystem>
#include <tuple>
#include <string>

namespace Engine
{
    namespace Importer
    {
        template <class _Ty>
        class Importer
        {
        public:
            virtual std::pair<std::string, std::shared_ptr<_Ty>> import(std::filesystem::path path_to_config) = 0;
        };
    }
}
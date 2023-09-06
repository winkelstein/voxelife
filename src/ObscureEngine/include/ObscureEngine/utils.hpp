#pragma once
#include <fstream>
#include <vector>

namespace Engine
{
    namespace utils
    {

        template <typename pod>
        std::ostream &serialize(std::ostream &os, std::vector<pod> const &v)
        {
            // this only works on built in data types (pods)
            static_assert(std::is_trivial<pod>::value && std::is_standard_layout<pod>::value,
                          "can only serialize pod types with this function");

            auto size = v.size();
            os.write(reinterpret_cast<char const *>(&size), sizeof(size));
            os.write(reinterpret_cast<char const *>(v.data()), v.size() * sizeof(pod));
            return os;
        }

        template <typename POD>
        inline std::istream &deserialize(std::istream &is, std::vector<POD> &v)
        {
            static_assert(std::is_trivial<POD>::value && std::is_standard_layout<POD>::value,
                          "Can only deserialize POD types with this function");

            decltype(v.size()) size;
            is.read(reinterpret_cast<char *>(&size), sizeof(size));
            v.resize(size);
            is.read(reinterpret_cast<char *>(v.data()), v.size() * sizeof(POD));
            return is;
        }
    }
}
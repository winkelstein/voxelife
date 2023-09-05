#include <fstream>
#include <vector>

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
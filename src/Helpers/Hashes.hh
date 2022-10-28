#ifndef HASHES
#define HASHES

#include <vector>
#include <unordered_set>

namespace std {
    template <>
    struct hash<unordered_set<unsigned int>> {
        auto operator()(const unordered_set<unsigned int>& vec) const -> size_t {
            std::size_t seed = vec.size();
            for (auto& i : vec) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    template <>
    struct hash<vector<unsigned int>> {
        auto operator()(const vector<unsigned int>& vec) const -> size_t {
            std::size_t seed = vec.size();
            for (auto& i : vec) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
};

#endif

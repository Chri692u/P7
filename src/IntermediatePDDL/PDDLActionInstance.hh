#ifndef PDDL_ACTION_INSTANCE_HH
#define PDDL_ACTION_INSTANCE_HH

#include <vector>
#include <unordered_set>
#include <string>

#include "PDDLAction.hh"
#include "../Helpers/Hashes.hh"

struct PDDLInstance;

class PDDLActionInstance {
public:
    size_t GetHash();

    const PDDLAction *action = nullptr;
    const std::vector<unsigned int> objects;
    PDDLActionInstance() {};
    PDDLActionInstance(const PDDLAction *action, const std::vector<unsigned int> objects) : action(action), objects(objects) {}; 
    std::string ToString(const PDDLInstance* instance);
    std::string LiteralsToString(std::vector<PDDLLiteral> literals, const PDDLInstance* instance);

    friend bool operator==(const PDDLActionInstance& lhs, const PDDLActionInstance& rhs) {
        if (lhs.action != rhs.action)
            return false;
        if (lhs.objects != rhs.objects)
            return false;
        return true;
    }

    PDDLActionInstance& operator=(const PDDLActionInstance& other) {
        return *new(this) PDDLActionInstance(action, objects);
    }

private:
    size_t Hash = 0;
};

namespace std {
    template <>
    struct hash<PDDLActionInstance> {
        auto operator()(const PDDLActionInstance& s) const -> size_t {
            std::size_t h1 = std::hash<const PDDLAction*>{}(s.action);
            std::size_t h2 = hash<vector<unsigned int>>{}(s.objects);
            return h1 ^ (h2 << 1);
        }
    };

    template <>
    struct hash<const vector<PDDLActionInstance>> {
        auto operator()(const vector<PDDLActionInstance>& vec) const -> size_t {
            std::size_t seed = vec.size();
            for (auto i : vec) {
                seed ^= 0x8e3471b5 + i.GetHash() + (seed >> 3);
            }
            return seed;
        }
    };

    template <>
    struct hash<vector<PDDLActionInstance>> {
        auto operator()(vector<PDDLActionInstance>& vec) -> size_t {
            std::size_t seed = vec.size();
            for (int i = 0; i < vec.size(); i++)
                seed ^= 0x8e3471b5 + vec.at(i).GetHash() + (seed >> 3);
            return seed;
        }
    };

    template <>
    struct hash<vector<PDDLActionInstance*>> {
        auto operator()(vector<PDDLActionInstance*>& vec) -> size_t {
            std::size_t seed = vec.size();
            for (int i = 0; i < vec.size(); i++)
                seed ^= 0x8e3471b5 + vec.at(i)->GetHash() + (seed >> 3);
            return seed;
        }
    };
}

#endif

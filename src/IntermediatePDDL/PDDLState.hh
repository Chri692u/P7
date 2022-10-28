#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>

#include "PDDLActionInstance.hh"

struct PDDLInstance;

struct MultiFact {
    std::vector<unsigned int> fact;
    MultiFact(std::vector<unsigned int> fact) : fact(fact) {};
    MultiFact(const std::vector<unsigned int> *indexes, const std::vector<unsigned int> *objects) {
        fact.reserve(indexes->size());
        for (int i = 0; i < indexes->size(); i++)
            fact.push_back(objects->at(indexes->at(i)));
    };

#pragma region Operators
#pragma region Equality
    friend bool operator== (const MultiFact &lhs, const MultiFact &rhs) {
        return lhs.fact == rhs.fact;
    }

    friend bool operator== (const MultiFact &lhs, const std::vector<unsigned int> &rhs) {
        return lhs.fact == rhs;
    }

    friend bool operator== (const std::vector<unsigned int> &lhs, const MultiFact &rhs) {
        return lhs == rhs.fact;
    }
    friend bool operator== (const MultiFact &lhs, const std::pair<const std::vector<unsigned int>*, const std::vector<unsigned int>*> &rhs) {
        if (rhs.first->size() != lhs.fact.size())
                return false;
        for (int i = 0; i < rhs.first->size(); i++)
            if (rhs.second->at(rhs.first->at(i)) != lhs.fact.at(i))
                return false;
        return true;
    }
    friend bool operator== (const std::pair<const std::vector<unsigned int>*, const std::vector<unsigned int>*> &lhs, const MultiFact &rhs) {
        return rhs == lhs;
    }
#pragma endregion Equality
#pragma endregion Operators

private:
};

struct PDDLState {
    // Key - Index of predicate | Value - Set of objects which the predicate is true for
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
    // Key - Index of predicate | Value - List of combinations of objcets which the predicate is true for (Should be a set, but cpp has a stroke trying to has a vector)
    std::unordered_map<unsigned int, std::vector<MultiFact>> multiFacts;

    PDDLState() {};
    PDDLState(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts, std::unordered_map<unsigned int, std::vector<MultiFact>> multiFacts) :
        unaryFacts(unaryFacts), multiFacts(multiFacts) {};

#pragma region ContainsFact
    bool ContainsFact(const unsigned int key, const unsigned int value) const {
        return (unaryFacts.at(key).contains(value));
    };

    bool ContainsFact(const unsigned int key, const MultiFact *value) const {
        auto AreEqual = [&value](const MultiFact &MF) {
                    return (*value) == MF;
                };
        if (!std::any_of(multiFacts.at(key).begin(), multiFacts.at(key).end(), AreEqual))
            return false;
        return true;
    };

    bool ContainsFact(const unsigned int key, const std::vector<unsigned int> *value) const {
        auto AreEqual = [&value](const MultiFact &MF) {
                    return *value == MF;
                };
        if (!std::any_of(multiFacts.at(key).begin(), multiFacts.at(key).end(), AreEqual))
            return false;
        return true;
    };

    bool ContainsFact(const unsigned int &key, const std::vector<unsigned int> *indexes, const std::vector<unsigned int> *objects) const {
        auto AreEqual = [&indexes, &objects](const MultiFact &MF) {
                    return std::make_pair(indexes, objects) == MF;
                };
        if (!std::any_of(multiFacts.at(key).begin(), multiFacts.at(key).end(), AreEqual))
            return false;
        return true;
    }
#pragma endregion ContainsFact

    void DoAction(const PDDLActionInstance *action);
    void UndoAction(const PDDLActionInstance *action);

    std::string ToString(const PDDLInstance* instance);

    // Very slow, please only use with caution
    friend bool operator== (const PDDLState &lhs, const PDDLState &rhs) {
        // Check unary facts
        //// Check that they contain the same keys
        for (auto iter : lhs.unaryFacts)
            if (!rhs.unaryFacts.contains(iter.first))
                return false;
        for (auto iter : rhs.unaryFacts)
            if (!lhs.unaryFacts.contains(iter.first))
                return false;
        //// 
        //// Check that they contain the same values
        for (auto iter : lhs.unaryFacts)
            if (lhs.unaryFacts.at(iter.first) != rhs.unaryFacts.at(iter.first))
                return false;
        ////
        //
        // Check multi facts
        //// Check that they contain the same keys
        for (auto iter : lhs.multiFacts)
            if (!rhs.multiFacts.contains(iter.first))
                return false;
        for (auto iter : rhs.multiFacts)
            if (!lhs.multiFacts.contains(iter.first))
                return false;
        //// 
        //// Check that they contain the same values
        for (auto iter : lhs.multiFacts)
            if (lhs.multiFacts.at(iter.first) != rhs.multiFacts.at(iter.first))
                return false;
        ////
        // 

        return true;
    };
    
};

namespace std {
    template <>
    struct hash<MultiFact> {
        auto operator()(MultiFact& s) const -> size_t {
            std::size_t h1 = hash<vector<unsigned int>>{}(s.fact);
            return h1;
        }
    };

    template <>
    struct hash<vector<MultiFact>> {
        auto operator()(vector<MultiFact>& vec) const -> size_t {
            std::size_t seed = vec.size();
            for (auto& i : vec) {
                seed ^= hash<MultiFact>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    template <>
    struct hash<PDDLState> {
        auto operator()(const PDDLState& s) const -> size_t {
            std::size_t unaryFactSeed = s.unaryFacts.size();
            for (auto KVPAIR : s.unaryFacts)
                unaryFactSeed ^= hash<unordered_set<unsigned int>>{}(KVPAIR.second) + 0x9e3779b9 + (unaryFactSeed << 6) + (unaryFactSeed >> 2);
            std::size_t multiFactSeed = s.multiFacts.size();
            for (auto KVPAIR : s.multiFacts)
                multiFactSeed ^= hash<vector<MultiFact>>{}(KVPAIR.second) + 0x9e3779b9 + (unaryFactSeed << 6) + (unaryFactSeed >> 2);
            return unaryFactSeed ^ (multiFactSeed << 1);
        }
    };
}

#endif

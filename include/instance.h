#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <functional>

class Instance {
    private:
        std::map<std::size_t, std::size_t> _restrictiveDigestion;
        std::size_t _sequenceLength;
        std::vector<std::size_t> _map;

    public:
        std::map<std::size_t, std::size_t>& RestrictiveDigestion();
        const std::size_t& SequenceLength();
        std::vector<std::size_t>& Map();

        bool checkFragmentViability(const std::size_t& fragment);
        std::size_t BinomialCoefficient(const std::size_t& n, const std::size_t& k);

        Instance(const std::vector<std::size_t>& restrictiveDigestion);
        ~Instance();
};
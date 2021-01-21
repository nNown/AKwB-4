#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <functional>

class Instance {
    private:
        std::vector<std::pair<int, int>> _restrictiveDigestion;
        int _sequenceLength;
        std::vector<int> _map;
        int _expectedMapFragments;

    public:
        std::vector<std::pair<int, int>>& RestrictiveDigestion();
        const int& SequenceLength();
        std::vector<int>& Map();
        const int& ExpectedMapFragments();

        int findElement(const std::vector<std::pair<int, int>>& list, const std::pair<int, int>& element);

        bool useFragment(const int& fragment, const bool& returnToSet);
        int BinomialCoefficient(const int& n, const int& k);

        Instance(const std::vector<int>& restrictiveDigestion);
        ~Instance();
};
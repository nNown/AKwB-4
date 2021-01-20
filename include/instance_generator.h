#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <math.h>
#include <functional>
#include <iostream>

class InstanceGenerator {
    private:
        static InstanceGenerator* _generator;
        InstanceGenerator();

    public:
        std::pair<std::vector<std::size_t>, std::vector<std::size_t>> GenerateInstance(std::pair<std::size_t, std::size_t> range, std::size_t cutsQuantity, bool direction);

        static InstanceGenerator* Generator();
        ~InstanceGenerator();
};
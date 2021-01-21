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
        std::pair<std::vector<int>, std::vector<int>> GenerateInstance(std::pair<int, int> range, int cutsQuantity, bool direction);

        static InstanceGenerator* Generator();
        ~InstanceGenerator();
};
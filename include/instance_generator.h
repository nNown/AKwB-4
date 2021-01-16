#pragma once

#include <map>
#include <vector>

class Instance {
    private:

    public:
};

class InstanceGenerator {
    private:
        static InstanceGenerator* _generator;
        InstanceGenerator();

    public:
        std::map<std::vector<std::size_t>, std::vector<std::size_t>> RestrictiveDigestionMap();
        
        static InstanceGenerator* Generator();
        ~InstanceGenerator();
};
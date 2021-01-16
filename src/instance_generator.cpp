#include <instance_generator.h>

InstanceGenerator* InstanceGenerator::_generator = nullptr;
InstanceGenerator::InstanceGenerator() {}

std::map<std::vector<std::size_t>, std::vector<std::size_t>> InstanceGenerator::RestrictiveDigestionMap() {
    std::map<std::vector<std::size_t>, std::vector<std::size_t>> restrictiveDigestionMap = std::map<std::vector<std::size_t>, std::vector<std::size_t>>();
    restrictiveDigestionMap.insert({ { 2, 3, 3, 4, 5, 7, 8, 9, 9, 10, 12, 15 }, { 2, 5, 3, 3 } });
    restrictiveDigestionMap.insert({ { 2, 3, 4, 5, 5, 8, 9, 10, 12, 15 }, { 4, 5, 2, 5 } });

    return restrictiveDigestionMap;
}

InstanceGenerator* InstanceGenerator::Generator() {
    if(_generator == nullptr) {
        _generator = new InstanceGenerator();
    }

    return _generator;
}

InstanceGenerator::~InstanceGenerator() {}
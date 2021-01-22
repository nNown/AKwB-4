#include <instance_generator.h>

InstanceGenerator* InstanceGenerator::_generator = nullptr;
InstanceGenerator::InstanceGenerator() {}

std::pair<std::vector<int>, std::vector<int>> InstanceGenerator::GenerateInstance(std::pair<int, int> range, int cutsQuantity, bool direction) {
    if(range.first >= range.second || cutsQuantity < 1) throw std::runtime_error("Incorrectly formated range or non-positive cuts quantity");
    
    std::vector<int> restrictionMap = std::vector<int>(cutsQuantity + 1);
    for(auto& site : restrictionMap) {
        int element = 0;
        // while(std::find(std::begin(restrictionMap), std::end(restrictionMap), element) != std::end(restrictionMap)) element = range.first + std::rand() % range.second + 1;
        while(element < 1) element = range.first + std::rand() % range.second + 1;

        site = element;
    }
    
    std::vector<int> instance = std::vector<int>();
    int summedElementsNumber = 1;
    while(summedElementsNumber <= restrictionMap.size()) {
        for(int i = 0; i <= restrictionMap.size() - summedElementsNumber; i++) {
            int currentElement = 0;
            for(int j = i; j < i + summedElementsNumber; j++) {
                currentElement += restrictionMap[j];
            }
            instance.push_back(currentElement);
        }
        summedElementsNumber++;
    }

    direction ? std::sort(instance.begin(), instance.end(), std::greater<int>()) : std::sort(instance.begin(), instance.end(), std::less<int>());
    return std::make_pair(instance, restrictionMap);
}

InstanceGenerator* InstanceGenerator::Generator() {
    if(_generator == nullptr) {
        _generator = new InstanceGenerator();
    }

    return _generator;
}

InstanceGenerator::~InstanceGenerator() {}
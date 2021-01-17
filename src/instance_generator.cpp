#include <instance_generator.h>

InstanceGenerator* InstanceGenerator::_generator = nullptr;
InstanceGenerator::InstanceGenerator() {}

std::pair<std::vector<std::size_t>, std::vector<std::size_t>> InstanceGenerator::GenerateInstance(std::pair<std::size_t, std::size_t> range, std::size_t cutsQuantity, bool direction) {
    if(range.first >= range.second || cutsQuantity < 1) throw std::runtime_error("Incorrectly formated range or non-positive cuts quantity");
    
    std::vector<std::size_t> restrictionMap = std::vector<std::size_t>(cutsQuantity + 1);
    for(auto& site : restrictionMap) {
        std::size_t element = 0;
        while(std::find(std::begin(restrictionMap), std::end(restrictionMap), element) != std::end(restrictionMap)) element = range.first + std::rand() % range.second + 1;

        site = element;
    }
    
    std::vector<std::size_t> instance = std::vector<std::size_t>();
    std::size_t summedElementsNumber = 1;
    while(summedElementsNumber <= restrictionMap.size()) {
        for(std::size_t i = 0; i <= restrictionMap.size() - summedElementsNumber; i++) {
            std::size_t currentElement = 0;
            for(std::size_t j = i; j < i + summedElementsNumber; j++) {
                currentElement += restrictionMap[j];
            }
            instance.push_back(currentElement);
        }
        summedElementsNumber++;
    }

    direction ? std::sort(instance.begin(), instance.end(), std::greater<std::size_t>()) : std::sort(instance.begin(), instance.end(), std::less<std::size_t>());
    return std::make_pair(instance, restrictionMap);
}

std::size_t InstanceGenerator::BinomialCoefficient(std::size_t n, std::size_t k) {
    std::size_t counter = 1;
    std::size_t denominator = 1;
    for(std::size_t i = 1; i <= k; i++) {
        counter *= (n + 1) - i;
        denominator *= i;
    }
    return counter / denominator;
}

InstanceGenerator* InstanceGenerator::Generator() {
    if(_generator == nullptr) {
        _generator = new InstanceGenerator();
    }

    return _generator;
}

InstanceGenerator::~InstanceGenerator() {}
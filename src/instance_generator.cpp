#include <instance_generator.h>

InstanceGenerator* InstanceGenerator::_generator = nullptr;
InstanceGenerator::InstanceGenerator() {}

std::pair<std::vector<std::size_t>, std::vector<std::size_t>> InstanceGenerator::GenerateInstance(std::pair<std::size_t, std::size_t> range, std::size_t cutsQuantity, bool direction) {
    if(range.first >= range.second || cutsQuantity < 1) throw std::runtime_error("Incorrectly formated range or non-positive cuts quantity");
    
    std::vector<std::size_t> restrictionMap = std::vector<std::size_t>(cutsQuantity + 1);
    for(auto& element : restrictionMap) {
        element = 1 + std::rand() % range.second + 1;
    }
    
    std::vector<std::size_t> instance = std::vector<std::size_t>();
    std::size_t summedElementsNumber = 1;
    while(summedElementsNumber <= cutsQuantity + 1) {
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
    double result = 1;
    for(double i = 1.0; i <= k; i++) {
        result *= ((n + 1) - i)/i;
    }
    return std::floor(result);
}

InstanceGenerator* InstanceGenerator::Generator() {
    if(_generator == nullptr) {
        _generator = new InstanceGenerator();
    }

    return _generator;
}

InstanceGenerator::~InstanceGenerator() {}
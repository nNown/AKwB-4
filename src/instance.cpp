#include <instance.h>

std::map<std::size_t, std::size_t>& Instance::RestrictiveDigestion() { return this->_restrictiveDigestion; }
const std::size_t& Instance::SequenceLength() { return this->_sequenceLength; }
std::vector<std::size_t>& Instance::Map() { return this->_map; }

bool Instance::checkFragmentViability(const std::size_t& fragment) {
    std::size_t mapLength = 0;
    for(std::size_t i = 0; i < this->_map.size(); i++) {
        std::size_t currentFragment = 0;
        if(this->_map[i] == 0) break;
        for(std::size_t j = i; j < this->_map.size(); j++) {
            currentFragment += this->_map[j];
        }

        if(i == 0) {
            mapLength = currentFragment + fragment;
        }

        if(this->_restrictiveDigestion.count(currentFragment + fragment) > 0) {
            if(this->_restrictiveDigestion[currentFragment + fragment] > 0) return false;
        }
    }

    if(this->_restrictiveDigestion.count(this->_sequenceLength - mapLength) > 0) {
        if(this->_restrictiveDigestion[this->_sequenceLength - mapLength] > 0) return false;
    } 

    if(this->_restrictiveDigestion.count(fragment) > 0) {
        if(this->_restrictiveDigestion[fragment] > 0) return false;
    }
    return true;
}

std::size_t Instance::BinomialCoefficient(const std::size_t& n, const std::size_t& k) {
    std::size_t counter = 1;
    std::size_t denominator = 1;

    for(std::size_t i = 1; i <= k; i++) {
        counter *= (n + 1) - i;
        denominator *= i;
    }

    return counter / denominator;
}

Instance::Instance(const std::vector<std::size_t>& restrictiveDigestion) {
    this->_sequenceLength = 0;
    for(auto& fragment : restrictiveDigestion) {
        if(fragment > this->_sequenceLength) {
            this->_sequenceLength = fragment;
        }

        this->_restrictiveDigestion.insert({ fragment, 0 });
    }

    std::size_t n = 1, result = 0;
    while(result < this->_restrictiveDigestion.size()) {
        result = this->BinomialCoefficient(n + 2, 2);
        n++;
    }

    if(result == restrictiveDigestion.size()) {
        this->_map = std::vector<std::size_t>(n);
    } else {
        this->_map = std::vector<std::size_t>();
    }
}
Instance::~Instance() {}
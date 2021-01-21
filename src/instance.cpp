#include <instance.h>

std::vector<std::pair<int, int>>& Instance::RestrictiveDigestion() { return this->_restrictiveDigestion; }
const int& Instance::SequenceLength() { return this->_sequenceLength; }
std::vector<int>& Instance::Map() { return this->_map; }
const int& Instance::ExpectedMapFragments() { return this->_expectedMapFragments; }

int Instance::findElement(const std::vector<std::pair<int, int>>& list, const std::pair<int, int>& element) {
    for(std::size_t i = 0; i < list.size(); i++) {
        if(list[i] == element) return i;
    }
    return -1;
}

bool Instance::useFragment(const int& fragment, const bool& returnToSet) {
    std::vector<int> usedFragments = std::vector<int>();

    int inputFragmentPosition = this->findElement(this->_restrictiveDigestion, returnToSet ? std::make_pair(fragment, 1) : std::make_pair(fragment, 0));
    if(inputFragmentPosition != -1) {
        returnToSet ? this->_restrictiveDigestion[inputFragmentPosition].second = 0 : this->_restrictiveDigestion[inputFragmentPosition].second = 1;
        usedFragments.push_back(inputFragmentPosition);
    } else {
        for(auto& fragment : usedFragments) {
            this->_restrictiveDigestion[fragment].second = 0;
        }
        return false;
    }

    int checkedFragment = fragment;
    for(auto i = this->_map.rbegin(); i != this->_map.rend(); ++i) {
        checkedFragment += *i;

        int checkedFragmentPosition = this->findElement(this->_restrictiveDigestion, returnToSet ? std::make_pair(checkedFragment, 1) : std::make_pair(checkedFragment, 0));
        if(checkedFragmentPosition != -1) {
            returnToSet ? this->_restrictiveDigestion[checkedFragmentPosition].second = 0 : this->_restrictiveDigestion[checkedFragmentPosition].second = 1;
            usedFragments.push_back(checkedFragmentPosition);
        } else {
            for(auto& fragment : usedFragments) {
                this->_restrictiveDigestion[fragment].second = 0;
            }
            return false;
        }
    }

    if(this->_sequenceLength - checkedFragment > 0) {
        int wholeFragmentBackwards = this->findElement(this->_restrictiveDigestion, returnToSet ? std::make_pair(this->_sequenceLength - checkedFragment, 1) : std::make_pair(this->_sequenceLength - checkedFragment, 0));
        if(wholeFragmentBackwards != -1) {
            // returnToSet ? this->_restrictiveDigestion[wholeFragmentBackwards].second = 0 : this->_restrictiveDigestion[wholeFragmentBackwards].second = 1;
            // usedFragments.push_back(wholeFragmentBackwards);
        } else {
            for(auto& fragment : usedFragments) {
                this->_restrictiveDigestion[fragment].second = 0;
            }
            return false;
        }
    }
    return true;
}

int Instance::BinomialCoefficient(const int& n, const int& k) {
    int counter = 1;
    int denominator = 1;

    for(int i = 1; i <= k; i++) {
        counter *= (n + 1) - i;
        denominator *= i;
    }

    return counter / denominator;
}

Instance::Instance(const std::vector<int>& restrictiveDigestion) {
    this->_sequenceLength = 0;
    for(auto& fragment : restrictiveDigestion) {
        if(fragment > this->_sequenceLength) {
            this->_sequenceLength = fragment;
        }

        this->_restrictiveDigestion.push_back({ fragment, 0 });
    }

    int n = 1, result = 0;
    while(result < this->_restrictiveDigestion.size()) {
        result = this->BinomialCoefficient(n + 2, 2);
        n++;
    }

    if(result == restrictiveDigestion.size()) {
        this->_expectedMapFragments = n;
    } else {
        this->_expectedMapFragments = 0;
    }
    this->_map = std::vector<int>();
}
Instance::~Instance() {}
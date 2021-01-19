#include <iostream>
#include <instance_parser.h>
#include <instance_generator.h>
#include <cstdlib>
#include <time.h>

bool findRestrictionMap(std::vector<std::size_t> restrictiveDigestion, std::vector<std::size_t>& map, std::size_t depth);

int main(void) {
    std::srand(std::time(NULL));
    
    InstanceParser* instanceParser = InstanceParser::Parser();
    InstanceGenerator* instanceGenerator = InstanceGenerator::Generator();

    auto instance = instanceGenerator->GenerateInstance({ 2, 6 }, 2, true);
    // instanceParser->SaveInstance(instance.first, "./tests");
    // instanceParser->SaveInstance(instance.second, "./results");

    
    std::size_t n = 1, result = instanceGenerator->BinomialCoefficient(n + 2, 2);
    while(result < instance.first.size()) {
        n++;
        result = instanceGenerator->BinomialCoefficient(n + 2, 2);
    }

    std::vector<std::size_t> answer = std::vector<std::size_t>(n);
    std::cout << answer.size() << std::endl;
    for(auto& element : instance.first) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    if(result == instance.first.size()) {
        bool test = findRestrictionMap(instance.first, answer, 0);
        std::cout << (test ? "True" : "False") << std::endl;
        for(auto& element : answer) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

bool findRestrictionMap(std::vector<std::size_t> restrictiveDigestion, std::vector<std::size_t>& map, std::size_t depth) {
    if(depth == map.size()) return true;

    std::size_t sequenceLength = 0;
    for(auto& fragment : restrictiveDigestion) {
        if(fragment > sequenceLength) {
            sequenceLength = fragment;
        }
    }

    if(depth == 0) {
        std::size_t secondLongestFragment = 0;
        for(auto& fragment : restrictiveDigestion) {
            if(fragment > secondLongestFragment && fragment < sequenceLength) {
                secondLongestFragment = fragment;
            }
        }

        std::size_t firstFragment = sequenceLength - secondLongestFragment;
        auto fragmentPositionForwards = std::find(restrictiveDigestion.begin(), restrictiveDigestion.end(), firstFragment);
        auto fragmentPositionBackwards = std::find(restrictiveDigestion.begin(), restrictiveDigestion.end(), sequenceLength - firstFragment);

        if(fragmentPositionForwards != restrictiveDigestion.end() && fragmentPositionBackwards != restrictiveDigestion.end()) {
            restrictiveDigestion.erase(fragmentPositionForwards);
            restrictiveDigestion.erase(fragmentPositionBackwards);

            map[depth] = firstFragment;
            findRestrictionMap(restrictiveDigestion, map, depth + 1);
        } else {
            return false;
        }
    } else {
        std::size_t summedResult = 0;
        for(auto& fragment : map) {
            summedResult += fragment;
        }

        for(auto& fragment : restrictiveDigestion) {
            std::vector<std::size_t> restrictiveDigestionCopy = std::vector<std::size_t>(restrictiveDigestion);
            auto fragmentPositionForwards = std::find(restrictiveDigestionCopy.begin(), restrictiveDigestionCopy.end(), summedResult + fragment);
            auto fragmentPositionBackwards = std::find(restrictiveDigestionCopy.begin(), restrictiveDigestionCopy.end(), sequenceLength - (summedResult + fragment));

            if(fragmentPositionForwards != restrictiveDigestionCopy.end() && fragmentPositionBackwards != restrictiveDigestionCopy.end()) {
                restrictiveDigestionCopy.erase(fragmentPositionForwards);
                restrictiveDigestionCopy.erase(fragmentPositionBackwards);

                map[depth] = fragment;
                findRestrictionMap(restrictiveDigestionCopy, map, depth + 1);
            }
        }
    }

    return false;
}
#include <iostream>
#include <instance_parser.h>
#include <instance_generator.h>
#include <cstdlib>
#include <time.h>

bool findRestrictionMap(std::vector<std::size_t> restrictiveDigestionResult, std::vector<std::size_t>& map, std::size_t depth);

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

bool findRestrictionMap(std::vector<std::size_t> restrictiveDigestionResult, std::vector<std::size_t>& map, std::size_t depth) {
    if(depth == map.size()) return true;

    std::size_t sequenceLength = 0;
    for(auto& fragment : restrictiveDigestionResult) {
        if(fragment > sequenceLength) {
            sequenceLength = fragment;
        }
    }
    if(depth == 0) {
        std::size_t secondLongestFragment = 0;
        for(auto& fragment : restrictiveDigestionResult) {
            if(fragment > secondLongestFragment && fragment < sequenceLength) {
                secondLongestFragment = fragment;
            }
        }

        std::size_t firstFragment = sequenceLength - secondLongestFragment;
        auto firstFragmentPositionInResult = std::find(std::begin(restrictiveDigestionResult), std::end(restrictiveDigestionResult), firstFragment);
        auto firstFragmentPositionBackwards = std::find(std::begin(restrictiveDigestionResult), std::end(restrictiveDigestionResult), sequenceLength - firstFragment);

        if(firstFragmentPositionInResult != std::end(restrictiveDigestionResult) && firstFragmentPositionBackwards != std::end(restrictiveDigestionResult)) {
            restrictiveDigestionResult.erase(firstFragmentPositionInResult);
            restrictiveDigestionResult.erase(firstFragmentPositionBackwards);
            map[depth] = firstFragment;
            findRestrictionMap(restrictiveDigestionResult, map, depth + 1);
        }

        return false;
    } else {
        for(auto& fragmentLength : restrictiveDigestionResult) {
            std::cout << "Depth: " << depth << " : " << fragmentLength << std::endl;
            std::size_t summedMapFragments = 0;
            for(auto& fragment : map) {
                std::cout << fragment << " ";
                summedMapFragments += fragment;
            }
            std::cout << std::endl;
            
            auto fragmentPositionInResult = std::find(std::begin(restrictiveDigestionResult), std::end(restrictiveDigestionResult), summedMapFragments);
            auto fragmentPositionBackwards = std::find(std::begin(restrictiveDigestionResult), std::end(restrictiveDigestionResult), sequenceLength - summedMapFragments);
            if(fragmentPositionInResult != std::end(restrictiveDigestionResult) && fragmentPositionBackwards != std::end(restrictiveDigestionResult)) {
                restrictiveDigestionResult.erase(fragmentPositionInResult);
                restrictiveDigestionResult.erase(fragmentPositionBackwards);
                map[depth] = fragmentLength;
                findRestrictionMap(restrictiveDigestionResult, map, depth + 1);
            }

            if(depth == map.size()) break;
        }
    }

    return false;
}
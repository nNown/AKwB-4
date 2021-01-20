#include <iostream>
#include <instance.h>
#include <instance_parser.h>
#include <instance_generator.h>
#include <cstdlib>
#include <time.h>
#include <tuple>
#include <map>

bool findRestrictionMap(Instance& instance, const std::size_t& depth);

int main(void) {
    std::srand(std::time(NULL));
    
    InstanceParser* instanceParser = InstanceParser::Parser();
    InstanceGenerator* instanceGenerator = InstanceGenerator::Generator();

    auto instance = Instance(instanceParser->LoadInstance("./tests/instance.rdi")); 

    // auto generatedInstance = instanceGenerator->GenerateInstance({ 3, 8 }, 3, false);
    // instanceParser->SaveInstance(generatedInstance.first, "./tests");
    // instanceParser->SaveInstance(generatedInstance.second, "./results");

    // auto instance = Instance(generatedInstance.first);
    if(instance.Map().size() > 0) {
        findRestrictionMap(instance, 0);
    }

    return 0;
}

bool findRestrictionMap(Instance& instance, const std::size_t& depth) {
    std::size_t mapLength = 0;
    for(auto& fragment : instance.Map()) {
        mapLength += fragment;
    }

    if(depth == instance.Map().size()) {
        if(mapLength == instance.SequenceLength()) {
            for(auto& fragment : instance.Map()) {
                std::cout << fragment << " ";
            }
            std::cout << std::endl;
            return true;
        }
        return false;
    }

    if(depth == 0) {
        std::size_t secondLongestFragment = 0;
        for(auto& [ fragment, usedCount ] : instance.RestrictiveDigestion()) {
            if(fragment > secondLongestFragment && fragment < instance.SequenceLength()) {
                secondLongestFragment = fragment;
            }
        }

        std::size_t firstFragment = instance.SequenceLength() - secondLongestFragment;
        if(instance.checkFragmentViability(firstFragment)) {
            instance.Map()[depth] = firstFragment;

            instance.RestrictiveDigestion()[firstFragment] = 1;
            instance.RestrictiveDigestion()[secondLongestFragment] = 1;

            findRestrictionMap(instance, depth + 1);
        }
    } else {
        for(auto& [ fragment, usedCount ] : instance.RestrictiveDigestion()) {
            if(instance.checkFragmentViability(fragment)) {
                for(std::size_t i = 0; i < instance.Map().size(); i++) {
                    std::size_t currentFragment = 0;
                    if(instance.Map()[i] == 0) break;
                    for(std::size_t j = i; j < instance.Map().size(); j++) {
                        currentFragment += instance.Map()[j];
                    }
                    instance.RestrictiveDigestion()[currentFragment] = 1;
                }
                instance.RestrictiveDigestion()[fragment] = 1;
                instance.RestrictiveDigestion()[mapLength + fragment] = 1;

                instance.Map()[depth] = fragment;
                findRestrictionMap(instance, depth + 1);
                instance.Map()[depth] = 0;

                for(std::size_t i = 0; i < instance.Map().size(); i++) {
                    std::size_t currentFragment = 0;
                    if(instance.Map()[i] == 0) break;
                    for(std::size_t j = i; j < instance.Map().size(); j++) {
                        currentFragment += instance.Map()[j];
                    }
                    instance.RestrictiveDigestion()[currentFragment] = 0;
                }
                instance.RestrictiveDigestion()[fragment] = 0;
                instance.RestrictiveDigestion()[mapLength + fragment] = 0;
            }

        }  
    }
    return false;
}
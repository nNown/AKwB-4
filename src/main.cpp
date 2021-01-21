#include <iostream>
#include <instance.h>
#include <instance_parser.h>
#include <instance_generator.h>
#include <cstdlib>
#include <time.h>
#include <tuple>
#include <map>

bool findRestrictionMap(Instance& instance, const int& depth);

int main(void) {
    std::srand(std::time(NULL));
    
    InstanceParser* instanceParser = InstanceParser::Parser();
    InstanceGenerator* instanceGenerator = InstanceGenerator::Generator();

    auto instance = Instance(instanceParser->LoadInstance("./tests/instance.rdi")); 

    // auto generatedInstance = instanceGenerator->GenerateInstance({ 14, 56 }, 14, false);
    // instanceParser->SaveInstance(generatedInstance.first, "./tests");
    // instanceParser->SaveInstance(generatedInstance.second, "./results");

    // auto instance = Instance(generatedInstance.first);
    if(instance.ExpectedMapFragments() > 0) {
        findRestrictionMap(instance, 0);
    }

    return 0;
}

bool findRestrictionMap(Instance& instance, const int& depth) {
    int mapLength = 0;
    for(auto& fragment : instance.Map()) {
        mapLength += fragment;
    }

    if(depth == instance.ExpectedMapFragments()) {
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
        int secondLongestFragment = 0;
        for(auto& [ fragment, usedCount ] : instance.RestrictiveDigestion()) {
            if(fragment > secondLongestFragment && fragment < instance.SequenceLength()) {
                secondLongestFragment = fragment;
            }
        }

        int firstFragment = instance.SequenceLength() - secondLongestFragment;
        if(instance.useFragment(firstFragment, false)) {
            instance.Map().push_back(firstFragment);
            findRestrictionMap(instance, depth + 1);
        }
    } else {
        for(auto& [ fragment, usedCount ] : instance.RestrictiveDigestion()) {
            if(instance.useFragment(fragment, false)) {
                instance.Map().push_back(fragment);

                if(!findRestrictionMap(instance, depth + 1)) {
                    instance.Map().pop_back();
                    instance.useFragment(fragment, true);
                }

            }

        }  
    }
    return false;
}
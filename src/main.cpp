#include <iostream>
#include <chrono>
#include <instance.h>
#include <instance_parser.h>
#include <instance_generator.h>
#include <cstdlib>
#include <time.h>
#include <tuple>
#include <map>

bool findRestrictionMap(Instance& instance, const int& depth, bool& found);

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    
    InstanceParser* instanceParser = InstanceParser::Parser();
    InstanceGenerator* instanceGenerator = InstanceGenerator::Generator();
    
    auto instance = Instance(instanceParser->LoadInstance(argv[1]));
    if(instance.ExpectedMapFragments() > 0) {
        std::cout << "Restriction map: "; 

        bool answer = false;
        auto start = std::chrono::high_resolution_clock::now();
        findRestrictionMap(instance, 0, answer);
        auto stop = std::chrono::high_resolution_clock::now();

        if(!answer) std::cout << "not found" << std::endl;
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Got in " << (duration.count() * 0.000001) << " seconds" << std::endl;

    } else {
        std::cout << "Instance doesn't contain any possible result" << std::endl;
    }

    return 0;
}

bool findRestrictionMap(Instance& instance, const int& depth, bool& found) {
    if(depth == instance.ExpectedMapFragments()) {
        int mapLength = 0;
        for(auto& fragment : instance.Map()) {
            mapLength += fragment;
        }

        if(mapLength == instance.SequenceLength()) {
            found = true;
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
            findRestrictionMap(instance, depth + 1, found);
        }
    } else {
        // int uniqueFragment = -1;
        for(auto& [ fragment, usedCount ] : instance.RestrictiveDigestion()) {
            // if(fragment == uniqueFragment) continue;

            // uniqueFragment = fragment;
            if(instance.useFragment(fragment, false)) {
                instance.Map().push_back(fragment);

                if(!findRestrictionMap(instance, depth + 1, found)) {
                    // uniqueFragment = -1;
                    instance.Map().pop_back();
                    instance.useFragment(fragment, true);
                }

            }
        }  
    }
    return false;
}
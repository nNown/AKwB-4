#include <iostream>
#include <instance_parser.h>
#include <instance_generator.h>

int main(void) {
    InstanceParser* instanceParser = InstanceParser::Parser();
    InstanceGenerator* instanceGenerator = InstanceGenerator::Generator();

    // std::vector<std::size_t> instance = instanceParser->LoadInstance("./test.txt");
    // instanceParser->SaveInstance(instance, "./tests");

    auto restrictiveDigestionMap = instanceGenerator->RestrictiveDigestionMap();
    for(auto& [ instance, result ] : restrictiveDigestionMap) {
        for(auto& fragmentLength : instance) {
            std::cout << fragmentLength << " ";
        }
        std::cout << std::endl;
        for(auto& fragmentLength : result) {
            std::cout << fragmentLength << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
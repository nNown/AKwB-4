#include <iostream>
#include <instance_parser.h>
#include <instance_generator.h>
#include <cstdlib>
#include <time.h>

int main(void) {
    std::srand(std::time(NULL));
    
    InstanceParser* instanceParser = InstanceParser::Parser();
    InstanceGenerator* instanceGenerator = InstanceGenerator::Generator();

    auto instance = instanceGenerator->GenerateInstance({ 2, 8 }, 2, true);
    instanceParser->SaveInstance(instance.first, "./tests");
    instanceParser->SaveInstance(instance.second, "./results");
    std::cout << std::endl;

    return 0;
}
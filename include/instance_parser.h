#pragma once

#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <vector>
#include <sstream>

class InstanceParser {
    private:
        static InstanceParser* _parser;
        InstanceParser();
        
        
    public:
        std::vector<int> LoadInstance(const std::string& path);
        void SaveInstance(const std::vector<int>& instance, const std::string& path);
        static InstanceParser* Parser();
        ~InstanceParser();
};
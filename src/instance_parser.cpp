#include <instance_parser.h>

InstanceParser* InstanceParser::_parser = nullptr;
InstanceParser::InstanceParser() {}

std::vector<std::size_t> InstanceParser::LoadInstance(const std::string& path) {
    std::ifstream instanceFile = std::ifstream(path, std::ios::in);
    if(!instanceFile.is_open()) throw std::runtime_error("Failed to open file");

    std::vector<std::size_t> sequence = std::vector<std::size_t>();

    std::string fragmentLength;
    while(instanceFile >> fragmentLength) {
        try {
            sequence.push_back(std::stoi(fragmentLength));
        } catch(const std::exception& err) {
            throw err;
            // throw std::runtime_error("Instance file contains other characters than digits");
        }
    }

    instanceFile.close();
    return sequence;
}

void InstanceParser::SaveInstance(const std::vector<std::size_t>& instance, const std::string& path) {
    std::stringstream filename;
    filename << path << "/" << "instance" << ".rdi";

    int filesWithTakenName = 0;
    while(std::filesystem::exists(filename.str())) {
        ++filesWithTakenName;
        filename.str(std::string());
        filename << path << "/" << "instance" << filesWithTakenName << ".rdm";
    }

    std::ofstream instanceFile = std::ofstream(filename.str(), std::ios::out);
    for(auto& value : instance) {
        instanceFile << value << " ";
    }
    instanceFile.close();
}

InstanceParser* InstanceParser::Parser() {
    if(_parser == nullptr) {
        _parser = new InstanceParser();
    }

    return _parser;
}

InstanceParser::~InstanceParser() {}
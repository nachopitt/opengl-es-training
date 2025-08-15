#include "utils/FileReader.h"
#include <fstream>
#include <iostream>

namespace rendix::utils {

    std::string FileReader::readTextFile(const std::string &path) const {
        std::string buffer;
        std::ifstream file(path);

        if (!file.is_open())
        {
            std::cerr << "Failed to open text file: " << path << std::endl;
            return "";
        }

        file.seekg(0, std::ios::end);
        buffer.resize(file.tellg());
        file.seekg(0);
        file.read(&buffer[0], buffer.size());

        return buffer;
    }

    std::vector<char> FileReader::readBinaryFile(const std::string &path) const {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Failed to open binary file: " << path << std::endl;
            return std::vector<char>();
        }

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        if (!file.read(buffer.data(), size))
        {
            std::cerr << "Failed to read binary file: " << path << std::endl;
            return std::vector<char>();
        }

        return buffer;
    }
}

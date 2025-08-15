#ifndef RENDIX_UTILS_I_FILE_READER_H
#define RENDIX_UTILS_I_FILE_READER_H

#include <string>
#include <vector>

namespace rendix::utils {

    class IFileReader
    {
    public:
        virtual ~IFileReader() = default;
        virtual std::string readTextFile(const std::string& path) const = 0;
        virtual std::vector<char> readBinaryFile(const std::string &path) const = 0;
    };
}
#endif // RENDIX_UTILS_I_FILE_READER_H

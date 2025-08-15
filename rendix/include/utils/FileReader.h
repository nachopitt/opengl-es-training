#ifndef RENDIX_UTILS_FILE_READER_H
#define RENDIX_UTILS_FILE_READER_H

#include "utils/IFileReader.h"

namespace rendix::utils
{

    class FileReader : public IFileReader
    {
    public:
        FileReader() = default;
        ~FileReader() = default;
        std::string readTextFile(const std::string &path) const override;
        std::vector<char> readBinaryFile(const std::string &path) const override;
    };
}
#endif // RENDIX_UTILS_FILE_READER_H

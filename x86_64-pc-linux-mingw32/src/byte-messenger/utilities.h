#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>
#include <string>
#include <sys/types.h>
#include <vector>

namespace util
{
    std::string getTimestamp();
    std::string getKeyStringFromPair(std::string pairString);
    std::string getValueStringFromPair(std::string pairString);
    std::string getMessageFilename(uint32_t id);
    uint32_t getIdFromFilename(std::string name);
    std::string getStringFromData(const std::vector<uint8_t> &data);
    std::string getStringFromNData(const std::vector<uint8_t> &data, size_t length);
    std::vector<uint8_t> getDataFromString(const std::string &dataString);
}

#endif // UTILITIES_H

#include "utilities.h"

#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

std::string util::getTimestamp()
{
    std::time_t now = std::time(nullptr);
    return std::asctime(std::localtime(&now));
}

std::string util::getKeyStringFromPair(std::string pairString)
{
    std::string result;

    size_t pos = pairString.find('=');
    if (pos != std::string::npos)
    {
        result = pairString.substr(0, pos);
    }
    else
    {
        return pairString;
    }

    return result;
}

std::string util::getValueStringFromPair(std::string pairString)
{
    std::string result;

    size_t pos = pairString.find('=');
    if (pos != std::string::npos && pos + 1 < pairString.size())
    {
        result = pairString.substr(pos + 1);
    }
    else
    {
        return pairString;
    }

    return result;
}

std::string util::getMessageFilename(uint32_t id)
{
    std::stringstream ss;

    ss << "message";
    ss << std::setw(6) << std::setfill('0') << id;
    ss << ".txt";

    return ss.str();
}

uint32_t util::getIdFromFilename(std::string name)
{
    // Message filename format: "message######.txt" where ###### = the ID number of the message
    // as a decimal number with prefill 0's.  Example: "message000001.txt"
    // Position after prefext "message" = 7
    // Position after ID portion = 7 + 6 = 13
    std::string idString = name.substr(7, 13);

    return std::stoul(idString);
}

std::string util::getStringFromData(const std::vector<uint8_t> &data)
{
    std::stringstream ss;

    for (size_t index = 0; index < data.size(); index++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(data[index]);

        if (index < data.size())
        {
            ss << ' ';
        }
    }

    return ss.str();
}

std::string util::getStringFromNData(const std::vector<uint8_t> &data, size_t length)
{
    std::stringstream ss;

    for (size_t index = 0; index < data.size() && index < length; index++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(data[index]);

        if (index < data.size())
        {
            ss << ' ';
        }
    }

    return ss.str();
}

std::vector<uint8_t> util::getDataFromString(const std::string &dataString)
{
    std::vector<uint8_t> result;
    std::istringstream iss(dataString);
    std::string token;

    while (iss >> token)
    {
        uint8_t byte = static_cast<uint8_t>(std::stoul(token, nullptr, 16));
        result.push_back(byte);
    }

    return result;
}

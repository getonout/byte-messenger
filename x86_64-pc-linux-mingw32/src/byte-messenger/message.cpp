#include "message.h"

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "utilities.h"

Message::Message() : id(0)
{

}

Message::~Message()
{

}

void Message::setId(uint32_t value)
{
    id = value;
}

uint32_t Message::getId()
{
    return id;
}

void Message::setName(const char *value)
{
    name = value;
}

std::string Message::getName()
{
    return name;
}

size_t Message::getLength()
{
    return data.size();
}

void Message::addByte(uint8_t value)
{
    data.push_back(value);
}

void Message::addBytes(const std::vector<uint8_t> &bytes)
{
    data.insert(data.end(), bytes.begin(), bytes.end());
}

bool Message::insertByte(uint8_t value, size_t pos)
{
    if (pos > data.size())
    {
        return false;
    }

    data.insert(data.begin() + pos, value);

    return true;
}

void Message::clear()
{
    data.clear();
}

bool Message::removeByte(size_t pos)
{
    if (pos > data.size())
    {
        return false;
    }

    data.erase(data.begin() + pos);

    return true;
}

void Message::setData(const std::vector<uint8_t> &newData)
{
    data = newData;
}

const std::vector<uint8_t> &Message::getData()
{
    return data;
}

std::string Message::getString()
{
    std::string result;

    for (uint8_t element : data)
    {
        std::stringstream ss;
        ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(element);
        result += ss.str();
    }

    return result;
}

void Message::printInfo()
{
    std::cout << "Message Info:" << std::endl;
    std::cout << "  ID=" << id << std::endl;
    std::cout << "  Name=" << name << std::endl;
    std::cout << "  Data={" << getString() << "}" << std::endl;
}

bool Message::writeToFile()
{
    std::ofstream outFile(util::getMessageFilename(id));

    if (!outFile)
    {
        return false;
    }

    outFile << "ID=" << id << std::endl;
    outFile << "Name=" << name << std::endl;
    outFile << "Data Length=" << data.size() << std::endl;

    for (size_t index = 0; index < data.size(); index++)
    {
        outFile << "Byte[" << index << "]=" << static_cast<unsigned int>(data[index]) << std::endl;
    }

    outFile.close();

    return true;
}

bool Message::readFromFile()
{
    std::ifstream inFile(util::getMessageFilename(id));

    if (!inFile)
    {
        return false;
    }

    std::string inLine;

    //ID
    std::getline(inFile, inLine);
    // Ignore this because the ID is related to the file name so it should not be changed

    //Name
    std::getline(inFile, inLine);
    //setName(getValueAfterEqual(inLine).c_str());
    setName(util::getValueStringFromPair(inLine).c_str());

    //Data Length
    std::getline(inFile, inLine);
    //size_t length = std::stoul(getValueAfterEqual(inLine));
    size_t length = std::stoul(util::getValueStringFromPair(inLine));

    //Data
    data.clear();
    for (size_t index = 0; index < length; index++)
    {
        std::getline(inFile, inLine);
        uint8_t byte = std::stoul(util::getValueStringFromPair(inLine));
        data.push_back(byte);
    }

    inFile.close();

    return true;
}

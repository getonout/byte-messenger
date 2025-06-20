#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>
#include <vector>

class Message
{
public:
    Message();
    ~Message();

    void setId(uint32_t value);
    uint32_t getId();
    void setName(const char *value);
    std::string getName();
    size_t getLength();
    void addByte(uint8_t value);
    void addBytes(const std::vector<uint8_t> &bytes);
    bool insertByte(uint8_t value, size_t pos);
    void clear();
    bool removeByte(size_t pos);
    void setData(const std::vector<uint8_t> &newData);
    const std::vector<uint8_t> &getData();
    std::string getString();
    void printInfo();

    bool writeToFile();
    bool readFromFile();

private:
    uint32_t id;
    std::string name;
    std::vector<uint8_t> data;
};

#endif // MESSAGE_H

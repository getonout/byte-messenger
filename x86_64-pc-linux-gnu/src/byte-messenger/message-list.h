#ifndef MESSAGE_LIST_H
#define MESSAGE_LIST_H

#include <cstdint>
#include <vector>

#include "message.h"

#define LIST_FILENAME "message-list.txt"

class MessageList
{
public:
    MessageList();
    ~MessageList();

    enum class fields_t {ALL,
                         IDS_ONLY,
                         NAMES_ONLY,
                         IDS_NAMES_ONLY};

    size_t getQuantity();
    bool messageExists(uint32_t id);
    bool addMessage(Message &value);
    Message &getMessage(uint32_t id);
    void removeMessage(uint32_t id);
    bool updateMessage(Message &value);
    void printInfo(fields_t level = fields_t::ALL);
    bool writeToFiles();
    bool readFromFiles();
    std::vector<Message> getMessages();

private:
    std::vector<Message> messages;
    Message emptyMessage;


};

#endif // MESSAGE_LIST_H

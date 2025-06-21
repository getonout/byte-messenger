/**
 * \file message-list.cpp
 * \brief Source implementation file for the MessageList class.
 */

#include "message-list.h"

#include <cstdint>
#include <fstream>
#include <iostream>

#include "utilities.h"

MessageList::MessageList()
{

}

MessageList::~MessageList()
{

}

size_t MessageList::getQuantity()
{
    return messages.size();
}

bool MessageList::messageExists(uint32_t id)
{
    for (Message element : messages)
    {
        if (element.getId() == id)
        {
            return true;
        }
    }

    return false;
}

bool MessageList::addMessage(Message &value)
{
    if (messageExists(value.getId()))
    {
        return false;
    }

    messages.push_back(value);

    return true;
}

Message &MessageList::getMessage(uint32_t id)
{
    for (size_t index = 0; index < messages.size(); index++)
    {
        if (messages[index].getId() == id)
        {
            return messages[index];
        }
    }

    return emptyMessage;
}

void MessageList::removeMessage(uint32_t id)
{
    for (size_t index = 0; index < messages.size(); index++)
    {
        if (messages[index].getId() == id)
        {
            messages.erase(messages.begin() + index);
        }
    }
}

bool MessageList::updateMessage(Message &value)
{
    if (!messageExists(value.getId()))
    {
        return false;
    }

    removeMessage(value.getId());
    return addMessage(value);
}

void MessageList::printInfo(fields_t level)
{
    std::cout << "Messages:" << std::endl;

    for (Message element : messages)
    {
        if (level == fields_t::ALL)
        {
            element.printInfo();\
        }
        else if (level == fields_t::IDS_ONLY)
        {
            std::cout << "Message Info:" << std::endl;
            std::cout << "  ID=" << element.getId() << std::endl;
        }
        else if (level == fields_t::NAMES_ONLY)
        {
            std::cout << "Message Info:" << std::endl;
            std::cout << "  Name=" << element.getName() << std::endl;
        }
        else if (level == fields_t::IDS_NAMES_ONLY)
        {
            std::cout << "Message Info:" << std::endl;
            std::cout << "  ID=" << element.getId() << std::endl;
            std::cout << "  Name=" << element.getName() << std::endl;
        }
    }
}

bool MessageList::writeToFiles()
{
    std::ofstream outFile(LIST_FILENAME);

    if (!outFile)
    {
        return false;
    }

    // File contents consists of file names of the message information files.
    for (Message element : messages)
    {
        outFile << util::getMessageFilename(element.getId()) << std::endl;
        element.writeToFile();
    }

    outFile.close();

    return true;
}

bool MessageList::readFromFiles()
{
    messages.clear();

    std::ifstream inFile(LIST_FILENAME);

    if (!inFile)
    {
        return false;
    }

    std::string inLine;

    // File contents consists of the file names of the message information files.
    while (std::getline(inFile, inLine))
    {
        // Read each message information file and add to the list.
        uint32_t id = util::getIdFromFilename(inLine);
        if (id != 0)
        {
            Message message;
            message.setId(id);
            message.readFromFile();
            messages.push_back(message);
        }
    }

    inFile.close();

    return true;
}

std::vector<Message> MessageList::getMessages()
{
    return messages;
}

#ifndef MESSAGE_LIST_H
#define MESSAGE_LIST_H

/**
 * \file message-list.h
 * \brief Source header file for the MessageList class.
 */

#include <cstdint>
#include <vector>

#include "message.h"

#define LIST_FILENAME "message-list.txt"

/**
 * \class MessageList
 * \brief Encapsulates functionality for managing a list of Message instances.
 */
class MessageList
{
public:
    /**
     * Constructor.
     */
    MessageList();
    /**
     * Destructor.
     */
    ~MessageList();

    enum class fields_t {ALL,
                         IDS_ONLY,
                         NAMES_ONLY,
                         IDS_NAMES_ONLY};

    /**
     * Obtains the number of messages contained in the list.
     * \return The number of messages.
     */
    size_t getQuantity();
    /**
     * Determines of a message with the specified ID value already exists within the list.
     * \param id The message ID value to search for.
     * \return true if a message with the specified ID exists within the list and false
     *         otherwise.
     */
    bool messageExists(uint32_t id);
    /**
     * Adds the specified message to the list.
     * \param value Reference to the Message object to add.
     * \return Success result of the operation.
     */
    bool addMessage(Message &value);
    /**
     * Obtains a reference to the Message object for the specified ID.
     * \param id The ID value of the message reference to obtain.
     * \return Reference to the Message object found.  If the specified ID is not found
     *         within the list, a placeholder message is used.
     */
    Message &getMessage(uint32_t id);
    /**
     * Removes the Message object with the specified ID from the list if it exists.
     * \param id The ID value of the Message object to remove from the list.
     */
    void removeMessage(uint32_t id);
    /**
     * Replaces the Message object within the list with the specified Message object.
     * \param value Reference to the Message object to use for replacement.
     * \return Success result of the operation.
     */
    bool updateMessage(Message &value);
    /**
     * Prints the information for the MessageList to stdout.
     * \param level Specifies with fields of the messages that should be printed.
     */
    void printInfo(fields_t level = fields_t::ALL);
    /**
     * Writes all of the information associated with the MessageList object and its
     * contained Message objects to files.  The file name for the MessageList is
     * "message-list.txt".  Refer to Message::writeToFile() for a description of the
     * file names for the Message objects.
     * \return Success result of the operation.
     */
    bool writeToFiles();
    /**
     * Reads the information to be associated with the MessageList object and its
     * contained Message objects from files.  Refer to MessageList::writeToFiles() and
     * Message::writeToFile() for a description of the file names.
     * \return Success result of the operation.
     */
    bool readFromFiles();
    /**
     * Obtains a vector containing all of the Message objects within the list.
     * \return Vector containing the Message objects of the list.
     */
    std::vector<Message> getMessages();

private:
    std::vector<Message> messages; ///< Vector containing the Message objects.
    Message emptyMessage; ///< Place holder message used when a unfound message ID value
                          ///< is supplied.                  
};

#endif // MESSAGE_LIST_H

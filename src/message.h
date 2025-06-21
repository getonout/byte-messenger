#ifndef MESSAGE_H
#define MESSAGE_H

/**
 * \file message.h
 * \brief Source header file for the Message class.
 */

#include <cstdint>
#include <string>
#include <vector>

/**
 * \class Message
 * \brief Encapsulates functionality relating to messages.
 */
class Message
{
public:
    /**
     * Constructor.
     */
    Message();
    /**
     * Destructor.
     */
    ~Message();

    /**
     * Sets the ID value associated with the message.
     * \param value The new ID value.
     */
    void setId(uint32_t value);
    /**
     * Obtains the ID value associated with the message.
     * \return The message ID value.
     */
    uint32_t getId();
    /**
     * Sets the name string associated with the message.
     * \param value String representing the name of the message.
     */
    void setName(const char *value);
    /**
     * Obtains the name string associated with the message.
     * \return The name string associated with the message.
     */
    std::string getName();
    /**
     * Obtains the length of the message data in bytes.
     * \return The Length of the message data in bytes.
     */
    size_t getLength();
    /**
     * Appends a byte of data to the message.
     * \param value The value of the byte to append to the message.
     */
    void addByte(uint8_t value);
    /**
     * Appends multiple bytes of data to the message.
     * \param bytes Vector of data bytes to append to the message.
     */
    void addBytes(const std::vector<uint8_t> &bytes);
    /**
     * Inserts a byte of data into the specified position with the message data.
     * \param value The byte value to insert.
     * \param pos The index position within the message data to insert the new byte value.
     * \return Success result of the operation.
     */
    bool insertByte(uint8_t value, size_t pos);
    /**
     * Clears out all of the message data.
     */
    void clear();
    /**
     * Removes one byte of data at the specified index position of the message data.
     * \param pos The index position within the message data to remove one byte.
     * \return Success result of the operation.
     */
    bool removeByte(size_t pos);
    /**
     * Replaces the current data of the message with the supplied data.
     * \param newData Vector containing the new data for replacement.
     */
    void setData(const std::vector<uint8_t> &newData);
    /**
     * Obtains a reference to the message data.
     * \return Reference to a vector containing the message data.
     */
    const std::vector<uint8_t> &getData();
    /**
     * Obtains a string representing the string values of the message data.  Converted
     * data values are in hexadecimal format.
     * \return String representing the message data.
     */
    std::string getString();
    /**
     * Print all information about the associated message to stdout.
     */
    void printInfo();

    /**
     * Writes the information for the associated message to a file.  The name of the
     * file is dependent upon the ID of the message.  The format of the message information
     * file name is "message######.txt" where ###### is a six-digit decimal value of the
     * message ID pre-filled with 0's (Ex. the file name for message ID 1 =
     * "message000001.txt".
     * \return Success result of the operation.
     */
    bool writeToFile();
    /**
     * Reads the information for the associated message from a file.  See writeToFile() for
     * information regarding the file name.
     * \return Success result of the operation.
     */
    bool readFromFile();

private:
    uint32_t id; ///< The ID value of the associated message.
    std::string name; ///< String representing the name of the associated message.
    std::vector<uint8_t> data; ///< The data bytes of the associated message.
};

#endif // MESSAGE_H

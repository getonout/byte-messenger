#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * \file utilities.h
 * \brief Source header file for utility routines.
 */

#include <cstdint>
#include <string>
#include <sys/types.h>
#include <vector>

namespace util
{
    /**
     * Obtains a string representing a timestamp of the current time.
     * \return The timestamp string.
     */
    std::string getTimestamp();
    /**
     * Obtains a string of the key portion of a key-value pair.  The key-value pair
     * format is <key>=<value>.
     * \param pairString A string containing the entire key-value pair.
     * \return The key string.
     */
    std::string getKeyStringFromPair(std::string pairString);
    /**
     * Obtains a string of the value portion of a key-value pair.  The key-value pair
     * format is <key>=<value>.
     * \param pairString A string containing the entire key-value pair.
     * \return The value string.
     */
    std::string getValueStringFromPair(std::string pairString);
    /**
     * Obtains the file name of the information storage file associated with the message
     * with a specified ID value.  The file name format is "message######.txt" where
     * ###### is a six-digit decimal representation of the ID value pre-filled with 0's.
     * \param id ID value of the file's message.
     * \return String representation of the associated file name.
     */
    std::string getMessageFilename(uint32_t id);
    /**
     * Extracts the ID value from a string containing a file name for message information.
     * \param name String containing the file name.
     * \return the ID value for the associated message information file.
     */
    uint32_t getIdFromFilename(std::string name);
    /**
     * Constructs a string representation of a vector of binary data.  The data values
     * will presented in hexadecimal format.
     * \param data Reference to a vector contaning the data bytes to convert.
     * \return String representation of the binary data.
     */
    std::string getStringFromData(const std::vector<uint8_t> &data);
    /**
     * Constructs a string representation of a specified quantity of data bytes from a
     * vector of binary data.  The data values will be presented in hexadecimal format.
     * \param data Reference to a vector contaning the data bytes to convert.
     * \param length The number of data bytes to convert.
     * \return String representation of the binary data.
     */
    std::string getStringFromNData(const std::vector<uint8_t> &data, size_t length);
    /**
     * Constructs a vector of binary data conforming to the values in the supplied
     * string representation of the data.
     * \param dataString The string representation of the data to convert.
     * \return Vector containing the converted binary data.
     */
    std::vector<uint8_t> getDataFromString(const std::string &dataString);
}

#endif // UTILITIES_H

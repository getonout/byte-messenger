#ifndef MESSAGE_WINDOW_H
#define MESSAGE_WINDOW_H

/**
 * \file message-window.h
 * \brief Source header file for the MessageWindow class.
 */

#include <cstdint>
#include <cstring>
#include <QDialog>
#include <vector>

#include "message.h"

namespace Ui {
class MessageWindow;
}

/**
 * \class MessageWindow
 * \brief Implements a GUI window to provide the user with functionality for managing the
 *        information associated with a Message.
 */
class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor.
     */
    explicit MessageWindow(QWidget *parent = nullptr);
    /**
     * Destructor.
     */
    ~MessageWindow();

    /**
     * Sets the ID value of the Message object associated with the window.
     * \param value The new ID value of the Message object.
     */
    void setMessageId(uint32_t value);
    /**
     * Obtains the ID value of the Message object associated with the window.
     * \return The ID value of the associated Message object.
     */
    uint32_t getMessageId();
    /**
     * Sets the name string of the Message object associated with the window.
     * \param value The new string value to set the Message object's name to.
     */
    void setName(std::string value);
    /**
     * Obtains a string representing the name of the associated Message object.
     * \return The name string of the associated Message object.
     */
    std::string getName();
    /**
     * Sets the binary data for the Message object associated with the window.
     * \param data Reference to a vector of data bytes to used for replacing the
     *        Message object's data.
     */
    void setData(const std::vector<uint8_t> &data);
    /**
     * Obtains the binary data for the Message object associated with the window.
     * \return Vector containing the Message object's binary data.
     */
    std::vector<uint8_t> getData();
    /**
     * Sets the enable state of the "sendButton".
     * \param enable The new enable state.
     */
    void enableSendButton(bool enable = true);

public slots:
    /**
     * Qt handler for handling "loadButton" clicking.
     */
    void handleLoadButton();
    /**
     * Qt handler for handling "saveButton" clicking.
     */
    void handleSaveButton();
    /**
     * Qt handler for handling "sendButton" clicking.
     */
    void handleSendButton();
    /**
     * Qt handler for handling "addButton" clicking.
     */
    void handleAddButton();

private:
    Ui::MessageWindow *ui;

    Message message; ///< The Message object associated with the window.
};

#endif // MESSAGE_WINDOW_H

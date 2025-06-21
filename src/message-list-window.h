#ifndef MESSAGE_LIST_WINDOW_H
#define MESSAGE_LIST_WINDOW_H

/**
 * \file message-list-window.h
 * \brief Source header file for the MessageListWindow class.
 */

#include <QDialog>
#include <QListWidget>

#include "message.h"
#include "message-list.h"

namespace Ui {
class MessageListWindow;
}

/**
 * \class MessageListWindow
 * \brief Implements a GUI window which provides the user a functionality for managing a
 *        MessageList.
 */
class MessageListWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor.
     */
    explicit MessageListWindow(QWidget *parent = nullptr);
    /**
     * Destructor.
     */
    ~MessageListWindow();
    /**
     * Initializes the MessageList associated with the window.
     */
    void initialize();
    /**
     * Adds the specified Message object to the associated MessageList and updates the
     * list widget for displaying the MessageList.
     * \param message Reference to the Message object to add to the associated MessageList.
     */
    void addMessage(Message &message);

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
     * Qt handler for handling "openButton" clicking.
     */
    void handleOpenButton();

private:
    Ui::MessageListWindow *ui;

    MessageList messageList; ///< MessageList object associated with the window.
    QListWidget *pList; ///< Convenience variable for referring to the widget for displaying
                        ///< the MessageList information.

    /**
     * Updates the list widget for displaying the MessageList with the information for the
     * supplied Message object.
     * \param message Reference to the Message object for updating the list widget.
     */
    void addMessageToList(Message &message);
    /**
     * Clears out the list widget used for displaying MessageList information.
     */
    void clearMessageList();
};

#endif // MESSAGE_LIST_WINDOW_H

/**
 * \file message-list-window.cpp
 * \brief Source implementation file for the MessageListWindow class.
 */

#include "message-list-window.h"
#include "ui_message-list-window.h"

#include <cstdlib>
#include <iomanip>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <sstream>
#include <string>

#include "message.h"
#include "message-list.h"
#include "message-window.h"
#include "object-manager.h"

MessageListWindow::MessageListWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageListWindow)
{
    ui->setupUi(this);

    pList = this->findChild<QListWidget *>("messageList");
}

MessageListWindow::~MessageListWindow()
{
    delete ui;
}

void MessageListWindow::initialize()
{
    messageList.readFromFiles();

    for (Message message : messageList.getMessages())
    {
        addMessage(message);
    }
}

void MessageListWindow::addMessage(Message &message)
{
    if (messageList.messageExists(message.getId()))
    {
        messageList.removeMessage(message.getId());
    }

    messageList.addMessage(message);
    addMessageToList(message);
}

void MessageListWindow::handleLoadButton()
{
    clearMessageList();
    initialize();
}

void MessageListWindow::handleSaveButton()
{
    messageList.writeToFiles();
}

#include <iostream>

void MessageListWindow::handleOpenButton()
{
    // Get selected item (if any)
    QList<QListWidgetItem *> selectedItems = pList->selectedItems();

    if (selectedItems.isEmpty())
    {
        return;
    }

    // Item selection is single selection, but the selection query will only return
    // a list.  The list should only contain one item, so just get the first item of the
    // list.
    QListWidgetItem *pItem = selectedItems.first();
    QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(pList->itemWidget(pItem));
    std::stringstream ss(pLineEdit->text().toStdString());
    std::string idString;

    // Obtain the ID portion of the text from the selected item.
    std::getline(ss, idString, ':');
    uint32_t id = std::strtoul(idString.c_str(), nullptr, 10);

    // Obtain the associated message information from the MessageList using the ID
    // and update the message information displayed on the window.
    Message message = messageList.getMessage(id);

    MessageWindow *pWindow = ObjectManager::getMessageWindow();
    pWindow->setMessageId(message.getId());
    pWindow->setName(message.getName());
    pWindow->setData(message.getData());
}

void MessageListWindow::addMessageToList(Message &message)
{
    std::string line;
    std::stringstream ss;

    ss << std::setw(6) << std::setfill('0') << message.getId();
    line += ss.str();
    line += ": ";
    line += message.getName();

    QLineEdit *pLineEdit = new QLineEdit();
    pLineEdit->setReadOnly(true);
    pLineEdit->setText(line.c_str());
    QListWidgetItem *pItem = new QListWidgetItem(pList);
    pList->addItem(pItem);
    pList->setItemWidget(pItem, pLineEdit);

    //TODO: Fix sorting
}

void MessageListWindow::clearMessageList()
{
    pList->clear();
}

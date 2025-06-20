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

    QListWidgetItem *pItem = selectedItems.first();
    QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(pList->itemWidget(pItem));
    std::stringstream ss(pLineEdit->text().toStdString());
    std::string idString;

    std::getline(ss, idString, ':');
    uint32_t id = std::strtoul(idString.c_str(), nullptr, 10);

    Message message = messageList.getMessage(id);

    std::cout << "message.getId()=" << message.getId() << std::endl;
    std::cout << "message.getName()=" << message.getName() << std::endl;
    std::cout << "message.getString()=" << message.getString() << std::endl;

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

#include "message-window.h"
#include "ui_message-window.h"

#include <cstdint>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <QFontDatabase>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#ifdef WIN_BUILD
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <sys/types.h>
#include <vector>

#include "message-list-window.h"
#include "object-manager.h"
#include "utilities.h"

MessageWindow::MessageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageWindow)
{
    ui->setupUi(this);

    QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(12);
    this->findChild<QTextEdit *>("dataEdit")->setFont(fixedFont);
}

MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::setMessageId(uint32_t value)
{
    this->findChild<QSpinBox *>("messageIdSpinBox")->setValue(value);
}

uint32_t MessageWindow::getMessageId()
{
    return this->findChild<QSpinBox *>("messageIdSpinBox")->value();
}

void MessageWindow::setName(std::string value)
{
    this->findChild<QLineEdit *>("nameEdit")->setText(value.c_str());
}

std::string MessageWindow::getName()
{
    return this->findChild<QLineEdit *>("nameEdit")->text().toStdString();
}

void MessageWindow::setData(const std::vector<uint8_t> &data)
{
    this->findChild<QTextEdit *>("dataEdit")->setText(util::getStringFromData(data).c_str());
    message.setData(data);
}

std::vector<uint8_t> MessageWindow::getData()
{
    std::string dataString = this->findChild<QTextEdit *>("dataEdit")->toPlainText().toStdString();

    return util::getDataFromString(dataString);
}

void MessageWindow::enableSendButton(bool enable)
{
    this->findChild<QPushButton *>("sendButton")->setEnabled(enable);
}

void MessageWindow::handleLoadButton()
{
    message.setId(getMessageId());
    message.readFromFile();
    setName(message.getName());
    setData(message.getData());
}

void MessageWindow::handleSaveButton()
{
    message.setId(getMessageId());
    message.setName(getName().c_str());
    message.clear();
    message.addBytes(getData());
    message.writeToFile();
}

void MessageWindow::handleSendButton()
{
    const std::vector<uint8_t> &data = message.getData();

    std::cout << "MessageWindow::handleSendButton(): sending data, peer socket = " << ObjectManager::getPeerSocket()
              << " data.size() = " << data.size() << std::endl;

#ifdef WIN_BUILD
    u_long mode = 1;
    ioctlsocket(ObjectManager::getPeerSocket(), FIONBIO, &mode);

    ssize_t result = send(ObjectManager::getPeerSocket(), reinterpret_cast<const char *>(data.data()), data.size(), 0); // Winsock2 does not have MSG_DONTWAIT
#else
    ssize_t result = send(ObjectManager::getPeerSocket(), data.data(), data.size(), MSG_DONTWAIT);
#endif

    if (result > 0)
    {
        ObjectManager::getBasicDisplay()->addNLine(data, result);
    }
    else
    {
        std::cerr << "MessageWindow::handleSendButton(): send() error = " << errno << std::endl;
        ObjectManager::getBasicDisplay()->addString("Error sending data!");
    }
}

void MessageWindow::handleAddButton()
{
    message.setId(getMessageId());
    message.setName(getName().c_str());
    message.clear();
    message.addBytes(getData());
    ObjectManager::getMessageListWindow()->addMessage(message);
}

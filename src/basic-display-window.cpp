/**
 * \file basic-display-window.cpp
 * \brief Source implementation file for the BasicDisplayWindow class.
 */

#include "basic-display-window.h"
#include "ui_basic-display-window.h"

#include <cstdint>
#include <iostream>
#include <QEvent>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QWidget>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

#include "object-manager.h"
#include "main-window.h"
#include "message-window.h"
#include "utilities.h"

BasicDisplayWindow::BasicDisplayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BasicDisplayWindow)
{
    ui->setupUi(this);

    pList = this->findChild<QListWidget *>("inputList");

    qRegisterMetaType<buffer_t>("buffer_t");

    QObject::connect(this, &BasicDisplayWindow::readSignal,
                     this, &BasicDisplayWindow::handleReadSignal);
}

BasicDisplayWindow::~BasicDisplayWindow()
{
    delete ui;
}

void BasicDisplayWindow::readCallback(std::vector<uint8_t> data)
{
    // Need to trigger by signal as the callback is being triggered from another thread
    emit ObjectManager::getBasicDisplay()->readSignal(data);
}

void BasicDisplayWindow::addLine(const std::vector<uint8_t> &data, bool isRx, bool withTimestamp)
{
    std::string line;

    // Construct the preamble of the displayed text if needed.
    if (withTimestamp)
    {
        line += "[";
        line += util::getTimestamp();
        line += "], ";
    }

    if (isRx)
    {
        line += "Rx, ";
    }
    else
    {
        line += "Tx, ";
    }

    // Create a new QLineEdit widget to add to the list widget to display the text.
    line += util::getStringFromData(data);
    QLineEdit *pLineEdit = new QLineEdit();
    pLineEdit->setReadOnly(true); // Don't allow editing.
    pLineEdit->setText(line.c_str());
    QListWidgetItem *pItem = new QListWidgetItem(pList);
    pList->addItem(pItem);
    pList->setItemWidget(pItem, pLineEdit);
}

void BasicDisplayWindow::addNLine(const std::vector<uint8_t> &data, size_t length, bool isRx, bool withTimestamp)
{
    std::string line;

    // Construct the preamble of the displayed text if needed.
    if (withTimestamp)
    {
        line += "[";
        line += util::getTimestamp();
        line += "], ";
    }

    if (isRx)
    {
        line += "Rx, ";
    }
    else
    {
        line += "Tx, ";
    }

    // Create a new QLineEdit widget to add to the list widget to display the text.
    line += util::getStringFromNData(data, length);
    QLineEdit *pLineEdit = new QLineEdit();
    pLineEdit->setReadOnly(true); // Don't allow editing.
    pLineEdit->setText(line.c_str());
    QListWidgetItem *pItem = new QListWidgetItem(pList);
    pList->addItem(pItem);
    pList->setItemWidget(pItem, pLineEdit);
}

void BasicDisplayWindow::addString(const std::string &value, bool withTimestamp)
{
    std::string line;

    // Construct the preamble of the displayed text if needed.
    if (withTimestamp)
    {
        line += "[";
        line += util::getTimestamp();
        line += "], ";
    }

    // Create a new QLineEdit widget to add to the list widget to display the text.
    line += value;
    QLineEdit *pLineEdit = new QLineEdit();
    pLineEdit->setReadOnly(true); // Don't allow editing.
    pLineEdit->setText(line.c_str());
    QListWidgetItem *pItem = new QListWidgetItem(pList);
    pList->addItem(pItem);
    pList->setItemWidget(pItem, pLineEdit);
}

void BasicDisplayWindow::handleReadSignal(std::vector<uint8_t> data)
{
    addLine(data);
}

void BasicDisplayWindow::handleCopyButton()
{
    // Get selected item (if any)
    QList<QListWidgetItem *> selectedItems = pList->selectedItems();

    if (selectedItems.isEmpty())
    {
        return;
    }

    // The list widget is single selection, but selection query only returns a list.
    // The list should only contain one item, so just get the first item.
    QListWidgetItem *pItem = selectedItems.first();
    QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(pList->itemWidget(pItem));
    std::stringstream ss(pLineEdit->text().toStdString());
    std::string field;
    std::string lastField;

    // The data will be the last field of the comma separated text (this is to account
    // for the optional preamble.
    while (std::getline(ss, field, ','))
    {
        lastField = field;
    }

    ObjectManager::getMessageWindow()->setData(util::getDataFromString(lastField));
}

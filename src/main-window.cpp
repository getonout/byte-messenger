/**
 * \file main-window.cpp
 * \brief Source implementation file for the MainWindow class.
 */

#include "main-window.h"
#include "./ui_main-window.h"

#include <QPushButton>

#include "basic-display-window.h"
#include "connection-window.h"
#include "message-list-window.h"
#include "message-window.h"
#include "object-manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the sub windows.
    BasicDisplayWindow *pDisplay = new BasicDisplayWindow(this);
    ObjectManager::setBasicDisplay(pDisplay);
    ObjectManager::getBasicDisplay()->show();

    ConnectionWindow *pConnectionWindow = new ConnectionWindow(this);
    ObjectManager::setConnectionWindow(pConnectionWindow);
    ObjectManager::getConnectionWindow()->show();

    MessageWindow *pMessageWindow = new MessageWindow(this);
    ObjectManager::setMessageWindow(pMessageWindow);
    // Don't show the Message window by default.

    MessageListWindow *pMessageListWindow = new MessageListWindow(this);
    ObjectManager::setMessageListWindow(pMessageListWindow);
    ObjectManager::getMessageListWindow()->initialize();
    // Don't show the Message List window by default.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleBasicDisplayButton()
{
    BasicDisplayWindow *pWindow = ObjectManager::getBasicDisplay();

    if (pWindow != nullptr)
    {
        if (pWindow->isHidden())
        {
            pWindow->show();
        }
        else
        {
            pWindow->hide();
        }
    }
}

void MainWindow::handleConnectionButton()
{
    ConnectionWindow *pWindow = ObjectManager::getConnectionWindow();

    if (pWindow != nullptr)
    {
        if (pWindow->isHidden())
        {
            pWindow->show();
        }
        else
        {
            pWindow->hide();
        }
    }
}

void MainWindow::handleMessageButton()
{
    MessageWindow *pWindow = ObjectManager::getMessageWindow();

    if (pWindow != nullptr)
    {
        if (pWindow->isHidden())
        {
            pWindow->show();
        }
        else
        {
            pWindow->hide();
        }
    }
}

void MainWindow::handleMessageListButton()
{
    MessageListWindow *pWindow = ObjectManager::getMessageListWindow();

    if (pWindow != nullptr)
    {
        if (pWindow->isHidden())
        {
            pWindow->show();
        }
        else
        {
            pWindow->hide();
        }
    }
}

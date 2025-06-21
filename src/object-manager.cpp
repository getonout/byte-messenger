/**
 * \file object-manager.cpp
 * \brief Source implementation file for the ObjectManager class.
 */

#include "object-manager.h"

#include <iostream>
#ifdef WIN_BUILD
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include <string>

#include "basic-display-window.h"
#include "connection-window.h"
#include "main-window.h"
#include "message-list.h"
#include "message-list-window.h"

ObjectManager::ObjectManager() : pBasicDisplay(nullptr),
                                          pMainWindow(nullptr),
                                          pMessageListWindow(nullptr),
                                          pMessageWindow(nullptr)
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::createInstance()
{
    if (pInstance == nullptr)
    {
        pInstance = new ObjectManager();
    }
    else
    {
        std::cerr << "ObjectManager::createInstance(): Error" << std::endl;
    }
}

ObjectManager *ObjectManager::getObjectManager()
{
    return pInstance;
}

void ObjectManager::setMainWindow(MainWindow *pWindow)
{
    if (pInstance != nullptr)
    {
        pInstance->pMainWindow;
    }
    else
    {
        std::cerr << "ObjectManager::setMainWindow(): pInstance = nullptr" << std::endl;
    }
}

MainWindow *ObjectManager::getMainWindow()
{
    if (pInstance != nullptr)
    {
        return pInstance->pMainWindow;
    }
    else
    {
        std::cerr << "ObjectManager::getMainWindow(): pInstance = nullptr" << std::endl;

        return nullptr;
    }
}

void ObjectManager::setConnectionWindow(ConnectionWindow *pWindow)
{
    if (pInstance != nullptr)
    {
        pInstance->pConnectionWindow = pWindow;
    }
    else
    {
        std::cerr << "ObjectManager::setConnectionWindow(): pInstance = nullptr" << std::endl;
    }
}

ConnectionWindow *ObjectManager::getConnectionWindow()
{
    if (pInstance != nullptr)
    {
        return pInstance->pConnectionWindow;
    }
    else
    {
        std::cerr << "ObjectManager::getConnectionWindow(): pInstance = nullptr" << std::endl;

        return nullptr;
    }
}

void ObjectManager::setBasicDisplay(BasicDisplayWindow *pWindow)
{
    if (pInstance != nullptr)
    {
        pInstance->pBasicDisplay = pWindow;
    }
    else
    {
        std::cerr << "ObjectManager::setBasicDisplay(): pInstance = nullptr" << std::endl;
    }
}

BasicDisplayWindow *ObjectManager::getBasicDisplay()
{
    if (pInstance != nullptr)
    {
        return pInstance->pBasicDisplay;
    }
    else
    {
        std::cerr << "ObjectManager::getBasicDisplay(): pInstance = nullptr" << std::endl;

        return nullptr;
    }
}


void ObjectManager::setMessageListWindow(MessageListWindow *pWindow)
{
    if (pInstance != nullptr)
    {
        pInstance->pMessageListWindow = pWindow;
    }
    else
    {
        std::cerr << "ObjectManager::setMessageListWindow(): pInstance = nullptr" << std::endl;
    }
}

MessageListWindow *ObjectManager::getMessageListWindow()
{
    if (pInstance != nullptr)
    {
        return pInstance->pMessageListWindow;
    }
    else
    {
        std::cerr << "ObjectManager::getMessageListWindow(): pInstance = nullptr" << std::endl;

        return nullptr;
    }
}

void ObjectManager::setMessageWindow(MessageWindow *pWindow)
{
    if (pInstance != nullptr)
    {
        pInstance->pMessageWindow = pWindow;
    }
    else
    {
        std::cerr << "ObjectManager::setMessageWindow(): pInstance = nullptr" << std::endl;
    }
}

MessageWindow *ObjectManager::getMessageWindow()
{
    if (pInstance != nullptr)
    {
        return pInstance->pMessageWindow;
    }
    else
    {
        std::cerr << "ObjectManager::getMessageWindow(): pInstance = nullptr" << std::endl;

        return nullptr;
    }
}

#ifdef WIN_BUILD
void ObjectManager::setListenSocket(SOCKET value)
{
    if (pInstance != nullptr)
    {
        pInstance->listenSocket = value;
    }
    else
    {
        std::cerr << "ObjectManager::setListenSocket(): pInstance = nullptr" << std::endl;
    }
}

SOCKET ObjectManager::getListenSocket()
{
    if (pInstance != nullptr)
    {
        return pInstance->listenSocket;
    }
    else
    {
        std::cerr << "ObjectManager::getListenSocket(): pInstance = nullptr" << std::endl;
        return INVALID_SOCKET;
    }
}

void ObjectManager::setPeerSocket(SOCKET value)
{
    if (pInstance != nullptr)
    {
        pInstance->peerSocket = value;
    }
    else
    {
        std::cerr << "ObjectManager::setPeerSocket(): pInstance = nullptr" << std::endl;
    }
}

SOCKET ObjectManager::getPeerSocket()
{
    if (pInstance != nullptr)
    {
        return pInstance->peerSocket;
    }
    else
    {
        std::cerr << "ObjectManager::getPeerSocket(): pInstance = nullptr" << std::endl;

        return INVALID_SOCKET;
    }
}
#else
void ObjectManager::setListenSocket(int value)
{
    if (pInstance != nullptr)
    {
        pInstance->listenSocket = value;
    }
    else
    {
        std::cerr << "ObjectManager::setListenSocket(): pInstance = nullptr" << std::endl;
    }
}

int ObjectManager::getListenSocket()
{
    if (pInstance != nullptr)
    {
        return pInstance->listenSocket;
    }
    else
    {
        std::cerr << "ObjectManager::getListenSocket(): pInstance = nullptr" << std::endl;
        return -1;
    }
}

void ObjectManager::setPeerSocket(int value)
{
    if (pInstance != nullptr)
    {
        pInstance->peerSocket = value;
    }
    else
    {
        std::cerr << "ObjectManager::setPeerSocket(): pInstance = nullptr" << std::endl;
    }
}

int ObjectManager::getPeerSocket()
{
    if (pInstance != nullptr)
    {
        return pInstance->peerSocket;
    }
    else
    {
        std::cerr << "ObjectManager::getPeerSocket(): pInstance = nullptr" << std::endl;

        return -1;
    }
}
#endif

void ObjectManager::setPeerAddress(const sockaddr_in *pAddress)
{
    if (pInstance != nullptr)
    {
        std::memcpy(&pInstance->peerAddress, pAddress, sizeof(sockaddr_in));
    }
    else
    {
        std::cerr << "ObjectManager::setPeerAddress(): pInstance = nullptr" << std::endl;
    }
}

sockaddr_in *ObjectManager::getPeerAddress()
{
    if (pInstance != nullptr)
    {
        return &pInstance->peerAddress;
    }
    else
    {
        std::cerr << "ObjectManager::getPeerAddress(): pInstance = nullptr" << std::endl;
        return nullptr;
    }
}

void ObjectManager::setConnectionStatus(bool value)
{
    if (pInstance != nullptr)
    {
        pInstance->isConnected = value;
    }
    else
    {
        std::cerr << "ObjectManager::setConnectionStatus(): pInstance = nullptr" << std::endl;
    }
}

bool ObjectManager::getConnectionStatus()
{
    if (pInstance != nullptr)
    {
        return pInstance->isConnected;
    }
    else
    {
        std::cerr << "ObjectManager::getConnectionStatus(): pInstance = nullptr" << std::endl;

        return false;
    }
}

void ObjectManager::setReadThread(pthread_t thread)
{
    if (pInstance != nullptr)
    {
        pInstance->readThread = thread;
    }
    else
    {
        std::cerr << "ObjectManager::setReadThread(): pInstance = nullptr" << std::endl;
    }
}

pthread_t ObjectManager::getReadThread()
{
    if (pInstance != nullptr)
    {
        return pInstance->readThread;
    }
    else
    {
        std::cerr << "ObjectManager::getReadThread(): pInstance = nullptr" << std::endl;

        return 0;
    }
}

void ObjectManager::setAcceptThread(pthread_t thread)
{
    if (pInstance != nullptr)
    {
        pInstance->acceptThread = thread;
    }
    else
    {
        std::cerr << "ObjectManager::setAcceptThread(): pInstance = nullptr" << std::endl;
    }
}

pthread_t ObjectManager::getAcceptThread()
{
    if (pInstance != nullptr)
    {
        return pInstance->acceptThread;
    }
    else
    {
        std::cerr << "ObjectManager::getAcceptThread(): pInstance = nullptr" << std::endl;

        return 0;
    }
}

ObjectManager *ObjectManager::pInstance = nullptr;

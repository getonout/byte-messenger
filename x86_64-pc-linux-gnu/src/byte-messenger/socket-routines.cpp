#include "socket-routines.h"

#include <arpa/inet.h>
#include <csignal>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include "connection-window.h"
#include "object-manager.h"

int tcp::connectClient(const char *pAddress, uint16_t port)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        std::cerr << "Error: clientConnect(): Error creating socket" << std::endl;
        return CONNECT_SOCKET_ERROR;
    }

    sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (!inet_aton(pAddress, &address.sin_addr))
    {
        std::cerr << "Error: clientConnect(): Invalid address (" << pAddress << ")" << std::endl;
        close(sock);
        return CONNECT_ADDRESS_ERROR;
    }

    if (connect(sock, reinterpret_cast<sockaddr *>(&address), sizeof(address)) < 0)
    {
        std::cerr << "Error: clientConnect(): Error connecting to peer" << std::endl;
        close(sock);
        return CONNECT_CONNECT_ERROR;
    }

    ObjectManager::setConnectionStatus(true);

    return sock;
}

void tcp::disconnectClient()
{
    close(ObjectManager::getPeerSocket());
    ObjectManager::setConnectionStatus(false);
}

void tcp::readThreadSigHandler(int sig)
{
    pthread_exit(nullptr);
}

void *tcp::readThread(void *pData)
{
    signal(SIGTERM, readThreadSigHandler);

    readCallback_t callback = reinterpret_cast<readCallback_t>(pData);

    uint8_t pTempBuf[MAX_READ_SIZE];

    bool connected = ObjectManager::getConnectionStatus();

    while (connected)
    {
        ssize_t result = recv(ObjectManager::getPeerSocket(), pTempBuf, MAX_READ_SIZE, 0);

        if (result < 0)
        {
            std::cerr << "tcp::readThread(): recv() error=" << result << std::endl;
            tcp::disconnectClient();
            connected = false;
        }
        else if (result == 0)
        {
            tcp::disconnectClient();
            connected = false;
            ObjectManager::getConnectionWindow()->updateConnectionInfo(false);
        }
        else
        {
            std::vector<uint8_t> buffer(pTempBuf, pTempBuf + result);

            callback(buffer);
        }
    }

    return nullptr;
}

bool tcp::startReadLoop(readCallback_t callback)
{
    pthread_t thread;

    int result = pthread_create(&thread, nullptr, readThread, reinterpret_cast<void *>(callback));

    if (result != 0)
    {
        return false;
    }
    else
    {
        ObjectManager::setReadThread(thread);

        return true;
    }
}

void tcp::acceptThreadSigHandler(int sig)
{
    pthread_exit(nullptr);
}

void *tcp::acceptThread(void *pData)
{
    signal(SIGTERM, acceptThreadSigHandler);

    acceptCallback_t callback = reinterpret_cast<acceptCallback_t>(pData);

    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == -1)
    {
        std::cerr << "Error: acceptThread(): Error creating socket" << std::endl;
        callback(-1);
        return nullptr;
    }

    int optVal = 1;
    if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) == -1)
    {
        std::cerr << "Error: acceptThread(): Error in setsockopt()" << std::endl;
        close(listenSock);
        callback(-1);
        return nullptr;
    }

    sockaddr_in listenAddr;
    std::memset(&listenAddr, 0, sizeof(listenAddr));
    listenAddr.sin_family = AF_INET;
    listenAddr.sin_addr.s_addr = INADDR_ANY;
    // Port in ObjectManager updated in ConnectionWindow button handler
    listenAddr.sin_port = htons(ObjectManager::getConnectionWindow()->getPortValue());

    if (bind(listenSock, reinterpret_cast<sockaddr *>(&listenAddr), sizeof(listenAddr)) == -1)
    {
        std::cerr << "Error: acceptThread(): Error binding socket" << std::endl;
        std::cerr << "  Error = " << errno << std::endl;
        close(listenSock);
        callback(-1);
        return nullptr;
    }

    if (listen(listenSock, 1) == -1)
    {
        std::cerr << "Error: acceptThread(): Error listening socket" << std::endl;
        close(listenSock);
        callback(-1);
        return nullptr;
    }

    ObjectManager::setListenSocket(listenSock);

    sockaddr_in clientAddr;
    std::memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t clientAddrLen = sizeof(clientAddr);

    int clientSock = accept(listenSock, reinterpret_cast<sockaddr *>(&clientAddr), &clientAddrLen);
    if (clientSock == -1)
    {
        std::cerr << "Error: acceptThread(): Error accepting socket" << std::endl;
        close(listenSock);
        callback(-1);
        return nullptr;
    }

    ObjectManager::setConnectionStatus(true);
    ObjectManager::setPeerSocket(clientSock);
    ObjectManager::setPeerAddress(&clientAddr);

    callback(clientSock);

    return nullptr;
}

bool tcp::startAcceptThread(acceptCallback_t callback)
{
    pthread_t thread;

    int result = pthread_create(&thread, nullptr, acceptThread, reinterpret_cast<void *>(callback));

    if (result != 0)
    {
        return false;
    }
    else
    {
        ObjectManager::setAcceptThread(thread);

        return true;
    }
}

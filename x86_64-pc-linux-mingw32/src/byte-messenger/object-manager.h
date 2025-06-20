#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#ifdef WIN_BUILD
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include <pthread.h>
#include <string>

#include "basic-display-window.h"
#include "connection-window.h"
#include "main-window.h"
#include "message-list.h"
#include "message-list-window.h"
#include "message-window.h"

class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    static void createInstance();
    static ObjectManager *getObjectManager();

    static void setMainWindow(MainWindow *pWindow);
    static MainWindow *getMainWindow();

    static void setConnectionWindow(ConnectionWindow *pWindow);
    static ConnectionWindow *getConnectionWindow();

    static void setBasicDisplay(BasicDisplayWindow *pWindow);
    static BasicDisplayWindow *getBasicDisplay();

    static void setMessageListWindow(MessageListWindow *pWindow);
    static MessageListWindow *getMessageListWindow();

    static void setMessageWindow(MessageWindow *pWindow);
    static MessageWindow *getMessageWindow();

#ifdef WIN_BUILD
    static void setListenSocket(SOCKET value);
    static SOCKET getListenSocket();

    static void setPeerSocket(SOCKET value);
    static SOCKET getPeerSocket();
#else
    static void setListenSocket(int value);
    static int getListenSocket();

    static void setPeerSocket(int value);
    static int getPeerSocket();
#endif

    static void setPeerAddress(const sockaddr_in *pAddress);
    static sockaddr_in *getPeerAddress();

    static void setConnectionStatus(bool value);
    static bool getConnectionStatus();

    static void setReadThread(pthread_t thread);
    static pthread_t getReadThread();

    static void setAcceptThread(pthread_t thread);
    static pthread_t getAcceptThread();

private:
    // Windows
    MainWindow *pMainWindow;
    ConnectionWindow *pConnectionWindow;
    BasicDisplayWindow *pBasicDisplay;
    MessageListWindow *pMessageListWindow;
    MessageWindow *pMessageWindow;

#ifdef WIN_BUILD
    SOCKET listenSocket;
    SOCKET peerSocket;
#else
    int listenSocket;
    int peerSocket;
#endif
    sockaddr_in peerAddress;
    bool isConnected;
    pthread_t readThread;
    pthread_t acceptThread;

    static ObjectManager *pInstance;
};

#endif // OBJECT_MANAGER_H

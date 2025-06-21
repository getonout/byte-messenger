#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

/**
 * \file object-manager.h
 * \brief Source header file for the ObjectManager class.
 */

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

/**
 * \class ObjectManager
 * \brief Class providing functionality for tracking global data.
 */
class ObjectManager
{
public:
    /**
     * Constructor.
     */
    ObjectManager();
    /**
     * Destructor.
     */
    ~ObjectManager();

    /**
     * Creates a global instance of the ObjectManager.
     */
    static void createInstance();
    /**
     * Obtains a pointer to the global instance.
     */
    static ObjectManager *getObjectManager();

    /**
     * Sets the instance MainWindow pointer.
     * \param pWindow Pointer to the MainWindow to track.
     */
    static void setMainWindow(MainWindow *pWindow);
    /**
     * Obtains the MainWindow pointer of the instance.
     * \return The tracked MainWindow pointer.
     */
    static MainWindow *getMainWindow();

    /**
     * Sets the instance ConnectionWindow pointer.
     * \param pWindow Pointer to the ConnectionWindow to track.
     */
    static void setConnectionWindow(ConnectionWindow *pWindow);
    /**
     * Obtains the ConnectionWindow pointer of the instance.
     * \return The tracked ConnectionWindow pointer.
     */
    static ConnectionWindow *getConnectionWindow();

    /**
     * Sets the instance BasicDisplayWindow pointer.
     * \param pWindow Pointer to the BasicDisplayWindow to track.
     */
    static void setBasicDisplay(BasicDisplayWindow *pWindow);
    /**
     * Obtains the BasicDisplayWindow pointer of the instance.
     * \return The tracked BasicDisplayWindow pointer.
     */
    static BasicDisplayWindow *getBasicDisplay();

    /**
     * Sets the instance MessageListWindow pointer.
     * \param pWindow Pointer to the MessageListWindow to track.
     */
    static void setMessageListWindow(MessageListWindow *pWindow);
    /**
     * Obtains the MessageListWindow pointer of the instance.
     * \return The tracked MessageListWindow pointer.
     */
    static MessageListWindow *getMessageListWindow();

    /**
     * Sets the instance MessageWindow pointer.
     * \param pWindow Pointer to the MessageWindow to track.
     */
    static void setMessageWindow(MessageWindow *pWindow);
    /**
     * Obtains the MessageWindow pointer of the instance.
     * \return The tracked MessageWindow pointer.
     */
    static MessageWindow *getMessageWindow();

#ifdef WIN_BUILD
    /**
     * Sets the instance listening SOCKET value.
     * \param value The listening SOCKET value to track.
     */
    static void setListenSocket(SOCKET value);
    /**
     * Obtains the listening SOCKET value of the instance.
     * \return The tracked listening SOCKET value.
     */
    static SOCKET getListenSocket();

    /**
     * Sets the instance peer SOCKET value.
     * \param value The peer SOCKET value to track.
     */
    static void setPeerSocket(SOCKET value);
    /**
     * Obtains the peer SOCKET value of the instance.
     * \return The tracked peer SOCKET value.
     */
    static SOCKET getPeerSocket();
#else
    /**
     * Sets the instance listening socket file descriptor value.
     * \param value The listening socket file descriptor value to track.
     */
    static void setListenSocket(int value);
    /**
     * Obtains the listening socket file descriptor value of the instance.
     * \return The tracked listening socket file descriptor value.
     */
    static int getListenSocket();

    /**
     * Sets the instance peer socket file descriptor value.
     * \param value The peer socket file descriptor value to track.
     */
    static void setPeerSocket(int value);
    /**
     * Obtains the peer socket file descriptor value of the instance.
     * \return The tracked peer socket file descriptor value.
     */
    static int getPeerSocket();
#endif

    /**
     * Set the peer address data structure of the instance.
     * \param pAddress Pointer to an address structure containing the new address data.
     */
    static void setPeerAddress(const sockaddr_in *pAddress);
    /**
     * Obtains the peer address data structure value of the instance.
     * \return Pointer to the track peer address data structure value.
     */
    static sockaddr_in *getPeerAddress();

    /**
     * Sets the connection status value of the instance.
     * \param value The new connection status value.
     */
    static void setConnectionStatus(bool value);
    /**
     * Obtains the connection status value of the instance.
     * \return The tracked connection status value.
     */
    static bool getConnectionStatus();

    /**
     * Sets the read thread handle of the instance.
     * \param thread The thread handle to track.
     */
    static void setReadThread(pthread_t thread);
    /**
     * Obtains the thread handle of the tracked read thread.
     * \return The tracked thread handle.
     */
    static pthread_t getReadThread();

    /**
     * Sets the accept thread handle of the instance.
     * \param thread The thread handle to track.
     */
    static void setAcceptThread(pthread_t thread);
    /**
     * Obtains the thread handle of the tracked accept thread.
     * \return The tracked thread handle.
     */
    static pthread_t getAcceptThread();

private:
    MainWindow *pMainWindow; ///< Pointer to the tracked MainWindow object.
    ConnectionWindow *pConnectionWindow; ///< Pointer to the tracked ConnectionWindow
                                         ///< object.
    BasicDisplayWindow *pBasicDisplay; ///< Pointer to the tracked BasicDisplayWindow
                                       ///< object.
    MessageListWindow *pMessageListWindow; ///< Pointer to the tracked MessageListWindow
                                           ///< object.
    MessageWindow *pMessageWindow; ///< Pointer to the tracked MessageWindow object.

#ifdef WIN_BUILD
    SOCKET listenSocket; ///< Tracked listen socket SOCKET value.
    SOCKET peerSocket; ///< Tracked peer socket SOCKET value.
#else
    int listenSocket; ///< Tracked listen socket file descriptor value.
    int peerSocket; ///< Tracked peer socket file descriptor value.
#endif
    sockaddr_in peerAddress; ///< Tracked peer address data structure.
    bool isConnected; ///< Tracked connection status value.
    pthread_t readThread; ///< Thread handle of the tracked read thread.
    pthread_t acceptThread; ///< Thread handle of the tracked accept thread.

    static ObjectManager *pInstance; ///< Static instance pointer.
};

#endif // OBJECT_MANAGER_H

#ifndef SOCKET_ROUTINES_H
#define SOCKET_ROUTINES_H

/**
 * \file socket-routines.h
 * \brief Source header file for socket routines.
 */

#include <cstdint>
#include <sys/types.h>
#include <vector>
#ifdef WIN_BUILD
#include <winsock2.h>
#endif

namespace tcp
{
enum {CONNECT_SOCKET_ERROR = -1,
      CONNECT_ADDRESS_ERROR = -2,
      CONNECT_CONNECT_ERROR = -3};

enum {MAX_READ_SIZE = 1024};

/**
 * Callback function invoked when data is read from the read thread.
 */
typedef void (*readCallback_t)(std::vector<uint8_t> data);
#ifdef WIN_BUILD
/**
 * Callback function invoked when a client connection is accepted from the accept thread.
 */
typedef void (*acceptCallback_t)(SOCKET socket);
#else
/**
 * Callback function invoked when a client connection is accepted from the accept thread.
 */
typedef void (*acceptCallback_t)(int socket);
#endif

#ifdef WIN_BUILD
/**
 * Executes the necessary functions to setup socket communications.
 * \return 0 upon success.  A non-zero error code upon failure.
 */
int initialize();
/**
 * Initiates a client connection to a server.
 * \param pAddress String representing the address of the server to connect to.
 * \param port The port value of the server to connect to.
 * \param sock Reference to SOCKET value which will be updated to the SOCKET value of the
 *        connected socket upon success.
 * \return 0 upon success.  A non-zero error code upon failure.
 */
int connectClient(const char *pAddress, uint16_t port, SOCKET &sock);
#else
/**
 * Initiates a client connection to a server.
 * \param pAddress String representing the address of the server to connect to.
 * \param port The port value of the server to connect to.
 * \return Upon success, the file descriptor value of the connected socket is returned.
 *         A value of -1 upon failure.
 */
int connectClient(const char *pAddress, uint16_t port);
#endif
/**
 * Disconnects the client connection if it is established and closes the connection socket.
 */
void disconnectClient();
/**
 * Terminates the read thread upon receiving a signal.
 * \param sig The received signal value.
 */
void readThreadSigHandler(int sig);
/**
 * The read thread function.  Performs the necessary processing of the read thread such as
 * reading data from the peer socket and invoking the specified callback function when
 * appropriate.
 * \param pData The thread function argument.  This should be set to the callback function
 *        to be invoked.
 * \return nullptr value.
 */
void *readThread(void *pData);
/**
 * Creates the read thread and specifies the callback function to be supplied to the
 * read thread.
 * \param callback The callback function to be supplied to the read thread.
 * \return The success result of the thread creation.
 */
bool startReadLoop(readCallback_t callback);
/**
 * Terminates the accept thread upon receiving a signal.
 * \param sig The received signal value.
 */
void acceptThreadSigHandler(int sig);
/**
 * The accept thread function.  Performs the necessary processing of the accept thread such
 * as accepting the client connection and invoking the specified callback function when
 * appropriate.
 * \param pData The thread function argument.  This should be set to the callback function
 *        to be invoked.
 * \return nullptr value.
 */
void *acceptThread(void *pData);
/**
 * Creates the accept thread and specifies the callback function to be supplied to the
 * accept thread.
 * \param callback The callback function to be supplied to the accept thread.
 * \return The success result of the thread creation.
 */
bool startAcceptThread(acceptCallback_t callback);
}

#endif // SOCKET_ROUTINES_H

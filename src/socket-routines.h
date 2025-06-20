#ifndef SOCKET_ROUTINES_H
#define SOCKET_ROUTINES_H

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

// Cannot pass argument by reference between threads
typedef void (*readCallback_t)(std::vector<uint8_t> data);
#ifdef WIN_BUILD
typedef void (*acceptCallback_t)(SOCKET socket);
#else
typedef void (*acceptCallback_t)(int socket);
#endif

#ifdef WIN_BUILD
int initialize();
int connectClient(const char *pAddress, uint16_t port, SOCKET &sock);
#else
int connectClient(const char *pAddress, uint16_t port);
#endif
void disconnectClient();
void readThreadSigHandler(int sig);
void *readThread(void *pData);
bool startReadLoop(readCallback_t callback);
void acceptThreadSigHandler(int sig);
void *acceptThread(void *pData);
bool startAcceptThread(acceptCallback_t callback);
}

#endif // SOCKET_ROUTINES_H

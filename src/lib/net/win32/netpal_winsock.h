#ifndef NETPAL_WINSOCK_H
#define NETPAL_WINSOCK_H

#include <WS2tcpip.h>

typedef SOCKET socket_handle;
typedef struct pollfd pollfd_handle;

#include "common/macros.h"
#include "common/ptbool.h"

PT_BOOL netpal_init();
void netpal_deinit();

PT_BOOL netpal_connectSocket(socket_handle socket, struct sockaddr_in, REF_RET(int));
socket_handle netpal_createSocket(int af, int type, int protocol, REF_RET(int));

PT_BOOL netpal_createAddress(struct sockaddr_in *hint, int family, const char *hostname, int port, REF_RET(int));
PT_BOOL netpal_bind(socket_handle socket, struct sockaddr_in hint, REF_RET(int));
PT_BOOL netpal_listen(socket_handle socket, REF_RET(int));
PT_BOOL netpal_closeSocket(socket_handle socket);
int netpal_poll(pollfd_handle*, int nfds, int timeout);
int netpal_readSocket(socket_handle fd, char *buf, size_t len, int flags);
int netpal_writeSocket(socket_handle fd, const char *buf, size_t len, int flags);
socket_handle netpal_acceptSocket(socket_handle listener, struct sockaddr *sa, socklen_t *slen);
int netpal_setSocketOption(socket_handle, int level, int optName, const char* optval, int optLen);
int netpal_getSocketOption(socket_handle, int level, int optName, char* optval, int* optLen);
void netpal_getHostName(char* buffer, size_t len);
int netpal_avail(socket_handle);

#endif /* NETPAL_WINSOCK_H */
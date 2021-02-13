#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "socket.h"
#include "common/ptbool.h"

typedef struct {
    socket_data client;
    struct sockaddr_in hint;
} tcp_client_data, *ptcp_client_data;

ptcp_client_data tcp_client_create();
void tcp_client_free(ptcp_client_data);
PT_BOOL tcp_client_connect(ptcp_client_data, const char*, int port);
PT_BOOL tcp_client_setNoDelay(ptcp_client_data ptr, PT_BOOL value);
PT_BOOL tcp_client_getNoDelay();
psocket_data tcp_client_getClient(ptcp_client_data ptr);
void tcp_client_setClient(ptcp_client_data, psocket_data socket);
int tcp_client_getReceiveTimeout(ptcp_client_data);
void tcp_client_setReceiveTimeout(ptcp_client_data, int value);
int tcp_client_getReceiveBufferSize(ptcp_client_data);
void tcp_client_setReceiveBufferSize(ptcp_client_data, int value);
PT_BOOL tcp_client_isConnected(ptcp_client_data);
int tcp_client_getAvailable(ptcp_client_data);
void tcp_client_close(ptcp_client_data);
int tcp_client_errno(ptcp_client_data);
void tcp_client_errno_str(ptcp_client_data, char* buffer, size_t len);

#endif /* TCP_CLIENT_H */
#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H

#include "socket.h"
#include "common/ptbool.h"

typedef struct {
    socket_data server;
    struct sockaddr_in hint;
    int port;
} tcp_listener_data, *ptcp_listener_data;


ptcp_listener_data tcp_listener_create(int port);
void tcp_listener_free(ptcp_listener_data);
PT_BOOL tcp_listener_bind(ptcp_listener_data);
PT_BOOL tcp_listener_start(ptcp_listener_data);
PT_BOOL tcp_listener_stop(ptcp_listener_data);
void tcp_listener_accept(ptcp_listener_data, socket_data*);
int tcp_listener_errno(ptcp_listener_data);
void tcp_listener_errno_str(ptcp_listener_data, char* buffer, size_t len);

#endif /* TCP_LISTENER_H */
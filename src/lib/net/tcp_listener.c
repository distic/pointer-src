#include "tcp_listener.h"
#include <stdlib.h>
#include "netpal.h"
#include <assert.h>

ptcp_listener_data tcp_listener_create(int port)
{
    ptcp_listener_data ptr = (ptcp_listener_data)malloc(sizeof(tcp_listener_data));
    socket_create(&ptr->server);

    netpal_createAddress(&ptr->hint, AF_INET, NULL, port, &ptr->server.last_errno);
    return ptr;
}

void tcp_listener_free(ptcp_listener_data ptr)
{
    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
    }
}

PT_BOOL tcp_listener_bind(ptcp_listener_data ptr)
{
    assert(ptr != NULL);
    return netpal_bind(ptr->server.handle, ptr->hint, &ptr->server.last_errno);
}

PT_BOOL tcp_listener_start(ptcp_listener_data ptr)
{
    assert(ptr != NULL);
    return netpal_listen(ptr->server.handle, &ptr->server.last_errno);
}

PT_BOOL tcp_listener_stop(ptcp_listener_data ptr)
{
    assert(ptr != NULL);
    socket_close(&ptr->server);
    return PT_TRUE;
}

void tcp_listener_accept(ptcp_listener_data ptr, socket_data* socket)
{
    socket_handle sh = netpal_acceptSocket(ptr->server.handle, NULL, NULL);
    if (sh == INVALID_SOCKET)
    {
        socket->handle = INVALID_SOCKET;
    }

    socket_create2(socket, sh);
}

int tcp_listener_errno(ptcp_listener_data ptr)
{
    assert (ptr != NULL);
    return socket_errno(&ptr->server);
}

void tcp_listener_errno_str(ptcp_listener_data ptr, char* buffer, size_t len)
{
    assert (ptr != NULL);
    assert (buffer != NULL);
    assert (len > 0);

    int err = tcp_listener_errno(ptr);

    switch (err) {
        /* TODO: Finish tcp_listener_errno_str */
    }
}
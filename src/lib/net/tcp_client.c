#include "tcp_client.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "netpal.h"
#include "common/ptbool.h"

ptcp_client_data tcp_client_create()
{
    ptcp_client_data ptr = (ptcp_client_data)malloc(sizeof(tcp_client_data));
    socket_create(&ptr->client);
    return ptr;
}

void tcp_client_free(ptcp_client_data ptr)
{
    if (ptr != NULL) {
        if (ptr->client.handle != INVALID_SOCKET) {
            socket_close(&ptr->client);
        }

        free(ptr);
        ptr = NULL;
    }
}

PT_BOOL tcp_client_connect(ptcp_client_data ptr, const char* hostname, int port)
{
    assert (ptr != NULL);
    if (netpal_createAddress(&ptr->hint, AF_INET, hostname, port, &ptr->client.last_errno) == PT_FALSE) {
        return PT_FALSE;
    }

    if (netpal_connectSocket(ptr->client.handle, ptr->hint, &ptr->client.last_errno) == PT_FALSE) {
        return PT_FALSE;
    }

    return PT_TRUE;
}

PT_BOOL tcp_client_setNoDelay(ptcp_client_data ptr, PT_BOOL value)
{
#if _WIN32

    // char nflag;
    // int size = sizeof(nflag);

    // // Set the new state
    // char flag = value ? '1' : '0';
    // size = sizeof(flag);
    // if (client->setSocketOption(IPPROTO_TCP, TCP_NODELAY, (const char *)&flag, size) == SOCKET_ERROR)
    // {
    //     throw "getsockerror_winsock()";
    // }

    // // Verify the new state
    // if (client->getSocketOption(IPPROTO_TCP, TCP_NODELAY, &nflag, &size) == SOCKET_ERROR)
    // {
    //     throw "getsockerror_winsock()";
    // }

    // return value ? (nflag == '1') : (nflag == '0');
#else
    printf("[WRN]: tcp_client_setNoDelay() not implemented on Unix-based systems.\n");
#endif
    return PT_TRUE;
}

PT_BOOL tcp_client_getNoDelay(ptcp_client_data ptr)
{
    printf("[WRN]: tcp_client_getNoDelay() not implemented on Unix-based systems.\n");
    return PT_FALSE;
}

psocket_data tcp_client_getClient(ptcp_client_data ptr)
{
    assert (ptr != NULL);

    return &ptr->client;
}

void tcp_client_setClient(ptcp_client_data ptr, psocket_data socket)
{
    assert (ptr != NULL);
    ptr->client = *socket;
}

int tcp_client_getReceiveTimeout(ptcp_client_data ptr)
{
    return 0;
}

void tcp_client_setReceiveTimeout(ptcp_client_data ptr, int value)
{

}

int tcp_client_getReceiveBufferSize(ptcp_client_data ptr)
{
    return 0;
}

void tcp_client_setReceiveBufferSize(ptcp_client_data ptr, int value)
{

}

PT_BOOL tcp_client_isConnected(ptcp_client_data ptr)
{
    return PT_FALSE;
}

int tcp_client_getAvailable(ptcp_client_data ptr)
{
    return 0;
}

void tcp_client_close(ptcp_client_data ptr)
{
    assert (ptr != NULL);
    socket_close(&ptr->client);
}

int tcp_client_errno(ptcp_client_data ptr)
{
    assert (ptr != NULL);
    return ptr->client.last_errno;
}

void tcp_client_errno_str(ptcp_client_data ptr, char* buffer, size_t len)
{
    assert (ptr != NULL);
    assert (buffer != NULL);
    assert (len > 0);

    int err = tcp_client_errno(ptr);

    switch (err) {
        /* TODO: Finish tcp_client_errno_str */
    }
}
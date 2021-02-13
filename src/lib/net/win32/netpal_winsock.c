#define NETPAL_IMPL

#include "net/netpal.h"
#include "netpal_winsock.h"

#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32.lib")


#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

PT_BOOL netpal_init()
{
    // Initialize winsock
    struct WSAData wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        return PT_FALSE;
    }

    return PT_TRUE;
}

void netpal_deinit()
{
    WSACleanup();
}

PT_BOOL netpal_connectSocket(socket_handle socket, struct sockaddr_in serv_addr, REF_RET(int))
{
    socket_handle ret = connect(socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret == INVALID_SOCKET) {
        *ref_ret = GetLastError();

        perror("netpal_connectSocket: ");
        return PT_FALSE;
    }
    return PT_TRUE;
}

socket_handle netpal_createSocket(int af, int type, int protocol, REF_RET(int))
{
    socket_handle ret = socket(af, type, protocol);
    if (ret == INVALID_SOCKET) {
        *ref_ret = ret;
        perror("netpal_createSocket: ");
    }
    return ret;
}

PT_BOOL netpal_createAddress(struct sockaddr_in *hint, int family, const char *hostname, int port, REF_RET(int))
{
    // Bind the IP address and port to a socket
    hint->sin_family = family;
    hint->sin_port = htons(port);
    if (hostname == NULL)
    {
        hint->sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton...
    }
    else
    {
        // InetPtonA(family, "127.0.0.1", &hint);

        hint->sin_addr.s_addr = inet_addr(hostname);
        
        // if (inet_pton(AF_INET, hostname, &hint.sin_addr))
        // {
        //     printf("\nInvalid address/ Address not supported \n");
        // }
    }

    // TODO: what the fuck is this??????
    *ref_ret = PT_TRUE;
    return *ref_ret;
}

PT_BOOL netpal_bind(socket_handle socket, struct sockaddr_in hint, REF_RET(int))
{
    *ref_ret = bind(socket, (struct sockaddr *)&hint, sizeof(hint));
    return PT_TRUE;
}

PT_BOOL netpal_listen(socket_handle socket, REF_RET(int))
{
    *ref_ret = listen(socket, SOMAXCONN);
    return PT_TRUE;
}

PT_BOOL netpal_closeSocket(socket_handle socket)
{
    closesocket(socket);
    return PT_TRUE;
}

int netpal_poll(pollfd_handle* pfd, int nfds, int timeout)
{
    return WSAPoll(pfd, nfds, timeout);
}

int netpal_readSocket(socket_handle socket, char *buf, size_t len, int flags)
{
    int n = recv(socket, buf, (int)len, flags);

    if (n == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        if (err == WSAEINTR || err == WSAEWOULDBLOCK)
        {
            return 0;
        }
        // throwError(err);
    }

    return n;
}

int netpal_writeSocket(socket_handle socket, const char *buf, size_t len, int flags)
{
    int n = send(socket, buf, (int)len, flags);

    if (n == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        if (err == WSAEINTR)
        {
            return 0;
        }
        if (err == WSAEWOULDBLOCK)
        {
            // s->m_pollWrite = true;
            return 0;
        }
        // throwError(err);
    }
    return n;
}

socket_handle netpal_acceptSocket(socket_handle listener, struct sockaddr *sa, socklen_t *slen)
{
    return accept(listener, NULL, NULL); // a, &b);
}

int netpal_setSocketOption(socket_handle socket, int level, int optName, const char* optval, int optLen)
{
    HRESULT iResult = setsockopt(socket, level, optName, optval, optLen);
    if (iResult == SOCKET_ERROR)
    {
        // LOG((CLOG_CRIT "setsockopt for '%d' failed with error: %u", optName, WSAGetLastError()));
    }

    return iResult;
}

int netpal_getSocketOption(socket_handle socket, int level, int optName, char* optval, int* optLen)
{
    HRESULT iResult = getsockopt(socket, level, optName, optval, (socklen_t *)optLen);
    if (iResult == SOCKET_ERROR)
    {
        // LOG((CLOG_CRIT "getsockopt for '%d' failed with error: %u", optName, WSAGetLastError()));
    }

    return iResult;
}

void netpal_getHostName(char* buffer, size_t len)
{
    char name[256];
    if (gethostname(name, sizeof(name)) == -1)
    {
        name[0] = '\0';
    }
    else
    {
        name[sizeof(name) - 1] = '\0';
    }
    // return std::string(name);
}

int netpal_avail(socket_handle sh)
{
    //-------------------------
    // Set the socket I/O mode: In this case FIONBIO
    // enables or disables the blocking mode for the 
    // socket based on the numerical value of iMode.
    // If iMode = 0, blocking is enabled; 
    // If iMode != 0, non-blocking mode is enabled.

    int iMode = -1;

    int iResult = ioctlsocket(sh, FIONREAD, &iMode);
    if (iResult != NO_ERROR)
    {
        return iMode;
    }

    return iMode;
}
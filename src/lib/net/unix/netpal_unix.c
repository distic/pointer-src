#include "netpal_unix.h"
#include <poll.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>

#define SIZE 1024

#define MIN(a,b) ((a) < (b) ? (a) : (b))

PT_BOOL _netpal_internal_senddata(socket_handle, void *buf, int buflen);
PT_BOOL _netpal_internal_readdata(socket_handle, void *buf, int buflen);
PT_BOOL _netpal_internal_readlong(socket_handle, long *value);
PT_BOOL _netpal_internal_sendlong(socket_handle, long value);


PT_BOOL netpal_init()
{
    return PT_TRUE;
}

void netpal_deinit()
{
    /* do nothing. */
}

PT_BOOL netpal_connectSocket(socket_handle socket, struct sockaddr_in serv_addr, REF_RET(int))
{
    int ret = connect(socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        *ref_ret = ret;
        perror("netpal_connectSocket: ");
        return PT_FALSE;
    }
    return PT_TRUE;
}

socket_handle netpal_createSocket(int af, int type, int protocol, REF_RET(int))
{
    int ret = socket(af, type, protocol);
    if (ret == -1) {
        *ref_ret = ret;
        perror("netpal_createSocket: ");
    }
    return ret;
}

PT_BOOL netpal_createAddress(struct sockaddr_in *hint, int family, const char *hostname, int port, REF_RET(int))
{
    /* Bind the IP address and port to a socket */
    hint->sin_family = family;
    hint->sin_port = htons(port);
    if (hostname == NULL)
    {
        hint->sin_addr.s_addr = INADDR_ANY; /* could also use inet_pton... */
    }
    else
    {
        hint->sin_addr.s_addr = inet_addr(hostname);

        /* if (inet_pton(AF_INET, hostname, &hint.sin_addr))
         * {
         *     printf("\nInvalid address/ Address not supported \n");
         * } */
    }

    /* TODO: what the fuck is this?????? */
    *ref_ret = PT_TRUE;
    return *ref_ret;
}

PT_BOOL netpal_bind(socket_handle socket, struct sockaddr_in hint, REF_RET(int))
{
    *ref_ret = bind(socket, (struct sockaddr*)&hint, sizeof(hint));
    if (*ref_ret == -1) {
        perror("netpal_bind: ");
        return PT_FALSE;
    }
    return PT_TRUE;
}

PT_BOOL netpal_listen(socket_handle socket, REF_RET(int))
{
    *ref_ret = listen(socket, SOMAXCONN);
    if (*ref_ret == -1) {
        perror("netpal_listen: ");
        return PT_FALSE;
    }
    return PT_TRUE;
}

PT_BOOL netpal_closeSocket(socket_handle socket)
{
    close(socket);
    return PT_TRUE;
}

int netpal_poll(pollfd_handle *fds, int nfds, int timeout)
{
    return poll(fds, nfds, timeout);
}

int netpal_readSocket(socket_handle fd, char *buf, size_t len, int flags)
{
    return read(fd, buf, len);
}

int netpal_writeSocket(socket_handle fd, const char *buf, size_t len, int flags)
{
    return write(fd, buf, len);
}

socket_handle netpal_acceptSocket(socket_handle listener, struct sockaddr *sa, socklen_t *slen)
{
    int ret = accept(listener, sa, slen);
    if (ret == -1) {
        perror("netpal_acceptSocket: ");
    }

    return ret;
}

int netpal_setSocketOption(socket_handle fd, int level, int optName, const char* optval, int optLen)
{
    return setsockopt(fd, level, optName, optval, (socklen_t)optLen);
}

int netpal_getSocketOption(socket_handle fd, int level, int optName, char* optval, int* optLen)
{
    return getsockopt(fd, level, optName, optval, (socklen_t *)optLen);
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
    
    buffer = name;
}

int netpal_avail(socket_handle sh)
{
    int result;
    int err;
    while ((err = ioctl(sh, FIONREAD, &result)) < 0 && errno == EINTR);
    if (err == -1)
    {
        return 0;
    }

    return result;
}
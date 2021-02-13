#include "socket.h"
#include "socket_errno.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _WIN32
#include <errno.h>
#include <unistd.h>
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void socket_create(psocket_data pSock)
{
    assert(pSock != NULL);
    socket_create3(pSock, AF_INET, SOCK_STREAM, 0);
}

void socket_create2(psocket_data pSock, socket_handle handle)
{
    assert(pSock != NULL);
    pSock->handle = handle;
    pSock->last_errno = 0;
}

void socket_create3(psocket_data pSock, int af, int type, int protocol)
{
    assert(pSock != NULL);
    pSock->last_errno = 0;
    pSock->handle = netpal_createSocket(af, type, protocol, &pSock->last_errno);
}

void socket_free(psocket_data ptr)
{
    if (ptr != NULL)
    {
        /* The dev is responsible for closing the socket. */

        free(ptr);
        ptr = NULL;
    }
}

void socket_close(psocket_data ptr)
{
    assert(ptr != NULL);
    netpal_closeSocket(ptr->handle);
}

int socket_setSocketOption(psocket_data ptr, int level, int optName, const char *optVal, int optLen)
{
    assert(ptr != NULL);
    return netpal_setSocketOption(ptr->handle, level, optName, optVal, optLen);
}

int socket_getSocketOption(psocket_data ptr, int level, int optName, char *optVal, int *optLen)
{
    assert(ptr != NULL);
    return netpal_getSocketOption(ptr->handle, level, optName, optVal, optLen);
}

int socket_read(psocket_data ptr, char *buffer, size_t len)
{
    assert(ptr != NULL);

    int rb = netpal_readSocket(ptr->handle, buffer, len, 0);
    printf("socket_read: %d\n", rb);
    return rb;
}

int socket_write(psocket_data ptr, const char *buffer, size_t len)
{
    assert(ptr != NULL);

    int sb = netpal_writeSocket(ptr->handle, buffer, len, 0);
    printf("socket_write: %d\n", sb);
    return sb;
}

int socket_avail(psocket_data ptr)
{
    assert(ptr != NULL);
    return netpal_avail(ptr->handle);
}

PT_BOOL socket_sendfile(psocket_data ptr, const char *filename, pfiletrans_callback pcb)
{
    assert(ptr != NULL);

    PT_BOOL result = PT_TRUE;

    socket_handle fd = ptr->handle;

    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        result = PT_FALSE;
        goto end;
    }

    fseek(f, 0, SEEK_END);
    long long filesize = ftell(f);
    rewind(f);

    if (filesize == EOF)
    {
        result = PT_FALSE;
        goto end;
    }

    if (!_socket_internal_sendlong(fd, filesize))
    {
        result = PT_FALSE;
        goto end;
    }

    pcb->CALLBACK_OnFileTransferStarted(k_filetrans_send, filesize);

    if (filesize > 0)
    {
        char buffer[1024];
        do
        {
            long num = MIN(filesize, sizeof(buffer));
            num = fread(buffer, 1, num, f);
            if (num < 1)
            {
                result = PT_FALSE;
                goto end;
            }

            if (!_socket_internal_senddata(fd, buffer, num, pcb->CALLBACK_OnFileTransferStatus))
            {
                result = PT_FALSE;
                goto end;
            }

            filesize -= num;
        } while (filesize > 0);
    }

end:
    if (f != NULL)
    {
        fclose(f);
    }

    pcb->CALLBACK_OnFileTransferFinished(result);

    return result;
}

PT_BOOL socket_recvfile(psocket_data ptr, const char *filename, pfiletrans_callback pcb)
{
    assert(ptr != NULL);

    PT_BOOL result = PT_TRUE;

    socket_handle fd = ptr->handle;

    FILE *f = fopen(filename, "wb");
    if (f == NULL)
    {
        return PT_FALSE;
    }

    long long filesize = 0;
    if (!_socket_internal_readlong(fd, &filesize))
    {
        result = PT_FALSE;
        goto end;
    }

    pcb->CALLBACK_OnFileTransferStarted(k_filetrans_recv, filesize);

    if (filesize > 0)
    {
        char buffer[1024];
        do
        {
            long num = MIN(filesize, sizeof(buffer));
            if (!_socket_internal_readdata(fd, buffer, num, pcb->CALLBACK_OnFileTransferStatus))
            {
                result = PT_FALSE;
                goto end;
            }

            long offset = 0;
            do
            {
                size_t written = fwrite(&buffer[offset], 1, num - offset, f);
                if (written < 1)
                {
                    result = PT_FALSE;
                    goto end;
                }

                offset += written;
            } while (offset < num);
            filesize -= num;
        } while (filesize > 0);
    }

end:
    if (f != NULL)
    {
        if (fclose(f) != 0)
        {
            result = PT_FALSE;
        }
    }

    pcb->CALLBACK_OnFileTransferFinished(result);

    return result;
}

int socket_errno(psocket_data ptr)
{
    assert(ptr != NULL);

    return ptr->last_errno;
}

void socket_errno_str(psocket_data ptr, char *buffer, size_t len)
{
    assert(ptr != NULL);
    assert(buffer != NULL);
    assert(len > 0);

    int err = socket_errno(ptr);

    switch (err)
    {
        /* TODO: Finish socket_errno_str */
    }
}

PT_BOOL _socket_internal_senddata(socket_handle fd, void *buf, int buflen, DEF_CALLBACK_OnFileTransferStatus)
{
    unsigned char *pbuf = (unsigned char *)buf;

    int total = buflen;

    while (buflen > 0)
    {
        int num = send(fd, pbuf, buflen, 0);
        if (num == 0)
        {
            if (num == EWOULDBLOCK)
            {
                /* optional: use select() to check for timeout to fail the send */
                continue;
            }
            
            return PT_FALSE;
        }

        pbuf += num;
        buflen -= num;

        if (CALLBACK_OnFileTransferStatus != NULL)
        {
            CALLBACK_OnFileTransferStatus(k_filetrans_send, num);
        }
    }

    return PT_TRUE;
}

PT_BOOL _socket_internal_readdata(socket_handle fd, void *buf, int buflen, DEF_CALLBACK_OnFileTransferStatus)
{
    unsigned char *pbuf = (unsigned char *)buf;

    int total = buflen;

    while (buflen > 0)
    {
        // int num = netpal_avail(fd);
        int num = recv(fd, pbuf, buflen, 0);
        if (num == 0)
        {
            if (num == EWOULDBLOCK)
            {
                /* optional: use select() to check for timeout to fail the read */
                continue;
            }

            break;
        }
        else if (num == 0)
        {
            return PT_FALSE;
        }

        // num = recv(fd, pbuf, buflen, 0);

        pbuf += num;
        buflen -= num;

        if (CALLBACK_OnFileTransferStatus != NULL)
        {
            CALLBACK_OnFileTransferStatus(k_filetrans_recv, num);
        }
    }

    return PT_TRUE;
}

PT_BOOL _socket_internal_readlong(socket_handle fd, long long *value)
{
    if (!_socket_internal_readdata(fd, value, sizeof(value), NULL))
    {
        return PT_FALSE;
    }

    *value = ntohl(*value);
    return PT_TRUE;
}

PT_BOOL _socket_internal_sendlong(socket_handle fd, long long value)
{
    value = htonl(value);

    return _socket_internal_senddata(fd, &value, sizeof(value), NULL);
}
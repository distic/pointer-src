#ifndef SOCKET_H
#define SOCKET_H

#include "netpal.h"
#include "filetrans.h"
#include "common/ptbool.h"

typedef struct {
    socket_handle handle;
    int last_errno;
} socket_data, *psocket_data;


void socket_create(psocket_data);
void socket_create2(psocket_data pSocketBuffer, socket_handle handle);
void socket_create3(psocket_data pSocketBuffer, int af, int type, int protocol);
void socket_free(psocket_data);
void socket_close(psocket_data);
int socket_setSocketOption(psocket_data, int level, int optName, const char *optVal, int optLen);
int socket_getSocketOption(psocket_data, int level, int optName, char *optVal, int *optLen);
int socket_read(psocket_data, char* buf, size_t len);
int socket_write(psocket_data, const char* buf, size_t len);
int socket_avail(psocket_data);
int socket_errno(psocket_data);
void socket_errno_str(psocket_data, char* buffer, size_t len);

PT_BOOL socket_sendfile(psocket_data, const char* filename, pfiletrans_callback);
PT_BOOL socket_recvfile(psocket_data, const char* filename, pfiletrans_callback);


/* internal calls */
PT_BOOL _socket_internal_senddata(socket_handle, void *buf, int buflen, DEF_CALLBACK_OnFileTransferStatus);
PT_BOOL _socket_internal_readdata(socket_handle, void *buf, int buflen, DEF_CALLBACK_OnFileTransferStatus);
PT_BOOL _socket_internal_readlong(socket_handle, long long *value);
PT_BOOL _socket_internal_sendlong(socket_handle, long long value);

#endif /* SOCKET_H */
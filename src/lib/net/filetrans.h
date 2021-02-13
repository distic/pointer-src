#ifndef FILETRANS_H
#define FILETRANS_H

#include "common/ptbool.h"

enum e_filetrans_type {
    k_filetrans_recv,
    k_filetrans_send
};

#define DEF_CALLBACK_OnFileTransferStarted \
        void (*CALLBACK_OnFileTransferStarted)(enum e_filetrans_type, long total)

#define DEF_CALLBACK_OnFileTransferStatus \
        void (*CALLBACK_OnFileTransferStatus)(enum e_filetrans_type, long len)

#define DEF_CALLBACK_OnFileTransferFinished \
        void (*CALLBACK_OnFileTransferFinished)(PT_BOOL success)


typedef struct {
    DEF_CALLBACK_OnFileTransferStarted;
    DEF_CALLBACK_OnFileTransferStatus;
    DEF_CALLBACK_OnFileTransferFinished;
} filetrans_callback, *pfiletrans_callback;


#endif /* FILETRANS_H */
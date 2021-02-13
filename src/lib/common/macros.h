#ifndef MACRO_H
#define MACRO_H

#include <memory.h>

#define REF_RET(TYPE) \
        TYPE* ref_ret


#define PTZeroMem(V) \
        memset(V, '\0', sizeof(V));

#define PTZeroMem2(V, LEN) \
        memset(V, '\0', LEN);

#endif /* MACRO_H */
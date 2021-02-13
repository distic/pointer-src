#ifndef NETPAL_H
#define NETPAL_H

#if _WIN32
#include "win32/netpal_winsock.h"
#else
#include "unix/netpal_unix.h"
#endif

#endif /* NETPAL_H */
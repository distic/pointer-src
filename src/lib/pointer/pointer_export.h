#ifndef POINTER_EXPORT_H
#define POINTER_EXPORT_H

#if defined(_MSC_VER)
    /*  Microsoft */
    #define POWERTIP_EXPORT __declspec(dllexport)
    #define POWERTIP_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    /*  GCC */
    #define POWERTIP_EXPORT __attribute__((visibility("default")))
    #define POWERTIP_IMPORT
#else
    /*  do nothing and hope for the best? */
    #define POWERTIP_EXPORT
    #define POWERTIP_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif


#endif /* POINTER_EXPORT_H */
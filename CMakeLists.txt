cmake_minimum_required (VERSION 3.8)

project ("pointer-src" C)

# set (CMAKE_CXX_STANDARD 17)
# set (CMAKE_CXX_EXTENSIONS ON)
# set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set (POINTER_GUIAPP_ID "com.ahmadnchatila.Pointer")
set (POINTER_SERVER_ID "com.ahmadnchatila.pointers")
set (POINTER_CLIENT_ID "com.ahmadnchatila.pointerc")
set (POINTER_DAEMON_ID "com.ahmadnchatila.pointerd")

#
# Apps sources
#
set (APPS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/apps")
set (LIB_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

set (ANDROID_SOURCE_DIR "${APPS_SOURCE_DIR}/flutter/android")
set (IOS_SOURCE_DIR "${APPS_SOURCE_DIR}/flutter/ios")

set (LIB_ANDROID_SOURCE_DIR "${LIB_SOURCE_DIR}/pointer/android")


#
# Cmd sources
#
set (CMD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/cmd")


#
# PowerTip User Account Password
#
set (POINTER_USER_USERNAME "DnD_PowerTipApp")
set (POINTER_USER_PASSWORD "8ba09ff7-a2a4-4d5b-83e8-8713769df3ee")

if (WIN32)
    set (POINTER_POWTIPD_NAME "powtipd.exe")
    set (POINTER_POWTIPS_NAME "powtips.exe")
else()
    set (POINTER_POWTIPD_NAME "powtipd")
    set (POINTER_POWTIPS_NAME "powtips")
endif()

add_definitions(
    -DPOINTER_USER_USERNAME="${POINTER_USER_USERNAME}"
    -DPOINTER_USER_PASSWORD="${POINTER_USER_PASSWORD}"
    -DPOINTER_GUIAPP_ID="${POINTER_GUIAPP_ID}"
    -DPOINTER_SERVER_ID="${POINTER_SERVER_ID}"
    -DPOINTER_CLIENT_ID="${POINTER_CLIENT_ID}"
    -DPOINTER_DAEMON_ID="${POINTER_DAEMON_ID}"
    -DPOINTER_POWTIPD_NAME="${POINTER_POWTIPD_NAME}"
    -DPOINTER_POWTIPS_NAME="${POINTER_POWTIPS_NAME}"
)

#
# PowerTip version
#
include (cmake/Version.cmake)

# Add headers to source list
if (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
    set (POINTER_ADD_HEADERS FALSE)
else()
    set (POINTER_ADD_HEADERS TRUE)
endif()

if (UNIX)
    if (NOT APPLE)
        if (${CMAKE_SYSTEM_NAME} MATCHES "Android")
            add_definitions(
                -DANDROID
                -DJNIAPI)
            endif()

        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        set (LINUX TRUE)
    endif()

    # For config.h, detect the libraries, functions, etc.
    include (CheckIncludeFiles)
    include (CheckLibraryExists)
    include (CheckFunctionExists)
    include (CheckTypeSize)
    include (CheckIncludeFileCXX)
    include (CheckSymbolExists)
    include (CheckCSourceCompiles)

    # check_include_file_cxx (istream HAVE_ISTREAM)
    # check_include_file_cxx (ostream HAVE_OSTREAM)
    # check_include_file_cxx (sstream HAVE_SSTREAM)

    check_include_files (inttypes.h HAVE_INTTYPES_H)
    check_include_files (locale.h HAVE_LOCALE_H)
    check_include_files (memory.h HAVE_MEMORY_H)
    check_include_files (stdlib.h HAVE_STDLIB_H)
    check_include_files (strings.h HAVE_STRINGS_H)
    check_include_files (string.h HAVE_STRING_H)
    check_include_files (sys/select.h HAVE_SYS_SELECT_H)
    check_include_files (sys/socket.h HAVE_SYS_SOCKET_H)
    check_include_files (sys/stat.h HAVE_SYS_STAT_H)
    check_include_files (sys/time.h HAVE_SYS_TIME_H)
    check_include_files (sys/utsname.h HAVE_SYS_UTSNAME_H)
    check_include_files (unistd.h HAVE_UNISTD_H)
    check_include_files (wchar.h HAVE_WCHAR_H)

    check_function_exists (getpwuid_r HAVE_GETPWUID_R)
    check_function_exists (gmtime_r HAVE_GMTIME_R)
    check_function_exists (nanosleep HAVE_NANOSLEEP)
    check_function_exists (poll HAVE_POLL)
    check_function_exists (sigwait HAVE_POSIX_SIGWAIT)
    check_function_exists (strftime HAVE_STRFTIME)
    check_function_exists (vsnprintf HAVE_VSNPRINTF)
    check_function_exists (inet_aton HAVE_INET_ATON)

    # For some reason, the check_function_exists macro doesn't detect
    # the inet_aton on some pure Unix platforms (e.g. sunos5). So we
    # need to do a more detailed check and also include some extra libs.
    if (NOT HAVE_INET_ATON)
        set (CMAKE_REQUIRED_LIBRARIES nsl)

        check_c_source_compiles (
            "#include <arpa/inet.h>\n int main() { inet_aton (0, 0); }"
            HAVE_INET_ATON_ADV)

        set (CMAKE_REQUIRED_LIBRARIES)

        if (HAVE_INET_ATON_ADV)
            # Override the previous fail.
            set (HAVE_INET_ATON 1)

            # Assume that both nsl and socket will be needed,
            # it seems safe to add socket on the back of nsl,
            # since socket only ever needed when nsl is needed.
            list (APPEND libs nsl socket)
        endif()

    endif()

    check_type_size (char SIZEOF_CHAR)
    check_type_size (int SIZEOF_INT)
    check_type_size (long SIZEOF_LONG)
    check_type_size (short SIZEOF_SHORT)
    
    # pthread is used on both Linux and Mac
    check_library_exists ("pthread" pthread_create "" HAVE_PTHREAD)
    if (HAVE_PTHREAD)
        list (APPEND libs pthread)
    else()
        if (${CMAKE_SYSTEM_NAME} MATCHES "Android")
            # not important on Android-based devices.
            message("PTHREAD implementation is not available on Android, which is fine.")
        else()
            message (FATAL_ERROR "Missing library: pthread")
        endif()
    endif()
    
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows|Mac")

    message("configuring Android app CMakeLists.txt")
    configure_file (${ANDROID_SOURCE_DIR}/app/src/main/cpp/CMakeLists.txt.in ${ANDROID_SOURCE_DIR}/app/src/main/cpp/CMakeLists.txt)

    message("configuring Android library CMakeLists.txt")
    configure_file (${LIB_ANDROID_SOURCE_DIR}/app/src/main/cpp/CMakeLists.txt.in ${LIB_ANDROID_SOURCE_DIR}/app/src/main/cpp/CMakeLists.txt)

endif()

add_subdirectory(src)
file(GLOB headers "*.h")
file(GLOB sources "*.c")

if (POINTER_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

if (WIN32)
    file(GLOB net_headers "win32/*.h")
    file(GLOB net_sources "win32/*.c")
elseif (UNIX)
    file(GLOB net_headers "unix/*.h")
    file(GLOB net_sources "unix/*.c")
endif()

list(APPEND headers ${net_headers})
list(APPEND sources ${net_sources})

if (POINTER_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

add_library(net STATIC ${sources})

target_link_libraries(net ${CMAKE_DL_LIBS} ${libs})
if (UNIX)
endif()
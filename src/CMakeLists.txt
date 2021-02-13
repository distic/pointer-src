include_directories (./lib)
include_directories (${CMAKE_CURRENT_BINARY_DIR}/lib)

add_subdirectory(lib)
# add_subdirectory(apps)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "iOS|Android")
    # add_subdirectory(cmd)
    # add_subdirectory(tests)
endif()
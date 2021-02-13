file(GLOB headers "*.h")
file(GLOB sources "*.cpp")

if (POWERTIP_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

if (POWERTIP_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

add_library(arch_gui STATIC ${sources})

if (UNIX)
    target_link_libraries(arch_gui logs ${CMAKE_DL_LIBS} ${libs})
endif()
file(GLOB headers "*.h")
file(GLOB sources "*.c")

if (POINTER_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

list(APPEND headers ${pointer_headers})
list(APPEND sources ${pointer_sources})

if (POINTER_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

add_library(pointer SHARED ${sources})

if (${CMAKE_SYSTEM_NAME} MATCHES "iOS")

    set_target_properties(pointer PROPERTIES
        FRAMEWORK TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.ahmadnchatila.libpointer"
        # PUBLIC_HEADER "${headers}"
    )

endif()

target_link_libraries(pointer net ${CMAKE_DL_LIBS} ${libs})
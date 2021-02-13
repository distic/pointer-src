file (GLOB win32_app_sources 
                "*.cpp"
                "ui/*.cpp")

file (GLOB win32_app_headers
                "*.h"
                "ui/*.h")



list(APPEND sources ${win32_app_sources})
list(APPEND headers ${win32_app_headers})

list(APPEND sources
        misc/powertip.ico
        misc/powertip.rc
        misc/DeclareDPIAware.manifest
        misc/small.ico
    )

if (POWERTIP_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (WIN32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")
    endif()
endif()

add_executable(powertip WIN32 ${sources})
target_link_libraries(powertip
core
platform
logs
ipc
app
arch_net
net
qrcode
arch_gui
arch_os
arch_xarch
os
io
utils
${SOCKPP_LIBS}
${libs})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    install (TARGETS powertip DESTINATION ${POWERTIP_BUNDLE_BINARY_DIR})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    install (TARGETS powertip DESTINATION bin)
endif()

#
# ScreenSaver
#

# add_executable(scrsaver WIN32 "ScreenSaver.c")

# set_target_properties(scrsaver 
#     PROPERTIES 
#         OUTPUT_NAME "scrsaver"
#         SUFFIX ".scr"
#     )
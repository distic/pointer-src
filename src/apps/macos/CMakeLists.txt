set (powtips_bin ${CMAKE_BINARY_DIR}/bin/powtips)
set (powtipd_bin ${CMAKE_BINARY_DIR}/bin/powtipd)

set (PROJ_LIBS ${CMAKE_BINARY_DIR}/_Xcode_Deps/${CMAKE_BUILD_TYPE}/lib)

set (PROJ_ENTITLEMENTS ${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/PowerTip-${CMAKE_BUILD_TYPE}.entitlements)
set (PROJ_PLIST ${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/Contents/Info.plist.in)

configure_file (PowerTip-macOS.xcodeproj/project.pbxproj.in ${CMAKE_CURRENT_SOURCE_DIR}/PowerTip-macOS.xcodeproj/project.pbxproj)
configure_file (${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/Contents/Info.plist.in ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)

file (GLOB_RECURSE LibFiles ${CMAKE_BINARY_DIR}/src/lib/*.a)
foreach (LibFile IN LISTS LibFiles)
    file (COPY ${LibFile} DESTINATION ${PROJ_LIBS})
endforeach()

############################################################################################################
## Full CMake Project Generator
##
## Issue(s)
## ========
## 1) Statusbar icon doesn't show when running the app.
## 2) Sandbox doesn't work on GUI app. Hence, results in IPC connection failure for some weird reason.
## 
############################################################################################################

# project ("PowerTip-macos" C CXX Swift)

# file(GLOB_RECURSE SOURCES "*.mm" "*swift")
# file(GLOB_RECURSE HEADERS "*.h" "*.hpp")

# set(STATIC_DEPENDENCIES
#     app
#     arch_daemon
#     arch_dir
#     arch_fake_hid
#     arch_net
#     arch_os
#     arch_xarch
#     core
#     io
#     ipc
#     logs
#     net
#     os
#     platform
#     qrcode
#     utils
# )

# if( NOT SKIP_FIND_FOUNDATION_LIBRARY)
#    find_library( FOUNDATION_LIBRARY Foundation)
#    message( STATUS "FOUNDATION_LIBRARY is ${FOUNDATION_LIBRARY}")
# endif()

# if( NOT SKIP_FIND_COCOA_LIBRARY)
#    find_library( COCOA_LIBRARY Cocoa)
#    message( STATUS "COCOA_LIBRARY is ${COCOA_LIBRARY}")
# endif()

# set(DEPENDENCIES
#     ${FOUNDATION_LIBRARY}
#     ${COCOA_LIBRARY}
# )

# set(PROJ_ENTITLEMENTS_Debug ${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/PowerTip-Debug.entitlements)
# set(PROJ_ENTITLEMENTS_Release ${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/PowerTip-Release.entitlements)
# set(PROJ_ENTITLEMENTS_RelWithDebInfo ${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/PowerTip-RelWithDebInfo.entitlements)
# set(PROJ_ENTITLEMENTS_MinSizeRel ${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/PowerTip-MinSizeRel.entitlements)

# set(PROJ_PLIST ${CMAKE_SOURCE_DIR}/dist/apple/PowerTip-macOS/bundle/PowerTip.app/Contents/Info.plist.in)

# set(GLOBAL_RESOURCES
#     Assets.xcassets
#     Views/PopupMenuView.xib
# )

# set(BASE_RESOURCES
#     Base.lproj/Main.storyboard
# )

# set(RESOURCES
#    ${GLOBAL_RESOURCES}
#    ${BASE_RESOURCES}
# )

# ##
# ## PowerTip
# ##

# add_executable(PowerTip MACOSX_BUNDLE
#     ${SOURCES}
#     ${HEADERS}
#     ${PUBLIC_HEADERS}
#     ${PROJECT_HEADERS}
#     ${PRIVATE_HEADERS}
#     ${RESOURCES}
#     ${CMD_DEPENDENCIES}
# )

# target_link_libraries( PowerTip
#     ${STATIC_DEPENDENCIES}
#     ${DEPENDENCIES}
# )

# set_source_files_properties(
# ${RESOURCES}
#    PROPERTIES
#       MACOSX_PACKAGE_LOCATION
#       Resources
# )

# set (CMD_DEPENDENCIES 
#         powtipd 
#         powtips
# )

# add_dependencies(PowerTip ${CMD_DEPENDENCIES})

# set_source_files_properties(${CMD_DEPENDENCIES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

# if (APPLE)
#     set_target_properties(PowerTip PROPERTIES
#         MACOSX_BUNDLE_INFO_PLIST ${PROJ_PLIST}
#         XCODE_ATTRIBUTE_CODE_SIGN_STYLE Automatic
#         XCODE_ATTRIBUTE_DEVELOPMENT_TEAM 6ZT79K7QRE
#         XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.ahmadnchatila.PowerTip"
#         XCODE_ATTRIBUTE_PRODUCT_PRODUCT_NAME "PowerTip"
#         XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon
#         XCODE_ATTRIBUTE_SWIFT_OBJC_BRIDGING_HEADER "src/gui/macos/PowerTip-Bridging-Header.h"
#         XCODE_ATTRIBUTE_SWIFT_OPTIMIZATION_LEVEL "-Onone"
#         XCODE_ATTRIBUTE_SWIFT_VERSION 5.0
#         XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES YES
#     )

#     set_target_properties(PowerTip PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS[variant=Debug] ${PROJ_ENTITLEMENTS_Debug} )
#     set_target_properties(PowerTip PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS[variant=Release] ${PROJ_ENTITLEMENTS_Release} )
#     set_target_properties(PowerTip PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS[variant=RelWithDebInfo] ${PROJ_ENTITLEMENTS_RelWithDebInfo} )
#     set_target_properties(PowerTip PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS[variant=MinSizeRel] ${PROJ_ENTITLEMENTS_MinSizeRel} )

# endif()

# # add_custom_command(TARGET PowerTip POST_BUILD
# #     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:powtips> ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/PowerTip.app/Contents/MacOS
# #     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:powtipd> ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/PowerTip.app/Contents/MacOS
# #     # COMMENT "HACK HACK: Consider removing the \"Debug\" string from the file copy when switching to Release builds !!!!!"
# # )
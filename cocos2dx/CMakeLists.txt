#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME hello-world)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
    ezyfox-client/src/handler/EzyEventHandlers.cpp
    ezyfox-client/src/handler/EzyDataHandlers.cpp
    ezyfox-client/src/handler/EzyEventHandler.cpp
    ezyfox-client/src/handler/EzyAppDataHandlers.cpp
    ezyfox-client/src/handler/EzyPluginDataHandlers.cpp
    ezyfox-client/src/handler/EzyPluginDataHandler.cpp
    ezyfox-client/src/handler/EzyAppDataHandler.cpp
    ezyfox-client/src/handler/EzyDataHandler.cpp
    ezyfox-client/src/EzyUTClient.cpp
    ezyfox-client/src/logger/EzyLogger.cpp
    ezyfox-client/src/config/EzyClientConfig.cpp
    ezyfox-client/src/entity/EzyApp.cpp
    ezyfox-client/src/entity/EzyString.cpp
    ezyfox-client/src/entity/EzyZone.cpp
    ezyfox-client/src/entity/EzyPrimitive.cpp
    ezyfox-client/src/entity/EzyObject.cpp
    ezyfox-client/src/entity/EzyArray.cpp
    ezyfox-client/src/entity/EzyValue.cpp
    ezyfox-client/src/entity/EzyUser.cpp
    ezyfox-client/src/entity/EzyPlugin.cpp
    ezyfox-client/src/codec/EzyMessage.cpp
    ezyfox-client/src/codec/EzyDataDecoder.cpp
    ezyfox-client/src/codec/EzyDataEncoder.cpp
    ezyfox-client/src/EzyClient.cpp
    ezyfox-client/src/setup/EzySetup.cpp
    ezyfox-client/src/EzyClients.cpp
    ezyfox-client/src/manager/EzyPluginManager.cpp
    ezyfox-client/src/manager/EzyAppManager.cpp
    ezyfox-client/src/manager/EzyHandlerManager.cpp
    ezyfox-client/src/manager/EzyPingManager.cpp
    ezyfox-client/src/constant/EzyConnectionStatus.cpp
    ezyfox-client/src/constant/EzyCommand.cpp
    ezyfox-client/src/constant/EzyDisconnectReason.cpp
    ezyfox-client/src/constant/EzyConnectionFailedReason.cpp
    ezyfox-client/src/concurrent/EzyThread.cpp
    ezyfox-client/src/concurrent/EzyScheduleAtFixedRate.cpp
    ezyfox-client/src/gc/EzyReleasePool.cpp
    ezyfox-client/src/gc/EzyAutoReleasePool.cpp
    ezyfox-client/src/request/EzyRequest.cpp
    ezyfox-client/src/request/EzyRequestSerializer.cpp
    ezyfox-client/src/event/EzyEvent.cpp
    ezyfox-client/src/event/EzyEventType.cpp
    ezyfox-client/src/base/EzyRef.cpp
    ezyfox-client/src/socket/EzyTcpSocketClient.cpp
    ezyfox-client/src/socket/EzySocketClient.cpp
    ezyfox-client/src/socket/EzySocketAdapter.cpp
    ezyfox-client/src/socket/EzySocketCore.cpp
    ezyfox-client/src/socket/EzyMainEventsLoop.cpp
    ezyfox-client/src/socket/EzyPingSchedule.cpp
    ezyfox-client/src/socket/EzySocketPool.cpp
    ezyfox-client/src/socket/EzySocketReader.cpp
    ezyfox-client/src/socket/EzyUTSocketClient.cpp
    ezyfox-client/src/socket/EzyUdpSocketClient.cpp
    ezyfox-client/src/socket/EzySocketWriter.cpp
     Classes/SocketClientProxy.cpp   
     Classes/AppDelegate.cpp
     Classes/HelloWorldScene.cpp
     Classes/ParallaxNodeExtras.cpp
     Classes/CustomParallaxNode.cpp
     Classes/GameManager.cpp
     )
list(APPEND GAME_HEADER
    ezyfox-client/src/handler/EzyPluginDataHandlers.h
    ezyfox-client/src/handler/EzyEventHandler.h
    ezyfox-client/src/handler/EzyPluginDataHandler.h
    ezyfox-client/src/handler/EzyDataHandlers.h
    ezyfox-client/src/handler/EzyEventHandlers.h
    ezyfox-client/src/handler/EzyAppDataHandler.h
    ezyfox-client/src/handler/EzyDataHandler.h
    ezyfox-client/src/handler/EzyAppDataHandlers.h
    ezyfox-client/src/EzyClient.h
    ezyfox-client/src/EzyClients.h
    ezyfox-client/src/EzyUTClient.h
    ezyfox-client/src/logger/EzyLogger.h
    ezyfox-client/src/util/EzyStack.h
    ezyfox-client/src/util/EzyMaps.h
    ezyfox-client/src/config/EzyClientConfig.h
    ezyfox-client/src/entity/EzyUser.h
    ezyfox-client/src/entity/EzyPlugin.h
    ezyfox-client/src/entity/EzyPrimitive.h
    ezyfox-client/src/entity/EzyArray.h
    ezyfox-client/src/entity/EzyValue.h
    ezyfox-client/src/entity/EzyZone.h
    ezyfox-client/src/entity/EzyApp.h
    ezyfox-client/src/entity/EzyObject.h
    ezyfox-client/src/entity/EzyString.h
    ezyfox-client/src/codec/EzyDataEncoder.h
    ezyfox-client/src/codec/EzyMessage.h
    ezyfox-client/src/codec/EzyDataDecoder.h
    ezyfox-client/src/setup/EzySetup.h
    ezyfox-client/src/EzyHeaders.h
    ezyfox-client/src/manager/EzyHandlerManager.h
    ezyfox-client/src/manager/EzyAppManager.h
    ezyfox-client/src/manager/EzyPingManager.h
    ezyfox-client/src/manager/EzyPluginManager.h
    ezyfox-client/src/EzyMacro.h
    ezyfox-client/src/constant/EzyStatusCode.h
    ezyfox-client/src/constant/EzyConnectionStatus.h
    ezyfox-client/src/constant/EzyTransportType.h
    ezyfox-client/src/constant/EzyConnectionFailedReason.h
    ezyfox-client/src/constant/EzyDisconnectReason.h
    ezyfox-client/src/constant/EzyCommand.h
    ezyfox-client/src/concurrent/EzyThread.h
    ezyfox-client/src/concurrent/EzyScheduleAtFixedRate.h
    ezyfox-client/src/gc/EzyReleasePool.h
    ezyfox-client/src/gc/EzyAutoReleasePool.h
    ezyfox-client/src/request/EzyRequest.h
    ezyfox-client/src/request/EzyRequestSerializer.h
    ezyfox-client/src/event/EzyEventType.h
    ezyfox-client/src/event/EzyEvent.h
    ezyfox-client/src/base/EzyRef.h
    ezyfox-client/src/socket/EzySocketDelegate.h
    ezyfox-client/src/socket/EzySocketAdapter.h
    ezyfox-client/src/socket/EzySocketClient.h
    ezyfox-client/src/socket/EzySocketReader.h
    ezyfox-client/src/socket/EzySocketDefine.h
    ezyfox-client/src/socket/EzyTcpSocketClient.h
    ezyfox-client/src/socket/EzySocketPool.h
    ezyfox-client/src/socket/EzyUdpSocketClient.h
    ezyfox-client/src/socket/EzyUTSocketClient.h
    ezyfox-client/src/socket/EzySender.h
    ezyfox-client/src/socket/EzySocketCore.h
    ezyfox-client/src/socket/EzySocketWriter.h
    ezyfox-client/src/socket/EzyPingSchedule.h
    ezyfox-client/src/socket/EzyMainEventsLoop.h
     Classes/SocketClientProxy.h
     Classes/AppDelegate.h
     Classes/HelloWorldScene.h
     Classes/ParallaxNodeExtras.h
     Classes/CustomParallaxNode.h
     Classes/GameManager.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE ezyfox-client/src
        PRIVATE ezyfox-client/src/handler
        PRIVATE ezyfox-client/src/logger
        PRIVATE ezyfox-client/src/util
        PRIVATE ezyfox-client/src/config
        PRIVATE ezyfox-client/src/entity
        PRIVATE ezyfox-client/src/codec
        PRIVATE ezyfox-client/src/setup
        PRIVATE ezyfox-client/src/manager
        PRIVATE ezyfox-client/src/constant
        PRIVATE ezyfox-client/src/concurrent
        PRIVATE ezyfox-client/src/gc
        PRIVATE ezyfox-client/src/request
        PRIVATE ezyfox-client/src/event
        PRIVATE ezyfox-client/src/base
        PRIVATE ezyfox-client/src/socket
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()

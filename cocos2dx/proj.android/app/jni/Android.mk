LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := \
		hellocpp/main.cpp \
        $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
        $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
        $(LOCAL_PATH)/../../../Classes/CustomParallaxNode.cpp \
        $(LOCAL_PATH)/../../../Classes/ParallaxNodeExtras.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyEventHandlers.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyDataHandlers.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyEventHandler.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyAppDataHandlers.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyPluginDataHandlers.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyPluginDataHandler.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyAppDataHandler.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/handler/EzyDataHandler.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/EzyUTClient.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/logger/EzyLogger.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/config/EzyClientConfig.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyApp.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyString.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyZone.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyPrimitive.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyObject.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyArray.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyValue.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyUser.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyJson.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/entity/EzyPlugin.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/codec/EzyMessage.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/codec/EzyDataDecoder.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/codec/EzyDataEncoder.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/EzyClient.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/setup/EzySetup.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/EzyClients.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/manager/EzyPluginManager.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/manager/EzyAppManager.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/manager/EzyHandlerManager.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/manager/EzyPingManager.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/constant/EzyConnectionStatus.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/constant/EzyCommand.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/constant/EzyDisconnectReason.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/constant/EzyConnectionFailedReason.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/concurrent/EzyThread.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/concurrent/EzyScheduleAtFixedRate.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/gc/EzyReleasePool.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/gc/EzyAutoReleasePool.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/request/EzyRequest.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/request/EzyRequestSerializer.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/event/EzyEvent.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/event/EzyEventType.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/base/EzyRef.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzyTcpSocketClient.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzySocketClient.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzySocketAdapter.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzySocketCore.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzyMainEventsLoop.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzyPingSchedule.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzySocketPool.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzySocketReader.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzyUTSocketClient.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzyUdpSocketClient.cpp \
		$(LOCAL_PATH)../../../ezyfox-client/src/socket/EzySocketWriter.cpp \

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../../Classes \
		$(LOCAL_PATH)/../../../ezyfox-client/src \
		$(LOCAL_PATH)/../../../ezyfox-client/src/handler \
		$(LOCAL_PATH)/../../../ezyfox-client/src/logger \
		$(LOCAL_PATH)/../../../ezyfox-client/src/util \
		$(LOCAL_PATH)/../../../ezyfox-client/src/config \
		$(LOCAL_PATH)/../../../ezyfox-client/src/entity \
		$(LOCAL_PATH)/../../../ezyfox-client/src/codec \
		$(LOCAL_PATH)/../../../ezyfox-client/src/setup \
		$(LOCAL_PATH)/../../../ezyfox-client/src/manager \
		$(LOCAL_PATH)/../../../ezyfox-client/src/constant \
		$(LOCAL_PATH)/../../../ezyfox-client/src/concurrent \
		$(LOCAL_PATH)/../../../ezyfox-client/src/gc \
		$(LOCAL_PATH)/../../../ezyfox-client/src/request \
		$(LOCAL_PATH)/../../../ezyfox-client/src/event \
		$(LOCAL_PATH)/../../../ezyfox-client/src/base \
		$(LOCAL_PATH)/../../../ezyfox-client/src/socket \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

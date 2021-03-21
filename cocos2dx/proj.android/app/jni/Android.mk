LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := \
		hellocpp/main.cpp \
		$(LOCAL_PATH)/../../../Classes/SocketClientProxy.cpp \
        $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
        $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
        $(LOCAL_PATH)/../../../Classes/CustomParallaxNode.cpp \
        $(LOCAL_PATH)/../../../Classes/ParallaxNodeExtras.cpp

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)
$(call import-module, ezyfox-client)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

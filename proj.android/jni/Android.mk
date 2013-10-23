LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/TitleScene.cpp \
                   ../../Classes/ScreenHelper.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/GamePiece.cpp \
                   ../../Classes/Grid.cpp \
                   ../../Classes/SpritHelper.cpp \
                   ../../Classes/Goals.cpp \
                   ../../Classes/HUD.cpp 
                   
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
/Users/akinlin/Desktop/TBDEntertainment/Cocos2d/cocos2d-2.1rc0-x-2.1.3/external/Box2D                 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static box2d_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) $(call import-module,external/Box2D)

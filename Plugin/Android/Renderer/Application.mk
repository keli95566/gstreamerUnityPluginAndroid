APP_ABI := armeabi-v7a 
APP_PLATFORM := android-28

APP_STL := gnustl_static
APP_CPPFLAGS += -std=c++11
NDK_TOOLCHAIN_VERSION := clang
APP_BUILD_SCRIPT :=Android.mk
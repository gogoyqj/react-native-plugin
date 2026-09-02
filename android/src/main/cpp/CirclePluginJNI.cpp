#include <jni.h>
#include <android/log.h>
#include <jsi/jsi.h>

#include "../../../../cpp/CirclePluginTurboModule.h"

#define TAG "CirclePlugin"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

using namespace facebook;

extern "C" {

/**
 * 注册 CirclePluginTurboModule 到 JS runtime。
 * 由 CirclePluginModule.registerTurboModule() 调用。
 */
JNIEXPORT void JNICALL
Java_com_circleplugin_CirclePluginModule_nativeRegisterTurboModule(
    JNIEnv *env,
    jclass clazz,
    jlong runtimePtr) {

    LOGI("Registering CirclePluginTurboModule");

    auto *runtime = reinterpret_cast<jsi::Runtime *>(runtimePtr);

    circleplugin::installCirclePluginTurboModule(*runtime);

    LOGI("CirclePluginTurboModule registered successfully");
}

} // extern "C"

#include <jni.h>
#include <android/log.h>

#include "../../../../cpp/CircleDrawer.h"

#define TAG "CirclePlugin"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT jbyteArray JNICALL
Java_com_circleplugin_CirclePluginModule_nativeDrawCircle(
    JNIEnv *env,
    jclass clazz,
    jint radius,
    jint color) {

    LOGI("drawCircle: radius=%d, color=0x%08X", radius, color);

    auto result = circleplugin::drawCircle(radius, static_cast<uint32_t>(color));

    jbyteArray jPixels = env->NewByteArray(result.pixels.size());
    if (jPixels == nullptr) {
        LOGE("Failed to allocate JNI byte array");
        return nullptr;
    }

    env->SetByteArrayRegion(jPixels, 0, result.pixels.size(),
                            reinterpret_cast<const jbyte *>(result.pixels.data()));

    return jPixels;
}

} // extern "C"

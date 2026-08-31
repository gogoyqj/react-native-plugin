#include <jni.h>
#include <android/log.h>
#include <jsi/jsi.h>

#include "../../../../cpp/CircleJSI.h"

#define TAG "CirclePlugin"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

using namespace facebook;

extern "C" {

/**
 * Java_com_circleplugin_CirclePluginModule_nativeInstallJSI
 *
 * 从 Java 侧接收 JSI Runtime 指针，调用 C++ 安装 JSI 绑定。
 * 命名规则: Java_包名_类名_方法名
 */
JNIEXPORT void JNICALL
Java_com_circleplugin_CirclePluginModule_nativeInstallJSI(
    JNIEnv *env,
    jclass clazz,
    jlong runtimePtr) {

    LOGI("Installing CircleJSI bindings");

    // 将 jlong 转回 jsi::Runtime*
    auto *runtime = reinterpret_cast<jsi::Runtime *>(runtimePtr);

    // 调用 C++ 安装函数
    circleplugin::installCircleJSI(*runtime);

    LOGI("CircleJSI bindings installed successfully");
}

} // extern "C"

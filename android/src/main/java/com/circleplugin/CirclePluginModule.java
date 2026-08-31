package com.circleplugin;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;

public class CirclePluginModule extends ReactContextBaseJavaModule {
    static {
        System.loadLibrary("circleplugin");
    }

    // JSI 安装函数 — 通过 JNI 调用 C++ 侧的 installCircleJSI
    private static native void nativeInstallJSI(long runtimePtr);

    public CirclePluginModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @NonNull
    @Override
    public String getName() {
        return "CirclePlugin";
    }

    /**
     * 安装 JSI 绑定。
     * 在 ReactHost 初始化时调用。
     */
    public void installJSI(long runtimePtr) {
        nativeInstallJSI(runtimePtr);
    }
}

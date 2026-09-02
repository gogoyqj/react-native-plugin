package com.circleplugin;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;

public class CirclePluginModule extends ReactContextBaseJavaModule {
    static {
        System.loadLibrary("circleplugin");
    }

    // JNI: 注册 TurboModule 到 JS runtime
    static native void nativeRegisterTurboModule(long runtimePtr);

    public CirclePluginModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @NonNull
    @Override
    public String getName() {
        return "CirclePlugin";
    }

    /**
     * 注册 TurboModule 到 JS runtime。
     * 在 JSIModulePackage.getJSIModules() 时调用。
     */
    public static void registerTurboModule(long runtimePtr) {
        nativeRegisterTurboModule(runtimePtr);
    }
}

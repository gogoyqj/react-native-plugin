package com.circleplugin;

import androidx.annotation.NonNull;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ViewManager;
import com.facebook.react.bridge.JSIModulePackage;
import com.facebook.react.bridge.JSIModuleSpec;
import com.facebook.react.bridge.JavaScriptContextHolder;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class CirclePluginPackage implements ReactPackage, JSIModulePackage {

    @NonNull
    @Override
    public List<NativeModule> createNativeModules(@NonNull ReactApplicationContext reactContext) {
        List<NativeModule> modules = new ArrayList<>();
        modules.add(new CirclePluginModule(reactContext));
        return modules;
    }

    @NonNull
    @Override
    public List<ViewManager> createViewManagers(@NonNull ReactApplicationContext reactContext) {
        return Collections.emptyList();
    }

    /**
     * TurboModule 注册 — 在 TurboModuleManager 初始化之后、JS 执行之前调用。
     * 包装 __turboModuleProxy，注入 CirclePlugin TurboModule。
     */
    @Override
    public List<JSIModuleSpec> getJSIModules(
            ReactApplicationContext reactApplicationContext,
            JavaScriptContextHolder jsContext) {

        CirclePluginModule.registerTurboModule(jsContext.get());

        return Collections.emptyList();
    }
}

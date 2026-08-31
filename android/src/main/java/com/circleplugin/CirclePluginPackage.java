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

    private CirclePluginModule circleModule;

    @NonNull
    @Override
    public List<NativeModule> createNativeModules(@NonNull ReactApplicationContext reactContext) {
        circleModule = new CirclePluginModule(reactContext);
        List<NativeModule> modules = new ArrayList<>();
        modules.add(circleModule);
        return modules;
    }

    @NonNull
    @Override
    public List<ViewManager> createViewManagers(@NonNull ReactApplicationContext reactContext) {
        return Collections.emptyList();
    }

    /**
     * JSI 模块初始化 — 在 JS runtime 启动时调用。
     * 这里安装 C++ JSI 绑定。
     */
    @Override
    public List<JSIModuleSpec> getJSIModules(
            ReactApplicationContext reactApplicationContext,
            JavaScriptContextHolder jsContext) {

        // 获取 JSI Runtime 指针，传给 native 层
        if (circleModule != null) {
            circleModule.installJSI(jsContext.get());
        }

        return Collections.emptyList();
    }
}

package com.circleplugin;

import android.util.Base64;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.Arguments;

public class CirclePluginModule extends ReactContextBaseJavaModule {
    static {
        System.loadLibrary("circleplugin");
    }

    // Native method from C++ via JNI
    private static native byte[] nativeDrawCircle(int radius, int color);

    public CirclePluginModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @NonNull
    @Override
    public String getName() {
        return "CirclePlugin";
    }

    @ReactMethod
    public void drawCircle(double radius, double color, Promise promise) {
        try {
            int r = (int) radius;
            int c = (int) color;

            if (r <= 0 || r > 2048) {
                promise.reject("INVALID_RADIUS", "radius must be between 1 and 2048");
                return;
            }

            // Call C++ implementation via JNI
            byte[] pixels = nativeDrawCircle(r, c);

            // Convert to base64
            String base64 = Base64.encodeToString(pixels, Base64.NO_WRAP);

            WritableMap result = Arguments.createMap();
            result.putInt("width", r * 2);
            result.putInt("height", r * 2);
            result.putString("data", base64);

            promise.resolve(result);
        } catch (Exception e) {
            promise.reject("CIRCLE_ERROR", e.getMessage(), e);
        }
    }
}

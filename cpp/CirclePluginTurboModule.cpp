#include "CirclePluginTurboModule.h"

using namespace facebook;

// RN 0.73 没有 ArrayBuffer::createFromBytes，通过 MutableBuffer 包装
class RawBuffer : public jsi::MutableBuffer {
public:
  RawBuffer(std::vector<uint8_t> data) : data_(std::move(data)) {}
  uint8_t *data() override { return data_.data(); }
  size_t size() const override { return data_.size(); }

private:
  std::vector<uint8_t> data_;
};

namespace circleplugin {

/**
 * CirclePlugin TurboModule — JSI HostObject。
 * JS 侧通过 TurboModuleRegistry.getEnforcing('CirclePlugin') 访问。
 */
class CirclePluginModule : public jsi::HostObject {
public:
  jsi::Value get(jsi::Runtime &rt, const jsi::PropNameID &name) override {
    auto methodName = name.utf8(rt);

    if (methodName == "drawCircle") {
      return jsi::Function::createFromHostFunction(
          rt, name, 2,
          [](jsi::Runtime &runtime,
             const jsi::Value &,
             const jsi::Value *args,
             size_t count) -> jsi::Value {

            if (count < 2) {
              throw jsi::JSError(
                  runtime, "drawCircle requires 2 arguments: radius, color");
            }

            int radius = static_cast<int>(args[0].asNumber());
            uint32_t color = static_cast<uint32_t>(args[1].asNumber());

            if (radius <= 0 || radius > 2048) {
              throw jsi::JSError(
                  runtime, "radius must be between 1 and 2048");
            }

            auto result = drawCircle(radius, color);

            auto buffer = jsi::ArrayBuffer(
                runtime,
                std::make_shared<RawBuffer>(std::move(result.pixels)));

            auto obj = jsi::Object(runtime);
            obj.setProperty(runtime, "width", jsi::Value(result.width));
            obj.setProperty(runtime, "height", jsi::Value(result.height));
            obj.setProperty(runtime, "buffer", std::move(buffer));

            return obj;
          });
    }

    return jsi::Value::undefined();
  }

  std::vector<jsi::PropNameID> getPropertyNames(
      jsi::Runtime &rt) override {
    std::vector<jsi::PropNameID> names;
    names.push_back(jsi::PropNameID::forAscii(rt, "drawCircle"));
    return names;
  }
};

/**
 * 安装 CirclePlugin TurboModule。
 *
 * 调用时机：JSIModulePackage.getJSIModules()，在 TurboModuleManager
 * 安装 __turboModuleProxy 之后、JS bundle 执行之前。
 *
 * 包装已有的 __turboModuleProxy：
 *   - "CirclePlugin" → 返回我们的 HostObject
 *   - 其他模块 → 委托给原始 proxy
 */
void installCirclePluginTurboModule(jsi::Runtime &runtime) {
  // shared_ptr 包装 move-only 的 jsi::Value，使 lambda 可拷贝
  auto originalProxy = std::make_shared<jsi::Value>(
      runtime.global().getProperty(runtime, "__turboModuleProxy"));

  auto module = std::make_shared<CirclePluginModule>();

  auto wrapper = jsi::Function::createFromHostFunction(
      runtime,
      jsi::PropNameID::forAscii(runtime, "__turboModuleProxy"),
      1,
      [originalProxy, module](
          jsi::Runtime &rt,
          const jsi::Value &,
          const jsi::Value *args,
          size_t count) -> jsi::Value {

        if (count < 1) {
          throw jsi::JSError(
              rt, "__turboModuleProxy requires 1 argument");
        }

        std::string moduleName = args[0].getString(rt).utf8(rt);

        if (moduleName == "CirclePlugin") {
          return jsi::Object::createFromHostObject(rt, module);
        }

        // 委托给原始 TurboModule proxy
        if (originalProxy->isObject() &&
            originalProxy->asObject(rt).isFunction(rt)) {
          return originalProxy->asObject(rt).asFunction(rt).call(
              rt, args, count);
        }

        return jsi::Value::null();
      });

  runtime.global().setProperty(
      runtime, "__turboModuleProxy", std::move(wrapper));
}

} // namespace circleplugin

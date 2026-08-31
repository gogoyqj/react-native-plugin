#include "CircleJSI.h"

using namespace facebook;

namespace circleplugin {

void installCircleJSI(jsi::Runtime &runtime) {
  // 注册全局函数: __drawCircle(radius, color) → { width, height, buffer }
  auto drawCircleFunc = jsi::Function::createFromHostFunction(
    runtime,
    jsi::PropNameID::forAscii(runtime, "__drawCircle"),
    2, // 参数个数: radius, color
    [](jsi::Runtime &rt,
       const jsi::Value &thisVal,
       const jsi::Value *args,
       size_t count) -> jsi::Value {

      // 参数校验
      if (count < 2) {
        throw jsi::JSError(rt, "__drawCircle requires 2 arguments: radius, color");
      }

      int radius = static_cast<int>(args[0].asNumber());
      uint32_t color = static_cast<uint32_t>(args[1].asNumber());

      if (radius <= 0 || radius > 2048) {
        throw jsi::JSError(rt, "radius must be between 1 and 2048");
      }

      // 调用 C++ 实现
      auto result = drawCircle(radius, color);

      // 创建 ArrayBuffer，拷贝像素数据
      auto buffer = jsi::ArrayBuffer::createFromBytes(
        rt,
        result.pixels.data(),
        result.pixels.size()
      );

      // 构造返回对象: { width, height, buffer }
      auto obj = jsi::Object(rt);
      obj.setProperty(rt, "width", jsi::Value(result.width));
      obj.setProperty(rt, "height", jsi::Value(result.height));
      obj.setProperty(rt, "buffer", std::move(buffer));

      return obj;
    });

  // 注册到全局
  rt.global().setProperty(runtime, "__drawCircle", std::move(drawCircleFunc));
}

} // namespace circleplugin

#include "CircleJSI.h"

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

      // 创建 ArrayBuffer (RN 0.73 通过 MutableBuffer)
      auto buffer = jsi::ArrayBuffer(
        rt,
        std::make_shared<RawBuffer>(std::move(result.pixels))
      );

      // 构造返回对象: { width, height, buffer }
      auto obj = jsi::Object(rt);
      obj.setProperty(rt, "width", jsi::Value(result.width));
      obj.setProperty(rt, "height", jsi::Value(result.height));
      obj.setProperty(rt, "buffer", std::move(buffer));

      return obj;
    });

  // 注册到全局
  runtime.global().setProperty(runtime, "__drawCircle", std::move(drawCircleFunc));
}

} // namespace circleplugin

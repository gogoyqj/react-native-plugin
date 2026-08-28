#include "CircleDrawer.h"
#include <cmath>

namespace circleplugin {

CircleResult drawCircle(int radius, uint32_t color) {
  int size = radius * 2;
  CircleResult result;
  result.width = size;
  result.height = size;
  result.pixels.resize(size * size * 4, 0);

  uint8_t r = (color >> 24) & 0xFF;
  uint8_t g = (color >> 16) & 0xFF;
  uint8_t b = (color >> 8)  & 0xFF;
  uint8_t a =  color        & 0xFF;

  float cx = radius - 0.5f;
  float cy = radius - 0.5f;
  float r2 = static_cast<float>(radius) * radius;

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      float dx = x - cx;
      float dy = y - cy;
      if (dx * dx + dy * dy <= r2) {
        int idx = (y * size + x) * 4;
        result.pixels[idx + 0] = r;
        result.pixels[idx + 1] = g;
        result.pixels[idx + 2] = b;
        result.pixels[idx + 3] = a;
      }
    }
  }

  return result;
}

} // namespace circleplugin

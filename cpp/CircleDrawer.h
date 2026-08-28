#pragma once

#include <cstdint>
#include <vector>

namespace circleplugin {

struct CircleResult {
  std::vector<uint8_t> pixels; // RGBA buffer
  int width;
  int height;
};

/**
 * Draw a filled circle as RGBA pixel data.
 *
 * @param radius  Circle radius in pixels
 * @param color   Fill color as 0xRRGGBBAA
 * @return        RGBA pixel buffer with dimensions (2*radius x 2*radius)
 */
CircleResult drawCircle(int radius, uint32_t color);

} // namespace circleplugin
